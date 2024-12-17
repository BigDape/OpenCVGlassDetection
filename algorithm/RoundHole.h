#ifndef ROUNDHOLE_H
#define ROUNDHOLE_H

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
#include <opencv2/core/cuda.hpp>
#include <HSTool.h>

class RoundHole
{
public:
    RoundHole();

    void HoughCircleRadius(cv::Mat image,
                           std::vector<double>& diameters,
                           std::vector<cv::Point>& centers);
};

#endif // ROUNDHOLE_H
