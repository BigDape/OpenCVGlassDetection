#ifndef HSALGORITHMINTERFACE_H
#define HSALGORITHMINTERFACE_H

#include <vector>
#include <QString>
#include <windows.h>
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include "HSTool.h"


namespace HSAlgorithmNamespace
{
    // 抽象接口类
    class HSAlgorithmInterface
    {
    public:
        typedef std::function<void (NewGlassResult& result)> CallbackFun; //回调函数
        virtual ~HSAlgorithmInterface(){}

        virtual void init(JigsawPuzzleDataPack pack,
                          cv::Mat& image1,
                          cv::Mat& image2,
                          cv::Mat& image3) = 0;

        virtual void RegisterResultCallback(CallbackFun func) = 0;

        virtual void SyncExecu(int& currentFrameCount,
                           cv::Mat& image1,
                           cv::Mat& image2,
                           cv::Mat& image3) = 0;

        virtual void TestExecu(cv::Mat& image) = 0;

        virtual void Stop() = 0;

        virtual void Exit() = 0;
    };
}
// 用于创建对象的函数（DLL 导出函数）
extern "C" __declspec(dllexport) HSAlgorithmNamespace::HSAlgorithmInterface* createAlgorithmObject();

#endif // HSALGORITHMINTERFACE_H
