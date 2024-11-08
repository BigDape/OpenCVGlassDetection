#ifndef HSJSONCPPINTERFACE_H
#define HSJSONCPPINTERFACE_H

#include <QString>
#include <QDateTime>
#include "HSTool.h"

// struct DefectData{
//     int DefectID; //序号
//     QString Time; //时间
//     QString DefectType; //类型
//     QString DetectLeve; //等级
//     double X; //坐标X
//     double Y; //坐标Y
//     double Lenth; //长
//     double Width; //宽
//     double Area; //区域
// };

// struct SizeData{
//     int HolesID;// 序号
//     QString Time;// 时间
//     QString Type;// 类型
//     double HolesHeight;// 长X
//     double HolesWidth;// 宽Y
//     double DistanceHorizontal;// 边距X
//     double DistanceVertical;// 边距Y
//     QString HolesLeve;//等级
// };

// //单个孔/门夹/丝印
// struct HoleData {
//     QString HolesID;
//     QString Time;
//     QString Type;
//     QString HolesLeve;
//     double DistanceHorizontal;
//     double DistanceVertical;
//     double HolesWidth;
//     double HolesHeight;
//     QString ImageHolesPath;
// };
// //单块玻璃写入json文件中的数据
// struct HoleResult {
//     int GlassID;
//     std::vector<HoleData> holes;
//     double GlassLength;
//     double GlassWidth;
//     double GlassAngle;
//     QString ImageHolesLinePath;
//     QString jsonFullPath; //json文件地址
// };

// //单个缺陷
// struct DefeteData{
//     QString Time;
//     int DefectID;
//     QString DefectType;
//     QString DetectLeve;
//     double X;
//     double Y;
//     double Lenth;
//     double Width;
//     double Area;
//     QString ImageNGPath;
// };
// //单块玻璃写入json文件中的缺陷数据
// struct DefeteResult{
//     int GlassID;
//     std::vector<DefeteData> defetes;
//     double GlassWidth;
//     double GlassLength;
//     double GlassAngle;
//     QString jsonFullPath; //json文件地址
//     QDateTime currentTime;
// };

// //工单：光源控制器参数
// struct LightControllerParameters{
//     int signalChange;                       //信号切换
//     int lightField_1_LuminescenceTime;      //光场1发光时间
//     int lightField_1_DelayTime;             //光场1延时时间
//     int lightField_2_LuminescenceTime;      //光场2发光时间
//     int lightField_2_DelayTime;             //光场2延时时间
//     int lightField_3_LuminescenceTime;      //光场3发光时间
//     int lightField_3_DelayTime;             //光场3延时时间
//     int lightField_4_LuminescenceTime;      //光场4发光时间
//     int lightField_4_DelayTime;             //光场4延时时间
//     int lightField_5_LuminescenceTime;      //光场5发光时间
//     int lightField_5_DelayTime;             //光场5延时时间
//     int lightField_6_LuminescenceTime;      //光场6发光时间
//     int lightField_6_DelayTime;             //光场6延时时间
//     int lightField_7_LuminescenceTime;      //光场7发光时间
//     int lightField_7_DelayTime;             //光场7延时时间
//     int lightField_8_LuminescenceTime;      //光场8发光时间
//     int lightField_8_DelayTime;             //光场8延时时间
//     int lightField_9_LuminescenceTime;      //光场9发光时间
//     int lightField_9_DelayTime;             //光场9延时时间
//     int lightField_10_LuminescenceTime;      //光场10发光时间
//     int lightField_10_DelayTime;             //光场10延时时间
//     int lightField_11_LuminescenceTime;      //光场11发光时间
//     int lightField_11_DelayTime;             //光场11延时时间
//     int lightField_12_LuminescenceTime;      //光场12发光时间
//     int lightField_12_DelayTime;             //光场12延时时间
//     int horizontalDarkFieldSelectionReg;     //横向暗场选择寄存器
//     int CameraLightCtrl;                     //相机光场控制
//     int LightSignalSlection;                //行信号源选择
//     int LightField;                         //光场数量
// };
// //工单：尺寸测量
// struct DimensionalMeasurementParameters{
//     double YB;  //Y方向B
//     double YK;  //Y方向精度K
//     double width;   //宽度
//     double widthDeviation; //宽度误差
//     double diagonal1; //对角线1
//     double diagonal1Deviation; //对角线1误差
//     double diagonal2; //对角线1
//     double diagonal2Deviation; //对角线1误差
//     int enableMeasure;  //尺寸测量启用
//     double camera1PixAccury;    //相机1像素精度
//     double camera1K;            //相机1像素k值
//     double camera2CompareCamera1; //相机2与相机1精度比值
//     double camera2K;                //相机2像素K值
//     double length;                  //长度
//     double lengthDeviation;         //长度误差
// };
// //工单：控制器系统参数
// struct ControllerSystemParameters {
//     int PixAccury;                          //像素精度
//     int PhotoelectricSignalPulseFiltering;  //光电信号脉冲滤波
//     int PhotoelectricSignalCameraDistance;  //光电相机距离
//     int InnerLineFrequency;                 //内部行频
//     int FrameSignalDuration;                //帧信号持续时间
//     int PhotMode;                           //拍照模式
//     int PhotoEndDelayLine;                  //拍照结束延时行数
//     int EnableModuleOn;                     //模块使能信号
//     int CameraFrameSignalStartDelayLine;    //相机帧信号出发延时行数
//     int CameraPhotoLine;                    //相机拍照函数
//     int CameraStartPlusDuration;            //相机触发脉冲持续时间
// };
// //工单：相机参数
// struct CameraParameters{
//     int FrameCount;         //帧次
//     int PhotoLineCount;     //拍照行数
//     int ExposureTime;       //曝光时间
//     int CameraGain;         //相机增益
// };
// //工单：编码器参数
// struct CoderParameters{
//     int PressureWheelACount;  //压轮编码器A计数
//     int PressureWheelBCount;  //压轮编码器B计数
//     int PressureWheel4FrequencyCount; //压轮编码器四倍频计数
//     int PressureWheelK;             //压轮编码器系数
//     int ExceptOnePixAccury;         //期望单个像素精度
//     int EveryLineToCoderCount;      //每行对应的编码计数
//     int Coder4FrequencyCount;       //编码器4倍频计数
//     int CoderUnitScaleToDistance;   //编码器单位刻度对应距离
//     int CoderUnitTimePlusCount;     //编码器单位时间脉冲计数
//     int CoderTriggerLineCount;      //编码器触发行计数
//     int CoderCount;                 //编码器计数
//     int CoderCountTime;             //编码器计数时间
//     int CoderCountEndFlag;          //编码器计数结束标记
//     int CoderCircleCount;           //编码器装数
//     int CoderPulseFiltering;        //编码器脉冲滤波
//     int CoderChannel;               //编码通道
//     int RollerCircumference;        //辊道周长
//     int RollerMaxToLine;            //辊道最大速度对应行频
// };
// //工单：缺陷检测参数
// struct DefectDetectionCoderParameters{
//     int Camera12PixOffset;          //12相机像素偏差
//     int Camera23PixOffset;         //23相机像素偏差
//     int Camera24PixOffset;          //24相机像素偏差
//     int SiyinToRollerDistance;      //丝印离辊道距离
//     int GlassThickness;             //玻璃厚度
//     int EnableDefect;               //缺陷检测启用
// };
// //工单：缺陷面积阈值
// struct DefectAreaThresholdParameters{
//     int HuashanAreaThreahold;        //划痕面积阈值
//     int QijieAreaThreahold;         //气节面积阈值
//     int ZanwuAreaThreahold;         //脏污面积阈值
// };
// //工单：自定义参数
// struct CustomParameters{
//     int SaveOrigin;                 //保存原图
//     int SaveImage;                  //保存整图
//     int SaveDefectIamge;            //保存缺检图
//     int SaveCorpImage;              //保存裁剪图像
//     int EnableDimensionalMeasurement; //尺寸测量启用
//     int EnableDefect;               //缺陷检测启用
// };
// //工单
// struct WorkOrder{
//     LightControllerParameters LCParam;          //光电控制器参数
//     DimensionalMeasurementParameters DMParam;   //尺寸测量参数
//     ControllerSystemParameters CSParam;         //控制器系统参数
//     std::vector<CameraParameters> CVecParam;       //相机参数
//     CoderParameters CoderParam;                 //控制器参数
//     DefectDetectionCoderParameters DDCParam;    //缺陷检测参数
//     DefectAreaThresholdParameters DATParam;     //缺陷面积阈值参数
//     CustomParameters CTParam;                   //自定义参数
// };

namespace HSJsoncppNamespace {

    class HSJsoncppInterface
    {
    public:
        virtual ~HSJsoncppInterface(){}
        virtual void getFlawImageFromJson(QString jsonFileName,
                                  int GlassID,
                                  int defectid,
                                  QString& ImagePath1,
                                  QString& ImagePath2,
                                  QString& ImagePath3) = 0;

        virtual void getDefectSFromJson(QString jsonFullPath,
                                int glassid,
                                std::vector<DefectData>& Defects) = 0;

        virtual void readHoleFromJson(QString jsonFullPath, int glassid, QString& ImageHolesLinePath) = 0;

        virtual void readSizeSmallImage(QString jsonFileName, int GlassID, int row, QString& ImageHolesPath) = 0;

        virtual void readSizeFromJson(QString jsonFilePath,int glassid,std::vector<SizeData>& result) = 0;

        virtual void writeSizeToJson(HoleResult inputdata) = 0;

        virtual void writeDefectToJson(DefeteResult defect,int GlassID) = 0;

        //communication模块保存json
        virtual void writeComDataToJson(QString recipeFullpath, const SignalControl& data) = 0;

        //main创建空白json工单
        virtual void writeEmptyRecipeToJson(QString path) = 0;
        virtual void readRecipeFromJson(QString path, SignalControl& signalCtrl) = 0;
        virtual void writeRecipeToJson(QString fullpath, SignalControl signalCtrl) = 0;
        //更新json文件内容
        virtual void updateRecipeToJson(QString fullpath, SignalControl signalCtrl) = 0;
        //Cabrate创建空白json文件
        virtual void writeEmptyCalibrateToJson(QString path) = 0;
        virtual void readCalibrateFromJson(QString path, CropArgPackage& crop) = 0;
        virtual void writeCalibrateToJson(QString path, CropArgPackage crop) = 0;
    };
}

    // 用于创建对象的函数（DLL 导出函数）
    extern "C" __declspec(dllexport) HSJsoncppNamespace::HSJsoncppInterface* createJsoncppObject();


#endif // HSJSONCPPINTERFACE_H
