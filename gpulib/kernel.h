#ifndef KERNEL_H
#define KERNEL_H

#include <cuda_runtime.h>
#include <device_launch_parameters.h>
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/cudaarithm.hpp>
#include <opencv2/cudaimgproc.hpp>
#include <opencv2/dnn/dnn.hpp>

extern "C" void cudaProcessClassification(cv::Mat defectimage, cv::dnn::Net net);

#endif // KERNEL_H
