#include "RoundHole.h"

RoundHole::RoundHole() {}

void RoundHole::HoughCircleRadius(cv::Mat glass1,
                                  cv::Mat glass2,
                                  cv::Mat glass3,
                                  std::vector<GlassSizeInfo2>& sizeRes)
{
    try {
        if (glass1.empty() || glass2.empty() || glass3.empty())
            return;
        cv::Mat holeBinaryImage;
        cv::Ptr<cv::cuda::CannyEdgeDetector> cannyDetector = cv::cuda::createCannyEdgeDetector(30, 80,1,true);
        cv::cuda::GpuMat gpuInputImage(glass1);
        cv::cuda::GpuMat gpuCannyEdges;
        cannyDetector->detect(gpuInputImage, gpuCannyEdges);
        gpuCannyEdges.download(holeBinaryImage);
        std::vector<std::vector<cv::Point> > contourss;
        cv::findContours(holeBinaryImage, contourss, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_NONE); //找轮廓 138ms
        std::vector<cv::Mat> separatedRegions;
        for (size_t i = 0; i < contourss.size(); i++) {
            cv::Rect rect = cv::boundingRect(contourss[i]);
            double ratio = (double)std::min<int>(rect.width , rect.height) / ((double)std::max<int>(rect.width , rect.height));
            if ( ratio < 0.15 || rect.height > glass1.rows * 0.5 || rect.height < 80 || rect.width > glass1.cols * 0.5 || rect.width < 80) {//过滤掉非孔
                continue;
            }
            if (rect.x < 256 || rect.x > (glass1.cols - 256) ) {//去除弧形边缘
                continue;
            }
            if (rect.y < 256 || rect.y > (glass1.rows - 256) ) {
                continue;
            }
            if (rect.x < 0) {
                rect.x = 0;
            }
            if (rect.x > glass1.cols) {
                rect.x = glass1.cols -1 ;
            }
            if (rect.y < 0) {
                rect.y = 0;
            }
            if (rect.y > glass1.rows) {
                rect.y = glass1.rows;
            }
            if (rect.width < 0) {
                rect.width = 0;
            }
            if (rect.width > glass1.cols) {
                rect.width = glass1.cols;
            }
            if (rect.height < 0) {
                rect.height = 0;
            }
            if (rect.height > glass1.rows) {
                rect.height = glass1.rows;
            }
            if (rect.x + rect.width > glass1.cols) {
                continue;
            }
            if (rect.y + rect.height > glass1.rows) {
                continue;
            }
            cv::Mat separatedRegion0 = glass1(rect);
            cv::Mat separatedRegion1 = glass2(rect);
            cv::Mat separatedRegion2 = glass3(rect);

            GlassSizeInfo2 hole;
            hole.time = QDateTime::currentDateTime().toString("MM-dd HH:mm:ss");
            hole.sizeType = ("孔洞");
            hole.sizeLevel = "OK";
            hole.Pixlength = separatedRegion0.rows;
            hole.PixWidth = separatedRegion0.cols;
            hole.PixMarginsX = rect.x + rect.width/2;
            hole.PixMarginsY = rect.y + rect.height/2;
            QString path0 = SyncSaveImage(separatedRegion0);
            QString path1 = SyncSaveImage(separatedRegion1);
            QString path2 = SyncSaveImage(separatedRegion2);
            hole.imagePath0 = path0;
            hole.imagePath1 = path1;
            hole.imagePath2 = path2;
            hole.Region0 = separatedRegion0;
            hole.Region1 = separatedRegion1;
            hole.Region2 = separatedRegion2;
            hole.rect = rect;           // 坐标信息
            sizeRes.push_back(hole);
        }
    } catch(...) {
        qDebug()<<"HoughCircleRadius unknown Exception.";
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

}


