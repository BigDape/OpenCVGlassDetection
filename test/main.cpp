#include <iostream>
#include <QObject>
#include <QDir>
#include "HSAlgorithmInterface.h"

typedef HSAlgorithmNamespace::HSAlgorithmInterface* (*createAlgorithmObjectFunc1)();

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
    cv::Mat image1 = cv::imread("D:/testopencv/part2.jpg");
    qDebug()<<"image1 sucess";
    cv::Mat grayImage;
    cv::cvtColor(image1, grayImage, cv::COLOR_BGR2GRAY);

    algorithmPtr->TestExecu(grayImage);
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

    // 霍夫圆变换
    // cv::Mat image1 = cv::imread("D:/testopencv/defect/defect137.jpg");
    // qDebug()<<"image1 sucess";
    // cv::Mat grayImage;
    // cv::cvtColor(image1, grayImage, cv::COLOR_BGR2GRAY);
    // std::vector<cv::Vec3f> circles;
    // cv::HoughCircles(grayImage, circles, cv::HOUGH_GRADIENT, 1, 50, 100, 30, 0, 0);
    // for (size_t i = 0; i < circles.size(); i++) {
    //     float x = circles[i][0];
    //     float y = circles[i][1];
    //     float radius = circles[i][2];
    //     qDebug() << "Circle " << i + 1 << " center: (" << x << ", " << y << "), radius: " << radius;
    // }

    // 最大内接矩形
    // cv::Mat image1 = cv::imread("D:/testopencv/defect/defect132.jpg");
    // qDebug()<<"image1 sucess";
    // cv::Mat grayImage;
    // cv::cvtColor(image1, grayImage, cv::COLOR_BGR2GRAY);
    // std::vector<std::vector<cv::Point>> contours;
    // std::vector<cv::Vec4i> hierarchy;
    // cv::findContours(grayImage, contours, hierarchy, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);

    // if (contours.empty()) {
    //     std::cout << "No contours found." << std::endl;
    // }

    // double maxArea = 0;
    // double maxWidth = 0;
    // double maxHeight = 0;
    // for (const auto& contour : contours) {
    //     cv::RotatedRect rotatedRect = cv::minAreaRect(contour);
    //     double width = rotatedRect.size.width;
    //     double height = rotatedRect.size.height;
    //     double area = width * height;
    //     if (area > maxArea) {
    //         maxArea = area;
    //         maxWidth = static_cast<int>(width);
    //         maxHeight = static_cast<int>(height);
    //     }
    // }
    // qDebug()<<"maxWidth = "<<maxWidth <<", maxHeight ="<<maxHeight;
    return 0;
}
