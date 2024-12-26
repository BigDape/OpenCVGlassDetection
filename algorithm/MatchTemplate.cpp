#include "MatchTemplate.h"
#include <QDateTime>
#include <QString>
#include <opencv2/opencv.hpp>
#include <opencv2/cudaarithm.hpp>
#include <opencv2/cudaimgproc.hpp>

MatchTemplate::MatchTemplate(QObject *parent)
    :QObject(parent)
{
    QString path3 = QDir::currentPath() + QString("/../main/template/model3.jpg");
    cv::Mat model3 = cv::imread(path3.toStdString());
    templateImages.push_back(model3);
}

MatchTemplate::~MatchTemplate()
{
}

void MatchTemplate::setTemplate(std::vector<QString> modelPaths)
{
    for (int i = 0; i < (int)modelPaths.size(); ++i) {
        try {
            // 加载丝印匹配模版
            cv::Mat model1 = cv::imread(modelPaths[i].toStdString());
            templateImages.push_back(model1);
        } catch(...) {
            std::exception_ptr eptr = std::current_exception();
            if (eptr) {
                try {
                    std::rethrow_exception(eptr);
                } catch (const std::exception& ex) {
                    qDebug() << "Exception: "<<modelPaths[i]<<" is Not meeting the requirements. message:" << ex.what();
                }
            }
        }
    }
}

bool MatchTemplate::onMatchSilkscreen(cv::Mat image1,
                                      cv::Mat image2,
                                      cv::Mat targetImage,
                                      std::vector<GlassSizeInfo2>& sizeRes,
                                      double minimumSimilarity/* = 0.3*/)
{
    try {
        for (int i = 0; i < (int)templateImages.size(); ++i) {
            qDebug()<<"i = "<<i;
            cv::Mat result;
            int match_method = cv::TM_CCOEFF_NORMED;// cv::normalize(result,result,0,1,cv::NORM_MINMAX,-1,cv::Mat());
            cv::Mat templateImageGray;
            if (templateImages[i].rows >  targetImage.rows || templateImages[i].cols > targetImage.cols) {
                qDebug()<<"targetImage.rows ="<<targetImage.rows<<", "<<targetImage.cols<<",templateImages[i].rows="<<templateImages[i].rows<<","<<templateImages[i].cols;
                continue;
            }
            if (templateImages[i].channels() != 1) {
                cv::cvtColor(templateImages[i], templateImageGray, cv::COLOR_BGR2GRAY);
            } else {
                templateImageGray = templateImages[i];
            }
            if (targetImage.channels() != 1) {
                cv::cvtColor(targetImage, targetImage, cv::COLOR_BGR2GRAY);
            }
            //cv::Mat mask = MatchTemplate::GenerateMask(templateImageGray, 200);
            // //将图像数据传输到GPU
            cv::cuda::GpuMat gpu_src(targetImage);
            cv::cuda::GpuMat gpu_template(templateImageGray);
            // 创建基于GPU的模板匹配对象
            cv::Ptr<cv::cuda::TemplateMatching> matcher = cv::cuda::createTemplateMatching(cv::DataType<unsigned char>::type,match_method);
            // 在GPU上进行模板匹配
            cv::cuda::GpuMat gpu_result;

            matcher->match(gpu_src,gpu_template, gpu_result);
            // 将结果从GPU传输回CPU
            gpu_result.download(result);

            //cv::matchTemplate(targetImage, templateImageGray, result, match_method,mask);
            std::vector<cv::Point> locations;
            qDebug()<<"result ="<<result.rows<<","<<result.cols;
            MatchTemplate::nonMaxSuppression(match_method, result, minimumSimilarity,locations);
            MatchTemplate::inResult(locations,image1,image2,targetImage,templateImageGray,sizeRes);
        }
    } catch(...) {
        qDebug()<<"throw a unknow Exception.";
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
    return true;
}

cv::Mat MatchTemplate::GenerateMask(cv::Mat templateImage, int threshold/* = 128*/)
{
    cv::Mat mask;
    cv::threshold(templateImage, mask, threshold, 255, cv::THRESH_BINARY); // 使用cv::threshold函数生成掩膜
    return mask;
}

void MatchTemplate::nonMaxSuppression(int match_method,
                                      cv::Mat& result,
                                      double thresholdValue,
                                      std::vector<cv::Point>& locations,
                                      int radius/* = 10*/)
{
   // while (true) {
        double maxVal,minVal;
        cv::Point maxLoc,minLoc;
        cv::minMaxLoc(result, &minVal, &maxVal, &minLoc, &maxLoc);
        qDebug()<<"MatchTemplate::nonMaxSuppression maxVal ="<<maxVal;
        // 对于平方差匹配法，最小值位置是最佳匹配位置,对于其他匹配方法，最大值位置是最佳匹配位置
        if (match_method == cv::TM_SQDIFF || match_method == cv::TM_SQDIFF_NORMED) {
            if (minVal < thresholdValue) {
                locations.push_back(minLoc);
                // 将最大位置周围一定范围内的匹配度置零
                // for (int row = std::max(minLoc.y - radius, 0); row <= std::min(minLoc.y + radius, result.rows - 1); ++row) {
                //     for (int col = std::max(minLoc.x - radius, 0); col <= std::min(minLoc.x + radius, result.cols - 1); ++col) {
                //         result.at<float>(row, col) = 0;
                //     }
                // }
            } else {
                //break;
            }
        } else {
            if (maxVal > thresholdValue) {
                locations.push_back(maxLoc);
                // 将最大位置周围一定范围内的匹配度置零
                // for (int row = std::max(maxLoc.y - radius, 0); row <= std::min(maxLoc.y + radius, result.rows - 1); ++row) {
                //     for (int col = std::max(maxLoc.x - radius, 0); col <= std::min(maxLoc.x + radius, result.cols - 1); ++col) {
                //         result.at<float>(row, col) = 0;
                //     }
                // }
            } else {
                //break;
            }
        }
   // }
}

void MatchTemplate::inResult(std::vector<cv::Point> locations,
                             cv::Mat image1,
                             cv::Mat image2,
                             cv::Mat targetImage,
                             cv::Mat templateImageGray,
                             std::vector<GlassSizeInfo2>& sizeRes)
{
    for (int i = 0; i<(int)locations.size(); ++i) {
        int x = std::max(locations[i].x, 0);
        int y = std::max(locations[i].y, 0);
        int width = std::min(templateImageGray.cols, targetImage.cols - x - 1);
        int height = std::min(templateImageGray.rows, targetImage.rows - y - 1);
        cv::Rect rect(x, y, width, height);

        cv::Mat sImage0 = image1(rect);
        cv::Mat sImage1 = image2(rect);
        cv::Mat sImage2 = targetImage(rect);
        GlassSizeInfo2 siyin;
        siyin.time = QDateTime::currentDateTime().toString("MM-dd HH:mm:ss");
        siyin.sizeType = tr("丝印");
        siyin.sizeLevel = "OK";
        siyin.Pixlength = templateImageGray.rows;
        siyin.PixWidth = templateImageGray.cols;
        siyin.PixMarginsX = rect.x + rect.width/2;
        siyin.PixMarginsY = rect.y + rect.height/2;

        int randomNumber = std::rand() % 12356791;
        QString path0 = "D:/HVCache/cache/" +QString::number(randomNumber)+"_0.jpg";
        QString path1 = "D:/HVCache/cache/" +QString::number(randomNumber)+"_1.jpg";
        QString path2 = "D:/HVCache/cache/" +QString::number(randomNumber)+"_2.jpg";
        saveMatToImage(path0,sImage0);
        saveMatToImage(path1,sImage1);
        saveMatToImage(path2,sImage2);
        siyin.imagePath0 = path0;
        siyin.imagePath1 = path1;
        siyin.imagePath2 = path2;
        siyin.Region0 = sImage0;
        siyin.Region1 = sImage1;
        siyin.Region2 = sImage2;
        siyin.rect = rect;           // 坐标信息
        sizeRes.push_back(siyin);
        qDebug()<<"siyin.type ="<<siyin.sizeType
                 <<", siyin.Path0 ="<<siyin.imagePath0
                 <<", siyin.Path1 ="<<siyin.imagePath1
                 <<", siyin.Path2 ="<<siyin.imagePath2;
    }
}


