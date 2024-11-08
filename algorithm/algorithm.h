#ifndef ALGORITHM_H
#define ALGORITHM_H

#include <opencv2/opencv.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include "HSAlgorithmInterface.h"

class ProcessTile;
class Algorithm: public HSAlgorithmNamespace::HSAlgorithmInterface
{
public:
    Algorithm();
    virtual ~Algorithm();
    virtual void init(std::vector<cv::Mat>& mat0, std::vector<cv::Mat>& mat1, CropArgPackage packages) override;
    virtual void Execu(int currentFrameCount) override;
    virtual void TestExecu(cv::Mat& image) override;
    virtual void GetFrameResult(NewGlassResult& result) override;
    virtual void Stop() override;
    virtual void Exit() override;
private:
    cv::Mat HorizontalPuzzle(cv::Mat mat00,
                                        cv::Mat mat10,
                                        CameraCropArg arg0,
                                        CameraCropArg arg1);

private:
    std::shared_ptr<ProcessTile> proPtr;
    cv::Mat image1;                         // 透视场图像
    cv::Mat image2;                         // 反射亮场
    cv::Mat image3;                         // 反射暗场
    std::queue<NewGlassResult> ResultQue; //结果队列
};

#endif // ALGORITHM_H
