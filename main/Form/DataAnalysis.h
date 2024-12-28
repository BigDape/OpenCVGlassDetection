/********************************************************************************
 *  Puspose:
 *      DataAnalysis.h 数据分析界面头文件
 *
 * Author:
 *      zhang shuanggui
 *
 * create time:
 *      2025/11/25
 *
 *******************************************************************************/
#ifndef DATAANALYSIS_H
#define DATAANALYSIS_H

#include <QWidget>
#include <QTableWidgetItem>
#include "MyGraphicsitem.h"
#include "HSTool.h"

namespace Ui {
class DataAnalysis;
}

/**
 * @brief The chartParam struct 查询结果数据
 */
struct chartParam{
    int huahengGlassCount = 0;              // 划痕数量
    int yiwuGlassCount = 0;                 // 异物数量
    int qipaoGlassCount = 0;                // 气泡数量
    int madianGlassCount = 0;               // 麻点数量
    int shuiyinGlassCount = 0;              // 水印数量
    int youmobuliangGlassCount = 0;         // 油墨不良碎屑
    int juchibianGlassCount = 0;            // 锯齿边数量
    int siyinquexianGlassCount = 0;         // 丝印缺陷数量
    int guahuaGlassCount = 0;               // 刮花数量
    int liewenGlassCount = 0;               // 裂纹数量
    int benbianjiaoGlassCount = 0;          // 崩边角数量
    int totalglass = 0;  //玻璃总的数量
};



class DataAnalysis : public QWidget
{
    Q_OBJECT

public:
    explicit DataAnalysis(QWidget *parent = nullptr);
    ~DataAnalysis();

    /**
     * @brief displayInfoToTable 数据分析界面显示搜索到的数据
     * @param datas
     */
    void displayInfoToTable(std::vector<GlassDataBaseInfo2>& datas);

    /**
     * @brief InitTable 初始化表格
     */
    void InitTable();

    /**
     * @brief InitChart 初始化饼状图
     * @param chartdata
     */
    void InitChart(chartParam chartdata);

    /**
     * @brief StatisticalSearchData 信息统计表格
     * @param datas 统计信息数据
     * @param chartdata 饼状图数据
     */
    void StatisticalSearchData(std::vector<GlassDataBaseInfo2> datas, chartParam& chartdata);

    /**
     * @brief setTableWidgetItem
     * @param row
     * @param col
     * @param text
     * @param table
     * @param brush
     */
    void setTableWidgetItem(int row,
                            int col,
                            QString text,
                            QTableWidget* table,
                            QBrush brush = Qt::white);

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
};

#endif // DATAANALYSIS_H
