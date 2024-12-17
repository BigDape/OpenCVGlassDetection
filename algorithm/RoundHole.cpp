#include "RoundHole.h"

RoundHole::RoundHole() {}

void RoundHole::HoughCircleRadius(cv::Mat image,
                                  std::vector<double>& diameters,
                                  std::vector<cv::Point>& centers)
{
    try {
        // 霍夫圆变换
        std::vector<cv::Vec3f> circles;
        cv::cuda::GpuMat gpuInputImage(image);
        cv::Ptr<cv::cuda::HoughCirclesDetector> dector = cv::cuda::createHoughCirclesDetector(1, image.rows/8, 100, 30, 80, 10000);
        dector->detect(gpuInputImage,circles);

        qDebug()<<"circles.size() ="<<circles.size();
        for (size_t i = 0; i < circles.size(); i++) {
            double diameter = 2 * circles[i][2];
            diameters.push_back(diameter);
            cv::Point center = cv::Point(cvRound(circles[i][0]), cvRound(circles[i][1]));
            centers.push_back(center);
            int radius = cvRound(circles[i][2]);
            qDebug() << "Circle " << i + 1 << " center: (" << center.x << ", " << center.y << "), radius: " << radius;
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


