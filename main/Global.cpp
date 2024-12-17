#include "Global.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <QSettings>
#include <QFile>
#include <QImage>

GlobalParamter::GlobalParamter(){}

GlobalParamter::~GlobalParamter(){}

GlobalParamter& GlobalParamter::getInstance()
{
    static GlobalParamter param;
    return param;
}

QString GlobalParamter::GetParamterFromIniFile(QString fullpath, QString key)
{
    QString result = "default";
    try{
        QSettings settings(fullpath, QSettings::IniFormat);
        // 检查文件是否存在
        if (QFile::exists(settings.fileName())) {
            result = settings.value(key, "default").toString();
            if (result == "default") {
                qDebug() << "Key not found in config file. Using default value.";
            } else {
                qDebug() << "Value from config file: " << result;
            }
        }
    } catch (...) {
        qDebug() << "GlobalParamter::GetParamterFromIniFile => An unknown error occurred.";
        // 获取当前的异常信息
        std::exception_ptr eptr = std::current_exception();
        if (eptr) {
            try {
                std::rethrow_exception(eptr);
            } catch (const std::exception& ex) {
                qDebug() << "Exception: " << ex.what();
            }
        }
    }
    return result;
}

void GlobalParamter::SetParamterIntoIniFile(QString fullpath, QString key, QString value)
{
    QSettings settings(fullpath, QSettings::IniFormat);
    // 修改特定键的值
    settings.beginGroup("system");
    settings.setValue(key, value);
    settings.endGroup();
}

QImage GlobalParamter::cvMat2QImage(const cv::Mat& mat)
{
    // 8-bits unsigned, NO. OF CHANNELS = 1
    if(mat.type() == CV_8UC1)
    {
        QImage image(mat.cols, mat.rows, QImage::Format_Indexed8);
        // Set the color table (used to translate colour indexes to qRgb values)
        image.setColorCount(256);
        for(int i = 0; i < 256; i++)
        {
            image.setColor(i, qRgb(i, i, i));
        }
        // Copy input Mat
        uchar *pSrc = mat.data;
        for(int row = 0; row < mat.rows; row ++)
        {
            uchar *pDest = image.scanLine(row);
            memcpy(pDest, pSrc, mat.cols);
            pSrc += mat.step;
        }
        return image;
    }
    // 8-bits unsigned, NO. OF CHANNELS = 3
    else if(mat.type() == CV_8UC3)
    {
        // Copy input Mat
        const uchar *pSrc = (const uchar*)mat.data;
        // Create QImage with same dimensions as input Mat
        QImage image(pSrc, mat.cols, mat.rows, mat.step, QImage::Format_RGB888);
        return image.rgbSwapped();
    }
    else if(mat.type() == CV_8UC4)
    {
        qDebug() << "CV_8UC4";
        // Copy input Mat
        const uchar *pSrc = (const uchar*)mat.data;
        // Create QImage with same dimensions as input Mat
        QImage image(pSrc, mat.cols, mat.rows, mat.step, QImage::Format_ARGB32);
        return image.copy();
    }
    else
    {
        qDebug() << "ERROR: Mat could not be converted to QImage.";
        return QImage();
    }
}
cv::Mat GlobalParamter::QImage2cvMat(QImage image)
{
    cv::Mat mat;
    qDebug() << image.format();
    switch(image.format())
    {
    case QImage::Format_Grayscale8:
        mat = cv::Mat(image.height(), image.width(), CV_8UC1, (void*)image.constBits(), image.bytesPerLine());
        break;
    case QImage::Format_ARGB32:
    case QImage::Format_RGB32:
    case QImage::Format_ARGB32_Premultiplied:
        mat = cv::Mat(image.height(), image.width(), CV_8UC4, (void*)image.constBits(), image.bytesPerLine());
        break;
    case QImage::Format_RGB888:
        mat = cv::Mat(image.height(), image.width(), CV_8UC3, (void*)image.constBits(), image.bytesPerLine());
        cv::cvtColor(mat, mat, cv::COLOR_BGR2RGB);
        break;
    case QImage::Format_Indexed8:
        mat = cv::Mat(image.height(), image.width(), CV_8UC1, (void*)image.constBits(), image.bytesPerLine());
        break;
    }
    return mat;
}

void GlobalParamter::ReassignValue(SignalControl signalctrl)
{
    SystemName = signalctrl.systemName;
    camDefineNum = signalctrl.CamareNumber;
    Camera0Name = signalctrl.Camare0Name;
    Camera1Name = signalctrl.Camare1Name;
    Camera2Name = signalctrl.Camare2Name;
    Camera3Name = signalctrl.Camare3Name;
    serverIp = signalctrl.ServerIP;
    serverPort = signalctrl.ServerPort;
    YAccuracy = signalctrl.YAccuracy;
    XCamera0Accuracy = signalctrl.XCamera0Accuracy;
    XCamera1Accuracy = signalctrl.XCamera1Accuracy;
    Camera0Frame = signalctrl.Camera0Frame;
    Camera0PhotoRow = signalctrl.Camera0PhotoRow;
    Camera0ExposureTime = signalctrl.Camera0ExposureTime;
    Camera0Gain = signalctrl.Camera0Gain;
    Camera1Frame = signalctrl.Camera1Frame;
    Camera1PhotoRow = signalctrl.Camera1PhotoRow;
    Camera1ExposureTime = signalctrl.Camera1ExposureTime;
    Camera1Gain = signalctrl.Camera1Gain;
    Camera2Frame = signalctrl.Camera2Frame;
    Camera2PhotoRow = signalctrl.Camera2PhotoRow;
    Camera2ExposureTime = signalctrl.Camera2ExposureTime;
    Camera2Gain = signalctrl.Camera2Gain;
    Camera3Frame = signalctrl.Camera3Frame;
    Camera3PhotoRow = signalctrl.Camera3PhotoRow;
    Camera3ExposureTime = signalctrl.Camera3ExposureTime;
    Camera3Gain = signalctrl.Camera3Gain;
    // 控制器参数
    EncodePulseFilterUs = signalctrl.EncodePulseFilterUs;
    PhotoelectricSensorFiltering = signalctrl.PhotoelectricSensorFiltering;
    WheelEncoderPhotoPulse = signalctrl.WheelEncoderPhotoPulse;
    EncoderMode = signalctrl.EncoderMode;
    SolenoidValve1DownDelay = signalctrl.SolenoidValve1DownDelay;
    SolenoidValve1UpDelay = signalctrl.SolenoidValve1UpDelay;
    SolenoidValve2DownDelay = signalctrl.SolenoidValve2DownDelay;
    SolenoidValve2UpDelay = signalctrl.SolenoidValve2UpDelay;
    WheelAEncoder = signalctrl.WheelAEncoder;
    WheelBEncoder = signalctrl.WheelBEncoder;
    ErrorPhotoCount = signalctrl.ErrorPhotoCount;
    // 光源控制器参数
    LightField1GlowTime = signalctrl.LightField1GlowTime;
    LightField2GlowTime = signalctrl.LightField2GlowTime;
    LightField3GlowTime = signalctrl.LightField3GlowTime;
    LightField4GlowTime = signalctrl.LightField4GlowTime;
    LightSignalSynchronizationDelayRegister = signalctrl.LightSignalSynchronizationDelayRegister;
    PhotoMode = signalctrl.PhotoMode;
    LightCameraEnable = signalctrl.LightCameraEnable;
    WorkMode = signalctrl.WorkMode;
    LightSourcePulseEndPointRegister = signalctrl.LightSourcePulseEndPointRegister;
    SyncPulsePeriodRegister = signalctrl.SyncPulsePeriodRegister;
    CameraFrameSignalTriggerDelay = signalctrl.CameraFrameSignalTriggerDelay;
    TimelapseAfterPhotoShootEnd = signalctrl.TimelapseAfterPhotoShootEnd;
    SelectedLightFieldNumber = signalctrl.SelectedLightFieldNumber;
    FrameSignalOutput = signalctrl.FrameSignalOutput;
}
