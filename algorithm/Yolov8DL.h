#ifndef YOLOV8DL_H
#define YOLOV8DL_H

#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/dnn.hpp>
#include <QDir>
#include <opencv2/core/ocl.hpp>
// #include <opencv2/cudaarithm.hpp>
#include <opencv2/cudaimgproc.hpp>
#include <opencv2/dnn/dnn.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/core/cuda.hpp>
#include <opencv2/dnn.hpp>
#include <opencv2/cudawarping.hpp>
#include <opencv2/cudafilters.hpp>
#include <cuda_runtime.h>
#include <device_launch_parameters.h>
#include <vector>
#include <opencv2/core/cuda.hpp>
#include<future>      //std::future std::promise
#include <HSTool.h>

class Yolov8DL
{
public:
    Yolov8DL();
    void YoloDefectClassification(std::vector<regionInfor>& Regions, std::vector<GlassDefect2>& unitVec);
    void threadProcessClassification(regionInfor defectimage, std::promise<GlassDefect2>& promiseObj);
private:
    cv::dnn::Net net; //神经网络
    std::mutex mut;   //锁
};

#endif // YOLOV8DL_H
