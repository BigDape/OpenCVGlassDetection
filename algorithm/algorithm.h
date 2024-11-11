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
    virtual void init(JigsawPuzzleDataPack pack,
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
    cv::Mat HorizontalPuzzle(cv::Mat mat00,
                                        cv::Mat mat10,
                                        CameraCropArg arg0,
                                        CameraCropArg arg1);

private:
    std::shared_ptr<ProcessTile> proPtr;
    std::queue<NewGlassResult> ResultQue; //结果队列
    std::unordered_map<int,std::shared_ptr<std::thread>> threadMap; //线程hash表，帧->线程
    CallbackFun mainFunction; //显示结果函数
};
#endif // ALGORITHM_H
