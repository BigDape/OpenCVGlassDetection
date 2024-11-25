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
    virtual void Puzzle(int cameraNumber,
                        std::vector<cv::Mat> mat0,
                        std::vector<cv::Mat> mat1,
                        std::vector<CameraCropArg> args,
                        cv::Mat& image1,
                        cv::Mat& image2,
                        cv::Mat& image3) override;
    virtual void RegisterResultCallback(CallbackFun func) override;
    virtual void SyncExecu(int& currentFrameCount,
                       cv::Mat& image1,
                       cv::Mat& image2,
                       cv::Mat& image3) override;
    virtual void TestExecu(cv::Mat& image) override;
    virtual void Stop() override;
    virtual void Exit() override;

private:
    /**
     * @brief stitchFieldImages 拼接单个光场的两个相机的照片
     * @param [in] arg0  相机0的裁剪参数，通过界面标定而来
     * @param [in] mat00 相机0拍摄到的原始图片
     * @param [in] arg1  相机1的裁剪参数，通过界面标定而来
     * @param [in] mat10 相机1拍摄的原始图片
     * @param [out] concatImage 结果数据，一帧拼接好的单个光场的图片
     */
    void stitchFieldImages(CameraCropArg arg0,
                           cv::Mat mat00,
                           CameraCropArg arg1,
                           cv::Mat mat10,
                           cv::Mat& concatImage);

private:
    std::shared_ptr<ProcessTile> proPtr;
    std::queue<NewGlassResult> ResultQue; //结果队列
    CallbackFun mainFunction; //显示结果函数
};
#endif // ALGORITHM_H
