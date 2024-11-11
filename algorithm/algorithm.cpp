#include "algorithm.h"
#include <QDir>
#include <QDebug>
#include <opencv2/opencv.hpp>
#include "processtile.h"

Algorithm::Algorithm()
{
    proPtr = std::make_shared<ProcessTile>();
}

Algorithm::~Algorithm()
{}

//拼图
void Algorithm::init(JigsawPuzzleDataPack pack,
                  cv::Mat& image1,
                  cv::Mat& image2,
                  cv::Mat& image3)
{
    cv::Mat mat00 = pack.mat0[0];
    cv::Mat mat10 = pack.mat1[0];
    CameraCropArg arg0 = pack.packages.args[0];
    CameraCropArg arg1 = pack.packages.args[0];
    image1 = Algorithm::HorizontalPuzzle(pack.mat0[0],
                                         pack.mat1[0],
                                         arg0,
                                         arg1);
    image2 = Algorithm::HorizontalPuzzle(pack.mat0[1],
                                         pack.mat1[1],
                                         arg0,
                                         arg1);
    image3 = Algorithm::HorizontalPuzzle(pack.mat0[2],
                                         pack.mat1[2],
                                         arg0,
                                         arg1);
}

void Algorithm::RegisterResultCallback(CallbackFun func)
{
    mainFunction = func;//执行函数
}

void Algorithm::SyncExecu(int& currentFrameCount,
                      cv::Mat& image1,
                      cv::Mat& image2,
                      cv::Mat& image3)
{
    std::vector<std::shared_ptr<NewDefectUnitData>> frameGlassResult;
    // proPtr->CV_DefectsDetected(image1,image2,image3,length,width,imagePath);//多线程处理
    std::shared_ptr<std::thread> processThread = std::make_shared<std::thread>(&ProcessTile::CV_DefectsDetected,
                                            proPtr.get(),
                                            image1,
                                            image2,
                                            image3,
                                            currentFrameCount);
    threadMap.insert(std::make_pair(currentFrameCount,processThread));
    if (threadMap[currentFrameCount]->joinable()) {
        threadMap[currentFrameCount]->join();
        NewGlassResult result;
        proPtr->getDefectResult(currentFrameCount, result);
        mainFunction(result);
    }
}

void Algorithm::TestExecu(cv::Mat& image)
{
    double length = 0;
    double width = 0;
    QString Path;
    std::vector<std::shared_ptr<NewDefectUnitData>> frameGlassResult;
    proPtr->CV_DefectsDetected(image,image,image,0);
    NewGlassResult result;
    proPtr->getDefectResult(0, result);
}

void Algorithm::Stop()
{

}

void Algorithm::Exit()
{

}

cv::Mat Algorithm::HorizontalPuzzle(cv::Mat mat00,
                                    cv::Mat mat10,
                                    CameraCropArg arg0,
                                    CameraCropArg arg1)
{
    cv::Mat resultmat00 = mat00(cv::Rect(arg0.leftPixCrop,
                                         arg0.topPixCrop,
                                         mat00.cols-arg0.leftPixCrop-arg0.rightPixCrop,
                                         mat00.rows-arg0.topPixCrop-arg0.bottomPixCrop));
    cv::Mat resultmat10 = mat10(cv::Rect(arg1.leftPixCrop,
                                         arg1.topPixCrop,
                                         mat10.cols-arg1.leftPixCrop-arg1.rightPixCrop,
                                         mat10.rows-arg1.topPixCrop-arg1.bottomPixCrop));
    cv::Mat result(mat00.rows, mat00.cols, mat00.type());

    // 将第一个图像复制到结果图像的左侧
    resultmat00.copyTo(result(cv::Rect(0, 0, resultmat00.cols, resultmat00.rows)));

    // 将第二个图像复制到结果图像的右侧
    resultmat10.copyTo(result(cv::Rect(resultmat00.cols, 0, resultmat10.cols, resultmat10.rows)));
    return result;
}
