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
        virtual ~HSAlgorithmInterface(){}

        virtual void init(std::vector<cv::Mat>& mat0, std::vector<cv::Mat>& mat1, CropArgPackage packages) = 0;

        virtual void Execu(int currentFrameCount) = 0;

        virtual void TestExecu(cv::Mat& image) = 0;

        virtual void GetFrameResult(NewGlassResult& result) = 0;

        virtual void Stop() = 0;

        virtual void Exit() = 0;
    };
}
// 用于创建对象的函数（DLL 导出函数）
extern "C" __declspec(dllexport) HSAlgorithmNamespace::HSAlgorithmInterface* createAlgorithmObject();

#endif // HSALGORITHMINTERFACE_H
