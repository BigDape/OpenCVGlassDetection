#ifndef DATAANALYSIS_H
#define DATAANALYSIS_H

#include <QWidget>
#include <QTableWidgetItem>
#include "MyGraphicsitem.h"
#include "HSTool.h"
#include "HSDatabaseInterface.h"

namespace Ui {
class DataAnalysis;
}

/**
 * @brief The chartParam struct 查询结果数据
 */
struct chartParam{
    int benbianGlassCount;      // 崩边数量
    int liewenGlassCount;       // 裂纹数量
    int huashanGlassCount;      // 划伤数量
    int qipaoGlassCount;        // 气泡数量
    int jieshiGlassCount;       // 结石数量
    int bolisuixieGlassCount;   // 玻璃碎屑
    int heidianGlassCount;      // 黑点数量
    int mobuliangGlassCount;    // 膜不良数量
    int zanwuGlassCount;        // 脏污数量
    int yinjiGlassCount;        // 印记数量
    int maoxuGlassCount;        // 毛絮数量
    int shuidiGlassCount;       // 水滴数量
    int totalglass;             // 总的玻璃数量
    chartParam():benbianGlassCount(0),
                liewenGlassCount(0),
                huashanGlassCount(0),
                qipaoGlassCount(0),
                jieshiGlassCount(0),
                bolisuixieGlassCount(0),
                heidianGlassCount(0),
                mobuliangGlassCount(0),
                zanwuGlassCount(0),
                yinjiGlassCount(0),
                maoxuGlassCount(0),
                shuidiGlassCount(0){}
};

class DataAnalysis : public QWidget
{
    Q_OBJECT

public:
    explicit DataAnalysis(QWidget *parent = nullptr);
    ~DataAnalysis();
    void displayInfoToTable(std::vector<GlassDataBaseInfo2>& datas);
    void InitTable();
    void InitChart(chartParam chartdata);
    void StatisticalSearchData(std::vector<GlassDataBaseInfo2> datas, chartParam& chartdata);
    void InitGlassTypeCB();

public slots:
    void slotSearchData();
    void slotClearData();
    void slotDisplayDefect(QTableWidgetItem* item);
    void slotDisplayImage(QTableWidgetItem* item);

private:
    Ui::DataAnalysis *ui;
    MyGraphicsItem* loadedPixmapItem;
    QGraphicsScene* scene;
    MyGraphicsItem* loadedPixmapItem2;
    QGraphicsScene* scene2;
    MyGraphicsItem* loadedPixmapItem3;
    QGraphicsScene* scene3;
    int currentGlassID;  //当前玻璃ID
    chartParam chartdata;
    HSDatabaseNamespace::HSDatabaseInterface* databasePtr;
};

#endif // DATAANALYSIS_H
