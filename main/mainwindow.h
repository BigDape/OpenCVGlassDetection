#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QDockWidget>
#include <QMainWindow>
#include <QSettings>
#include <QThread>
#include <QTableWidgetItem>
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/core.hpp>
#include <atomic>
#include "Form/LightControl.h"
#include "Form/MyGraphicsitem.h"
#include "Form/Calibrate.h"
#include "HSAlgorithmInterface.h"
#include "HSDatabaseInterface.h"
#include "HSCameraInterface.h"
#include "Form/DataAnalysis.h"
#include "HSTool.h"


QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

/**
 * @brief The MainWindow class 用户主界面类
 */
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

    void InitImageCacheDirectory();//初始化图片缓存目录

    /**
     * @brief ProcessThreadCV 开始处理流程
     */
    void ProcessThreadCV();

private:
    /**
     * @brief upDateOverView 更新概述
     * @param [in] status 更新的玻璃帧所属部分
     */
    void upDateOverView();

    /**
     * @brief imageDisplay 主界面上的图片显示
     * @param [in] part 更新的玻璃帧所属部分
     * @param [in] currentFrameCount 相机拍照所属的帧数
     * @param [in] image 要显示的图像
     */
    void imageDisplay(CV_GLASSPART part, cv::Mat image);

    /**
     * @brief checkFrameParam 检查相机获取的图像是否符合要求
     * @param [in] imageunit 原始图像数据
     * @return true 符合要求 false 不符合要求
     */
    bool checkFrameParam(FrameImage imageunit0, FrameImage imageunit1);

    /**
     * @brief clearGlassDisplay 一片玻璃处理完后，重新清理部分全局变量
     * @param [in] part 所属玻璃的部分
     */
    void clearGlassDisplay();

    void insertGlassStaticTable(GlassDataBaseInfo2 data);//插入一行统计数据

    void setTableWidgetItem(int row,
                            int col,
                            QString text,
                            QTableWidget* table,
                            QBrush brush = Qt::white);
    /**
     * @brief [in] summaryDefectNumber 统计缺陷，判断是否NG
     * @param [in] diviX A与B区分界X
     * @param [in] AisLeft A区是否在左边
     * @param [in] siyinRect 丝印的位置（匹配到的第一个丝印）todo:玻璃没有丝印
     */
    void summaryDefectNumber(int diviX,
                             bool AisLeft,
                             cv::Rect siyinRect);

    void insertDefectTable(GlassDefect2 defect);//插入一行统计数据

    void loadedPixmapImage(QImage img,
                           QGraphicsView* view,
                           MyGraphicsItem* loadImgItem); //加载小图

    void initLoadedImage(MyGraphicsItem* loadItem, QGraphicsView* view);

    void insertSizeTable(GlassSizeInfo2 info);

    void batchInsertSizeTable(std::vector<GlassSizeInfo2> infos);

    int RangeDefectCount(std::vector<cv::Rect> cacheVes, int Xmm, int MaxDefectCount);//查看指定范围内的缺陷数量

    // 划痕判断NG
    void NGorOKHuaheng(GlassDefect2 defect);
    void NGorOKyiwu(GlassDefect2 defect, int diviX, bool AisLeft);
    void NGorOKqipao(GlassDefect2 defect);
    void NGorOKmadian(GlassDefect2 defect, int diviX, bool AisLeft, cv::Rect siyinRect);
    void NGorOKshuiyin(GlassDefect2 defect, int diviX, bool AisLeft);
    void NGorOKyoumobuliang(GlassDefect2 defect, int diviX, bool AisLeft, cv::Rect siyinRect);
    void NGorOKjuchibian(GlassDefect2 defect);
    void NGorOKsiyinquexian(GlassDefect2 defect);
    void NGorOKguahua(GlassDefect2 defect, int diviX, bool AisLeft);
    void NGorOKliewen(GlassDefect2 defect);
    void NGorOKbengbianjiao(GlassDefect2 defect);

    void handleFrameData(NewGlassResult result);
    void handleFrameData(std::vector<GlassSizeInfo2>& glassSize);
    /**
     * @brief GetCameraBufferAndExceute 获取相机照片和执行程序
     */
    void GetCameraBufferAndExceute();
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
    void slot_GlassStaticTableInsertRowData(GlassDataBaseInfo2 info);

    /**
     * @brief slot_SingleSizeUpdataTableData 在尺寸统计表插入数据
     * @param info
     */
    void slot_SingleSizeUpdataTableData(std::vector<GlassSizeInfo2> infos);

    /**
     * @brief slot_RefreshSystemTime 在概述界面实时更新系统时间
     */
    void slot_RefreshSystemTime();

    /**
     * @brief slot_DisplayMain 槽函数，在主界面上显示图片
     * @param [in] part 图片属于玻璃的什么位置
     * @param [in] image 玻璃cv::Mat图像
     */
    void slot_DisplayMain(cv::Mat image);

    /**
     * @brief slot_UpdateDefectTable 显示缺陷表格上的信息
     * @param [in] part 图像是玻璃的哪一部分
     * @param [in] glassDefectDatas 玻璃的缺陷数据
     */
    void slot_UpdateDefectTable(CV_GLASSPART part, std::vector<GlassDefect2> FrameDefects);

    void slot_UpdateDefectImages(QTableWidgetItem* item);//更新缺陷小图

    void slot_UpdateSizeImage(QTableWidgetItem* item);//更新尺寸小图

    void slot_InsertDatabase();//数据库批量插入

    void slot_InsertSizeDatabase(std::vector<GlassSizeInfo2> datas);

    void slot_RebackHistoryImage();

signals:
    void sign_InsertDatabase();//数据库批量插入
    void sign_GlassStaticTableInsertRowData(GlassDataBaseInfo2 info);//数据统计表插入一行
    void sign_DisplayMain(cv::Mat image); //显示图片
    void sign_UpdateDefectTable(CV_GLASSPART part, std::vector<GlassDefect2> FrameDefects);
    void sign_SingleSizeUpdataTableData(std::vector<GlassSizeInfo2> infos);
protected:
    /**
     * @brief mousePressEvent 捕获在主界面显示界面上的鼠标坐标
     * @param event
     */
    void mousePressEvent(QMouseEvent *event) override;
    // 右击菜单栏
    void contextMenuEvent(QContextMenuEvent *event) override;

private:
    Ui::MainWindow* ui;                     /* 主界面ui对象 */
    QAction* m_pExit;                       /* 退出按钮对象 */
    QAction* m_pSettings;                   /* 设置按钮对象 */
    QAction* m_pStart;                      /* 开始按钮对象 */
    QAction* m_pStop;                       /* 停止按钮对象 */
    QAction* m_pDB;                         /* 数据查询按钮对象 */
    QAction* m_offline;                     /* 离线模式按钮对象 */
    QAction* m_calibrate;                   /* 标定模式按钮对象 */

    MyGraphicsItem* loadedPixmapItem = nullptr;         /* 缺陷小图光场1 */
    MyGraphicsItem* loadedPixmapItem2 = nullptr;        /* 缺陷小图光场2 */
    MyGraphicsItem* loadedPixmapItem3 = nullptr;        /* 缺陷小图光场3 */
    MyGraphicsItem* loadedPixmapItem4 = nullptr;        /* 尺寸轮廓图展示 */
    MyGraphicsItem* loadedPixmapItem50 = nullptr;       /* 透射亮场尺寸小图 */
    MyGraphicsItem* loadedPixmapItem51 = nullptr;       /* 反射亮场尺寸小图 */
    MyGraphicsItem* loadedPixmapItem52 = nullptr;       /* 反射暗场尺寸小图 */
    MyGraphicsItem* loadedPixmapItem6 = nullptr;        /* 实时缺陷光场1 */
    MyGraphicsItem* loadedPixmapItem7 = nullptr;        /* 实时缺陷光场2 */
    MyGraphicsItem* loadedPixmapItem8 = nullptr;        /* 实时缺陷光场3 */
    MyGraphicsItem* myloadedPixmapItem = nullptr;

    std::shared_ptr<LightControl> m_lightControl;             /* 设置界面 */
    QTimer* _timer;                                           /* 时钟用于更新系统时间 */
    QTimer* _timer1;                                          /* 时钟用于获取相机图像 */
    std::shared_ptr<Calibrate> calibratePtr = nullptr;        /* 标定界面 */
    std::shared_ptr<DataAnalysis> dataanalysisPtr;            /* 数据查询界面 */

    HSDatabaseNamespace::HSDatabaseInterface* databasePtr = nullptr;        /* 数据库指针 */
    HSAlgorithmNamespace::HSAlgorithmInterface* algorithmPtr = nullptr;     /* 算法指针 */
    HSJsoncppNamespace::HSJsoncppInterface* jsoncppPtr = nullptr;           /* jsoncpp指针 */
    SocketNameSpace::HSSocketInterface* SocketObjectPtr = nullptr;
    CameraNameSpace::HSCameraInterface* cameraPtr0 = nullptr;               /* 相机0指针 */
    CameraNameSpace::HSCameraInterface* cameraPtr1 = nullptr;               /* 相机1指针 */
    HMODULE databaseDllHandle;                                              /* databse动态库句柄 */
    HMODULE algorithmDllHandle;                                             /* algorithm动态库句柄 */
    HMODULE cameraDllHandle;                                                /* camera动态库句柄 */
    HMODULE jsoncppDllHandle;                                               /* jsoncpp动态库句柄 */
    HMODULE socketDllHandle;
    QHBoxLayout* hbox_layout;                                               /* 多个相机界面布局 */
    std::vector<DushenCameraArgs> m_args;                                   /* 相机参数 */
    std::vector<QString> classes;                                           /* 缺陷种类 */

    std::atomic<int>    m_benbianNumber = 0;                                /* 崩边数量 */
    std::atomic<int>    m_liewenNumber = 0;                                 /* 裂纹数量 */

    std::atomic<int> defectPrimaryKey;                                      /* 缺陷数据库主键 */
    std::atomic<int> glassPrimaryKey;                                       /* glass_table表主键 */
    std::atomic<int> sizePrimaryKey;                                        /* 尺寸数据库主键 */

    QHBoxLayout* ImageLayout = nullptr;                                     /* 显示图片的布局 */
    std::shared_ptr<std::thread> m_startThread = nullptr;                   /* 开始线程指针 */
    std::mutex m_mutex;                                                     /* 全局锁 */
    cv::Mat m_glassRegion;                                                  /* 显示玻璃的区域 */
    GlassResult m_glassResult;      // 玻璃信息
    std::vector<cv::Rect>   m_AmadianRects;     // A区麻点的区域的点集合。todo：一片玻璃结束需要清理
    std::vector<cv::Rect>   m_BmadianRects;     // B区麻点的区域点集合。todo：一片玻璃结束需要清理
    std::vector<cv::Rect>   m_BshuiyinRects;    // B区水印的区域点集合。todo：一片玻璃结束需要清理
    std::vector<cv::Rect>   m_A10mm2youmobuliangRects; // A区10mm范围内2级点的区域点集合
    std::vector<cv::Rect>   m_A10mm3youmobuliangRects; // A区10mm范围内3级点的区域点集合
    std::vector<cv::Rect>   m_B10mm2youmobuliangRects; // B区10mm范围内2级点的区域点集合
    std::vector<cv::Rect>   m_B10mm3youmobuliangRects; // B区10mm范围内3级点的区域点集合
    int   m_juchibianAllLengthRects = 0; // 锯齿边长度
    int   m_juchibianAllWidthRects = 0; // 锯齿边宽度
};
#endif // MAINWINDOW_H
