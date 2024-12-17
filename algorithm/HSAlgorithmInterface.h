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
        typedef std::function<void (NewGlassResult result)> CallbackFun; //回调函数
        virtual ~HSAlgorithmInterface(){}
        virtual void HorizontalPuzzle(int currentframe,
                            std::vector<cv::Mat> mat0,
                            std::vector<cv::Mat> mat1,
                            std::vector<CameraCropArg> args,
                            cv::Mat& image1,
                            cv::Mat& image2,
                            cv::Mat& image3) = 0;
        virtual void VerticalPuzzle(NewGlassResult result,
                                    cv::Mat projectionImage,
                                    cv::Mat reflectionLightImage,
                                    cv::Mat reflectionDarkImage,
                                    cv::Mat& glassRegion0,
                                    cv::Mat& glassRegion1,
                                    cv::Mat& glassRegion3) = 0;

        virtual void setTemplate(std::vector<QString> modelPaths) = 0;
        virtual bool onMatchSilkscreen(cv::Mat image1,
                               cv::Mat image2,
                               cv::Mat targetImage,
                               std::vector<GlassSizeInfo2>& sizeRes,
                               double minimumSimilarity) = 0;

        virtual bool onMatchHole(cv::Mat image0,
                                 cv::Mat image1,
                                 cv::Mat image2,
                                 std::vector<GlassSizeInfo2>& sizeRes) = 0;

        virtual int PartGlassAB(cv::Rect rect, double pixAccuracy, bool& AisLeft) = 0;

        virtual void RegisterResultCallback(CallbackFun func) = 0;

        virtual NewGlassResult SyncExecu(int& currentFrameCount,
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
