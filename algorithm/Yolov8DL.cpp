#include "Yolov8DL.h"

#define MODEL_NAME "/model/best.onnx"

Yolov8DL::Yolov8DL()
{
    // 加载模型
    QString Path = QDir::currentPath() + QString("/../main") + MODEL_NAME;
    qDebug()<<"onnx Path = "<<Path;
    net = cv::dnn::readNetFromONNX(Path.toStdString());
    net.setPreferableBackend(cv::dnn::DNN_BACKEND_CUDA);
    net.setPreferableTarget(cv::dnn::DNN_TARGET_CUDA);
    if (!net.empty()) {
        qDebug()<<"!net.empty()";
    } else {
        qDebug()<<"Load onnx model is fail.";
    }
}

void Yolov8DL::YoloDefectClassification(std::vector<regionInfor>& Regions, std::vector<GlassDefect2>& unitVec)
{
    auto start = std::chrono::high_resolution_clock::now();// 开始时间
    std::vector<std::thread> threads;
    //
    // 缺陷检测
    //
    qDebug()<<"Regions.size()"<<Regions.size();
    std::vector<std::promise<GlassDefect2>> promiseObjs(Regions.size());
    for (int i = 0 ; i < (int)Regions.size(); ++i) {
        std::promise<GlassDefect2> promiseObj;
        threads.push_back(std::thread(&Yolov8DL::threadProcessClassification, this, Regions[i], std::ref(promiseObjs[i])));
    }
    for (int i=0; i< (int)threads.size();++i) {
        if (threads[i].joinable()) {
            GlassDefect2 it = promiseObjs[i].get_future().get();
            threads[i].join();
            unitVec.push_back(it);
        }
    }
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> duration = end - start;
    qDebug() << "time：" << duration.count() << " ms";
}

void Yolov8DL::threadProcessClassification(regionInfor defectimage, std::promise<GlassDefect2>& promiseObj)
{
    cv::Mat threeChannelImage;
    cv::cvtColor(defectimage.region, threeChannelImage, cv::COLOR_BGRA2BGR);
    /*1ms*/

    cv::Mat blob;
    cv::dnn::blobFromImage(threeChannelImage, blob, 1.0 / 255.0, cv::Size(640, 640), cv::Scalar(), false, false);

    // 准备输入
    std::vector<cv::Mat> outputs;
    mut.lock();
    net.setInput(blob);//1,3/640/640
    net.forward(outputs, net.getUnconnectedOutLayersNames());// 前向传播并获取输出
    mut.unlock();
    /*1069ms*/

    int rows = outputs[0].size[1];
    int dimensions = outputs[0].size[2];
    rows = outputs[0].size[2];
    dimensions = outputs[0].size[1];
    outputs[0] = outputs[0].reshape(1, dimensions);
    cv::transpose(outputs[0], outputs[0]);// 矩阵装置

    /*1120ms*/
    float* data = (float*)outputs[0].data;
    cv::Point class_id1;
    double maxClassScore1;
    cv::Mat res1 = outputs[0](cv::Rect(4,0,7,rows));//std::vector<std::string> classes={ "JieShi_Min", "MaoXu_Min", "QiPao_Min", "ShuiDi_Min", "BoLiXue_Min", "HeiDian_Min", "HuaShang_Min"};
    cv::minMaxLoc(res1, 0, &maxClassScore1, 0, &class_id1);


    data += dimensions*class_id1.y;
    float x = data[0];
    float y = data[1];
    float w = data[2];
    float h = data[3];
    GlassDefect2 result;
    result.id = 0;
    result.time = QDateTime::currentDateTime().toString("MM-dd HH:mm:ss");
    result.typeID = class_id1.x;
    result.pixLength = h;
    result.pixWidth = w;
    result.pixX = x;
    result.pixY = y;
    result.pixArea = h*w;
    result.imagePath0 = defectimage.path;
    promiseObj.set_value(result);//设置结果
}
