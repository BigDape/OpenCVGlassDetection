#ifndef GLOBAL_H
#define GLOBAL_H

#include <unordered_map>
#include <utility>
#include <vector>
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/core.hpp>
#include "HSTool.h"
#include "HSAlgorithmInterface.h"
#include "HSDatabaseInterface.h"
#include "HSCameraInterface.h"
#include "HSJsoncppInterface.h"
#include "HSSocketInterface.h"

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
    void ReassignValue(SignalControl signalctrl);
public:
    QString CurrentRecipe   = "";            // 当前工单名称：8nm
    QString SystemName      = "";               // 当前系统名称：大拓智能视觉检测
    int camDefineNum        = 0;                 // 相机个数
    QString Camera0Name     = "";              // 当前照相机0名称：DSXL810003076
    QString Camera1Name     = "";              // 当前照相机1名称：DSXL810002378
    QString Camera2Name     = "";              // 当前照相机2名称：DSXL810002135
    QString Camera3Name     = "";              // 当前照相机3名称：DSXL810002382
    QString serverIp        = "";                 // 控制器IP地址：192.168.1.200
    int serverPort          = 0;                   // 控制器Port：7002
    double YAccuracy        = 0.0;                  // Y方向像素精度
    double XCamera0Accuracy = 0.0;            // X方向相机0像素精度
    double XCamera1Accuracy = 0.0;            // x方向相机1像素精度
    int Camera0Frame = 0;                   // 相机0帧次
    int Camera0PhotoRow = 0;                // 相机0拍照行数
    int Camera0ExposureTime = 0;            // 相机0曝光时间
    int Camera0Gain = 0;                    // 相机0增益
    int Camera1Frame = 0;                   // 相机1帧次
    int Camera1PhotoRow = 0;                // 相机1拍照行数
    int Camera1ExposureTime = 0;            // 相机1曝光时间
    int Camera1Gain = 0;                    // 相机1增益
    int Camera2Frame = 0;                   // 相机2帧次
    int Camera2PhotoRow = 0;                // 相机2拍照行数
    int Camera2ExposureTime = 0;            // 相机2曝光时间
    int Camera2Gain = 0;                    // 相机2增益
    int Camera3Frame = 0;                   // 相机3帧次
    int Camera3PhotoRow = 0;                // 相机3拍照行数
    int Camera3ExposureTime = 0;            // 相机3曝光时间
    int Camera3Gain = 0;                    // 相机3增益
    unsigned int EncodePulseFilterUs = 0;   // 编码器参数--编码脉冲滤波
    unsigned int PhotoelectricSensorFiltering = 0;// 编码器参数--光电传感器滤波
    unsigned int WheelEncoderPhotoPulse = 0;   //  编码器参数--压轮编码器产生拍照脉冲(四倍频)
    unsigned int EncoderMode = 0;              // 编码器参数--编码器模式(0辊道/1压轮)
    unsigned int SolenoidValve1DownDelay = 0;  // 编码器参数--光电1触发电磁阀降下延时(ms)
    unsigned int SolenoidValve1UpDelay = 0;    // 编码器参数--光电1离开电磁阀升起延时(ms)
    unsigned int SolenoidValve2DownDelay = 0;  // 编码器参数--光电2触发电磁阀降下延时(ms)
    unsigned int SolenoidValve2UpDelay = 0;// 编码器参数--光电2离开电磁阀升起延时(ms)
    unsigned int WheelAEncoder = 0;             // 编码器参数--压轮编码器A相计数
    unsigned int WheelBEncoder = 0;         // 编码器参数--压轮编码器B相计数
    unsigned int ErrorPhotoCount = 0;       // 编码器参数--查看错误拍照次数
    unsigned int LightField1GlowTime = 0;   // 光源控制器参数--光场1发光时间10ns
    unsigned int LightField2GlowTime = 0;   // 光源控制器参数--光场2发光时间10ns
    unsigned int LightField3GlowTime = 0;   // 光源控制器参数--光场3发光时间10ns
    unsigned int LightField4GlowTime = 0;    // 光源控制器参数--光场4发光时间10ns
    unsigned int LightSignalSynchronizationDelayRegister = 0;// 光源控制器参数--光源信号同步信号延时寄存器
    unsigned int PhotoMode = 0;             // 光源控制器参数--拍照模式
    unsigned int LightCameraEnable = 0;     // 光源控制器参数--光源相机使能信号
    unsigned int WorkMode = 0;              // 光源控制器参数--工作模式(0工作/1测试)
    unsigned int LightSourcePulseEndPointRegister = 0;// 光源控制器参数--光源脉冲结束点寄存器
    unsigned int SyncPulsePeriodRegister = 0; //光源控制器参数--同步脉冲周期寄存器
    unsigned int CameraFrameSignalTriggerDelay = 0;// 光源控制器参数--相机帧信号触发延时行数(行)
    unsigned int TimelapseAfterPhotoShootEnd = 0;// 光源控制器参数--拍照结束延时行数(行)
    unsigned int SelectedLightFieldNumber = 0;// 光源控制器参数--选择光场的数量
    unsigned int FrameSignalOutput = 0;// 光源控制器参数--帧信号输出

    std::unordered_map<int,std::pair<QString,QString>> rowMapXY; //当前玻璃的缺陷坐标
    CropArgPackage crops;  //标定数据
    SYSTEMSTATUS currentsystem = SYSTEMSTATUS::INIT;  //当前系统状态

    HSDatabaseNamespace::HSDatabaseInterface* databasePtr = nullptr;        /* 数据库指针 */
    HSAlgorithmNamespace::HSAlgorithmInterface* algorithmPtr = nullptr;     /* 算法指针 */
    HSJsoncppNamespace::HSJsoncppInterface* jsoncppPtr = nullptr;           /* jsoncpp指针 */
    SocketNameSpace::HSSocketInterface* SocketObjectPtr = nullptr;
    CameraNameSpace::HSCameraInterface* cameraPtr0 = nullptr;               /* 相机0指针 */
    CameraNameSpace::HSCameraInterface* cameraPtr1 = nullptr;               /* 相机1指针 */
};


#endif // GLOBAL_H
