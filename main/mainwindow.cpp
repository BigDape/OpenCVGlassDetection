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
#include <algorithm>



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
    classes =  std::vector<QString>{tr("划痕"),
                                    tr("异物"),
                                    tr("气泡"),
                                    tr("麻点"),
                                    tr("水印"),
                                    tr("油墨不良"),
                                    tr("锯齿边"),
                                   tr("丝印缺陷"),
                                   tr("刮花"),
                                   tr("裂纹"),
                                   tr("崩边角")};
    //
    // 设置窗口属性
    // Qt::FramelessWindowHint(无窗口边框)
    // Qt::WindowSystemMenuHint(为窗口添加一个窗口系统系统菜单，并尽可能地添加一个关闭按钮)
    // Qt::WindowMinMaxButtonsHint(为窗口添加一个“最小化”按钮 和一个“最大化”按钮)
    //
    setWindowFlags(Qt::FramelessWindowHint | Qt::WindowSystemMenuHint | Qt::WindowMinMaxButtonsHint);

    MainWindow::InitImageCacheDirectory();
    MainWindow::InitComponents();
    MainWindow::InitDatabaseParam();
    MainWindow::InitRegisterMetaType();
    MainWindow::InitToolBar();
    MainWindow::InitGlassStaticTableWidget();
    MainWindow::InitSingleFlawTableWidget();
    MainWindow::InitSingleSizeTableWidget();
    MainWindow::InitCameraSettingTableWidget();
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
        PARAM.databasePtr = databasePtr;    // 智能指针赋值全局变量
        PARAM.databasePtr->openDataBase();  // 打开数据库
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
        PARAM.algorithmPtr = algorithmPtr;
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
        PARAM.cameraPtr0 = cameraPtr0;
        PARAM.cameraPtr1 = cameraPtr1;
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
        PARAM.jsoncppPtr = jsoncppPtr;
    }
    //
    // 动态加载通讯组件
    //
    if (SocketObjectPtr == nullptr) {
        QString exePath = QCoreApplication::applicationDirPath();
        QString dllPath = exePath + "/../socket/socket.dll";
        socketDllHandle = LoadLibrary(dllPath.toStdWString().c_str());
        if (!socketDllHandle) {
            qFatal() << "Failed to load DLL. Error code: " << GetLastError();
        }
        // 获取创建数据库对象的函数指针
        createSocketObjectFunc1 createFunc = (createSocketObjectFunc1)GetProcAddress(socketDllHandle, "createSocketObject");
        if (!createFunc) {
            qFatal() << "Failed to get function pointer. Error code: " << GetLastError() ;
            FreeLibrary(socketDllHandle);
        } else {
            qDebug() << "Success to get  socketDllHandle function pointer. ";
        }
        SocketObjectPtr = createFunc();
        PARAM.SocketObjectPtr = SocketObjectPtr;
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
    qRegisterMetaType<std::vector<GlassDefect2>>("std::vector<GlassDefect2>");
    qRegisterMetaType<GlassDataBaseInfo2>("GlassDataBaseInfo2");
    qRegisterMetaType<cv::Mat>("cv::Mat");
    qRegisterMetaType<CV_GLASSPART>("CV_GLASSPART");
    qRegisterMetaType<std::vector<GlassSizeInfo2>>("std::vector<GlassSizeInfo2>");
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
                                tr("时间"),
                                tr("OK/NG"),
                                tr("尺寸OK/NG"),
                                tr("长度"),
                                tr("宽度"),
                                tr("缺陷OK/NG"),
                                tr("缺陷数量"),
                                tr("划痕"),
                                tr("异物"),
                                tr("气泡"),
                                tr("麻点"),
                                tr("水印"),
                                tr("油墨不良"),
                                tr("锯齿边"),
                                tr("丝印缺陷"),
                                tr("刮花"),
                                tr("裂纹"),
                                tr("崩边角")};
    ui->glassstatictablewidget->setColumnCount(headerLabels.size());    //19项
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
    ui->glassstatictablewidget->setColumnWidth(17, 100);
    ui->glassstatictablewidget->setColumnWidth(18, 100);

    //
    // 读取数据库信息，插入数据统计表格中
    //
    std::vector<GlassDataBaseInfo2> datas;
    if (PARAM.databasePtr != nullptr)
        PARAM.databasePtr->queryTableData(datas, "SELECT * FROM glass_table ORDER BY id DESC LIMIT 100;");
    for (auto& data : datas) {
        MainWindow::insertGlassStaticTable(data);
    }
    // 注册回调函数
    connect(this, SIGNAL(sign_GlassStaticTableInsertRowData(GlassDataBaseInfo2)), this, SLOT(slot_GlassStaticTableInsertRowData(GlassDataBaseInfo2)));
}

void MainWindow::InitSingleFlawTableWidget()
{
    //
    // 初始化单个缺陷界面
    //
    MainWindow::initLoadedImage(loadedPixmapItem, ui->graphicsView);
    MainWindow::initLoadedImage(loadedPixmapItem2, ui->graphicsView_2);
    MainWindow::initLoadedImage(loadedPixmapItem3, ui->graphicsView_3);

    ui->SingleFlawtableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->SingleFlawtableWidget->setColumnWidth(0, 90);
    ui->SingleFlawtableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->SingleFlawtableWidget->verticalHeader()->setVisible(false);

    //
    // 若数据统计界面不为空，则显示第一行玻璃的缺陷信息
    //
    QTableWidgetItem *itemID = ui->glassstatictablewidget->item(0, 0);
    if (itemID != NULL) {
        int glassid = itemID->text().toInt();
        QString sql = QString("SELECT * FROM glass_defect WHERE glassid = %1;").arg(glassid);
        std::vector<GlassDefect2> datas;
        if (PARAM.databasePtr != nullptr)
            PARAM.databasePtr->queryTableData(datas, sql);
        if (datas.size() > 0) {
            ui->SingleFlawtableWidget->setRowCount(datas.size());
            ui->SingleFlawtableWidget->setColumnCount(9);
            //
            // 更新缺陷小图
            //
            QImage img1(datas[0].imagePath0);
            QImage img2(datas[0].imagePath1);
            QImage img3(datas[0].imagePath2);

            MainWindow::loadedPixmapImage(img1,ui->graphicsView,loadedPixmapItem);
            MainWindow::loadedPixmapImage(img2,ui->graphicsView_2,loadedPixmapItem2);
            MainWindow::loadedPixmapImage(img3,ui->graphicsView_3,loadedPixmapItem3);

            // 插入缺陷
            for (auto& defect : datas) {
                MainWindow::insertDefectTable(defect);
            }
        }
    }
    // 双击更新小图
    connect(ui->SingleFlawtableWidget,SIGNAL(itemDoubleClicked(QTableWidgetItem*)), this, SLOT(slot_UpdateDefectImages(QTableWidgetItem*)));
    connect(this, SIGNAL(sign_UpdateDefectTable(CV_GLASSPART, std::vector<GlassDefect2>)), this, SLOT(slot_UpdateDefectTable(CV_GLASSPART, std::vector<GlassDefect2>)));

}

void MainWindow::InitSingleSizeTableWidget()
{
    //
    // 初始化尺寸信息界面
    //
    MainWindow::initLoadedImage(loadedPixmapItem50, ui->graphicsView_Field_1);
    MainWindow::initLoadedImage(loadedPixmapItem51, ui->graphicsView_Field_2);
    MainWindow::initLoadedImage(loadedPixmapItem52, ui->graphicsView_Field_3);

    ui->singleSizeTableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->singleSizeTableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->singleSizeTableWidget->verticalHeader()->setVisible(false);
    ui->singleSizeTableWidget->setColumnWidth(0, 90);

    //
    // 读取历史尺寸信息
    //
    QTableWidgetItem *itemID = ui->glassstatictablewidget->item(0, 0);
    if (itemID != NULL) {
        int glassid = itemID->text().toInt();
        QString sql = QString("SELECT * FROM glass_sizeinfo WHERE glassid = %1;").arg(glassid);
        std::vector<GlassSizeInfo2> datas;
        if (PARAM.databasePtr != nullptr)
            PARAM.databasePtr->queryTableData(datas, sql);
        MainWindow::batchInsertSizeTable(datas);
    }
    connect(ui->singleSizeTableWidget,SIGNAL(itemDoubleClicked(QTableWidgetItem*)), this, SLOT(slot_UpdateSizeImage(QTableWidgetItem*)));
    connect(this, SIGNAL(sign_SingleSizeUpdataTableData(std::vector<GlassSizeInfo2>)), this, SLOT(slot_SingleSizeUpdataTableData(std::vector<GlassSizeInfo2>)));
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
    camerawid->InitDushenCameraWidget(PARAM.cameraPtr0,m_args[0]);
    hbox_layout->addWidget(camerawid);
    DushenCameraWidget * camerawid1 = new DushenCameraWidget(nullptr);
    camerawid1->InitDushenCameraWidget(PARAM.cameraPtr1,m_args[1]);
    hbox_layout->addWidget(camerawid1);
    //启动相机
    camerawid->StartCamera();
    camerawid1->StartCamera();
}

void MainWindow::InitFlawShowWidget()
{
    connect(this, SIGNAL(sign_DisplayMain(cv::Mat)), this, SLOT(slot_DisplayMain(cv::Mat)));
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
    if (PARAM.databasePtr != nullptr)
        PARAM.databasePtr->queryTableData(datas, sql);
    if (datas.size()  > 0){
        m_glassResult.glassSummary = datas[0];
    }
    ui->glassTotalCountLB->setText(QString::number(m_glassResult.glassSummary.glasstotalcount));
    ui->glassTotalCountLB->setAlignment(Qt::AlignCenter);

    ui->currentGlassStatus->setText(QString(m_glassResult.glassSummary.currentglassstatus));
    ui->currentGlassStatus->setAlignment(Qt::AlignCenter);

    ui->glassOKCountLB->setText(QString::number(m_glassResult.glassSummary.OKcount));
    ui->glassOKCountLB->setAlignment(Qt::AlignCenter);

    ui->glassNGCountLB->setText(QString::number(m_glassResult.glassSummary.NGcount));
    ui->glassNGCountLB->setAlignment(Qt::AlignCenter);

    ui->qualicaficationRateLB->setText(QString::number(m_glassResult.glassSummary.passrate));
    ui->qualicaficationRateLB->setAlignment(Qt::AlignCenter);

    ui->ExceptionCountLB->setText(QString::number(m_glassResult.glassSummary.exceptioncount));
    ui->ExceptionCountLB->setAlignment(Qt::AlignCenter);
}

void MainWindow::InitDatabaseParam()
{
    if (PARAM.databasePtr != nullptr) { //启动程序时，获取新的主键
        defectPrimaryKey = PARAM.databasePtr->getCurrentDefectTableMaxID();
        glassPrimaryKey = PARAM.databasePtr->getCurrentGlassTableMaxID();
        sizePrimaryKey = PARAM.databasePtr->getCurrentSizeTableMaxID();
    }
    // PARAM赋值读取
    if (PARAM.jsoncppPtr != nullptr) {
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
        PARAM.jsoncppPtr->readRecipeFromJson(neddLoadJsonFileName, signalctrl);
        PARAM.ReassignValue(signalctrl);// 初始化全局变量
    }
    //注册回调函数
    connect(this,SIGNAL(sign_InsertDatabase()), this, SLOT(slot_InsertDatabase()));
}

void MainWindow::ProcessThreadCV()
{
    //
    // 根据信号平台帧信号获取图片
    //
LOOPGET:
    //std::this_thread::sleep_for(std::chrono::seconds(1));
    MainWindow::GetCameraBufferAndExceute();
    if (PARAM.currentsystem != SYSTEMSTATUS::STOP) {
        goto LOOPGET;
    }
}


///////////////////////////////////////////////////////private///////////////////////////////////////////////////////////////////
///
///

void MainWindow::upDateOverView()
{
    m_glassResult.glassSummary.id = 0; //todo:获取数据库表的主键
    m_glassResult.glassSummary.time = QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss");
    m_glassResult.glassSummary.glasstotalcount += 1; //玻璃块数加一
    if (m_glassResult.glassStatistics.defectOKorNG == "NG" || m_glassResult.glassStatistics.sizeOKorNG == "NG") {
        m_glassResult.glassSummary.currentglassstatus = "NG" ;
        m_glassResult.glassSummary.NGcount += 1;
    } else {
        m_glassResult.glassSummary.currentglassstatus = "OK";
        m_glassResult.glassSummary.OKcount += 1;
    }
    m_glassResult.glassSummary.passrate = (double)m_glassResult.glassSummary.OKcount / (double)m_glassResult.glassSummary.glasstotalcount;
    m_glassResult.glassSummary.exceptioncount = 0;
    m_glassResult.glassSummary.messagePath = "";
    m_glassResult.glassSummary.lastglassID = glassPrimaryKey;  //最后一块玻璃的ID,ID对应的是数据统计里面的ID

    ui->glassTotalCountLB->setText(QString::number(m_glassResult.glassSummary.glasstotalcount));
    ui->currentGlassStatus->setText(QString(m_glassResult.glassSummary.currentglassstatus));
    ui->glassOKCountLB->setText(QString::number(m_glassResult.glassSummary.OKcount));
    ui->glassNGCountLB->setText(QString::number(m_glassResult.glassSummary.NGcount));
    QString text = "%"+ QString::number(m_glassResult.glassSummary.passrate * 100);
    ui->qualicaficationRateLB->setText(text);
    ui->ExceptionCountLB->setText(QString::number(m_glassResult.glassSummary.exceptioncount));
    QString mes1 = "玻璃["+QString::number(glassPrimaryKey) + "] 玻璃结束状态更新成功。";
    INFOMATION.outputMessage(ui->loglistWidget,mes1);
}

void MainWindow::imageDisplay(CV_GLASSPART part, cv::Mat image)
{
    try{
        if (image.rows <= 0) {
            qDebug()<<"imageDisplay in param image.rows == 0";
            return;
        }
        //将不同帧图片拼接起来，注意非第一帧图片有重复区域
        if (part == CV_GLASSPART::HEAD || part == CV_GLASSPART::WholeGlass) {
            if (!m_glassRegion.empty())
                m_glassRegion.release();
            m_glassRegion = image;
        } else {
            if (image.rows != m_glassRegion.rows && m_glassRegion.rows != 0 ) {
                /* 每帧图像的行数因为仿射有变化，现在缩放统一大小 */
                double scaleFactor = (double)m_glassRegion.rows / (double)image.rows;// 计算缩放因子
                double newWidth1 = static_cast<int>((double)image.cols * scaleFactor);// 计算缩放后的宽
                qDebug()<<"(double)image.cols = "<<(double)image.cols <<", scaleFactor ="<<scaleFactor<<", m_glassRegion.rows ="<<m_glassRegion.rows;
                cv::resize(image, image, cv::Size(newWidth1, m_glassRegion.rows));
            }
            if (m_glassRegion.rows == 0 || m_glassRegion.cols == 0) {//算法误判头部
                qDebug()<<"算法误判头部:m_glassRegion.rows ="<<m_glassRegion.rows<<", m_glassRegion.cols ="<<m_glassRegion.cols;
                m_glassRegion = image;
            } else  {
                cv::hconcat(m_glassRegion,image,m_glassRegion);
            }
        }
        if (!m_glassRegion.empty()) {
            emit sign_DisplayMain(m_glassRegion);//显示图片
        }
    } catch(...) {
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


bool MainWindow::checkFrameParam(FrameImage imageunit0, FrameImage imageunit1)
{
    if (imageunit0.buffers.size() <= 0 || imageunit1.buffers.size() <= 0) {
        return false;
    }
    if (imageunit0.framecount != imageunit1.framecount || imageunit0.framecount <=0 || imageunit1.framecount <=0) {
        return false;
    }
    if (imageunit0.fieldnumberset <= 0 || imageunit1.fieldnumberset <= 0) {
        return false;
    }
    return true;
}



void MainWindow::slot_InsertDatabase()
{
    if (PARAM.databasePtr != nullptr) {
        PARAM.databasePtr->insertOneData(m_glassResult.glassStatistics);
        if ( !m_glassResult.glassDefects.empty() ){
            PARAM.databasePtr->batchInsertData(m_glassResult.glassDefects);
        }
        PARAM.databasePtr->batchInsertData(m_glassResult.glassSize);
        PARAM.databasePtr->insertOneData(m_glassResult.glassSummary);
    }
}

void  MainWindow::slot_InsertSizeDatabase(std::vector<GlassSizeInfo2> datas)
{
    if ( datas.empty() ){
        qDebug()<<"slot_InsertSizeDatabase Datas.empty()";
        return;
    } else {
        if (PARAM.databasePtr != nullptr) {
            PARAM.databasePtr->batchInsertData(datas);
        }
    }
}

/////////////////////////////////public slot///////////////////////////////////////////////////////////////

void MainWindow::slot_CloseSystem()
{
    if (PARAM.databasePtr != nullptr) {
        PARAM.databasePtr->closeDataBase();
        PARAM.databasePtr = nullptr;
        FreeLibrary(databaseDllHandle);
    }
    if (PARAM.algorithmPtr!= nullptr) {
        PARAM.algorithmPtr = nullptr;
        FreeLibrary(algorithmDllHandle);
    }
    if (PARAM.cameraPtr0 != nullptr && PARAM.cameraPtr1 != nullptr) {
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
    //
    // 进行开始流程，打开相机
    // 设置界面上相关按钮的亮和灰
    //
    m_pStart->setEnabled(false);
    m_pExit->setEnabled(false);
    m_pStop->setEnabled(true);
    m_pSettings->setEnabled(false);
    m_offline->setEnabled(false);

    if (PARAM.cameraPtr0 != nullptr && PARAM.cameraPtr1 != nullptr) {
        if (!PARAM.cameraPtr0->IsStarted(m_args[0].camName)){
            QString message = m_args[0].camName + tr("camera is not started.");
            INFOMATION.criticalMessageBox(this,message);
        }
        if (!PARAM.cameraPtr1->IsStarted(m_args[1].camName)){
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
            if (PARAM.algorithmPtr != nullptr) {
                // PARAM.algorithmPtr->RegisterResultCallback(std::bind(&MainWindow::MainWindowsDisplay, this, std::placeholders::_1));
                // //遍历容器
                // for(int i = 0; i < (int)offlineSelectedFiles.size(); ++i) {
                //     qDebug() << offlineSelectedFiles[i];//输出文件的完整路径名
                //     cv::Mat projectionImage,reflectionLightImage,reflectionDarkImage;
                //     projectionImage = cv::imread(offlineSelectedFiles[i].toStdString());
                //     PARAM.algorithmPtr->SyncExecu(i, projectionImage,reflectionLightImage,reflectionDarkImage);
                // }
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

void MainWindow::slot_GlassStaticTableInsertRowData(GlassDataBaseInfo2 info)
{
    MainWindow::insertGlassStaticTable(info);
}

void MainWindow::slot_SingleSizeUpdataTableData(std::vector<GlassSizeInfo2> infos)
{
    ui->singleSizeTableWidget->clear();
    QStringList headerLabels = {tr("序号"),
                                    tr("时间"),
                                    tr("类型"),
                                    tr("等级"),
                                    tr("长X(mm)"),
                                    tr("宽Y(mm)"),
                                    tr("边距X(mm)"),
                                    tr("边距Y(mm)"),
                                    tr("尺寸ID")};
    ui->singleSizeTableWidget->setColumnCount(headerLabels.size());
    ui->singleSizeTableWidget->setHorizontalHeaderLabels(headerLabels);
    ui->singleSizeTableWidget->setRowCount(0);
    MainWindow::batchInsertSizeTable(infos);
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

void MainWindow::GetCameraBufferAndExceute()
{
    FrameImage imageunit0;
    FrameImage imageunit1;
    // 获取每帧图片
CAMERA0:
    if (PARAM.cameraPtr0 != nullptr && PARAM.cameraPtr1 != nullptr) {
        PARAM.cameraPtr0->startGetFrameBuffer(imageunit0);
        if (imageunit0.buffers.empty()) {
            if (PARAM.currentsystem == SYSTEMSTATUS::STOP) return;
            goto CAMERA0;
        }
CAMERA1:
        PARAM.cameraPtr1->startGetFrameBuffer(imageunit1);
        if (imageunit1.buffers.empty()) {
            if (PARAM.currentsystem == SYSTEMSTATUS::STOP) return;
            goto CAMERA1;
        }
    }
    // 对imageunit进行参数检查
    if (!MainWindow::checkFrameParam(imageunit0, imageunit1)) {
        qDebug()<<"参数不符合要求，可能出现丢帧等情况";
        return;
    }

    if (PARAM.algorithmPtr != nullptr){
        cv::Mat projectionImage,reflectionLightImage,reflectionDarkImage;
        // 多个相机横向拼图
        PARAM.algorithmPtr->HorizontalPuzzle(imageunit0.framecount,
                                            imageunit0.buffers,
                                            imageunit1.buffers,
                                            PARAM.crops.args,
                                            projectionImage,
                                            reflectionLightImage,
                                            reflectionDarkImage);

        if (projectionImage.rows != 0 && reflectionLightImage.rows != 0 && reflectionDarkImage.rows != 0) {
            QString ID = QString::number(imageunit0.framecount);
            SyncSaveImage(projectionImage,"D:/HVCache/light/projectionImage"+ID+".jpg");
            SyncSaveImage(reflectionLightImage,"D:/HVCache/light/reflectionLightImage"+ID+".jpg");
            SyncSaveImage(reflectionDarkImage,"D:/HVCache/light/reflectionDarkImage"+ID+".jpg");
        } else {
            qDebug()<<"拼图出现错误";
        }

        // 执行当前算法
        NewGlassResult result = PARAM.algorithmPtr->SyncExecu(imageunit0.framecount,
                                                              projectionImage,
                                                              reflectionLightImage,
                                                              reflectionDarkImage);
        if (result.isEmpty) return;

        if (result.part == CV_GLASSPART::HEAD) {
            glassPrimaryKey += 1;
            m_glassResult.glassID = glassPrimaryKey;
        }

        // 纵向拼图
        PARAM.algorithmPtr->VerticalPuzzle(result,
                                           projectionImage,
                                           reflectionLightImage,
                                           reflectionDarkImage,
                                           m_glassResult.glassRegion0,
                                           m_glassResult.glassRegion1,
                                           m_glassResult.glassRegion2);

        // 匹配丝印和孔
        if (result.part == CV_GLASSPART::TAIL) {
            // 保存整图
            SyncSaveImage(m_glassResult.glassRegion0,"D:/HVCache/history/0.jpg");
            SyncSaveImage(m_glassResult.glassRegion1,"D:/HVCache/history/1.jpg");
            SyncSaveImage(m_glassResult.glassRegion2,"D:/HVCache/history/2.jpg");

            PARAM.algorithmPtr->onMatchSilkscreen(m_glassResult.glassRegion0,
                                                  m_glassResult.glassRegion1,
                                                  m_glassResult.glassRegion2,
                                                  m_glassResult.glassSize,0.3);//相似度设置为0.3

            // 对图像进行分区
            if (m_glassResult.glassSize.size() > 0 ) {// 有丝印
                result.divingX = PARAM.algorithmPtr->PartGlassAB(m_glassResult.glassSize[0].rect,
                                                                 PARAM.XCamera0Accuracy,
                                                                 result.AisLeft);
            } else {//
                qDebug()<<"未找到丝印";
                result.divingX = 0;
                result.AisLeft = true;
            }

            PARAM.algorithmPtr->onMatchHole(m_glassResult.glassRegion0,
                                            m_glassResult.glassRegion1,
                                            m_glassResult.glassRegion2,
                                            m_glassResult.glassSize);
        }

        // 逐帧处理结果
        try{
            MainWindow::imageDisplay(result.part, result.glassRegion);// 分帧显示透射场图像
            MainWindow::handleFrameData(result); // 处理缺陷数据
            if (result.part == CV_GLASSPART::TAIL) { // 玻璃结束
                MainWindow::summaryDefectNumber(result.divingX,
                                                result.AisLeft,
                                                result.sizeRes[0].rect);// 统计缺陷数据
                emit sign_GlassStaticTableInsertRowData(m_glassResult.glassStatistics); //更新统计信息
                emit sign_UpdateDefectTable(result.part, m_glassResult.glassDefects);   //更新缺陷数据
                MainWindow::handleFrameData(result.sizeRes);// 处理尺寸数据
                emit sign_SingleSizeUpdataTableData(m_glassResult.glassSize);//更新尺寸信息
                MainWindow::upDateOverView();               // 更新概述信息
                emit sign_InsertDatabase();                 // 更新数据库
                MainWindow::clearGlassDisplay();            //玻璃结束，清理
            }
        } catch (...) {
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
}

void MainWindow::slot_DisplayMain(cv::Mat image)
{
    try{
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
    } catch (...) {
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

void MainWindow::slot_UpdateDefectTable(CV_GLASSPART part, std::vector<GlassDefect2> FrameDefects)
{
    if (part == CV_GLASSPART::HEAD) {//清除表格
        ui->SingleFlawtableWidget->clear();
        QStringList headerLabels = {tr("序号"),
                                    tr("时间"),
                                    tr("类型"),
                                    tr("等级"),
                                    tr("坐标X"),
                                    tr("坐标Y"),
                                    tr("长"),
                                    tr("宽"),
                                    tr("面积"),
                                    tr("缺陷ID")};
        ui->SingleFlawtableWidget->setColumnCount(headerLabels.size());
        ui->SingleFlawtableWidget->setHorizontalHeaderLabels(headerLabels);
        ui->SingleFlawtableWidget->setRowCount(0);
    }
    if (FrameDefects.size() > 0 ) {
        QImage img1(FrameDefects[0].imagePath0);
        QImage img2(FrameDefects[0].imagePath1);
        QImage img3(FrameDefects[0].imagePath2);
        MainWindow::loadedPixmapImage(img1,ui->graphicsView,loadedPixmapItem);
        MainWindow::loadedPixmapImage(img2,ui->graphicsView_2,loadedPixmapItem2);
        MainWindow::loadedPixmapImage(img3,ui->graphicsView_3,loadedPixmapItem3);
        for (auto defect: m_glassResult.glassDefects) {
            MainWindow::insertDefectTable(defect);
        }
    }
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

void MainWindow::slot_UpdateDefectImages(QTableWidgetItem* item)
{
    try {
        if (item) {
            int row = item->row();
            qDebug()<<" row = "<<row;
            QString defectID = ui->SingleFlawtableWidget->item(row, 9)->text();
            qDebug()<<"defectID = "<<defectID;
            if (PARAM.databasePtr != nullptr) {
                QString querySql = QString("SELECT * FROM glass_defect WHERE id = %1;").arg(defectID.toInt());
                std::vector<GlassDefect2> datas;
                PARAM.databasePtr->queryTableData(datas, querySql);
                if (datas.size() > 0) {
                    QImage img1=QImage(datas[0].imagePath0);
                    QImage img2=QImage(datas[0].imagePath1);
                    QImage img3=QImage(datas[0].imagePath2);
                    if(img1.isNull()) {
                        qDebug() << "img1图像("<<datas[0].imagePath0<<")无法加载，可能文件不存在。";
                    } else {
                        loadedPixmapItem->loadImage(img1);
                        int nwidth = ui->graphicsView->width(), nheight = ui->graphicsView->height();
                        loadedPixmapItem->setQGraphicsViewWH(nwidth, nheight);
                        ui->graphicsView->setSceneRect((QRectF(-(nwidth / 2), -(nheight / 2), nwidth, nheight)));
                        ui->graphicsView->update();
                    }
                    if(img2.isNull()) {
                        qDebug() << "img2图像("<<datas[0].imagePath1<<")无法加载，可能文件不存在。";
                    } else {
                        loadedPixmapItem2->loadImage(img2);
                        int nwidth2 = ui->graphicsView_2->width(), nheight2 = ui->graphicsView_2->height();
                        loadedPixmapItem2->setQGraphicsViewWH(nwidth2, nheight2);
                        ui->graphicsView_2->setSceneRect((QRectF(-(nwidth2 / 2), -(nheight2 / 2), nwidth2, nheight2)));
                        ui->graphicsView_2->update();
                    }
                    if(img3.isNull()) {
                        qDebug() << "img3图像("<<datas[0].imagePath2<<")无法加载，可能文件不存在。";
                    } else {
                        loadedPixmapItem3->loadImage(img3);
                        int nwidth3 = ui->graphicsView_3->width(), nheight3 = ui->graphicsView_3->height();
                        loadedPixmapItem3->setQGraphicsViewWH(nwidth3, nheight3);
                        ui->graphicsView_3->setSceneRect((QRectF(-(nwidth3 / 2), -(nheight3 / 2), nwidth3, nheight3)));
                        ui->graphicsView_3->update();
                    }
                }
            }
        } else {
            qDebug()<<"item 为空";
        }
    } catch(...) {
        qDebug()<<" MainWindow::slot_UpdateDefectImages throw a unknow Exception.";
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

void MainWindow::slot_UpdateSizeImage(QTableWidgetItem* item)
{
    if (item) {
        int row = item->row();
        QString sizeID = ui->singleSizeTableWidget->item(row, 7)->text();
        qDebug()<<"sizeID = "<< sizeID;
        if (PARAM.databasePtr != nullptr) {
            QString querySql = QString("SELECT * FROM glass_sizeinfo WHERE id = %1;").arg(sizeID.toInt());
            std::vector<GlassSizeInfo2> datas;
            PARAM.databasePtr->queryTableData(datas, querySql);
            if (datas.size() > 0) {
                QImage img1=QImage(datas[0].imagePath0);
                QImage img2=QImage(datas[0].imagePath1);
                QImage img3=QImage(datas[0].imagePath2);
                if(img1.isNull()) {
                    qDebug() << "img1图像("<<datas[0].imagePath0<<")无法加载，可能文件不存在。";
                } else {
                    loadedPixmapItem50->loadImage(img1);
                    int nwidth = ui->graphicsView_Field_1->width(), nheight = ui->graphicsView_Field_1->height();
                    loadedPixmapItem50->setQGraphicsViewWH(nwidth, nheight);
                    ui->graphicsView_Field_1->setSceneRect((QRectF(-(nwidth / 2), -(nheight / 2), nwidth, nheight)));
                    ui->graphicsView_Field_1->update();
                }
                if(img2.isNull()) {
                    qDebug() << "img2图像("<<datas[0].imagePath1<<")无法加载，可能文件不存在。";
                } else {
                    loadedPixmapItem51->loadImage(img2);
                    int nwidth2 = ui->graphicsView_Field_2->width(), nheight2 = ui->graphicsView_Field_2->height();
                    loadedPixmapItem51->setQGraphicsViewWH(nwidth2, nheight2);
                    ui->graphicsView_Field_2->setSceneRect((QRectF(-(nwidth2 / 2), -(nheight2 / 2), nwidth2, nheight2)));
                    ui->graphicsView_Field_2->update();
                }
                if(img3.isNull()) {
                    qDebug() << "img3图像("<<datas[0].imagePath2<<")无法加载，可能文件不存在。";
                } else {
                    loadedPixmapItem52->loadImage(img3);
                    int nwidth3 = ui->graphicsView_Field_3->width(), nheight3 = ui->graphicsView_Field_3->height();
                    loadedPixmapItem52->setQGraphicsViewWH(nwidth3, nheight3);
                    ui->graphicsView_Field_3->setSceneRect((QRectF(-(nwidth3 / 2), -(nheight3 / 2), nwidth3, nheight3)));
                    ui->graphicsView_Field_3->update();
                }
            }
        }
    } else {
        qDebug()<<"item 为空";
    }
}

void MainWindow::slot_RebackHistoryImage()
{
    if (PARAM.currentsystem != SYSTEMSTATUS::RUNNING) {
        QString sql ="";
        //1、找到历史图片，显示到界面上
        //2、更新统计数据
        //3、生成缺陷小图并显示数据
        //4、生成尺寸信息并显示数据
    } else {
        INFOMATION.criticalMessageBox(this,"系统运行过程中，不能切换当前玻璃数据！");
    }
}

void MainWindow::InitImageCacheDirectory()
{
    try{
        createDir(HISTORYPATH);
        createDir(CAMERAPATH);
        createDir(CACHEPATH);
        createDir(LIGHTPATH);
    } catch(...){
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


void MainWindow::contextMenuEvent(QContextMenuEvent *event)
{
    QMenu menu(this);
    // 设置右键菜单样式
    menu.setStyleSheet("QMenu {"
                       "background-color: #f0f0f0; "
                       "border: 1px solid gray; "
                       "}"
                       "QMenu::item {"
                       "padding: 5px 20px; "
                       "}"
                       "QMenu::item:selected {"
                       "background-color: #ccc; "
                       "}");

    QAction *action1 = new QAction("上一页", this);
    QAction *action2 = new QAction("下一页", this);

    connect(action1, &QAction::triggered, this, [this]() {
        qDebug() << "菜单项1被点击";
    });
    connect(action2, &QAction::triggered, this, [this]() {
        qDebug() << "菜单项2被点击";
    });

    menu.addAction(action1);
    menu.addAction(action2);

    menu.exec(event->globalPos());
}

void MainWindow::insertGlassStaticTable(GlassDataBaseInfo2 data)
{
    try{
        QTableWidgetItem *itemID = ui->glassstatictablewidget->item(0, 0);
        //
        // 同一块玻璃的数据插入到表格的同一行，新玻璃插入到第一行
        //
        if (itemID != NULL) {
            if(itemID->text().toInt() != data.id){
                ui->glassstatictablewidget->insertRow(0);
            }
        } else {
            ui->glassstatictablewidget->insertRow(0);
        }
        // NG背景颜色为红色，OK背景颜色为绿色
        QBrush brush = Qt::white;
        if (data.OKorNG != "OK") { //OK/NG
            brush = Qt::red;
        } else {
            brush = Qt::green;
        }
        MainWindow::setTableWidgetItem(0,0,QString::number(data.id),ui->glassstatictablewidget,brush);//ID
        MainWindow::setTableWidgetItem(0,1,data.time,ui->glassstatictablewidget,brush);//时间
        MainWindow::setTableWidgetItem(0,2,QString::number(data.id),ui->glassstatictablewidget,brush);//OK/NG
        MainWindow::setTableWidgetItem(0,3,data.sizeOKorNG,ui->glassstatictablewidget,brush);//尺寸OK/NG
        MainWindow::setTableWidgetItem(0,4,QString::number(data.length,'f', 2),ui->glassstatictablewidget,brush);//长度
        MainWindow::setTableWidgetItem(0,5,QString::number(data.width,'f', 2),ui->glassstatictablewidget,brush);//宽度
        MainWindow::setTableWidgetItem(0,6,data.defectOKorNG,ui->glassstatictablewidget,brush);//缺陷OK/NG
        MainWindow::setTableWidgetItem(0,7,QString::number(data.defectNumber),ui->glassstatictablewidget,brush);//缺陷数量
        MainWindow::setTableWidgetItem(0,8,QString::number(data.huahenNumber),ui->glassstatictablewidget,brush);//划痕
        MainWindow::setTableWidgetItem(0,9,QString::number(data.yiwuNumber),ui->glassstatictablewidget,brush);//异物
        MainWindow::setTableWidgetItem(0,10,QString::number(data.qipaoNumber),ui->glassstatictablewidget,brush);//气泡
        MainWindow::setTableWidgetItem(0,11,QString::number(data.madianNumber),ui->glassstatictablewidget,brush);//麻点
        MainWindow::setTableWidgetItem(0,12,QString::number(data.shuiyinNumber),ui->glassstatictablewidget,brush);//水印
        MainWindow::setTableWidgetItem(0,13,QString::number(data.youmobuliangNumber),ui->glassstatictablewidget,brush);//油墨不良
        MainWindow::setTableWidgetItem(0,14,QString::number(data.juchibianNumber),ui->glassstatictablewidget,brush);//锯齿边
        MainWindow::setTableWidgetItem(0,15,QString::number(data.siyinquexianNumber),ui->glassstatictablewidget,brush);// 丝印缺陷
        MainWindow::setTableWidgetItem(0,16,QString::number(data.guahuaNumber),ui->glassstatictablewidget,brush);// 刮花
        MainWindow::setTableWidgetItem(0,17,QString::number(data.liewenNumber),ui->glassstatictablewidget,brush);// 裂纹
        MainWindow::setTableWidgetItem(0,18,QString::number(data.benbianjiaoNumber),ui->glassstatictablewidget,brush);// 崩边角
        // 设置表格内容居中显示
        for (int i = 0; i < ui->glassstatictablewidget->columnCount(); ++i) {
            ui->glassstatictablewidget->horizontalHeaderItem(i)->setTextAlignment(Qt::AlignCenter);
        }
        ui->glassstatictablewidget->verticalHeader()->setVisible(false); // 隐藏行号
    } catch(...) {
        std::exception_ptr eptr = std::current_exception();
        if (eptr) {
            try {
                std::rethrow_exception(eptr);
            } catch (const std::exception& ex) {
                qDebug() << "insertGlassStaticTable Exception: " << ex.what();
            }
        }
    }

}

void MainWindow::setTableWidgetItem(int row,
                                    int col,
                                    QString text,
                                    QTableWidget* table,
                                    QBrush brush/* = Qt::white*/)
{
    QTableWidgetItem* item = new QTableWidgetItem(text);
    item->setBackground(brush);
    item->setTextAlignment(Qt::AlignCenter);
    item->setFlags(item->flags() & ~Qt::ItemIsEditable);
    table->setItem(row, col, item);
}

void MainWindow::summaryDefectNumber(int diviX, bool AisLeft, cv::Rect siyinRect)
{
    for(auto defect : m_glassResult.glassDefects) {
        if (defect.defectType == tr("划痕")) {
            MainWindow::NGorOKHuaheng(defect);
        } else if (defect.defectType == tr("异物")) {
            MainWindow::NGorOKyiwu(defect, diviX, AisLeft);
        } else if (defect.defectType == tr("气泡")) {
            MainWindow::NGorOKqipao(defect);
        } else if (defect.defectType == tr("麻点")) {
            MainWindow::NGorOKmadian(defect, diviX, AisLeft, siyinRect);
        } else if (defect.defectType == tr("水印")) {
            MainWindow::NGorOKshuiyin(defect, diviX, AisLeft);
        } else if (defect.defectType == tr("油墨不良")) {
            MainWindow::NGorOKyoumobuliang(defect, diviX, AisLeft, siyinRect);
        } else if (defect.defectType == tr("锯齿边")) {
            MainWindow::NGorOKjuchibian(defect);
        } else if (defect.defectType == tr("丝印缺陷")) {
            MainWindow::NGorOKsiyinquexian(defect);
        } else if (defect.defectType == tr("刮花")) {
            MainWindow::NGorOKguahua(defect, diviX, AisLeft);
        } else if (defect.defectType == tr("裂纹")) {
            MainWindow::NGorOKliewen(defect);
        } else if (defect.defectType == tr("崩边角")) {
            MainWindow::NGorOKbengbianjiao(defect);
        }
    }
}

void MainWindow::insertDefectTable(GlassDefect2 defect)
{
    ui->SingleFlawtableWidget->insertRow(0);

    MainWindow::setTableWidgetItem(0,0,QString::number(defect.defectId),ui->SingleFlawtableWidget);//ID
    MainWindow::setTableWidgetItem(0,1,defect.time,ui->SingleFlawtableWidget);//时间
    MainWindow::setTableWidgetItem(0,2,defect.defectType,ui->SingleFlawtableWidget);//类型
    MainWindow::setTableWidgetItem(0,3,defect.defectLevel,ui->SingleFlawtableWidget);//等级
    MainWindow::setTableWidgetItem(0,4,QString::number(defect.x,'f', 2),ui->SingleFlawtableWidget);//坐标X
    MainWindow::setTableWidgetItem(0,5,QString::number(defect.y,'f', 2),ui->SingleFlawtableWidget);//坐标Y
    MainWindow::setTableWidgetItem(0,6,QString::number(defect.length,'f', 2),ui->SingleFlawtableWidget);// 长
    MainWindow::setTableWidgetItem(0,7,QString::number(defect.width,'f', 2),ui->SingleFlawtableWidget);// 宽
    MainWindow::setTableWidgetItem(0,8,QString::number(defect.area,'f', 2),ui->SingleFlawtableWidget);// 面积
    MainWindow::setTableWidgetItem(0,9,QString::number(defect.id),ui->SingleFlawtableWidget);// 缺陷id

    for (int row = 0; row < ui->SingleFlawtableWidget->rowCount(); ++row) {
        for (int col = 0; col < ui->SingleFlawtableWidget->columnCount(); ++col) {
            QTableWidgetItem* item = ui->SingleFlawtableWidget->item(row, col);
            if (item) {
                item->setFlags(item->flags() & ~Qt::ItemIsEditable);
            }
        }
    }
}

void MainWindow::loadedPixmapImage(QImage img,
                                   QGraphicsView* view,
                                   MyGraphicsItem* loadImgItem)
{
    loadImgItem->loadImage(img);
    int nwidth = view->width();
    int nheight = view->height();
    loadImgItem->setQGraphicsViewWH(nwidth, nheight);
    view->setSceneRect((QRectF(-(nwidth / 2), -(nheight / 2), nwidth, nheight)));
    view->update();
}

void MainWindow::initLoadedImage(MyGraphicsItem* loadItem, QGraphicsView* view)
{
    QGraphicsScene* scene = new QGraphicsScene();
    loadItem = new MyGraphicsItem();
    view->setScene(scene);
    scene->addItem(loadItem);
}

void MainWindow::insertSizeTable(GlassSizeInfo2 info)
{
    ui->singleSizeTableWidget->insertRow(0);
    MainWindow::setTableWidgetItem(0,0,QString::number(info.sizeID),ui->singleSizeTableWidget);// 序号
    MainWindow::setTableWidgetItem(0,1,info.time,ui->singleSizeTableWidget);// 时间
    MainWindow::setTableWidgetItem(0,2,info.sizeType,ui->singleSizeTableWidget);// 类型
    MainWindow::setTableWidgetItem(0,3,info.sizeLevel,ui->singleSizeTableWidget);// 等级
    MainWindow::setTableWidgetItem(0,4,QString::number(info.lengthX, 'f', 2),ui->singleSizeTableWidget);// 长X
    MainWindow::setTableWidgetItem(0,5,QString::number(info.widthY, 'f', 2),ui->singleSizeTableWidget);// 宽Y
    MainWindow::setTableWidgetItem(0,6,QString::number(info.marginsX, 'f', 2),ui->singleSizeTableWidget);// 边距X
    MainWindow::setTableWidgetItem(0,7,QString::number(info.marginsY, 'f', 2),ui->singleSizeTableWidget);// 边距Y
    MainWindow::setTableWidgetItem(0,8,QString::number(info.id),ui->singleSizeTableWidget);
}

void MainWindow::batchInsertSizeTable(std::vector<GlassSizeInfo2> infos)
{
    if(infos.size() > 0 ) {
        for (auto info : infos) {
            MainWindow::insertSizeTable(info);
        }
        for (int row = 0; row < ui->singleSizeTableWidget->rowCount(); ++row) {
            for (int col = 0; col < ui->singleSizeTableWidget->columnCount(); ++col) {
                QTableWidgetItem* item = ui->singleSizeTableWidget->item(row, col);
                if (item) {
                    item->setFlags(item->flags() & ~Qt::ItemIsEditable);
                }
            }
        }
        //显示孔洞小图
        QImage img2(infos[0].imagePath0);
        MainWindow::loadedPixmapImage(img2,ui->graphicsView_Field_1,loadedPixmapItem50);
        QImage img3(infos[0].imagePath1);
        MainWindow::loadedPixmapImage(img3,ui->graphicsView_Field_2,loadedPixmapItem51);
        QImage img4(infos[0].imagePath2);
        MainWindow::loadedPixmapImage(img3,ui->graphicsView_Field_3,loadedPixmapItem52);
    }
}

//查看指定范围内的缺陷数量
int MainWindow::RangeDefectCount(std::vector<cv::Rect> cacheVes, int Xmm, int MaxDefectCount)
{
    int XmmPix = Xmm / PARAM.YAccuracy;
    if ((int)cacheVes.size() >= MaxDefectCount) {
        std::vector<int> Result;
        for (int i = 0; i < (int)cacheVes.size(); ++i) {
            int count = 0;
            for (int j = 0; j < (int)cacheVes.size(); ++j) {
                double distance = std::sqrt((cacheVes[i].x - cacheVes[j].x)*(cacheVes[i].x - cacheVes[j].x) + (cacheVes[i].y - cacheVes[j].y)*(cacheVes[i].y - cacheVes[j].y));
                if (distance < XmmPix) {
                    ++count;
                }
            }
            Result.push_back(count);
        }
        int res = *std::max_element(Result.begin(),Result.end());
        return res;
    }
}

// 划痕判断NG
void MainWindow::NGorOKHuaheng(GlassDefect2 defect)
{
    if (defect.gregion == glassRegion::EDGE) {
        if (defect.rect.width * PARAM.XCamera0Accuracy > 5 || defect.rect.height * PARAM.YAccuracy > 5) {//边部大于5mm划伤算缺陷
            m_glassResult.glassStatistics.defectOKorNG = "NG";
            m_glassResult.glassStatistics.huahenNumber += 1;
            m_glassResult.glassStatistics.defectNumber += 1;
        }
    } else if(defect.gregion == glassRegion::FACE) {
        m_glassResult.glassStatistics.defectOKorNG = "NG";
        m_glassResult.glassStatistics.huahenNumber += 1;
        m_glassResult.glassStatistics.defectNumber += 1;
    }
}

void MainWindow::NGorOKyiwu(GlassDefect2 defect, int diviX, bool AisLeft)
{
    m_glassResult.glassStatistics.yiwuNumber += 1;
    m_glassResult.glassStatistics.defectNumber += 1;
    if (m_glassResult.glassStatistics.defectOKorNG == "NG")//已经NG了，不需要再判断
        return;
    if (AisLeft) {// A区在左侧
        if (defect.x <= diviX) {
            m_glassResult.glassStatistics.AyiwuNumber += 1;
        } else {
            m_glassResult.glassStatistics.ByiwuNumber += 1;
        }
    } else {// B区在右侧
        if (defect.x <= diviX) {
            m_glassResult.glassStatistics.ByiwuNumber += 1;
        } else {
            m_glassResult.glassStatistics.AyiwuNumber += 1;
        }
    }
    if (m_glassResult.glassStatistics.ByiwuNumber > 3 || m_glassResult.glassStatistics.AyiwuNumber > 3) {
        m_glassResult.glassStatistics.defectOKorNG = "NG";
    }
}

void MainWindow::NGorOKqipao(GlassDefect2 defect)
{
    m_glassResult.glassStatistics.qipaoNumber += 1;
    m_glassResult.glassStatistics.defectNumber += 1;
    if (m_glassResult.glassStatistics.defectOKorNG == "NG")//已经NG了，不需要再判断
        return;
    if (defect.rect.width * PARAM.XCamera0Accuracy > 0.3 || defect.rect.height * PARAM.YAccuracy > 0.3) {
        m_glassResult.glassStatistics.defectOKorNG = "NG";
    } else if (defect.rect.width * PARAM.XCamera0Accuracy <= 0.3) {
        m_glassResult.glassStatistics.sqipaoNumber += 1;
    }
    if (m_glassResult.glassStatistics.sqipaoNumber > 2) {
        m_glassResult.glassStatistics.defectOKorNG = "NG";
    }
}

void MainWindow::NGorOKmadian(GlassDefect2 defect, int diviX, bool AisLeft, cv::Rect siyinRect)
{
    if (defect.rect.height * PARAM.YAccuracy > 0.3 || defect.rect.width * PARAM.XCamera0Accuracy > 0.3) {//过滤一级点
        m_glassResult.glassStatistics.madianNumber += 1;
        m_glassResult.glassStatistics.defectNumber += 1;
        if (m_glassResult.glassStatistics.defectOKorNG == "NG")//已经NG了，不需要再判断
            return;
        int pix30mm = max(30/PARAM.YAccuracy,30/PARAM.XCamera0Accuracy);
        if (defect.rect.height * PARAM.YAccuracy <= 0.5 || defect.rect.width * PARAM.XCamera0Accuracy <= 0.5) {//二级点
            if (defect.x >= (siyinRect.x - pix30mm) && defect.y >= (siyinRect.y - pix30mm)
                && defect.x <= (siyinRect.x + siyinRect.width + pix30mm) && defect.y<= (siyinRect.y + siyinRect.height + pix30mm)) {//在丝印外延30mm内
                m_AmadianRects.push_back(defect.rect);
                m_glassResult.glassStatistics.siyin30mm2madianNumber += 1;
            } else {
                if (AisLeft) {// A区在左侧
                    if (defect.x <= diviX) {
                        m_glassResult.glassStatistics.A2madianNumber += 1;
                        m_AmadianRects.push_back(defect.rect);
                    } else {
                        m_glassResult.glassStatistics.B2madianNumber += 1;
                        m_BmadianRects.push_back(defect.rect);
                    }
                } else { // A区在右侧
                    if (defect.x <= diviX) {
                        m_glassResult.glassStatistics.B2madianNumber += 1;
                        m_AmadianRects.push_back(defect.rect);
                    } else {
                        m_glassResult.glassStatistics.A2madianNumber += 1;
                        m_BmadianRects.push_back(defect.rect);
                    }
                }
            }
        } else { //三级点
            if (defect.x >= (siyinRect.x - pix30mm) && defect.y >= (siyinRect.y - pix30mm)
                && defect.x <= (siyinRect.x + siyinRect.width + pix30mm) && defect.y<= (siyinRect.y + siyinRect.height + pix30mm)) {//在丝印外延30mm内
                m_glassResult.glassStatistics.siyin30mm3madianNumber += 1;
            } else {
                if (AisLeft) {// A区在左侧
                    if (defect.x <= diviX) {
                        m_glassResult.glassStatistics.A3madianNumber += 1;
                        m_AmadianRects.push_back(defect.rect);
                    } else {
                        m_glassResult.glassStatistics.B3madianNumber += 1;
                        m_BmadianRects.push_back(defect.rect);
                    }
                } else { // A区在右侧
                    if (defect.x <= diviX) {
                        m_glassResult.glassStatistics.B3madianNumber += 1;
                        m_BmadianRects.push_back(defect.rect);
                    } else {
                        m_glassResult.glassStatistics.A3madianNumber += 1;
                        m_AmadianRects.push_back(defect.rect);
                    }
                }
            }
        }
        // A、B区10mm范围内的麻点数量
        if (m_glassResult.glassStatistics.A10mmmadianNumber < 3) {
            m_glassResult.glassStatistics.A10mmmadianNumber = MainWindow::RangeDefectCount(m_AmadianRects, 10, 3);
        }
        if (m_glassResult.glassStatistics.B10mmmadianNumber < 6) {
            m_glassResult.glassStatistics.B10mmmadianNumber = MainWindow::RangeDefectCount(m_BmadianRects, 10, 6);
        }
        // 判断是否NG
        if (m_glassResult.glassStatistics.A2madianNumber > 5 || m_glassResult.glassStatistics.A3madianNumber > 2
            || m_glassResult.glassStatistics.B2madianNumber >10 || m_glassResult.glassStatistics.B3madianNumber > 4
            || m_glassResult.glassStatistics.siyin30mm2madianNumber >2 || m_glassResult.glassStatistics.siyin30mm3madianNumber>1
            || m_glassResult.glassStatistics.A10mmmadianNumber >= 3 || m_glassResult.glassStatistics.B10mmmadianNumber >= 6) {
            m_glassResult.glassStatistics.defectOKorNG = "NG";
        }
    }
}

void MainWindow::NGorOKshuiyin(GlassDefect2 defect, int diviX, bool AisLeft)
{
    if (defect.rect.height * PARAM.YAccuracy > 0.5 || defect.rect.width * PARAM.XCamera0Accuracy > 0.5) {
        m_glassResult.glassStatistics.shuiyinNumber += 1;
        m_glassResult.glassStatistics.defectNumber += 1;
        if (m_glassResult.glassStatistics.defectOKorNG == "NG")//已经NG了，不需要再判断
            return;
        if (AisLeft) {// A区在左侧
            if (defect.x <= diviX) {
                m_glassResult.glassStatistics.AshuiyinNumber += 1;
            } else {
                m_BshuiyinRects.push_back(defect.rect);
            }
        } else { // A区在右侧
            if (defect.x <= diviX) {
                m_glassResult.glassStatistics.AshuiyinNumber += 1;
            } else {
                m_BshuiyinRects.push_back(defect.rect);
            }
        }
    }
    if (m_glassResult.glassStatistics.B5mmshuiyinNumber < 3) {//B区5mm范围内的水印数量
        m_glassResult.glassStatistics.B5mmshuiyinNumber = MainWindow::RangeDefectCount(m_BshuiyinRects, 5, 3);
    }
    if (m_glassResult.glassStatistics.AshuiyinNumber > 0 || m_glassResult.glassStatistics.B5mmshuiyinNumber >= 3) {
        m_glassResult.glassStatistics.defectOKorNG = "NG";
    }
}

void MainWindow::NGorOKyoumobuliang(GlassDefect2 defect, int diviX, bool AisLeft, cv::Rect siyinRect)
{
    if (defect.rect.height * PARAM.YAccuracy > 0.3 || defect.rect.width * PARAM.XCamera0Accuracy > 0.3) {
        m_glassResult.glassStatistics.youmobuliangNumber += 1;
        m_glassResult.glassStatistics.defectNumber += 1;
        if (m_glassResult.glassStatistics.defectOKorNG == "NG")//已经NG了，不需要再判断
            return;
        int pix30mm = max(30/PARAM.YAccuracy,30/PARAM.XCamera0Accuracy);
        if (defect.rect.height * PARAM.YAccuracy <= 0.5 || defect.rect.width * PARAM.XCamera0Accuracy <= 0.5) {//二级点
            if (defect.x >= (siyinRect.x - pix30mm) && defect.y >= (siyinRect.y - pix30mm)
                && defect.x <= (siyinRect.x + siyinRect.width + pix30mm) && defect.y<= (siyinRect.y + siyinRect.height + pix30mm)){//丝印外延30mm
                m_glassResult.glassStatistics.siyin30mm2youmobuliangNumber += 1;
                m_A10mm2youmobuliangRects.push_back(defect.rect);
            } else {
                if (AisLeft) {// A区在左侧
                    if (defect.x <= diviX) {
                        m_glassResult.glassStatistics.A2youmobuliangNumber += 1;
                        m_A10mm2youmobuliangRects.push_back(defect.rect);
                    } else {
                        m_glassResult.glassStatistics.B2youmobuliangNumber += 1;
                        m_B10mm2youmobuliangRects.push_back(defect.rect);
                    }
                } else { // A区在右侧
                    if (defect.x <= diviX) {
                        m_glassResult.glassStatistics.B2youmobuliangNumber += 1;
                        m_B10mm2youmobuliangRects.push_back(defect.rect);
                    } else {
                        m_glassResult.glassStatistics.A2youmobuliangNumber += 1;
                        m_A10mm2youmobuliangRects.push_back(defect.rect);
                    }
                }
            }
        } else { // 三级点
            if (defect.x >= (siyinRect.x - pix30mm) && defect.y >= (siyinRect.y - pix30mm)
                && defect.x <= (siyinRect.x + siyinRect.width + pix30mm) && defect.y<= (siyinRect.y + siyinRect.height + pix30mm)){//丝印外延30mm
                m_glassResult.glassStatistics.siyin30mm3youmobuliangNumber += 1;
                m_A10mm3youmobuliangRects.push_back(defect.rect);
            } else {
                if (AisLeft) {// A区在左侧
                    if (defect.x <= diviX) {
                        m_A10mm3youmobuliangRects.push_back(defect.rect);
                        m_glassResult.glassStatistics.A3youmobuliangNumber += 1;
                    } else {
                        m_B10mm3youmobuliangRects.push_back(defect.rect);
                        m_glassResult.glassStatistics.B3youmobuliangNumber += 1;
                    }
                } else { // A区在右侧
                    if (defect.x <= diviX) {
                        m_A10mm3youmobuliangRects.push_back(defect.rect);
                        m_glassResult.glassStatistics.B3youmobuliangNumber += 1;
                    } else {
                        m_B10mm3youmobuliangRects.push_back(defect.rect);
                        m_glassResult.glassStatistics.A3youmobuliangNumber += 1;
                    }
                }
            }
        }
        if (m_glassResult.glassStatistics.A10mm2youmobuliangNumber <= 3 || m_glassResult.glassStatistics.A10mm3youmobuliangNumber <= 2
            || m_glassResult.glassStatistics.B10mm2youmobuliangNumber <= 6 || m_glassResult.glassStatistics.B10mm3youmobuliangNumber <= 4) { //10mm范围内不允许有...
            m_glassResult.glassStatistics.A10mm2youmobuliangNumber = MainWindow::RangeDefectCount(m_A10mm2youmobuliangRects, 10, 3);
            m_glassResult.glassStatistics.A10mm3youmobuliangNumber = MainWindow::RangeDefectCount(m_A10mm3youmobuliangRects, 10, 2);
            m_glassResult.glassStatistics.B10mm2youmobuliangNumber = MainWindow::RangeDefectCount(m_B10mm2youmobuliangRects, 10, 6);
            m_glassResult.glassStatistics.B10mm3youmobuliangNumber = MainWindow::RangeDefectCount(m_B10mm3youmobuliangRects, 10, 4);
        }
        // 判断NG
        if (m_glassResult.glassStatistics.A3youmobuliangNumber > 3 || m_glassResult.glassStatistics.A2youmobuliangNumber >5
            || m_glassResult.glassStatistics.A10mm2youmobuliangNumber > 3 || m_glassResult.glassStatistics.A10mm3youmobuliangNumber >2
            || m_glassResult.glassStatistics.B2youmobuliangNumber > 10 || m_glassResult.glassStatistics.B3youmobuliangNumber > 6
            || m_glassResult.glassStatistics.B10mm2youmobuliangNumber > 6 || m_glassResult.glassStatistics.B10mm3youmobuliangNumber >4
            || m_glassResult.glassStatistics.siyin30mm2youmobuliangNumber > 2 || m_glassResult.glassStatistics.siyin30mm3youmobuliangNumber > 1) {
            m_glassResult.glassStatistics.defectOKorNG = "NG";
        }
    }
}

void MainWindow::NGorOKjuchibian(GlassDefect2 defect)
{
    if (defect.rect.height * PARAM.YAccuracy > 1 || defect.rect.width * PARAM.XCamera0Accuracy > 1) {
        m_glassResult.glassStatistics.juchibianNumber += 1;
        m_glassResult.glassStatistics.defectNumber += 1;
        if (m_glassResult.glassStatistics.defectOKorNG == "NG")//已经NG了，不需要再判断
            return;
        double pix100mm = (double)100.0 / PARAM.YAccuracy;
        if (m_glassResult.glassStatistics.juchibianAllLength < pix100mm) {
            m_juchibianAllLengthRects += defect.rect.height;
            m_juchibianAllWidthRects += defect.rect.width;
            m_glassResult.glassStatistics.juchibianAllLength = std::max<int>(m_juchibianAllLengthRects,m_juchibianAllWidthRects);
        }
        if (m_glassResult.glassStatistics.juchibianAllLength > pix100mm) {
            m_glassResult.glassStatistics.defectOKorNG = "NG";
        }
    }
}

void MainWindow::NGorOKsiyinquexian(GlassDefect2 defect)
{
    if(defect.defectLevel == "NG") {
        m_glassResult.glassStatistics.siyinquexianNumber += 1;
        m_glassResult.glassStatistics.defectNumber += 1;
        m_glassResult.glassStatistics.defectOKorNG = "NG";
    }
}

void MainWindow::NGorOKguahua(GlassDefect2 defect, int diviX, bool AisLeft)
{
    if (defect.rect.height * PARAM.YAccuracy > 1 || defect.rect.width * PARAM.XCamera0Accuracy > 1) {
        m_glassResult.glassStatistics.guahuaNumber += 1;
        m_glassResult.glassStatistics.defectNumber += 1;
        if (AisLeft) {// A区在左侧
            if (defect.x <= diviX) {
                m_glassResult.glassStatistics.AguahuaNumber += 1;
            }
        } else { // A区在右侧
            if (defect.x >= diviX) {
                m_glassResult.glassStatistics.AguahuaNumber += 1;
            }
        }
        if (m_glassResult.glassStatistics.AguahuaNumber > 0) {
            m_glassResult.glassStatistics.defectOKorNG = "NG";
        }
    }
}

void MainWindow::NGorOKliewen(GlassDefect2 defect)
{
    if (defect.rect.height * PARAM.YAccuracy > 1 && defect.rect.width * PARAM.XCamera0Accuracy > 0.1){
        m_glassResult.glassStatistics.liewenNumber += 1;
        m_glassResult.glassStatistics.defectNumber += 1;
        m_glassResult.glassStatistics.defectOKorNG = "NG";
    }
}

void MainWindow::NGorOKbengbianjiao(GlassDefect2 defect)
{
    if (defect.rect.height * PARAM.YAccuracy > 1 || defect.rect.width * PARAM.XCamera0Accuracy > 1){
        m_glassResult.glassStatistics.benbianjiaoNumber += 1;
        m_glassResult.glassStatistics.defectNumber += 1;
        m_glassResult.glassStatistics.defectOKorNG = "NG";
    }
}

void MainWindow::handleFrameData(NewGlassResult result)
{
    int defectId = result.defectRes.size();
    m_glassResult.glassStatistics.length += result.pixGlassLength * PARAM.XCamera0Accuracy;
    m_glassResult.glassStatistics.width += result.pixGlassWidth * PARAM.YAccuracy;
    for (auto& defect : result.defectRes) {
        defect.id = ++defectPrimaryKey;                                    // 主键id,在所有缺陷中的顺序
        defect.defectId = ++defectId;
        defect.x = defect.pixX * PARAM.XCamera0Accuracy;
        defect.y = defect.pixY * PARAM.YAccuracy;
        defect.length = defect.pixLength * PARAM.YAccuracy;
        defect.width = defect.pixWidth * PARAM.XCamera0Accuracy;
        defect.area = defect.pixArea * PARAM.XCamera0Accuracy;
        defect.glassid = glassPrimaryKey;
        m_glassResult.glassDefects.push_back(defect);//将每帧数据插入全局变量中
    }
}

void MainWindow::handleFrameData(std::vector<GlassSizeInfo2>& glassSize)
{
    int sizeID = 0;
    for (auto& size : glassSize) {
        size.sizeID = ++sizeID;
        size.lengthX = size.Pixlength * PARAM.YAccuracy;
        size.widthY = size.PixWidth * PARAM.XCamera0Accuracy;
        size.marginsX = size.PixMarginsX * PARAM.YAccuracy;
        size.marginsY = size.PixMarginsY * PARAM.XCamera0Accuracy;
        size.glassid = glassPrimaryKey;
        m_glassResult.glassSize.push_back(size);
    }
}


void MainWindow::clearGlassDisplay()
{
    m_AmadianRects.clear();
    m_BmadianRects.clear();
    m_BshuiyinRects.clear();
    m_A10mm2youmobuliangRects.clear();
    m_A10mm3youmobuliangRects.clear();
    m_B10mm2youmobuliangRects.clear();
    m_B10mm3youmobuliangRects.clear();
    m_juchibianAllLengthRects = 0;
    m_juchibianAllWidthRects = 0;
    if (!m_glassResult.glassRegion0.empty())
        m_glassResult.glassRegion0.release();
    if (!m_glassResult.glassRegion1.empty())
        m_glassResult.glassRegion1.release();
    if (!m_glassResult.glassRegion2.empty())
        m_glassResult.glassRegion2.release();
    m_glassResult.glassStatistics = GlassDataBaseInfo2();
    m_glassResult.glassDefects.clear();
    m_glassResult.glassSize.clear();
}


