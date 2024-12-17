#ifndef MATCHTEMPLATE_H
#define MATCHTEMPLATE_H

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
#include <QObject>

class MatchTemplate: public QObject
{
    Q_OBJECT
public:
    explicit MatchTemplate(QObject *parent = nullptr);
    ~MatchTemplate();
    void setTemplate(std::vector<QString> modelPaths);
    bool onMatchSilkscreen(cv::Mat image1,
                           cv::Mat image2,
                           cv::Mat targetImage,
                           std::vector<GlassSizeInfo2>& sizeRes,
                           double minimumSimilarity = 0.3);
    cv::Mat GenerateMask(cv::Mat templateImage, int threshold = 128);

    /**
     * @brief nonMaxSuppression 获取模版匹配里面多个符合要求的结果
     * @param result 模版匹配的结果
     * @param thresholdValue 相似度的最小阈值0~1
     * @param locations 获取到的结果的位置
     * @param radius 清除已获得匹配的相似度值，将其周围一定范围内的匹配度置零
     */
    void nonMaxSuppression(int match_method,
                           cv::Mat& result,
                           double thresholdValue,
                           std::vector<cv::Point>& locations,
                           int radius = 10);

    /**
     * @brief inResult 将匹配到的丝印结果整理成界面所需要的结构体
     * @param locations 匹配到的最佳丝印顶点
     * @param image1 透射场玻璃整图
     * @param image2 反射亮场的玻璃整图
     * @param targetImage 反射暗场的玻璃整图
     * @param templateImageGray 模版灰度图
     * @param sizeRes 丝印的结果
     */
    void inResult(std::vector<cv::Point> locations,
                  cv::Mat image1,
                  cv::Mat image2,
                  cv::Mat targetImage,
                  cv::Mat templateImageGray,
                  std::vector<GlassSizeInfo2>& sizeRes);

private:
    std::vector<cv::Mat> templateImages;   //模版图像
};

#endif // MATCHTEMPLATE_H
