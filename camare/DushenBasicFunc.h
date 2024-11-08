#ifndef DUSHENBASICFUNC_H
#define DUSHENBASICFUNC_H

#include <QDir>
#include <QFileInfo>
#include <QGraphicsPixmapItem>
#include <QGraphicsView>
#include <QMutex>
#include <QObject>
#include <QThread>
#include <QTime>
#include <QTimer>
#include <unordered_map>
#include <mutex>
#include <queue>
#include "HSCameraInterface.h"
#include "DVPCamera.h"

// 线程安全的unorder_map
template<typename K, typename V>
class ThreadSafeUnorderedMap {
public:
    // 插入键值对
    void insert(const K& key, const std::queue<V>& value) {
        std::lock_guard<std::mutex> guard(mutex_);
        unordered_map_.insert(std::make_pair(key, value));
    }
    // 根据键获取值
    bool get(const K& key, std::queue<V>& value) {
        std::lock_guard<std::mutex> guard(mutex_);
        auto it = unordered_map_.find(key);
        if (it!= unordered_map_.end()) {
            value = it->second;
            return true;
        }
        return false;
    }
    // 删除键值对
    void erase(const K& key) {
        std::lock_guard<std::mutex> guard(mutex_);
        unordered_map_.erase(key);
    }
    // 往队列中push
    void push(const K& key, V& value) {
        std::lock_guard<std::mutex> guard(mutex_);
        auto it = unordered_map_.find(key);
        if (it!= unordered_map_.end()) {
            std::queue<V> tmp = it->second;
            tmp.push(value);
            unordered_map_[key] = tmp;
        } else {
            std::queue<V> tmp;
            tmp.push(value);
            unordered_map_[key] = tmp;
        }
    }
    // 从队列中pop
    V pop(const K& key) {
        std::lock_guard<std::mutex> guard(mutex_);
        auto it = unordered_map_.find(key);
        V value;
        if (it!= unordered_map_.end()) {
            std::queue<V> tmp = it->second;
            if (!tmp.empty()) {
                value = tmp.front();
                tmp.pop();
            }
        }
        return value;
    }
    // 判断指定handle的队列是否为空
    bool empty(const K& key) {
       std::lock_guard<std::mutex> guard(mutex_);
        auto it = unordered_map_.find(key);
        if (it!= unordered_map_.end()) {
            std::queue<V> tmp = it->second;
            return tmp.empty();
        }
        return true;
    }
private:
    std::unordered_map<K, std::queue<V>> unordered_map_;
    std::mutex mutex_;
};

// 回调函数返回的结构体
struct callbackDataStruct{
    dvpUint64 uFrameID;
    dvpUint64 uTimestamp;
    dvpInt32 iWidth;
    dvpInt32 iHeight;
    dvpUint32 uBytes;
    dvpImageFormat format;
    void* buffer;
    callbackDataStruct():uFrameID(0)
                       , uTimestamp(0)
                       , iWidth(0)
                       , iHeight(0)
                       , uBytes(0)
                       , format(dvpImageFormat::FORMAT_B16_G16_R16)
                       , buffer(nullptr){}
};


class DushenBasicFunc : public CameraNameSpace::HSCameraInterface
{
public:
    explicit DushenBasicFunc(){}
    virtual ~DushenBasicFunc(){}

    bool IsValidHandle(dvpHandle handle);                                       //检查相机是否存在
    void IsMonoCamera(dvpHandle handle);                                        //检查是否为黑白相机
    void InitSpinExpoTime();                                                    //初始化曝光时间
    void InitSpinGain();                                                        //初始化增益
    void InitFrameCount();                                                      //初始化帧次
    void InitImageHeight();                                                     //初始化相机高度
    void InitAEMode();
    void InitAETarget();
    void InitTrigger();                                                         //初始化trigger
    void InitROIMode();
    void InitTargetFormat();
    void InitColorSolution();
    int WIDTH_BYTES(int BitCount, int Width);


public:
    virtual CameraNameSpace::HSCameraError InitCamera(DushenCameraArgs args) override;
    virtual unsigned int getCameraCounts() override;
    virtual std::vector<QString> getCameraFriendlyNames() override;
    virtual QString getCurrentCameraFriendlyName() override;
    virtual bool IsScanned(const QString FriendlyName) override;
    virtual bool IsOpened(const QString FriendlyName) override;
    virtual CameraNameSpace::HSCameraError StopFunc(const QString FriendlyName) override;
    virtual CameraNameSpace::HSCameraError Closefunc(const QString FriendlyName) override;
    virtual bool SearchCamera(const QString FriendlyName) override;
    virtual CameraNameSpace::HSCameraError OpenFunc(const QString FriendlyName) override;
    virtual CameraNameSpace::HSCameraError LoadIni(const QString FriendlyName) override;
    virtual CameraNameSpace::HSCameraError ScanFunc(const QString FriendlyName) override;
    virtual CameraNameSpace::HSCameraError ShowProperty(const QString FriendlyName,HWND windowsID) override;
    virtual CameraNameSpace::HSCameraError TriggerFunc(const QString FriendlyName) override;
    virtual CameraNameSpace::HSCameraError SaveIni(const QString FriendlyName) override;
    virtual CameraNameSpace::HSCameraError setFieldSelectedView(int field) override;
    virtual CameraNameSpace::HSCameraError setSoftTriggerFlag(bool flag) override;
    virtual CameraNameSpace::HSCameraError StartFunc(const QString FriendlyName) override;
    virtual bool IsStarted(const QString FriendlyName) override;
    virtual bool GetCameraState(const QString FriendlyName) override;
    virtual QString DispRate() override;
    virtual QImage DispImage() override;
    virtual CameraNameSpace::HSCameraError startGetFrameBuffer(FrameImage& imageunit) override;
    virtual int GetCurrentFrameCount() override;// 获取当前获取到的图像是第几帧，从0开始

private:
    dvpQuickRoi QuickRoiDetail;
    QString QuickRoiDetailInfo[16];
    dvpUint32 QuickRoiSel = 0;              //分辨率模式索引
    dvpUint32 ColorSolutionSel = 0;
    bool bTrigStatus =  false;
    bool m_IsOpened = false;
    bool CameraState = false;               //相机状态：true：start,false:stop
    bool m_IsStarted = false;
    bool bMono;
    QString strFrameCount;                  // 相机获取到的图像帧数
    QString strFilePath;                    // 保存图像时用到的完整路径
    QString strDir;                         // 图像保存的路径
    QString strLoadPath;
    QString m_FriendlyName;
    dvpStreamState state;
    bool m_IsScanned = false;               // 是否扫描
    dvpUint32 m_CameraCounts = 0;           // 相机数量
    dvpCameraInfo info[16];                 // 相机信息
    int FieldNumberSet;                     // 场的数量
    std::atomic<int> frameSignal;           // 帧信号：1开始拍照，0结束拍照
    dvpHandle m_handle = 0;                 // 相机句柄
    dvpFrameCount FrameCount;
    QThread* m_pThread = nullptr;
    double m_expo;                          // 曝光时间
    double m_gain;                          // 相机增益
    double m_height;                        // 拍照行数
    int m_framecount;                       // 帧次
    QTimer* timer;                          // 定时器
    byte** Last_Buffer;                     // 图片buffer缓存
    QImage m_ShowImage;                     // 相机界面显示小图
    QString m_currentFriendlyName;          // 当前对象的相机名称
    QString m_currentIniPath;               // 当前相机配置文件路径
    int m_FieldSelectedView = 1;            // 相机选择的场
    bool m_SoftTriggerFlag =  false;        // 软触发信号
    int ImageOffset = 200;                  // 偏移行数
    int ImageLineSize = 0;                  // 一行像元的字节数
    static int m_currentFrameCount;            // 当前帧数
public:
    static ThreadSafeUnorderedMap<dvpHandle,callbackDataStruct> MapSS;// handle->buffer
    static dvpInt32 OnGetFrame(dvpHandle handle, dvpStreamEvent event, void* pContext, dvpFrame* pFrame, void* pBuffer);
};

#endif // DUSHENBASICFUNC_H
