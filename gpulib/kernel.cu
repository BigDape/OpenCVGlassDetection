#include "kernel.h"

// CUDA 核函数，处理图像分类
__global__ void processClassificationKernel(cv::cuda::GpuMat* gpuImages,
                                            int tcount,
                                            cv::dnn::Net* net,
                                            int* type,
                                            float* pixLength,
                                            float* pixWidth,
                                            float* pixX,
                                            float* pixY)
{
    int tid = threadIdx.x + blockIdx.x * blockDim.x;
    if (tid < tcount) {
        // cv::cuda::GpuMat image = gpuImages[tid];
        // cv::cuda::GpuMat threeChannelImage;
        // cv::cuda::cvtColor(image, threeChannelImage, cv::COLOR_BGRA2BGR);
//         if (threeChannelImage.empty()) {
//             return;
//         }

        // cv::cuda::GpuMat blob;
        // cv::dnn::blobFromImage(threeChannelImage, blob, 1.0 / 255.0, cv::Size(640, 640), cv::Scalar(), true, false);

//         // 准备输入
        // std::vector<cv::cuda::GpuMat> image1;
//         net->setInput(gpuImages[tid]);

// //         // 前向传播并获取输出
//         std::vector<cv::cuda::GpuMat> outputs;
//         net->forward(outputs, net->getUnconnectedOutLayersNames());

//         int rows = outputs[0].size[1];
//         int dimensions = outputs[0].size[2];
//         if (dimensions > rows) {
//             rows = outputs[0].size[2];
//             dimensions = outputs[0].size[1];
//             outputs[0] = outputs[0].reshape(1, dimensions);
//             cv::transpose(outputs[0], outputs[0]);
//         }

//         float* data = (float*)outputs[0].data;
        // std::vector<int> class_ids;
        // std::vector<float> confidences;
        // std::vector<cv::Rect> boxes;

        // std::vector<std::string> classes = { "JieShi_Min", "MaoXu_Min", "QiPao_Min", "ShuiDi_Min", "BoLiXue_Min", "HeiDian_Min", "HuaShang_Min" };
        // double modelScoreThreshold = 0.1;
        // double modelConfidenceThreshold = 0.1;

        // cv::Point class_id1;
        // double maxClassScore1;
        // cv::Mat res1 = outputs[0](cv::Rect(4, 0, 7, rows));//7==classes.size()
        // cv::cuda::minMaxLoc(res1, 0, &maxClassScore1, 0, &class_id1);
        // data += dimensions * class_id1.y;
        // type[tid] = class_id1.x;
        // pixX[tid] = data[0];
        // pixY[tid] = data[1];
        // pixWidth[tid] = data[2];
        // pixLength[tid] = data[3];
    }
}

void cudaProcessClassification(cv::Mat defectimage, cv::dnn::Net net)
{
//     NewDefectUnitData resdata;
//     cv::Mat* defectimage_dev;
//     cv::dnn::Net* net_dev;
//     NewDefectUnitData* resdata_dev;

//     // 将输入图像、网络和输出数据复制到 GPU 内存
//     cudaMalloc(&defectimage_dev, sizeof(cv::Mat));
//     cudaMemcpy(defectimage_dev, &defectimage, sizeof(cv::Mat), cudaMemcpyHostToDevice);
//     cudaMalloc(&net_dev, sizeof(cv::dnn::Net));
//     cudaMemcpy(net_dev, &net, sizeof(cv::dnn::Net), cudaMemcpyHostToDevice);
//     cudaMalloc(&resdata_dev, sizeof(NewDefectUnitData));

//     // 调用 CUDA 核函数
//     dim3 blockSize(1);
//     dim3 gridSize(1);
//     processClassificationKernel<<<gridSize, blockSize>>>(defectimage_dev, net_dev, resdata_dev);

//     // 将结果从 GPU 内存复制回主机内存
//     cudaMemcpy(&resdata, resdata_dev, sizeof(NewDefectUnitData), cudaMemcpyDeviceToHost);

//     // 释放 GPU 内存
//     cudaFree(defectimage_dev);
//     cudaFree(net_dev);
//     cudaFree(resdata_dev);
}
