#ifndef PROCESSTILE_H
#define PROCESSTILE_H

#include <QObject>
#include <QQueue>
#include <QString>
#include <QtDebug>
#include <QThreadPool>
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <mutex>
#include <atomic>
#include "HSTool.h"

// 合并元素的结构体
struct ConnectedComponent {
    cv::Rect rect;
    int area;
    int x;
    int y;
};

class ProcessTile
{
public:
    ProcessTile(){}
    void OfflineTileImageProcess(QString fullpath);

    void CV_DefectsDetected(cv::Mat image1,
                                         cv::Mat image2,
                                         cv::Mat image3,
                                         double& length,
                                         double& width,
                                        QString& imagePath);
    std::vector<NewDefectUnitData> getDefectResult();//获取每一帧图片
private:
    void saveMatToImage(QString fullpath,cv::Mat region);
    void cropRectangleMat(const cv::Mat image, cv::Mat &dst, int row1y, int Column1x, int row2y, int Column2x);
    void prewittEdgeDetection(cv::Mat& src, cv::Mat& dst); //Prewitt边缘检测
    void getBaseLineFromImage(cv::Mat& region, cv::Mat& baseline);//获取基准矩阵
    void edgeDefectDetection(cv::Mat& region,
                             std::vector<regionInfor>& edgeRegionInfos,
                             int topAddition,
                             int bottomAddition,
                             int leftAddition,
                             int rightAddition);//边部缺陷检出
    /**
     * @brief YoloDefectClassification 调用YOLO数据模型计算
     * @param [in] Regions 缺陷小图
     * @param [out] frameGlassResult 每帧图片结果
     */
    void YoloDefectClassification(std::vector<regionInfor>& Regions);
    void image1DefectsDetected(cv::Mat& image,
                               double& glassLength,
                               double& glassWidth,
                               QString& imagePath);
    void image2DefectsDetected(cv::Mat& image);
    void image3DefectsDetected(cv::Mat& image);
    bool isClose(ConnectedComponent c1, ConnectedComponent c2, int threshold);
    void swap(ConnectedComponent& c1, ConnectedComponent& c2);
    void HoughCircleRadius(cv::Mat image, double& diameter);
    void LengthWidthInscribedRectangle(cv::Mat image, double& width, double& Height, double& area);
    /**
     * @brief affineTransformation 仿射变换
     * @param oldvertices 斜的四边形四个顶点
     * @param newvertices 新的四边形四个顶点
     * @param image 斜的图形
     * @param warpedImage 仿射变换后的图形
     */
    void affineTransformation(std::vector<cv::Point2f> oldvertices,
                              std::vector<cv::Point2f> newvertices,
                              cv::Mat image,
                              cv::Mat& warpedImage);
    void calculateBoundingRectangle(cv::Rect maxBoundingRect,
                                    cv::RotatedRect Rect1,
                                    std::vector<cv::Point2f>& oldvertices,
                                    std::vector<cv::Point2f>& newvertices);
    void CuttinGlassDdges(cv::Mat Frame, cv::Mat& result);
    void threadProcessClassification(regionInfor defectimage);
    /**
     * @brief getDefectStandardRect 获取缺陷小图标准矩形框
     * @param framCroppedImage 面部整图
     * @param pixX 标准矩形框X中点
     * @param pixY 标准矩形框Y中点
     * @param pixLength 标准矩形框长度
     * @param pixWidth 标准矩形框宽度
     * @return 在面部整图上需要切割的矩形
     */
    cv::Rect getDefectStandardRect(cv::Mat& framCroppedImage,
                                                int pixX,
                                                int pixY,
                                                int pixLength,
                                                int pixWidth);
    int PointHashCode(int x, int y);

    QString SyncSaveCurrentTimeImage(cv::Mat& region, QString path=QString(""));//异步保存图片

private:
    cv::dnn::Net net; //神经网络
    std::mutex mut;   //锁
    std::atomic<int> defectid = 0;     // 缺陷id（每块玻璃的id）
    std::unordered_map<int,cv::Rect> rectMap;
    SafeDefinitionThreadSafeVector<NewDefectUnitData> defectResult; //缺陷结果
};


#endif // PROCESSTILE_H
