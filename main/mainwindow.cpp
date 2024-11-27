/********************************************************************************
 *  Puspose:
 *      mainwidnows.cpp
 *
 * Author:
 *      zhang shuanggui
 *
 * create time:
 *      2025/11/25
 *
 *******************************************************************************/

/////////////////////////////////////////////////////////////////////////////////
///
///  @brief 头文件
///
#include "mainwindow.h"
#include "QLabel"
#include "math.h"
#include "ui_mainwindow.h"
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QProgressDialog>
#include <QString>
#include <QTextStream>
#include <QFileDialog>
#include <QThreadPool>
#include <QLineEdit>
#include <QtNetwork/QHostAddress>
#include <QtNetwork/QTcpSocket>
#include <cassert>
#include "Form/DushenCameraWidget.h"
#include "HsListener.h"
#include "Global.h"
#include <opencv2/core/ocl.hpp>
#include <opencv2/cudaimgproc.hpp>
#include <opencv2/dnn/dnn.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/core/cuda.hpp>
#include <opencv2/dnn.hpp>
#include <chrono>
#include <opencv2/cudawarping.hpp>
#include <opencv2/cudafilters.hpp>
#include <opencv2/opencv.hpp>
#include <QRegularExpression>

/////////////////////////////////////////////////////////////////////////////////
///
///  @brief dll函数指针声明
///
typedef HSDatabaseNamespace::HSDatabaseInterface* (*CreateDatabaseObjectFunc1)();
typedef HSAlgorithmNamespace::HSAlgorithmInterface* (*createAlgorithmObjectFunc1)();
typedef CameraNameSpace::HSCameraInterface* (*createCameraObjectFunc1)();
typedef SocketNameSpace::HSSocketInterface* (*createSocketObjectFunc1)();
typedef HSJsoncppNamespace::HSJsoncppInterface* (*createJsoncppObjectFunc)();


/////////////////////////////////////////////////////////////////////////////////
/// \brief MainWindow::MainWindow 构造函数 public
/// \param parent
///
MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , dataanalysisPtr(nullptr)
    , hbox_layout(nullptr)
{
    ui->setupUi(this);
    classes =  std::vector<QString>{tr("JieShi_Min"),
                                    tr("MaoXu_Min"),
                                    tr("QiPao_Min"),
                                    tr("ShuiDi_Min"),
                                    tr("BoLiXue_Min"),
                                    tr("HeiDian_Min"),
                                    tr("HuaShang_Min")};
    //
    // 设置窗口属性
    // Qt::FramelessWindowHint(无窗口边框)
    // Qt::WindowSystemMenuHint(为窗口添加一个窗口系统系统菜单，并尽可能地添加一个关闭按钮)
    // Qt::WindowMinMaxButtonsHint(为窗口添加一个“最小化”按钮 和一个“最大化”按钮)
    //
    setWindowFlags(Qt::FramelessWindowHint | Qt::WindowSystemMenuHint | Qt::WindowMinMaxButtonsHint);

    MainWindow::InitComponents();
    MainWindow::InitDatabaseParam();
    MainWindow::InitRegisterMetaType();
    MainWindow::InitToolBar();
    MainWindow::InitGlassStaticTableWidget();
    MainWindow::InitSingleFlawTableWidget();
    MainWindow::InitSingleSizeTableWidget();
    MainWindow::InitCameraSettingTableWidget();
    MainWindow::InitRealTimeFlawTableWidget();
    MainWindow::InitFlawShowWidget();
    MainWindow::InitSummaryTableWidget();

    this->showMaximized();
    QWidget::showFullScreen();
    cv::utils::logging::setLogLevel(cv::utils::logging::LOG_LEVEL_ERROR);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////
/// \brief MainWindow::~MainWindow 析构函数
///
MainWindow::~MainWindow()
{
    delete ui;
}

///////////////////////////////////////public//////////////////////////////////////////////////////////////
void MainWindow::InitComponents()
{
    // 加载共享组件HSTool
    QString exePath = QCoreApplication::applicationDirPath();
    //
    // 动态加载数据库组件
    //
    if (databasePtr == nullptr) {
        QString dllPath = exePath + "/../database/database.dll";
        databaseDllHandle = LoadLibrary(dllPath.toStdWString().c_str());
        if (!databaseDllHandle) {
            qDebug() << "Failed to load DLL. Error code: " << GetLastError();
        }
        // 获取创建数据库对象的函数指针
        CreateDatabaseObjectFunc1 createFunc = (CreateDatabaseObjectFunc1)GetProcAddress(databaseDllHandle, "createDatabaseObject");
        if (!createFunc) {
            qDebug() << "Failed to get function pointer. Error code: " << GetLastError() ;
            FreeLibrary(databaseDllHandle);
            QString mes = "加载数据库组件失败。";
            INFOMATION.outputMessage(ui->loglistWidget,mes);
        } else {
            qDebug() << "Success to get CreateDatabaseObjectFunc1 function pointer. ";
            QString mes = "加载数据库组件成功。";
            INFOMATION.outputMessage(ui->loglistWidget,mes);
        }
        databasePtr = createFunc();
        databasePtr->openDataBase();//打开数据库
    }
    //
    // 动态加载算法组件
    //
    if (algorithmPtr== nullptr) {
        QString dllPath = exePath + "/../algorithm/algorithm.dll";
        algorithmDllHandle = LoadLibrary(dllPath.toStdWString().c_str());
        if (!algorithmDllHandle) {
            qDebug() << "Failed to load DLL. Error code: " << GetLastError();
        }
        // 获取创建数据库对象的函数指针
        createAlgorithmObjectFunc1 createFunc = (createAlgorithmObjectFunc1)GetProcAddress(algorithmDllHandle, "createAlgorithmObject");
        if (!createFunc) {
            qDebug() << "Failed to get function pointer. Error code: " << GetLastError() ;
            FreeLibrary(algorithmDllHandle);
            QString mes = "加载算法组件失败。";
            INFOMATION.outputMessage(ui->loglistWidget,mes);
        } else {
            qDebug() << "Success to get  createAlgorithmObjectFunc1 function pointer. ";
            QString mes = "加载算法组件成功。";
            INFOMATION.outputMessage(ui->loglistWidget,mes);
        }
        algorithmPtr = createFunc();
    }
    //
    // 动态加载相机组件
    //
    if ( cameraPtr0 == nullptr && cameraPtr1 == nullptr) {
        QString dllPath = exePath + "/../camare/camera.dll";
        cameraDllHandle = LoadLibrary(dllPath.toStdWString().c_str());
        if (!cameraDllHandle) {
            qDebug() << "Failed to load DLL. Error code: " << GetLastError();
        }
        // 获取创建数据库对象的函数指针
        createCameraObjectFunc1 createFunc = (createCameraObjectFunc1)GetProcAddress(cameraDllHandle, "createCameraObject");
        if (!createFunc) {
            qDebug() << "Failed to get function pointer. Error code: " << GetLastError() ;
            FreeLibrary(cameraDllHandle);
            QString mes = "加载相机组件失败。";
            INFOMATION.outputMessage(ui->loglistWidget,mes);
        } else {
            qDebug() << "Success to get  createCameraObjectFunc1 function pointer. ";
            QString mes = "加载相机组件成功。";
            INFOMATION.outputMessage(ui->loglistWidget,mes);
        }
        cameraPtr0 = createFunc();
        cameraPtr1 = createFunc();
    }
    //
    // 动态加载jsoncpp组件
    //
    if (jsoncppPtr==nullptr) {
        QString exePath = QCoreApplication::applicationDirPath();
        QString dllPath = exePath + "/../jsoncpp/jsoncpp.dll";
        jsoncppDllHandle = LoadLibrary(dllPath.toStdWString().c_str());
        if (!jsoncppDllHandle) {
            qFatal() << "Failed to load DLL. Error code: " << GetLastError();
        }
        // 获取创建数据库对象的函数指针
        createJsoncppObjectFunc createFunc = (createJsoncppObjectFunc)GetProcAddress(jsoncppDllHandle, "createJsoncppObject");
        if (!createFunc) {
            qDebug() << "Failed to get function pointer. Error code: " << GetLastError() ;
            FreeLibrary(jsoncppDllHandle);
            QString mes = "加载jsoncpp组件失败。";
            INFOMATION.outputMessage(ui->loglistWidget,mes);
        } else {
            qDebug() << "Success to get  jsoncppDllHandle function pointer. ";
            QString mes = "加载jsoncpp组件成功。";
            INFOMATION.outputMessage(ui->loglistWidget,mes);
        }
        jsoncppPtr = createFunc();
    }
    //
    // 声明设置对象指针
    //
    if(m_lightControl == nullptr) {
        m_lightControl = std::make_shared<LightControl>(nullptr);//设置窗口
    }
    //
    // 声明标定指针
    //
    if (calibratePtr == nullptr) {
        calibratePtr = std::make_shared<Calibrate>(nullptr);
    }
}

void MainWindow::InitRegisterMetaType()
{
    //注册自定义类型，供connect调用
    qRegisterMetaType<QAbstractSocket::SocketState>("QAbstractSocket::SocketState");
}

void MainWindow::InitToolBar()
{
    // 退出按钮
    m_pExit = new QAction("&退出", this);
    m_pExit->setShortcut(QKeySequence::Quit);
    m_pExit->setToolTip(tr("Exit System."));
    m_pExit->setIcon(QIcon(":/icons/exit.png"));
    ui->toolBar->addAction(m_pExit);
    // 设置按钮
    m_pSettings = new QAction("&设置", this);
    m_pSettings->setToolTip(tr("Device Settings."));
    m_pSettings->setIcon(QIcon(":/icons/setup.png"));
    ui->toolBar->addAction(m_pSettings);
    // 开始按钮
    m_pStart = new QAction("&开始", this);
    m_pStart->setToolTip(tr("Start."));
    m_pStart->setIcon(QIcon(":/icons/start_icon.png"));
    ui->toolBar->addAction(m_pStart);
    // 停止按钮
    m_pStop = new QAction("&停止", this);
    m_pStop->setToolTip(tr("Stop."));
    m_pStop->setIcon(QIcon(":/icons/Stop.png"));
    ui->toolBar->addAction(m_pStop);
    m_pStop->setEnabled(false);
    // 数据查询按钮
    m_pDB = new QAction("&数据查询", this);
    m_pDB->setShortcut(QKeySequence::Quit);
    m_pDB->setToolTip(tr("Database."));
    m_pDB->setIcon(QIcon(":/icons/analysis.png"));
    ui->toolBar->addAction(m_pDB);
    // 离线模式
    m_offline = new QAction("&离线模式", this);
    m_offline->setToolTip(tr("Offline."));
    m_offline->setIcon(QIcon(":/icons/switch.png"));
    ui->toolBar->addAction(m_offline);
    // 标定
    m_calibrate = new QAction("&标定", this);
    m_calibrate->setToolTip(tr("calibrate."));
    m_calibrate->setIcon(QIcon(":/icons/glass.png"));
    ui->toolBar->addAction(m_calibrate);

    ui->toolBar->setIconSize(QSize(40, 40));
    ui->toolBar->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    ui->toolBar->toggleViewAction()->setEnabled(false);
    ui->toolBar->setFloatable(false);
    ui->toolBar->setMovable(false);
    //
    // 标题栏
    //
    connect(m_pExit, SIGNAL(triggered()), this, SLOT(slot_CloseSystem()));                  //点击退出响应事件
    connect(m_pSettings, SIGNAL(triggered()), this,SLOT(slot_ShowSystemSettingForm()));     //点击设置响应事件
    connect(m_pStart, SIGNAL(triggered()), this, SLOT(slot_ActionStart()));                 //点击开始响应事件
    connect(m_pStop, SIGNAL(triggered()), this, SLOT(slot_ActionStop()));                   //点击停止响应事件
    connect(m_pDB, SIGNAL(triggered()), this, SLOT(slot_DataSearch()));                     //点击数据查询响应事件
    connect(m_offline, SIGNAL(triggered()), this, SLOT(slot_Offline()));                    //点击离线模式响应事件
    connect(m_calibrate, SIGNAL(triggered()), this, SLOT(slot_Calibrate()));                //点击标定响应时间
}

void MainWindow::InitGlassStaticTableWidget()
{
    //
    // 设置表头
    //
    QStringList headerLabels = {tr("ID"),
                                tr("time"),
                                tr("OK/NG"),
                                tr("sizeOK/NG"),
                                tr("length"),
                                tr("width"),
                                tr("diagonal1"),
                                tr("diagonal2"),
                                tr("defectNumber"),
                                tr("defectOK/NG"),
                                tr("huashan"),
                                tr("qipao"),
                                tr("jieshi"),
                                tr("benbian"),
                                tr("zanwu"),
                                tr("liewen"),
                                tr("qita")};
    ui->glassstatictablewidget->setColumnCount(headerLabels.size());
    ui->glassstatictablewidget->setHorizontalHeaderLabels(headerLabels);

    ui->glassstatictablewidget->setColumnWidth(0, 100);
    ui->glassstatictablewidget->setColumnWidth(1, 200);
    ui->glassstatictablewidget->setColumnWidth(2, 100);
    ui->glassstatictablewidget->setColumnWidth(3, 100);
    ui->glassstatictablewidget->setColumnWidth(4, 100);
    ui->glassstatictablewidget->setColumnWidth(5, 100);
    ui->glassstatictablewidget->setColumnWidth(6, 100);
    ui->glassstatictablewidget->setColumnWidth(7, 100);
    ui->glassstatictablewidget->setColumnWidth(8, 100);
    ui->glassstatictablewidget->setColumnWidth(9, 100);
    ui->glassstatictablewidget->setColumnWidth(10, 100);
    ui->glassstatictablewidget->setColumnWidth(11, 100);
    ui->glassstatictablewidget->setColumnWidth(12, 100);
    ui->glassstatictablewidget->setColumnWidth(13, 100);
    ui->glassstatictablewidget->setColumnWidth(14, 100);
    ui->glassstatictablewidget->setColumnWidth(15, 100);
    ui->glassstatictablewidget->setColumnWidth(16, 100);
    //
    // 读取数据库信息，插入数据统计表格中
    //
    QString sql = "SELECT * FROM glass_table ORDER BY id DESC LIMIT 100;";
    std::vector<GlassDataBaseInfo2> datas;
    databasePtr->queryTableData(datas, sql);
    for (int i=0; i < (int)datas.size(); ++i) {
        GlassDataBaseInfo2 data = datas[i];
        ui->glassstatictablewidget->insertRow(0);
        //ID
        QTableWidgetItem* id = new QTableWidgetItem(QString::number(data.id));
        id->setTextAlignment(Qt::AlignCenter);
        id->setFlags(id->flags() & ~Qt::ItemIsEditable);
        ui->glassstatictablewidget->setItem(0, 0, id);
        //时间
        QTableWidgetItem* time = new QTableWidgetItem(data.time);
        time->setTextAlignment(Qt::AlignCenter);
        time->setFlags(time->flags() & ~Qt::ItemIsEditable);
        ui->glassstatictablewidget->setItem(0, 1, time);
        //OK/NG
        QTableWidgetItem* isok = new QTableWidgetItem(data.OKorNG);
        isok->setTextAlignment(Qt::AlignCenter);
        isok->setFlags(isok->flags() & ~Qt::ItemIsEditable);
        ui->glassstatictablewidget->setItem(0, 2, isok);
        //尺寸OK/NG
        QTableWidgetItem* issizeok = new QTableWidgetItem(data.sizeOKorNG);
        issizeok->setTextAlignment(Qt::AlignCenter);
        issizeok->setFlags(issizeok->flags() & ~Qt::ItemIsEditable);
        ui->glassstatictablewidget->setItem(0, 3, issizeok);
        //长度
        QTableWidgetItem* length = new QTableWidgetItem(QString::number(data.width,'f', 2));//??这里为啥要对调
        length->setTextAlignment(Qt::AlignCenter);
        length->setFlags(length->flags() & ~Qt::ItemIsEditable);
        ui->glassstatictablewidget->setItem(0, 4, length);
        //宽度
        QTableWidgetItem* width = new QTableWidgetItem(QString::number(data.length,'f', 2));//??这里为啥要对调
        width->setTextAlignment(Qt::AlignCenter);
        width->setFlags(width->flags() & ~Qt::ItemIsEditable);
        ui->glassstatictablewidget->setItem(0, 5, width);
        //对角线1
        QTableWidgetItem* diagonal1 = new QTableWidgetItem(QString::number(data.duijiaoxian1,'f', 2));
        diagonal1->setTextAlignment(Qt::AlignCenter);
        diagonal1->setFlags(diagonal1->flags() & ~Qt::ItemIsEditable);
        ui->glassstatictablewidget->setItem(0, 6, diagonal1);
        //对角线2
        QTableWidgetItem* diagonal2 = new QTableWidgetItem(QString::number(data.duijiaoxian2,'f', 2));
        diagonal2->setTextAlignment(Qt::AlignCenter);
        diagonal2->setFlags(diagonal2->flags() & ~Qt::ItemIsEditable);
        ui->glassstatictablewidget->setItem(0, 7, diagonal2);
        //缺陷数量
        QTableWidgetItem* flawcount = new QTableWidgetItem(QString::number(data.defectNumber));
        flawcount->setTextAlignment(Qt::AlignCenter);
        flawcount->setFlags(flawcount->flags() & ~Qt::ItemIsEditable);
        ui->glassstatictablewidget->setItem(0, 8, flawcount);
        //缺陷OK/NG
        QTableWidgetItem* isflawok = new QTableWidgetItem(data.defectOKorNG);
        isflawok->setTextAlignment(Qt::AlignCenter);
        isflawok->setFlags(isflawok->flags() & ~Qt::ItemIsEditable);
        ui->glassstatictablewidget->setItem(0, 9, isflawok);
        //划伤
        QTableWidgetItem* flaw1 = new QTableWidgetItem(QString::number(data.huashanNumber));
        flaw1->setTextAlignment(Qt::AlignCenter);
        flaw1->setFlags(flaw1->flags() & ~Qt::ItemIsEditable);
        ui->glassstatictablewidget->setItem(0, 10, flaw1);
        //气泡
        QTableWidgetItem* flaw2 = new QTableWidgetItem(QString::number(data.qipaoNumber));
        flaw2->setTextAlignment(Qt::AlignCenter);
        flaw2->setFlags(flaw2->flags() & ~Qt::ItemIsEditable);
        ui->glassstatictablewidget->setItem(0, 11, flaw2);
        //结石
        QTableWidgetItem* flaw7 = new QTableWidgetItem(QString::number(data.jieshiNumber));
        flaw7->setTextAlignment(Qt::AlignCenter);
        flaw7->setFlags(flaw7->flags() & ~Qt::ItemIsEditable);
        ui->glassstatictablewidget->setItem(0, 12, flaw7);
        //崩边
        QTableWidgetItem* flaw3 = new QTableWidgetItem(QString::number(data.benbianNumber));
        flaw3->setTextAlignment(Qt::AlignCenter);
        flaw3->setFlags(flaw3->flags() & ~Qt::ItemIsEditable);
        ui->glassstatictablewidget->setItem(0, 13, flaw3);
        //脏污
        QTableWidgetItem* flaw4 = new QTableWidgetItem(QString::number(data.zanwuNumber));
        flaw4->setTextAlignment(Qt::AlignCenter);
        flaw4->setFlags(flaw4->flags() & ~Qt::ItemIsEditable);
        ui->glassstatictablewidget->setItem(0, 14, flaw4);
        //裂纹
        QTableWidgetItem* flaw5 = new QTableWidgetItem(QString::number(data.liewenNumber));
        flaw5->setTextAlignment(Qt::AlignCenter);
        flaw5->setFlags(flaw5->flags() & ~Qt::ItemIsEditable);
        ui->glassstatictablewidget->setItem(0, 15, flaw5);
        //其他
        QTableWidgetItem* flaw6 = new QTableWidgetItem(QString::number(data.qitaNumber));
        flaw6->setTextAlignment(Qt::AlignCenter);
        flaw6->setFlags(flaw6->flags() & ~Qt::ItemIsEditable);
        ui->glassstatictablewidget->setItem(0, 16, flaw6);

        // 设置表格内容居中显示
        for (int i = 0; i < ui->glassstatictablewidget->columnCount(); ++i) {
            ui->glassstatictablewidget->horizontalHeaderItem(i)->setTextAlignment(Qt::AlignCenter);
        }
        ui->glassstatictablewidget->verticalHeader()->setVisible(false); // 隐藏行号
    }
}

void MainWindow::InitSingleFlawTableWidget()
{
    //
    // 初始化单个缺陷界面
    //
    QGraphicsScene* scene = new QGraphicsScene();
    loadedPixmapItem = new MyGraphicsItem();
    scene->addItem(loadedPixmapItem);
    ui->graphicsView->setScene(scene);

    QGraphicsScene* scene2 = new QGraphicsScene();
    loadedPixmapItem2 = new MyGraphicsItem();
    scene2->addItem(loadedPixmapItem2);
    ui->graphicsView_2->setScene(scene2);

    QGraphicsScene* scene3 = new QGraphicsScene();
    loadedPixmapItem3 = new MyGraphicsItem();
    scene3->addItem(loadedPixmapItem3);
    ui->graphicsView_3->setScene(scene3);

    ui->SingleFlawtableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->SingleFlawtableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->SingleFlawtableWidget->verticalHeader()->setVisible(false);
    ui->SingleFlawtableWidget->setColumnWidth(0, 90);

    for (int row = 0; row < ui->SingleFlawtableWidget->rowCount(); ++row) {
        for (int col = 0; col < ui->SingleFlawtableWidget->columnCount(); ++col) {
            QTableWidgetItem* item = ui->SingleFlawtableWidget->item(row, col);
            if (item) {
                item->setFlags(item->flags() & ~Qt::ItemIsEditable);
            }
        }
    }
    //
    // 若数据统计界面不为空，则显示第一行玻璃的缺陷信息
    //
    QTableWidgetItem *itemID = ui->glassstatictablewidget->item(0, 0);
    if (itemID != NULL) {
        int glassid = itemID->text().toInt();
        QString sql = QString("SELECT * FROM glass_defect WHERE glassid = %1;").arg(glassid);
        std::vector<GlassDefect2> datas;
        databasePtr->queryTableData(datas, sql);
        if (datas.size() > 0) {
            ui->SingleFlawtableWidget->setRowCount(datas.size());
            ui->SingleFlawtableWidget->setColumnCount(9);
            //
            // 更新缺陷小图
            //
            QImage img1(datas[0].imagePath);
            QImage img2(datas[0].imagePath);
            QImage img3(datas[0].imagePath);

            loadedPixmapItem->loadImage(img1);
            int nwidth = ui->graphicsView->width();
            int nheight = ui->graphicsView->height();
            loadedPixmapItem->setQGraphicsViewWH(nwidth, nheight);
            ui->graphicsView->setSceneRect((QRectF(-(nwidth / 2), -(nheight / 2), nwidth, nheight)));

            loadedPixmapItem2->loadImage(img2);
            int nwidth2 = ui->graphicsView_2->width();
            int nheight2 = ui->graphicsView_2->height();
            loadedPixmapItem2->setQGraphicsViewWH(nwidth, nheight);
            ui->graphicsView_2->setSceneRect((QRectF(-(nwidth2 / 2), -(nheight2 / 2), nwidth2, nheight2)));

            loadedPixmapItem3->loadImage(img3);
            int nwidth3 = ui->graphicsView_3->width();
            int nheight3 = ui->graphicsView_3->height();
            loadedPixmapItem3->setQGraphicsViewWH(nwidth, nheight);
            ui->graphicsView_3->setSceneRect((QRectF(-(nwidth3 / 2), -(nheight3 / 2), nwidth3, nheight3)));
            for (int i = 0; i < (int)datas.size(); ++i) {
                GlassDefect2 data = datas[i];
                //序号
                QTableWidgetItem* item0 = new QTableWidgetItem(QString::number(data.defectId));
                item0->setTextAlignment(Qt::AlignCenter);
                ui->SingleFlawtableWidget->setItem(i, 0, item0);
                //时间
                QTableWidgetItem* item1 = new QTableWidgetItem(data.time);
                item1->setTextAlignment(Qt::AlignCenter);
                ui->SingleFlawtableWidget->setItem(i, 1, item1);
                //类型
                QTableWidgetItem* item2 = new QTableWidgetItem(data.defectType);
                item2->setTextAlignment(Qt::AlignCenter);
                ui->SingleFlawtableWidget->setItem(i , 2, item2);
                //等级
                QTableWidgetItem* item3 = new QTableWidgetItem(data.defectLevel);
                item3->setTextAlignment(Qt::AlignCenter);
                ui->SingleFlawtableWidget->setItem(i, 3, item3);
                //坐标X
                QTableWidgetItem* item4 = new QTableWidgetItem(QString::number(data.x,'f', 2));
                item4->setTextAlignment(Qt::AlignCenter);
                ui->SingleFlawtableWidget->setItem(i, 4, item4);
                //坐标Y
                QTableWidgetItem* item5 = new QTableWidgetItem(QString::number(data.y,'f', 2));
                item5->setTextAlignment(Qt::AlignCenter);
                ui->SingleFlawtableWidget->setItem(i, 5, item5);
                //长
                QTableWidgetItem* item6 = new QTableWidgetItem(QString::number(data.length,'f', 2));
                item6->setTextAlignment(Qt::AlignCenter);
                ui->SingleFlawtableWidget->setItem(i, 6, item6);
                //宽
                QTableWidgetItem* item7 = new QTableWidgetItem(QString::number(data.width,'f', 2));
                item7->setTextAlignment(Qt::AlignCenter);
                ui->SingleFlawtableWidget->setItem(i, 7, item7);
                //区域
                QTableWidgetItem* item8 = new QTableWidgetItem(QString::number(data.area,'f', 2));
                item8->setTextAlignment(Qt::AlignCenter);
                ui->SingleFlawtableWidget->setItem(i, 8, item8);
            }
        }
    }
}

void MainWindow::InitSingleSizeTableWidget()
{
    //
    // 初始化尺寸信息界面
    //
    QGraphicsScene* scene = new QGraphicsScene();
    loadedPixmapItem4 = new MyGraphicsItem();
    ui->graphicsView_outLine->setScene(scene);
    scene->addItem(loadedPixmapItem);

    QGraphicsScene* scene2=new QGraphicsScene();
    loadedPixmapItem5 = new MyGraphicsItem();
    ui->graphicsView_Field->setScene(scene2);
    scene2->addItem(loadedPixmapItem2);

    ui->singleSizeTableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->singleSizeTableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->singleSizeTableWidget->verticalHeader()->setVisible(false);
    ui->singleSizeTableWidget->setColumnWidth(0, 90);

    for (int row = 0; row < ui->singleSizeTableWidget->rowCount(); ++row) {
        for (int col = 0; col < ui->singleSizeTableWidget->columnCount(); ++col) {
            QTableWidgetItem* item = ui->singleSizeTableWidget->item(row, col);
            if (item) {
                item->setFlags(item->flags() & ~Qt::ItemIsEditable);
            }
        }
    }
    //
    // todo:
    //
}

void MainWindow::InitCameraSettingTableWidget()
{
    hbox_layout = new QHBoxLayout(ui->tab_6);
    DushenCameraArgs arg0;
    arg0.camName = PARAM.Camera0Name;
    arg0.camNumber = PARAM.camDefineNum;
    arg0.fieldnumberset = PARAM.SelectedLightFieldNumber;
    arg0.expo = PARAM.Camera0ExposureTime;
    arg0.framecount = PARAM.Camera0Frame;
    arg0.height = PARAM.Camera0PhotoRow;
    arg0.gain = PARAM.Camera0Gain;
    qDebug()<<"arg0.camName = "<<arg0.camName
             <<",arg0.camNumber="<<arg0.camNumber
             <<",arg0.fieldnumberset="<<arg0.fieldnumberset
             <<",arg0.expo="<<arg0.expo
             <<",arg0.framecount="<<arg0.framecount
             <<",arg0.height="<<arg0.height
             <<",arg0.gain ="<<arg0.gain;
    m_args.push_back(arg0);
    DushenCameraArgs arg1;
    arg1.camName = PARAM.Camera1Name;
    arg1.camNumber = PARAM.camDefineNum;
    arg1.fieldnumberset = PARAM.SelectedLightFieldNumber;
    arg1.expo = PARAM.Camera1ExposureTime;
    arg1.framecount = PARAM.Camera1Frame;
    arg1.height = PARAM.Camera1PhotoRow;
    arg1.gain = PARAM.Camera1Gain;
    qDebug()<<"arg1.camName = "<<arg1.camName
             <<",arg1.camNumber="<<arg1.camNumber
             <<",arg1.fieldnumberset="<<arg1.fieldnumberset
             <<",arg1.expo="<<arg1.expo
             <<",arg1.framecount="<<arg1.framecount
             <<",arg1.height="<<arg1.height
             <<",arg1.gain ="<<arg1.gain;
    m_args.push_back(arg1);
    DushenCameraWidget * camerawid = new DushenCameraWidget(nullptr);
    camerawid->InitDushenCameraWidget(cameraPtr0,m_args[0]);
    hbox_layout->addWidget(camerawid);
    DushenCameraWidget * camerawid1 = new DushenCameraWidget(nullptr);
    camerawid1->InitDushenCameraWidget(cameraPtr1,m_args[1]);
    hbox_layout->addWidget(camerawid1);
    //启动相机
    camerawid->StartCamera();
    camerawid1->StartCamera();
}

void MainWindow::InitRealTimeFlawTableWidget()
{
    QGraphicsScene* scene=new QGraphicsScene();
    loadedPixmapItem6 = new MyGraphicsItem();
    scene->addItem(loadedPixmapItem6);
    ui->graphicsView_Field1->setScene(scene);

    QGraphicsScene* scene2=new QGraphicsScene();
    loadedPixmapItem7= new MyGraphicsItem();
    scene2->addItem(loadedPixmapItem7);
    ui->graphicsView_Field2->setScene(scene2);

    QGraphicsScene* scene3=new QGraphicsScene();
    loadedPixmapItem8 = new MyGraphicsItem();
    scene3->addItem(loadedPixmapItem8);
    ui->graphicsView_Field3->setScene(scene3);
}

void MainWindow::InitFlawShowWidget()
{
    //
    // todo：缺陷主界面显示，显示opencv已经处理好的图片
    //
}

void MainWindow::InitSummaryTableWidget()
{
    //
    // 时间定时刷新
    //
    _timer = new QTimer();
    connect(_timer, &QTimer::timeout, this, &MainWindow::slot_RefreshSystemTime);
    _timer->start(1000);
    //
    // 读取数据库获取初始化值
    //

    QString sql = "SELECT * FROM glass_summary ORDER BY time DESC LIMIT 1;";
    std::vector<GlassSummary> datas;
    databasePtr->queryTableData(datas, sql);
    if (datas.size()  > 0){
        m_summary = datas[0];
    }
    ui->glassTotalCountLB->setText(QString::number(m_summary.glasstotalcount));
    ui->glassTotalCountLB->setAlignment(Qt::AlignCenter);

    ui->currentGlassStatus->setText(QString(m_summary.currentglassstatus));
    ui->currentGlassStatus->setAlignment(Qt::AlignCenter);

    ui->glassOKCountLB->setText(QString::number(m_summary.OKcount));
    ui->glassOKCountLB->setAlignment(Qt::AlignCenter);

    ui->glassNGCountLB->setText(QString::number(m_summary.NGcount));
    ui->glassNGCountLB->setAlignment(Qt::AlignCenter);

    ui->qualicaficationRateLB->setText(QString::number(m_summary.passrate));
    ui->qualicaficationRateLB->setAlignment(Qt::AlignCenter);

    ui->ExceptionCountLB->setText(QString::number(m_summary.exceptioncount));
    ui->ExceptionCountLB->setAlignment(Qt::AlignCenter);
}

void MainWindow::InitDatabaseParam()
{
    if (databasePtr!=nullptr) {
        //启动程序时，获取新的主键
        int64_t newID = 0;
        databasePtr->getCurrentDefectTableMaxID(newID);
        defectPrimaryKey = newID;
        int64_t newGlassID = 0;
        databasePtr->getCurrentGlassTableMaxID(newGlassID);
        glassPrimaryKey = newGlassID;
        int64_t newSizeID = 0;
        databasePtr->getCurrentSizeTableMaxID(newSizeID);
        sizePrimaryKey = newSizeID;
    } else {
        qDebug()<<"InitDatabaseParam fail";
    }
    // PARAM赋值读取
    if (jsoncppPtr!= nullptr) {
        QString iniPath = QDir::currentPath() + QString("/") + SYSTEMNAME;
        qDebug()<<"iniPath ="<<iniPath;
        QFile inifile(iniPath);
        if (!inifile.exists()) {
            qDebug()<<"iniPath is not exist.=>"<<iniPath;
        }
        QString needLoadJsonFile = PARAM.GetParamterFromIniFile(iniPath,"system/recipe");//需要加载的工单名称system模块的recipe配置文件
        QString neddLoadJsonFileName = QDir::currentPath() + QString("/Recipes/") + needLoadJsonFile + QString(".json");
        qDebug()<<"neddLoadJsonFileName = "<<neddLoadJsonFileName;
        SignalControl signalctrl;
        jsoncppPtr->readRecipeFromJson(neddLoadJsonFileName, signalctrl);
        // 初始化全局变量
        PARAM.SystemName = signalctrl.systemName;
        PARAM.camDefineNum = signalctrl.CamareNumber;
        PARAM.Camera0Name = signalctrl.Camare0Name;
        PARAM.Camera1Name = signalctrl.Camare1Name;
        PARAM.Camera2Name = signalctrl.Camare2Name;
        PARAM.Camera3Name = signalctrl.Camare3Name;
        PARAM.serverIp = signalctrl.ServerIP;
        PARAM.serverPort = signalctrl.ServerPort;
        PARAM.YAccuracy = signalctrl.YAccuracy;
        PARAM.XCamera0Accuracy = signalctrl.XCamera0Accuracy;
        PARAM.XCamera1Accuracy = signalctrl.XCamera1Accuracy;
        PARAM.Camera0Frame = signalctrl.Camera0Frame;
        PARAM.Camera0PhotoRow = signalctrl.Camera0PhotoRow;
        PARAM.Camera0ExposureTime = signalctrl.Camera0ExposureTime;
        PARAM.Camera0Gain = signalctrl.Camera0Gain;
        PARAM.Camera1Frame = signalctrl.Camera1Frame;
        PARAM.Camera1PhotoRow = signalctrl.Camera1PhotoRow;
        PARAM.Camera1ExposureTime = signalctrl.Camera1ExposureTime;
        PARAM.Camera1Gain = signalctrl.Camera1Gain;
        PARAM.Camera2Frame = signalctrl.Camera2Frame;
        PARAM.Camera2PhotoRow = signalctrl.Camera2PhotoRow;
        PARAM.Camera2ExposureTime = signalctrl.Camera2ExposureTime;
        PARAM.Camera2Gain = signalctrl.Camera2Gain;
        PARAM.Camera3Frame = signalctrl.Camera3Frame;
        PARAM.Camera3PhotoRow = signalctrl.Camera3PhotoRow;
        PARAM.Camera3ExposureTime = signalctrl.Camera3ExposureTime;
        PARAM.Camera3Gain = signalctrl.Camera3Gain;
        // 控制器参数
        PARAM.EncodePulseFilterUs = signalctrl.EncodePulseFilterUs;
        PARAM.PhotoelectricSensorFiltering = signalctrl.PhotoelectricSensorFiltering;
        PARAM.WheelEncoderPhotoPulse = signalctrl.WheelEncoderPhotoPulse;
        PARAM.EncoderMode = signalctrl.EncoderMode;
        PARAM.SolenoidValve1DownDelay = signalctrl.SolenoidValve1DownDelay;
        PARAM.SolenoidValve1UpDelay = signalctrl.SolenoidValve1UpDelay;
        PARAM.SolenoidValve2DownDelay = signalctrl.SolenoidValve2DownDelay;
        PARAM.SolenoidValve2UpDelay = signalctrl.SolenoidValve2UpDelay;
        PARAM.WheelAEncoder = signalctrl.WheelAEncoder;
        PARAM.WheelBEncoder = signalctrl.WheelBEncoder;
        PARAM.ErrorPhotoCount = signalctrl.ErrorPhotoCount;
        // 光源控制器参数
        PARAM.LightField1GlowTime = signalctrl.LightField1GlowTime;
        PARAM.LightField2GlowTime = signalctrl.LightField2GlowTime;
        PARAM.LightField3GlowTime = signalctrl.LightField3GlowTime;
        PARAM.LightField4GlowTime = signalctrl.LightField4GlowTime;
        PARAM.LightSignalSynchronizationDelayRegister = signalctrl.LightSignalSynchronizationDelayRegister;
        PARAM.PhotoMode = signalctrl.PhotoMode;
        PARAM.LightCameraEnable = signalctrl.LightCameraEnable;
        PARAM.WorkMode = signalctrl.WorkMode;
        PARAM.LightSourcePulseEndPointRegister = signalctrl.LightSourcePulseEndPointRegister;
        PARAM.SyncPulsePeriodRegister = signalctrl.SyncPulsePeriodRegister;
        PARAM.CameraFrameSignalTriggerDelay = signalctrl.CameraFrameSignalTriggerDelay;
        PARAM.TimelapseAfterPhotoShootEnd = signalctrl.TimelapseAfterPhotoShootEnd;
        PARAM.SelectedLightFieldNumber = signalctrl.SelectedLightFieldNumber;
        PARAM.FrameSignalOutput = signalctrl.FrameSignalOutput;
    }
}

void MainWindow::ProcessThreadCV()
{
    //
    // 根据信号平台帧信号获取图片
    //
    unsigned int nowFrameSignal = PARAM.FrameSignalOutput;//当前帧信号状态
    m_databaseThread = std::make_shared<std::thread>(&MainWindow::SyncInsertDatabase, this);
LOOPGET:
    if ( nowFrameSignal > 0 && nowFrameSignal == PARAM.FrameSignalOutput) {         //帧信号持续拉高，玻璃中部
        qDebug()<<"1";
        MainWindow::slot_GetCameraBuffer();
        if (PARAM.currentsystem == SYSTEMSTATUS::STOP) return;
    } else if(nowFrameSignal > 0 && nowFrameSignal != PARAM.FrameSignalOutput) {    //帧信号从高到低，玻璃尾部
        qDebug()<<"2";
        MainWindow::slot_GetCameraBuffer();
        nowFrameSignal = PARAM.FrameSignalOutput; //临时帧信号拉低
        if (PARAM.currentsystem == SYSTEMSTATUS::STOP) return;
    } else if(nowFrameSignal <= 0 && nowFrameSignal != PARAM.FrameSignalOutput) {   //帧信号从低到高，玻璃开始
        qDebug()<<"3";
        ++glassPrimaryKey;
        nowFrameSignal = PARAM.FrameSignalOutput;                                   //临时帧信号拉高
        MainWindow::slot_GetCameraBuffer();                        //获取图片并处理
        if (PARAM.currentsystem == SYSTEMSTATUS::STOP) return;
    } else {                                                                        //没有帧信号
        std::this_thread::sleep_for(std::chrono::seconds(1));
        qDebug()<<"No frame signal";
    }
    if (PARAM.currentsystem != SYSTEMSTATUS::STOP) {
        goto LOOPGET;
    }
}

void MainWindow::MainWindowsDisplay(NewGlassResult result)
{
    auto start = std::chrono::high_resolution_clock::now();// 开始时间
    try{
        if (!result.isEmpty) {
            std::vector<GlassDefect2> glassDefectDatas;
            MainWindow::realUpdateDatabase(result, glassDefectDatas);// 存储入数据库
            MainWindow::upDateOverView(result.part);// 汇总信息
            MainWindow::imageDisplay(result.part, result.currentFrameCount, result.glassRegion);// 投射场图像显示
            MainWindow::UpdateStatisticsTable(result);// 统计数据
            MainWindow::realUpdateDefectTable(result.part, glassDefectDatas);// 缺陷数据更新
            MainWindow::realUpdateDefectDisplay(result);// 实时缺陷小图
            MainWindow::updateSizeInfoTable(result.sizeRes);// 缺陷尺寸数据
            MainWindow::clearGlassDisplay(result.part);//玻璃结束，清理
            auto end = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double, std::milli> duration = end - start;
            qDebug() << "Display ["<<result.currentFrameCount <<"] time：" << duration.count() << " ms";
        } else {
            qDebug()<<"result.isEmpty == true;";
        }
    } catch (...) {
        qDebug() << "MainWindow::MainWindowsDisplay => An unknown error occurred.";
        // 获取当前的异常信息
        std::exception_ptr eptr = std::current_exception();
        if (eptr) {
            try {
                std::rethrow_exception(eptr);
            } catch (const std::exception& ex) {
                qDebug() << "Exception: " << ex.what();
            }
        }
    }
}

///////////////////////////////////////////////////////private///////////////////////////////////////////////////////////////////
///
///

void MainWindow::upDateOverView(CV_GLASSPART status)
{
    if (status == CV_GLASSPART::TAIL) {//玻璃结束写入界面
        m_summary.glasstotalcount = m_summary.glasstotalcount + 1;
        m_summary.currentglassstatus = m_currentSatus;
        if (m_currentSatus == "OK") {
            m_summary.OKcount = m_summary.OKcount + 1;
        } else {
            m_summary.NGcount = m_summary.NGcount + 1;
        }
        m_summary.passrate = (double) m_summary.OKcount / m_summary.glasstotalcount;
        m_summary.exceptioncount = 0;//todo:异常结束玻璃
        ui->glassTotalCountLB->setText(QString::number(m_summary.glasstotalcount));
        ui->currentGlassStatus->setText(QString(m_summary.currentglassstatus));
        ui->glassOKCountLB->setText(QString::number(m_summary.OKcount));
        ui->glassNGCountLB->setText(QString::number(m_summary.NGcount));
        ui->qualicaficationRateLB->setText(QString::number(m_summary.passrate));
        ui->ExceptionCountLB->setText(QString::number(m_summary.exceptioncount));

        QString mes1 = "玻璃["+QString::number(glassPrimaryKey) + "] 玻璃结束状态更新成功。";
        INFOMATION.outputMessage(ui->loglistWidget,mes1);
    }
}

void MainWindow::imageDisplay(CV_GLASSPART part, int currentFrameCount, cv::Mat image)
{
    try{
        if (image.rows <= 0) {
            qDebug()<<"imageDisplay in param image.rows == 0";
            return;
        }
        //将不同帧图片拼接起来，注意非第一帧图片有重复区域
        if (part == CV_GLASSPART::HEAD) {
            if (!m_glassRegion.empty())
                m_glassRegion.release();
            if (currentFrameCount > 1){
                /* 删除掉重复的行数 */
                CameraCropArg arg0 = PARAM.crops.args[0];
                int hasDeletePix = 200 - arg0.topPixCrop - arg0.bottomPixCrop;//重复的200行需要减去的行数
                cv::Rect rect(hasDeletePix,0,image.cols - hasDeletePix, image.rows);//image已经被转置90度
                image = image(rect);//裁剪若干列重复行数
            }
            m_glassRegion = image;
        } else {
            /* 删除掉重复的行数 */
            CameraCropArg arg0 = PARAM.crops.args[0];
            int hasDeletePix = 200 - arg0.topPixCrop - arg0.bottomPixCrop;//重复的200行需要减去的行数
            cv::Rect rect(hasDeletePix,0,image.cols - hasDeletePix, image.rows);//image已经被转置90度
            image = image(rect);//裁剪若干列重复行数
            if (image.rows != m_glassRegion.rows && m_glassRegion.rows != 0 ) {
                /* 每帧图像的行数因为仿射有变化，现在缩放统一大小 */
                double scaleFactor = (double)m_glassRegion.rows / (double)image.rows;// 计算缩放因子
                double newWidth1 = static_cast<int>((double)image.cols * scaleFactor);// 计算缩放后的宽
                qDebug()<<"(double)image.cols = "<<(double)image.cols <<", scaleFactor ="<<scaleFactor<<", m_glassRegion.rows ="<<m_glassRegion.rows;
                auto start = std::chrono::high_resolution_clock::now();// 开始时间
                cv::resize(image, image, cv::Size(newWidth1, m_glassRegion.rows));
                auto end = std::chrono::high_resolution_clock::now();
                std::chrono::duration<double, std::milli> duration0 = end - start;
                qDebug() << "++++++++++++ cv::resize time：" << duration0.count() << " ms";
            }
            if (m_glassRegion.rows == 0 || m_glassRegion.cols == 0) {//算法误判头部
                qDebug()<<"算法误判头部:m_glassRegion.rows ="<<m_glassRegion.rows<<", m_glassRegion.cols ="<<m_glassRegion.cols;
                m_glassRegion = image;
            } else  {
                auto start = std::chrono::high_resolution_clock::now();// 开始时间
                cv::hconcat(m_glassRegion,image,m_glassRegion);
                auto end = std::chrono::high_resolution_clock::now();
                std::chrono::duration<double, std::milli> duration0 = end - start;
                qDebug() << "++++++++++++ cv::hconcat time：" << duration0.count() << " ms";
            }
        }
    } catch(...) {
        qDebug() << "MainWindow::imageDisplay => An unknown error occurred.";
        // 获取当前的异常信息
        std::exception_ptr eptr = std::current_exception();
        if (eptr) {
            try {
                std::rethrow_exception(eptr);
            } catch (const std::exception& ex) {
                qDebug() << "Exception: " << ex.what();
            }
        }
    }
    // QString path = "D:/testopencv/image"+ QString::number(part) + ".jpg";
    // cv::imwrite(path.toStdString(),m_glassRegion);

    bool success = QMetaObject::invokeMethod(this,
                                             "slot_DisplayMain",
                                             Qt::QueuedConnection,
                                             Q_ARG(CV_GLASSPART, part),
                                             Q_ARG(cv::Mat, m_glassRegion));
    if (success) {
        qDebug() << "MainWindow::imageDisplay Method invocation slot_DisplayMain successful.";

    } else {
        qDebug() << "MainWindow::imageDisplay Method invocation slot_DisplayMain failed.";
    }
}

void MainWindow::UpdateStatisticsTable(NewGlassResult& result)
{
    GlassDataBaseInfo baseinfo;
    baseinfo.id = glassPrimaryKey;                                                          // 玻璃的id，唯一的主键
    baseinfo.time = QDateTime::currentDateTime().toString().toStdString().data();           // 时间
    baseinfo.OKorNG = m_currentSatus;         // 整体情况OK或者NG
    baseinfo.sizeOKorNG = m_sizeOKorNG;     //尺寸OK或者NG
    m_glassLength = m_glassLength + result.pixGlassLength;
    baseinfo.length = m_glassLength;          // 玻璃的长度
    baseinfo.width = result.pixGlassWidth;           // 玻璃的宽度
    baseinfo.duijiaoxian1 = std::sqrt(m_glassLength*m_glassLength + result.pixGlassWidth* result.pixGlassWidth);    // 玻璃的对角线1
    baseinfo.duijiaoxian2 = std::sqrt(m_glassLength*m_glassLength + result.pixGlassWidth* result.pixGlassWidth);    // 玻璃的对角线2
    baseinfo.defectNumber = m_defectNumber;       // 玻璃的缺陷数量
    baseinfo.defectOKorNG = m_defectNumber==0?"OK":"NG";   // 缺陷OK或者NG
    baseinfo.huashanNumber = m_huashanNumber;      // 划伤数量
    baseinfo.qipaoNumber = m_qipaoNumber;        // 气泡数量
    baseinfo.jieshiNumber = m_jieshiNumber;       // 结石数量
    baseinfo.benbianNumber = m_benbianNumber;      // 崩边数量
    baseinfo.zanwuNumber = m_zanwuNumber;        // 脏污数量
    baseinfo.liewenNumber = m_liewenNumber;       // 裂纹数量
    baseinfo.qitaNumber = m_qitaNumber;         // 其它数量
    bool success = QMetaObject::invokeMethod(this,
                                             "slot_GlassStaticTableInsertRowData",
                                             Qt::AutoConnection,
                                             Q_ARG(GlassDataBaseInfo, baseinfo));
    if (success) {
        qDebug() << "Method invocation slot_GlassStaticTableInsertRowData successful.";
        QString mes2 = "玻璃 帧["+QString::number(result.currentFrameCount) + "] 玻璃统计数据更新成功。";
        INFOMATION.outputMessage(ui->loglistWidget,mes2);
    } else {
        qDebug() << "Method invocation slot_GlassStaticTableInsertRowData failed.";
    }
}

void MainWindow::realUpdateDatabase(NewGlassResult result,std::vector<GlassDefect2>& glassDefectDatas)
{
    m_defectNumber = m_defectNumber + result.res.size();//缺陷总数量
    for (int i =0; i < (int)result.res.size(); ++i) {
        GlassDefect2 tmp;
        tmp.id = ++defectPrimaryKey;                                    // 主键id,在所有缺陷中的顺序
        tmp.defectId = m_defectNumber + i - result.res.size();          // 缺陷id，在一块玻璃中缺陷的顺序
        tmp.time = result.res[i].time;                                  // 缺陷检测时间
        tmp.defectType = classes[result.res[i].type];                   // 缺陷类型
        if (tmp.defectType == tr("JieShi_Min")) {
            ++m_jieshiNumber;
        } else if(tmp.defectType == tr("MaoXu_Min")) {
            ++m_zanwuNumber;
        } else if (tmp.defectType == tr("QiPao_Min")) {
            ++m_qipaoNumber;
        } else if (tmp.defectType == tr("ShuiDi_Min")) {
            ++m_qitaNumber;
        } else if (tmp.defectType == tr("BoLiXue_Min")) {
            ++m_qitaNumber;
        } else if (tmp.defectType == tr("HeiDian_Min")) {
            ++m_qitaNumber;
        } else if (tmp.defectType == tr("HuaShang_Min")) {
            ++m_huashanNumber;
        }
        tmp.defectLevel = "NG";                          // 缺陷等级，OK NG
        m_currentSatus = "NG";

        tmp.x = result.res[i].pixX * PARAM.XCamera0Accuracy;                   // 缺陷在玻璃上的X坐标
        tmp.y = result.res[i].pixY * PARAM.YAccuracy;                          // 缺陷在玻璃上的Y坐标
        tmp.length = result.res[i].pixLength * PARAM.YAccuracy;                // 缺陷的长度
        tmp.width = result.res[i].pixWidth * PARAM.XCamera0Accuracy;           // 缺陷的宽度
        tmp.area = result.res[i].pixArea * PARAM.XCamera0Accuracy;             // 缺陷面积大小
        tmp.glassid = glassPrimaryKey;                                         // 外键id,玻璃的id
        tmp.imagePath = result.res[i].imagePath;                               // 缺陷图片的路径
        VecDefect.push(tmp);
        glassDefectDatas.push_back(tmp);
    }
    QString mes1 = "帧["+QString::number(result.currentFrameCount) + "] 玻璃缺陷存入数据库成功。";
    INFOMATION.outputMessage(ui->loglistWidget,mes1);
}

void MainWindow::realUpdateDefectTable(CV_GLASSPART part, std::vector<GlassDefect2>& glassDefectDatas)
{
    if (glassDefectDatas.size() <= 0)
        return;

    bool success = QMetaObject::invokeMethod(this,
                                             "slot_UpdateDefectTable",
                                             Qt::AutoConnection,
                                             Q_ARG(CV_GLASSPART, part),
                                             Q_ARG(std::vector<GlassDefect2>, glassDefectDatas));
    if (success) {
        qDebug() << "Method invocation successful.";
        QString mes3 = "玻璃缺陷数据表格更新成功。";
        INFOMATION.outputMessage(ui->loglistWidget,mes3);
    } else {
        qDebug() << "Method invocation failed.";
    }
}

void MainWindow::realUpdateDefectDisplay(NewGlassResult& result)
{
    if ((int)result.res.size() <= 0) return;
    bool success = QMetaObject::invokeMethod(this,
                                             "slot_UpdateDefectDisplay",
                                             Qt::AutoConnection,
                                             Q_ARG(NewGlassResult, result));
    if (success) {
        qDebug() << "Method invocation successful.";
        QString mes4 = "玻璃实时缺陷小图更新成功。";
        INFOMATION.outputMessage(ui->loglistWidget,mes4);
    } else {
        qDebug() << "Method invocation failed.";
    }
}

void MainWindow::updateSizeInfoTable(std::vector<DoorClampAndHole>& sizeRes)
{
    GlassSizeInfo info;
    for (int i = 0; i < (int)sizeRes.size(); ++i ) {
        GlassSize size;
        size.id = ++sizePrimaryKey;
        size.sizeID = m_sizeid++;
        size.time = QDateTime::currentDateTime().toString();
        if (sizeRes[i].type == SizeType::DoorClam) {
            size.sizeType = tr("DoorClam");
        } else if (sizeRes[i].type == SizeType::Hole ) {
            size.sizeType = tr("Hole");
        }
        size.sizeLevel = "OK";
        size.lengthX = sizeRes[i].PixHeight * PARAM.YAccuracy;
        size.widthY = sizeRes[i].PixWidth * PARAM.XCamera0Accuracy;
        size.marginsX = sizeRes[i].MarginsX * PARAM.YAccuracy;
        size.marginsY = sizeRes[i].MarginsY * PARAM.XCamera0Accuracy;
        size.glassid = glassPrimaryKey;
        size.imagePath = sizeRes[i].Path;
        m_mutex.lock();
        m_sizedatas.push_back(size);
        m_mutex.unlock();

        GlassSizeInfo2 data;//数据库结构体
        data.id = size.id;
        data.sizeno = size.sizeID;
        data.time = size.time;
        data.sizeType = size.sizeType;
        data.sizeLevel = size.sizeLevel;
        data.lengthX = size.lengthX;
        data.widthY = size.widthY;
        data.marginsX = size.marginsX;
        data.marginsY = size.marginsY;
        data.glassid = size.glassid;
        data.imagePath = size.imagePath;
        m_mutex.lock();
        if (databasePtr!=nullptr) {
            databasePtr->insertOneData(data);
        }
        m_mutex.unlock();
    }
    m_mutex.lock();
    info.sizedatas = m_sizedatas;
    m_mutex.unlock();
    info.sizeCount = sizeRes.size();
    //info.OutLinePath = //todo：轮廓图
    bool success = QMetaObject::invokeMethod(this,
                                             "slot_SingleSizeUpdataTableData",
                                             Qt::AutoConnection,
                                             Q_ARG(GlassSizeInfo, info));
    if (success) {
        qDebug() << "MainWindow::updateSizeInfoTable Method invocation successful.";
        QString mes5 = "玻璃缺陷尺寸数据更新成功。";
        INFOMATION.outputMessage(ui->loglistWidget,mes5);
    } else {
        qDebug() << "MainWindow::updateSizeInfoTable Method invocation failed.";
    }
}

bool MainWindow::checkFrameParam(FrameImage& imageunit)
{
    if (imageunit.buffers.size() <= 0) {
        return false;
    }
    if (imageunit.fieldnumberset <= 0) {
        return false;
    }
    return true;
}

void MainWindow::clearGlassDisplay(CV_GLASSPART part)
{
    if (part == CV_GLASSPART::TAIL) {// 重新初始化一些变量
        m_currentSatus = "OK";
        m_glassLength = 0;
        m_sizeOKorNG = "OK";
        m_defectNumber = 0;
        m_jieshiNumber = 0;
        m_zanwuNumber = 0;
        m_qipaoNumber = 0;
        m_qitaNumber = 0;
        m_huashanNumber = 0;
        m_glassLength = 0;
        m_currentRow = 0;
        m_sizedatas.clear();
        m_sizeid = 0 ;
    }
}

void MainWindow::saveMatToImage(QString fullpath,cv::Mat region )
{
    std::string filename = fullpath.toStdString();
    cv::imwrite(filename, region);
}

QString MainWindow::SyncSaveCurrentTimeImage(cv::Mat& region,QString path/*=""*/)
{
    try{
        if (path == "") {
            int randomNumber = std::rand() % 123567;
            QString time = QDateTime::currentDateTime().toString("hh-mm-ss");
            path = "D:/testopencv/camera/"+time +"-"+ QString::number(randomNumber)+".jpg";
        }
        std::thread th1(&MainWindow::saveMatToImage,this,path,region);
        th1.detach();
        return path;
    } catch(...) {
        qDebug() << " ProcessTile::SyncSaveCurrentTimeImage =>An unknown error occurred.";
        // 获取当前的异常信息
        std::exception_ptr eptr = std::current_exception();
        if (eptr) {
            try {
                std::rethrow_exception(eptr);
            } catch (const std::exception& ex) {
                qDebug() << "Exception: " << ex.what();
            }
        }
        return "";
    }
}

void MainWindow::SyncInsertDatabase()
{
DATABASE:
    if ( VecDefect.empty() ){
        std::this_thread::sleep_for(std::chrono::seconds(1));
        if (PARAM.currentsystem == SYSTEMSTATUS::STOP) return;
        goto DATABASE;
    } else {
        if (PARAM.currentsystem == SYSTEMSTATUS::STOP) return;
        GlassDefect2 tmp = VecDefect.pop();
        if (tmp.id != 0) {
            if (databasePtr != nullptr) {
                databasePtr->insertOneData(tmp);
            }
        }
        goto DATABASE;
    }
}

/////////////////////////////////public slot///////////////////////////////////////////////////////////////

void MainWindow::slot_CloseSystem()
{
    if (databasePtr != nullptr) {
        databasePtr->closeDataBase();
        FreeLibrary(databaseDllHandle);
    }
    if (algorithmPtr!= nullptr) {
        FreeLibrary(algorithmDllHandle);
    }
    if (cameraPtr0!=nullptr&&cameraPtr1) {
        FreeLibrary(cameraDllHandle);
    }
    close();
    qApp->exit(0);
}

void MainWindow::slot_ShowSystemSettingForm()
{
    if(m_lightControl == nullptr) {
        m_lightControl = std::make_shared<LightControl>(this);//设置窗口
    }
    m_lightControl->setHidden(false);
    m_lightControl->setWindowFlags(Qt::Window);
    m_lightControl->setWindowModality(Qt::ApplicationModal); //点击之后不可对其它窗体操作
    m_lightControl->setWindowFlags(m_lightControl->windowFlags() & ~Qt::WindowMinMaxButtonsHint);//设置窗口无最小化按钮
    m_lightControl->setWindowFlags(m_lightControl->windowFlags() & ~Qt::WindowMaximizeButtonHint);//设置窗口无全屏按钮
    m_lightControl->setWindowIcon(QIcon(":/toolbar/icons/setup.ico"));
    m_lightControl->setWindowTitle("系统设置");
    m_lightControl->show();
}

void MainWindow::slot_ActionStart()
{
    qDebug()<<"slot_ActionStart";
    //
    // 进行开始流程，打开相机
    // 设置界面上相关按钮的亮和灰
    //
    m_pStart->setEnabled(false);
    m_pExit->setEnabled(false);
    m_pStop->setEnabled(true);
    m_pSettings->setEnabled(false);
    m_offline->setEnabled(false);

    if (cameraPtr0!=nullptr && cameraPtr1 != nullptr) {
        if (!cameraPtr0->IsStarted(m_args[0].camName)){
            QString message = m_args[0].camName + tr("camera is not started.");
            INFOMATION.criticalMessageBox(this,message);
        }
        if (!cameraPtr1->IsStarted(m_args[1].camName)){
            QString message = m_args[1].camName + tr("camera is not started.");
            INFOMATION.criticalMessageBox(this,message);
        }
    }
    PARAM.currentsystem = SYSTEMSTATUS::RUNNING;
    //
    // 根据信号平台帧信号获取图片
    //
    m_startThread = std::make_shared<std::thread>(&MainWindow::ProcessThreadCV, this);
}

void MainWindow::slot_ActionStop()
{
    PARAM.currentsystem = SYSTEMSTATUS::STOP;
    m_pStart->setEnabled(true);
    m_pExit->setEnabled(true);
    m_pStop->setEnabled(false);
    m_pSettings->setEnabled(true);
    m_offline->setEnabled(true);

    if (m_databaseThread != nullptr) {
        if(m_databaseThread->joinable()) {
            m_databaseThread->join();
        }
    }
    if (m_startThread != nullptr) {
        if(m_startThread->joinable()) {
            m_startThread->join();
        }
    }
}

void MainWindow::slot_DataSearch()
{
    //
    // 进行数据查询
    //
    if (dataanalysisPtr == nullptr) {
        dataanalysisPtr = std::make_shared<DataAnalysis>(this);
    }
    dataanalysisPtr->setWindowFlags(Qt::Window);
    dataanalysisPtr->setWindowModality(Qt::ApplicationModal); //点击之后不可对其它窗体操作
    dataanalysisPtr->setWindowFlags(dataanalysisPtr->windowFlags() & ~Qt::WindowMinMaxButtonsHint);//设置窗口无最小化按钮
    dataanalysisPtr->setWindowFlags(dataanalysisPtr->windowFlags() & ~Qt::WindowMaximizeButtonHint);//设置窗口无全屏按钮
    dataanalysisPtr->setWindowTitle("数据查询");
    dataanalysisPtr->show();
}

void MainWindow::slot_Offline()
{
    try {
        //获取选择的目录路径
        QStringList offlineSelectedFiles =  QFileDialog::getOpenFileNames( this, "选择文件或目录", "D:/", "All Files (*);;Directories (*/)", nullptr, QFileDialog::ReadOnly);
        //若目录路径不为空
        if (!offlineSelectedFiles.isEmpty()) {
            auto start = std::chrono::high_resolution_clock::now();// 开始时间
            if (algorithmPtr != nullptr) {
                algorithmPtr->RegisterResultCallback(std::bind(&MainWindow::MainWindowsDisplay, this, std::placeholders::_1));
                //遍历容器
                for(int i = 0; i < (int)offlineSelectedFiles.size(); ++i) {
                    qDebug() << offlineSelectedFiles[i];//输出文件的完整路径名
                    cv::Mat projectionImage,reflectionLightImage,reflectionDarkImage;
                    projectionImage = cv::imread(offlineSelectedFiles[i].toStdString());
                    algorithmPtr->SyncExecu(i, projectionImage,reflectionLightImage,reflectionDarkImage);
                }
            } else {
                qDebug()<<"algorithmPtr == nullptr";
            }
            auto endf1 = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double, std::milli> durationf1 = endf1 - start;
            qDebug() << "Finished 2 time：" << durationf1.count() << " ms";
        } else {
            return;
        }
    } catch(...) {
        qDebug()<<"slot_ButtonExportClicked() error";
    }
}

void MainWindow::slot_Calibrate()
{
    if (calibratePtr == nullptr) {
        calibratePtr = std::make_shared<Calibrate>(nullptr);
    }
    calibratePtr->setWindowFlags(Qt::Window);
    calibratePtr->setWindowModality(Qt::ApplicationModal); //点击之后不可对其它窗体操作
    calibratePtr->setWindowFlags(calibratePtr->windowFlags() & ~Qt::WindowMinMaxButtonsHint);//设置窗口无最小化按钮
    calibratePtr->setWindowFlags(calibratePtr->windowFlags() & ~Qt::WindowMaximizeButtonHint);//设置窗口无全屏按钮
    calibratePtr->setWindowTitle("图片标定");
    calibratePtr->show();
}

void MainWindow::slot_GlassStaticTableInsertRowData(GlassDataBaseInfo info)
{
    QTableWidgetItem *itemID = ui->glassstatictablewidget->item(0, 0);
    //
    // 同一块玻璃的多帧图片插入到表格的同一行
    //
    if (itemID != NULL) {
        if(itemID->text().toInt() != info.id)
            ui->glassstatictablewidget->insertRow(0);
    } else {
        ui->glassstatictablewidget->insertRow(0);
    }
    //ID
    QTableWidgetItem* id = new QTableWidgetItem(QString::number(info.id));
    id->setTextAlignment(Qt::AlignCenter);
    id->setFlags(id->flags() & ~Qt::ItemIsEditable);
    ui->glassstatictablewidget->setItem(0, 0, id);
    //时间
    QTableWidgetItem* time = new QTableWidgetItem(info.time);
    time->setTextAlignment(Qt::AlignCenter);
    time->setFlags(time->flags() & ~Qt::ItemIsEditable);
    ui->glassstatictablewidget->setItem(0, 1, time);
    //OK/NG
    QTableWidgetItem* isok = new QTableWidgetItem(info.OKorNG);
    isok->setTextAlignment(Qt::AlignCenter);
    isok->setFlags(isok->flags() & ~Qt::ItemIsEditable);
    ui->glassstatictablewidget->setItem(0, 2, isok);
    //尺寸OK/NG
    QTableWidgetItem* issizeok = new QTableWidgetItem(info.sizeOKorNG);
    issizeok->setTextAlignment(Qt::AlignCenter);
    issizeok->setFlags(issizeok->flags() & ~Qt::ItemIsEditable);
    ui->glassstatictablewidget->setItem(0, 3, issizeok);
    //长度
    QTableWidgetItem* length = new QTableWidgetItem(QString::number(info.length,'f', 2));
    length->setTextAlignment(Qt::AlignCenter);
    length->setFlags(length->flags() & ~Qt::ItemIsEditable);
    ui->glassstatictablewidget->setItem(0, 4, length);
    //宽度
    QTableWidgetItem* width = new QTableWidgetItem(QString::number(info.width,'f', 2));
    width->setTextAlignment(Qt::AlignCenter);
    width->setFlags(width->flags() & ~Qt::ItemIsEditable);
    ui->glassstatictablewidget->setItem(0, 5, width);
    //对角线1
    QTableWidgetItem* diagonal1 = new QTableWidgetItem(QString::number(info.duijiaoxian1,'f', 2));
    diagonal1->setTextAlignment(Qt::AlignCenter);
    diagonal1->setFlags(diagonal1->flags() & ~Qt::ItemIsEditable);
    ui->glassstatictablewidget->setItem(0, 6, diagonal1);
    //对角线2
    QTableWidgetItem* diagonal2 = new QTableWidgetItem(QString::number(info.duijiaoxian2,'f', 2));
    diagonal2->setTextAlignment(Qt::AlignCenter);
    diagonal2->setFlags(diagonal2->flags() & ~Qt::ItemIsEditable);
    ui->glassstatictablewidget->setItem(0, 7, diagonal2);
    //缺陷数量
    QTableWidgetItem* flawcount = new QTableWidgetItem(QString::number(info.defectNumber));
    flawcount->setTextAlignment(Qt::AlignCenter);
    flawcount->setFlags(flawcount->flags() & ~Qt::ItemIsEditable);
    ui->glassstatictablewidget->setItem(0, 8, flawcount);
    //缺陷OK/NG
    QTableWidgetItem* isflawok = new QTableWidgetItem(info.defectOKorNG);
    isflawok->setTextAlignment(Qt::AlignCenter);
    isflawok->setFlags(isflawok->flags() & ~Qt::ItemIsEditable);
    ui->glassstatictablewidget->setItem(0, 9, isflawok);
    //划伤
    QTableWidgetItem* flaw1 = new QTableWidgetItem(QString::number(info.huashanNumber));
    flaw1->setTextAlignment(Qt::AlignCenter);
    flaw1->setFlags(flaw1->flags() & ~Qt::ItemIsEditable);
    ui->glassstatictablewidget->setItem(0, 10, flaw1);
    //气泡
    QTableWidgetItem* flaw2 = new QTableWidgetItem(QString::number(info.qipaoNumber));
    flaw2->setTextAlignment(Qt::AlignCenter);
    flaw2->setFlags(flaw2->flags() & ~Qt::ItemIsEditable);
    ui->glassstatictablewidget->setItem(0, 11, flaw2);
    //结石
    QTableWidgetItem* flaw7 = new QTableWidgetItem(QString::number(info.jieshiNumber));
    flaw7->setTextAlignment(Qt::AlignCenter);
    flaw7->setFlags(flaw7->flags() & ~Qt::ItemIsEditable);
    ui->glassstatictablewidget->setItem(0, 12, flaw7);
    //崩边
    QTableWidgetItem* flaw3 = new QTableWidgetItem(QString::number(info.benbianNumber));
    flaw3->setTextAlignment(Qt::AlignCenter);
    flaw3->setFlags(flaw3->flags() & ~Qt::ItemIsEditable);
    ui->glassstatictablewidget->setItem(0, 13, flaw3);
    //脏污
    QTableWidgetItem* flaw4 = new QTableWidgetItem(QString::number(info.zanwuNumber));
    flaw4->setTextAlignment(Qt::AlignCenter);
    flaw4->setFlags(flaw4->flags() & ~Qt::ItemIsEditable);
    ui->glassstatictablewidget->setItem(0, 14, flaw4);
    //裂纹
    QTableWidgetItem* flaw5 = new QTableWidgetItem(QString::number(info.liewenNumber));
    flaw5->setTextAlignment(Qt::AlignCenter);
    flaw5->setFlags(flaw5->flags() & ~Qt::ItemIsEditable);
    ui->glassstatictablewidget->setItem(0, 15, flaw5);
    //其他
    QTableWidgetItem* flaw6 = new QTableWidgetItem(QString::number(info.qitaNumber));
    flaw6->setTextAlignment(Qt::AlignCenter);
    flaw6->setFlags(flaw6->flags() & ~Qt::ItemIsEditable);
    ui->glassstatictablewidget->setItem(0, 16, flaw6);

    // 设置表格内容居中显示
    for (int i = 0; i < ui->glassstatictablewidget->columnCount(); ++i) {
        ui->glassstatictablewidget->horizontalHeaderItem(i)->setTextAlignment(Qt::AlignCenter);
    }
    ui->glassstatictablewidget->verticalHeader()->setVisible(false); // 隐藏行号
}

void MainWindow::slot_SingleFlawUpdateTableData(GlassDefectInfo info)
{
    if(info.defectdatas.size() > 0 && (int)info.defectdatas.size() == info.defectCount) {
        ui->SingleFlawtableWidget->setRowCount(info.defectdatas.size());
        ui->SingleFlawtableWidget->setColumnCount(9);
        for (int i = 0; i < info.defectCount; i++) {
            //序号
            QString DefectID = QString::number(info.defectdatas[i].defectId);
            QTableWidgetItem* item0 = new QTableWidgetItem(DefectID);
            item0->setTextAlignment(Qt::AlignCenter);
            ui->SingleFlawtableWidget->setItem(i, 0, item0);
            //时间
            QString Time = info.defectdatas[i].time;
            QTableWidgetItem* item1 = new QTableWidgetItem(Time);
            item1->setTextAlignment(Qt::AlignCenter);
            ui->SingleFlawtableWidget->setItem(i, 1, item1);
            //类型
            QString DefectType = info.defectdatas[i].defectType;
            QTableWidgetItem* item2 = new QTableWidgetItem(DefectType);
            item2->setTextAlignment(Qt::AlignCenter);
            ui->SingleFlawtableWidget->setItem(i , 2, item2);
            //等级
            QString DetectLeve = info.defectdatas[i].defectLevel;
            QTableWidgetItem* item3 = new QTableWidgetItem(DetectLeve);
            item3->setTextAlignment(Qt::AlignCenter);
            ui->SingleFlawtableWidget->setItem(i, 3, item3);
            //坐标X
            QString X = QString::number(info.defectdatas[i].x,'f', 2);
            QTableWidgetItem* item4 = new QTableWidgetItem(X);
            item4->setTextAlignment(Qt::AlignCenter);
            ui->SingleFlawtableWidget->setItem(i, 4, item4);
            //坐标Y
            QString Y = QString::number(info.defectdatas[i].y,'f', 2);
            QTableWidgetItem* item5 = new QTableWidgetItem(Y);
            item5->setTextAlignment(Qt::AlignCenter);
            ui->SingleFlawtableWidget->setItem(i, 5, item5);
            //长
            QString Lenth = QString::number(info.defectdatas[i].length,'f', 2);
            QTableWidgetItem* item6 = new QTableWidgetItem(Lenth);
            item6->setTextAlignment(Qt::AlignCenter);
            ui->SingleFlawtableWidget->setItem(i, 6, item6);
            //宽
            QString Width = QString::number(info.defectdatas[i].width,'f', 2);
            QTableWidgetItem* item7 = new QTableWidgetItem(Width);
            item7->setTextAlignment(Qt::AlignCenter);
            ui->SingleFlawtableWidget->setItem(i, 7, item7);
            //区域
            QString Area = QString::number(info.defectdatas[i].area,'f', 2);
            QTableWidgetItem* item8 = new QTableWidgetItem(Area);
            item8->setTextAlignment(Qt::AlignCenter);
            ui->SingleFlawtableWidget->setItem(i, 8, item8);
            //插入坐标到map中，用于追踪缺陷
            PARAM.rowMapXY[info.defectdatas[i].defectId] = std::make_pair(X,Y);
        }
        //
        // 更新缺陷小图
        //
        QImage img1(info.defectdatas[0].imagePath1);
        QImage img2(info.defectdatas[0].imagePath2);
        QImage img3(info.defectdatas[0].imagePath3);

        loadedPixmapItem->loadImage(img1);
        int nwidth = ui->graphicsView->width();
        int nheight = ui->graphicsView->height();
        loadedPixmapItem->setQGraphicsViewWH(nwidth, nheight);
        ui->graphicsView->setSceneRect((QRectF(-(nwidth / 2), -(nheight / 2), nwidth, nheight)));

        loadedPixmapItem2->loadImage(img2);
        int nwidth2 = ui->graphicsView_2->width();
        int nheight2 = ui->graphicsView_2->height();
        loadedPixmapItem2->setQGraphicsViewWH(nwidth, nheight);
        ui->graphicsView_2->setSceneRect((QRectF(-(nwidth2 / 2), -(nheight2 / 2), nwidth2, nheight2)));

        loadedPixmapItem3->loadImage(img3);
        int nwidth3 = ui->graphicsView_3->width();
        int nheight3 = ui->graphicsView_3->height();
        loadedPixmapItem3->setQGraphicsViewWH(nwidth, nheight);
        ui->graphicsView_3->setSceneRect((QRectF(-(nwidth3 / 2), -(nheight3 / 2), nwidth3, nheight3)));
    }
}

void MainWindow::slot_SingleSizeUpdataTableData(GlassSizeInfo info)
{
    if(info.sizedatas.size() > 0 && (int)info.sizedatas.size() == info.sizeCount) {
        ui->singleSizeTableWidget->setRowCount(info.sizeCount);
        for (int i = 0; i < info.sizeCount; i++) {
            // 序号
            QString HolesID = QString::number(info.sizedatas[i].sizeID);
            QTableWidgetItem* item0 = new QTableWidgetItem(HolesID);
            item0->setTextAlignment(Qt::AlignCenter);
            ui->singleSizeTableWidget->setItem(i, 0, item0);
            // 时间
            QString Time = info.sizedatas[i].time;
            QTableWidgetItem* item1 = new QTableWidgetItem(Time);
            item1->setTextAlignment(Qt::AlignCenter);
            ui->singleSizeTableWidget->setItem(i, 1, item1);
            // 类型
            QString Type = info.sizedatas[i].sizeType;
            QTableWidgetItem* item2 = new QTableWidgetItem(Type);
            item2->setTextAlignment(Qt::AlignCenter);
            ui->singleSizeTableWidget->setItem(i, 2, item2);
            //孔洞
            QString HolesLeve = info.sizedatas[i].sizeLevel;
            QTableWidgetItem* item3 = new QTableWidgetItem(HolesLeve);
            item3->setTextAlignment(Qt::AlignCenter);
            ui->singleSizeTableWidget->setItem(i, 3, item3);
            // 长X
            QString HolesHeight = QString::number(info.sizedatas[i].lengthX,'f', 2);
            QTableWidgetItem* item4 = new QTableWidgetItem(HolesHeight);
            item4->setTextAlignment(Qt::AlignCenter);
            ui->singleSizeTableWidget->setItem(i, 4, item4);
            // 宽Y
            QString HolesWidth = QString::number(info.sizedatas[i].widthY,'f', 2);
            QTableWidgetItem* item5 = new QTableWidgetItem(HolesWidth);
            item5->setTextAlignment(Qt::AlignCenter);
            ui->singleSizeTableWidget->setItem(i, 5, item5);
            // 边距X
            QString DistanceHorizontal = QString::number(info.sizedatas[i].marginsX,'f', 2);
            QTableWidgetItem* item6 = new QTableWidgetItem(DistanceHorizontal);
            item6->setTextAlignment(Qt::AlignCenter);
            ui->singleSizeTableWidget->setItem(i, 6, item6);
            // 边距Y
            QString DistanceVertical = QString::number(info.sizedatas[i].marginsY,'f', 2);
            QTableWidgetItem* item7 = new QTableWidgetItem(DistanceVertical);
            item7->setTextAlignment(Qt::AlignCenter);
            ui->singleSizeTableWidget->setItem(i, 7, item7);
        }
        //显示孔洞小图
        if (nullptr != ui->singleSizeTableWidget->item(0, 0)) {
            QString ImageHolesPath = info.sizedatas[0].imagePath;
            qDebug() << "ImageHolesPath = " << ImageHolesPath;
            QImage img2(ImageHolesPath);
            loadedPixmapItem5->loadImage(img2);
            int nwidth = ui->graphicsView_2->width();
            int nheight = ui->graphicsView_2->height();
            loadedPixmapItem5->setQGraphicsViewWH(nwidth, nheight);
            ui->graphicsView_Field->setSceneRect((QRectF(-(nwidth / 2), -(nheight / 2), nwidth, nheight)));
        }
        //显示轮廓图
        if(loadedPixmapItem4 != nullptr){
            QString ImageHolesLinePath = info.OutLinePath;
            qDebug() << "ImageHolesLinePath = " << ImageHolesLinePath;
            QImage img1(ImageHolesLinePath);
            loadedPixmapItem4->loadImage(img1);
            int nwidth = ui->graphicsView->width();
            int nheight = ui->graphicsView->height();
            loadedPixmapItem4->setQGraphicsViewWH(nwidth, nheight);
            ui->graphicsView->setSceneRect((QRectF(-(nwidth / 2), -(nheight / 2), nwidth, nheight)));
        }
    }
}

void MainWindow::slot_RefreshSystemTime()
{
    QDate currentDate = QDate::currentDate();
    QLocale locale1(QLocale::Chinese);
    QString weekday = locale1.dayName(currentDate.dayOfWeek(), QLocale::LongFormat);
    ui->weekLB->setText(weekday);
    ui->weekLB->setAlignment(Qt::AlignCenter);
    ui->weekLB->setStyleSheet("font-size: 30px;color: black;font-weight: bold;");

    QLocale locale(QLocale::Chinese);
    QString chineseDate = locale.toString(currentDate, "yyyy'年'MM'月'dd'日'");
    ui->YearMonthDayLB->setText(chineseDate);
    ui->YearMonthDayLB->setAlignment(Qt::AlignCenter);
    ui->YearMonthDayLB->setStyleSheet("font-size: 30px;color: black;font-weight: bold;"); // 设置字体大小为 20 像素

    QDateTime currentDateTime = QDateTime::currentDateTime();
    QTime currentTime = currentDateTime.time();
    QString chineseTime = currentTime.toString("hh:mm:ss");
    ui->timeLB->setText(chineseTime);
    ui->timeLB->setAlignment(Qt::AlignCenter);
    ui->timeLB->setStyleSheet("font-size: 40px;color: black;font-weight: bold;"); // 设置字体大小为 20 像素
}

void MainWindow::slot_GetCameraBuffer()
{
    FrameImage imageunit0;
    FrameImage imageunit1;
    // 获取每帧图片
    if (cameraPtr0!=nullptr && cameraPtr1!=nullptr) {
CAMERA0:
        cameraPtr0->startGetFrameBuffer(imageunit0);
        if (imageunit0.buffers.empty()) {
            if (PARAM.currentsystem == SYSTEMSTATUS::STOP) return;
            goto CAMERA0;
        }
CAMERA1:
        cameraPtr1->startGetFrameBuffer(imageunit1);
        if (imageunit1.buffers.empty()) {
            if (PARAM.currentsystem == SYSTEMSTATUS::STOP) return;
            goto CAMERA1;
        }

    } else {
        qDebug()<<"cameraPtr0 == nullptr And cameraPtr1 == nullptr";
        return;
    }
    // 对imageunit进行参数检查
    if (!MainWindow::checkFrameParam(imageunit0) || !MainWindow::checkFrameParam(imageunit0)){
        qDebug()<<"参数不符合要求";
        return;
    }

    std::vector<cv::Mat> mat0;  // 相机0
    std::vector<cv::Mat> mat1;  // 相机1
    for (int i=0; i<imageunit0.fieldnumberset; ++i) {
        cv::Mat region0 = imageunit0.buffers[i];
        cv::Mat region1 = imageunit1.buffers[i];
        mat0.push_back(region0);
        mat1.push_back(region1);
    }

    if (algorithmPtr != nullptr){
        cv::Mat projectionImage,reflectionLightImage,reflectionDarkImage;
        // 多个相机拼图
        algorithmPtr->Puzzle(2,mat0,mat1,PARAM.crops.args,projectionImage,reflectionLightImage,reflectionDarkImage);
        if (projectionImage.rows != 0 && reflectionLightImage.rows != 0 && reflectionDarkImage.rows != 0){
            QString ID = QString::number(imageunit0.framecount);
            MainWindow::SyncSaveCurrentTimeImage(projectionImage,"D:/testopencv/projectionImage"+ID+".jpg");
            MainWindow::SyncSaveCurrentTimeImage(reflectionLightImage,"D:/testopencv/reflectionLightImage"+ID+".jpg");
            MainWindow::SyncSaveCurrentTimeImage(reflectionDarkImage,"D:/testopencv/reflectionDarkImage"+ID+".jpg");
        } else {
            qDebug()<<"拼图出现错误";
        }

        algorithmPtr->RegisterResultCallback(std::bind(&MainWindow::MainWindowsDisplay, this, std::placeholders::_1));
        // 执行当前算法
        int currentcount = imageunit0.framecount; //获取当前帧数
        algorithmPtr->SyncExecu(currentcount, projectionImage,reflectionLightImage,reflectionDarkImage);
    } else {
        qDebug()<<"algorithmPtr == nullptr";
        return;
    }
}

void MainWindow::slot_DisplayMain(CV_GLASSPART part, cv::Mat image)
{
    try{
        qDebug()<<"image.rows = "<<image.rows <<", image.cols ="<<image.cols;
        QImage qImage = PARAM.cvMat2QImage(image);
        QGraphicsScene *scene = new QGraphicsScene();
        if (myloadedPixmapItem == nullptr) {
            myloadedPixmapItem = new MyGraphicsItem();
        }

        myloadedPixmapItem->loadImage(qImage);
        myloadedPixmapItem->setQGraphicsViewWH(1500,410);
        scene->addItem(myloadedPixmapItem);
        ui->display->setScene(scene);
        ui->display->update();
        QString mes = " 玻璃图像更新成功。";
        INFOMATION.outputMessage(ui->loglistWidget,mes);
    } catch (...) {
        qDebug() << "An unknown error occurred in imageDisplay.";
        // 获取当前的异常信息
        std::exception_ptr eptr = std::current_exception();
        if (eptr) {
            try {
                std::rethrow_exception(eptr);
            } catch (const std::exception& ex) {
                qDebug() << "Exception: " << ex.what();
            }
        }
    }
}

void MainWindow::slot_UpdateDefectTable(CV_GLASSPART part, std::vector<GlassDefect2> glassDefectDatas)
{
    if (part == CV_GLASSPART::HEAD) {//清除表格
        ui->SingleFlawtableWidget->clear();
    }

    ui->SingleFlawtableWidget->setRowCount(ui->SingleFlawtableWidget->rowCount() + glassDefectDatas.size());
    ui->SingleFlawtableWidget->setColumnCount(9);
    // 更新缺陷小图
    QImage img1(glassDefectDatas[0].imagePath);
    QImage img2(glassDefectDatas[0].imagePath);
    QImage img3(glassDefectDatas[0].imagePath);

    loadedPixmapItem->loadImage(img1);
    int nwidth = ui->graphicsView->width();
    int nheight = ui->graphicsView->height();
    loadedPixmapItem->setQGraphicsViewWH(nwidth, nheight);
    ui->graphicsView->setSceneRect((QRectF(-(nwidth / 2), -(nheight / 2), nwidth, nheight)));

    loadedPixmapItem2->loadImage(img2);
    int nwidth2 = ui->graphicsView_2->width();
    int nheight2 = ui->graphicsView_2->height();
    loadedPixmapItem2->setQGraphicsViewWH(nwidth, nheight);
    ui->graphicsView_2->setSceneRect((QRectF(-(nwidth2 / 2), -(nheight2 / 2), nwidth2, nheight2)));

    loadedPixmapItem3->loadImage(img3);
    int nwidth3 = ui->graphicsView_3->width();
    int nheight3 = ui->graphicsView_3->height();
    loadedPixmapItem3->setQGraphicsViewWH(nwidth, nheight);
    ui->graphicsView_3->setSceneRect((QRectF(-(nwidth3 / 2), -(nheight3 / 2), nwidth3, nheight3)));

    for (int i = m_currentRow ; i < (int)(m_currentRow + glassDefectDatas.size()); ++i) {
        GlassDefect2 data = glassDefectDatas[i - m_currentRow];
        //序号
        QTableWidgetItem* item0 = new QTableWidgetItem(QString::number(data.defectId));
        item0->setTextAlignment(Qt::AlignCenter);
        ui->SingleFlawtableWidget->setItem(i, 0, item0);
        //时间
        QTableWidgetItem* item1 = new QTableWidgetItem(data.time);
        item1->setTextAlignment(Qt::AlignCenter);
        ui->SingleFlawtableWidget->setItem(i, 1, item1);
        //类型
        QTableWidgetItem* item2 = new QTableWidgetItem(data.defectType);
        item2->setTextAlignment(Qt::AlignCenter);
        ui->SingleFlawtableWidget->setItem(i , 2, item2);
        //等级
        QTableWidgetItem* item3 = new QTableWidgetItem(data.defectLevel);
        item3->setTextAlignment(Qt::AlignCenter);
        ui->SingleFlawtableWidget->setItem(i, 3, item3);
        //坐标X
        QTableWidgetItem* item4 = new QTableWidgetItem(QString::number(data.x,'f', 2));
        item4->setTextAlignment(Qt::AlignCenter);
        ui->SingleFlawtableWidget->setItem(i, 4, item4);
        //坐标Y
        QTableWidgetItem* item5 = new QTableWidgetItem(QString::number(data.y,'f', 2));
        item5->setTextAlignment(Qt::AlignCenter);
        ui->SingleFlawtableWidget->setItem(i, 5, item5);
        //长
        QTableWidgetItem* item6 = new QTableWidgetItem(QString::number(data.length,'f', 2));
        item6->setTextAlignment(Qt::AlignCenter);
        ui->SingleFlawtableWidget->setItem(i, 6, item6);
        //宽
        QTableWidgetItem* item7 = new QTableWidgetItem(QString::number(data.width,'f', 2));
        item7->setTextAlignment(Qt::AlignCenter);
        ui->SingleFlawtableWidget->setItem(i, 7, item7);
        //区域
        QTableWidgetItem* item8 = new QTableWidgetItem(QString::number(data.area,'f', 2));
        item8->setTextAlignment(Qt::AlignCenter);
        ui->SingleFlawtableWidget->setItem(i, 8, item8);
    }
    m_currentRow = m_currentRow + glassDefectDatas.size();
}

void MainWindow::slot_UpdateDefectDisplay(NewGlassResult result)
{
    GlassDefect info;
    info.id = defectPrimaryKey;              //主键id,在所有缺陷中的顺序
    info.defectId = result.res[0].id;        // 缺陷id，在一块玻璃中缺陷的顺序
    info.time = result.res[0].time;           // 缺陷检测时间
    info.defectType = classes[result.res[0].type];     // 缺陷类型
    info.defectLevel = "NG";    // 缺陷等级，OK NG
    info.x = result.res[0].pixX *PARAM.XCamera0Accuracy;               // 缺陷在玻璃上的X坐标
    info.y = result.res[0].pixY * PARAM.YAccuracy;               // 缺陷在玻璃上的Y坐标
    info.length = result.res[0].pixLength * PARAM.YAccuracy;          // 缺陷的长度
    info.width = result.res[0].pixWidth * PARAM.XCamera0Accuracy;           // 缺陷的宽度
    info.area = result.res[0].pixArea * PARAM.XCamera0Accuracy;            // 缺陷面积大小
    info.glassid = glassPrimaryKey;         // 外键id,玻璃的id
    info.imagePath1 = result.res[0].imagePath;      // 光场1缺陷图片的路径
    info.imagePath2 = result.res[0].imagePath;      // 光场2缺陷图片的路径
    info.imagePath3 = result.res[0].imagePath;      // 光场3缺陷图片的路径
    // 更新缺陷小图
    QImage img1(info.imagePath1);
    QImage img2(info.imagePath2);
    QImage img3(info.imagePath3);

    loadedPixmapItem6->loadImage(img1);
    int nwidth = ui->graphicsView_Field1->width();
    int nheight = ui->graphicsView_Field1->height();
    loadedPixmapItem6->setQGraphicsViewWH(nwidth, nheight);
    ui->graphicsView_Field1->setSceneRect((QRectF(-(nwidth / 2), -(nheight / 2), nwidth, nheight)));
    ui->graphicsView_Field1->update();

    loadedPixmapItem2->loadImage(img2);
    int nwidth2 = ui->graphicsView_Field2->width();
    int nheight2 = ui->graphicsView_Field2->height();
    loadedPixmapItem2->setQGraphicsViewWH(nwidth, nheight);
    ui->graphicsView_Field2->setSceneRect((QRectF(-(nwidth2 / 2), -(nheight2 / 2), nwidth2, nheight2)));
    ui->graphicsView_Field2->update();

    loadedPixmapItem3->loadImage(img3);
    int nwidth3 = ui->graphicsView_Field3->width();
    int nheight3 = ui->graphicsView_Field3->height();
    loadedPixmapItem3->setQGraphicsViewWH(nwidth, nheight);
    ui->graphicsView_Field3->setSceneRect((QRectF(-(nwidth3 / 2), -(nheight3 / 2), nwidth3, nheight3)));
    ui->graphicsView_Field3->update();

    // 更新数据
    ui->defectID1LB->setText(QString::number(info.defectId));
    ui->defectID2LB->setText(QString::number(info.defectId));
    ui->defectID3LB->setText(QString::number(info.defectId));

    ui->defectTime1LB->setText(info.time);
    ui->defectTime2LB->setText(info.time);
    ui->defectTime3LB->setText(info.time);

    ui->defectType1LB->setText(info.defectType);
    ui->defectType2LB->setText(info.defectType);
    ui->defectType3LB->setText(info.defectType);

    ui->defectLevel1LB->setText(info.defectLevel);
    ui->defectLevel2LB->setText(info.defectLevel);
    ui->defectLevel3LB->setText(info.defectLevel);

    ui->defectX1LB->setText(QString::number(info.x));
    ui->defectX2LB->setText(QString::number(info.x));
    ui->defectX3LB->setText(QString::number(info.x));

    ui->defectY1LB->setText(QString::number(info.y));
    ui->defectY2LB->setText(QString::number(info.y));
    ui->defectY3LB->setText(QString::number(info.y));

    ui->defectLength1LB->setText(QString::number(info.length));
    ui->defectLength2LB->setText(QString::number(info.length));
    ui->defectLength3LB->setText(QString::number(info.length));

    ui->defectWidth1LB->setText(QString::number(info.width));
    ui->defectWidth2LB->setText(QString::number(info.width));
    ui->defectWidth3LB->setText(QString::number(info.width));

    ui->defectArea1LB->setText(QString::number(info.area));
    ui->defectArea2LB->setText(QString::number(info.area));
    ui->defectArea3LB->setText(QString::number(info.area));
}

/////////////////////////////////////protected/////////////////////////////////////////////////////////////

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    if (ui->qWidget != nullptr && ui->qWidget->underMouse()) {
        QPoint pos = event->pos();
        qDebug() << "Mouse clicked at position: (" << pos.x() << ", " << pos.y() << ")";
        QWidget::mousePressEvent(event);
    }
}

