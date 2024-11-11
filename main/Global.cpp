#include "Global.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <QSettings>
#include <QFile>
#include <QImage>

GlobalParamter::GlobalParamter()
    :CurrentRecipe(""),
     SystemName(""),
     camDefineNum(0),
     Camera0Name(""),
     Camera1Name(""),
     Camera2Name(""),
     Camera3Name(""),
     serverIp(""),
     serverPort(0),
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
     FrameSignalOutput(0),
     currentsystem(SYSTEMSTATUS::INIT)
{}

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
        qDebug() << "An unknown error occurred.";
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


