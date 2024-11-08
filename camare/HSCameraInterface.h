
//使用方法： std::unique_ptr<CameraNameSpace::HSCameraInterface> myObject = CameraNameSpace::createMyDllObject();
#ifndef HSCAMERAINTERFACE_H
#define HSCAMERAINTERFACE_H

#include <memory>
#include <vector>
#include <QString>
#include <windows.h>
#include <QImage>

struct DushenCameraArgs{
    double expo;        // 相机曝光时间
    double gain;        // 相机增益
    double height;      // 相机行数
    double framecount;  // 相机多少帧
    int fieldnumberset; // 场的数量
    int camNumber;      // 相机个数
    QString camName;    // 相机名称
};

struct FrameImage {
    std::vector<QImage> buffers;//每个场对应图片
    int fieldnumberset; // 场的数量
    int framecount;     // 当前帧
};

namespace CameraNameSpace {

    // 错误码枚举
    enum class HSCameraError {
        SUCCESS = 0,
        INVALID_PARAMETER,
        OUT_OF_MEMORY,
        INNER_ERROR
    };
    // 抽象接口类
    class HSCameraInterface
    {
    public:
        virtual ~HSCameraInterface(){}
        /**
         * @brief InitCamera 初始化相机
         * @param args
         * @return
         */
        virtual HSCameraError InitCamera(DushenCameraArgs args) = 0;
        /**
         * @brief getCameraCounts 获取相机个数
         * @return
         */
        virtual unsigned int getCameraCounts() = 0;
        /**
         * @brief getCameraFriendlyNames 获取相机的名称数组
         * @return
         */
        virtual std::vector<QString> getCameraFriendlyNames() = 0;
        /**
         * @brief getCurrentCameraFriendlyName 获取当前相机名称
         * @return
         */
        virtual QString getCurrentCameraFriendlyName() = 0;
        /**
         * @brief IsScanned 获取相机是否已被扫描过
         * @param FriendlyName 相机名称
         * @return
         */
        virtual bool IsScanned(const QString FriendlyName) = 0;
        /**
         * @brief IsOpened 获取相机是否被打开
         * @param FriendlyName 相机名称
         * @return
         */
        virtual bool IsOpened(const QString FriendlyName) = 0;
        /**
         * @brief StopFunc 停止相机执行
         * @return
         */
        virtual HSCameraError StopFunc(const QString FriendlyName) = 0;
        /**
         * @brief Closefunc 关闭相机
         * @param FriendlyName 相机名称
         * @return
         */
        virtual HSCameraError Closefunc(const QString FriendlyName) = 0;
        /**
         * @brief SearchCamera 查询某个名称的相机是否被打开
         * @param FriendlyName
         * @return
         */
        virtual bool SearchCamera(const QString FriendlyName) = 0;
        /**
         * @brief OpenFunc 打开相机
         * @param FriendlyName 相机名称
         * @return
         */
        virtual HSCameraError OpenFunc(const QString FriendlyName) = 0;
        /**
         * @brief LoadIni 加载ini配置文件
         * @param FriendlyName
         * @return
         */
        virtual HSCameraError LoadIni(const QString FriendlyName) = 0;
        /**
         * @brief ScanFunc 相机扫描
         * @param FriendlyName
         * @return
         */
        virtual HSCameraError ScanFunc(const QString FriendlyName) = 0;
        /**
         * @brief ShowProperty 打开相机属性窗口
         * @param FriendlyName
         * @return
         */
        virtual HSCameraError ShowProperty(const QString FriendlyName,HWND windowsID) = 0;
        /**
         * @brief TriggerFunc 触发相机
         * @param FriendlyName
         * @return
         */
        virtual HSCameraError TriggerFunc(const QString FriendlyName) = 0;
        /**
         * @brief SaveIni 保存Ini文件
         * @param FriendlyName
         * @return
         */
        virtual HSCameraError SaveIni(const QString FriendlyName) = 0;
        /**
         * @brief setFieldSelectedView 设置相机选择的光场
         * @param FriendlyName
         * @return
         */
        virtual HSCameraError setFieldSelectedView(int field) = 0;
        /**
         * @brief setSoftTriggerFlag 设置相机软触发标记
         * @param flag
         * @return
         */
        virtual HSCameraError setSoftTriggerFlag(bool flag) = 0;
        /**
         * @brief StartFunc 设置相机开始
         * @param FriendlyName
         * @return
         */
        virtual HSCameraError StartFunc(const QString FriendlyName) = 0;
        /**
         * @brief IsStarted 获取相机是否开始
         * @param FriendlyName
         * @return
         */
        virtual bool IsStarted(const QString FriendlyName) = 0;
        /**
         * @brief GetCameraState 获取相机状态
         * @param FriendlyName
         * @return
         */
        virtual bool GetCameraState(const QString FriendlyName) = 0;
        /**
         * @brief DispRate 显示帧率
         */
        virtual QString DispRate() = 0;
        /**
         * @brief DispImage 显示图片
         */
        virtual QImage DispImage() = 0;
        /**
         * @brief startGetFrameBuffer 按照采集一帧图像，可以按照设定的频率采集
         * @param queue 结果数据
         */
        virtual HSCameraError startGetFrameBuffer(FrameImage& frame) = 0;
        // 获取当前获取到的图像是第几帧，从0开始
        virtual int GetCurrentFrameCount() = 0;
    };

}
    // 用于创建对象的函数（DLL 导出函数）
    extern "C" __declspec(dllexport) CameraNameSpace::HSCameraInterface* createCameraObject();

#endif // HSCAMERAINTERFACE_H
