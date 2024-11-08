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
void Algorithm::init(std::vector<cv::Mat>& mat0, std::vector<cv::Mat>& mat1, CropArgPackage packages)
{
    cv::Mat mat00 = mat0[0];
    cv::Mat mat10 = mat1[0];
    CameraCropArg arg0 = packages.args[0];
    CameraCropArg arg1 = packages.args[0];
    image1 = Algorithm::HorizontalPuzzle(mat0[0],
                                         mat1[0],
                                         arg0,
                                         arg1);
    image2 = Algorithm::HorizontalPuzzle(mat0[1],
                                         mat1[1],
                                         arg0,
                                         arg1);
    image3 = Algorithm::HorizontalPuzzle(mat0[2],
                                         mat1[2],
                                         arg0,
                                         arg1);
}

void Algorithm::Execu(int currentFrameCount)
{
    double length = 0;
    double width = 0;
    QString imagePath = "";
    std::vector<std::shared_ptr<NewDefectUnitData>> frameGlassResult;
    proPtr->CV_DefectsDetected(image1,image2,image3,length,width,imagePath);
    NewGlassResult data;
    data.res = proPtr->getDefectResult();
    data.currentFrameCount = currentFrameCount;
    data.pixGlassLength = length;
    data.pixGlassWidth = width;
    data.FaceQimagePath = imagePath;
    ResultQue.push(data);
}

void Algorithm::TestExecu(cv::Mat& image)
{
    double length = 0;
    double width = 0;
    QString Path;
    std::vector<std::shared_ptr<NewDefectUnitData>> frameGlassResult;
    proPtr->CV_DefectsDetected(image,image2,image3,length,width,Path);
}

void Algorithm::GetFrameResult(NewGlassResult& result)
{
    result = ResultQue.front();
    ResultQue.pop();
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
