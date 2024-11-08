#include "DataAnalysis.h"
#include "ui_DataAnalysis.h"
#include <QMessageBox>
#include <QDebug>
#include <QtCharts>
#include <QBarSeries>
#include <QBarCategoryAxis>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtCharts/QChartView>
#include <QtCharts/QBarSet>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarCategoryAxis>
#include <QtCharts/QValueAxis>
#include <QtCore/QString>
#include <windows.h>

typedef HSDatabaseNamespace::HSDatabaseInterface* (*CreateDatabaseObjectFunc)();

DataAnalysis::DataAnalysis(QWidget *parent) :
    QWidget(parent)
    , ui(new Ui::DataAnalysis)
    , databasePtr(nullptr)
{
    ui->setupUi(this);

    if (databasePtr == nullptr) {
        QString exePath = QCoreApplication::applicationDirPath();
        QString dllPath = exePath + "/../database/database.dll";
        HMODULE dllHandle = LoadLibrary(dllPath.toStdWString().c_str());
        if (!dllHandle) {
            qFatal() << "Failed to load DLL. Error code: " << GetLastError();
        }
        // 获取创建数据库对象的函数指针
        CreateDatabaseObjectFunc createFunc = (CreateDatabaseObjectFunc)GetProcAddress(dllHandle, "createDatabaseObject");
        if (!createFunc) {
            qFatal() << "Failed to get function pointer. Error code: " << GetLastError() ;
            FreeLibrary(dllHandle);
        }
        databasePtr = createFunc();
    }

    scene=new QGraphicsScene();
    loadedPixmapItem = new MyGraphicsItem();
    ui->graphicsView->setScene(scene);
    scene->addItem(loadedPixmapItem);

    scene2=new QGraphicsScene();
    loadedPixmapItem2 = new MyGraphicsItem();
    ui->graphicsView_2->setScene(scene2);
    scene2->addItem(loadedPixmapItem2);

    scene3=new QGraphicsScene();
    loadedPixmapItem3 = new MyGraphicsItem();
    ui->graphicsView_3->setScene(scene3);
    scene3->addItem(loadedPixmapItem3);

    ui->tableWidget_2->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableWidget_2->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableWidget_2->verticalHeader()->setVisible(false);
    ui->tableWidget_2->setColumnWidth(0, 90);
    //
    // connect
    //
    connect(ui->searchBT,SIGNAL(clicked()),this,SLOT(slotSearchData()));
    connect(ui->clearBT,SIGNAL(clicked()),this,SLOT(slotClearData()));
    connect(ui->tableWidget,SIGNAL(itemDoubleClicked(QTableWidgetItem *)), this, SLOT(slotDisplayDefect(QTableWidgetItem*)));
    connect(ui->tableWidget_2,SIGNAL(itemDoubleClicked(QTableWidgetItem *)), this, SLOT(slotDisplayImage(QTableWidgetItem*)));
    DataAnalysis::InitTable();
    DataAnalysis::InitGlassTypeCB();
    ui->tabWidget->setCurrentIndex(0);
}

DataAnalysis::~DataAnalysis()
{
    delete ui;
}

void DataAnalysis::slotSearchData()
{
    // 玻璃id不为空，则后面不用看
    std::vector<GlassDataBaseInfo2> datas;
    if(!ui->glassIDLE->text().isEmpty()){
        QString tableid = ui->glassIDLE->text();
        QString sql = QString("SELECT * FROM glass_table WHERE tableID = '%1';").arg(tableid);
        databasePtr->queryTableData(datas,sql);
        DataAnalysis::displayInfoToTable(datas);
    } else {
            QString year1 = ui->YearSCB->currentText();
            QString month1 = ui->MonthSCB->currentText();
            QString day1 = ui->DaySCB->currentText();
            QString hour1 = ui->HourSCB->currentText();
            QString minute1 = ui->MinuteSCB->currentText();
            QString starttime = year1 + "-" + month1 + "-" +day1 + " " + hour1 + ":" + minute1 + ":" + QString("00");
            QString year2 = ui->YearECB->currentText();
            QString month2 = ui->MonthECB->currentText();
            QString day2 = ui->DayECB->currentText();
            QString hour2 = ui->HourECB->currentText();
            QString minute2 = ui->MonthECB->currentText();
            QString endtime = year2 + "-" + month2 + "-" +day2 + " " + hour2 + ":" + minute2 + ":" + QString("59");
            QString glasstype = ui->glassTypeCB->currentText();
            QString sql;
            if (glasstype.size() != 0){
                sql = QString("SELECT * FROM glass_table WHERE time >= '%1' AND time <= '%2' AND glassType = '%3';").arg(starttime).arg(endtime).arg(glasstype);
            } else {
                sql = QString("SELECT * FROM glass_table WHERE time >= '%1' AND time <= '%2';").arg(starttime).arg(endtime);
            }

            databasePtr->queryTableData(datas,sql);
            DataAnalysis::displayInfoToTable(datas);

            //查询柱状图数据
            DataAnalysis::StatisticalSearchData(datas, chartdata);
            DataAnalysis::InitChart(chartdata);
    }
}

void DataAnalysis::slotClearData()
{
    ui->glassIDLE->clear();
    ui->tableWidget->clear();
    ui->tableWidget_2->clear();
    DataAnalysis::InitTable();
    DataAnalysis::InitGlassTypeCB();
}

void DataAnalysis::displayInfoToTable(std::vector<GlassDataBaseInfo2>& datas)
{
    qDebug()<<__FUNCTION__<<"datas.size() =" <<datas.size();
    ui->tabWidget->setCurrentIndex(0);
    if (datas.size()>0) {
        int row = 0;
        for(int i=0; i<(int)datas.size(); ++i) {
            GlassDataBaseInfo2 info = datas[i];
            ui->tableWidget->insertRow(0);//插入第一行
            //ID
//            QString ID = info.tableID;
//            QTableWidgetItem* id = new QTableWidgetItem(ID);
//            id->setTextAlignment(Qt::AlignCenter);
//            id->setFlags(id->flags() & ~Qt::ItemIsEditable);
//            ui->tableWidget->setItem(row, 0, id);
//            //时间
//            QString datetime = info.time;
//            QTableWidgetItem* time = new QTableWidgetItem(datetime);
//            time->setTextAlignment(Qt::AlignCenter);
//            time->setFlags(time->flags() & ~Qt::ItemIsEditable);
//            ui->tableWidget->setItem(row, 1, time);
//            //玻璃ID
//            QString glassID = QString::number(info.glassID);
//            QTableWidgetItem* glassid = new QTableWidgetItem(glassID);
//            glassid->setTextAlignment(Qt::AlignCenter);
//            glassid->setFlags(glassid->flags() & ~Qt::ItemIsEditable);
//            ui->tableWidget->setItem(row, 2, glassid);
//            //玻璃类型
//            QString glasstype = info.glassType;
//            QTableWidgetItem* type = new QTableWidgetItem(glasstype);
//            type->setTextAlignment(Qt::AlignCenter);
//            type->setFlags(type->flags() & ~Qt::ItemIsEditable);
//            ui->tableWidget->setItem(row, 3, type);
//            //玻璃厚度
//            QString glassthickness = info.glassThickness;
//            QTableWidgetItem* thickness = new QTableWidgetItem(glassthickness);
//            thickness->setTextAlignment(Qt::AlignCenter);
//            thickness->setFlags(thickness->flags() & ~Qt::ItemIsEditable);
//            ui->tableWidget->setItem(row, 4, thickness);
//            //OK/NG
//            QString glassisOK = info.OKorNG;
//            QTableWidgetItem* isok = new QTableWidgetItem(glassisOK);
//            if (info.OKorNG != "OK")
//                isok->setForeground(QColor(255, 0, 0));
//            isok->setTextAlignment(Qt::AlignCenter);
//            isok->setFlags(isok->flags() & ~Qt::ItemIsEditable);
//            ui->tableWidget->setItem(row, 5, isok);
//            //尺寸OK/NG
//            QString glassisSizeOK = info.sizeOKorNG;
//            QTableWidgetItem* issizeok = new QTableWidgetItem(glassisSizeOK);
//            if (info.sizeOKorNG != "OK")
//                issizeok->setForeground(QColor(255, 0, 0));
//            issizeok->setTextAlignment(Qt::AlignCenter);
//            issizeok->setFlags(issizeok->flags() & ~Qt::ItemIsEditable);
//            ui->tableWidget->setItem(row, 6, issizeok);

//            //长度
//            QString glasslength = QString::number(info.length);
//            QTableWidgetItem* length = new QTableWidgetItem(glasslength);
//            length->setTextAlignment(Qt::AlignCenter);
//            length->setFlags(length->flags() & ~Qt::ItemIsEditable);
//            ui->tableWidget->setItem(row, 7, length);
//            //宽度
//            QString glasswidth = QString::number(info.width);
//            QTableWidgetItem* width = new QTableWidgetItem(glasswidth);
//            width->setTextAlignment(Qt::AlignCenter);
//            width->setFlags(width->flags() & ~Qt::ItemIsEditable);
//            ui->tableWidget->setItem(row, 8, width);
//            //对角线1
//            QString glassdiagonal1 = QString::number(info.duijiaoxian1);
//            QTableWidgetItem* diagonal1 = new QTableWidgetItem(glassdiagonal1);
//            diagonal1->setTextAlignment(Qt::AlignCenter);
//            diagonal1->setFlags(diagonal1->flags() & ~Qt::ItemIsEditable);
//            ui->tableWidget->setItem(row, 9, diagonal1);
//            //对角线2
//            QString glassdiagonal2 = QString::number(info.duijiaoxian2);
//            QTableWidgetItem* diagonal2 = new QTableWidgetItem(glassdiagonal2);
//            diagonal2->setTextAlignment(Qt::AlignCenter);
//            diagonal2->setFlags(diagonal2->flags() & ~Qt::ItemIsEditable);
//            ui->tableWidget->setItem(row, 10, diagonal2);
//            //缺陷数量
//            QString glassFlawCount = QString::number(info.defectNumber);
//            QTableWidgetItem* flawcount = new QTableWidgetItem(glassFlawCount);
//            flawcount->setTextAlignment(Qt::AlignCenter);
//            flawcount->setFlags(flawcount->flags() & ~Qt::ItemIsEditable);
//            ui->tableWidget->setItem(row, 11, flawcount);
//            //缺陷OK/NG
//            QString glassisFlawOK = info.defectOKorNG;
//            QTableWidgetItem* isflawok = new QTableWidgetItem(glassisFlawOK);
//            if (glassisFlawOK != "OK")
//                isflawok->setForeground(QColor(255, 0, 0));
//            isflawok->setTextAlignment(Qt::AlignCenter);
//            isflawok->setFlags(isflawok->flags() & ~Qt::ItemIsEditable);
//            ui->tableWidget->setItem(row, 12, isflawok);
//            //崩边
//            QString glassFlaw1 = QString::number(info.benbianNumber);
//            QTableWidgetItem* flaw1 = new QTableWidgetItem(glassFlaw1);
//            flaw1->setTextAlignment(Qt::AlignCenter);
//            flaw1->setFlags(flaw1->flags() & ~Qt::ItemIsEditable);
//            ui->tableWidget->setItem(row, 13, flaw1);
//            //裂纹
//            QString glassFlaw2 = QString::number(info.liewenNumber);
//            QTableWidgetItem* flaw2 = new QTableWidgetItem(glassFlaw2);
//            flaw2->setTextAlignment(Qt::AlignCenter);
//            flaw2->setFlags(flaw2->flags() & ~Qt::ItemIsEditable);
//            ui->tableWidget->setItem(row, 14, flaw2);
//            //划伤
//            QString glassFlaw3 = QString::number(info.huashanNumber);
//            QTableWidgetItem* flaw3 = new QTableWidgetItem(glassFlaw3);
//            flaw3->setTextAlignment(Qt::AlignCenter);
//            flaw3->setFlags(flaw3->flags() & ~Qt::ItemIsEditable);
//            ui->tableWidget->setItem(row, 15, flaw3);
//            //气泡
//            QString glassFlaw4 = QString::number(info.qipaoNumber);
//            QTableWidgetItem* flaw4 = new QTableWidgetItem(glassFlaw4);
//            flaw4->setTextAlignment(Qt::AlignCenter);
//            flaw4->setFlags(flaw4->flags() & ~Qt::ItemIsEditable);
//            ui->tableWidget->setItem(row, 16, flaw4);
//            //结石
//            QString glassFlaw5 = QString::number(info.jieshiNumber);
//            QTableWidgetItem* flaw5 = new QTableWidgetItem(glassFlaw5);
//            flaw5->setTextAlignment(Qt::AlignCenter);
//            flaw5->setFlags(flaw5->flags() & ~Qt::ItemIsEditable);
//            ui->tableWidget->setItem(row, 17, flaw5);
//            //玻璃碎屑
//            QString glassFlaw6 = QString::number(info.bolisuixieNumber);
//            QTableWidgetItem* flaw6 = new QTableWidgetItem(glassFlaw6);
//            flaw6->setTextAlignment(Qt::AlignCenter);
//            flaw6->setFlags(flaw6->flags() & ~Qt::ItemIsEditable);
//            ui->tableWidget->setItem(row, 18, flaw6);
//            //黑点
//            QString glassFlaw7 = QString::number(info.heidianNumber);
//            QTableWidgetItem* flaw7 = new QTableWidgetItem(glassFlaw7);
//            flaw7->setTextAlignment(Qt::AlignCenter);
//            flaw7->setFlags(flaw7->flags() & ~Qt::ItemIsEditable);
//            ui->tableWidget->setItem(row, 19, flaw7);
//            //膜不良
//            QString glassFlaw8 = QString::number(info.mobuliangNumber);
//            QTableWidgetItem* flaw8 = new QTableWidgetItem(glassFlaw8);
//            flaw8->setTextAlignment(Qt::AlignCenter);
//            flaw8->setFlags(flaw8->flags() & ~Qt::ItemIsEditable);
//            ui->tableWidget->setItem(row, 20, flaw8);
//            //印记
//            QString glassFlaw9 = QString::number(info.yinjiNumber);
//            QTableWidgetItem* flaw9 = new QTableWidgetItem(glassFlaw9);
//            flaw9->setTextAlignment(Qt::AlignCenter);
//            flaw9->setFlags(flaw9->flags() & ~Qt::ItemIsEditable);
//            ui->tableWidget->setItem(row, 21, flaw9);
//            //脏污
//            QString glassFlaw10 = QString::number(info.zanwuNumber);
//            QTableWidgetItem* flaw10 = new QTableWidgetItem(glassFlaw10);
//            flaw10->setTextAlignment(Qt::AlignCenter);
//            flaw10->setFlags(flaw10->flags() & ~Qt::ItemIsEditable);
//            ui->tableWidget->setItem(row, 22, flaw10);
//            //毛絮
//            QString glassFlaw11 = QString::number(info.maoxuNumber);
//            QTableWidgetItem* flaw11 = new QTableWidgetItem(glassFlaw11);
//            flaw11->setTextAlignment(Qt::AlignCenter);
//            flaw11->setFlags(flaw11->flags() & ~Qt::ItemIsEditable);
//            ui->tableWidget->setItem(row, 23, flaw11);
//            //水滴
//            QString glassFlaw12 = QString::number(info.shuidiNumber);
//            QTableWidgetItem* flaw12 = new QTableWidgetItem(glassFlaw12);
//            flaw12->setTextAlignment(Qt::AlignCenter);
//            flaw12->setFlags(flaw12->flags() & ~Qt::ItemIsEditable);
//            ui->tableWidget->setItem(row, 24, flaw12);
//            // 设置表格内容居中显示
//            for (int i = 0; i < ui->tableWidget->columnCount(); ++i) {
//                ui->tableWidget->horizontalHeaderItem(i)->setTextAlignment(Qt::AlignCenter);
//            }
//            ui->tableWidget->verticalHeader()->setVisible(false); // 隐藏行
        }
    }
}


void DataAnalysis::InitTable()
{
    // 设置表头
    QStringList headerLabels = {tr("ID"),tr("time"),tr("glassID"),tr("glasstype"),tr("glassThc"),tr("OK/NG"),tr("sizeOK/NG"),tr("length"),tr("width"),tr("duijiaoxian1"),tr("duijaioxian2"),
                               tr("defectnumber"),tr("defectOK/NG"),tr("benbian"),tr("liewen"),tr("huashan"),tr("qipao"),tr("jieshi"),tr("bolisuixie"),tr("heidian"),tr("mobuliang"),tr("zanwu"),
                                tr("yinji"),tr("maoxu"),tr("shuidi")};
    //{"ID","时间","玻璃ID","玻璃类型","玻璃厚度","OK/NG","尺寸OK/NG","长度","宽度","对角线1","对角线2",
    //"缺陷数量","缺陷OK/NG","崩边","裂纹","划伤","气泡","结石","玻璃碎屑","黑点","膜不良","脏污","印记","毛絮","水滴"}
    ui->tableWidget->setColumnCount(headerLabels.size());
    ui->tableWidget->setHorizontalHeaderLabels(headerLabels);
    ui->tableWidget->setColumnWidth(0, 70);
    ui->tableWidget->setColumnWidth(1, 160);
    ui->tableWidget->setColumnWidth(2, 70);
    ui->tableWidget->setColumnWidth(3, 70);
    ui->tableWidget->setColumnWidth(4, 70);
    ui->tableWidget->setColumnWidth(5, 70);
    ui->tableWidget->setColumnWidth(6, 80);
    ui->tableWidget->setColumnWidth(7, 70);
    ui->tableWidget->setColumnWidth(8, 70);
    ui->tableWidget->setColumnWidth(9, 70);
    ui->tableWidget->setColumnWidth(10, 70);
    ui->tableWidget->setColumnWidth(11, 70);
    ui->tableWidget->setColumnWidth(12, 80);
    ui->tableWidget->setColumnWidth(13, 70);
    ui->tableWidget->setColumnWidth(14, 70);
    ui->tableWidget->setColumnWidth(15, 70);
    ui->tableWidget->setColumnWidth(16, 70);
    ui->tableWidget->setColumnWidth(17, 70);
    ui->tableWidget->setColumnWidth(18, 70);
    ui->tableWidget->setColumnWidth(19, 70);
    ui->tableWidget->setColumnWidth(20, 70);
    ui->tableWidget->setColumnWidth(21, 70);
    ui->tableWidget->setColumnWidth(22, 70);
    ui->tableWidget->setColumnWidth(23, 70);
    ui->tableWidget->setColumnWidth(24, 70);
    //
    // 缺陷表格初始化
    //
    QStringList headerLabel = {tr("ID"),tr("DefectID"),tr("Time"),tr("DefectName"),tr("DetectLeve"),tr("X"),tr("Y"),tr("Lenth"),tr("Width"),tr("Area")};
    ui->tableWidget_2->setColumnCount(headerLabel.size());
    ui->tableWidget_2->setHorizontalHeaderLabels(headerLabel);
    ui->tableWidget_2->setColumnWidth(0, 70);
    ui->tableWidget_2->setColumnWidth(1, 70);
    ui->tableWidget_2->setColumnWidth(2, 160);
    ui->tableWidget_2->setColumnWidth(3, 70);
    ui->tableWidget_2->setColumnWidth(4, 70);
    ui->tableWidget_2->setColumnWidth(5, 70);
    ui->tableWidget_2->setColumnWidth(6, 80);
    ui->tableWidget_2->setColumnWidth(7, 70);
    ui->tableWidget_2->setColumnWidth(8, 70);
    ui->tableWidget_2->setColumnWidth(9, 70);
}

void DataAnalysis::slotDisplayDefect(QTableWidgetItem* item)
{
    // 获取所在行的第一列内容
    if(item != NULL) {
        QString ColumnContent = ui->tableWidget->item(item->row(), 2)->text();
        ui->glassidLB->setText(ColumnContent);
        qDebug()<<__FUNCTION__<<"ColumnContent =" <<ColumnContent;
        currentGlassID = ColumnContent.toInt();
        QString sql = QString("SELECT * FROM glass_defect WHERE glassid = %1;").arg(ColumnContent);
        std::vector<GlassDefect2> datas;
        databasePtr->queryTableData(datas,sql);
        qDebug()<<"datas.size() ="<<datas.size();

        if (datas.size() != 0) {
            ui->tabWidget->setCurrentIndex(1);
            ui->tableWidget_2->setRowCount(datas.size());
            for(int i=0; i<(int)datas.size(); ++i){
                GlassDefect2 data = datas[i];
                //ID
                QTableWidgetItem* item00 = new QTableWidgetItem(QString::number(data.id));
                item00->setTextAlignment(Qt::AlignCenter);
                item00->setFlags(item00->flags() & ~Qt::ItemIsEditable);
                ui->tableWidget_2->setItem(i , 0, item00);
                //序号
                QTableWidgetItem* item0 = new QTableWidgetItem(QString::number(data.defectId));
                item0->setTextAlignment(Qt::AlignCenter);
                item0->setFlags(item0->flags() & ~Qt::ItemIsEditable);
                ui->tableWidget_2->setItem(i , 1, item0);
                //时间
                QTableWidgetItem* item1 = new QTableWidgetItem(data.time);
                item1->setTextAlignment(Qt::AlignCenter);
                item1->setFlags(item1->flags() & ~Qt::ItemIsEditable);
                ui->tableWidget_2->setItem(i , 2, item1);
                //类型
                QTableWidgetItem* item2 = new QTableWidgetItem(data.defectType);
                item2->setTextAlignment(Qt::AlignCenter);
                item2->setFlags(item2->flags() & ~Qt::ItemIsEditable);
                ui->tableWidget_2->setItem(i , 3, item2);
                //等级
                QTableWidgetItem* item3 = new QTableWidgetItem(data.defectLevel);
                item3->setTextAlignment(Qt::AlignCenter);
                item3->setFlags(item3->flags() & ~Qt::ItemIsEditable);
                ui->tableWidget_2->setItem(i, 4, item3);
                //坐标X
                QTableWidgetItem* item4 = new QTableWidgetItem(QString::number(data.x));
                item4->setTextAlignment(Qt::AlignCenter);
                item4->setFlags(item4->flags() & ~Qt::ItemIsEditable);
                ui->tableWidget_2->setItem(i, 5, item4);
                //坐标Y
                QTableWidgetItem* item5 = new QTableWidgetItem(QString::number(data.y));
                item5->setTextAlignment(Qt::AlignCenter);
                item5->setFlags(item5->flags() & ~Qt::ItemIsEditable);
                ui->tableWidget_2->setItem(i , 6, item5);
                //长
                QTableWidgetItem* item6 = new QTableWidgetItem(QString::number(data.length));
                item6->setTextAlignment(Qt::AlignCenter);
                item6->setFlags(item6->flags() & ~Qt::ItemIsEditable);
                ui->tableWidget_2->setItem(i, 7, item6);
                //宽
                QTableWidgetItem* item7 = new QTableWidgetItem(QString::number(data.width));
                item7->setTextAlignment(Qt::AlignCenter);
                item7->setFlags(item7->flags() & ~Qt::ItemIsEditable);
                ui->tableWidget_2->setItem(i , 8, item7);
                //区域
                QTableWidgetItem* item8 = new QTableWidgetItem(QString::number(data.area));
                item8->setTextAlignment(Qt::AlignCenter);
                item8->setFlags(item8->flags() & ~Qt::ItemIsEditable);
                ui->tableWidget_2->setItem(i, 9, item8);
                ui->tableWidget_2->verticalHeader()->setVisible(false); // 隐藏行
                //显示图片
                if(i ==0){
                    QString ImagePath = data.imagePath;//D:/SaveDefectImage/2024-09-04/边Ok/11-31-53-1
                    qDebug() << "imagepath = " << ImagePath;
                    QImage img1=QImage(ImagePath+"/1.jpg");
                    QImage img2=QImage(ImagePath+"/2.jpg");
                    QImage img3=QImage(ImagePath+"/3.jpg");
                    if(!img1.isNull()) {
                        loadedPixmapItem->loadImage(img1);
                        int nwidth = ui->graphicsView->width(), nheight = ui->graphicsView->height();
                        loadedPixmapItem->setQGraphicsViewWH(nwidth, nheight);
                        ui->graphicsView->setSceneRect((QRectF(-(nwidth / 2), -(nheight / 2), nwidth, nheight)));
                    }
                    if(!img2.isNull()){
                        loadedPixmapItem2->loadImage(img2);
                        int nwidth2 = ui->graphicsView_2->width(), nheight2 = ui->graphicsView_2->height();
                        loadedPixmapItem2->setQGraphicsViewWH(nwidth2, nheight2);
                        ui->graphicsView_2->setSceneRect((QRectF(-(nwidth2 / 2), -(nheight2 / 2), nwidth2, nheight2)));
                    }
                    if(!img3.isNull()){
                        loadedPixmapItem3->loadImage(img3);
                        int nwidth3 = ui->graphicsView_3->width(), nheight3 = ui->graphicsView_3->height();
                        loadedPixmapItem3->setQGraphicsViewWH(nwidth3, nheight3);
                        ui->graphicsView_3->setSceneRect((QRectF(-(nwidth3 / 2), -(nheight3 / 2), nwidth3, nheight3)));
                    }
                }
            }
        }
    } else {
        qDebug()<<"item == NULL";
    }

}

void DataAnalysis::slotDisplayImage(QTableWidgetItem* item)
{
    if(item != NULL) {
        QString ColumnContent = ui->tableWidget_2->item(item->row(), 0)->text();
        qDebug()<<__FUNCTION__<<"ColumnContent =" <<ColumnContent;
        QString sql= QString("SELECT * FROM glass_defect WHERE id = %1;").arg(ColumnContent.toInt());
        std::vector<GlassDefect2> datas;
        databasePtr->queryTableData(datas,sql);
        if(datas.size()>0){
            QString ImagePath = datas[0].imagePath;//D:/SaveDefectImage/2024-09-04/边Ok/11-31-53-1
            qDebug() << "imagepath = " << ImagePath;
            QImage img1=QImage(ImagePath+"/1.jpg");
            QImage img2=QImage(ImagePath+"/2.jpg");
            QImage img3=QImage(ImagePath+"/3.jpg");
            if(!img1.isNull()) {
                loadedPixmapItem->loadImage(img1);
                int nwidth = ui->graphicsView->width(), nheight = ui->graphicsView->height();
                loadedPixmapItem->setQGraphicsViewWH(nwidth, nheight);
                ui->graphicsView->setSceneRect((QRectF(-(nwidth / 2), -(nheight / 2), nwidth, nheight)));
            }
            if(!img2.isNull()){
                loadedPixmapItem2->loadImage(img2);
                int nwidth2 = ui->graphicsView_2->width(), nheight2 = ui->graphicsView_2->height();
                loadedPixmapItem2->setQGraphicsViewWH(nwidth2, nheight2);
                ui->graphicsView_2->setSceneRect((QRectF(-(nwidth2 / 2), -(nheight2 / 2), nwidth2, nheight2)));
            }
            if(!img3.isNull()){
                loadedPixmapItem3->loadImage(img3);
                int nwidth3 = ui->graphicsView_3->width(), nheight3 = ui->graphicsView_3->height();
                loadedPixmapItem3->setQGraphicsViewWH(nwidth3, nheight3);
                ui->graphicsView_3->setSceneRect((QRectF(-(nwidth3 / 2), -(nheight3 / 2), nwidth3, nheight3)));
            }
        }
    }
}

void DataAnalysis::InitChart(chartParam chartdata)
{
    QChart* chart = new QChart;
    chart->legend()->setVisible(false);
    QString totalstr = "(" + tr("search glass total") + QString(" =") + QString::number(chartdata.totalglass) + QString(")");
    chart->setTitle(tr("Defect statistics chart") + totalstr);
    QChartView* chartView = new QChartView(this);
    chartView->setRenderHint(QPainter::Antialiasing);
    chartView->setChart(chart);
    //加入到界面中
    QVBoxLayout* layout = new QVBoxLayout;
    layout->addWidget(chartView);
    ui->tab_3->setLayout(layout);
    //设置X轴
    QBarCategoryAxis* category_axis_x = new QBarCategoryAxis(chart);
    chart->addAxis(category_axis_x, Qt::AlignBottom);
    QStringList categories = { tr("benbian"), tr("liewen"), tr("huashan"), tr("qipao"),
                               tr("jieshi"), tr("bolisuixie"), tr("heidian"), tr("mobuliang"),
                               tr("zangwu"), tr("yingji"), tr("maoxu"), tr("shuidi")};
    category_axis_x->setCategories(categories);
    category_axis_x->setTitleText(tr("defect"));

    //设置Y轴
    QValueAxis* axis_y = new QValueAxis(chart);
    chart->addAxis(axis_y, Qt::AlignLeft);

    //创建柱状图
    QBarSeries* bar_series = new QBarSeries(chart);
    chart->addSeries(bar_series);

    bar_series->attachAxis(category_axis_x);
    bar_series->attachAxis(axis_y);

    //创建1组柱状图
    QBarSet* set = new QBarSet("", chart);
    bar_series->append(set);
    //设置数据
    QList<qreal> list_data = {(double)chartdata.benbianGlassCount,
                              (double)chartdata.liewenGlassCount,
                              (double)chartdata.huashanGlassCount,
                              (double)chartdata.qipaoGlassCount,
                              (double)chartdata.jieshiGlassCount,
                              (double)chartdata.bolisuixieGlassCount,
                              (double)chartdata.heidianGlassCount,
                              (double)chartdata.mobuliangGlassCount,
                              (double)chartdata.zanwuGlassCount,
                              (double)chartdata.yinjiGlassCount,
                              (double)chartdata.maoxuGlassCount,
                              (double)chartdata.shuidiGlassCount};
    set->append(list_data);
    // 求最大显示值
    int maxValue = 0;
    if (list_data.size() > 0) {
        maxValue = list_data.at(0);
        for (int value : list_data) {
            if (value > maxValue) {
                maxValue = value;
            }
        }
    }
    axis_y->setRange(0, maxValue);//设置显示范围
    axis_y->setTickCount(maxValue-1);//设置Y轴刻度数
    axis_y->setTitleText(tr("glass no"));
}

void DataAnalysis::StatisticalSearchData(std::vector<GlassDataBaseInfo2> datas, chartParam& chartdata)
{
    chartdata.totalglass = datas.size();
    if(datas.size() > 0) {
        for(int i =0 ; i< (int)datas.size(); ++i) {
//              GlassDataBaseInfo2 info = datas[i];
//              if (info.benbianNumber > 0) {
//                  chartdata.benbianGlassCount = chartdata.benbianGlassCount + 1;
//              }
//              if(info.liewenNumber > 0) {
//                  chartdata.liewenGlassCount = chartdata.liewenGlassCount + 1;
//              }
//              if(info.huashanNumber > 0) {
//                  chartdata.huashanGlassCount = chartdata.huashanGlassCount + 1;
//              }
//              if(info.qipaoNumber > 0) {
//                  chartdata.qipaoGlassCount = chartdata.qipaoGlassCount + 1;
//              }
//              if(info.jieshiNumber > 0) {
//                  chartdata.jieshiGlassCount = chartdata.jieshiGlassCount + 1;
//              }
//              if(info.bolisuixieNumber > 0) {
//                  chartdata.bolisuixieGlassCount = chartdata.bolisuixieGlassCount + 1;
//              }
//              if(info.heidianNumber > 0) {
//                  chartdata.heidianGlassCount = chartdata.heidianGlassCount + 1;
//              }
//              if(info.mobuliangNumber > 0) {
//                  chartdata.mobuliangGlassCount = chartdata.mobuliangGlassCount + 1;
//              }
//              if(info.zanwuNumber > 0) {
//                  chartdata.zanwuGlassCount = chartdata.zanwuGlassCount + 1;
//              }
//              if(info.yinjiNumber > 0) {
//                  chartdata.yinjiGlassCount = chartdata.yinjiGlassCount + 1;
//              }
//              if(info.maoxuNumber > 0) {
//                  chartdata.maoxuGlassCount = chartdata.maoxuGlassCount + 1;
//              }
//              if(info.shuidiNumber > 0) {
//                  chartdata.shuidiGlassCount = chartdata.shuidiGlassCount + 1;
//              }
        }
    }
}

void DataAnalysis::InitGlassTypeCB()
{
    //
    // 将系统工单的所有文件名字作为玻璃类型
    //
    ui->glassTypeCB->clear();
    QString recipePath = QDir::currentPath() + "/Recipes";
    qDebug()<<"recipePath = " <<recipePath;
    QDir dir(recipePath);
    QFileInfoList fileList = dir.entryInfoList(QStringList() << "*.json");
    if (fileList.size() > 0) {
        for(auto fileInfo:fileList) {
           ui->glassTypeCB->addItem(fileInfo.baseName());
        }
    }
}
