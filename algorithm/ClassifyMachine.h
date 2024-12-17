#ifndef CLASSIFYMACHINE_H
#define CLASSIFYMACHINE_H

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
#include <HSTool.h>

class ClassifyMachine
{
public:
    ClassifyMachine();

    int IdentificationDefect(ClassifyParam param);

    void GetFeatures(cv::Rect regionRect, cv::Mat region, cv::Mat& featureVector);

    void GetCoOccUrrenceMatrix(const cv::Mat& image,
                               int a,
                               int b,
                               std::vector<std::vector<double>> & cooccurrence_matrix);

    std::vector<cv::Mat> laplacianPyramid(cv::Mat inputImage, int numLevels);
    void directionalFiltering(cv::Mat& inputImage,
                              cv::Mat& horizontalResult,
                              cv::Mat& verticalResult);
    //  Contourlet 变换特征
    void ContourletFeature(cv::Mat image);

    double calculateEccentricity(cv::Mat binaryImage);

    double calculateRoundness(cv::Mat image);

    double secondDifferenceMeasure(cv::Mat region, bool isHorizontal);

    double grayscaleMean(cv::Mat region);

    double AspectRatio(cv::Rect regionRect);

    double RegionArea(cv::Mat region, int Threshold);
private:
    cv::Mat correlationCoefficient;
};

#endif // CLASSIFYMACHINE_H
