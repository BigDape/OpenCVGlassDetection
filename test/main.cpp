#include <iostream>
#include <QObject>
#include <QDir>
#include "HSAlgorithmInterface.h"

typedef HSAlgorithmNamespace::HSAlgorithmInterface* (*createAlgorithmObjectFunc1)();

#include <iostream>
#include <opencv2/opencv.hpp>
#include <math.h>
#include <omp.h>

using namespace std;
using namespace cv;

#include <iostream>
#include <opencv2/opencv.hpp>
static bool isOverlap(cv::Rect& rect1, cv::Rect& rect2) {
    return (std::max(rect1.x, rect2.x) < std::min(rect1.x + rect1.width, rect2.x + rect2.width) &&
            std::max(rect1.y, rect2.y) < std::min(rect1.y + rect1.height, rect2.y + rect2.height));
}

static bool isClose(ConnectedComponent c1, ConnectedComponent c2, int threshold)
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

int main() {
#ifdef false
    // 读取图像
    cv::Mat image = cv::imread("D:/testopencv/tile1.jpg");

    if (image.empty()) {
        std::cout << "无法读取图像。" << std::endl;
    }

    int width = image.cols;
    int height = image.rows;

    // 计算每份的宽度和高度
    int partWidth = width;
    int partHeight = height / 3;

    // 分割并保存三份图像
    for (int i = 0; i < 3; i++) {
        cv::Rect roi(0, i * partHeight, partWidth, partHeight);
        cv::Mat partImage = image(roi);
        std::string filename = "part" + std::to_string(i + 1) + ".jpg";
        cv::imwrite(filename, partImage);
    }

    std::cout << "图像分割并保存完成。" << std::endl;
    return 0 ;
#endif
    try{
    //
    // 动态加载算法组件
    //
    HSAlgorithmNamespace::HSAlgorithmInterface* algorithmPtr = nullptr;   //算法指针
    QString exePath = QDir::currentPath();
    qDebug()<<"exePath ="<<exePath;
    if (algorithmPtr== nullptr) {
        QString dllPath = exePath + "/../algorithm/algorithm.dll";
        HMODULE algorithmDllHandle = LoadLibrary(dllPath.toStdWString().c_str());
        if (!algorithmDllHandle) {
            qDebug() << "Failed to load DLL. Error code: " << GetLastError();
        }
        // 获取创建数据库对象的函数指针
        createAlgorithmObjectFunc1 createFunc = (createAlgorithmObjectFunc1)GetProcAddress(algorithmDllHandle, "createAlgorithmObject");
        if (!createFunc) {
            qDebug() << "Failed to get function pointer. Error code: " << GetLastError() ;
            FreeLibrary(algorithmDllHandle);
        } else {
            qDebug() << "Success to get  createAlgorithmObjectFunc1 function pointer. ";
        }
        algorithmPtr = createFunc();
    }
    std::cout<<"test 1233"<<std::endl;
    cv::Mat image1 = cv::imread("D:/testopencv/1.jpeg");
    cv::Rect rect2(0,0,image1.cols,8600);
    cv::Mat image2 = image1(rect2);

    cv::Mat clonedMat = image2.clone();
    auto start = std::chrono::high_resolution_clock::now();// 开始时间
    cv::Mat grayImage;
    cv::cvtColor(image2, grayImage, cv::COLOR_BGR2GRAY);
    cv::Mat EdgeResult;

    cv::threshold(grayImage, EdgeResult,25,255,cv::THRESH_TOZERO);
    cv::Mat dst;
    cv::Canny(EdgeResult, dst, 20, 80);

    cv::Mat dilatedImage;
    cv::Mat element = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(2, 2));
    cv::dilate(dst, dilatedImage, element);//膨胀

    std::vector<std::vector<cv::Point> > contours;
    cv::findContours(dilatedImage, contours, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_NONE); //找轮廓 138ms cv::CHAIN_APPROX_NONE cv::RETR_EXTERNAL

    qDebug()<<"contours.size() = "<<contours.size();

    //
    // 求轮廓的最大外接矩形(该矩形与上下左右边平行)
    //
    std::vector<int> XXs;
    std::vector<int> YYs;
    cv::RotatedRect maxminAreaRect;    // 带倾斜角度的最大外接矩形
    cv::Rect maxBoundingRect(0,0,0,0); // 平行于坐标轴的最大外接矩形
    std::vector<ConnectedComponent> components;
    std::vector<int> maxIndexS;
    int maxarea = -1;
    for(int i = 0; i < (int)contours.size(); i++) {/* 20ms */
        std::vector<cv::Point> contour = contours[i];
        for (int i = 0; i <(int)contour.size(); ++i) {
            cv::Point point = contour[i];
            XXs.push_back(point.x);
            YYs.push_back(point.y);
        }
        cv::RotatedRect rect = cv::minAreaRect(contour); //获取轮廓的最大外接矩形
        cv::Rect boundingRect = rect.boundingRect();
        double area = boundingRect.width * boundingRect.height;
        if (maxarea <= area) {
            maxarea = area;
            maxIndexS.push_back(i);
        } else {
            if(area > 1000000) {
                maxIndexS.push_back(i);
            }
        }
        ConnectedComponent component;
        component.rect = boundingRect;
        component.area = area;

        components.push_back(component);

        cv::Scalar color(256, 256, 256);
        cv::rectangle(clonedMat, boundingRect, color, 1);//在原图上画框
    }
    std::sort(maxIndexS.begin(), maxIndexS.end(), std::greater<int>());
    for(auto& index: maxIndexS)
        components.erase(components.begin()+index);//找到代表背景的元素（通常是面积最大的那个），去除掉

    // 计算玻璃区域的最大外接矩形
    if (!XXs.empty() && !YYs.empty()) {
        int minX = *std::min_element(XXs.begin(), XXs.end());
        int minY = *std::min_element(YYs.begin(), YYs.end());
        int maxX = *std::max_element(XXs.begin(),XXs.end());
        int maxY = *std::max_element(YYs.begin(),YYs.end());
        maxBoundingRect.x = minX < 0 ? 0 : minX;
        maxBoundingRect.y = minY < 0 ? 0 : minY;
        maxBoundingRect.height = (maxBoundingRect.y + maxY - minY) > grayImage.rows ? (grayImage.rows - maxBoundingRect.y) : (maxY - minY);
        maxBoundingRect.width = (maxBoundingRect.x + maxX - minX) > grayImage.cols ? (grayImage.cols - maxBoundingRect.x) : (maxX - minX);
    }

    // 合并新的区域,todo：待优化
    for (int i = 0; i < (int)components.size(); i++) {
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

    for (int i = 0; i < (int)components.size(); i++) {
        // 单个缺陷的矩形框
        cv::Rect rect = components[i].rect;
        //qDebug()<<"rect=("<<rect.x<<","<<rect.y<<","<<rect.width<<","<<rect.height<<")";
        cv::Scalar color(255, 255, 255);
        cv::rectangle(image2, rect, color, 1);//在原图上画框
    }
    qDebug()<<"components.size()="<<components.size();
    SyncSaveImage(image2,"D:/testopencv/image2.jpg");

    cv::Mat croppedImage0 = grayImage(maxBoundingRect);

    cv::Rect rect(0,0,croppedImage0.cols,256);
    cv::Mat topEdge0 = croppedImage0(rect);
    SyncSaveImage(topEdge0,"D:/testopencv/topEdge0.jpg");
    cv::Rect rect1(croppedImage0.cols-256,0,256,croppedImage0.rows);
    cv::Mat rightEdge0 = croppedImage0(rect1);
    SyncSaveImage(rightEdge0,"D:/testopencv/rightEdge0.jpg");
    cv::Rect rect3(0,0,256,croppedImage0.rows);
    cv::Mat leftEdge0 = croppedImage0(rect3);
    SyncSaveImage(leftEdge0,"D:/testopencv/leftEdge0.jpg");

    // 计算列投影
    cv::Mat verticalProjection;
    cv::reduce(topEdge0, verticalProjection, 0, cv::REDUCE_SUM, CV_32S);

    // 求行投影的平均值
    cv::Scalar meanValue = cv::mean(verticalProjection);
    int rangeValue = 0;//波动范围参数，根据实际情况修改
    qDebug()<<"meanValue[0] =" << meanValue[0];



    // 计算大于平均值的位置
    bool pixcontinue =  false;
    int startloc = 0;
    cv::Rect tmprect;
    cv::Mat tmpregion;
    for (int i = 0; i < verticalProjection.cols -1; ++i) {
        if (verticalProjection.at<int>(0, i) > (meanValue[0]- rangeValue)) {
            pixcontinue = true;
        } else {
            if (pixcontinue == true) {
                pixcontinue = false;
                if (i-startloc > 5) {//连续间隔大于6
                    cv::Rect rect(startloc,30,i-startloc,160);
                    cv::Mat defect0 = topEdge0(rect);
                    tmprect = rect;
                    tmpregion = defect0;
                    cv::Scalar color(255, 255, 255);
                    cv::rectangle(topEdge0, rect, color, 1);//在原图上画框

                    QString path = "D:/testopencv/defect/"+QString::number(i)+".jpg";
                    SyncSaveImage(defect0,path);
                }
            }
            startloc = i;
        }
    }
    QString path1 = "D:/testopencv/topEdge1.jpg";
    SyncSaveImage(topEdge0,path1);


    ClassifyParam param;
    param.regionRect = tmprect;
    param.region = tmpregion;
    algorithmPtr->TestExecu(param);

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> duration = end - start;
    qDebug() << "Algorithm time：" << duration.count() << " ms";
    // SyncSaveImage(dilatedImage,"D:/testopencv/dilatedImage.jpg");
    std::this_thread::sleep_for(std::chrono::seconds(15));
    // cv::Rect rect1(8278,480,274,774);
    // cv::Mat model1 = image1(rect1);

    // cv::Rect rect2(8968,1072,972,1292);
    // cv::Mat model2 = image1(rect2);

    // QString path1 = "D:/testopencv/glass/model1.jpg";
    // cv::imwrite(path1.toStdString(), model1);

    // QString path2 = "D:/testopencv/glass/model2.jpg";
    // cv::imwrite(path2.toStdString(), model2);

    // qDebug()<<"image1 sucess";
    // cv::Mat grayImage;
    // cv::cvtColor(image1, grayImage, cv::COLOR_BGR2GRAY);




    } catch(...) {
        qDebug() << "main test An unknown error occurred.";
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

    return 0;
}
