#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QDockWidget>
#include <QMainWindow>
#include <QSettings>
#include <QThread>
#include <QTableWidgetItem>
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
#include "HSTool.h"


QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    /**
     * @brief MainWindow 构造函数
     * @param parent
     */
    MainWindow(QWidget* parent = nullptr);

    /**
     * @brief MainWindow 析构函数
     */
    ~MainWindow();

    /**
     * @brief InitComponents 初始化组件
     */
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

    /**
     * @brief InitDatabaseParam 初始化数据库相关参数
     */
    void InitDatabaseParam();

    /**
     * @brief ProcessThreadCV 开始处理流程
     */
    void ProcessThreadCV();

    /**
     * @brief MainWindowsDisplay 主界面显示数据
     * @param result 算法计算得到的结果
     */
    void MainWindowsDisplay(NewGlassResult result);

private:
    /**
     * @brief upDateOverView 更新概述
     * @param [in] status 更新的玻璃帧所属部分
     */
    void upDateOverView(CV_GLASSPART status);

    /**
     * @brief imageDisplay 主界面上的图片显示
     * @param [in] part 更新的玻璃帧所属部分
     * @param [in] currentFrameCount 相机拍照所属的帧数
     * @param [in] image 要显示的图像
     */
    void imageDisplay(CV_GLASSPART part,
                      int currentFrameCount,
                      cv::Mat image);

    /**
     * @brief UpdateStatisticsTable 更新统计数据
     * @param [in] result 算法结果
     */
    void UpdateStatisticsTable(NewGlassResult& result);

    /**
     * @brief realUpdateDatabase 更新数据库
     * @param [in] result 算法结果
     * @param [out] glassDefectDatas 算法统计的缺陷结果
     */
    void realUpdateDatabase(NewGlassResult result,std::vector<GlassDefect2>& glassDefectDatas);

    /**
     * @brief realUpdateDefectTable 更新缺陷表格
     * @param [in] part 更新的玻璃帧所属部分
     * @param [in] glassDefectDatas 统计算法后的缺陷结果
     */
    void realUpdateDefectTable(CV_GLASSPART part, std::vector<GlassDefect2>& glassDefectDatas);

    /**
     * @brief realUpdateDefectDisplay 更新实时缺陷信息表
     * @param [in] result 算法结果
     */
    void realUpdateDefectDisplay(NewGlassResult& result);

    /**
     * @brief updateSizeInfoTable 更新尺寸表格
     * @param [in] sizeRes 尺寸信息
     */
    void updateSizeInfoTable(std::vector<DoorClampAndHole>& sizeRes);

    /**
     * @brief checkFrameParam 检查相机获取的图像是否符合要求
     * @param [in] imageunit 原始图像数据
     * @return true 符合要求 false 不符合要求
     */
    bool checkFrameParam(FrameImage& imageunit);

    /**
     * @brief clearGlassDisplay 一片玻璃处理完后，重新清理部分全局变量
     * @param [in] part 所属玻璃的部分
     */
    void clearGlassDisplay(CV_GLASSPART part);

    /**
     * @brief saveMatToImage 保存cv::Mat到本地
     * @param [in] fullpath 包含文件名称的完整路径
     * @param [in] region 需要保存的cv::Mat
     */
    void saveMatToImage(QString fullpath,cv::Mat region );

    /**
     * @brief SyncSaveCurrentTimeImage 异步保存cv::Mat到本地
     * @param [in] region 需要保存的cv::Mat
     * @param [in] path 包含文件名称的完整路径，若未指定则会在D:/testopencv/camera/下以时间+随机数命名的文件
     * @return 返回文件保存的路径地址
     */
    QString SyncSaveCurrentTimeImage(cv::Mat& region,QString path="");


    void SyncInsertDatabase();

public slots:
    /**
     * @brief slot_CloseSystem 槽函数，关闭系统时触发
     */
    void slot_CloseSystem();

    /**
     * @brief slot_ShowSystemSettingForm 槽函数，打开设置界面
     */
    void slot_ShowSystemSettingForm();

    /**
     * @brief slot_ActionStart 槽函数，开始执行
     */
    void slot_ActionStart();

    /**
     * @brief slot_ActionStop 槽函数，停止执行
     */
    void slot_ActionStop();

    /**
     * @brief slot_DataSearch 槽函数，打开数据查询界面
     */
    void slot_DataSearch();

    /**
     * @brief slot_Offline 槽函数，打开离线模式界面
     */
    void slot_Offline();

    /**
     * @brief slot_Calibrate 槽函数，打开标定界面
     */
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

    /**
     * @brief slot_SingleSizeUpdataTableData 在尺寸统计表插入数据
     * @param info
     */
    void slot_SingleSizeUpdataTableData(GlassSizeInfo info);

    /**
     * @brief slot_RefreshSystemTime 在概述界面实时更新系统时间
     */
    void slot_RefreshSystemTime();

    /**
     * @brief slot_GetCameraBuffer 获取相机buffer病处理
     */
    void slot_GetCameraBuffer();

    /**
     * @brief slot_DisplayMain 槽函数，在主界面上显示图片
     * @param part
     * @param image
     */
    void slot_DisplayMain(CV_GLASSPART part, cv::Mat image);                                // 槽函数显示缺陷整图
    void slot_UpdateDefectTable(CV_GLASSPART part, std::vector<GlassDefect2> glassDefectDatas);                 // 槽函数显示缺线表格
    void slot_UpdateDefectDisplay(NewGlassResult result);                                    // 槽函数显示实时缺陷
signals:
    /**
     * @brief sign_GlassStaticTableInsertRowData 在玻璃统计表中插入一行数据
     * @param info
     */
    void sign_GlassStaticTableInsertRowData(GlassDataBaseInfo info);
    void sign_DisplayMain(QString imageUrl);

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

    MyGraphicsItem* loadedPixmapItem = nullptr; // 缺陷小图光场1
    MyGraphicsItem* loadedPixmapItem2 = nullptr;// 缺陷小图光场2
    MyGraphicsItem* loadedPixmapItem3 = nullptr;// 缺陷小图光场3

    MyGraphicsItem* loadedPixmapItem4 = nullptr; //尺寸轮廓图展示
    MyGraphicsItem* loadedPixmapItem5 = nullptr; //尺寸小图

    MyGraphicsItem* loadedPixmapItem6 = nullptr; //实时缺陷光场1
    MyGraphicsItem* loadedPixmapItem7 = nullptr; //实时缺陷光场2
    MyGraphicsItem* loadedPixmapItem8 = nullptr; //实时缺陷光场3

    MyGraphicsItem* myloadedPixmapItem = nullptr;

    std::shared_ptr<LightControl> m_lightControl;             // 设置界面
    QString _offlineSelectedDir;                              // 离线模式下选择的路径
    QTimer* _timer;                                           // 时钟用于更新系统时间
    QTimer* _timer1;                                          // 时钟用于获取相机图像
    std::shared_ptr<Calibrate> calibratePtr = nullptr;        // 标定界面
    std::shared_ptr<DataAnalysis> dataanalysisPtr;            // 数据查询界面

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
    std::atomic<double> m_glassLength = 0;       //当前玻璃长度
    std::atomic<int>    m_defectNumber = 0;         // 当前缺陷的数量
    std::atomic<int>    m_huashanNumber = 0;        // 当前划伤数量
    std::atomic<int>    m_qipaoNumber = 0;        // 气泡数量
    std::atomic<int>    m_jieshiNumber = 0;       // 结石数量
    std::atomic<int>    m_benbianNumber = 0;      // 崩边数量
    std::atomic<int>    m_zanwuNumber = 0;        // 脏污数量
    std::atomic<int>    m_liewenNumber = 0;       // 裂纹数量
    std::atomic<int>    m_qitaNumber = 0;         // 其它数量

    std::atomic<int> defectPrimaryKey;  //缺陷数据库主键
    std::atomic<int> glassPrimaryKey;   //glass_table表主键
    std::atomic<int> sizePrimaryKey;    // 尺寸数据库主键

    QHBoxLayout* ImageLayout = nullptr;   //显示图片的布局
    std::shared_ptr<std::thread> m_startThread = nullptr;
    std::vector<GlassSize> m_sizedatas;//存储尺寸数据
    std::mutex m_mutex; //全局锁
    std::atomic<int> m_sizeid = 0;//在每片玻璃上的排列顺序
    std::atomic<int> m_currentRow = 0 ; //每片玻璃的行数
    cv::Mat m_glassRegion;   // 显示玻璃的区域
    SafeDefinitionThreadSafeVector<GlassDefect2> VecDefect;
    std::shared_ptr<std::thread> m_databaseThread = nullptr;
};
#endif // MAINWINDOW_H
