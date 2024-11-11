#ifndef GLOBAL_H
#define GLOBAL_H

#include <unordered_map>
#include <utility>
#include <vector>
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
    int camDefineNum;                 // 相机个数
    QString Camera0Name;              // 当前照相机0名称：DSXL810003076
    QString Camera1Name;              // 当前照相机1名称：DSXL810002378
    QString Camera2Name;              // 当前照相机2名称：DSXL810002135
    QString Camera3Name;              // 当前照相机3名称：DSXL810002382
    QString serverIp;                 // 控制器IP地址：192.168.1.200
    int serverPort;                   // 控制器Port：7002
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
    unsigned int EncodePulseFilterUs;   // 编码器参数--编码脉冲滤波
    unsigned int PhotoelectricSensorFiltering;// 编码器参数--光电传感器滤波
    unsigned int WheelEncoderPhotoPulse;   //  编码器参数--压轮编码器产生拍照脉冲(四倍频)
    unsigned int EncoderMode;              // 编码器参数--编码器模式(0辊道/1压轮)
    unsigned int SolenoidValve1DownDelay;  // 编码器参数--光电1触发电磁阀降下延时(ms)
    unsigned int SolenoidValve1UpDelay;    // 编码器参数--光电1离开电磁阀升起延时(ms)
    unsigned int SolenoidValve2DownDelay;  // 编码器参数--光电2触发电磁阀降下延时(ms)
    unsigned int SolenoidValve2UpDelay;// 编码器参数--光电2离开电磁阀升起延时(ms)
    unsigned int WheelAEncoder;             // 编码器参数--压轮编码器A相计数
    unsigned int WheelBEncoder;         // 编码器参数--压轮编码器B相计数
    unsigned int ErrorPhotoCount;       // 编码器参数--查看错误拍照次数
    unsigned int LightField1GlowTime;   // 光源控制器参数--光场1发光时间10ns
    unsigned int LightField2GlowTime;   // 光源控制器参数--光场2发光时间10ns
    unsigned int LightField3GlowTime;   // 光源控制器参数--光场3发光时间10ns
    unsigned int LightField4GlowTime;    // 光源控制器参数--光场4发光时间10ns
    unsigned int LightSignalSynchronizationDelayRegister;// 光源控制器参数--光源信号同步信号延时寄存器
    unsigned int PhotoMode;             // 光源控制器参数--拍照模式
    unsigned int LightCameraEnable;     // 光源控制器参数--光源相机使能信号
    unsigned int WorkMode;              // 光源控制器参数--工作模式(0工作/1测试)
    unsigned int LightSourcePulseEndPointRegister;// 光源控制器参数--光源脉冲结束点寄存器
    unsigned int SyncPulsePeriodRegister; //光源控制器参数--同步脉冲周期寄存器
    unsigned int CameraFrameSignalTriggerDelay;// 光源控制器参数--相机帧信号触发延时行数(行)
    unsigned int TimelapseAfterPhotoShootEnd;// 光源控制器参数--拍照结束延时行数(行)
    unsigned int SelectedLightFieldNumber;// 光源控制器参数--选择光场的数量
    unsigned int FrameSignalOutput;// 光源控制器参数--帧信号输出

    std::unordered_map<int,std::pair<QString,QString>> rowMapXY; //当前玻璃的缺陷坐标
    CropArgPackage crops;  //标定数据
    SYSTEMSTATUS currentsystem;  //当前系统状态
};


#endif // GLOBAL_H
