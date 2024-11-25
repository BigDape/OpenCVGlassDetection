﻿#include "processtile.h"
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/dnn.hpp>
#include <QDir>
#include <chrono>
#include <opencv2/core/ocl.hpp>
#include <opencv2/cudaarithm.hpp>
#include <opencv2/cudaimgproc.hpp>
#include <opencv2/dnn/dnn.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/core/cuda.hpp>
#include <opencv2/dnn.hpp>
#include <chrono>
#include<future>      //std::future std::promise
#include <opencv2/cudawarping.hpp>
#include <opencv2/cudafilters.hpp>

//检出缺陷滤波
#define AREATHRESHOLD 25

extern "C" void cudaProcessClassification(cv::Mat defectimage, cv::dnn::Net net);

#include <cuda_runtime.h>
#include <device_launch_parameters.h>
#include <vector>

// CUDA 核函数，处理图像分类
// __global__ void processClassificationKernel(std::vector<cv::cuda::GpuMat>* defectimage, cv::dnn::Net* net, NewDefectUnitData* resdata) {
//     // 这里假设只有一个线程在运行，实际应用中你可能需要根据图像大小和 GPU 资源来调整线程配置
//     int tid = threadIdx.x + blockIdx.x * blockDim.x;
//     if (tid < (int)defectimage->size()) {
//         auto it = defectimage->begin();
//         std::advance(it, tid);
//         cv::cuda::GpuMat image = *it;
//         cv::cuda::GpuMat threeChannelImage;
//         cv::cuda::cvtColor(image, threeChannelImage, cv::COLOR_BGRA2BGR);
//         if (threeChannelImage.empty()) {
//             return;
//         }

//         cv::cuda::GpuMat blob;
//         cv::dnn::blobFromImage(threeChannelImage, blob, 1.0 / 255.0, cv::Size(640, 640), cv::Scalar(), true, false);

//         // 准备输入
//         net->setInput(blob);

//         // 前向传播并获取输出
//         std::vector<cv::Mat> outputs;
//         net->forward(outputs, net->getUnconnectedOutLayersNames());

//         int rows = outputs[0].size[1];
//         int dimensions = outputs[0].size[2];
//         if (dimensions > rows) {
//             rows = outputs[0].size[2];
//             dimensions = outputs[0].size[1];
//             outputs[0] = outputs[0].reshape(1, dimensions);
//             cv::transpose(outputs[0], outputs[0]);
//         }

//         float* data = (float*)outputs[0].data;
//         std::vector<int> class_ids;
//         std::vector<float> confidences;
//         std::vector<cv::Rect> boxes;

//         std::vector<std::string> classes = { "JieShi_Min", "MaoXu_Min", "QiPao_Min", "ShuiDi_Min", "BoLiXue_Min", "HeiDian_Min", "HuaShang_Min" };
//         double modelScoreThreshold = 0.1;
//         double modelConfidenceThreshold = 0.1;

//         cv::Point class_id1;
//         double maxClassScore1;
//         cv::Mat res1 = outputs[0](cv::Rect(4, 0, classes.size(), rows));
//         cv::minMaxLoc(res1, 0, &maxClassScore1, 0, &class_id1);
//         data += dimensions * class_id1.y;
//         float x = data[0];
//         float y = data[1];
//         float w = data[2];
//         float h = data[3];

//         resdata->id = 0;
//         // resdata->time = std::to_string(std::time(nullptr));
//         resdata->type = class_id1.x;
//         resdata->pixLength = h;
//         resdata->pixWidth = w;
//         resdata->pixX = x;
//         resdata->pixY = y;
//         resdata->pixArea = h * w;
//     }
// }

ProcessTile::ProcessTile()
{
    // 加载模型
    net = cv::dnn::readNetFromONNX("D:/best.onnx");
    net.setPreferableBackend(cv::dnn::DNN_BACKEND_CUDA);
    net.setPreferableTarget(cv::dnn::DNN_TARGET_CUDA);
    if (!net.empty()) {
        qDebug()<<"!net.empty()";
    } else {
        qDebug()<<"Load onnx model is fail.";
    }
}


// 离线模式调用的函数
void ProcessTile::OfflineTileImageProcess(QString fullpath)
{
    (void) fullpath;
//    QString tile1Fullpath,tile2Fullpath,tile3Fullpath,tile4Fullpath;
//    if (Global::isJpg) {
//        tile1Fullpath = fullpath + QString("/tile1.jpg");
//        tile2Fullpath = fullpath + QString("/tile2.jpg");
//        tile3Fullpath = fullpath + QString("/tile3.jpg");
//        tile4Fullpath = fullpath + QString("/tile4.jpg");
//    } else {
//        tile1Fullpath = fullpath + QString("/tile1.bmp");
//        tile2Fullpath = fullpath + QString("/tile2.bmp");
//        tile3Fullpath = fullpath + QString("/tile3.bmp");
//        tile4Fullpath = fullpath + QString("/tile4.bmp");
//    }

//    bool res1 = QFile::exists(tile1Fullpath);
//    bool res2 = QFile::exists(tile2Fullpath);
//    bool res3 = QFile::exists(tile3Fullpath);
//    bool res4 = QFile::exists(tile4Fullpath);
//    if( res1 && res2 && res3 && res4) {
//        ReadImage(&mosaickthread[0].MosaickResultImage,tile1Fullpath.toStdString().data());
//        ReadImage(&mosaickthread[1].MosaickResultImage,tile2Fullpath.toStdString().data());
//        ReadImage(&mosaickthread[2].MosaickResultImage,tile3Fullpath.toStdString().data());
//        ReadImage(&mosaickthread[3].MosaickResultImage,tile4Fullpath.toStdString().data());
//        GetDictTuple(Global::RecipeDict,"自定义参数",&UserDefinedDict);
//        ProcessTile::PreProceeTile();
//    } else {
//        qDebug() << tile1Fullpath << tile2Fullpath << tile3Fullpath << tile4Fullpath << " is not exists()";
//    }
}


void ProcessTile::CV_DefectsDetected(cv::Mat image1,
                                     cv::Mat image2,
                                     cv::Mat image3,
                                     int currentFrame)
{
    try{
       ProcessTile::image1DefectsDetected(image1,currentFrame);
    } catch (...) {
        qDebug() << "ProcessTile::CV_DefectsDetected => An unknown error occurred.";
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

    ProcessTile::image2DefectsDetected(image2);
    ProcessTile::image3DefectsDetected(image3);
}

void ProcessTile::saveMatToImage(QString fullpath,cv::Mat region )
{
    std::string filename = fullpath.toStdString();
    cv::imwrite(filename, region);
}

// 左上角坐标点和右上角坐标点
void ProcessTile::cropRectangleMat(const cv::Mat image,
                                    cv::Mat &dst,
                                    int row1y,
                                    int Column1x,
                                    int row2y,
                                    int Column2x)
 {
     // 确保裁剪区域在图像范围内
     CV_Assert(row1y >= 0 && row1y < image.rows && Column1x >= 0 && Column1x < image.cols);
     CV_Assert(row2y >= 0 && row2y <= image.rows && Column2x >= 0 && Column2x <= image.cols);
     CV_Assert(row1y < row2y && Column1x < Column2x);

     // 创建裁剪区域的Rect对象
     cv::Rect roi(Column1x, row1y, Column2x - Column1x, row2y - row1y);

     // 使用ROI裁剪图像
     dst = image(roi);
 }

void ProcessTile::prewittEdgeDetection(cv::Mat& src, cv::Mat& dst) {
    cv::Mat kernelX = (cv::Mat_<int>(3, 3) << -1, 0, 1,
                       -1, 0, 1,
                       -1, 0, 1);
    cv::Mat kernelY = (cv::Mat_<int>(3, 3) << -1, -1, -1,
                       0, 0, 0,
                       1, 1, 1);

    cv::Mat gx, gy;
    cv::filter2D(src, gx, -1, kernelX);
    cv::filter2D(src, gy, -1, kernelY);

    cv::magnitude(gx, gy, dst);
}

void ProcessTile::getBaseLineFromImage(cv::Mat& region, cv::Mat& baseline)
{
    if (region.rows > 0 ) {
       cv::Mat baseLineRow1 = region.row(region.rows/4);
       cv::Mat baseLineRow2 = region.row((region.rows/4)*2);
       cv::Mat baseLineRow3 = region.row((region.rows/4)*3);

       cv::Scalar meanValue1 = cv::mean(baseLineRow1);
       double average1 = meanValue1[0];
       cv::Scalar meanValue2 = cv::mean(baseLineRow2);
       double average2 = meanValue2[0];
       cv::Scalar meanValue3 = cv::mean(baseLineRow3);
       double average3 = meanValue3[0];
       //
       // 取平均值为中间的为基准线
       //
       double midAverage = 0;
       if ((average1 <= average2 && average2 <= average3) || (average3 <= average2 && average2 <= average1)) {
           midAverage = average2;
           baseline = baseLineRow2;
           qDebug()<<"2/4 is baseline";
       } else if ((average2 <= average1 && average1 <= average3) || (average3 <= average1 && average1 <= average2)) {
           midAverage = average1;
           baseline = baseLineRow1;
           qDebug()<<"1/4 is baseline";
       } else {
           midAverage = average3;
           baseline = baseLineRow3;
           qDebug()<<"3/4 is baseline";
       }
       qDebug()<<"midAverage ="<<midAverage;
    } else {
        qWarning()<<"get baseLine is failed.";
    }
}

// region是玻璃区域
void ProcessTile::edgeDefectDetection(cv::Mat& region,
                                      std::vector<regionInfor>& edgeRegionInfos,
                                      int topAddition,
                                      int bottomAddition,
                                      int leftAddition,
                                      int rightAddition,
                                      std::vector<DoorClampAndHole>& results)
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
    if (topAddition != 0) {
        for (int i =0; i < regionCol/640; ++i) {
            cv::Rect rect(i*640, 0, 640, 640);
            cv::Mat topEdgeRegion = region(rect);
            regionInfor info;
            info.id = id++;
            info.path = ProcessTile::SyncSaveCurrentTimeImage(topEdgeRegion);
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
                info.path = ProcessTile::SyncSaveCurrentTimeImage(topEdgeRegion);
                info.region = topEdgeRegion;
                edgeRegionInfos.push_back(info);
                ProcessTile::SyncSaveCurrentTimeImage(topEdgeRegion);
            }
        }
    }
    //
    // 沿着图像的最右边开始从上往下裁剪小图
    //
    if (rightAddition != 0) {
        std::vector<EdgeElement> Y1Y2X1X2;//存储门夹的坐标值
        for (int i = 1; i < regionRow/640; ++i) {
            cv::Rect rect(regionCol-640, i*640, 640, 640);
            cv::Mat rightEdgeRegion = region(rect);

            ProcessTile::DoorClampDetection(rightEdgeRegion,rect,id,Y1Y2X1X2);

            regionInfor info;
            info.id = id++;
            info.path = ProcessTile::SyncSaveCurrentTimeImage(rightEdgeRegion);
            info.region = rightEdgeRegion;
            edgeRegionInfos.push_back(info);
        }

        ProcessTile::DoorClampResultData(Y1Y2X1X2, edgeRegionInfos, results);
        if (regionRow%640 != 0) {
            int lastY = regionRow - (regionRow%640);
            cv::Rect rect(regionCol-640,lastY, 640, regionRow%640);
            cv::Mat rightEdgeRegion = region(rect);
            if (rightEdgeRegion.rows != 0 && rightEdgeRegion.cols != 0) {
                regionInfor info;
                info.id = id++;
                info.path = ProcessTile::SyncSaveCurrentTimeImage(rightEdgeRegion);
                info.region = rightEdgeRegion;
                edgeRegionInfos.push_back(info);
            }
        }
    }
    //
    // 沿着图像最下边缘开始裁剪小图
    //
    if (bottomAddition != 0) {
        for (int i =0; i < regionCol/640 -1; ++i) {
            cv::Rect rect(i*640, regionRow - 640, 640, 640);
            cv::Mat bottomEdgeRegion = region(rect);
            regionInfor info;
            info.id = id++;
            info.path = ProcessTile::SyncSaveCurrentTimeImage(bottomEdgeRegion);
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
                info.path = ProcessTile::SyncSaveCurrentTimeImage(bottomEdgeRegion);
                info.region = bottomEdgeRegion;
                edgeRegionInfos.push_back(info);
            }
        }
    }
    //
    // 沿着图像的最左边开始裁剪小图
    //
    if (leftAddition != 0) {
        std::vector<EdgeElement> Y1Y2X1X2;//存储门夹的坐标值
        for (int i = 1; i < regionRow/640 -1; ++i) {
            cv::Rect rect(0, i*640, 640, 640); //在图像上的坐标：X = 0, Y = i*640
            cv::Mat leftEdgeRegion = region(rect);

            ProcessTile::DoorClampDetection(leftEdgeRegion,rect,id,Y1Y2X1X2);

            QString path = "D:/testopencv/defect/" + QString::number(i) + ".jpg";
            regionInfor info;
            info.id = id++;
            info.path = ProcessTile::SyncSaveCurrentTimeImage(leftEdgeRegion,path);
            info.region = leftEdgeRegion;
            edgeRegionInfos.push_back(info);
        }//for (int i = 1; i < regionRow/640 -1; ++i)
        // 门夹数据拼接
        ProcessTile::DoorClampResultData(Y1Y2X1X2, edgeRegionInfos, results);
        if (regionRow % 640 != 0) {
            int lastY = regionRow - (regionRow%640) - 640;
            cv::Rect rect(0,lastY, 640, regionRow%640);
            cv::Mat leftEdgeRegion = region(rect);
            if (leftEdgeRegion.rows != 0 && leftEdgeRegion.cols != 0) {
                regionInfor info;
                info.id = id++;
                info.path = ProcessTile::SyncSaveCurrentTimeImage(leftEdgeRegion);
                info.region = leftEdgeRegion;
                edgeRegionInfos.push_back(info);
            }
        }
    }
}

void ProcessTile::YoloDefectClassification(std::vector<regionInfor>& Regions, std::vector<NewDefectUnitData>& unitVec)
{
    auto start = std::chrono::high_resolution_clock::now();// 开始时间
    std::vector<std::thread> threads;
    //
    // 缺陷检测
    //
    qDebug()<<"Regions.size()"<<Regions.size();
    std::vector<std::promise<NewDefectUnitData>> promiseObjs(Regions.size());
    for (int i = 0 ; i < (int)Regions.size(); ++i) {
        std::promise<NewDefectUnitData> promiseObj;
        threads.push_back(std::thread(&ProcessTile::threadProcessClassification, this, Regions[i], std::ref(promiseObjs[i])));
    }
    for (int i=0; i< (int)threads.size();++i) {
        if (threads[i].joinable()) {
            NewDefectUnitData it = promiseObjs[i].get_future().get();
            threads[i].join();
            unitVec.push_back(it);
        }
    }
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> duration = end - start;
    //qDebug() << "time：" << duration.count() << " ms";
}

void ProcessTile::image1DefectsDetected(cv::Mat& image, int currentframe)
{
    int DeviceCount = cv::cuda::getCudaEnabledDeviceCount();
    if (DeviceCount < 1) {
        std::cout << "No GPU support." << std::endl;
    } else {
        std::cout << "GPU support available. Device Count ="<<DeviceCount<< std::endl;
    }

    int imageRows = image.rows;
    int imageCols = image.cols;
    CV_GLASSPART part = CV_GLASSPART::UNKNOW;
    qDebug()<<"imageRows ="<<imageRows<<",imageCols="<<imageCols;

    if (imageRows > 0 ) {/*30ms*/
        cv::setNumThreads(26);
        std::vector<DoorClampAndHole> sizeRes;//尺寸界面的结果
        //
        // 边缘检测
        //
        auto start = std::chrono::high_resolution_clock::now();// 开始时间
        // cv::cuda::GpuMat gpuImage(image);
        // cv::cuda::GpuMat gpuCannyEdges;
        cv::Mat cannyEdges;
        cv::Canny(image, cannyEdges, 50, 150);
        // cv::Ptr<cv::cuda::CannyEdgeDetector> canny=cv::cuda::createCannyEdgeDetector(50,100);
        // canny->detect(gpuImage,gpuCannyEdges);
        // gpuCannyEdges.download(cannyEdges);
        QString filename2 = "D:/testopencv/cannyEdges.jpg";
        ProcessTile::SyncSaveCurrentTimeImage(cannyEdges,filename2);


        /*315ms*/
        //
        // 获取region
        //
        cv::Mat dilatedImage;
        cv::Mat element = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(3, 3));
        cv::dilate(cannyEdges, dilatedImage, element);//膨胀

       std::vector<std::vector<cv::Point> > contours;
       cv::findContours(dilatedImage, contours, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_NONE); //找轮廓
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
       int maxHeight = 0;
       int minX = 999999999;
       int minY = 999999999;
       /*478ms*/
       for(int i = 0; i < (int)contours.size(); i++) {
           std::vector<cv::Point> contour = contours[i];
           // 获取轮廓的最大外接矩形
           cv::RotatedRect rect = cv::minAreaRect(contour);
           cv::Rect boundingRect = rect.boundingRect();
           double area = boundingRect.width * boundingRect.height;
           XXs.push_back(boundingRect.x);
           XXs.push_back(boundingRect.x + boundingRect.width);
           cv::Scalar color(std::rand() % 256, std::rand() % 256, std::rand() % 256);
           cv::rectangle(image, boundingRect, color, 2);//在原图上画框
           if (boundingRect.width > maxWidth) {
               maxArea = area;
               maxAreaContourIndex = i;
               maxminAreaRect = rect;
               maxBoundingRect = boundingRect;
               // maxWidth = boundingRect.width;
               // if (boundingRect.x <minX) {
               //     minX = boundingRect.x;
               // }

           }
           // if (boundingRect.height > maxHeight) {
           //     qDebug()<<"maxHeight ="<<maxHeight <<", boundingRect.height ="<<boundingRect.height;
           //     maxHeight = boundingRect.height;
           //     if (boundingRect.y < minY) {
           //         minY = boundingRect.y;
           //     }
           // }
       }
       QString path = "D:/testopencv/defect765.jpg";
       saveMatToImage(path,image);
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
           // maxBoundingRect.x = minX;
           // maxBoundingRect.y = minY;
           // maxBoundingRect.width = maxWidth;
           // maxBoundingRect.height = maxHeight;
           if (maxBoundingRect.y <= 0) {
               part = CV_GLASSPART::TAIL;
               // qDebug()<<"maxminAreaRect.angle ="<<maxminAreaRect.angle;
               // double angle_degrees = maxminAreaRect.angle;
               // double angle_radians = angle_degrees * CV_PI / 180.0;//弧度
               // double tan_value = std::tan(angle_radians);// 使用cmath库中的tan函数求正切值
               // double pixXt = tan_value * maxBoundingRect.height ;
               // cv::Point2f P1; //平行四边形的左上顶点
               // cv::Point2f P2; //平行四边形的右上顶点
               // cv::Point2f P3; //平行四边形的右下顶点
               // cv::Point2f P4; //平行四边形的左下顶点
               // if (tan_value > 0) {//玻璃上部向右倾斜
               //     P1.x = maxBoundingRect.x + pixXt;
               //     P1.y = 0;
               //     P2.x = maxBoundingRect.x + maxBoundingRect.width; //P1x坐标加上宽度
               //     P2.y = 0;
               //     P3.x = maxBoundingRect.x + maxBoundingRect.width -pixXt;
               //     P3.y = maxBoundingRect.height;
               //     P4.x = maxBoundingRect.x;
               //     P4.y = maxBoundingRect.height;
               // } else if (tan_value == 0) {//垂直
               //     P1.x = maxBoundingRect.x;
               //     P1.y = 0;
               //     P2.x = maxBoundingRect.x + maxBoundingRect.width; //P1x坐标加上宽度
               //     P2.y = 0;
               //     P3.x = maxBoundingRect.x + maxBoundingRect.width;
               //     P3.y = maxBoundingRect.height;
               //     P4.x = maxBoundingRect.x;
               //     P4.y = maxBoundingRect.height;
               // } else {//玻璃上部向左倾斜
               //     P1.x = maxBoundingRect.x;
               //     P1.y = 0;
               //     P2.x = maxBoundingRect.x + maxBoundingRect.width+ pixXt; //P1x坐标加上宽度
               //     P2.y = 0;
               //     P3.x = maxBoundingRect.x + maxBoundingRect.width;
               //     P3.y = maxBoundingRect.height;
               //     P4.x = maxBoundingRect.x- pixXt;
               //     P4.y = maxBoundingRect.height;
               // }
               // oldvertices.push_back(P1);
               // oldvertices.push_back(P2);
               // oldvertices.push_back(P3);
               // oldvertices.push_back(P4);
           } else {
               part = CV_GLASSPART::HEAD;
           }


       }
       qDebug()<<"maxBoundingRect.x ="<<maxBoundingRect.x
                <<",maxBoundingRect.y="<<maxBoundingRect.y
                <<"maxBoundingRect.w ="<<maxBoundingRect.width
                <<",maxBoundingRect.height="<<maxBoundingRect.height;
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
       QString filenametmp1 = "D:/testopencv/tmp1.jpg";
       ProcessTile::SyncSaveCurrentTimeImage(tmp1,filenametmp1);


       /*496ms*/
       //
       // 找到玻璃区域
       //
       if (maxAreaContourIndex != -1) {

           ProcessTile::calculateBoundingRectangle(part, maxBoundingRect,maxminAreaRect, oldvertices, newvertices);//计算出图片扶正的顶点矩阵
           // 仿射变换原图
           cv::Mat warpedImage;//仿射变换后的图片
           // ProcessTile::affineTransformation(oldvertices,
           //                                   newvertices,
           //                                   image,
           //                                   warpedImage);
           std::thread th1 = std::thread(&ProcessTile::affineTransformation,
                                         this,
                                         oldvertices,
                                         newvertices,
                                         image,
                                         std::ref(warpedImage));


           /*1088ms*/

            // 仿射变换二值图像
           cv::Mat warpedEageImage;//仿射变换后的二值图片
           // ProcessTile::affineTransformation(oldvertices,
           //                                   newvertices,
           //                                   cannyEdges,
           //                                   warpedEageImage);
           std::thread th2 = std::thread(&ProcessTile::affineTransformation,
                                         this,
                                         oldvertices,
                                         newvertices,
                                         cannyEdges,
                                         std::ref(warpedEageImage));
           th1.join();
           th2.join();
           QString filename45 = "D:/testopencv/warpedImage.jpg";
           ProcessTile::SyncSaveCurrentTimeImage(warpedImage,filename45);
           QString filename46 = "D:/testopencv/warpedEageImage.jpg";
           ProcessTile::SyncSaveCurrentTimeImage(warpedEageImage,filename46);
           qDebug()<<"最大外轮廓的面积："<<maxArea;

           /*1746ms*/


           //
           // 获取面积最大的轮廓的边界矩形
           //
           // cv::Rect boundingRect1 = cv::boundingRect(contours[maxAreaContourIndex]);
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

           QString filename48 = "D:/testopencv/croppedImage.jpg";
           ProcessTile::SyncSaveCurrentTimeImage(croppedImage,filename48);
           QString filename47 = "D:/testopencv/croppedEdgeImage.jpg";
           ProcessTile::SyncSaveCurrentTimeImage(croppedEdgeImage,filename47);
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
           ProcessTile::edgeDefectDetection(croppedImage,
                                            edgeregions,
                                            topAddition,
                                            bottomAddition,
                                            leftAddition,
                                            rightAddition,
                                            sizeRes);
           /*1823ms*/
           //
           // 面部缺陷检出
           //

           cv::Mat framCroppedImage;
           ProcessTile::CuttinGlassDdges(croppedImage, framCroppedImage);//将图片的四周640个像素切割（去边）
           cv::Mat framcroppedEdgeImage;
           ProcessTile::CuttinGlassDdges(croppedEdgeImage, framcroppedEdgeImage);//将图片的四周640个像素切割（去边）

           QString filename3 = "D:/testopencv/framCroppedImage.jpg";
           ProcessTile::SyncSaveCurrentTimeImage(framCroppedImage,filename3);
           QString filename4 = "D:/testopencv/framcroppedEdgeImage.jpg";
           ProcessTile::SyncSaveCurrentTimeImage(framcroppedEdgeImage,filename4);
           //
           // 将面部相邻的缺陷联通起来
           // 将相连的域联通
           //
           cv::Mat labels;
           cv::Mat stats;
           cv::Mat centroids;
           cv::Mat resizedImage;
           cv::resize(framcroppedEdgeImage, resizedImage, cv::Size(framcroppedEdgeImage.cols / 2, framcroppedEdgeImage.rows / 2));
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
           qDebug()<<"backgroundIndex = " <<backgroundIndex<<",maxArea ="<<maxArea;
           qDebug()<<"components =" <<components.size();

           // 合并新的区域
           for (int i = 0; i < (int)components.size(); i++) {
                ConnectedComponent iComponent = components[i];
                //qDebug()<<"iComponent area ="<<iComponent.area<<"=>i="<<i<<",components.size()="<<components.size();
                for (int j = i + 1; j < (int)components.size(); j++) {
                    ConnectedComponent jComponent = components[j];
                    if (isClose(iComponent, jComponent, 20)) {//最短欧式距离20个像元
                        int minX = std::min(iComponent.rect.x, jComponent.rect.x);
                        int minY = std::min(iComponent.rect.y, jComponent.rect.y);
                        int maxX = std::max(iComponent.rect.x + iComponent.rect.width, jComponent.rect.x + jComponent.rect.width);
                        int maxY = std::max(iComponent.rect.y + iComponent.rect.height, jComponent.rect.y + jComponent.rect.height);
                        cv::Rect mergedRect(minX, minY, maxX - minX, maxY - minY);
                        iComponent.rect = mergedRect;
                        iComponent.area = iComponent.rect.area();
                        iComponent.x = (minX + maxX) /2;
                        iComponent.y = (minY + maxY) /2;
                        components.erase(components.begin()+j);//删除jComponent元素，
                        components[i] = iComponent;
                        //qDebug()<<"change i="<<i <<",j="<<j<<",components.size()="<<components.size();
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
                   //qDebug()<<"components[i].rect.width = "<<components[i].rect.width<<",components[i].rect.height = "<<components[i].rect.height;
                   /*
                   double similarityValue = std::min((double)components[i].rect.width ,(double)components[i].rect.height) / std::max((double)components[i].rect.width ,(double)components[i].rect.height);
                   if (components[i].rect.width >= 100 && components[i].rect.height >= 100 && similarityValue>0.8){//可能是圆
                       qDebug()<<"similarityValue = "<<similarityValue;
                       cv::Mat circle = framcroppedEdgeImage(components[i].rect);
                       double diameter;
                       ProcessTile::HoughCircleRadius(circle, diameter);
                       DoorClampAndHole hole;
                       hole.PixHeight = diameter;
                       hole.PixWidth = diameter;
                       hole.MarginsX = rect.x + 32 + diameter/2;
                       hole.MarginsY = rect.y + 32 + diameter/2;
                       hole.Region = circle;
                       hole.type = SizeType::Hole;
                       hole.Path = ProcessTile::SyncSaveCurrentTimeImage(hole.Region);
                       sizeRes.push_back(hole);
                       //continue; //圆不用作为缺陷检测
                   }
                    */
                   rect.x = rect.x + 32; //rect是面部坐标，转化为玻璃坐标
                   rect.y = rect.y + 32;
                   cv::Scalar color(std::rand() % 256, std::rand() % 256, std::rand() % 256);
                   cv::rectangle(croppedImage, rect, color, 2);//在原图上画框
               } else {
                   continue;
               }
               // 剪裁YOLO模型大小的图像
               cv::Rect yoloRect = ProcessTile::getDefectStandardRect(framCroppedImage, components[i].x,components[i].y,640,640);
               // 去除重复剪裁图像
               int hashKey = ProcessTile::PointHashCode(yoloRect.x,yoloRect.y);
               if (rectMap.find(hashKey) != rectMap.end()){
                   continue;
               }
               rectMap.insert(std::pair<int,cv::Rect>(hashKey,yoloRect));
               cv::Mat defectRegion = framCroppedImage(yoloRect);
               regionInfor info;
               info.region = defectRegion;
               info.path = ProcessTile::SyncSaveCurrentTimeImage(defectRegion);
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
           QString imagePath = ProcessTile::SyncSaveCurrentTimeImage(NewCroppedImage,filePath);
           // 合并边图和面部图，进行分类
           std::vector<regionInfor> mergeRegions;
           mergeRegions.reserve(edgeregions.size() + defectRegions.size());
           mergeRegions.insert(mergeRegions.end(), edgeregions.begin(), edgeregions.end());
           mergeRegions.insert(mergeRegions.end(), defectRegions.begin(), defectRegions.end());
           std::vector<NewDefectUnitData> unitResult;

           ProcessTile::YoloDefectClassification(mergeRegions,unitResult);
           NewGlassResult result;
           result.isEmpty = false;
           result.res = unitResult;
           result.pixGlassLength = glassLength;
           result.pixGlassWidth = glassWidth;
           result.FaceQimagePath = imagePath;
           result.currentFrameCount = currentframe;
           result.sizeRes = sizeRes;
           result.glassRegion = NewCroppedImage;
           result.part = part;
           qDebug()<<"part ="<<part;
           frameResultMap.insert(currentframe,result);
           auto end = std::chrono::high_resolution_clock::now();
           std::chrono::duration<double, std::milli> duration = end - start;
           qDebug() << "Algorithm time：" << duration.count() << " ms";
       }
    } else {
        qWarning()<<"image1 row <= 0";
    }
}

void ProcessTile::image2DefectsDetected(cv::Mat& image)
{
    (void) image;
}

void ProcessTile::image3DefectsDetected(cv::Mat& image)
{
    (void) image;
}

bool ProcessTile::isClose(ConnectedComponent c1, ConnectedComponent c2, int threshold)
{
    if (c1.rect.x > c2.rect.x) {
        ProcessTile::swap(c1,c2);
    }
    if ( (c1.rect & c2.rect).area() > 0 ) {//两个矩形框重叠
        return true;
    } else { // 两个矩形相差threshold距离
        // double sqrtV = ProcessTile::rectMinEdgeDistance(c1.rect,c2.rect);
        double dx = c2.rect.x - c1.rect.x - c1.rect.width;
        if (dx > threshold) {//x方向不符合条件，则false
            return false;
        } else {//y方向
            if (c2.rect.y < c1.rect.y) {//c2的左顶点在c1的上方
                if (c1.rect.y > (c2.rect.y + c2.rect.height)){//c2左低点在c1左顶点的上方
                    double dy = c1.rect.y - c2.rect.y - c2.rect.height;
                    double distance = std::sqrt(std::pow(dx, 2) + std::pow(dy, 2));
                    return (distance <= threshold);
                } else {//c2左低点在c1左顶点的下方
                    return true;//dx < threshold
                }
            } else {//c2的左顶点在c1左顶点的下方
                if ((c1.rect.y + c1.rect.height) > c2.rect.y ) {//c1的左低点在c2的左顶点的下方
                    return true;//dx < threshold
                } else {//c1的左低点在c2的左顶点的上方
                    double dy = c2.rect.y - c1.rect.y - c1.rect.height;
                    double distance = std::sqrt(std::pow(dx, 2) + std::pow(dy, 2));
                    return (distance <= threshold);
                }
            }
        }
    }
}

void ProcessTile::swap(ConnectedComponent& c1, ConnectedComponent& c2)
{
    ConnectedComponent tmp = c1;
    c1 = c2;
    c2 = tmp;
}

void ProcessTile::HoughCircleRadius(cv::Mat image, double& diameter)
{
    // 霍夫圆变换
    std::vector<cv::Vec3f> circles;
    cv::HoughCircles(image, circles, cv::HOUGH_GRADIENT, 1, 50, 100, 30, 0, 0);
    double result = 0;
    for (size_t i = 0; i < circles.size(); i++) {
        float x = circles[i][0];
        float y = circles[i][1];
        float radius = circles[i][2];
        if (radius*2 > result) {
            result = radius*2;
        }
        qDebug() << "Circle " << i + 1 << " center: (" << x << ", " << y << "), radius: " << radius;
    }
    diameter = result;
    qDebug()<<"diameter = "<<diameter;
}

void ProcessTile::LengthWidthInscribedRectangle(cv::Mat image, double& width, double& Height, double& area)
{
    // 最大内接矩形
    cv::Mat grayImage;
    cv::cvtColor(image, grayImage, cv::COLOR_BGR2GRAY);
    std::vector<std::vector<cv::Point>> contours;
    std::vector<cv::Vec4i> hierarchy;
    cv::findContours(grayImage, contours, hierarchy, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);

    if (contours.empty()) {
        qDebug() << "No contours found.";
    }

    double maxArea = 0;
    double maxWidth = 0;
    double maxHeight = 0;
    for (const auto& contour : contours) {
        cv::RotatedRect rotatedRect = cv::minAreaRect(contour);
        double width1 = rotatedRect.size.width;
        double height1 = rotatedRect.size.height;
        double area1 = width1 * height1;
        if (area1 > maxArea) {
            maxArea = area1;
            maxWidth = width1;
            maxHeight = height1;
        }
    }
    width = maxWidth;
    Height = maxHeight;
    area = maxArea;
    qDebug()<<"maxWidth = "<<maxWidth <<", maxHeight ="<<maxHeight<<",maxArea ="<<maxArea;
}

// 仿射变换
void ProcessTile::affineTransformation(std::vector<cv::Point2f> oldvertices,
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
    // cv::warpPerspective(image, warpedImage, warpMatrix, image.size());

    cv::cuda::GpuMat gpuInput = cv::cuda::GpuMat(image);
    cv::cuda::GpuMat gpuOutput;
    int w = image.cols;
    int h = image.rows;
    cv::cuda::warpPerspective( gpuInput, gpuOutput, warpMatrix, cv::Size(w,h), cv::INTER_LINEAR , cv::BORDER_CONSTANT, 0, cv::cuda::Stream::Null() );
    gpuOutput.download(warpedImage);
}

void ProcessTile::calculateBoundingRectangle(CV_GLASSPART part,
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

void ProcessTile::CuttinGlassDdges(cv::Mat Frame, cv::Mat& result)
{
    cv::Rect FrameRect(32,32,Frame.cols-64,Frame.rows-64);
    result = Frame(FrameRect);
}

void ProcessTile::threadProcessClassification(regionInfor defectimage, std::promise<NewDefectUnitData>& promiseObj)
{
    auto start = std::chrono::high_resolution_clock::now();// 开始时间
    cv::Mat threeChannelImage;
    cv::cvtColor(defectimage.region, threeChannelImage, cv::COLOR_BGRA2BGR);
    /*1ms*/

    cv::Mat blob;
    cv::dnn::blobFromImage(threeChannelImage, blob, 1.0 / 255.0, cv::Size(640, 640), cv::Scalar(), false, false);

    /*200ms*/
    // 准备输入
    std::vector<cv::Mat> outputs;
    mut.lock();
    net.setInput(blob);//1,3/640/640
    net.forward(outputs, net.getUnconnectedOutLayersNames());// 前向传播并获取输出
    mut.unlock();

    /*1100ms*/
    int rows = outputs[0].size[1];
    int dimensions = outputs[0].size[2];
    //qDebug()<<"Edge rows ="<<rows<<", dimensions="<<dimensions;//yolo8 dimensions > rows
    rows = outputs[0].size[2];
    dimensions = outputs[0].size[1];
    outputs[0] = outputs[0].reshape(1, dimensions);
    cv::transpose(outputs[0], outputs[0]);


    /*1120ms*/
    float* data = (float*)outputs[0].data;
    cv::Point class_id1;
    double maxClassScore1;
    cv::Mat res1 = outputs[0](cv::Rect(4,0,7,rows));//std::vector<std::string> classes={ "JieShi_Min", "MaoXu_Min", "QiPao_Min", "ShuiDi_Min", "BoLiXue_Min", "HeiDian_Min", "HuaShang_Min"};
    cv::minMaxLoc(res1, 0, &maxClassScore1, 0, &class_id1);
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> duration = end - start;
    //qDebug() << "time：" << duration.count() << " ms";
    data += dimensions*class_id1.y;
    float x = data[0];
    float y = data[1];
    float w = data[2];
    float h = data[3];
    // qDebug()<<"maxClassScore1 ="<<maxClassScore1<<",class_id1 ="<<class_id1.x<<",class_id1.y="<<class_id1.y<<"x="<<x<<",y="<<y<<",w="<<w<<",h="<<h;
    // qDebug()<<"defectimage.pat ="<<defectimage.path;
    NewDefectUnitData result;
    result.id = ++defectid;
    result.time = QDateTime::currentDateTime().toString().toStdString().data();
    result.type = class_id1.x;
    result.pixLength = h;
    result.pixWidth = w;
    result.pixX = x;
    result.pixY = y;
    result.pixArea = h*w;
    result.imagePath = defectimage.path;
    promiseObj.set_value(result);//设置结果
    /*1100ms*/

}

cv::Rect ProcessTile::getDefectStandardRect(cv::Mat& framCroppedImage,int pixX, int pixY, int pixLength, int pixWidth)
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

int ProcessTile::PointHashCode(int x, int y)
{
    int hash = 7;
    hash = 71 * hash + x;
    hash = 71 * hash + y;
    return hash;
}

QString ProcessTile::SyncSaveCurrentTimeImage(cv::Mat& region,QString path/*=""*/)
{
    try{
        if (path == "") {
            // auto time = std::chrono::high_resolution_clock::now();
            // auto nanoseconds = std::chrono::duration_cast<std::chrono::nanoseconds>(time.time_since_epoch()).count();
            int randomNumber = std::rand() % 123567;
            QString time2 = QDateTime::currentDateTime().toString("hh-mm-ss");
            path = "D:/testopencv/defect/"+time2 +"-"+ QString::number(randomNumber)+".jpg";
        }
        std::thread th1(&ProcessTile::saveMatToImage,this,path,region);
        th1.detach();
        return path;
    } catch(...) {
        qDebug() << " ProcessTile::SyncSaveCurrentTimeImage =>An unknown error occurred.";
        // 获取当前的异常信息
        std::exception_ptr eptr = std::current_exception();
        if (eptr) {
            try {
                std::rethrow_exception(eptr);
            } catch (const std::exception& ex) {
                qDebug() << "Exception: " << ex.what();
            }
        }
        return "";
    }
}

bool ProcessTile::getDefectResult(int currentFrame, NewGlassResult& glassResult)
{
    if (frameResultMap.find(currentFrame, glassResult) != false) {
        frameResultMap.erase(currentFrame);
        return true;
    } else {
        return false;
    }
}

void ProcessTile::DoorClampDetection(cv::Mat& region,
                                     cv::Rect& rect,
                                     int id,
                                     std::vector<EdgeElement>& Y1Y2X1X2)
{
    // 获取图像的行数和列数
    int rows = region.rows;
    int cols = region.cols;

    // 用于存储每一行灰度值累加值的数组
    std::vector<int> rowGraySum(rows, 0);

    // 遍历图像的每一行
    for (int i = 0; i < rows; ++i) {
        // 遍历每一行的每一个像素
        for (int j = 0; j < cols; ++j) {
            rowGraySum[i] += region.at<uchar>(i, j);
        }
    }

    // 用于存储colGraySum的梯度变化值的数组
    std::vector<int> rowGraySumGradient(cols - 1, 0);

    // 计算colGraySum的梯度变化
    for (int j = 0; j < cols - 1; ++j) {
        rowGraySumGradient[j] = std::abs(rowGraySum[j + 1] - rowGraySum[j]);
    }

    // 求rowGraySumGradient梯度变化值的最大值和次大致
    int maxValue = rowGraySumGradient[0];
    int secondMaxValue = rowGraySumGradient[0];
    size_t maxIndex = 0;
    size_t secondMaxIndex = 0;

    for (size_t i = 1; i < rowGraySumGradient.size(); ++i) {
        if (rowGraySumGradient[i] > maxValue) {
            secondMaxValue = maxValue;
            secondMaxIndex = maxIndex;
            maxValue = rowGraySumGradient[i];
            maxIndex = i;
        } else if (rowGraySumGradient[i] > secondMaxValue && rowGraySumGradient[i] != maxValue) {
            secondMaxValue = rowGraySumGradient[i];
            secondMaxIndex = i;
        }
    }
    // 判断最大值大于10000，且次大值下标与最大值下标的差值在20以上
    int menjiaY1 = 0,menjiaY2=0;
    if ((maxValue >= 10000 || secondMaxValue >=10000) && cv::abs(maxIndex - secondMaxIndex) > 50){//梯度差大于10000，且两个坐标差值大于20像素，认为找到门夹两条边
        menjiaY1 =  maxIndex;
        menjiaY2 = secondMaxIndex;
    } else if ((maxValue >= 10000 || secondMaxValue >=10000) &&  cv::abs(maxIndex - secondMaxIndex) < 50) {//梯度差大于10000，且两个坐标差值小于20像素，认为找到门夹一条边
        menjiaY1 =  maxIndex;
    }
    //qDebug()<<"menjiaY1 ="<<menjiaY1 <<",menjiaY2 ="<<menjiaY2;
    /*查找垂直图像X轴的直线*/
    // 用于存储每一列灰度值累加值的数组
    std::vector<int> colGraySum(cols, 0);
    // 遍历图像的每一列
    for (int j = 0; j < cols; ++j) {
        // 遍历每一列的每一个像素
        for (int i = 0; i < rows; ++i) {
            colGraySum[j] += region.at<uchar>(i, j);
        }
    }
    // 用于存储colGraySum的梯度变化值的数组
    std::vector<int> colGraySumGradient(cols - 1, 0);

    // 计算colGraySum的梯度变化
    for (int j = 0; j < cols - 1; ++j) {
        colGraySumGradient[j] = std::abs(colGraySum[j + 1] - colGraySum[j]);
        // if (i==5)
        // qDebug() << "第 " << j + 1 << " 列的灰度值累加值为: " << colGraySum[j];
    }
    // for (int j = 0; j < cols - 1; ++j) {
    //     if (i==5)
    //     qDebug() << "第 " << j + 1 << " 列到第 " << j + 2 << " 列的灰度值累加值梯度变化为: " << colGraySumGradient[j];
    // }
    // 求colGraySumGradient梯度变化值的最大值和次大致
    int maxValueC = colGraySumGradient[0];
    int secondMaxValueC = colGraySumGradient[0];
    size_t maxIndexC = 0;
    size_t secondMaxIndexC = 0;

    for (size_t x = 1; x < colGraySumGradient.size(); ++x) {
        if (colGraySumGradient[x] > maxValueC) {
            secondMaxValueC = maxValueC;
            secondMaxIndexC = maxIndexC;
            maxValueC = colGraySumGradient[x];
            maxIndexC = x;
        } else if (colGraySumGradient[x] > secondMaxValueC && colGraySumGradient[x] != maxValueC) {
            secondMaxValueC = colGraySumGradient[x];
            secondMaxIndexC = x;
        }
    }
    //qDebug()<<"i ="<< i<<",maxIndexC ="<<maxIndexC <<",maxValueC ="<<maxValueC <<",secondMaxIndexC ="<<secondMaxIndexC<<",secondMaxValueC ="<<secondMaxValueC;

    // 判断最大值大于10000，且次大值下标与最大值下标的差值在20以上
    int menjiaX1 = 0,menjiaX2 = 0;
    if ((maxValueC >= 10000 || secondMaxValueC >=10000) && cv::abs(maxIndexC - secondMaxIndexC) > 50){//梯度差大于10000，且两个坐标差值大于20像素，认为找到门夹两条边
        menjiaX1 =  maxIndexC;
        menjiaX2 = secondMaxIndexC;
    } else if ((maxValueC >= 10000 || secondMaxValueC >=10000) &&  cv::abs(maxIndex - secondMaxIndexC) < 50) {//梯度差大于10000，且两个坐标差值小于20像素，认为找到门夹一条边
        menjiaX1 =  maxIndexC;
    }
    //qDebug()<<"menjiaX1 ="<<menjiaX1 <<",menjiaX2 ="<<menjiaX2;

    cv::Vec4i GradientPoint(menjiaY1, menjiaY2, menjiaX1, menjiaX2);
    EdgeElement element;
    element.id = id;
    element.point2 = GradientPoint;
    element.rect = rect;
    Y1Y2X1X2.push_back(element);
}


void ProcessTile::DoorClampResultData(std::vector<EdgeElement> Y1Y2X1X2,
                                      std::vector<regionInfor> edgeRegionInfos,
                                      std::vector<DoorClampAndHole>& results)
{
    // 门夹数据拼接
    for (size_t i = 0; i < Y1Y2X1X2.size(); ++i) {
        EdgeElement element = Y1Y2X1X2[i];
        cv::Vec4i point = element.point2;
        if (point[0] > 0 && point[1] > 0 && cv::abs(point[0] - point[1]) > 50) {//门夹在一张小图上
            DoorClampAndHole result;
            result.PixHeight = cv::abs(point[0] - point[1]);
            result.MarginsX  = std::min(point[0],point[1]) + element.rect.y + result.PixHeight/2;//边距X(门夹中心点到X轴坐标)
            if (point[2] > 0 && point[3] > 0 && cv::abs(point[2] - point[3]) > 50) {
                result.PixWidth = cv::abs(point[2] - point[3]);
                result.MarginsY = result.PixWidth /2 + element.rect.x;
                result.Path = edgeRegionInfos[element.id].path;
                result.Region = edgeRegionInfos[element.id].region;
                result.type = SizeType::DoorClam;
                qDebug()<<"class 1: MJPixHeight ="<<result.PixHeight
                         <<", MJPixWidth ="<<result.PixWidth
                         <<",MJMarginsX ="<<result.MarginsX
                         <<", MJMarginsY =" <<result.MarginsY
                         <<", MJPath = "<<result.Path;
                results.push_back(result);
            }
        } else if (point[0] > 0 && point[1] == 0 && cv::abs(point[0] - point[1]) > 50) { // 门夹被切分在连续的小图上
            int gap = i; //间隔了几张小图,初始化为第几张小图
            for (size_t j = i+1; j < Y1Y2X1X2.size(); ++j) {
                EdgeElement elementNext = Y1Y2X1X2[j];
                cv::Vec4i pointNext = elementNext.point2;
                gap = j - i;
                if (pointNext[0] > 0 && pointNext[1] == 0) {//找到门夹的下一幅小图
                    DoorClampAndHole result;
                    int x1 = std::min(std::min(point[2],point[3]), std::min(pointNext[2],pointNext[3]));
                    int x2 = std::max(std::max(point[2],point[3]), std::max(pointNext[2],pointNext[3]));
                    int y1 = 640 - point[0];
                    int y2 = pointNext[0];
                    result.PixHeight = y1 +y2 + (gap -1) * 640;//跨越多张图片的高
                    result.PixWidth = cv::abs(x1 + x2);
                    result.MarginsX  = std::min(y1,y2)+ element.rect.y + result.PixHeight/2;
                    result.MarginsY = result.PixWidth/2 + element.rect.x;
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
                    result.Region = Vresult;
                    result.Path = ProcessTile::SyncSaveCurrentTimeImage(Vresult);
                    result.type = SizeType::DoorClam;
                    qDebug()<<"class 2: MJPixHeight ="<<result.PixHeight
                             <<", MJPixWidth ="<<result.PixWidth
                             <<",MJMarginsX ="<<result.MarginsX
                             <<", MJMarginsY =" <<result.MarginsY
                             <<", MJPath =" << result.Path;
                    results.push_back(result);
                    i = j; // 跳到已经遍历过小图的下标，for循环会自动++。相当于从下一张图片开始遍历
                    break;
                }
            }
        }
    }
}


