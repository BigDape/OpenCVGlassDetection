#ifndef GLOBAL_H
#define GLOBAL_H

#include <unordered_map>
#include <utility>
#include <vector>
#include <Qwt/qwt_plot.h>
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/core.hpp>
#include "HSTool.h"

#define PARAM GlobalParamter::getInstance()

typedef struct FlawPoint {
    double x;
    double y;
    int FlawType;
} FlawPoint;

struct CourTour {
    int index;
    QString x;
    QString y;
};

//
// 线程安全的懒汉单例模式--局部静态变量
//
class GlobalParamter
{
private: //构造和析构函数私有，防止外部声明
    explicit GlobalParamter();
    virtual ~GlobalParamter();
public:
    static GlobalParamter& getInstance();
    QString GetParamterFromIniFile(QString fullpath, QString key);
    void SetParamterIntoIniFile(QString fullpath, QString key, QString value);
    QImage cvMat2QImage(const cv::Mat& mat);
    cv::Mat QImage2cvMat(QImage image);
public:
    QString CurrentRecipe;            // 当前工单名称：8nm
    QString SystemName;               // 当前系统名称：大拓智能视觉检测
    QString Camera0Name;              // 当前照相机0名称：DSXL810003076
    QString Camera1Name;              // 当前照相机1名称：DSXL810002378
    QString Camera2Name;              // 当前照相机2名称：DSXL810002135
    QString Camera3Name;              // 当前照相机3名称：DSXL810002382
    QString serverIp;                 // 控制器IP地址：192.168.1.200
    int serverPort;                   // 控制器Port：7002
    int FrameSignal;                  // 帧信号
    bool AlmLightSignal;              // 报警信号灯
    int AlmLightVal;                  // 报警值
    int FieldNumberSet;               // 场数
    QStringList camName;
    int camDefineNum;                   // 照相机个数
    QList<QString> camListName;         // 照相机名称list
    QList<int> FieldSelectedView;       // 光场选择的视角：1表示选中，0表示未选中
    quint64 GlassID_INT;                // 玻璃ID
    double RollerAngle;                 // 玻璃偏移的角度
    double encodeRollerYLength;         // 差分计算出来的长度
    std::vector<CourTour> courtourMapXY;// 轮廓点
    QwtPlot* m_plot;
    bool isOffline;                     // 是否触发了离线模式
    QString offlineFullPath;            // 离线模式路径
    int isSaveOriginImage;              // 保存原图
    int isSaveEntireImage;              // 保存整图
    int isSaveFlawImage;                // 保存缺捡图
    int isSaveCropImage;                // 保存裁剪图像
    int XYLengthEnable;                 // 尺寸测量启用
    int FlawDefectEnable;               // 缺陷检测启用
    int Camera12PixelDeviation;         // 12相机像素偏差
    int Camera23PixelDeviation;         // 23相机像素偏差
    int Camera24PixelDeviation;         // 24相机像素偏差
    int SilkToRollerDist;               // 丝印到辊道距离
    int ScratchAreaThreshold;           // 划痕面积阈值
    int BubbleStoneAreaThreshold;       // 气节面积阈值
    int DirtyAreaThreshold;             // 脏污面积阈值

    double YAccuracy;                  // Y方向像素精度
    double XCamera0Accuracy;            // X方向相机0像素精度
    double XCamera1Accuracy;            // x方向相机1像素精度
    int Camera0Frame;                   // 相机0帧次
    int Camera0PhotoRow;                // 相机0拍照行数
    int Camera0ExposureTime;            // 相机0曝光时间
    int Camera0Gain;                    // 相机0增益
    int Camera1Frame;                   // 相机1帧次
    int Camera1PhotoRow;                // 相机1拍照行数
    int Camera1ExposureTime;            // 相机1曝光时间
    int Camera1Gain;                    // 相机1增益
    int Camera2Frame;                   // 相机2帧次
    int Camera2PhotoRow;                // 相机2拍照行数
    int Camera2ExposureTime;            // 相机2曝光时间
    int Camera2Gain;                    // 相机2增益
    int Camera3Frame;                   // 相机3帧次
    int Camera3PhotoRow;                // 相机3拍照行数
    int Camera3ExposureTime;            // 相机3曝光时间
    int Camera3Gain;                    // 相机3增益
    int EncodeUnitToDist;               // 编码器单位刻度对应距离
    int EncodePulseFilterUs;            // 编码脉冲滤波
    int EncodeRevolution;               // 编码器转数
    int RollerPerimeterUm;              // 辊道周长
    int ExpectSinglePixelAccuracy;      // 期望单个像素精度
    int RollerMaxSpeedToRowCount;       // 辊道最大速度对应行频
    int EveryRowToEncodeCount;          // 每行对应的编码计数
    int PixelAccuracyUm;                    //像素精度um
    int PhotoelectricSignalPulseFilter;     //光电信号脉冲滤波
    int CamareTrigerPulseContinueTime10ns;  //相机触发脉冲持续时间10ns
    int PhotoelectricToCamareDist;          //光电与相机距离行
    int CamareFrameTrigerDelayRowCount;     // 相机帧触发延时行数
    int FrameSignalContinueTime;            //帧信号持续时间
    int ModuleEnableSignal;                 //模块使能信号
    int CamarePhotoRowCount;                //相机拍照行数
    int InnerRowFrequency;                  //内部行频
    int PhotoMode;                          //拍照模式
    int PhotoEndDelayRowCount;              //拍照延时行数
    int LightField1DelayTime;            //光场1延时时间10ns
    int LightField1GlowTime;             //光场1发光时间10ns
    int LightField2DelayTime;            //光场2延时时间10ns
    int LightField2GlowTime;             //光场2发光时间10ns
    int LightField3DelayTime;            //光场3延时时间10ns
    int LightField3GlowTime;             //光场3发光时间10ns
    int LightField4DelayTime;            //光场4延时时间10ns
    int LightField4GlowTime;             //光场4发光时间10ns
    int SelectedLightFieldNumber;        //选择光场数量
    int HorizontalDarkfieldSelectRegister;  //横向暗场选择寄存器
    int CamareAndLightFieldControl;         //相机与光场控制
    int SignalSwitch;                       //信号切换
    int RowSignalSelected;                  //行信号源选择
    std::unordered_map<int,std::pair<QString,QString>> rowMapXY; //当前玻璃的缺陷坐标
    CropArgPackage crops;  //标定数据
    SYSTEMSTATUS currentsystem;  //当前系统状态
};


#endif // GLOBAL_H
