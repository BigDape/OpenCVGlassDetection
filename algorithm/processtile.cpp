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
                                     double& length,
                                     double& width,
                                     QString& imagePath)
{
    ProcessTile::image1DefectsDetected(image1, length,width,imagePath);
    ProcessTile::image2DefectsDetected(image2);
    ProcessTile::image3DefectsDetected(image3);
}

void ProcessTile::saveMatToImage(QString fullpath,cv::Mat region )
{
    std::string filename = fullpath.toStdString();
    bool r = cv::imwrite(filename, region);
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

void ProcessTile::edgeDefectDetection(cv::Mat& region,
                                      std::vector<regionInfor>& edgeRegionInfos,
                                      int topAddition,
                                      int bottomAddition,
                                      int leftAddition,
                                      int rightAddition)
{
    //
    // 将边部全部切分，用来识别崩边和门夹
    //
    int regionRow = region.rows;
    int regionCol = region.cols;
    //
    // 沿着图像的最上边从左到右依次裁剪小图
    //
    if (topAddition != 0) {
        for (int i =0; i < regionCol/640; ++i) {
            cv::Rect rect(i*640, 0, 640, 640);
            cv::Mat topEdgeRegion = region(rect);
            regionInfor info;
            info.path =ProcessTile::SyncSaveCurrentTimeImage(topEdgeRegion);
            info.region = topEdgeRegion;
            edgeRegionInfos.push_back(info);
        }
        //不足256*256部分也截取
        if (regionCol%640 != 0) {
            int lastX = regionCol - (regionCol%640);
            cv::Rect rect(lastX, 0, regionCol%640, 640);
            cv::Mat topEdgeRegion = region(rect);
            regionInfor info;
            info.path = ProcessTile::SyncSaveCurrentTimeImage(topEdgeRegion);
            info.region = topEdgeRegion;
            edgeRegionInfos.push_back(info);
            ProcessTile::SyncSaveCurrentTimeImage(topEdgeRegion);
        }
    }
    //
    // 沿着图像的最右边开始从上往下裁剪小图
    //
    if (rightAddition != 0) {
        for (int i = 1; i < regionRow/640; ++i) {
            cv::Rect rect(regionCol-640, i*640, 640, 640);
            cv::Mat rightEdgeRegion = region(rect);
            regionInfor info;
            info.path = ProcessTile::SyncSaveCurrentTimeImage(rightEdgeRegion);
            info.region = rightEdgeRegion;
            edgeRegionInfos.push_back(info);
        }
        if (regionRow%640 != 0) {
            int lastY = regionRow - (regionRow%640);
            cv::Rect rect(regionCol-640,lastY, 640, regionRow%640);
            cv::Mat rightEdgeRegion = region(rect);
            regionInfor info;
            info.path = ProcessTile::SyncSaveCurrentTimeImage(rightEdgeRegion);
            info.region = rightEdgeRegion;
            edgeRegionInfos.push_back(info);
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
            info.path = ProcessTile::SyncSaveCurrentTimeImage(bottomEdgeRegion);
            info.region = bottomEdgeRegion;
            edgeRegionInfos.push_back(info);
        }
        if (regionCol%640 != 0) {
            int lastX = regionCol - (regionCol%640) - 640;
            cv::Rect rect(lastX, regionRow - 640, regionCol%640 , 640);
            cv::Mat bottomEdgeRegion = region(rect);
            regionInfor info;
            info.path = ProcessTile::SyncSaveCurrentTimeImage(bottomEdgeRegion);
            info.region = bottomEdgeRegion;
            edgeRegionInfos.push_back(info);
        }
    }
    //
    // 沿着图像的最左边开始裁剪小图
    //
    if (leftAddition != 0) {
        for (int i = 1; i < regionRow/640 -1; ++i) {
            cv::Rect rect(0, i*640, 640, 640);
            cv::Mat leftEdgeRegion = region(rect);
            regionInfor info;
            info.path = ProcessTile::SyncSaveCurrentTimeImage(leftEdgeRegion);
            info.region = leftEdgeRegion;
            edgeRegionInfos.push_back(info);
        }
        if (regionRow % 640 != 0) {
            int lastY = regionRow - (regionRow%640) - 640;
            cv::Rect rect(0,lastY, 640, regionRow%640);
            cv::Mat leftEdgeRegion = region(rect);
            regionInfor info;
            info.path = ProcessTile::SyncSaveCurrentTimeImage(leftEdgeRegion);
            info.region = leftEdgeRegion;
            edgeRegionInfos.push_back(info);
        }
    }
}

void ProcessTile::YoloDefectClassification(std::vector<regionInfor>& Regions)
{
    auto start = std::chrono::high_resolution_clock::now();// 开始时间
    // 加载模型
    net = cv::dnn::readNetFromONNX("D:/best.onnx");
    net.setPreferableBackend(cv::dnn::DNN_BACKEND_CUDA);
    net.setPreferableTarget(cv::dnn::DNN_TARGET_CUDA);
    if (!net.empty()) {
        qDebug()<<"!net.empty()";
        std::vector<std::thread> threads;
        //
        // 缺陷检测
        //
        qDebug()<<"Regions.size()"<<Regions.size();
        for (int i = 0 ; i < (int)Regions.size(); ++i) {
            threads.push_back(std::thread(&ProcessTile::threadProcessClassification, this, Regions[i]));
        }
        for (auto& th : threads) {
            if (th.joinable()) {
                th.join();
            }
        }
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double, std::milli> duration = end - start;
        qDebug() << "time：" << duration.count() << " ms";
    } else {
        qDebug()<<"Load onnx model is fail.";
    }

}

void ProcessTile::image1DefectsDetected(cv::Mat& image,
                                        double& glassLength,
                                        double& glassWidth,
                                        QString& imagePath)
{
    int DeviceCount = cv::cuda::getCudaEnabledDeviceCount();
    if (DeviceCount < 1) {
        std::cout << "No GPU support." << std::endl;
        return;
    }
    std::cout << "GPU support available. Device Count ="<<DeviceCount<< std::endl;
    if (image.rows > 0 ) {
        cv::setNumThreads(26);
        auto start = std::chrono::high_resolution_clock::now();// 开始时间
        //
        // 边缘检测
        //
        cv::Mat cannyEdges;
        cv::Canny(image, cannyEdges, 50, 150);
        // std::string filename2 = "D:/testopencv/cannyEdges.jpg";
        // cv::imwrite(filename2, cannyEdges);
       // 获取region
       std::vector<std::vector<cv::Point> > contours;
       cv::findContours(cannyEdges, contours, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_NONE); //找轮廓
       // 求轮廓的最大外接矩形(该矩形与上下左右边平行)
       double maxArea = 0;
       int maxAreaContourIndex = -1;
       cv::RotatedRect maxminAreaRect; //最大外接矩形
       cv::Rect maxBoundingRect(0,0,0,0);
       qDebug()<<"contours.size() = "<<contours.size();
       for(int i = 0; i < (int)contours.size(); i++) {
           std::vector<cv::Point> contour = contours[i];
           // 获取轮廓的最大外接矩形
           cv::RotatedRect rect = cv::minAreaRect(contour);
           cv::Rect boundingRect = rect.boundingRect();
           double area = boundingRect.width * boundingRect.height;
           if (area > maxArea) {
               maxArea = area;
               maxAreaContourIndex = i;
               maxminAreaRect = rect;
               maxBoundingRect = boundingRect;
           }
       }
       qDebug()<<"maxAreaContourIndex ="<<maxAreaContourIndex;

       // 找到玻璃区域
       if (maxAreaContourIndex != -1) {
           std::vector<cv::Point2f> oldvertices;//原始图像四个顶点坐标
           std::vector<cv::Point2f> newvertices; // 修正倾斜图像四个顶点坐标
           ProcessTile::calculateBoundingRectangle(maxBoundingRect,maxminAreaRect, oldvertices, newvertices);

           // todo:优化仿射变换，速度太慢
           // 仿射变换原图
           cv::Mat warpedImage;//仿射变换后的图片
           ProcessTile::affineTransformation(oldvertices,
                                             newvertices,
                                             image,
                                             warpedImage);
           // std::string filename45 = "D:/testopencv/warpedImage.jpg";
           // cv::imwrite(filename45, warpedImage);
           // 结束时间

            // 仿射变换二值图像
           cv::Mat warpedEageImage;//仿射变换后的二值图片
           ProcessTile::affineTransformation(oldvertices,
                                             newvertices,
                                             cannyEdges,
                                             warpedEageImage);
           // std::string filename46 = "D:/testopencv/warpedEageImage.jpg";
           // cv::imwrite(filename46, warpedEageImage);

           qDebug()<<"最大外轮廓的面积："<<maxArea;

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

           // std::string filename47 = "D:/testopencv/croppedEdgeImage.jpg";
           // cv::imwrite(filename47, croppedEdgeImage);

           //
           // 计算长宽
           //
           glassLength = maxminAreaRect.size.width;
           glassWidth = maxminAreaRect.size.height;
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
                                            rightAddition);


           //
           // 面部缺陷检出
           //

           cv::Mat framCroppedImage;
           ProcessTile::CuttinGlassDdges(croppedImage, framCroppedImage);//将图片的四周640个像素切割（去边）
           cv::Mat framcroppedEdgeImage;
           ProcessTile::CuttinGlassDdges(croppedEdgeImage, framcroppedEdgeImage);//将图片的四周640个像素切割（去边）

           std::string filename3 = "D:/testopencv/framCroppedImage.jpg";
           cv::imwrite(filename3, framCroppedImage);
           std::string filename4 = "D:/testopencv/framcroppedEdgeImage.jpg";
           cv::imwrite(filename4, framcroppedEdgeImage);

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

           //
           // 保存到本地
           //
           std::vector<regionInfor> defectRegions;
           for (int i = 0; i < (int)components.size(); i++) {
               // 单个缺陷的矩形框
               cv::Rect rect = components[i].rect;
               if (components[i].rect.area() >= AREATHRESHOLD ){
                   rect.x = rect.x + 32; //rect是面部坐标，转化为玻璃坐标
                   rect.y = rect.y + 32;
                    cv::Scalar color(std::rand() % 256, std::rand() % 256, std::rand() % 256);
                   cv::rectangle(croppedImage, rect, color, 2);//在原图上画框
                   // cv::rectangle(framCroppedImage, yoloRect, cv::Scalar(255, 255, 0), 2);//在原图上画框
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
           auto end = std::chrono::high_resolution_clock::now();
           std::chrono::duration<double, std::milli> duration = end - start;
           qDebug() << "time：" << duration.count() << " ms";

           // 装置90度异步保存图片
           QString filePath = "D:/testopencv/croppedImage.jpg";
           cv::Mat NewCroppedImage;
           cv::transpose(croppedImage, NewCroppedImage);
           cv::flip(NewCroppedImage, NewCroppedImage, 0);
           imagePath = ProcessTile::SyncSaveCurrentTimeImage(NewCroppedImage,filePath);

           // 合并边图和面部图，进行分类
           std::vector<regionInfor> mergeRegions;
           mergeRegions.reserve(edgeregions.size() + defectRegions.size());
           mergeRegions.insert(mergeRegions.end(), edgeregions.begin(), edgeregions.end());
           mergeRegions.insert(mergeRegions.end(), defectRegions.begin(), defectRegions.end());
           ProcessTile::YoloDefectClassification(mergeRegions);
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
    cv::Mat grayImage;
    cv::cvtColor(image, grayImage, cv::COLOR_BGR2GRAY);
    std::vector<cv::Vec3f> circles;
    cv::HoughCircles(grayImage, circles, cv::HOUGH_GRADIENT, 1, 50, 100, 30, 0, 0);
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
    cv::warpPerspective(image, warpedImage, warpMatrix, image.size());
}

void ProcessTile::calculateBoundingRectangle(cv::Rect maxBoundingRect,
                                             cv::RotatedRect Rect1,
                                             std::vector<cv::Point2f>& oldvertices,
                                             std::vector<cv::Point2f>& newvertices)
{
    //
    // 在原图上，四个顶点
    //
    cv::Point2f P[4];
    Rect1.points(P);
    for (int  i =0 ; i < 4; ++i) {
        oldvertices.push_back(P[i]);
        qDebug()<<"oldvertices, X="<<P[i].x<<",Y="<<P[i].y;
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

void ProcessTile::threadProcessClassification(regionInfor defectimage)
{
    cv::Mat threeChannelImage;
    cv::cvtColor(defectimage.region, threeChannelImage, cv::COLOR_BGRA2BGR);

    auto start = std::chrono::high_resolution_clock::now();// 开始时间
    cv::Mat blob;
    cv::dnn::blobFromImage(threeChannelImage, blob, 1.0 / 255.0, cv::Size(640, 640), cv::Scalar(), false, false);
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> duration = end - start;
    qDebug() << "time：" << duration.count() << " ms";
    // 准备输入
    std::vector<cv::Mat> outputs;
    mut.lock();
    net.setInput(blob);//1,3/640/640
    net.forward(outputs, net.getUnconnectedOutLayersNames());// 前向传播并获取输出
    mut.unlock();
    int rows = outputs[0].size[1];
    int dimensions = outputs[0].size[2];
    qDebug()<<"Edge rows ="<<rows<<", dimensions="<<dimensions;//yolo8 dimensions > rows
    rows = outputs[0].size[2];
    dimensions = outputs[0].size[1];
    outputs[0] = outputs[0].reshape(1, dimensions);
    cv::transpose(outputs[0], outputs[0]);

    float* data = (float*)outputs[0].data;
    cv::Point class_id1;
    double maxClassScore1;
    cv::Mat res1 = outputs[0](cv::Rect(4,0,7,rows));//std::vector<std::string> classes={ "JieShi_Min", "MaoXu_Min", "QiPao_Min", "ShuiDi_Min", "BoLiXue_Min", "HeiDian_Min", "HuaShang_Min"};
    cv::minMaxLoc(res1, 0, &maxClassScore1, 0, &class_id1);
    data += dimensions*class_id1.y;
    float x = data[0];
    float y = data[1];
    float w = data[2];
    float h = data[3];
    qDebug()<<"maxClassScore1 ="<<maxClassScore1<<",class_id1 ="<<class_id1.x<<",class_id1.y="<<class_id1.y<<"x="<<x<<",y="<<y<<",w="<<w<<",h="<<h;
    qDebug()<<"defectimage.pat ="<<defectimage.path;
    NewDefectUnitData result;
    result.id = ++defectid;
    result.time = QDateTime::currentDateTime().toString().toStdString().data();
    result.type = class_id1.x;
    result.pixLength = h;
    result.pixWidth = w;
    result.pixX = x;
    result.pixY = y;
    result.pixArea = h*w;
    result.imagePath =defectimage.path;
    defectResult.push(result);
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
            auto time = std::chrono::high_resolution_clock::now();
            auto nanoseconds = std::chrono::duration_cast<std::chrono::nanoseconds>(time.time_since_epoch()).count();
            QString time2 = QDateTime::currentDateTime().toString("hh-mm-ss");
            path = "D:/testopencv/defect/"+time2 +"-"+ QString::number(nanoseconds%1000000)+".jpg";
        }
        std::thread th1(&ProcessTile::saveMatToImage,this,path,region);
        th1.detach();
        return path;
    } catch(...) {
        qDebug() << "An unknown error occurred.";
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

std::vector<NewDefectUnitData> ProcessTile::getDefectResult()
{
    std::vector<NewDefectUnitData> res = defectResult.vector_;
    defectResult.clear();
    return defectResult.vector_;
}