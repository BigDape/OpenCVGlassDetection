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
void Algorithm::Puzzle(int cameraNumber,
                    std::vector<cv::Mat> mat0,
                    std::vector<cv::Mat> mat1,
                    std::vector<CameraCropArg> args,
                    cv::Mat& image1,
                    cv::Mat& image2,
                    cv::Mat& image3)
{
    if (args.size() >= 2 && mat0.size() == 3 && mat1.size() == 3) {//检查参数，两个相机和图像光场数量一致
        Algorithm::stitchFieldImages(args[0],
                                     mat0[0],
                                     args[1],
                                     mat1[0],
                                     image1); // 拼接投射亮场图像
        Algorithm::stitchFieldImages(args[0],
                                     mat0[1],
                                     args[1],
                                     mat1[1],
                                     image2);// 拼接反射亮场图像
        Algorithm::stitchFieldImages(args[0],
                                     mat0[2],
                                     args[1],
                                     mat1[2],
                                     image3);// 拼接反射暗场图像

    } else {
        qDebug()<<"error: 标定参数或者图像参数错误。";
    }
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
    std::thread t1 = std::thread(&ProcessTile::CV_DefectsDetected, proPtr.get(), image1,image2,image3,currentFrameCount,mainFunction);
    t1.detach();
    //proPtr->CV_DefectsDetected(image1,image2,image3,currentFrameCount,mainFunction);
}

void Algorithm::TestExecu(cv::Mat& image)
{
    proPtr->CV_DefectsDetected(image,image,image,777,mainFunction);
}

void Algorithm::Stop()
{

}

void Algorithm::Exit()
{

}

void Algorithm::stitchFieldImages(CameraCropArg arg0,
                                  cv::Mat mat00,
                                  CameraCropArg arg1,
                                  cv::Mat mat10,
                                  cv::Mat& concatImage)
{
    try{
        // 相机0处理
        int x0 = arg0.leftPixCrop;
        int y0 = arg0.topPixCrop;
        int width0 = mat00.cols - arg0.leftPixCrop - arg0.rightPixCrop;
        int height0 = mat00.rows - arg0.topPixCrop - arg0.bottomPixCrop;
        cv::Rect crop0 = cv::Rect(x0, y0, width0, height0);
        qDebug()<<"x0 = "<<x0 <<",y0 = "<<y0<<",width0 ="<<width0<<", height0 ="<<height0;
        cv::Mat mat00_crop = mat00(crop0);// 裁剪后的图片
        // 相机1处理
        int x1 = arg1.leftPixCrop;
        int y1 = arg1.topPixCrop;
        int width1 = mat10.cols - arg1.leftPixCrop - arg1.rightPixCrop;
        int height1 = mat10.rows - arg1.topPixCrop - arg1.bottomPixCrop;
        cv::Rect crop1 = cv::Rect(x1,y1,width1,height1);
        qDebug()<<"x1 = "<<x1 <<",y1 = "<<y1<<",width1 ="<<width1<<", height1 ="<<height1;
        cv::Mat mat10_crop = mat10(crop1);

        qDebug()<<"mat00_crop.rows ="<<mat00_crop.rows<<", mat10_crop.rows ="<<mat10_crop.rows;
        if (mat00_crop.cols >0 && mat10_crop.cols > 0 &&  mat00_crop.rows == mat10_crop.rows && mat00_crop.rows > 0 && mat10_crop.rows > 0) {
            cv::hconcat(mat00_crop,mat10_crop,concatImage);
        } else {
            qDebug()<<"mat00_crop.cols ="<<mat00_crop.cols
                    <<", mat10_crop.cols ="<<mat10_crop.cols
                    <<", mat00_crop.rows="<<mat00_crop.rows
                    <<", mat10.rows="<<mat10.rows
                    <<", mat00_crop.rows ="<<mat00_crop.rows
                    <<", mat10.rows ="<<mat10.rows;
            qDebug()<<"拼接参数不符合要求。";
        }
    } catch(...) {
        qDebug()<<"Algorithm::stitchFieldImages throw unknow exception.";
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

}

