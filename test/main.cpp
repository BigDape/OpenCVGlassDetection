#include <iostream>
#include <QObject>
#include <QDir>
#include "HSAlgorithmInterface.h"

typedef HSAlgorithmNamespace::HSAlgorithmInterface* (*createAlgorithmObjectFunc1)();

#include <iostream>
#include <opencv2/opencv.hpp>
#include <math.h>

using namespace std;
using namespace cv;

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
    cv::Mat image1 = cv::imread("D:/testopencv/reflectionDarkImage6.jpg");

    cv::Rect rect1(8278,480,274,774);
    cv::Mat model1 = image1(rect1);

    cv::Rect rect2(8968,1072,972,1292);
    cv::Mat model2 = image1(rect2);

    QString path1 = "D:/testopencv/glass/model1.jpg";
    cv::imwrite(path1.toStdString(), model1);

    QString path2 = "D:/testopencv/glass/model2.jpg";
    cv::imwrite(path2.toStdString(), model2);

    qDebug()<<"image1 sucess";
    cv::Mat grayImage;
    cv::cvtColor(image1, grayImage, cv::COLOR_BGR2GRAY);

    algorithmPtr->TestExecu(grayImage);


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
