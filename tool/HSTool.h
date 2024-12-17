#ifndef HSTOOL_H
#define HSTOOL_H

#include <QObject>
#include <QDateTime>
#include <QDir>
#include <mutex>
#include <vector>
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>

//////////////////文件保存路径//////////////////////
///
#define HISTORYPATH  "D:/HVCache/history/"
#define CAMERAPATH  "D:/HVCache/camera/"
#define CACHEPATH  "D:/HVCache/cache/"
#define LIGHTPATH "D:/HVCache/light/"

/**
 * @brief The CV_GLASSPART enum 图片属于玻璃的什么部分
 */
enum CV_GLASSPART {
    UNKNOW = 0,     /* 未知部分，用于初始化 */
    HEAD = 1,       /* 玻璃头部 */
    MIDDLE = 2,     /* 玻璃中部 */
    TAIL = 3,       /* 玻璃尾部 */
    EMPTY = 4,      /* 空白部分 */
    WholeGlass = 5, /* 整块玻璃 */
};

/**
 * @brief The FrameImage class main模块获取camera模块数据
 */
struct FrameImage {
    std::vector<cv::Mat> buffers;   /* 每个场对应图片 */
    int fieldnumberset;             /* 光场的数量 */
    int framecount;                 /* 当前帧数 */
    FrameImage():fieldnumberset(0),framecount(0){}
};


/**
 * @brief The SYSTEMSTATUS enum 系统执行状态
 */
enum SYSTEMSTATUS{
    INIT = 0,           /* 初始化状态 */
    SYANDBY = 1,        /* 待机状态 */
    OFFLINE = 2,        /* 离线状态 */
    STOP = 3,           /* 停止状态 */
    RUNNING = 4,        /* 运行状态 */
    ABNORMAL = 5,       /* 异常状态 */
    EXIT = 6,           /* 退出状态 */
    RESERVE = 7,        /* 保留状态 */
};

/**
 * @brief The SignalControl class 设置参数
 */
struct SignalControl {
/////////////////////////////////////////////////////////
    /**
   * @brief systemName 系统参数--系统名称
   */
    QString systemName;
    /**
   * @brief CamareNumber 系统参数--相机数量
   */
    int CamareNumber;
    /**
   * @brief Camare0Name 系统参数--相机0名称
   */
    QString Camare0Name;
    /**
   * @brief Camare1Name 系统参数--相机1名称
   */
    QString Camare1Name;
    /**
   * @brief Camare2Name 系统参数--相机2名称
   */
    QString Camare2Name;
    /**
   * @brief Camare3Name 系统参数--相机3名称
   */
    QString Camare3Name;
    /**
   * @brief ServerIP 系统参数--服务器IP
   */
    QString ServerIP;
    /**
   * @brief ServerPort 系统参数--服务端口
   */
    int ServerPort;
 //////////////////////////////////////////////////////////////
    /**
   * @brief YAccuracy 尺寸测量--Y方向像素精度
   */
    double YAccuracy;
    /**
   * @brief XCamera0Accuracy 尺寸测量--X方向相机0像素精度
   */
    double XCamera0Accuracy;
    /**
   * @brief XCamera1Accuracy 尺寸测量--X方向相机1像素精度
   */
    double XCamera1Accuracy;
//////////////////////////////////////////////////////////////
    /**
   * @brief Camera0Frame 相机参数--相机0帧次
   */
    int Camera0Frame;
    /**
   * @brief Camera0PhotoRow 相机参数--相机0拍照行数
   */
    int Camera0PhotoRow;
    /**
   * @brief Camera0ExposureTime 相机参数--相机0曝光时间
   */
    int Camera0ExposureTime;
    /**
   * @brief Camera0Gain 相机参数--相机0增益
   */
    int Camera0Gain;
    /**
   * @brief Camera1Frame 相机参数--相机1帧次
   */
    int Camera1Frame;
    /**
   * @brief Camera1PhotoRow 相机参数--相机1拍照行数
   */
    int Camera1PhotoRow;
    /**
   * @brief Camera1ExposureTime 相机参数--相机1曝光时间
   */
    int Camera1ExposureTime;
    /**
   * @brief Camera1Gain 相机参数--相机1增益
   */
    int Camera1Gain;
    /**
   * @brief Camera2Frame 相机参数--相机2帧次
   */
    int Camera2Frame;
    /**
   * @brief Camera2PhotoRow 相机参数--相机2拍照行数
   */
    int Camera2PhotoRow;
    /**
   * @brief Camera2ExposureTime 相机参数--相机2曝光时间
   */
    int Camera2ExposureTime;
    /**
   * @brief Camera2Gain 相机参数--相机2增益
   */
    int Camera2Gain;
    /**
   * @brief Camera3Frame 相机参数--相机3帧次
   */
    int Camera3Frame;
    /**
   * @brief Camera3PhotoRow 相机参数--相机3拍照行数
   */
    int Camera3PhotoRow;
    /**
   * @brief Camera3ExposureTime 相机参数--相机3曝光时间
   */
    int Camera3ExposureTime;
    /**
   * @brief Camera3Gain 相机参数--相机3增益
   */
    int Camera3Gain;
///////////////////////////////////////////////////////////////
    /**
     * @brief EncodePulseFilterUs 编码器参数--编码脉冲滤波
     */
    unsigned int EncodePulseFilterUs;
    /**
     * @brief PhotoelectricSensorFiltering 编码器参数--光电传感器滤波
     */
    unsigned int PhotoelectricSensorFiltering;
    /**
     * @brief WheelEncoderPhotoPulse   编码器参数--压轮编码器产生拍照脉冲(四倍频)
     */
    unsigned int WheelEncoderPhotoPulse;
    /**
     * @brief EncoderMode   编码器参数--编码器模式(0辊道/1压轮)
     */
    unsigned int EncoderMode;
    /**
     * @brief SolenoidValve1DownDelayLE  编码器参数--光电1触发电磁阀降下延时(ms)
     */
    unsigned int SolenoidValve1DownDelay;
    /**
     * @brief SolenoidValve1UpDelay  编码器参数--光电1离开电磁阀升起延时(ms)
     */
    unsigned int SolenoidValve1UpDelay;
    /**
     * @brief SolenoidValve2DownDelay  编码器参数--光电2触发电磁阀降下延时(ms)
     */
    unsigned int SolenoidValve2DownDelay;
    /**
     * @brief SolenoidValve2UpDelay  编码器参数--光电2离开电磁阀升起延时(ms)
     */
    unsigned int SolenoidValve2UpDelay;
    /**
     * @brief WheelAEncoderLB   编码器参数--压轮编码器A相计数
     */
    unsigned int WheelAEncoder;
    /**
     * @brief WheelBEncoder   编码器参数--压轮编码器B相计数
     */
    unsigned int WheelBEncoder;
    /**
     * @brief ErrorPhotoCount 编码器参数--查看错误拍照次数
     */
    unsigned int ErrorPhotoCount;
////////////////////////////////////////////////////////////////////////////
  /**
   * @brief 光源控制器参数--光场1发光时间10ns
   */
  unsigned int LightField1GlowTime;
  /**
   * @brief 光源控制器参数--光场2发光时间10ns
   */
  unsigned int LightField2GlowTime;
  /**
   * @brief 光源控制器参数--光场3发光时间10ns
   */
  unsigned int LightField3GlowTime;
  /**
   * @brief 光源控制器参数--光场4发光时间10ns
   */
  unsigned int LightField4GlowTime;
  /**
   * @brief 光源控制器参数--光源信号同步信号延时寄存器
   */
  unsigned int LightSignalSynchronizationDelayRegister;
  /**
   * @brief 光源控制器参数--拍照模式
   */
  unsigned int PhotoMode;
  /**
   * @brief 光源控制器参数--光源相机使能信号
   */
  unsigned int LightCameraEnable;
  /**
   * @brief 光源控制器参数--工作模式(0工作/1测试)
   */
  unsigned int WorkMode;
  /**
   * @brief 光源控制器参数--光源脉冲结束点寄存器
   */
  unsigned int LightSourcePulseEndPointRegister;
  /**
   * @brief 光源控制器参数--同步脉冲周期寄存器
   */
  unsigned int SyncPulsePeriodRegister;
  /**
   * @brief 光源控制器参数--相机帧信号触发延时行数(行)
   */
  unsigned int CameraFrameSignalTriggerDelay;
  /**
   * @brief 光源控制器参数--拍照结束延时行数(行)
   */
  unsigned int TimelapseAfterPhotoShootEnd;
  /**
   * @brief 光源控制器参数--选择光场的数量
   */
  unsigned int SelectedLightFieldNumber;
  /**
   * @brief 光源控制器参数--帧信号输出
   */
  unsigned int FrameSignalOutput;

  SignalControl():
    systemName(""),
    CamareNumber(0),
    Camare0Name(""),
    Camare1Name(""),
    Camare2Name(""),
    Camare3Name(""),
    ServerIP(""),
    ServerPort(0),
    YAccuracy(0.0),
    XCamera0Accuracy(0.0),
    XCamera1Accuracy(0.0),
    Camera0Frame(0),
    Camera0PhotoRow(0),
    Camera0ExposureTime(0),
    Camera0Gain(0),
    Camera1Frame(0),
    Camera1PhotoRow(0),
    Camera1ExposureTime(0),
    Camera1Gain(0),
    Camera2Frame(0),
    Camera2PhotoRow(0),
    Camera2ExposureTime(0),
    Camera2Gain(0),
    Camera3Frame(0),
    Camera3PhotoRow(0),
    Camera3ExposureTime(0),
    Camera3Gain(0),
    EncodePulseFilterUs(0),
    PhotoelectricSensorFiltering(0),
    WheelEncoderPhotoPulse(0),
    EncoderMode(0),
    SolenoidValve1DownDelay(0),
    SolenoidValve1UpDelay(0),
    SolenoidValve2DownDelay(0),
    SolenoidValve2UpDelay(0),
    WheelAEncoder(0),
    WheelBEncoder(0),
    ErrorPhotoCount(0),
    LightField1GlowTime(0),
    LightField2GlowTime(0),
    LightField3GlowTime(0),
    LightField4GlowTime(0),
    LightSignalSynchronizationDelayRegister(0),
    PhotoMode(0),
    LightCameraEnable(0),
    WorkMode(0),
    LightSourcePulseEndPointRegister(0),
    SyncPulsePeriodRegister(0),
    CameraFrameSignalTriggerDelay(0),
    TimelapseAfterPhotoShootEnd(0),
    SelectedLightFieldNumber(0),
    FrameSignalOutput(0){}
};

/**
 * @brief The GlassDataBaseInfo2 class 数据统计信息
 */
struct GlassDataBaseInfo2{
    int id;                 // 玻璃的id，唯一的主键
    QString time;           // 时间
    QString OKorNG;         // 整体情况OK或者NG
    QString sizeOKorNG;     // 尺寸OK或者NG
    double length;          // 玻璃的长度
    double width;           // 玻璃的宽度
    QString defectOKorNG;   // 缺陷OK或者NG
    int defectNumber;       // 玻璃的缺陷数量
    int huahenNumber;       // 划痕数量

    int yiwuNumber;         // 异物数量
    int AyiwuNumber;        // A区异物数量
    int ByiwuNumber;        // B区异物数量

    int qipaoNumber;        // 气泡数量
    int sqipaoNumber;       // 小气泡数量

    int madianNumber;       // 麻点数量
    int A2madianNumber;     // A区二级麻点数量
    int A3madianNumber;     // A区三级麻点数量
    int A10mmmadianNumber;  // A区10mm范围内麻点数量
    int B2madianNumber;     // B区二级麻点数量
    int B3madianNumber;     // B区三级麻点数量
    int B10mmmadianNumber;  // B区10mm麻点数量
    int siyin30mm2madianNumber; //丝印30mm附近2级麻点
    int siyin30mm3madianNumber; //丝印30mm附近3级麻点

    int shuiyinNumber;      // 水印数量
    int AshuiyinNumber;     // A区水印数量
    int B5mmshuiyinNumber;  // B区5mm范围内的水印数量

    int youmobuliangNumber; // 油墨不良数量
    int A3youmobuliangNumber; // A区3级油墨不良的数量
    int A2youmobuliangNumber; // A区2级油墨不良数量
    int A10mm2youmobuliangNumber; //A区10mm范围内2级油墨不良数量
    int A10mm3youmobuliangNumber; // A区10mm范围内3级油墨不良数量
    int B3youmobuliangNumber; // B区3级油墨不良数量
    int B2youmobuliangNumber; // B区2级油墨不良数量
    int B10mm2youmobuliangNumber; //B区10mm范围内2级油墨不良数量
    int B10mm3youmobuliangNumber; // B区10mm范围内3级油墨不良数量
    int siyin30mm3youmobuliangNumber; // 丝印30mm范围内3级点油墨不良数量
    int siyin30mm2youmobuliangNumber; // 丝印30mm范围内2级点油墨不良数量

    int juchibianNumber;    // 锯齿边数量
    int juchibianAllLength;  // 锯齿边总长度
    int siyinquexianNumber; // 丝印缺陷数量
    int guahuaNumber;       // 刮花数量
    int AguahuaNumber;      // A区刮花数量
    int liewenNumber;       // 裂纹数量
    int benbianjiaoNumber;   //崩边角数量
    QString historyPath;    // 历史图片信息
    GlassDataBaseInfo2()
        :id(0)
        , time("")
        , OKorNG("OK")
        , sizeOKorNG("OK")
        , length(0.0)
        , width(0.0)
        , defectOKorNG("OK")
        , defectNumber(0)
        , huahenNumber(0)
        , yiwuNumber(0)
        , AyiwuNumber(0)
        , ByiwuNumber(0)
        , qipaoNumber(0)
        , sqipaoNumber(0)
        , madianNumber(0)
        , A2madianNumber(0)
        , A3madianNumber(0)
        , A10mmmadianNumber(0)
        , B2madianNumber(0)
        , B3madianNumber(0)
        , B10mmmadianNumber(0)
        , siyin30mm2madianNumber(0)
        , siyin30mm3madianNumber(0)
        , shuiyinNumber(0)
        , AshuiyinNumber(0)
        , B5mmshuiyinNumber(0)
        , youmobuliangNumber(0)
        , A3youmobuliangNumber(0)
        , A2youmobuliangNumber(0)
        , A10mm2youmobuliangNumber(0)
        , A10mm3youmobuliangNumber(0)
        , B3youmobuliangNumber(0)
        , B2youmobuliangNumber(0)
        , B10mm2youmobuliangNumber(0)
        , B10mm3youmobuliangNumber(0)
        , siyin30mm3youmobuliangNumber(0)
        , siyin30mm2youmobuliangNumber(0)
        , juchibianNumber(0)
        , juchibianAllLength(0)
        , siyinquexianNumber(0)
        , guahuaNumber(0)
        , AguahuaNumber(0)
        , liewenNumber(0)
        , benbianjiaoNumber(0)
        , historyPath(""){}
};


/**
 * @brief The GlassSizeInfo2 class 孔洞、门夹、丝印信息
 */
struct GlassSizeInfo2{
    size_t id;              // 主键id,玻璃尺寸信息的顺序id
    int sizeID;             // 孔、门夹、丝印排列顺序
    QString time;           // 时间
    QString sizeType;       // 类型
    QString sizeLevel;      // 等级
    double lengthX;         // 长X(mm)
    double widthY;          // 宽Y(mm)
    double marginsX;        // 边距X(mm)
    double marginsY;        // 边距Y(mm)
    int Pixlength;          // 门夹长度
    int PixWidth;            // 门夹宽度
    int PixMarginsX;         // 门夹边距X
    int PixMarginsY;         // 门夹边距Y
    size_t glassid;         // 外键id,玻璃的id
    QString imagePath0;     // 透射亮场缺陷图片的路径
    QString imagePath1;     // 反射亮场缺陷图片的路径
    QString imagePath2;     // 反射暗场缺陷图片的路径
    cv::Mat Region0;         // 图片
    cv::Mat Region1;         // 图片
    cv::Mat Region2;         // 图片
    cv::Rect rect;           // 坐标信息
    GlassSizeInfo2():id(0),
        sizeID(0),
        time(""),
        sizeType(""),
        sizeLevel("OK"),
        lengthX(0.0),
        widthY(0.0),
        marginsX(0.0),
        marginsY(0.0),
        Pixlength(0),
        PixWidth(0),
        PixMarginsX(0),
        PixMarginsY(0),
        glassid(0),
        imagePath0(""),
        imagePath1(""),
        imagePath2(""){}
};

/**
 * @brief The glassRegion enum 缺陷所处位置
 */
enum glassRegion{
    EDGE = 1,
    FACE = 2,
};

/**
 * @brief The GlassDefect2 class 单个缺陷信息
 */
struct GlassDefect2{
    int id;                 // 主键id,在所有缺陷中的顺序
    int defectId;           // 缺陷id，在一块玻璃中缺陷的顺序
    QString time;           // 缺陷检测时间
    QString defectType;     // 缺陷类型
    QString defectLevel;    // 缺陷等级，OK NG
    int pixX;               // X坐标的像素值
    int pixY;               // Y坐标的像素值
    int pixLength;          // 长度的像素值
    int pixWidth;           // 宽度的像素值
    int pixArea;            // 面积的像素值
    double x;               // 缺陷在玻璃上的X坐标
    double y;               // 缺陷在玻璃上的Y坐标
    double length;          // 缺陷的长度
    double width;           // 缺陷的宽度
    double area;            // 缺陷面积大小
    size_t glassid;         // 外键id,玻璃的id
    QString imagePath0;     // 透射亮场缺陷图片的路径
    QString imagePath1;     // 反射亮场缺陷图片的路径
    QString imagePath2;     // 反射暗场缺陷图片的路径
    cv::Mat region0;
    cv::Mat region1;
    cv::Mat region2;
    cv::Rect rect;          // 缺陷在玻璃上的位置
    int typeID;             // 分类器的结果id
    glassRegion gregion;    // 缺陷在边部还是面部
    GlassDefect2():id(0),
                defectId(0),
                time(""),
                defectType(""),
                defectLevel(""),
                pixX(0),
                pixY(0),
                pixLength(0),
                pixWidth(0),
                pixArea(0),
                x(0),
                y(0),
                length(0),
                width(0),
                area(0),
                glassid(0),
                imagePath0(""),
                imagePath1(""),
                imagePath2(""),
                typeID(0){}

};

/**
 * @brief The GlassSummary class 概述信息
 */
struct GlassSummary{
    int id; // 主键id，标注不同的天数
    QString time;   // 刷新表格时的时间
    int glasstotalcount; //玻璃总数
    QString currentglassstatus; //玻璃当前状态
    int OKcount; //OK总数
    int NGcount; //NG总数
    double passrate; //合格率
    int exceptioncount; //异常数目
    QString messagePath; //日志文件所在的路径
    int lastglassID;  //最后一块玻璃的ID,ID对应的是数据统计里面的ID
    GlassSummary(){
        id = 0;
        time = "";
        glasstotalcount = 0;
        currentglassstatus = "OK";
        OKcount = 0;
        NGcount = 0;
        passrate = 0.0; //合格率
        exceptioncount = 0; //异常数目
        messagePath = ""; //日志文件所在的路径
        lastglassID = 0;  //最后一块玻璃的ID,ID对应的是数据统计里面的ID
    }
};

/**
 * @brief The CameraCropArg class 单个相机裁剪参数
 */
struct CameraCropArg{
    uint topPixCrop;        //图像上边缘裁剪多少像元
    uint bottomPixCrop;     //图像下边缘裁剪多少像元
    uint leftPixCrop;       //图像左侧边缘
    uint rightPixCrop;      //图像右侧边缘
    CameraCropArg():
        topPixCrop(0),
        bottomPixCrop(0),
        leftPixCrop(0),
        rightPixCrop(0){}
};

/**
 * @brief The CropArgPackage class 图像裁剪参数包
 */
struct CropArgPackage{
    int cameracount ; //多少相机多少图片
    std::vector<CameraCropArg> args; //裁剪像元
};

/**
 * @brief The NewGlassResult class 算法执行后的每帧结果
 */
struct NewGlassResult{
    bool isEmpty;
    int currentFrameCount;                   // 当前是第几帧
    std::vector<GlassDefect2> defectRes;     // 每帧结果数据
    std::vector<GlassSizeInfo2> sizeRes;     // 尺寸信息
    double pixGlassLength;                   // 这一帧长度
    double pixGlassWidth;                    // 这一帧宽度
    QString FaceQimagePath;                  // 图像保存
    cv::Mat glassRegion;                     // 玻璃图像
    CV_GLASSPART part;                       // 玻璃的哪一部分
    int divingX;                             // AB区分割坐标
    bool AisLeft;                            // A区在左边还是右边
    NewGlassResult():isEmpty(true),
                    currentFrameCount(0),
                    pixGlassLength(0),
                    pixGlassWidth(0),
                    FaceQimagePath(""),
                    part(CV_GLASSPART::UNKNOW),
        divingX(0),
        AisLeft(true){}
};

/**
 * @brief The regionInfor class 算法内部所用的检出缺陷信息
 */
struct regionInfor{
    int id;             // 序列id
    cv::Mat region;     // 区域
    QString path;       // 完整路径
    cv::Rect rect;      // 坐标信息
};

/**
 * @brief The ClassifyParam class 传统分类器输入参数
 */
struct ClassifyParam{
    cv::Rect regionRect;
    cv::Mat region;
};

/**
 * @brief The GlassResult class 一片玻璃显示信息参数包
 */
struct GlassResult {
    int glassID;                                                            /* 玻璃的主键ID */
    cv::Mat glassRegion0;                                                    /* 显示玻璃的区域0 */
    cv::Mat glassRegion1;                                                    /* 显示玻璃的区域1 */
    cv::Mat glassRegion2;                                                    /* 显示玻璃的区域2 */
    GlassDataBaseInfo2 glassStatistics;                                     /* 玻璃的统计信息 */
    std::vector<GlassDefect2> glassDefects;                                 /* 一片玻璃的所有缺陷信息 */
    std::vector<GlassSizeInfo2> glassSize;                                  /* 尺寸信息 */
    GlassSummary glassSummary;                                              /* 概述信息 */
};

/**
 * @brief The ConnectedComponent class 合并元素的结构体
 */
struct ConnectedComponent {
    cv::Rect rect;
    int area;
    int x;
    int y;
};

/**
 * @brief The EdgeElement class 边界小图元素
 */
struct EdgeElement {
    int id;           // 边界小图的id
    cv::Rect rect;    // 边界小图位置信息
    cv::Vec4i point2; // 计算梯度值
};

/**
 * @brief The EDGEPART enum 边部属于哪个部分
 */
enum EDGEPART {
    TOP = 0,
    LEFT = 1,
    RIGHT = 2,
    BOTTOM = 3,
    UNINIT = 4,
};

/**
 * @brief The EdgeInfo class 算法内部使用到的边部信息
 */
struct EdgeInfo{
    int id;
    cv::Mat region0;
    cv::Mat region1;
    cv::Mat region2;
    cv::Rect rect;
    EDGEPART PART;
    EdgeInfo():id(0),
        PART(EDGEPART::UNINIT){}
};

/**
 * @brief defectClasses 缺陷分类使用到的缺陷
 */
static std::vector<QString> defectClasses={"划痕","异物","气泡","麻点","水印","油墨不良","锯齿边","丝印缺陷","刮花","裂纹","崩边","崩角"};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void saveMatToImage(QString fullpath,cv::Mat region )
{
    std::string filename = fullpath.toStdString();
    cv::imwrite(filename, region);
}

static QString SyncSaveImage(cv::Mat& region,QString path="")
{
    try{
        if (path == "") {
            int randomNumber = std::rand() % 123567891;
            QString time2 = QDateTime::currentDateTime().toString("hh-mm-ss");
            path = "D:/HVCache/cache/"+time2 +"-"+ QString::number(randomNumber)+".jpg";
        }
        std::thread th1(&saveMatToImage,path,region);
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

static bool createDir(QString fullPath)
{
    QDir dir(fullPath);
    if (!dir.exists()) {
        if (dir.mkpath(fullPath)) {
            qDebug() << fullPath <<"目录创建成功";
            return true;
        } else {
            qDebug() << fullPath <<"目录创建失败";
            return false;
        }
    } else {
        qDebug() << fullPath <<"目录已存在";
        return true;
    }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template <typename T>
class SafeDefinitionThreadSafeVector {
public:
    SafeDefinitionThreadSafeVector() {}

    void push(const T& item) {
        std::lock_guard<std::mutex> lock(mutex_);
        vector_.push_back(item);
    }

    T pop() {
        std::lock_guard<std::mutex> lock(mutex_);
        if (vector_.empty()){
            return T();
        } else {
            T t = vector_.back();
            vector_.pop_back();
            return t;
        }
    }

    bool empty() {
        std::lock_guard<std::mutex> lock(mutex_);
        bool res = vector_.empty();
        return res;
    }

    void clear() {
        std::lock_guard<std::mutex> lock(mutex_);
        vector_.clear();
    }
public:
    std::vector<T> vector_;
    std::mutex mutex_;
};

template<typename Key, typename Value>
class ThreadSafeUnorderedMap {
private:
    std::unordered_map<Key, Value> mapData;
    std::mutex mutex_;

public:
    // 插入元素
    void insert(const Key& key, const Value& value) {
        std::lock_guard<std::mutex> lock(mutex_);
        mapData[key] = value;
    }

    // 查找元素
    bool find(const Key& key, Value& value) {
        std::lock_guard<std::mutex> lock(mutex_);
        auto it = mapData.find(key);
        if (it!= mapData.end()) {
            value = it->second;
            return true;
        }
        return false;
    }

    // 删除元素
    void erase(const Key& key) {
        std::lock_guard<std::mutex> lock(mutex_);
        mapData.erase(key);
    }
};

class __declspec(dllexport) HSTool
{
public:
    HSTool();
};


#endif // HSTOOL_H
