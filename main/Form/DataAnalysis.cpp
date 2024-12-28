/********************************************************************************
 *  Puspose:
 *      DataAnalysis.cpp 数据分析界面源文件
 *
 * Author:
 *      zhang shuanggui
 *
 * create time:
 *      2025/11/25
 *
 *******************************************************************************/
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
#include "../Global.h"


DataAnalysis::DataAnalysis(QWidget *parent) :
    QWidget(parent)
    , ui(new Ui::DataAnalysis)
{
    ui->setupUi(this);

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
        QString sql = QString("SELECT * FROM glass_table WHERE id = '%1';").arg(tableid);
        if (PARAM.databasePtr != nullptr)
            PARAM.databasePtr->queryTableData(datas,sql);
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
            QString sql;
            sql = QString("SELECT * FROM glass_table WHERE time >= '%1' AND time <= '%2';").arg(starttime).arg(endtime);

            if (PARAM.databasePtr != nullptr)
                PARAM.databasePtr->queryTableData(datas,sql);
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
}

void DataAnalysis::displayInfoToTable(std::vector<GlassDataBaseInfo2>& datas)
{
    qDebug()<<__FUNCTION__<<"datas.size() =" <<datas.size();
    ui->tabWidget->setCurrentIndex(0);
    for (int i=0; i<(int)datas.size();++i ) {
        GlassDataBaseInfo2 data = datas[i];
        try{
            QTableWidgetItem *itemID = ui->tableWidget->item(0, 0);
            //
            // 同一块玻璃的数据插入到表格的同一行，新玻璃插入到第一行
            //
            qDebug()<<"data.id ="<<data.id;
            if (itemID != NULL) {
                if(itemID->text().toInt() != data.id){
                    ui->tableWidget->insertRow(0);
                }
            } else {
                ui->tableWidget->insertRow(0);
            }
            // NG背景颜色为红色，OK背景颜色为绿色
            QBrush brush = Qt::white;
            if (data.OKorNG != "OK") { //OK/NG
                brush = Qt::red;
            } else {
                brush = Qt::green;
            }
            DataAnalysis::setTableWidgetItem(0,0,QString::number(data.id),ui->tableWidget,brush);//ID
            DataAnalysis::setTableWidgetItem(0,1,data.time,ui->tableWidget,brush);//时间
            DataAnalysis::setTableWidgetItem(0,2,data.OKorNG,ui->tableWidget,brush);//OK/NG
            DataAnalysis::setTableWidgetItem(0,3,data.sizeOKorNG,ui->tableWidget,brush);//尺寸OK/NG
            DataAnalysis::setTableWidgetItem(0,4,QString::number(data.length,'f', 2),ui->tableWidget,brush);//长度
            DataAnalysis::setTableWidgetItem(0,5,QString::number(data.width,'f', 2),ui->tableWidget,brush);//宽度
            DataAnalysis::setTableWidgetItem(0,6,data.defectOKorNG,ui->tableWidget,brush);//缺陷OK/NG
            DataAnalysis::setTableWidgetItem(0,7,QString::number(data.defectNumber),ui->tableWidget,brush);//缺陷数量
            DataAnalysis::setTableWidgetItem(0,8,QString::number(data.huahenNumber),ui->tableWidget,brush);//划痕
            DataAnalysis::setTableWidgetItem(0,9,QString::number(data.yiwuNumber),ui->tableWidget,brush);//异物
            DataAnalysis::setTableWidgetItem(0,10,QString::number(data.qipaoNumber),ui->tableWidget,brush);//气泡
            DataAnalysis::setTableWidgetItem(0,11,QString::number(data.madianNumber),ui->tableWidget,brush);//麻点
            DataAnalysis::setTableWidgetItem(0,12,QString::number(data.shuiyinNumber),ui->tableWidget,brush);//水印
            DataAnalysis::setTableWidgetItem(0,13,QString::number(data.youmobuliangNumber),ui->tableWidget,brush);//油墨不良
            DataAnalysis::setTableWidgetItem(0,14,QString::number(data.juchibianNumber),ui->tableWidget,brush);//锯齿边
            DataAnalysis::setTableWidgetItem(0,15,QString::number(data.siyinquexianNumber),ui->tableWidget,brush);// 丝印缺陷
            DataAnalysis::setTableWidgetItem(0,16,QString::number(data.guahuaNumber),ui->tableWidget,brush);// 刮花
            DataAnalysis::setTableWidgetItem(0,17,QString::number(data.liewenNumber),ui->tableWidget,brush);// 裂纹
            DataAnalysis::setTableWidgetItem(0,18,QString::number(data.benbianjiaoNumber),ui->tableWidget,brush);// 崩边角
            // 设置表格内容居中显示
            for (int i = 0; i < ui->tableWidget->columnCount(); ++i) {
                ui->tableWidget->horizontalHeaderItem(i)->setTextAlignment(Qt::AlignCenter);
            }
            ui->tableWidget->verticalHeader()->setVisible(false); // 隐藏行号
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
}


void DataAnalysis::InitTable()
{
    // 设置表头
    QStringList headerLabels = {tr("ID"),tr("时间"),tr("OK/NG"),tr("尺寸OK/NG"),tr("长度"),tr("宽度"),tr("缺陷OK/NG"),tr("缺陷数量"),tr("划痕"),tr("异物"),tr("气泡"),
                               tr("麻点"),tr("水印"),tr("油墨不良"),tr("锯齿边"),tr("丝印缺陷"),tr("刮花"),tr("裂纹"),tr("崩边角")};
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
        QString ColumnContent = ui->tableWidget->item(item->row(), 0)->text();
        ui->glassidLB->setText(ColumnContent);
        currentGlassID = ColumnContent.toInt();
        QString sql = QString("SELECT * FROM glass_defect WHERE glassid = %1;").arg(ColumnContent);
        std::vector<GlassDefect2> datas;
        if (PARAM.databasePtr != nullptr)
            PARAM.databasePtr->queryTableData(datas,sql);

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
                    QString ImagePath1 = data.imagePath0;
                    QString ImagePath2 = data.imagePath1;
                    QString ImagePath3 = data.imagePath2;
                    qDebug() << "imagepath1 = " << ImagePath1;
                    QImage img1=QImage(ImagePath1);
                    QImage img2=QImage(ImagePath2);
                    QImage img3=QImage(ImagePath3);
                    if(!img1.isNull()) {
                        loadedPixmapItem->loadImage(img1);
                        int nwidth = ui->graphicsView->width(), nheight = ui->graphicsView->height();
                        loadedPixmapItem->setQGraphicsViewWH(nwidth, nheight);
                        ui->graphicsView->setSceneRect((QRectF(-(nwidth / 2), -(nheight / 2), nwidth, nheight)));
                    } else {
                        qDebug() << "img1图像("<<ImagePath1<<")无法加载，可能文件不存在。";
                    }
                    if(!img2.isNull()){
                        loadedPixmapItem2->loadImage(img2);
                        int nwidth2 = ui->graphicsView_2->width(), nheight2 = ui->graphicsView_2->height();
                        loadedPixmapItem2->setQGraphicsViewWH(nwidth2, nheight2);
                        ui->graphicsView_2->setSceneRect((QRectF(-(nwidth2 / 2), -(nheight2 / 2), nwidth2, nheight2)));
                    } else {
                        qDebug() << "img2图像("<<ImagePath2<<")无法加载，可能文件不存在。";
                    }
                    if(!img3.isNull()){
                        loadedPixmapItem3->loadImage(img3);
                        int nwidth3 = ui->graphicsView_3->width(), nheight3 = ui->graphicsView_3->height();
                        loadedPixmapItem3->setQGraphicsViewWH(nwidth3, nheight3);
                        ui->graphicsView_3->setSceneRect((QRectF(-(nwidth3 / 2), -(nheight3 / 2), nwidth3, nheight3)));
                    } else {
                        qDebug() << "img3图像("<<ImagePath3<<")无法加载，可能文件不存在。";
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
        if (PARAM.databasePtr != nullptr)
            PARAM.databasePtr->queryTableData(datas,sql);
        if(datas.size()>0){
            QString ImagePath1 = datas[0].imagePath0;
            QString ImagePath2 = datas[0].imagePath1;
            QString ImagePath3 = datas[0].imagePath2;
            qDebug() << "imagepath = " << ImagePath1;
            QImage img1=QImage(ImagePath1);
            QImage img2=QImage(ImagePath2);
            QImage img3=QImage(ImagePath3);
            if(!img1.isNull()) {
                loadedPixmapItem->loadImage(img1);
                int nwidth = ui->graphicsView->width(), nheight = ui->graphicsView->height();
                loadedPixmapItem->setQGraphicsViewWH(nwidth, nheight);
                ui->graphicsView->setSceneRect((QRectF(-(nwidth / 2), -(nheight / 2), nwidth, nheight)));
            } else {
                qDebug() << "img1图像("<<ImagePath1<<")无法加载，可能文件不存在。";
            }
            if(!img2.isNull()){
                loadedPixmapItem2->loadImage(img2);
                int nwidth2 = ui->graphicsView_2->width(), nheight2 = ui->graphicsView_2->height();
                loadedPixmapItem2->setQGraphicsViewWH(nwidth2, nheight2);
                ui->graphicsView_2->setSceneRect((QRectF(-(nwidth2 / 2), -(nheight2 / 2), nwidth2, nheight2)));
            } else {
                qDebug() << "img2图像("<<ImagePath2<<")无法加载，可能文件不存在。";
            }
            if(!img3.isNull()){
                loadedPixmapItem3->loadImage(img3);
                int nwidth3 = ui->graphicsView_3->width(), nheight3 = ui->graphicsView_3->height();
                loadedPixmapItem3->setQGraphicsViewWH(nwidth3, nheight3);
                ui->graphicsView_3->setSceneRect((QRectF(-(nwidth3 / 2), -(nheight3 / 2), nwidth3, nheight3)));
            } else {
                qDebug() << "img3图像("<<ImagePath3<<")无法加载，可能文件不存在。";
            }
        }
    }
}

void DataAnalysis::InitChart(chartParam chartdata)
{
    QChart* chart = new QChart;
    chart->legend()->setVisible(false);
    QString totalstr = "(" + tr("查询玻璃总数") + QString(" =") + QString::number(chartdata.totalglass) + QString(")");
    chart->setTitle(tr("缺陷统计图标") + totalstr);
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
    QStringList categories = { tr("划痕"), tr("异物"), tr("气泡"), tr("麻点"),
                               tr("水印"), tr("油墨不良"), tr("锯齿边"), tr("丝印缺陷"),
                               tr("刮花"), tr("裂纹"), tr("崩边角")};
    category_axis_x->setCategories(categories);
    category_axis_x->setTitleText(tr("缺陷"));

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
    QList<qreal> list_data = {(double)chartdata.huahengGlassCount,
                              (double)chartdata.yiwuGlassCount,
                              (double)chartdata.qipaoGlassCount,
                              (double)chartdata.madianGlassCount,
                              (double)chartdata.shuiyinGlassCount,
                              (double)chartdata.youmobuliangGlassCount,
                              (double)chartdata.juchibianGlassCount,
                              (double)chartdata.siyinquexianGlassCount,
                              (double)chartdata.guahuaGlassCount,
                              (double)chartdata.liewenGlassCount,
                              (double)chartdata.benbianjiaoGlassCount};
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
             GlassDataBaseInfo2 info = datas[i];
             if (info.huahenNumber > 0) {
                chartdata.huahengGlassCount += 1;
             }
             if(info.liewenNumber > 0) {
                 chartdata.liewenGlassCount += 1;
             }
             if(info.yiwuNumber > 0) {
                 chartdata.yiwuGlassCount += 1;
             }
             if(info.qipaoNumber > 0) {
                 chartdata.qipaoGlassCount = chartdata.qipaoGlassCount + 1;
             }
             if(info.madianNumber > 0) {
                 chartdata.madianGlassCount += 1;
             }
             if(info.shuiyinNumber > 0) {
                 chartdata.shuiyinGlassCount += 1;
             }
             if(info.youmobuliangNumber > 0) {
                 chartdata.youmobuliangGlassCount += 1;
             }
             if(info.juchibianNumber > 0) {
                 chartdata.juchibianGlassCount += 1;
             }
             if(info.siyinquexianNumber > 0) {
                 chartdata.siyinquexianGlassCount += 1;
             }
             if(info.guahuaNumber > 0) {
                 chartdata.guahuaGlassCount += 1;
             }
             if(info.benbianjiaoNumber > 0) {
                 chartdata.benbianjiaoGlassCount += 1;
             }
        }
    }
}

void DataAnalysis::setTableWidgetItem(int row,
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

