#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QDockWidget>
#include <QMainWindow>
#include <QSettings>
#include <QThread>
#include <QTableWidgetItem>
#include "Global.h"
#include "Form/LightControl.h"
#include "Form/MyGraphicsitem.h"
#include "Form/Calibrate.h"
#include "HSAlgorithmInterface.h"
#include "HSDatabaseInterface.h"
#include "HSCameraInterface.h"
#include "Form/DataAnalysis.h"
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/core.hpp>
#include <atomic>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

enum RUNNINGSTATUS{
    UNKNOWN = 0,
    START,
    MID,
    END,
};


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget* parent = nullptr);
    ~MainWindow();
    void InitComponents();
    /**
     * @brief InitRegisterMetaType 注册信号与槽函数使用到的自定义结构体
     */
    void InitRegisterMetaType();
    /**
     * @brief InitToolBar 初始化工具栏
     */
    void InitToolBar();
    /**
     * @brief InitGlassStaticTableWidget 初始化数据统计界面
     */
    void InitGlassStaticTableWidget();
    /**
     * @brief InitSingleFlawTableWidget 初始化缺陷界面
     */
    void InitSingleFlawTableWidget();
    /**
     * @brief InitSingleSizeTableWidget 初始化尺寸界面
     */
    void InitSingleSizeTableWidget();
    /**
     * @brief InitCameraSettingTableWidget 初始化相机设置界面
     */
    void InitCameraSettingTableWidget();
    /**
     * @brief InitRealTimeFlawTableWidget 初始化相机实时缺陷界面
     */
    void InitRealTimeFlawTableWidget();
    /**
     * @brief InitFlawShowWidget 初始化缺陷显示界面
     */
    void InitFlawShowWidget();
    /**
     * @brief InitSummaryTableWidget 初始化总结界面
     */
    void InitSummaryTableWidget();
    void InitDatabaseParam();//初始化数据库相关参数
    void ProcessThreadCV();

    void MainWindowsDisplay(NewGlassResult& result);
private:
    void upDateOverView(RUNNINGSTATUS status);//更新概述
    void imageDisplay(QString& imageUrl);//图片显示
    void UpdateStatisticsTable(NewGlassResult& result); //更新统计数据
    void realUpdateDatabase(NewGlassResult& result,std::vector<GlassDefect2>& glassDefectDatas);//更新数据库
    void realUpdateDefectTable(std::vector<GlassDefect2>& glassDefectDatas);//更新缺陷表格
    void realUpdateDefectDisplay(NewGlassResult& result);
public slots:
    void slot_CloseSystem();
    void slot_ShowSystemSettingForm();
    void slot_ActionStart();
    void slot_ActionStop();
    void slot_DataSearch();
    void slot_Offline();
    void slot_Calibrate();
    /**
     * @brief slot_GlassStaticTableInsertRowData 在玻璃统计表中插入一行数据
     * @param info 要插入的数据
     */
    void slot_GlassStaticTableInsertRowData(GlassDataBaseInfo info);
    /**
     * @brief slot_SingleFlawUpdateTableData 在缺陷界面中更新表格和图片
     * @param info
     */
    void slot_SingleFlawUpdateTableData(GlassDefectInfo info);
    void slot_SingleSizeUpdataTableData(GlassSizeInfo info);
    void slot_RefreshSystemTime();
    void slot_GetCameraBuffer();
signals:
    /**
     * @brief sign_GlassStaticTableInsertRowData 在玻璃统计表中插入一行数据
     * @param info
     */
    void sign_GlassStaticTableInsertRowData(GlassDataBaseInfo info);

protected:
    void mousePressEvent(QMouseEvent *event) override;

private:
    Ui::MainWindow* ui;
    QAction* m_pExit;               // 退出
    QAction* m_pSettings;           // 设置
    QAction* m_pStart;              // 开始
    QAction* m_pStop;               // 停止
    QAction* m_pDB;                 // 数据查询
    QAction* m_offline;             // 离线模式
    QAction* m_calibrate;           // 标定

    MyGraphicsItem* loadedPixmapItem; // 缺陷小图光场1
    MyGraphicsItem* loadedPixmapItem2;// 缺陷小图光场2
    MyGraphicsItem* loadedPixmapItem3;// 缺陷小图光场3

    MyGraphicsItem* loadedPixmapItem4; //尺寸轮廓图展示
    MyGraphicsItem* loadedPixmapItem5; //尺寸小图

    MyGraphicsItem* loadedPixmapItem6; //实时缺陷光场1
    MyGraphicsItem* loadedPixmapItem7; //实时缺陷光场2
    MyGraphicsItem* loadedPixmapItem8; //实时缺陷光场3

    std::shared_ptr<LightControl> m_lightControl;   // 设置界面
    QString _offlineSelectedDir;                    // 离线模式下选择的路径
    QTimer* _timer;                                 // 时钟用于更新系统时间
    QTimer* _timer1;                                // 时钟用于获取相机图像
    std::shared_ptr<Calibrate> calibratePtr;        // 标定界面
    std::shared_ptr<DataAnalysis> dataanalysisPtr;  // 数据查询界面

    HSDatabaseNamespace::HSDatabaseInterface* databasePtr = nullptr;                 // 数据库指针
    HSAlgorithmNamespace::HSAlgorithmInterface* algorithmPtr = nullptr;              // 算法指针
    HSJsoncppNamespace::HSJsoncppInterface* jsoncppPtr = nullptr;                    // jsoncpp指针

    CameraNameSpace::HSCameraInterface* cameraPtr0 = nullptr;              // 相机0指针
    CameraNameSpace::HSCameraInterface* cameraPtr1 = nullptr;              // 相机1指针
    HMODULE databaseDllHandle;      //databse动态库句柄
    HMODULE algorithmDllHandle;
    HMODULE cameraDllHandle;
    HMODULE jsoncppDllHandle;

    QHBoxLayout* hbox_layout;  //多个相机界面布局
    std::vector<DushenCameraArgs> m_args; //相机参数
    std::vector<QString> classes;//缺陷种类
    GlassSummary m_summary;//汇总信息
    QString m_currentSatus = "OK";  //当前玻璃状态
    QString m_sizeOKorNG = "OK";  // 当前玻璃尺寸状态
    double m_glassLength = 0;       //当前玻璃长度
    int m_defectNumber = 0;         // 当前缺陷的数量
    int m_huashanNumber = 0;        // 当前划伤数量
    int m_qipaoNumber = 0;        // 气泡数量
    int m_jieshiNumber = 0;       // 结石数量
    int m_benbianNumber = 0;      // 崩边数量
    int m_zanwuNumber = 0;        // 脏污数量
    int m_liewenNumber = 0;       // 裂纹数量
    int m_qitaNumber = 0;         // 其它数量

    std::atomic<int> defectPrimaryKey;  //缺陷数据库主键
    std::atomic<int> glassPrimaryKey;   //glass_table表主键
    RUNNINGSTATUS runstatus = RUNNINGSTATUS::UNKNOWN; // 玻璃是否结束
    QHBoxLayout* ImageLayout = nullptr;   //显示图片的布局
    std::vector<std::shared_ptr<std::thread>> threadPool;  //获取帧信号的线程池
};
#endif // MAINWINDOW_H
