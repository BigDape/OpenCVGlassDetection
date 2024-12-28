/********************************************************************************
 *  Puspose:
 *      mainwidnows.h 处理函数
 *
 * Author:
 *      zhang shuanggui
 *
 * create time:
 *      2025/11/25
 *
 *******************************************************************************/

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

/////////////////////////////////////////////////////////////////////////////////////
///  @brief 引用的头文件
///
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
#include "HSJsoncppInterface.h"
#include "Form/DataAnalysis.h"
#include "HSTool.h"

////////////////////////////////////////////////////////////////////////////////////
///  @brief MainForm类的声明
///
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

    /**
     * @brief InitImageCacheDirectory 初始化图片缓存目录
     */
    void InitImageCacheDirectory();

    /**
     * @brief ProcessThreadCV 开始处理流程
     */
    void ProcessThreadCV();

private:
    /**
     * @brief upDateOverView 更新概述
     */
    void upDateOverView();

    /**
     * @brief imageDisplay 主界面上的图片显示
     * @param [in] part 更新的玻璃帧所属部分
     * @param [in] image 要显示的图像
     */
    void imageDisplay(CV_GLASSPART part, cv::Mat image);

    /**
     * @brief checkFrameParam 检查相机获取的图像是否符合要求
     * @param [in] imageunit0 imageunit 原始图像数据
     * @param [in] imageunit1 imageunit 原始图像数据
     * @return true 符合要求 false 不符合要求
     */
    bool checkFrameParam(FrameImage imageunit0, FrameImage imageunit1);

    /**
     * @brief clearGlassDisplay 一片玻璃处理完后，重新清理部分全局变量
     */
    void clearGlassDisplay();

    /**
     * @brief insertGlassStaticTable 统计界面中插入一行统计数据
     * @param [in] data 统计数据
     */
    void insertGlassStaticTable(GlassDataBaseInfo2 data);

    /**
     * @brief setTableWidgetItem 设置单个表格内容
     * @param [in] row 表格的第几行
     * @param [in] col 表格的第几列
     * @param [in] text 表格要填入的内容
     * @param [in] table 表格对象
     * @param [in] brush 表格背景颜色，默认为白色
     */
    void setTableWidgetItem(int row,
                            int col,
                            QString text,
                            QTableWidget* table,
                            QBrush brush = Qt::white);

    /**
     * @brief summaryDefectNumber 统计缺陷，判断是否NG
     * @param [in] diviX A与B区分界X
     * @param [in] AisLeft A区是否在左边
     * @param [in] siyinRect 丝印的位置（匹配到的第一个丝印
     */
    void summaryDefectNumber(int diviX,
                             bool AisLeft,
                             cv::Rect siyinRect);

    /**
     * @brief insertDefectTable 插入一行统计数据
     * @param [in] defect 单个缺陷信息
     */
    void insertDefectTable(GlassDefect2 defect);

    /**
     * @brief loadedPixmapImage 加载小图
     * @param [in] img 要加载的小图
     * @param [in] view 要显示的组件
     * @param [in] loadImgItem 显示的组件
     */
    void loadedPixmapImage(QImage img,
                           QGraphicsView* view,
                           MyGraphicsItem* loadImgItem);

    /**
     * @brief insertSizeTable 尺寸表格中插入尺寸信息
     * @param [in] info 尺寸信息
     */
    void insertSizeTable(GlassSizeInfo2 info);

    /**
     * @brief batchInsertSizeTable 批量插入多个尺寸信息数据
     * @param [in] infos 尺寸信息
     */
    void batchInsertSizeTable(std::vector<GlassSizeInfo2> infos);

    /**
     * @brief RangeDefectCount 查看指定范围内的缺陷数量
     * @param [in] cacheVes 缺陷位置集合
     * @param [in] Xmm 多少毫米范围内
     * @param [in] MaxDefectCount 最大缺陷数量
     * @return 返回最大的缺陷数量
     */
    int RangeDefectCount(std::vector<cv::Rect> cacheVes,
                         int Xmm,
                         int MaxDefectCount);

    /**
     * @brief NGorOKHuaheng 判断划痕是否NG
     * @param [in] defect
     */
    void NGorOKHuaheng(GlassDefect2 defect);

    /**
     * @brief NGorOKyiwu 判断异物是否NG
     * @param [in] defect 缺陷信息
     * @param [in] diviX
     * @param AisLeft
     */
    void NGorOKyiwu(GlassDefect2 defect,
                    int diviX,
                    bool AisLeft);

    /**
     * @brief NGorOKqipao 判断气泡是否NG
     * @param [in] defect 缺陷信息
     */
    void NGorOKqipao(GlassDefect2 defect);

    /**
     * @brief NGorOKmadian 判断麻点是否NG
     * @param [in] defect 缺陷信息
     * @param [in] diviX 玻璃X轴分界线，小于diviX是A区，大于divix是B区
     * @param [in] AisLeft A区是否在左边
     * @param [in] siyinRect 丝印所在位置
     */
    void NGorOKmadian(GlassDefect2 defect,
                      int diviX,
                      bool AisLeft,
                      cv::Rect siyinRect);

    /**
     * @brief NGorOKshuiyin 判断水印是否NG
     * @param [in] defect 缺陷信息
     * @param [in] diviX 玻璃X轴分界线，小于diviX是A区，大于divix是B区
     * @param [in] AisLeft A区是否在左边
     */
    void NGorOKshuiyin(GlassDefect2 defect,
                       int diviX,
                       bool AisLeft);

    /**
     * @brief NGorOKyoumobuliang 判断油墨不良是否NG
     * @param [in] defect 缺陷信息
     * @param [in] diviX 玻璃X轴分界线，小于diviX是A区，大于divix是B区
     * @param [in] AisLeft A区是否在左边
     * @param [in] siyinRect 丝印所在位置
     */
    void NGorOKyoumobuliang(GlassDefect2 defect,
                            int diviX,
                            bool AisLeft,
                            cv::Rect siyinRect);

    /**
     * @brief NGorOKjuchibian 判断锯齿便是否NG
     * @param [in] defect 缺陷信息
     */
    void NGorOKjuchibian(GlassDefect2 defect);

    /**
     * @brief NGorOKsiyinquexian 判断丝印缺陷
     * @param [in] defect 缺陷信息
     */
    void NGorOKsiyinquexian(GlassDefect2 defect);

    /**
     * @brief NGorOKguahua 判断刮花是否NG
     * @param [in] defect 缺陷信息
     * @param [in] diviX 玻璃X轴分界线，小于diviX是A区，大于divix是B区
     * @param [in] AisLeft A区是否在左边
     */
    void NGorOKguahua(GlassDefect2 defect,
                      int diviX,
                      bool AisLeft);

    /**
     * @brief NGorOKliewen 判断刮花是否NG
     * @param [in] defect 缺陷信息
     */
    void NGorOKliewen(GlassDefect2 defect);

    /**
     * @brief NGorOKbengbianjiao 判断崩边角是否NG
     * @param [in] defect 缺陷信息
     */
    void NGorOKbengbianjiao(GlassDefect2 defect);

    /**
     * @brief handleFrameData 处理每帧缺陷数据结果
     * @param [in] result 每帧数据结果
     */
    void handleFrameData(NewGlassResult result);

    /**
     * @brief handleFrameData 处理每帧尺寸数据结果
     * @param [in] glassSize 每帧数据尺寸结果
     */
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
     * @param [in] image 玻璃cv::Mat图像
     */
    void slot_DisplayMain(cv::Mat image);

    /**
     * @brief slot_UpdateDefectTable 显示缺陷表格上的信息
     * @param [in] part 图像是玻璃的哪一部分
     * @param [in] glassDefectDatas 玻璃的缺陷数据
     */
    void slot_UpdateDefectTable(CV_GLASSPART part, std::vector<GlassDefect2> FrameDefects);

    /**
     * @brief slot_UpdateDefectImages 更新缺陷小图
     * @param item 小图组件指针
     */
    void slot_UpdateDefectImages(QTableWidgetItem* item);

    /**
     * @brief slot_UpdateSizeImage 更新尺寸小图
     * @param item 小图组件指针
     */
    void slot_UpdateSizeImage(QTableWidgetItem* item);

    /**
     * @brief slot_InsertDatabase 数据库批量插入
     */
    void slot_InsertDatabase();

    /**
     * @brief slot_RebackHistoryImage 缺陷显示界面回溯历史图片
     */
    void slot_RebackHistoryImage();

    /**
     * @brief slot_Silkscreen 丝印匹配的模板
     */
    void slot_Silkscreen();

signals:
    /**
     * @brief sign_InsertDatabase 数据库批量插入
     */
    void sign_InsertDatabase();

    /**
     * @brief sign_GlassStaticTableInsertRowData 数据统计表插入一行
     * @param info
     */
    void sign_GlassStaticTableInsertRowData(GlassDataBaseInfo2 info);

    /**
     * @brief sign_DisplayMain 显示图片
     * @param image
     */
    void sign_DisplayMain(cv::Mat image);

    /**
     * @brief sign_UpdateDefectTable 更新缺陷表格
     * @param part 玻璃部分
     * @param FrameDefects 缺陷数据
     */
    void sign_UpdateDefectTable(CV_GLASSPART part, std::vector<GlassDefect2> FrameDefects);

    /**
     * @brief sign_SingleSizeUpdataTableData 更新尺寸表格
     * @param infos
     */
    void sign_SingleSizeUpdataTableData(std::vector<GlassSizeInfo2> infos);
protected:
    /**
     * @brief mousePressEvent 捕获在主界面显示界面上的鼠标坐标
     * @param event
     */
    void mousePressEvent(QMouseEvent *event) override;

    /**
     * @brief contextMenuEvent 右击显示菜单栏
     * @param event
     */
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
    QAction* m_silkscreen;                  /* 丝印匹配按钮对象 */

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

    std::atomic<int> defectPrimaryKey = 0;                                      /* 缺陷数据库主键 */
    std::atomic<int> glassPrimaryKey = 0;                                       /* glass_table表主键 */
    std::atomic<int> sizePrimaryKey = 0;                                        /* 尺寸数据库主键 */
    std::atomic<int> summaryPrimaryKey = 0;                                     /* summary表主键 */

    QHBoxLayout* ImageLayout = nullptr;                                     /* 显示图片的布局 */
    std::shared_ptr<std::thread> m_startThread = nullptr;                   /* 开始线程指针 */
    std::mutex m_mutex;                                                     /* 全局锁 */
    std::mutex time_mutex;                                                  /* 时间锁 */
    cv::Mat m_glassRegion;                                                  /* 显示玻璃的区域 */
    GlassResult m_glassResult;                                              /* 玻璃信息 */
    std::vector<cv::Rect>   m_AmadianRects;                                 /* A区麻点的区域的点集合。 */
    std::vector<cv::Rect>   m_BmadianRects;                                 /* B区麻点的区域点集合。 */
    std::vector<cv::Rect>   m_BshuiyinRects;                                /* B区水印的区域点集合。 */
    std::vector<cv::Rect>   m_A10mm2youmobuliangRects;                      /* A区10mm范围内2级点的区域点集合 */
    std::vector<cv::Rect>   m_A10mm3youmobuliangRects;                      /* A区10mm范围内3级点的区域点集合 */
    std::vector<cv::Rect>   m_B10mm2youmobuliangRects;                      /* B区10mm范围内2级点的区域点集合 */
    std::vector<cv::Rect>   m_B10mm3youmobuliangRects;                      /* B区10mm范围内3级点的区域点集合 */
    int   m_juchibianAllLengthRects = 0;                                    /* 锯齿边长度 */
    int   m_juchibianAllWidthRects = 0;                                     /* 锯齿边宽度 */
};
#endif // MAINWINDOW_H
