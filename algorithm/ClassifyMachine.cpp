#include "ClassifyMachine.h"
#include <opencv2/ximgproc.hpp>


#define GLCM_DIS 1  //灰度共生矩阵的统计距离
#define GLCM_CLASS 64 //计算灰度共生矩阵的图像灰度值等级化
#define GLCM_ANGLE_HORIZATION 0  //水平
#define GLCM_ANGLE_VERTICAL   1	 //垂直
#define GLCM_ANGLE_DIGONAL_45    2  //对角
#define GLCM_ANGLE_DIGONAL_135    3//对角

//[划痕，异物，气泡，麻点，水印，油墨不良，锯齿边，丝印，刮花，裂纹，崩边，崩角]
ClassifyMachine::ClassifyMachine()
{
}

void ClassifyMachine::GetCoOccUrrenceMatrix(const cv::Mat& image, int a, int b, std::vector<std::vector<double>> & cooccurrence_matrix)
{
    try {
        // only support gray image
        CV_Assert(image.channels() == 1);
        int Level = 52;//灰度值分成52个等级，如果耗时过长则
        int levelMoin = 5;
        cooccurrence_matrix.resize(Level);
        for (size_t i = 0; i < Level; ++i) {
            // 为每个内层向量（对应每行）初始化100个元素为0的double类型向量
            std::vector<double> colVector(Level, 0);
            cooccurrence_matrix[i] = colVector;
        }
        int sum = 0; //累计和
        for (auto i = 0; i < image.rows; i++) {
            for (auto j = 0; j < image.cols; j++) {
                if (i + b >= image.rows || j + a >= image.cols) {
                    continue;
                }
                int ij_valule = image.at<uchar>(i, j) / levelMoin;
                int offet_ab_value = image.at<uchar>(i + b, j + a)/levelMoin;
                cooccurrence_matrix[ij_valule][offet_ab_value] += 1;
                ++sum;
            }
        }
        for (auto i = 0; i < (int)cooccurrence_matrix.size(); i++) {
            for (auto j = 0; j < (int)cooccurrence_matrix.at(0).size(); j++) {
                cooccurrence_matrix[i][j] = cooccurrence_matrix[i][j] / sum;
            }
        }
    } catch (...) {
        std::exception_ptr eptr = std::current_exception();
        if (eptr) {
            try {
                std::rethrow_exception(eptr);
            } catch (const std::exception& ex) {
                qDebug() << "Exception GetCoOccUrrenceMatrix: " << ex.what();
            }
        }
    }
}

// 模拟图像多尺度分解（简单拉普拉斯金字塔分解示意）
std::vector<cv::Mat> ClassifyMachine::laplacianPyramid(cv::Mat inputImage, int numLevels)
{
    std::vector<cv::Mat> pyramid;
    cv::Mat currentImage = inputImage;
    for (int i = 0; i < numLevels; ++i)
    {
        cv::Mat downsampled;
        cv::pyrDown(currentImage, downsampled);
        cv::Mat upsampled;
        cv::pyrUp(downsampled, upsampled, currentImage.size());
        cv::Mat laplacian = currentImage - upsampled;
        pyramid.push_back(laplacian);
        currentImage = downsampled;
    }
    return pyramid;
}

// 简单模拟方向滤波（用Sobel算子获取水平和垂直方向特征）
void ClassifyMachine::directionalFiltering(cv::Mat& inputImage,
                                           cv::Mat& horizontalResult,
                                           cv::Mat& verticalResult)
{
    cv::Sobel(inputImage, horizontalResult, CV_16S, 1, 0);
    cv::Sobel(inputImage, verticalResult, CV_16S, 0, 1);
    cv::convertScaleAbs(horizontalResult, horizontalResult);
    cv::convertScaleAbs(verticalResult, verticalResult);
}

//  Contourlet 变换特征
void ClassifyMachine::ContourletFeature(cv::Mat image)
{
    // 进行多尺度分解
    int numLevels = 3;
    std::vector<cv::Mat> pyramid = laplacianPyramid(image, numLevels);

    // 对每个尺度的图像进行简单方向滤波（这里只是示意）
    for (size_t i = 0; i < pyramid.size(); ++i)
    {
        cv::Mat horizontal, vertical;
        directionalFiltering(pyramid[i], horizontal, vertical);
        // 这里可以进一步对水平和垂直方向滤波结果进行后续处理，比如显示等
        cv::Mat magnitude;
        magnitude.create(horizontal.size(), CV_32FC1);
        for (int y = 0; y < horizontal.rows; ++y)
        {
            for (int x = 0; x < horizontal.cols; ++x)
            {
                float hVal = horizontal.at<uchar>(y, x);
                float vVal = vertical.at<uchar>(y, x);
                float mag = std::sqrt(hVal * hVal + vVal * vVal);
                magnitude.at<float>(y, x) = mag;
            }
        }
        cv::Scalar meanValue = mean(magnitude);
        qDebug() << "Mean of the magnitude: " << meanValue[0] ;
    }
}

void ClassifyMachine::GetFeatures(int defectid, cv::Rect regionRect, cv::Mat region, cv::Mat& featureVector)
{
    try {
        // 计算图片的直观特征
        //1) 面积大小
        int Threshold = 30;
        double area = ClassifyMachine::RegionArea(region, Threshold);
        //2) 长宽比
        double ratio = ClassifyMachine::AspectRatio(regionRect);
        //3) 灰度均值
        double mean = ClassifyMachine::grayscaleMean(region);
        //4) X方向投影梯度变化
        double Xvalue = ClassifyMachine::secondDifferenceMeasure(region, true);
        //5) Y方向投影梯度变化
        double Yvalue = ClassifyMachine::secondDifferenceMeasure(region, false);
        //6) 圆度
        double roundness = ClassifyMachine::calculateRoundness(region);
        //7) 偏心率
        double E = ClassifyMachine::calculateEccentricity(region);
        //灰度共生矩阵
        std::vector<std::vector<double>>  cooccurrence_matrix;
        ClassifyMachine::GetCoOccUrrenceMatrix(region, 1, 1, cooccurrence_matrix);
        /************************计算特征值*********************/
        float u_i=0,u_j=0;
        for (auto i = 0;i < (int)cooccurrence_matrix.size();i++) {
            for (auto j = 0;j < (int)cooccurrence_matrix[0].size();j++) {
                u_i += i * cooccurrence_matrix[i][j];
                u_j += j * cooccurrence_matrix[i][j];
            }
        }
        float s_i_2=0,s_j_2=0;
        for (auto i = 0;i < (int)cooccurrence_matrix.size(); i++) {
            for (auto j = 0;j < (int)cooccurrence_matrix[0].size(); j++) {
                s_i_2 += (i-u_i) * (i-u_i) * cooccurrence_matrix[i][j];
                s_j_2 +=(j-u_j) * (j-u_j) * cooccurrence_matrix[i][j];
            }
        }
        float entropy = 0,energy = 0,contrast = 0,IDM = 0,correlation=0;
        for (auto i = 0; i < (int)cooccurrence_matrix.size(); i++) {
            for (auto j = 0;j < (int)cooccurrence_matrix[0].size(); j++) {
                //熵
                if(cooccurrence_matrix[i][j] > 0)
                    entropy -= cooccurrence_matrix[i][j] * log10(double(cooccurrence_matrix[i][j]));
                //能量
                energy += cooccurrence_matrix[i][j] * cooccurrence_matrix[i][j];
                //对比度
                contrast += (i - j) * (i - j) * cooccurrence_matrix[i][j];
                //一致性
                IDM += 1.0 / (1 + (i - j) * (i - j)) * cooccurrence_matrix[i][j];
                //自相关性
                correlation += ( i * j * cooccurrence_matrix[i][j] - u_i*u_j ) / ( sqrt(s_i_2) * sqrt(s_j_2) + 0.000001);
            }
        }

        // 归一化处理
        double maxEntropy = log2(52 * 52);
        entropy = entropy / maxEntropy;
        double contrast_max = 2 * (52 - 1) * (52 - 1);
        contrast = contrast / contrast_max;
        correlation = std::abs(correlation  / 100.0);
        correlation = correlation >1 ? 1 : correlation;

        featureVector.at<double>(0,0) = area;
        featureVector.at<double>(1,0) = ratio;
        featureVector.at<double>(2,0) = mean;
        featureVector.at<double>(3,0) = Xvalue;
        featureVector.at<double>(4,0) = Yvalue;
        featureVector.at<double>(5,0) = roundness;
        featureVector.at<double>(6,0) = E;
        featureVector.at<double>(7,0) = entropy;
        featureVector.at<double>(8,0) = energy;
        featureVector.at<double>(9,0) = contrast;
        featureVector.at<double>(10,0) = IDM;
        featureVector.at<double>(11,0) = correlation;

        // qDebug()<<"defectid ("<<defectid
        //      <<") 面积 ="<<area
        //      <<", 长宽比 ="<<ratio
        //      <<", 灰度均值 ="<<mean
        //      <<", X方向投影梯度变化="<<Xvalue
        //      <<", Y方向投影梯度变化="<<Yvalue
        //      <<", 圆度="<<roundness
        //      <<", 偏心率="<<E
        //      <<", 熵="<<entropy
        //      <<", 能量="<<energy
        //      <<", 对比度="<<contrast
        //      <<", 一致性="<<IDM
        //      <<", 自相关性="<<correlation;
    } catch(...) {
        std::exception_ptr eptr = std::current_exception();
        if (eptr) {
            try {
                std::rethrow_exception(eptr);
            } catch (const std::exception& ex) {
                qDebug() << "Exception GetFeatures: " << ex.what();
            }
        }
    }
}

// 计算图像目标区域的偏心率
double ClassifyMachine::calculateEccentricity(cv::Mat region)
{
    try {
        cv::Mat binaryImage;
        cv::threshold(region, binaryImage, 127, 255, cv::THRESH_BINARY);

        cv::Moments mu = moments(binaryImage, true);  // 计算矩，第二个参数设为true表示计算中心矩

        // 提取二阶中心矩
        double mu20 = mu.mu20;
        double mu02 = mu.mu02;
        double mu11 = mu.mu11;

        // 构建协方差矩阵（这里简单用两个变量表示特征值相关计算，实际更复杂的情况可能需要完整求特征值算法）
        double a = mu20 + mu02;
        double b = sqrt((mu20 - mu02) * (mu20 - mu02) + 4 * mu11 * mu11);

        // 计算最大和最小特征值（这里的推导基于协方差矩阵特征值计算理论简化而来）
        double lambda_max = (a + b) / 2;
        double lambda_min = (a - b) / 2;

        // 计算偏心率
        return sqrt(1 - lambda_min / lambda_max+0.0001);
    } catch(...) {
        std::exception_ptr eptr = std::current_exception();
        if (eptr) {
            try {
                std::rethrow_exception(eptr);
            } catch (const std::exception& ex) {
                qDebug() << "Exception calculateEccentricity: " << ex.what();
            }
        }
    }
    return 0.0;
}

// 计算轮廓的圆度
double ClassifyMachine::calculateRoundness(cv::Mat image)
{
    try{
        // 二值化图像，这里简单使用阈值127进行二值化，实际可根据情况调整阈值
        cv::Mat binaryImage;
        cv::threshold(image, binaryImage, 127, 255, cv::THRESH_BINARY);

        // 寻找轮廓
        std::vector<std::vector<cv::Point>> contours;
        cv::findContours(binaryImage, contours, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_NONE);

        // 假设只处理第一个轮廓（如果有多个轮廓，可根据需求遍历处理）
        if (!contours.empty()) {
            double area = cv::contourArea(contours[0]);
            double perimeter = arcLength(contours[0], true);
            if (perimeter == 0) {
                return 0;  // 避免除数为0的情况
            }
            double roundness = 4 * CV_PI * area / (perimeter * perimeter);
            return roundness;
        }
        else {
            return 0;
        }
    } catch(...) {
        std::exception_ptr eptr = std::current_exception();
        if (eptr) {
            try {
                std::rethrow_exception(eptr);
            } catch (const std::exception& ex) {
                qDebug() << "Exception calculateRoundness: " << ex.what();
            }
        }
    }
    return 0.0;
}

// 计算二阶差分的绝对值的平均值来衡量变化剧烈程度
double ClassifyMachine::secondDifferenceMeasure(cv::Mat region, bool isHorizontal)
{
    try{
        cv::Mat inputArray;
        if (isHorizontal) {
            // 计算水平投影（行投影）
            cv::reduce(region, inputArray, 1, cv::REDUCE_SUM, CV_32S);
        } else if (!isHorizontal) {
            // 计算列投影
            cv::reduce(region, inputArray, 0, cv::REDUCE_SUM, CV_32S);
        }

        if (inputArray.rows == 0 || inputArray.cols == 0) {
            return 0;  // 如果输入为空数组，返回0
        }
        // 检查是否为一维数组（单通道的行向量或者列向量形式）
        if (inputArray.channels()!= 1 || (inputArray.rows > 1 && inputArray.cols > 1)) {
            qDebug() << "输入的数组格式不符合要求，需为一维数组（单通道的行向量或列向量）";
            return -1;
        }
        int size = inputArray.rows * inputArray.cols;
        cv::Mat firstDiff;

        if (inputArray.rows == 1) {// 如果是行向量形式的一维数组
            for (int i = 0; i < inputArray.cols - 1; ++i) {
                int diff = std::abs(inputArray.at<int>(0, i+1) - inputArray.at<int>(0,i));
                firstDiff.push_back(diff);
            }
        } else {// 如果是列向量形式的一维数组
            for (int i = 0; i < inputArray.rows - 1; ++i) {
                int diff = std::abs(inputArray.at<int>(i+1, 0) - inputArray.at<int>(i,0));
                firstDiff.push_back(diff);
            }
        }

        double sumAbsDiff = 0;
        for (int i = 0; i < firstDiff.rows; ++i) {
            sumAbsDiff += firstDiff.at<int>(i,0);
        }
        double mean = sumAbsDiff / (firstDiff.rows * firstDiff.cols + 0.01);
        double res = mean /1000.0;
        return res >=1 ? 1 : res;
    } catch(...) {
        std::exception_ptr eptr = std::current_exception();
        if (eptr) {
            try {
                std::rethrow_exception(eptr);
            } catch (const std::exception& ex) {
                qDebug() << "Exception secondDifferenceMeasure: " << ex.what();
            }
        }
    }
    return 0.0;
}

double ClassifyMachine::grayscaleMean(cv::Mat region)
{
    try{
        if (!region.empty()) {
            cv::Scalar meanValue = cv::mean(region);
            double meanRes = meanValue.val[0]/255;
            return meanRes;
        } else {
            return 0.0;
        }
    } catch(...) {
        std::exception_ptr eptr = std::current_exception();
        if (eptr) {
            try {
                std::rethrow_exception(eptr);
            } catch (const std::exception& ex) {
                qDebug() << "Exception grayscaleMean: " << ex.what();
            }
        }
    }
    return 0.0;
}

double ClassifyMachine::AspectRatio(cv::Rect regionRect)
{
    try {
        if (regionRect.width > regionRect.height) {
            return ((double)regionRect.width - (double)regionRect.height)/((double)regionRect.width+0.0001);
        } else {
            return ((double)regionRect.height - (double)regionRect.width)/((double)regionRect.height+0.0001);
        }
    } catch(...) {
        std::exception_ptr eptr = std::current_exception();
        if (eptr) {
            try {
                std::rethrow_exception(eptr);
            } catch (const std::exception& ex) {
                qDebug() << "Exception AspectRatio: " << ex.what();
            }
        }
    }
    return 0.0;
}

double ClassifyMachine::RegionArea(cv::Mat region, int Threshold)
{
    try {
        cv::Mat dst;
        int retval = cv::threshold(region, dst, Threshold, 255, cv::THRESH_BINARY);
        double areaRatio = (double)retval/(double)(region.rows*region.cols + 1);
        areaRatio = areaRatio * 100;
        return areaRatio;
    } catch(...) {
        std::exception_ptr eptr = std::current_exception();
        if (eptr) {
            try {
                std::rethrow_exception(eptr);
            } catch (const std::exception& ex) {
                qDebug() << "Exception RegionArea: " << ex.what();
            }
        }
    }
    return 0.0;
}

int ClassifyMachine::IdentificationDefect(ClassifyParam param)
{
    try {
        std::vector<double> features;
        cv::Mat feature(12, 1, CV_64F);
        ClassifyMachine::GetFeatures(param.defectid, param.regionRect, param.region, feature);

        if (feature.at<double>(1)  > 0.4) {//划痕
            return 1;
        }
        //[面积,长宽比,灰度均值,X方向投影梯度变化,Y方向投影梯度变化,圆度,偏心率,熵,能量,对比度,一致性,自相关性]
        cv::Mat yiwuRow = (cv::Mat_<double>(1, 12) << 0.58334, 0.03334, 0.03334, 0.03334, 0.03334, 0.03334, 0.03334, 0.03334, 0.03334, 0.03334, 0.03334, 0.03334);
        cv::Mat HuahenRow = (cv::Mat_<double>(1, 12) << 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
        cv::Mat qipaoRow = (cv::Mat_<double>(1, 12) << 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
        cv::Mat madianRow = (cv::Mat_<double>(1, 12) << 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
        cv::Mat shuiyinRow = (cv::Mat_<double>(1, 12) << 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
        cv::Mat youmobuliangRow = (cv::Mat_<double>(1, 12) << 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
        cv::Mat juchibianRow = (cv::Mat_<double>(1, 12) << 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
        cv::Mat siyinRow = (cv::Mat_<double>(1, 12) << 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
        cv::Mat guahuaRow = (cv::Mat_<double>(1, 12) << 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
        cv::Mat liewenRow = (cv::Mat_<double>(1, 12) << 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
        cv::Mat benbianRow = (cv::Mat_<double>(1, 12) << 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
        cv::Mat benjiaoRow = (cv::Mat_<double>(1, 12) << 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
        cv::Mat HuahenResult = HuahenRow * feature;
        cv::Mat yiwuResult = yiwuRow * feature;
        cv::Mat qipaoResult = qipaoRow * feature;
        cv::Mat madianResult = madianRow * feature;
        cv::Mat shuiyinResult = shuiyinRow * feature;
        cv::Mat youmobuliangResult = youmobuliangRow * feature;
        cv::Mat juchibianResult = juchibianRow * feature;
        cv::Mat siyinResult = siyinRow * feature;
        cv::Mat guahuaResult = guahuaRow * feature;
        cv::Mat liewenResult = liewenRow * feature;
        cv::Mat benbianResult = benbianRow * feature;
        cv::Mat benjiaoResult = benjiaoRow * feature;

        features.push_back(yiwuResult.at<double>(0, 0));
        features.push_back(HuahenResult.at<double>(0, 0));
        features.push_back(qipaoResult.at<double>(0, 0));
        features.push_back(madianResult.at<double>(0, 0));
        features.push_back(shuiyinResult.at<double>(0, 0));
        features.push_back(youmobuliangResult.at<double>(0, 0));
        features.push_back(juchibianResult.at<double>(0, 0));
        features.push_back(siyinResult.at<double>(0, 0));
        features.push_back(guahuaResult.at<double>(0, 0));
        features.push_back(liewenResult.at<double>(0, 0));
        features.push_back(benbianResult.at<double>(0, 0));
        features.push_back(benjiaoResult.at<double>(0, 0));

        double maxValue = -1;
        int maxIndex = 0;
        for(int i=0; i< (int)features.size(); ++i) {
            if (maxValue < features[i]) {
                maxValue = features[i];
                maxIndex = i;
            }
        }

        return maxIndex;
    } catch(...) {
        std::exception_ptr eptr = std::current_exception();
        if (eptr) {
            try {
                std::rethrow_exception(eptr);
            } catch (const std::exception& ex) {
                qDebug() << "IdentificationDefect  Exception: " << ex.what();
            }
        }
    }
    return 0;
}



