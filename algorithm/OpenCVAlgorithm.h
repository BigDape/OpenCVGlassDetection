#ifndef OPENCVALGORITHM_H
#define OPENCVALGORITHM_H

#include <opencv2/opencv.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include "HSAlgorithmInterface.h"

class Yolov8DL;
class RoundHole;
class MatchTemplate;
class ClassifyMachine;
class OpenCVAlgorithm: public HSAlgorithmNamespace::HSAlgorithmInterface
{
public:
    OpenCVAlgorithm();
    virtual ~OpenCVAlgorithm();
    virtual void HorizontalPuzzle(int currentframe,
                        std::vector<cv::Mat> mat0,
                        std::vector<cv::Mat> mat1,
                        std::vector<CameraCropArg> args,
                        cv::Mat& image1,
                        cv::Mat& image2,
                        cv::Mat& image3) override;
    virtual void VerticalPuzzle(NewGlassResult result,
                                cv::Mat projectionImage,
                                cv::Mat reflectionLightImage,
                                cv::Mat reflectionDarkImage,
                                cv::Mat& glassRegion0,
                                cv::Mat& glassRegion1,
                                cv::Mat& glassRegion3) override;
    virtual void setTemplate(std::vector<QString> modelPaths) override;
    virtual bool onMatchSilkscreen(cv::Mat image1,
                                   cv::Mat image2,
                                   cv::Mat targetImage,
                                   std::vector<GlassSizeInfo2>& sizeRes,
                                   double minimumSimilarity) override;
    virtual bool onMatchHole(cv::Mat image0,
                             cv::Mat image1,
                             cv::Mat image2,
                             std::vector<GlassSizeInfo2>& sizeRes) override;

    virtual int PartGlassAB(cv::Rect rect, double pixAccuracy, bool& AisLeft) override;
    virtual void RegisterResultCallback(CallbackFun func) override;
    virtual NewGlassResult SyncExecu(int& currentFrameCount,
                       cv::Mat& image1,
                       cv::Mat& image2,
                       cv::Mat& image3) override;
    virtual void TestExecu(cv::Mat& image) override;
    virtual void Stop() override;
    virtual void Exit() override;

private:
    void bathroomDefectsDetected(cv::Mat& image,
                                 int currentframe,
                                 std::function<void (NewGlassResult result)> mainFunc);
    void EdgeDetectionFunction(cv::Mat src, cv::Mat& dst);
    void calculateBoundingRectangle(CV_GLASSPART part,
                                               cv::Rect maxBoundingRect,
                                               cv::RotatedRect Rect1,
                                               std::vector<cv::Point2f>& oldvertices,
                                               std::vector<cv::Point2f>& newvertices);
    void affineTransformation(std::vector<cv::Point2f> oldvertices,
                                         std::vector<cv::Point2f> newvertices,
                                         cv::Mat image,
                                         cv::Mat& warpedImage);
    void edgeDefectDetection(cv::Mat& region,
                                        std::vector<regionInfor>& edgeRegionInfos,
                                        int topAddition,
                                        int bottomAddition,
                                        int leftAddition,
                                        int rightAddition,
                                        std::vector<GlassSizeInfo2>& results);
    void edgeDefectDetection2(cv::Mat& region0,
                              cv::Mat& region1,
                              cv::Mat& region2,
                              int topAddition,
                              int bottomAddition,
                              int leftAddition,
                              int rightAddition,
                              std::vector<EdgeInfo>& edges,
                              cv::Mat& FrameRegion);

    void edgePartDefect(std::vector<EdgeInfo> edges, std::vector<GlassDefect2>& edgeDefect);


    void DoorClampDetection(cv::Mat& region,
                                       cv::Rect& rect,
                                       int id,
                                       std::vector<EdgeElement>& Y1Y2X1X2);
    void DoorClampResultData(std::vector<EdgeElement> Y1Y2X1X2,
                                        std::vector<regionInfor> edgeRegionInfos,
                                        std::vector<GlassSizeInfo2>& results);
    void CuttinGlassDdges(cv::Mat Frame, cv::Mat& result);
    bool isClose(ConnectedComponent c1, ConnectedComponent c2, int threshold);
    void swap(ConnectedComponent& c1, ConnectedComponent& c2);
    void HoughCircleRadius(cv::Mat image, double& diameter);
    cv::Rect getDefectStandardRect(cv::Mat& framCroppedImage,int pixX, int pixY, int pixLength, int pixWidth);
    int PointHashCode(int x, int y);
    NewGlassResult MeddiCookerDefectsDetected(cv::Mat image0,
                                                cv::Mat image1,
                                                cv::Mat image2,
                                              int currentframe);
    CV_GLASSPART DetermineGlassPart(cv::Rect maxBoundingRect, int imageRows);
private:
    /**
     * @brief stitchFieldImages 拼接单个光场的两个相机的照片
     * @param [in] arg0  相机0的裁剪参数，通过界面标定而来
     * @param [in] mat00 相机0拍摄到的原始图片
     * @param [in] arg1  相机1的裁剪参数，通过界面标定而来
     * @param [in] mat10 相机1拍摄的原始图片
     * @param [out] concatImage 结果数据，一帧拼接好的单个光场的图片
     */
    void stitchFieldImages(int currentframe,
                            CameraCropArg arg0,
                           cv::Mat mat00,
                           CameraCropArg arg1,
                           cv::Mat mat10,
                           cv::Mat& concatImage);

private:
    std::queue<NewGlassResult> ResultQue; //结果队列
    CallbackFun mainFunction; //显示结果函数
    cv::dnn::Net net; //神经网络
    std::mutex mut;   //锁
    std::atomic<int> defectid = 0;     // 缺陷id（每块玻璃的id）
    ThreadSafeUnorderedMap<int,NewGlassResult> frameResultMap; // 每帧结果数据
    std::atomic<bool> isGPU = false;
    std::atomic<int> siyinid = 0;
    std::shared_ptr<Yolov8DL> yolov8DLPtr = nullptr; //深度学习模型
    std::shared_ptr<RoundHole> roundHolePtr = nullptr; //识别圆孔
    std::shared_ptr<MatchTemplate> matchTemplatePtr = nullptr; // 丝印模版匹配
    std::shared_ptr<ClassifyMachine> classifyMachinePtr = nullptr; // 传统分类器
};
#endif // OPENCVALGORITHM_H
