#include "OpenCVAlgorithm.h"
#include <QDir>
#include <QDebug>
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/dnn.hpp>
#include <QDir>
#include <chrono>
#include <opencv2/core/ocl.hpp>
//#include <opencv2/cudaarithm.hpp>
#include <opencv2/cudaimgproc.hpp>
#include <opencv2/dnn/dnn.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/core/cuda.hpp>
#include <opencv2/dnn.hpp>
#include <chrono>
#include <opencv2/cudawarping.hpp>
#include <opencv2/cudafilters.hpp>
#include <cuda_runtime.h>
#include <device_launch_parameters.h>
#include <vector>
#include <opencv2/core/cuda.hpp>
#include <math.h>
#include <HSTool.h>
#include "MatchTemplate.h"
#include "RoundHole.h"
#include "Yolov8DL.h"
#include "ClassifyMachine.h"

//检出缺陷滤波
#define AREATHRESHOLD 25
#define MODEL_NAME "/model/best.onnx"
#define EDGETHICKNESS 256


OpenCVAlgorithm::OpenCVAlgorithm()
{
    // if (yolov8DLPtr == nullptr)
    //     yolov8DLPtr = std::make_shared<Yolov8DL>();
    if (roundHolePtr == nullptr)
        roundHolePtr = std::make_shared<RoundHole>();
    if (matchTemplatePtr == nullptr)
        matchTemplatePtr = std::make_shared<MatchTemplate>();
    if (classifyMachinePtr == nullptr)
        classifyMachinePtr = std::make_shared<ClassifyMachine>();

    int DeviceCount = cv::cuda::getCudaEnabledDeviceCount();
    if (DeviceCount < 1) {
        isGPU = false;
        std::cout << "No GPU support." << std::endl;
    } else {
        std::cout << "GPU support available. Device Count ="<<DeviceCount<< std::endl;
        cv::cuda::setDevice(0);
        isGPU = true;
    }
    cv::setNumThreads(28);
}

OpenCVAlgorithm::~OpenCVAlgorithm()
{}

//拼图
void OpenCVAlgorithm::HorizontalPuzzle(int currentframe,
                                        std::vector<cv::Mat> mat0,
                                        std::vector<cv::Mat> mat1,
                                        std::vector<CameraCropArg> args,
                                        cv::Mat& image1,
                                        cv::Mat& image2,
                                        cv::Mat& image3)
{
    try {
        if (args.size() >= 2 && mat0.size() == 3 && mat1.size() == 3) {//检查参数，两个相机和图像光场数量一致
            OpenCVAlgorithm::stitchFieldImages(currentframe,
                                     args[0],
                                     mat0[0],
                                     args[1],
                                     mat1[0],
                                     image1); // 拼接投射亮场图像
            OpenCVAlgorithm::stitchFieldImages(currentframe,
                                     args[0],
                                     mat0[1],
                                     args[1],
                                     mat1[1],
                                     image2);// 拼接反射亮场图像
            OpenCVAlgorithm::stitchFieldImages(currentframe,
                                     args[0],
                                     mat0[2],
                                     args[1],
                                     mat1[2],
                                     image3);// 拼接反射暗场图像

        } else {
            qDebug()<<"error: 标定参数或者图像参数错误。";
        }
    } catch(...) {
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

void OpenCVAlgorithm::VerticalPuzzle(NewGlassResult result,
                            cv::Mat projectionImage,
                            cv::Mat reflectionLightImage,
                            cv::Mat reflectionDarkImage,
                            cv::Mat& glassRegion0,
                            cv::Mat& glassRegion1,
                            cv::Mat& glassRegion2)
{
    if (projectionImage.rows == 0 || reflectionLightImage.rows == 0 || reflectionDarkImage.rows == 0) {
        return;
    }
    try{
        if (result.part == CV_GLASSPART::UNKNOW || result.part == CV_GLASSPART::EMPTY) {
            return;
        } else if (result.part == CV_GLASSPART::HEAD) { // 头部玻璃
            if (projectionImage.rows > 0 && reflectionLightImage.rows > 0 && reflectionDarkImage.rows > 0) {// 赋值第一片玻璃
                glassRegion0 = projectionImage;
                glassRegion1 = reflectionLightImage;
                glassRegion2 = reflectionDarkImage;
            }
        } else if (result.part == CV_GLASSPART::MIDDLE) {// 中部玻璃
            if (glassRegion0.cols == projectionImage.cols) {
                cv::vconcat(glassRegion0,projectionImage,glassRegion0);
            } else {
                qDebug()<<"m_glass0.cols != projectionImage.cols";
            }
            if (glassRegion1.cols == reflectionLightImage.cols) {
                cv::vconcat(glassRegion1,reflectionLightImage,glassRegion1);
            } else {
                qDebug()<<"m_glass1.cols != reflectionLightImage.cols";
            }
            if (glassRegion2.cols == reflectionDarkImage.cols) {
                cv::vconcat(glassRegion2,reflectionDarkImage,glassRegion2);
            } else {
                qDebug()<<"m_glass2.cols != reflectionDarkImage.cols";
            }
        } else if (result.part == CV_GLASSPART::TAIL || result.part == CV_GLASSPART::WholeGlass) { //尾部玻璃
            if (glassRegion0.cols == projectionImage.cols) {
                cv::vconcat(glassRegion0,projectionImage,glassRegion0);
            } else {
                qDebug()<<"m_glass0.cols != projectionImage.cols";
            }
            if (glassRegion1.cols == reflectionLightImage.cols) {
                cv::vconcat(glassRegion1,reflectionLightImage,glassRegion1);
            } else {
                qDebug()<<"m_glass1.cols != reflectionLightImage.cols";
            }
            if (glassRegion2.cols == reflectionDarkImage.cols) {
                cv::vconcat(glassRegion2,reflectionDarkImage,glassRegion2);
            } else {
                qDebug()<<"m_glass2.cols != reflectionDarkImage.cols";
            }
    } else {
        qDebug()<<"未知玻璃区域";
    }
    } catch(...) {
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

void OpenCVAlgorithm::RegisterResultCallback(CallbackFun func)
{
    mainFunction = func;//执行函数
}

NewGlassResult OpenCVAlgorithm::SyncExecu(int& currentFrameCount,
                      cv::Mat& image1,
                      cv::Mat& image2,
                      cv::Mat& image3)
{
    auto start = std::chrono::high_resolution_clock::now();// 开始时间
    NewGlassResult result = MeddiCookerDefectsDetected(image1,image2,image3,currentFrameCount);
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> duration = end - start;
    qDebug() << "OpenCVAlgorithm Finish time：" << duration.count() << " ms";
    return result;
}

void OpenCVAlgorithm::TestExecu(ClassifyParam param)
{
    if (classifyMachinePtr != nullptr) {
        int classid = classifyMachinePtr->IdentificationDefect(param);
        qDebug()<<"classid ="<<classid;
    }
}

void OpenCVAlgorithm::Stop()
{

}

void OpenCVAlgorithm::Exit()
{

}

void OpenCVAlgorithm::stitchFieldImages(int currentframe,
                                  CameraCropArg arg0,
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
            // 最后减掉200行剩余行数
            int hasDeletePix = 200 - arg0.topPixCrop - arg0.bottomPixCrop;//重复的200行需要减去的行数
            if (hasDeletePix > 0) {
                cv::Rect rect(0,hasDeletePix,concatImage.cols, concatImage.rows-hasDeletePix);//image已经被转置90度
                concatImage = concatImage(rect);//裁剪若干列重复行数
            }
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
        qDebug()<<"OpenCVAlgorithm::stitchFieldImages throw unknow exception.";
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

void OpenCVAlgorithm::setTemplate(std::vector<QString> modelPaths)
{
    if (matchTemplatePtr != nullptr) {
        matchTemplatePtr->setTemplate(modelPaths);
    }
}

bool OpenCVAlgorithm::onMatchSilkscreen(cv::Mat image1,
                               cv::Mat image2,
                               cv::Mat targetImage,
                               std::vector<GlassSizeInfo2>& sizeRes,
                               double minimumSimilarity)
{
    bool result = false;
    if (matchTemplatePtr != nullptr) {
        result =matchTemplatePtr->onMatchSilkscreen(image1,image2,targetImage,sizeRes,minimumSimilarity);
    }
    return result;
}

bool OpenCVAlgorithm::onMatchHole(cv::Mat image0,
                         cv::Mat image1,
                         cv::Mat image2,
                         std::vector<GlassSizeInfo2>& sizeRes)
{
    try {
        // 转为灰度图
        cv::Mat grayImage;
        if (image0.channels() != 1) {
            cv::cvtColor(image0, grayImage, cv::COLOR_BGR2GRAY);
        } else {
            grayImage = image0;
        }

        // 使用阈值函数进行二值化（这里相当于把灰度值大于10的设为255，不大于的设为0），优化了手动循环遍历赋值的过程
        cv::Mat binaryImage;
        threshold(grayImage, binaryImage, 10, 255, cv::THRESH_BINARY);

        // 使用OpenCV自带的连通组件分析函数，比自定义的简单函数更高效和完善
        cv::Mat labels, stats, centroids;
        int numLabels = connectedComponentsWithStats(binaryImage, labels, stats, centroids);

        // 这里可以根据后续需求对标记好的连通区域进行进一步处理，比如查看区域面积、位置等信息
        int maxArea = 0;
        int maxIndex = -1;
        for (int i = 1; i < numLabels; ++i) {  // 跳过背景标签0
            int pixArea = stats.at<int>(i, cv::CC_STAT_AREA);//面积，最大面积是背景还有比较小的是缺陷
            if(pixArea > maxArea){
                maxArea = pixArea;
                maxIndex = i;
            }

            int pixX = stats.at<int>(i, cv::CC_STAT_LEFT) ;
            int pixY = stats.at<int>(i, cv::CC_STAT_TOP);
            int pixWidth = stats.at<int>(i, cv::CC_STAT_WIDTH) ;
            int pixHeight = stats.at<int>(i, cv::CC_STAT_HEIGHT);
            cv::Rect rect(pixX,pixY,pixWidth,pixHeight);

            cv::Mat sImage0 = image0(rect);
            cv::Mat sImage1 = image1(rect);
            cv::Mat sImage2 = image2(rect);
            GlassSizeInfo2 hole;
            hole.time = QDateTime::currentDateTime().toString("MM-dd HH:mm:ss");
            hole.sizeType = ("孔");
            hole.sizeLevel = "OK";
            hole.Pixlength = rect.height;
            hole.PixWidth = rect.width;
            hole.PixMarginsX = rect.x + rect.width/2;
            hole.PixMarginsY = rect.y + rect.height/2;
            hole.imagePath0 = SyncSaveImage(sImage0);
            hole.imagePath1 = SyncSaveImage(sImage1);
            hole.imagePath2 = SyncSaveImage(sImage2);
            hole.Region0 = sImage0;
            hole.Region1 = sImage1;
            hole.Region2 = sImage2;
            hole.rect = rect;           // 坐标信息
            sizeRes.push_back(hole);

            qDebug()<<"siyin.type ="<<hole.sizeType
                     <<", siyin.Path0 ="<<hole.imagePath0
                     <<", siyin.Path1 ="<<hole.imagePath1
                     <<", siyin.Path2 ="<<hole.imagePath2;
            qDebug() << "质心x坐标: " << centroids.at<double>(i, 0);
            qDebug() << "质心y坐标: " << centroids.at<double>(i, 1) ;
        }
        return true;
    } catch(...) {
        std::exception_ptr eptr = std::current_exception();
        if (eptr) {
            try {
                std::rethrow_exception(eptr);
            } catch (const std::exception& ex) {
                qDebug() << __LINE__ <<" Exception: " << ex.what();
            }
        }
        return false;
    }
}


int OpenCVAlgorithm::PartGlassAB(cv::Rect rect, double pixAccuracy, bool& AisLeft)
{
    //获取到丝印的坐标，对玻璃区域进行划分
    int x = rect.x;
    int width = rect.width;
    int Pix10cm = (100/pixAccuracy);
    if (x > width/2) { // A区在玻璃的右侧，右侧边到（x-10cm,image.cols）为A区，（0，x-10cm）为B区
        AisLeft = false;
        return (x-Pix10cm);
    } else { // A区在玻璃的左侧，（0，x+width+10cm）为A区，(x+width+10cm, image.cols)为B区
        AisLeft = true;
        return (x+ width+Pix10cm);
    }
}

void OpenCVAlgorithm::bathroomDefectsDetected(cv::Mat& image,
                             int currentframe,
                             std::function<void (NewGlassResult result)> mainFunc)
{
    auto start = std::chrono::high_resolution_clock::now();// 开始时间

    int imageRows = image.rows;
    int imageCols = image.cols;
    CV_GLASSPART part = CV_GLASSPART::UNKNOW;
    qDebug()<<"imageRows ="<<imageRows<<",imageCols="<<imageCols;

    if (imageRows > 0 ) {/*30ms*/
        std::vector<GlassSizeInfo2> sizeRes;//尺寸界面的结果
        //
        // 边缘检测
        //
        cv::Mat cannyEdges;
        OpenCVAlgorithm::EdgeDetectionFunction(image, cannyEdges);

        std::vector<std::vector<cv::Point> > contours;
        cv::findContours(cannyEdges, contours, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_NONE); //找轮廓 138ms

        // 求轮廓的最大外接矩形(该矩形与上下左右边平行)
        double maxArea = 0;
        int maxAreaContourIndex = -1;
        cv::RotatedRect maxminAreaRect;    // 带倾斜角度的最大外接矩形
        cv::Rect maxBoundingRect(0,0,0,0); // 平行于坐标轴的最大外接矩形

        qDebug()<<"contours.size() = "<<contours.size();
        if (contours.size() <= 1) {
            qDebug()<<"背景图片或者无效图片";
            return;
        }
        std::vector<int> XXs;
        int maxWidth = 0;

        for(int i = 0; i < (int)contours.size(); i++) {/* 20ms */
            std::vector<cv::Point> contour = contours[i];
            // 获取轮廓的最大外接矩形
            cv::RotatedRect rect = cv::minAreaRect(contour);
            cv::Rect boundingRect = rect.boundingRect();
            double area = boundingRect.width * boundingRect.height;
            XXs.push_back(boundingRect.x);
            XXs.push_back(boundingRect.x + boundingRect.width);
            cv::Scalar color(256, 256, 256);
            cv::rectangle(image, boundingRect, color, 2);//在原图上画框
            if (boundingRect.width > maxWidth) {
                maxArea = area;
                maxAreaContourIndex = i;
                maxminAreaRect = rect;
                maxBoundingRect = boundingRect;
            }
        }


        qDebug()<<"maxBoundingRect.x ="<<maxBoundingRect.x
                 <<",maxBoundingRect.y="<<maxBoundingRect.y
                 <<"maxBoundingRect.w ="<<maxBoundingRect.width
                 <<",maxBoundingRect.height="<<maxBoundingRect.height;

        std::vector<cv::Point2f> oldvertices; // 原始图像四个顶点坐标，用于仿射变换扶正图像
        std::vector<cv::Point2f> newvertices; // 修正倾斜图像四个顶点坐标，用于仿射变换扶正图像
        if ( maxBoundingRect.width < imageCols/8) {//区域宽度占比小于图像宽度的1/8,则认定为玻璃中部
            part = CV_GLASSPART::MIDDLE;
            int PythagoreanSide = maxBoundingRect.width; //勾股定理短直角边
            qDebug()<<"PythagoreanSide ="<<PythagoreanSide;
            int minValue = *std::min_element(XXs.begin(), XXs.end());
            int MaxValue = *std::max_element(XXs.begin(),XXs.end());
            qDebug()<<"minValue ="<<minValue<<"MaxValue = "<<MaxValue;
            // 最大矩形边框重新赋值
            maxBoundingRect.x = minValue;
            maxBoundingRect.y = 0;
            maxBoundingRect.width = MaxValue - minValue;
            maxBoundingRect.height = imageRows;
            // 中部玻璃平行四边形面部的四个顶点提前重新赋值
            float midGlassWidth = MaxValue - minValue - PythagoreanSide; //平行四边形的上下边宽度
            cv::Point2f P1; //平行四边形的左上顶点
            P1.x = minValue;//也是最大外接矩形的x坐标
            P1.y = 0; //中部玻璃为0
            oldvertices.push_back(P1);
            cv::Point2f P2; //平行四边形的右上顶点
            P2.x = minValue + midGlassWidth; //P1x坐标加上宽度
            P2.y = 0;
            oldvertices.push_back(P2);
            cv::Point2f P3; //平行四边形的右下顶点
            cv::Point2f P4; //平行四边形的左下顶点
            if (maxminAreaRect.angle > 90) {//玻璃上部向右倾斜
                P4.x = minValue - PythagoreanSide;
                P4.y = imageRows;
            } else { //玻璃上部向左倾斜
                P4.x = minValue + PythagoreanSide;
                P4.y = imageRows;
            }
            P3.x = P4.x + midGlassWidth;
            P3.y = imageRows;
            oldvertices.push_back(P3);
            oldvertices.push_back(P4);// 必须按照顺序压入
        } else { // 此帧是玻璃的头部和尾部区
            if (maxBoundingRect.y <= 0) {
                part = CV_GLASSPART::TAIL;
            } else {
                part = CV_GLASSPART::HEAD;
            }
        }
        // 边界处理
        if (maxBoundingRect.x < 0) {
            maxBoundingRect.x = 0;
        }
        if (maxBoundingRect.y < 0) {
            maxBoundingRect.y = 0;
        }
        if ((maxBoundingRect.x + maxBoundingRect.width) > imageCols) {
            maxBoundingRect.width = imageCols - maxBoundingRect.x;
        }
        if ((maxBoundingRect.y + maxBoundingRect.height) > imageRows) {
            maxBoundingRect.height = imageRows - maxBoundingRect.y;
        }
        qDebug()<<"maxAreaContourIndex ="<<maxAreaContourIndex;
        qDebug()<<"maxBoundingRect.x ="<<maxBoundingRect.x
                 <<",maxBoundingRect.y="<<maxBoundingRect.y
                 <<"maxBoundingRect.w ="<<maxBoundingRect.width
                 <<",maxBoundingRect.height="<<maxBoundingRect.height;
        cv::Mat tmp1 = image(maxBoundingRect);
        SyncSaveImage(tmp1,"D:/testopencv/tmp1.jpg");

        //
        // 找到玻璃区域
        //
        if (maxAreaContourIndex != -1) {
            calculateBoundingRectangle(part, maxBoundingRect,maxminAreaRect, oldvertices, newvertices);//计算出图片扶正的顶点矩阵
            // 仿射变换原图
            cv::Mat warpedImage;//仿射变换后的图片
            std::thread th1 = std::thread(&OpenCVAlgorithm::affineTransformation,
                                          this,
                                          oldvertices,
                                          newvertices,
                                          image,
                                          std::ref(warpedImage));
            /*1088ms*/
            // 仿射变换二值图像
            cv::Mat warpedEageImage;//仿射变换后的二值图片
            std::thread th2 = std::thread(&OpenCVAlgorithm::affineTransformation,
                                          this,
                                          oldvertices,
                                          newvertices,
                                          cannyEdges,
                                          std::ref(warpedEageImage));
            th1.join();
            th2.join();
            /* 仿射变换165ms */
            SyncSaveImage(warpedImage,"D:/testopencv/warpedImage.jpg");
            SyncSaveImage(warpedEageImage,"D:/testopencv/warpedEageImage.jpg");
            qDebug()<<"最大外轮廓的面积："<<maxArea;
            /*1746ms*/
            //
            // 获取面积最大的轮廓的边界矩形
            //
            int newX0 = newvertices[0].x;
            int newY0 = newvertices[0].y;
            int width = newvertices[2].x-newvertices[0].x;
            int height = newvertices[2].y-newvertices[0].y;
            if (height > warpedImage.rows - newY0) {
                height = warpedImage.rows - newY0-1;
            }
            cv::Rect boundingRect1 = cv::Rect(newX0,newY0, width,height);
            qDebug()<<"boundingRect1 x="<<boundingRect1.x<<",y="<<boundingRect1.y<<",w="<<boundingRect1.width<<",h="<<boundingRect1.height;
            // 裁剪只有玻璃的图像，减去了背景
            cv::Mat croppedImage = warpedImage(boundingRect1);
            cv::Mat croppedEdgeImage =warpedEageImage(boundingRect1);

            SyncSaveImage(croppedImage,"D:/testopencv/croppedImage.jpg");
            SyncSaveImage(croppedEdgeImage,"D:/testopencv/croppedEdgeImage.jpg");
            //
            // 计算长宽
            //
            double glassLength = croppedImage.rows;
            double glassWidth = croppedImage.cols;
            qDebug()<<"glassLength = "<<glassLength <<",glassWidth="<<glassWidth;

            //
            // 边部缺陷检出
            //

            int topAddition = maxBoundingRect.y==0 ? 0 : maxBoundingRect.y; //图像上边没有玻璃边框
            int bottomAddition = maxBoundingRect.height == warpedImage.rows ? 0 : maxBoundingRect.height; //图像下边没有玻璃边框
            int leftAddition =  maxBoundingRect.x==0 ? 0 :  maxBoundingRect.x;//图像左边没有玻璃边框
            int rightAddition = (maxBoundingRect.x + maxBoundingRect.width) >= warpedImage.cols ? 0 : maxBoundingRect.x + maxBoundingRect.width;//图像右边没有玻璃边框
            std::vector<regionInfor> edgeregions;
            OpenCVAlgorithm::edgeDefectDetection(croppedImage,
                                             edgeregions,
                                             topAddition,
                                             bottomAddition,
                                             leftAddition,
                                             rightAddition,
                                             sizeRes);           /* 120ms */

            //
            // 面部缺陷检出
            //

            cv::Mat framCroppedImage;
            CuttinGlassDdges(croppedImage, framCroppedImage);//将图片的四周640个像素切割（去边）
            cv::Mat framcroppedEdgeImage;
            CuttinGlassDdges(croppedEdgeImage, framcroppedEdgeImage);//将图片的四周640个像素切割（去边）


            SyncSaveImage(framCroppedImage,"D:/testopencv/framCroppedImage.jpg");
            SyncSaveImage(framcroppedEdgeImage,"D:/testopencv/framcroppedEdgeImage.jpg");
            //
            // 将面部相邻的缺陷联通起来
            // 将相连的域联通
            //
            cv::Mat labels;
            cv::Mat stats;
            cv::Mat centroids;
            cv::Mat resizedImage;

            if (isGPU) {
                cv::cuda::GpuMat gpuframcroppedEdgeImage(framcroppedEdgeImage);
                cv::cuda::GpuMat gpuresizedImage;
                cv::cuda::resize(gpuframcroppedEdgeImage, gpuresizedImage, cv::Size(framcroppedEdgeImage.cols / 2, framcroppedEdgeImage.rows / 2));
                gpuresizedImage.download(resizedImage);
            } else {
                cv::resize(framcroppedEdgeImage, resizedImage, cv::Size(framcroppedEdgeImage.cols / 2, framcroppedEdgeImage.rows / 2));
            }


            int numComponents = connectedComponentsWithStats(resizedImage, labels, stats, centroids);//连通域

            //
            // 找到代表背景的元素（通常是面积最大的那个），去除掉
            //

            std::vector<ConnectedComponent> components;
            int backgroundIndex = 0;
            int maxArea = stats.at<int>(0, cv::CC_STAT_AREA)*4;
            for (int i = 0; i < numComponents; i++) {
                ConnectedComponent component;
                component.rect = cv::Rect(stats.at<int>(i, cv::CC_STAT_LEFT)*2,
                                          stats.at<int>(i, cv::CC_STAT_TOP)*2,
                                          stats.at<int>(i, cv::CC_STAT_WIDTH)*2,
                                          stats.at<int>(i, cv::CC_STAT_HEIGHT)*2);
                component.area = stats.at<int>(i, cv::CC_STAT_AREA)*4;
                components.push_back(component);

                int area = stats.at<int>(i, cv::CC_STAT_AREA) * 4;
                if (area > maxArea) {
                    maxArea = area;
                    backgroundIndex = i;
                }
            }
            components.erase(components.begin()+backgroundIndex);//找到代表背景的元素（通常是面积最大的那个），去除掉
            qDebug()<<"背景的元素:backgroundIndex = " <<backgroundIndex<<",maxArea ="<<maxArea <<", components =" <<components.size();

            // 合并新的区域
            for (int i = 0; i < (int)components.size(); i++) {
                ConnectedComponent iComponent = components[i];
                for (int j = i + 1; j < (int)components.size(); j++) {
                    ConnectedComponent jComponent = components[j];
                    if (isClose(iComponent, jComponent, 20)) {//最短欧式距离20个像元
                        int minX = iComponent.rect.x > jComponent.rect.x ? jComponent.rect.x : iComponent.rect.x;
                        int minY = iComponent.rect.y > jComponent.rect.y ? jComponent.rect.y : iComponent.rect.y;
                        int maxX = iComponent.rect.x + iComponent.rect.width > jComponent.rect.x + jComponent.rect.width ? (jComponent.rect.x + jComponent.rect.width) : (iComponent.rect.x + iComponent.rect.width);
                        int maxY = iComponent.rect.y + iComponent.rect.height > jComponent.rect.y + jComponent.rect.height ? (iComponent.rect.y + iComponent.rect.height) : (jComponent.rect.y + jComponent.rect.height);
                        cv::Rect mergedRect(minX, minY, maxX - minX, maxY - minY);
                        iComponent.rect = mergedRect;
                        iComponent.area = iComponent.rect.area();
                        iComponent.x = (minX + maxX) /2;
                        iComponent.y = (minY + maxY) /2;
                        components.erase(components.begin()+j);//删除jComponent元素，
                        components[i] = iComponent;
                        if (i==0){//合并完成，从前两个再遍历一遍
                            i =-1;
                        } else {
                            i = i-2;
                        }
                        break;
                    }
                }
            }

            /*2042ms*/
            //
            // 保存到本地
            //

            std::vector<regionInfor> defectRegions;
            std::unordered_map<int,cv::Rect> rectMap;
            for (int i = 0; i < (int)components.size(); i++) {
                // 单个缺陷的矩形框
                cv::Rect rect = components[i].rect;
                if (components[i].rect.area() >= AREATHRESHOLD ){
                    double similarityValue = std::min<double>((double)components[i].rect.width ,(double)components[i].rect.height) / max((double)components[i].rect.width ,(double)components[i].rect.height);
                    if (components[i].rect.width >= 120 && components[i].rect.height >= 120 && similarityValue>0.8){//可能是圆
                        qDebug()<<"similarityValue = "<<similarityValue;
                        cv::Mat circle = framcroppedEdgeImage(components[i].rect);
                        double diameter;
                        HoughCircleRadius(circle, diameter);
                        GlassSizeInfo2 hole;
                        hole.Pixlength = diameter;
                        hole.PixWidth = diameter;
                        hole.PixMarginsX = rect.x + 32 + diameter/2;
                        hole.PixMarginsY = rect.y + 32 + diameter/2;
                        hole.Region0 = circle;
                        hole.sizeType = ("孔");
                        hole.imagePath0 =SyncSaveImage(hole.Region0);
                        sizeRes.push_back(hole);
                        rect.x = rect.x + 32; //rect是面部坐标，转化为玻璃坐标
                        rect.y = rect.y + 32;
                        cv::Scalar color(256, 0, 0);
                        cv::rectangle(croppedImage, rect, color, 2);//在原图上画框
                    }
                } else {
                    continue;
                }
                // 剪裁YOLO模型大小的图像
                cv::Rect yoloRect = getDefectStandardRect(framCroppedImage, components[i].x,components[i].y,640,640);
                // 去除重复剪裁图像
                int hashKey = PointHashCode(yoloRect.x,yoloRect.y);
                if (rectMap.find(hashKey) != rectMap.end()){
                    continue;
                }
                rectMap.insert(std::pair<int,cv::Rect>(hashKey,yoloRect));
                cv::Mat defectRegion = framCroppedImage(yoloRect);
                regionInfor info;
                info.region = defectRegion;
                info.path = SyncSaveImage(defectRegion);
                info.rect = yoloRect;
                defectRegions.push_back(info);
            }
            rectMap.clear();
            qDebug()<<"components.size()="<<components.size();

            /*2079ms*/

            // 装置90度异步保存图片
            QString filePath = "D:/testopencv/croppedImageMain_"+QString::number(currentframe)+ ".jpg";
            cv::Mat NewCroppedImage;
            cv::transpose(croppedImage, NewCroppedImage);
            cv::flip(NewCroppedImage, NewCroppedImage, 0);
            QString imagePath = SyncSaveImage(NewCroppedImage,filePath);
            // 合并边图和面部图，进行分类
            std::vector<regionInfor> mergeRegions;
            mergeRegions.reserve(edgeregions.size() + defectRegions.size());
            mergeRegions.insert(mergeRegions.end(), edgeregions.begin(), edgeregions.end());
            mergeRegions.insert(mergeRegions.end(), defectRegions.begin(), defectRegions.end());
            std::vector<GlassDefect2> unitResult;
            if (yolov8DLPtr != nullptr) {
                yolov8DLPtr->YoloDefectClassification(mergeRegions,unitResult);
            }
            NewGlassResult result;
            result.isEmpty = false;
            result.defectRes = unitResult;
            result.pixGlassLength = glassLength;
            result.pixGlassWidth = glassWidth;
            result.FaceQimagePath = imagePath;
            result.currentFrameCount = currentframe;
            result.sizeRes = sizeRes;
            result.glassRegion = NewCroppedImage;
            result.part = part;
            qDebug()<<"part ="<<part;
            mainFunc(result);
            auto end = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double, std::milli> duration = end - start;
            qDebug() << "Algorithm time：" << duration.count() << " ms";
        }
    } else {
        qWarning()<<"image1 row <= 0";
    }
}

void OpenCVAlgorithm::EdgeDetectionFunction(cv::Mat src, cv::Mat& dst)
{
    //
    // 边缘检测
    //
    cv::Mat grayImage;
    if (src.channels()!= 1) {
        cv::cvtColor(src, grayImage, cv::COLOR_BGR2GRAY);
    } else {
        grayImage = src;
    }

    // 滤波
    cv::Mat thresholdMat;
    cv::threshold(grayImage, thresholdMat,25,255,cv::THRESH_TOZERO);
    // 边缘检测
    cv::Mat EdgeResult;
    if (!isGPU) { //CPU
        cv::Canny(thresholdMat, EdgeResult, 20, 80);
    } else { // GPU 143ms
        cv::Ptr<cv::cuda::CannyEdgeDetector> cannyDetector = cv::cuda::createCannyEdgeDetector(30, 60,1,true);
        cv::cuda::GpuMat gpuInputImage(thresholdMat);
        cv::cuda::GpuMat gpuCannyEdges;
        cannyDetector->detect(gpuInputImage, gpuCannyEdges);
        gpuCannyEdges.download(EdgeResult);
    }
    // 膨胀
    cv::Mat dilatedImage;
    if (!isGPU) { // CPU
        cv::Mat element = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(2, 2));
        cv::dilate(EdgeResult, dilatedImage, element);//膨胀
    } else { // GPU /*46ms*/
        // 将边缘检测后的图像数据传输到GPU内存
        cv::cuda::GpuMat gpuCannyEdges;
        gpuCannyEdges.upload(EdgeResult);
        // 创建GPU上的结构元素
        cv::cuda::GpuMat gpudilatedImage;
        cv::Mat element = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(2, 2));
        cv::Ptr<cv::cuda::Filter> dilateFilter = cv::cuda::createMorphologyFilter(cv::MORPH_DILATE,CV_8U,element);//膨胀
        dilateFilter->apply(gpuCannyEdges,gpudilatedImage);
        gpudilatedImage.download(dilatedImage);// 将结果从GPU内存传输回主机内存
    }
    dst = dilatedImage;
    SyncSaveImage(dst,"D:/testopencv/EdgeResult.jpg");
}

void OpenCVAlgorithm::calculateBoundingRectangle(CV_GLASSPART part,
                                             cv::Rect maxBoundingRect,
                                             cv::RotatedRect Rect1,
                                             std::vector<cv::Point2f>& oldvertices,
                                             std::vector<cv::Point2f>& newvertices)
{
    //
    // 在原图上，四个顶点
    //
    if (part == CV_GLASSPART::HEAD || part == CV_GLASSPART::TAIL) {//玻璃头部或者尾部才能正确获取原图的四个顶点
        cv::Point2f P[4];
        Rect1.points(P);
        double maxsum = 0;
        double minsum = P[0].x + P[0].y;
        int minIndex = 0, maxIndex = 0;
        for (int  i =0 ; i < 4; ++i) {
            double sum =  P[i].x + P[i].y;
            if (sum >= maxsum) {
                maxIndex = i;
                maxsum = sum;
            }
            if (sum < minsum) {
                minIndex = i;
                minsum  = sum;
            }
        }
        oldvertices.push_back(P[minIndex]);
        qDebug()<<"oldvertices, X="<<P[minIndex].x<<",Y="<<P[minIndex].y;
        cv::Point2f P23[2];
        int p23Index = 0;
        for (int i=0; i<4;++i){
            if (i!= minIndex && i != maxIndex) {
                P23[p23Index] = P[i];
                p23Index++;
            }
        }
        if (P23[0].x > P23[1].x) {
            oldvertices.push_back(P23[0]);
            qDebug()<<"oldvertices, X="<<P23[0].x<<",Y="<<P23[0].y;
            oldvertices.push_back(P[maxIndex]);
            qDebug()<<"oldvertices, X="<<P[maxIndex].x<<",Y="<<P[maxIndex].y;
            oldvertices.push_back(P23[1]);
            qDebug()<<"oldvertices, X="<<P23[1].x<<",Y="<<P23[1].y;
        } else {
            oldvertices.push_back(P23[1]);
            qDebug()<<"oldvertices, X="<<P23[1].x<<",Y="<<P23[1].y;
            oldvertices.push_back(P[maxIndex]);
            qDebug()<<"oldvertices, X="<<P[maxIndex].x<<",Y="<<P[maxIndex].y;
            oldvertices.push_back(P23[0]);
            qDebug()<<"oldvertices, X="<<P23[0].x<<",Y="<<P23[0].y;
        }


    } else {//玻璃中部，oldvertices已经赋过值
        for (int  i =0 ; i < 4; ++i) {
            qDebug()<<"oldvertices, X="<<oldvertices[i].x<<",Y="<<oldvertices[i].y;
        }
    }

    //
    // 修正图的四个顶点
    //
    cv::Point2f Vertices0;
    Vertices0.x = maxBoundingRect.x;
    Vertices0.y = maxBoundingRect.y;
    newvertices.push_back(Vertices0);
    qDebug()<<"newvertices, X="<<Vertices0.x<<",Y="<<Vertices0.y;
    cv::Point2f Vertices1;
    Vertices1.x = maxBoundingRect.x + maxBoundingRect.width;
    Vertices1.y = maxBoundingRect.y;
    newvertices.push_back(Vertices1);
    qDebug()<<"newvertices, X="<<Vertices1.x<<",Y="<<Vertices1.y;
    cv::Point2f Vertices2;
    Vertices2.x = maxBoundingRect.x + maxBoundingRect.width;
    Vertices2.y = maxBoundingRect.y + maxBoundingRect.height;
    newvertices.push_back(Vertices2);
    qDebug()<<"newvertices, X="<<Vertices2.x<<",Y="<<Vertices2.y;
    cv::Point2f Vertices3;
    Vertices3.x = maxBoundingRect.x;
    Vertices3.y = maxBoundingRect.y + maxBoundingRect.height;
    newvertices.push_back(Vertices3);
    qDebug()<<"newvertices, X="<<Vertices3.x<<",Y="<<Vertices3.y;
    return;
}

// 仿射变换
void OpenCVAlgorithm::affineTransformation(std::vector<cv::Point2f> oldvertices,
                                       std::vector<cv::Point2f> newvertices,
                                       cv::Mat image,
                                       cv::Mat& warpedImage)
{
    // 假设斜着的矩形的四个顶点
    cv::Point2f srcPoints[4];
    srcPoints[0] = oldvertices[0];
    srcPoints[1] = oldvertices[1];
    srcPoints[2] = oldvertices[2];
    srcPoints[3] = oldvertices[3];

    // 目标矩形的四个顶点（正的矩形）
    cv::Point2f dstPoints[4];
    dstPoints[0] = newvertices[0];
    dstPoints[1] = newvertices[1];
    dstPoints[2] = newvertices[2];
    dstPoints[3] = newvertices[3];

    // 计算仿射变换矩阵
    cv::Mat warpMatrix = cv::getPerspectiveTransform(srcPoints, dstPoints);
    // 应用仿射变换
    if (!isGPU){
        cv::warpPerspective(image, warpedImage, warpMatrix, image.size());
    } else {
        cv::cuda::GpuMat gpuInput = cv::cuda::GpuMat(image);
        cv::cuda::GpuMat gpuOutput;
        int w = image.cols;
        int h = image.rows;
        cv::cuda::warpPerspective( gpuInput, gpuOutput, warpMatrix, cv::Size(w,h), cv::INTER_LINEAR , cv::BORDER_CONSTANT, 0, cv::cuda::Stream::Null() );
        gpuOutput.download(warpedImage);
    }
}

// region是玻璃区域
void OpenCVAlgorithm::edgeDefectDetection(cv::Mat& region,
                                      std::vector<regionInfor>& edgeRegionInfos,
                                      int topAddition,
                                      int bottomAddition,
                                      int leftAddition,
                                      int rightAddition,
                                      std::vector<GlassSizeInfo2>& results)
{
    //
    // 将边部全部切分，用来识别崩边和门夹
    //
    int regionRow = region.rows;
    int regionCol = region.cols;
    int id = 0; //序列id，和edgeRegionInfos下标相对应
    //
    // 沿着图像的最上边从左到右依次裁剪小图
    //
    auto start1 = std::chrono::high_resolution_clock::now();// 开始时间
    if (topAddition != 0) {
        for (int i =0; i < regionCol/640; ++i) {
            cv::Rect rect(i*640, 0, 640, 640);
            cv::Mat topEdgeRegion = region(rect);
            regionInfor info;
            info.id = id++;
            info.path = SyncSaveImage(topEdgeRegion);
            info.region = topEdgeRegion;
            edgeRegionInfos.push_back(info);
        }
        //不足256*256部分也截取
        if (regionCol%640 != 0) {
            int lastX = regionCol - (regionCol%640);
            cv::Rect rect(lastX, 0, regionCol%640, 640);
            cv::Mat topEdgeRegion = region(rect);
            if (topEdgeRegion.rows != 0 && topEdgeRegion.cols != 0) {
                regionInfor info;
                info.id = id++;
                info.path = SyncSaveImage(topEdgeRegion);
                info.region = topEdgeRegion;
                edgeRegionInfos.push_back(info);
            }
        }
    }
    auto end1 = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> duration1 = end1 - start1;
    qDebug() << "沿着图像的最上边裁剪小图 time：" << duration1.count() << " ms";
    //
    // 沿着图像的最右边开始从上往下裁剪小图
    //
    auto start2 = std::chrono::high_resolution_clock::now();// 开始时间
    if (rightAddition != 0) {
        std::vector<EdgeElement> Y1Y2X1X2;//存储门夹的坐标值
        for (int i = 1; i < regionRow/640; ++i) {
            cv::Rect rect(regionCol-640, i*640, 640, 640);
            cv::Mat rightEdgeRegion = region(rect);
            //DoorClampDetection(rightEdgeRegion,rect,id,Y1Y2X1X2);
            regionInfor info;
            info.id = id++;
            info.path = SyncSaveImage(rightEdgeRegion);
            info.region = rightEdgeRegion;
            edgeRegionInfos.push_back(info);
        }

        //Algorithm::DoorClampResultData(Y1Y2X1X2, edgeRegionInfos, results);
        if (regionRow%640 != 0) {
            int lastY = regionRow - (regionRow%640);
            cv::Rect rect(regionCol-640,lastY, 640, regionRow%640);
            cv::Mat rightEdgeRegion = region(rect);
            if (rightEdgeRegion.rows != 0 && rightEdgeRegion.cols != 0) {
                regionInfor info;
                info.id = id++;
                info.path = SyncSaveImage(rightEdgeRegion);
                info.region = rightEdgeRegion;
                edgeRegionInfos.push_back(info);
            }
        }
    }
    auto end2 = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> duration2 = end2 - start2;
    qDebug() << "沿着图像的最右边裁剪小图 time：" << duration2.count() << " ms";
    //
    // 沿着图像最下边缘开始裁剪小图
    //
    auto start3 = std::chrono::high_resolution_clock::now();// 开始时间
    if (bottomAddition != 0) {
        for (int i =0; i < regionCol/640 -1; ++i) {
            cv::Rect rect(i*640, regionRow - 640, 640, 640);
            cv::Mat bottomEdgeRegion = region(rect);
            regionInfor info;
            info.id = id++;
            info.path = SyncSaveImage(bottomEdgeRegion);
            info.region = bottomEdgeRegion;
            edgeRegionInfos.push_back(info);
        }
        if (regionCol%640 != 0) {
            int lastX = regionCol - (regionCol%640) - 640;
            cv::Rect rect(lastX, regionRow - 640, regionCol%640 , 640);
            cv::Mat bottomEdgeRegion = region(rect);
            if (bottomEdgeRegion.rows != 0 && bottomEdgeRegion.cols != 0) {
                regionInfor info;
                info.id = id++;
                info.path = SyncSaveImage(bottomEdgeRegion);
                info.region = bottomEdgeRegion;
                edgeRegionInfos.push_back(info);
            }
        }
    }
    auto end3 = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> duration3 = end3 - start3;
    qDebug() << "沿着图像的最下边裁剪小图 time：" << duration3.count() << " ms";
    //
    // 沿着图像的最左边开始裁剪小图
    //
    auto start4 = std::chrono::high_resolution_clock::now();// 开始时间
    if (leftAddition != 0) {
        std::vector<EdgeElement> Y1Y2X1X2;//存储门夹的坐标值
        for (int i = 1; i < regionRow/640 -1; ++i) {
            cv::Rect rect(0, i*640, 640, 640); //在图像上的坐标：X = 0, Y = i*640
            cv::Mat leftEdgeRegion = region(rect);
            //DoorClampDetection(leftEdgeRegion,rect,id,Y1Y2X1X2);
            QString path = "D:/testopencv/defect/" + QString::number(i) + ".jpg";
            regionInfor info;
            info.id = id++;
            info.path = SyncSaveImage(leftEdgeRegion,path);
            info.region = leftEdgeRegion;
            edgeRegionInfos.push_back(info);
        }//for (int i = 1; i < regionRow/640 -1; ++i)
        // 门夹数据拼接
        //Algorithm::DoorClampResultData(Y1Y2X1X2, edgeRegionInfos, results);
        if (regionRow % 640 != 0) {
            int lastY = regionRow - (regionRow%640) - 640;
            cv::Rect rect(0,lastY, 640, regionRow%640);
            cv::Mat leftEdgeRegion = region(rect);
            if (leftEdgeRegion.rows != 0 && leftEdgeRegion.cols != 0) {
                regionInfor info;
                info.id = id++;
                info.path = SyncSaveImage(leftEdgeRegion);
                info.region = leftEdgeRegion;
                edgeRegionInfos.push_back(info);
            }
        }
    }
    auto end4 = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> duration4 = end4 - start4;
    qDebug() << "沿着图像的最左边裁剪小图 time：" << duration4.count() << " ms";
}

void OpenCVAlgorithm::DoorClampDetection(cv::Mat& region,
                                     cv::Rect& rect,
                                     int id,
                                     std::vector<EdgeElement>& Y1Y2X1X2)
{
    // 计算水平投影（行投影）
    cv::Mat horizontalProjection;
    cv::reduce(region, horizontalProjection, 1, cv::REDUCE_SUM, CV_32S);

    // 计算水平投影的梯度变化
    cv::Mat gradient;
    for (int i = 0; i < horizontalProjection.rows - 1; ++i) {
        int diff = std::abs(horizontalProjection.at<int>(i+1, 0) - horizontalProjection.at<int>(i,0));
        gradient.push_back(diff);
    }

    // 求梯度变化值的最大值和次大值
    double maxValue;
    cv::Point maxLoc;
    cv::minMaxLoc(gradient, nullptr, &maxValue, nullptr, &maxLoc);
    gradient.at<int>(maxLoc.y, maxLoc.x) = 0;
    double secondMaxValue;
    cv::Point secondMaxLoc;
    cv::minMaxLoc(gradient, nullptr, &secondMaxValue, nullptr, &secondMaxLoc);

    // 判断最大值大于10000，且次大值下标与最大值下标的差值在50以上
    int menjiaY1 = 0,menjiaY2=0;
    if ((maxValue >= 10000 || secondMaxValue >=10000) && cv::abs(maxLoc.y - secondMaxLoc.y) > 50){//梯度差大于10000，且两个坐标差值大于50像素，认为找到门夹两条边
        menjiaY1 =  maxLoc.y;
        menjiaY2 = secondMaxLoc.y;
    } else if ((maxValue >= 10000 || secondMaxValue >=10000) &&  cv::abs(maxLoc.y - secondMaxLoc.y) < 50) {//梯度差大于10000，且两个坐标差值小于50像素，认为找到门夹一条边
        menjiaY1 =  maxLoc.y;
    }

    // 计算列投影
    cv::Mat verticalProjection;
    cv::reduce(region, verticalProjection, 0, cv::REDUCE_SUM, CV_32S);
    // 计算垂直投影的梯度变化
    cv::Mat Vgradient;
    for (int i = 0; i < verticalProjection.cols - 1; ++i) {
        int diff = verticalProjection.at<int>(0, i + 1) - verticalProjection.at<int>(0, i);
        Vgradient.push_back(diff);
    }
    // 求Vgradient梯度变化值的最大值和次大致
    double maxValueC;
    cv::Point maxValueLocC;
    double secondMaxValueC;
    cv::Point secondmaxValueLocC;
    cv::minMaxLoc(Vgradient, nullptr, &maxValueC, nullptr, &maxValueLocC);
    Vgradient.at<int>(maxLoc.y, maxLoc.x) = 0;
    cv::minMaxLoc(Vgradient, nullptr, &secondMaxValueC, nullptr, &secondmaxValueLocC);

    // 判断最大值大于10000，且次大值下标与最大值下标的差值在20以上
    int menjiaX1 = 0,menjiaX2 = 0;
    if ((maxValueC >= 10000 || secondMaxValueC >=10000) && cv::abs(maxValueLocC.x - secondmaxValueLocC.x) > 50){//梯度差大于10000，且两个坐标差值大于20像素，认为找到门夹两条边
        menjiaX1 =  maxValueLocC.x;
        menjiaX2 = secondmaxValueLocC.x;
    } else if ((maxValueC >= 10000 || secondMaxValueC >=10000) &&  cv::abs(maxValueLocC.x - secondmaxValueLocC.x) < 50) {//梯度差大于10000，且两个坐标差值小于20像素，认为找到门夹一条边
        menjiaX1 =  maxValueLocC.x;
    }
    cv::Vec4i GradientPoint(menjiaY1, menjiaY2, menjiaX1, menjiaX2);
    EdgeElement element;
    element.id = id;
    element.point2 = GradientPoint;
    element.rect = rect;
    Y1Y2X1X2.push_back(element);
}

void OpenCVAlgorithm::DoorClampResultData(std::vector<EdgeElement> Y1Y2X1X2,
                                      std::vector<regionInfor> edgeRegionInfos,
                                      std::vector<GlassSizeInfo2>& results)
{
    // 门夹数据拼接
    for (size_t i = 0; i < Y1Y2X1X2.size(); ++i) {
        EdgeElement element = Y1Y2X1X2[i];
        cv::Vec4i point = element.point2;
        if (point[0] > 0 && point[1] > 0 && cv::abs(point[0] - point[1]) > 50) {//门夹在一张小图上
            GlassSizeInfo2 result;
            result.Pixlength = cv::abs(point[0] - point[1]);
            result.PixMarginsX  = std::min<int>(point[0],point[1]) + element.rect.y + result.Pixlength/2;//边距X(门夹中心点到X轴坐标)
            if (point[2] > 0 && point[3] > 0 && cv::abs(point[2] - point[3]) > 50) {
                result.PixWidth = cv::abs(point[2] - point[3]);
                result.PixMarginsY = result.PixWidth /2 + element.rect.x;
                result.imagePath0 = edgeRegionInfos[element.id].path;
                result.Region0 = edgeRegionInfos[element.id].region;
                result.sizeType = ("门夹");
                qDebug()<<"class 1: MJPixHeight ="<<result.Pixlength
                         <<", MJPixWidth ="<<result.PixWidth
                         <<",MJMarginsX ="<<result.PixMarginsX
                         <<", MJMarginsY =" <<result.PixMarginsY
                         <<", MJPath = "<<result.imagePath0;
                results.push_back(result);
            }
        } else if (point[0] > 0 && point[1] == 0 && cv::abs(point[0] - point[1]) > 50) { // 门夹被切分在连续的小图上
            int gap = i; //间隔了几张小图,初始化为第几张小图
            for (size_t j = i+1; j < Y1Y2X1X2.size(); ++j) {
                EdgeElement elementNext = Y1Y2X1X2[j];
                cv::Vec4i pointNext = elementNext.point2;
                gap = j - i;
                if (pointNext[0] > 0 && pointNext[1] == 0) {//找到门夹的下一幅小图
                    GlassSizeInfo2 result;
                    int x1 = std::min<int>(std::min<int>(point[2],point[3]), std::min<int>(pointNext[2],pointNext[3]));
                    int x2 = max(max(point[2],point[3]), max(pointNext[2],pointNext[3]));
                    int y1 = 640 - point[0];
                    int y2 = pointNext[0];
                    result.Pixlength = y1 +y2 + (gap -1) * 640;//跨越多张图片的高
                    result.PixWidth = cv::abs(x1 + x2);
                    result.PixMarginsX  = std::min<int>(y1,y2)+ element.rect.y + result.Pixlength/2;
                    result.PixMarginsY = result.PixWidth/2 + element.rect.x;
                    //把多张图片拼接起来存储
                    cv::Mat Vresult;
                    if (j - i == 1) {
                        cv::Mat image1 = edgeRegionInfos[element.id].region;
                        cv::Mat image2 = edgeRegionInfos[elementNext.id].region;
                        cv::vconcat(image1, image2, Vresult);
                    } else if (j - i == 2) {
                        cv::Mat image1 = edgeRegionInfos[element.id].region;
                        cv::Mat image2 = edgeRegionInfos[element.id + 1].region;
                        cv::Mat image3 = edgeRegionInfos[element.id + 2].region;
                        cv::vconcat(image1, image2, Vresult);
                        cv::vconcat(Vresult, image3, Vresult);
                    }
                    result.Region0 = Vresult;
                    result.imagePath0 = SyncSaveImage(Vresult);
                    result.sizeType = ("门夹");
                    qDebug()<<"class 2: MJPixHeight ="<<result.Pixlength
                             <<", MJPixWidth ="<<result.PixWidth
                             <<",MJMarginsX ="<<result.PixMarginsX
                             <<", MJMarginsY =" <<result.PixMarginsY
                             <<", MJPath =" << result.imagePath0;
                    results.push_back(result);
                    i = j; // 跳到已经遍历过小图的下标，for循环会自动++。相当于从下一张图片开始遍历
                    break;
                }
            }
        }
    }
}

void OpenCVAlgorithm::CuttinGlassDdges(cv::Mat Frame, cv::Mat& result)
{
    cv::Rect FrameRect(32,32,Frame.cols-64,Frame.rows-64);
    result = Frame(FrameRect);
}

bool OpenCVAlgorithm::isClose(ConnectedComponent c1, ConnectedComponent c2, int threshold)
{
    if (c1.rect.x > c2.rect.x) {
        ConnectedComponent tmp = c1;
        c1 = c2;
        c2 = tmp;
    }
    if ( (c1.rect & c2.rect).area() > 0 ) {//两个矩形框重叠
        return true;
    } else { // 两个矩形相差threshold距离
        double dx = c2.rect.x - (c1.rect.x + c1.rect.width);
        double dy = c2.rect.y - (c1.rect.y + c1.rect.height);
        double distance = std::sqrt(dx * dx + dy * dy);
        if (distance > threshold) {
            return false;
        } else {//y方向
            return true;
        }
    }
}

void OpenCVAlgorithm::HoughCircleRadius(cv::Mat image, double& diameter)
{
    try {
        // 霍夫圆变换
        std::vector<cv::Vec3f> circles;
        // cv::cuda::GpuMat gpuInputImage(image);
        // cv::Ptr<cv::cuda::HoughCirclesDetector> dector = cv::cuda::createHoughCirclesDetector(1, image.rows/8, 100, 30, 80, 10000);
        // dector->detect(gpuInputImage,circles);

        /**
        * @brief cv::HoughCircles
        */
        qDebug()<<"start HoughCircles";
        // cv::HoughCircles(image, circles, cv::HOUGH_GRADIENT, 1, image.rows/8, 100, 30, 0, 0);
        // double result = 0;
        // qDebug()<<"circles.size() ="<<circles.size();
        // for (size_t i = 0; i < circles.size(); i++) {
        //     float x = circles[i][0];
        //     float y = circles[i][1];
        //     float radius = circles[i][2];
        //     if (radius*2 > result) {
        //         result = radius*2;
        //     }
        //     qDebug() << "Circle " << i + 1 << " center: (" << x << ", " << y << "), radius: " << radius;
        // }
        // diameter = result;
        // qDebug()<<"diameter = "<<diameter;
    } catch(...) {
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

cv::Rect OpenCVAlgorithm::getDefectStandardRect(cv::Mat& framCroppedImage,int pixX, int pixY, int pixLength, int pixWidth)
{
    int yoloRx = pixX - pixWidth/2;
    int yoloRy = pixY - pixLength/2;
    if ( yoloRx < 0 ) {
        yoloRx = 0;
    } else if((yoloRx + pixWidth) > framCroppedImage.cols) {
        yoloRx = framCroppedImage.cols - pixWidth -1;
    }
    if (yoloRy < 0) {
        yoloRy = 0;
    } else if (yoloRy + pixLength > framCroppedImage.rows) {
        yoloRy = framCroppedImage.rows - pixLength -1;
    }
    return cv::Rect(yoloRx,yoloRy,pixLength,pixWidth);
}

int OpenCVAlgorithm::PointHashCode(int x, int y)
{
    int hash = 7;
    hash = 71 * hash + x;
    hash = 71 * hash + y;
    return hash;
}

NewGlassResult OpenCVAlgorithm::MeddiCookerDefectsDetected(cv::Mat image0,
                                                           cv::Mat image1,
                                                           cv::Mat image2,
                                                           int currentframe)
{
    int imageRows = image2.rows;
    int imageCols = image2.cols;
    CV_GLASSPART part = CV_GLASSPART::UNKNOW;
    qDebug()<<"imageRows ="<<imageRows<<", imageCols ="<<imageCols;
    NewGlassResult result;
    if (imageRows > 0 ) {
        //
        // 边缘检测
        //
        cv::Mat clonedMat = image2.clone();
        cv::Mat edgeImage;
        EdgeDetectionFunction(image2, edgeImage);
        std::vector<std::vector<cv::Point> > contours;
        cv::findContours(edgeImage, contours, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_NONE); //找轮廓 138ms cv::CHAIN_APPROX_NONE cv::RETR_EXTERNAL

        qDebug()<<"contours.size() = "<<contours.size();
        if (contours.size() <= 2) {
            qDebug()<<"背景图片或者无效图片";
            return NewGlassResult();
        }

        //
        // 求轮廓的最大外接矩形(该矩形与上下左右边平行)
        //
        std::vector<int> XXs;
        std::vector<int> YYs;
        cv::RotatedRect maxminAreaRect;    // 带倾斜角度的最大外接矩形
        cv::Rect maxBoundingRect(0,0,0,0); // 平行于坐标轴的最大外接矩形
        int maxArea = -1;
        int maxIndex = -1;
        std::vector<ConnectedComponent> components;
        for(int i = 0; i < (int)contours.size(); i++) {/* 20ms */
            try {
                std::vector<cv::Point> contour = contours[i];
                for (int i = 0; i <(int)contour.size(); ++i) {
                    cv::Point point = contour[i];
                    XXs.push_back(point.x);
                    YYs.push_back(point.y);
                }
                cv::RotatedRect rect = cv::minAreaRect(contour); //获取轮廓的最大外接矩形
                cv::Rect boundingRect = rect.boundingRect();
                double area = boundingRect.width * boundingRect.height;
                if (area < 25) continue;
                if (maxArea <= area) {
                    maxArea = area;
                    maxIndex = i;
                }

                ConnectedComponent component;
                component.rect = boundingRect;
                component.area = area;
                component.x = boundingRect.x;
                component.y = boundingRect.y;
                components.push_back(component);

                cv::Scalar color(256, 256, 256);
                cv::rectangle(clonedMat, boundingRect, color, 1);//在原图上画框

                // 检出的缺陷小图
                int sImageX = std::max<int>(boundingRect.x,0);
                int sImageY = std::max<int>(boundingRect.y,0);
                int sImageW = std::min<int>(boundingRect.width,imageCols - sImageX);
                int sImageH = std::min<int>(boundingRect.height,imageRows - sImageY);
                cv::Rect sImageRect(sImageX,sImageY,sImageW,sImageH);
                cv::Mat sImage0 = image0(sImageRect);
                cv::Mat sImage1 = image1(sImageRect);
                cv::Mat sImage2 = image2(sImageRect);
                QString sImagePath0 = SyncSaveImage(sImage0);
                QString sImagePath1 = SyncSaveImage(sImage1);
                QString sImagePath2 = SyncSaveImage(sImage2);

                GlassDefect2 data;
                data.time = QDateTime::currentDateTime().toString("hh:mm:ss").toStdString().data();        // 时间
                data.defectLevel = "NG";
                data.pixLength = boundingRect.height;   // 长度像元数
                data.pixWidth = boundingRect.width;    // 宽度像元数
                data.pixX = boundingRect.x;        // 像元X
                data.pixY = boundingRect.y;        // 像元Y
                data.pixArea = area;     // 面积
                data.region0 = sImage0;
                data.region1 = sImage1;
                data.region2 = sImage2;
                data.imagePath0 = sImagePath0;
                data.imagePath1 = sImagePath1;
                data.imagePath2 = sImagePath2;  // 小图存储的地址
                data.rect = boundingRect;
                data.gregion = glassRegion::FACE;
                result.defectRes.push_back(data);
            } catch(...) {
                qDebug()<<"for throw a unknow Exception.";
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

        SyncSaveImage(clonedMat,"D:/testopencv/clonedMat.jpg");
        // 合并临近缺陷
        if (maxIndex != -1 && maxIndex < components.size())
            components.erase(components.begin()+maxIndex);//找到代表背景的元素（通常是面积最大的那个），去除掉

        OpenCVAlgorithm::MergeConnectedDomainDefects(components);//合并缺陷

        // 计算玻璃区域的最大外接矩形
        OpenCVAlgorithm::CalculateMaximumBoundingRectangle(XXs, YYs, imageRows, imageCols, maxBoundingRect);
        qDebug()<<"判断玻璃部分后: maxBoundingRect.x ="<<maxBoundingRect.x
                 <<",maxBoundingRect.y="<<maxBoundingRect.y
                 <<"maxBoundingRect.w ="<<maxBoundingRect.width
                 <<",maxBoundingRect.height="<<maxBoundingRect.height;

        // 判断玻璃的位置
        part = OpenCVAlgorithm::DetermineGlassPart(maxBoundingRect, imageRows);
        qDebug()<<"part ="<<part;

        cv::Mat tmp = clonedMat(maxBoundingRect);
        QString filenametmp1 = "D:/HVCache/cache/tmp"+ QString::number(currentframe)+".jpg";
        SyncSaveImage(tmp,filenametmp1);

        //
        // 裁剪玻璃区域
        //
        cv::Mat croppedImage0 = image0(maxBoundingRect);
        cv::Mat croppedImage1 = image1(maxBoundingRect);
        cv::Mat croppedImage = clonedMat(maxBoundingRect);
        cv::Mat croppedEdgeImage = edgeImage(maxBoundingRect);
        SyncSaveImage(croppedImage,"D:/HVCache/cache/croppedImage.jpg");
        SyncSaveImage(croppedEdgeImage,"D:/HVCache/cache/croppedEdgeImage.jpg");

        //
        // 将玻璃区域分割成边部和面部
        //
        std::vector<EdgeInfo> edges;
        cv::Mat FrameRegion;
        int topCoordinate = maxBoundingRect.y==0 ? 0 : maxBoundingRect.y; //图像上边没有玻璃边框
        int bottomCoordinate = (maxBoundingRect.y + maxBoundingRect.height) >= imageRows ? 0 : maxBoundingRect.y + maxBoundingRect.height; //图像下边没有玻璃边框
        int leftCoordinate =  maxBoundingRect.x==0 ? 0 :  maxBoundingRect.x;//图像左边没有玻璃边框
        int rightCoordinate = (maxBoundingRect.x + maxBoundingRect.width) >= imageCols ? 0 : maxBoundingRect.x + maxBoundingRect.width;//图像右边没有玻璃边框
        edgeDefectDetection2(croppedImage0,
                             croppedImage1,
                             croppedImage,
                             topCoordinate,
                             bottomCoordinate,
                             leftCoordinate,
                             rightCoordinate,
                             edges,
                             FrameRegion);

        //
        // 边部缺陷检出
        //
        std::vector<GlassDefect2> edgeDefects;
        OpenCVAlgorithm::edgePartDefect(edges, edgeDefects);
        result.defectRes.insert(result.defectRes.end(), edgeDefects.begin(), edgeDefects.end());

        //
        // 面部缺陷分类
        //
        for (auto& defect : result.defectRes) {
            ClassifyParam param;
            param.region = defect.region2;
            param.regionRect = defect.rect;
            if (classifyMachinePtr != nullptr) {
                int classid = classifyMachinePtr->IdentificationDefect(param);
                defect.typeID = classid;
                if (classid < (int)defectClasses.size()) {
                    defect.defectType = defectClasses[classid];
                }
            }
        }

        // 旋转180度用于显示
        cv::Mat NewCroppedImage;
        cv::transpose(croppedImage, NewCroppedImage);
        cv::flip(NewCroppedImage, NewCroppedImage, 0);
        QString filePath = "D:/testopencv/croppedImageMain_"+QString::number(currentframe)+ ".jpg";
        QString imagePath = SyncSaveImage(NewCroppedImage,filePath);

        result.isEmpty = false;
        result.FaceQimagePath = imagePath;
        result.currentFrameCount = currentframe;
        result.glassRegion = NewCroppedImage;
        result.pixGlassLength = croppedImage.rows;
        result.pixGlassWidth = croppedImage.cols;
        result.part = part;

        return result;
        qDebug()<<"帧["<<result.currentFrameCount<<"]执行完毕";
        return result;
    } else {
        qDebug()<<"图片为空";
    }
    return NewGlassResult();
}

CV_GLASSPART OpenCVAlgorithm::DetermineGlassPart(cv::Rect maxBoundingRect, int imageRows)
{
    // 判断玻璃的位置
    if ( maxBoundingRect.y <= 3 ) {
        if ((double)maxBoundingRect.height/(double)imageRows > 0.99) {
            return CV_GLASSPART::MIDDLE;
        } else {
            return CV_GLASSPART::TAIL;
        }
    } else { // 此帧是玻璃的头部和尾部区
        if ((double)(maxBoundingRect.height +  maxBoundingRect.y)/(double)imageRows > 0.99 ){
            return CV_GLASSPART::HEAD;
        } else {
            return CV_GLASSPART::WholeGlass;
        }
    }
}

void OpenCVAlgorithm::edgeDefectDetection2(
                            cv::Mat& region0,
                            cv::Mat& region1,
                            cv::Mat& region2,
                          int topAddition,
                          int bottomAddition,
                          int leftAddition,
                          int rightAddition,
                          std::vector<EdgeInfo>& edges,
                          cv::Mat& FrameRegion)
{
    //
    // 将边部全部切分，用来识别崩边和门夹
    //
    int regionRow = region2.rows;
    int regionCol = region2.cols;
    //
    // 图像的最上边具有玻璃边
    //
    if (topAddition != 0) {
        cv::Rect rect(0,0,regionCol,EDGETHICKNESS);
        cv::Mat topEdge0 = region0(rect);
        cv::Mat topEdge1 = region1(rect);
        cv::Mat topEdge2 = region2(rect);
        EdgeInfo info;
        info.rect = rect;
        info.region0 = topEdge0;
        info.region1 = topEdge1;
        info.region2 = topEdge2;
        info.PART = EDGEPART::TOP;
        edges.push_back(info);
    }
    //
    // 图像的最右边具有玻璃边
    //
    if (rightAddition != 0) {
       cv::Rect rect(regionCol-EDGETHICKNESS,0,EDGETHICKNESS,regionRow);
       cv::Mat rightEdge0 = region0(rect);
       cv::Mat rightEdge1 = region1(rect);
       cv::Mat rightEdge2 = region2(rect);
       EdgeInfo info;
       info.rect = rect;
       info.region0 = rightEdge0;
       info.region1 = rightEdge1;
       info.region2 = rightEdge2;
       info.PART = EDGEPART::RIGHT;
       edges.push_back(info);
    }
    //
    // 沿着图像最下边缘开始裁剪小图
    //
    if (bottomAddition != 0) {
        cv::Rect rect(0,regionRow-EDGETHICKNESS,regionCol,EDGETHICKNESS);
        cv::Mat bottomEdge0 = region0(rect);
        cv::Mat bottomEdge1 = region1(rect);
        cv::Mat bottomEdge2 = region2(rect);
        EdgeInfo info;
        info.rect = rect;
        info.region0 = bottomEdge0;
        info.region1 = bottomEdge1;
        info.region2 = bottomEdge2;
        info.PART = EDGEPART::BOTTOM;
        edges.push_back(info);
    }
    //
    // 沿着图像的最左边开始裁剪小图
    //
    if (leftAddition != 0) {
       cv::Rect rect(0,0,EDGETHICKNESS,regionRow);
        cv::Mat leftEdge0 = region0(rect);
       cv::Mat leftEdge1 = region1(rect);
        cv::Mat leftEdge2 = region2(rect);
        EdgeInfo info;
        info.rect = rect;
        info.region0 = leftEdge0;
        info.region1 = leftEdge1;
        info.region2 = leftEdge2;
        info.PART = EDGEPART::LEFT;
        edges.push_back(info);
    }

    cv::Rect rect(EDGETHICKNESS,EDGETHICKNESS,regionCol-EDGETHICKNESS*2,regionRow-EDGETHICKNESS*2);
    FrameRegion = region2(rect);
}

void OpenCVAlgorithm::edgePartDefect(std::vector<EdgeInfo> edges, std::vector<GlassDefect2>& edgeDefects)
{
    for (auto edge : edges) {
        if (edge.PART == EDGEPART::TOP || edge.PART == EDGEPART::BOTTOM) {
            // 计算列投影
            cv::Mat verticalProjection;
            cv::reduce(edge.region2, verticalProjection, 0, cv::REDUCE_SUM, CV_32S);

            // 求行投影的平均值
            cv::Scalar meanValue = cv::mean(verticalProjection);
            int rangeValue = 0;//波动范围参数，根据实际情况修改

            // 计算大于平均值的位置
            bool pixcontinue =  false;
            int startloc = 0;
            for (int i = 0; i < verticalProjection.cols; ++i) {
                if (verticalProjection.at<int>(0, i) >= meanValue[0] + rangeValue) {
                    pixcontinue = true;
                } else {
                    if (pixcontinue == true) {
                        pixcontinue = false;
                        if (i-startloc > 20) {//连续间隔大于6
                            cv::Rect rect(startloc,0,i-startloc,EDGETHICKNESS);
                            cv::Mat defect0 = edge.region0(rect);
                            cv::Mat defect1 = edge.region1(rect);
                            cv::Mat defect2 = edge.region2(rect);

                            GlassDefect2 data;
                            data.time = QDateTime::currentDateTime().toString("hh:mm:ss").toStdString().data();        // 时间
                            data.defectLevel = "NG";
                            data.pixLength = rect.height;   // 长度像元数
                            data.pixWidth = rect.width;    // 宽度像元数
                            data.pixX = rect.x;        // 像元X
                            data.pixY = rect.y;        // 像元Y
                            data.pixArea = rect.height*rect.width;     // 面积
                            data.region0 = defect0;
                            data.region1 = defect1;
                            data.region2 = defect2;
                            data.imagePath0 = SyncSaveImage(defect0);;
                            data.imagePath1 = SyncSaveImage(defect1);
                            data.imagePath2 = SyncSaveImage(defect2);  // 小图存储的地址
                            data.rect = rect;
                            data.gregion = glassRegion::EDGE;
                            edgeDefects.push_back(data);
                        }
                    }
                    startloc = i;
                }
            }
        } else if (edge.PART == EDGEPART::LEFT || edge.PART == EDGEPART::RIGHT) {
            // 计算水平投影（行投影）
            cv::Mat horizontalProjection;
            cv::reduce(edge.region2, horizontalProjection, 1, cv::REDUCE_SUM, CV_32S);

            // 求行投影的平均值
            cv::Scalar meanValue = cv::mean(horizontalProjection);
            int rangeValue = 0;//波动范围参数，根据实际情况修改

            // 计算大于平均值的位置
            bool pixcontinue =  false;
            int startloc = 0;
            for (int i = 0; i < horizontalProjection.rows; ++i) {
                if(horizontalProjection.at<int>(i,0) >= (meanValue[0] + rangeValue)) {//大于反射暗场
                    pixcontinue = true;
                } else {
                    if (pixcontinue == true) {
                        pixcontinue = false;
                        if (i-startloc > 20) {//连续间隔大于6
                            cv::Rect rect(0,startloc,EDGETHICKNESS,i-startloc);
                            cv::Mat defect0 = edge.region0(rect);
                            cv::Mat defect1 = edge.region1(rect);
                            cv::Mat defect2 = edge.region2(rect);
                            GlassDefect2 data;
                            data.time = QDateTime::currentDateTime().toString("hh:mm:ss").toStdString().data();        // 时间
                            data.defectLevel = "NG";
                            data.pixLength = rect.height;   // 长度像元数
                            data.pixWidth = rect.width;    // 宽度像元数
                            data.pixX = rect.x;        // 像元X
                            data.pixY = rect.y;        // 像元Y
                            data.pixArea = rect.height*rect.width;     // 面积
                            data.imagePath0 = SyncSaveImage(defect0);;
                            data.imagePath1 = SyncSaveImage(defect1);
                            data.imagePath2 = SyncSaveImage(defect2);  // 小图存储的地址
                            data.rect = rect;
                            data.gregion = glassRegion::EDGE;
                            edgeDefects.push_back(data);
                        }
                    }
                    startloc = i;
                }
            }
        }
    }
}

void OpenCVAlgorithm::CalculateMaximumBoundingRectangle(std::vector<int>& XXs,
                                                        std::vector<int>& YYs,
                                                        int imageRows,
                                                        int imageCols,
                                                        cv::Rect& maxBoundingRect)
{
    // 计算玻璃区域的最大外接矩形
    if (!XXs.empty() && !YYs.empty()) {
        int minX = *std::min_element(XXs.begin(), XXs.end());
        int minY = *std::min_element(YYs.begin(), YYs.end());
        int maxX = *std::max_element(XXs.begin(),XXs.end());
        int maxY = *std::max_element(YYs.begin(),YYs.end());
        maxBoundingRect.x = minX < 0 ? 0 : minX;
        maxBoundingRect.y = minY < 0 ? 0 : minY;
        maxBoundingRect.height = (maxBoundingRect.y + maxY - minY) > imageRows ? (imageRows - maxBoundingRect.y) : (maxY - minY);
        maxBoundingRect.width = (maxBoundingRect.x + maxX - minX) > imageCols ? (imageCols - maxBoundingRect.x) : (maxX - minX);
    }
}

void OpenCVAlgorithm::MergeConnectedDomainDefects(std::vector<ConnectedComponent>& components)
{
    for (int i = 0; i < (int)components.size(); i++) {// 合并新的区域
        ConnectedComponent iComponent = components[i];
        for (int j = i + 1; j < (int)components.size(); j++) {
            ConnectedComponent jComponent = components[j];
            if (isClose(iComponent, jComponent, 20)) {//最短欧式距离20个像元
                int minX = iComponent.rect.x > jComponent.rect.x ? jComponent.rect.x : iComponent.rect.x;
                int minY = iComponent.rect.y > jComponent.rect.y ? jComponent.rect.y : iComponent.rect.y;
                int maxX = (iComponent.rect.x + iComponent.rect.width) > (jComponent.rect.x + jComponent.rect.width) ? (iComponent.rect.x + iComponent.rect.width) : (jComponent.rect.x + jComponent.rect.width);
                int maxY = (iComponent.rect.y + iComponent.rect.height) > (jComponent.rect.y + jComponent.rect.height) ? (iComponent.rect.y + iComponent.rect.height) : (jComponent.rect.y + jComponent.rect.height);
                cv::Rect mergedRect(minX, minY, maxX - minX, maxY - minY);
                iComponent.rect = mergedRect;
                iComponent.area = iComponent.rect.area();
                iComponent.x = (minX + maxX) /2;
                iComponent.y = (minY + maxY) /2;
                components.erase(components.begin()+j);//删除jComponent元素，
                components[i] = iComponent;
                if (i==0){//合并完成，从前两个再遍历一遍
                    i =-1;
                } else {
                    i = i-2;
                }
                break;
            }
        }
    }

}


