#ifndef HSTOOL_H
#define HSTOOL_H

#include <QObject>
#include <QDateTime>
#include <mutex>
#include <vector>
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>

//系统执行的状态
enum SYSTEMSTATUS{
    INIT = 0,       // 初始化状态
    SYANDBY,    // 待机状态
    OFFLINE,    // 离线状态
    STOP,       // 停止状态
    RUNNING,    // 运行状态
    ABNORMAL,   // 异常状态
    EXIT,     // 退出状态
    RESERVE,    // 保留状态
};

struct SignalControl {
   /**
   * @brief temp0编码器单位刻度对应距离(um)
   */
  unsigned int temp0;
  /**
   * @brief temp1编码脉冲滤波(us)
   */
  unsigned int temp1;
  /**
   * @brief temp2编码器计数结束标志
   */
  unsigned int temp2;
  /**
   * @brief temp3编码器计数
   */
  unsigned int temp3;
  /**
   * @brief temp4编码器触发行计数
   */
  unsigned int temp4;
  /**
   * @brief temp5编码器4倍频计数
   */
  unsigned int temp5;
  /**
   * @brief temp6编码器单位时间脉冲计数
   */
  unsigned int temp6;
  /**
   * @brief temp7编码器计数时间(0.5s)
   */
  unsigned int temp7;
  /**
   * @brief temp8编码通道
   */
  unsigned int temp8;
  /**
   * @brief temp9编码器转数
   */
  unsigned int temp9;
  /**
   * @brief temp10辊道周长(um)
   */
  unsigned int temp10;
  /**
   * @brief temp11期望单个像素精度(um)
   */
  unsigned int temp11;
  /**
   * @brief temp12辊道最大速度对应行频
   */
  unsigned int temp12;
  /**
   * @brief temp13每行对应的编码计数
   */
  unsigned int temp13;
  /**
   * @brief temp14像素精度(um)
   */
  unsigned int temp14;
  /**
   * @brief temp15光电信号脉冲滤波(us)
   */
  unsigned int temp15;
  /**
   * @brief temp16相机触发脉冲持续时间(10ns)
   */
  unsigned int temp16;
  /**
   * @brief temp17光电相机距离(行)
   */
  unsigned int temp17;
  /**
   * @brief temp18相机帧信号触发延时行数(行)
   */
  unsigned int temp18;
  /**
   * @brief temp19帧信号持续时间(10ns)
   */
  unsigned int temp19;
  /**
   * @brief temp20模块使能信号
   */
  unsigned int temp20;
  /**
   * @brief temp21相机拍照行数(行)
   */
  unsigned int temp21;
  /**
   * @brief temp22内部行频
   */
  unsigned int temp22;
  /**
   * @brief temp23光场1延时时间(10ns)
   */
  unsigned int temp23;
  /**
   * @brief temp24光场1发光时间(10ns)
   */
  unsigned int temp24;
  /**
   * @brief temp25光场2延时时间(10ns)
   */
  unsigned int temp25;
  /**
   * @brief temp26光场2发光时间(10ns)
   */
  unsigned int temp26;
  /**
   * @brief temp27光场3延时时间(10ns)
   */
  unsigned int temp27;
  /**
   * @brief temp28光场3发光时间(10ns)
   */
  unsigned int temp28;
  /**
   * @brief temp29光场4延时时间(10ns)
   */
  unsigned int temp29;
  /**
   * @brief temp30光场4发光时间(10ns)
   */
  unsigned int temp30;
  /**
   * @brief temp31光场5延时时间(10ns)
   */
  unsigned int temp31;
  /**
   * @brief temp32光场5发光时间(10ns)
   */
  unsigned int temp32;
  /**
   * @brief temp33光场6延时时间(10ns)
   */
  unsigned int temp33;
  /**
   * @brief temp34 光场6发光时间(10ns)
   */
  unsigned int temp34;
  /**
   * @brief temp35 35相机与光场控制
   */
  unsigned int temp35;
  /**
   * @brief temp36信号切换
   */
  unsigned int temp36;
  /**
   * @brief temp37行信号源选择
   */
  unsigned int temp37;
  unsigned int temp38;

  /**
   * @brief temp43光场7延时时间(10ns)
   */
  unsigned int temp43;
  /**
   * @brief temp44 光场7发光时间(10ns)
   */
  unsigned int temp44;
  /**
   * @brief temp45 光场8延时时间(10ns)
   */
  unsigned int temp45;
  /**
   * @brief temp46 光场8发光时间(10ns)
   */
  unsigned int temp46;
  /**
   * @brief temp47 光场9延时时间(10ns)
   */
  unsigned int temp47;
  /**
   * @brief temp48 光场9发光时间(10ns)
   */
  unsigned int temp48;
  /**
   * @brief temp49 光场10延时时间(10ns)
   */
  unsigned int temp49;
  /**
   * @brief temp50 光场10发光时间(10ns)
   */
  unsigned int temp50;
  /**
   * @brief temp51 光场11延时时间(10ns)
   */
  unsigned int temp51;
  /**
   * @brief temp52 光场11发光时间(10ns)
   */
  unsigned int temp52;
  /**
   * @brief temp53 光场12延时时间(10ns)
   */
  unsigned int temp53;
  /**
   * @brief temp54 光场12发光时间(10ns)
   */
  unsigned int temp54;
  /**
   * @brief temp55 选择光场的数量
   */
  unsigned int temp55;
  /**
   * @brief temp56 横向暗场选择寄存器
   */
  unsigned int temp56;
  /**
   * @brief tempRollerACount 压轮编码器A计数
   */
  unsigned int tempRollerACount;
  /**
   * @brief tempRollerBCount 压轮编码器B计数
   */
  unsigned int tempRollerBCount;
  /**
   * @brief tempRollerCofficient 压轮编码器系数
   */
  double tempRollerCofficient;
  /**
   * @brief tempAutoPhoto 拍照模式
   */
  unsigned int tempAutoPhoto;
  /**
   * @brief tempPhotoEndDelayLine 拍照结束延时行数
   */
  unsigned int tempPhotoEndDelayLine;
  /**
   * @brief tempRoller4ABCount 压轮编码器4倍频计数
   */
  unsigned int tempRoller4ABCount;
  /**
   * @brief systemName 系统名称
   */
  QString systemName;
  /**
   * @brief CamareNumber 相机数量
   */
  int CamareNumber;
  /**
   * @brief Camare0Name 相机0名称
   */
  QString Camare0Name;
  /**
   * @brief Camare1Name 相机1名称
   */
  QString Camare1Name;
  /**
   * @brief Camare2Name 相机2名称
   */
  QString Camare2Name;
  /**
   * @brief Camare3Name 相机3名称
   */
  QString Camare3Name;
  /**
   * @brief ServerIP 服务器IP
   */
  QString ServerIP;
  /**
   * @brief ServerPort 服务端口
   */
  int ServerPort;
  /**
   * @brief SaveOriginImage 保存原图
   */
  int SaveOriginImage;
  /**
   * @brief SaveEntireImage 保存整图
   */
  int SaveEntireImage;
  /**
   * @brief SaveFlawImage 保存缺检图
   */
  int SaveFlawImage;
  /**
   * @brief SaveCropImage 保存裁剪图
   */
  int SaveCropImage;
  /**
   * @brief XYLengthEnable 尺寸测量
   */
  int XYLengthEnable;
  /**
   * @brief FlawDefectEnable 缺陷检测
   */
  int FlawDefectEnable;
  /**
   * @brief Camera12PixelDeviation 12相机像素偏差
   */
  int Camera12PixelDeviation;
  /**
   * @brief Camera23PixelDeviation 23相机像素偏差
   */
  int Camera23PixelDeviation;
  /**
   * @brief Camera24PixelDeviation 24相机像素偏差
   */
  int Camera24PixelDeviation;
  /**
   * @brief SilkToRollerDist 丝印离辊道距离
   */
  int SilkToRollerDist;
  /**
   * @brief ScratchAreaThreshold 划痕面积阈值
   */
  int ScratchAreaThreshold;
  /**
   * @brief BubbleStoneAreaThreshold 气节面积阈值
   */
  int BubbleStoneAreaThreshold;
  /**
   * @brief DirtyAreaThreshold 脏污面积阈值
   */
  int DirtyAreaThreshold;
  /**
   * @brief YAccuracy Y方向像素精度
   */
  double YAccuracy;
  /**
   * @brief XCamera0Accuracy X方向相机0像素精度
   */
  double XCamera0Accuracy;
  /**
   * @brief XCamera1Accuracy X方向相机1像素精度
   */
  double XCamera1Accuracy;
  /**
   * @brief Camera0Frame 相机0帧次
   */
  int Camera0Frame;
  /**
   * @brief Camera0PhotoRow 相机0拍照行数
   */
  int Camera0PhotoRow;
  /**
   * @brief Camera0ExposureTime 相机0曝光时间
   */
  int Camera0ExposureTime;
  /**
   * @brief Camera0Gain 相机0增益
   */
  int Camera0Gain;
  /**
   * @brief Camera1Frame 相机1帧次
   */
  int Camera1Frame;
  /**
   * @brief Camera1PhotoRow 相机1拍照行数
   */
  int Camera1PhotoRow;
  /**
   * @brief Camera1ExposureTime 相机1曝光时间
   */
  int Camera1ExposureTime;
  /**
   * @brief Camera1Gain 相机1增益
   */
  int Camera1Gain;
  /**
   * @brief Camera2Frame 相机2帧次
   */
  int Camera2Frame;
  /**
   * @brief Camera2PhotoRow 相机2拍照行数
   */
  int Camera2PhotoRow;
  /**
   * @brief Camera2ExposureTime 相机2曝光时间
   */
  int Camera2ExposureTime;
  /**
   * @brief Camera2Gain 相机2增益
   */
  int Camera2Gain;
  /**
   * @brief Camera3Frame 相机3帧次
   */
  int Camera3Frame;
  /**
   * @brief Camera3PhotoRow 相机3拍照行数
   */
  int Camera3PhotoRow;
  /**
   * @brief Camera3ExposureTime 相机3曝光时间
   */
  int Camera3ExposureTime;
  /**
   * @brief Camera3Gain 相机3增益
   */
  int Camera3Gain;

  SignalControl():
    temp0(0),
    temp1(0),
    temp2(0),
    temp3(0),
    temp4(0),
    temp5(0),
    temp6(0),
    temp7(0),
    temp8(0),
    temp9(0),
    temp10(0),
    temp11(0),
    temp12(0),
    temp13(0),
    temp14(0),
    temp15(0),
    temp16(0),
    temp17(0),
    temp18(0),
    temp19(0),
    temp20(0),
    temp21(0),
    temp22(0),
    temp23(0),
    temp24(0),
    temp25(0),
    temp26(0),
    temp27(0),
    temp28(0),
    temp29(0),
    temp30(0),
    temp31(0),
    temp32(0),
    temp33(0),
    temp34(0),
    temp35(0),
    temp36(0),
    temp37(0),
    temp38(0),
    temp43(0),
    temp44(0),
    temp45(0),
    temp46(0),
    temp47(0),
    temp48(0),
    temp49(0),
    temp50(0),
    temp51(0),
    temp52(0),
    temp53(0),
    temp54(0),
    temp55(0),
    temp56(0),
    tempRollerACount(0),
    tempRollerBCount(0),
    tempRollerCofficient(0),
    tempAutoPhoto(0),
    tempPhotoEndDelayLine(0),
    tempRoller4ABCount(0),
    systemName(""),
    CamareNumber(0),
    Camare0Name(""),
    Camare1Name(""),
    Camare2Name(""),
    Camare3Name(""),
    ServerIP(""),
    ServerPort(0),
    SaveOriginImage(0),
    SaveEntireImage(0),
    SaveFlawImage(0),
    SaveCropImage(0),
    XYLengthEnable(0),
    FlawDefectEnable(0),
    Camera12PixelDeviation(0),
    Camera23PixelDeviation(0),
    Camera24PixelDeviation(0),
    SilkToRollerDist(0),
    ScratchAreaThreshold(0),
    BubbleStoneAreaThreshold(0),
    DirtyAreaThreshold(0),
    YAccuracy(0.0),
    XCamera0Accuracy(0.0),
    XCamera1Accuracy(0.0),
    Camera0Frame(0),
    Camera0PhotoRow(0),
    Camera0ExposureTime(0),
    Camera0Gain(0),
    Camera1Frame(0),
    Camera1PhotoRow(0),
    Camera1ExposureTime(0),
    Camera1Gain(0),
    Camera2Frame(0),
    Camera2PhotoRow(0),
    Camera2ExposureTime(0),
    Camera2Gain(0),
    Camera3Frame(0),
    Camera3PhotoRow(0),
    Camera3ExposureTime(0),
    Camera3Gain(0){}
};

//数据统计信息
struct GlassDataBaseInfo2{
    int id;              // 玻璃的id，唯一的主键
    QString time;           // 时间
    QString OKorNG;         // 整体情况OK或者NG
    QString sizeOKorNG;     // 尺寸OK或者NG
    double length;          // 玻璃的长度
    double width;           // 玻璃的宽度
    double duijiaoxian1;    // 玻璃的对角线1
    double duijiaoxian2;    // 玻璃的对角线2
    int defectNumber;       // 玻璃的缺陷数量
    QString defectOKorNG;   // 缺陷OK或者NG
    int huashanNumber;      // 划伤数量
    int qipaoNumber;        // 气泡数量
    int jieshiNumber;       // 结石数量
    int benbianNumber;      // 崩边数量
    int zanwuNumber;        // 脏污数量
    int liewenNumber;       // 裂纹数量
    int qitaNumber;         // 其它数量
    GlassDataBaseInfo2(){
        id =0;
        time = "0";
        OKorNG = "OK";
        sizeOKorNG = "OK";
        length =0;
        width =0;
        duijiaoxian1 = 0;
        duijiaoxian2 =0;
        defectNumber = 0;
        defectOKorNG = "OK";
        huashanNumber = 0;
        qipaoNumber = 0;
        jieshiNumber = 0;
        benbianNumber = 0;
        zanwuNumber = 0;
        liewenNumber = 0;
        qitaNumber = 0;
    }
};
// 孔洞、门夹、丝印信息
struct GlassSizeInfo2{
    size_t id;              // 主键id,玻璃尺寸信息的顺序id
    int sizeno;             // 孔、门夹、丝印排列顺序
    QString time;           // 时间
    QString sizeType;       // 类型
    QString sizeLevel;      // 等级
    double lengthX;         // 长X(mm)
    double widthY;          // 宽Y(mm)
    double marginsX;        // 边距X(mm)
    double marginsY;        // 边距Y(mm)
    size_t glassid;         // 外键id,玻璃的id
    QString imagePath;      // 缺陷图片的路径
};
//单个缺陷信息
struct GlassDefect2{
    size_t id;              // 主键id,在所有缺陷中的顺序
    int defectId;           // 缺陷id，在一块玻璃中缺陷的顺序
    QString time;           // 缺陷检测时间
    QString defectType;     // 缺陷类型
    QString defectLevel;    // 缺陷等级，OK NG
    double x;               // 缺陷在玻璃上的X坐标
    double y;               // 缺陷在玻璃上的Y坐标
    double length;          // 缺陷的长度
    double width;           // 缺陷的宽度
    double area;            // 缺陷面积大小
    size_t glassid;         // 外键id,玻璃的id
    QString imagePath;      // 缺陷图片的路径
};

struct GlassSummary{
    int id; // 主键id，标注不同的天数
    QString time;   // 刷新表格时的时间
    int glasstotalcount; //玻璃总数
    QString currentglassstatus; //玻璃当前状态
    int OKcount; //OK总数
    int NGcount; //NG总数
    double passrate; //合格率
    int exceptioncount; //异常数目
    QString messagePath; //日志文件所在的路径
    int lastglassID;  //最后一块玻璃的ID,ID对应的是数据统计里面的ID
    GlassSummary(){
        id = 0;
        time = "";
        glasstotalcount = 0;
        currentglassstatus = "OK";
        OKcount = 0;
        NGcount = 0;
        passrate = 0.0; //合格率
        exceptioncount = 0; //异常数目
        messagePath = ""; //日志文件所在的路径
        lastglassID = 0;  //最后一块玻璃的ID,ID对应的是数据统计里面的ID
    }
};

//单个缺陷信息
struct GlassDefect{
    size_t id;              // 主键id,在所有缺陷中的顺序
    int defectId;           // 缺陷id，在一块玻璃中缺陷的顺序
    QString time;           // 缺陷检测时间
    QString defectType;     // 缺陷类型
    QString defectLevel;    // 缺陷等级，OK NG
    double x;               // 缺陷在玻璃上的X坐标
    double y;               // 缺陷在玻璃上的Y坐标
    double length;          // 缺陷的长度
    double width;           // 缺陷的宽度
    double area;            // 缺陷面积大小
    size_t glassid;         // 外键id,玻璃的id
    QString imagePath1;      // 光场1缺陷图片的路径
    QString imagePath2;      // 光场2缺陷图片的路径
    QString imagePath3;      // 光场3缺陷图片的路径
};

// 孔洞、门夹、丝印信息
struct GlassSize{
    size_t id;              // 主键id,玻璃尺寸信息的顺序id
    int sizeID;             // 孔、门夹、丝印排列顺序
    QString time;           // 时间
    QString sizeType;       // 类型
    QString sizeLevel;      // 等级
    double lengthX;         // 长X(mm)
    double widthY;          // 宽Y(mm)
    double marginsX;        // 边距X(mm)
    double marginsY;        // 边距Y(mm)
    size_t glassid;         // 外键id,玻璃的id
    QString imagePath;      // 缺陷图片的路径
};

//数据统计信息
struct GlassDataBaseInfo{
    int id;              // 玻璃的id，唯一的主键
    QString time;           // 时间
    QString OKorNG;         // 整体情况OK或者NG
    QString sizeOKorNG;     // 尺寸OK或者NG
    double length;          // 玻璃的长度
    double width;           // 玻璃的宽度
    double duijiaoxian1;    // 玻璃的对角线1
    double duijiaoxian2;    // 玻璃的对角线2
    int defectNumber;       // 玻璃的缺陷数量
    QString defectOKorNG;   // 缺陷OK或者NG
    int huashanNumber;      // 划伤数量
    int qipaoNumber;        // 气泡数量
    int jieshiNumber;       // 结石数量
    int benbianNumber;      // 崩边数量
    int zanwuNumber;        // 脏污数量
    int liewenNumber;       // 裂纹数量
    int qitaNumber;         // 其它数量
    GlassDataBaseInfo(){
        id =0;
        time = "0";
        OKorNG = "OK";
        sizeOKorNG = "OK";
        length =0;
        width =0;
        duijiaoxian1 = 0;
        duijiaoxian2 =0;
        defectNumber = 0;
        defectOKorNG = "OK";
        huashanNumber = 0;
        qipaoNumber = 0;
        jieshiNumber = 0;
        benbianNumber = 0;
        zanwuNumber = 0;
        liewenNumber = 0;
        qitaNumber = 0;
    }
    ~GlassDataBaseInfo(){}
};
// 缺陷统计表格统计结果
struct GlassDefectInfo{
    std::vector<GlassDefect> defectdatas; //多行数据
    int defectCount;//缺陷数目
};
// 尺寸统计表格统计结果
struct GlassSizeInfo{
    std::vector<GlassSize> sizedatas; // 多行尺寸数据
    int sizeCount; //尺寸数据数目
    QString OutLinePath;    // 轮廓图片的路径
};

//数据总的统计结果
struct SummaryResult {
    int GlassNum;       //玻璃总数
    int ngNum;          //NG数目
    int okNum;          //OK数目
    double suceessRate; //合格率
    int sorted;         //已分拣
    int unsorted;       //待分检
    int exceptNum;      //异常数
    bool currentOKorNG; //当前玻璃OK或者NG
    bool currentSort;   //当前玻璃是否分拣
    SummaryResult():GlassNum(0),
        ngNum(0),
        okNum(0),
        suceessRate(0.0),
        sorted(0),
        unsorted(0),
        exceptNum(0),
        currentOKorNG(false),
        currentSort(false){}
};

struct DefectData{
    int DefectID; //序号
    QString Time; //时间
    QString DefectType; //类型
    QString DetectLeve; //等级
    double X; //坐标X
    double Y; //坐标Y
    double Lenth; //长
    double Width; //宽
    double Area; //区域
};

struct SizeData{
    int HolesID;// 序号
    QString Time;// 时间
    QString Type;// 类型
    double HolesHeight;// 长X
    double HolesWidth;// 宽Y
    double DistanceHorizontal;// 边距X
    double DistanceVertical;// 边距Y
    QString HolesLeve;//等级
};

//单个孔/门夹/丝印
struct HoleData {
    QString HolesID;
    QString Time;
    QString Type;
    QString HolesLeve;
    double DistanceHorizontal;
    double DistanceVertical;
    double HolesWidth;
    double HolesHeight;
    QString ImageHolesPath;
};
//单块玻璃写入json文件中的数据
struct HoleResult {
    int GlassID;
    std::vector<HoleData> holes;
    double GlassLength;
    double GlassWidth;
    double GlassAngle;
    QString ImageHolesLinePath;
    QString jsonFullPath; //json文件地址
};

//单个缺陷
struct DefeteData{
    QString Time;
    int DefectID;
    QString DefectType;
    QString DetectLeve;
    double X;
    double Y;
    double Lenth;
    double Width;
    double Area;
    QString ImageNGPath;
};
//单块玻璃写入json文件中的缺陷数据
struct DefeteResult{
    int GlassID;
    std::vector<DefeteData> defetes;
    double GlassWidth;
    double GlassLength;
    double GlassAngle;
    QString jsonFullPath; //json文件地址
    QDateTime currentTime;
};

//工单：光源控制器参数
struct LightControllerParameters{
    int signalChange;                       //信号切换
    int lightField_1_LuminescenceTime;      //光场1发光时间
    int lightField_1_DelayTime;             //光场1延时时间
    int lightField_2_LuminescenceTime;      //光场2发光时间
    int lightField_2_DelayTime;             //光场2延时时间
    int lightField_3_LuminescenceTime;      //光场3发光时间
    int lightField_3_DelayTime;             //光场3延时时间
    int lightField_4_LuminescenceTime;      //光场4发光时间
    int lightField_4_DelayTime;             //光场4延时时间
    int lightField_5_LuminescenceTime;      //光场5发光时间
    int lightField_5_DelayTime;             //光场5延时时间
    int lightField_6_LuminescenceTime;      //光场6发光时间
    int lightField_6_DelayTime;             //光场6延时时间
    int lightField_7_LuminescenceTime;      //光场7发光时间
    int lightField_7_DelayTime;             //光场7延时时间
    int lightField_8_LuminescenceTime;      //光场8发光时间
    int lightField_8_DelayTime;             //光场8延时时间
    int lightField_9_LuminescenceTime;      //光场9发光时间
    int lightField_9_DelayTime;             //光场9延时时间
    int lightField_10_LuminescenceTime;      //光场10发光时间
    int lightField_10_DelayTime;             //光场10延时时间
    int lightField_11_LuminescenceTime;      //光场11发光时间
    int lightField_11_DelayTime;             //光场11延时时间
    int lightField_12_LuminescenceTime;      //光场12发光时间
    int lightField_12_DelayTime;             //光场12延时时间
    int horizontalDarkFieldSelectionReg;     //横向暗场选择寄存器
    int CameraLightCtrl;                     //相机光场控制
    int LightSignalSlection;                //行信号源选择
    int LightField;                         //光场数量
};
//工单：尺寸测量
struct DimensionalMeasurementParameters{
    double YB;  //Y方向B
    double YK;  //Y方向精度K
    double width;   //宽度
    double widthDeviation; //宽度误差
    double diagonal1; //对角线1
    double diagonal1Deviation; //对角线1误差
    double diagonal2; //对角线1
    double diagonal2Deviation; //对角线1误差
    int enableMeasure;  //尺寸测量启用
    double camera1PixAccury;    //相机1像素精度
    double camera1K;            //相机1像素k值
    double camera2CompareCamera1; //相机2与相机1精度比值
    double camera2K;                //相机2像素K值
    double length;                  //长度
    double lengthDeviation;         //长度误差
};
//工单：控制器系统参数
struct ControllerSystemParameters {
    int PixAccury;                          //像素精度
    int PhotoelectricSignalPulseFiltering;  //光电信号脉冲滤波
    int PhotoelectricSignalCameraDistance;  //光电相机距离
    int InnerLineFrequency;                 //内部行频
    int FrameSignalDuration;                //帧信号持续时间
    int PhotMode;                           //拍照模式
    int PhotoEndDelayLine;                  //拍照结束延时行数
    int EnableModuleOn;                     //模块使能信号
    int CameraFrameSignalStartDelayLine;    //相机帧信号出发延时行数
    int CameraPhotoLine;                    //相机拍照函数
    int CameraStartPlusDuration;            //相机触发脉冲持续时间
};
//工单：相机参数
struct CameraParameters{
    int FrameCount;         //帧次
    int PhotoLineCount;     //拍照行数
    int ExposureTime;       //曝光时间
    int CameraGain;         //相机增益
};
//工单：编码器参数
struct CoderParameters{
    int PressureWheelACount;  //压轮编码器A计数
    int PressureWheelBCount;  //压轮编码器B计数
    int PressureWheel4FrequencyCount; //压轮编码器四倍频计数
    int PressureWheelK;             //压轮编码器系数
    int ExceptOnePixAccury;         //期望单个像素精度
    int EveryLineToCoderCount;      //每行对应的编码计数
    int Coder4FrequencyCount;       //编码器4倍频计数
    int CoderUnitScaleToDistance;   //编码器单位刻度对应距离
    int CoderUnitTimePlusCount;     //编码器单位时间脉冲计数
    int CoderTriggerLineCount;      //编码器触发行计数
    int CoderCount;                 //编码器计数
    int CoderCountTime;             //编码器计数时间
    int CoderCountEndFlag;          //编码器计数结束标记
    int CoderCircleCount;           //编码器装数
    int CoderPulseFiltering;        //编码器脉冲滤波
    int CoderChannel;               //编码通道
    int RollerCircumference;        //辊道周长
    int RollerMaxToLine;            //辊道最大速度对应行频
};
//工单：缺陷检测参数
struct DefectDetectionCoderParameters{
    int Camera12PixOffset;          //12相机像素偏差
    int Camera23PixOffset;         //23相机像素偏差
    int Camera24PixOffset;          //24相机像素偏差
    int SiyinToRollerDistance;      //丝印离辊道距离
    int GlassThickness;             //玻璃厚度
    int EnableDefect;               //缺陷检测启用
};
//工单：缺陷面积阈值
struct DefectAreaThresholdParameters{
    int HuashanAreaThreahold;        //划痕面积阈值
    int QijieAreaThreahold;         //气节面积阈值
    int ZanwuAreaThreahold;         //脏污面积阈值
};
//工单：自定义参数
struct CustomParameters{
    int SaveOrigin;                 //保存原图
    int SaveImage;                  //保存整图
    int SaveDefectIamge;            //保存缺检图
    int SaveCorpImage;              //保存裁剪图像
    int EnableDimensionalMeasurement; //尺寸测量启用
    int EnableDefect;               //缺陷检测启用
};
//工单
struct WorkOrder{
    LightControllerParameters LCParam;          //光电控制器参数
    DimensionalMeasurementParameters DMParam;   //尺寸测量参数
    ControllerSystemParameters CSParam;         //控制器系统参数
    std::vector<CameraParameters> CVecParam;       //相机参数
    CoderParameters CoderParam;                 //控制器参数
    DefectDetectionCoderParameters DDCParam;    //缺陷检测参数
    DefectAreaThresholdParameters DATParam;     //缺陷面积阈值参数
    CustomParameters CTParam;                   //自定义参数
};
// 图像裁剪参数
struct CameraCropArg{
    uint topPixCrop;        //图像上边缘裁剪多少像元
    uint bottomPixCrop;     //图像下边缘裁剪多少像元
    uint leftPixCrop;       //图像左侧边缘
    uint rightPixCrop;      //图像右侧边缘
    CameraCropArg():
        topPixCrop(0),
        bottomPixCrop(0),
        leftPixCrop(0),
        rightPixCrop(0){}
};
// 图像裁剪参数包
struct CropArgPackage{
    int cameracount ; //多少相机多少图片
    std::vector<CameraCropArg> args; //裁剪像元
};

// 单个缺陷数据
struct NewDefectUnitData{
    int id;              // 缺陷id
    int type;            // 缺陷种类
    QString time;        // 时间
    double pixLength;   // 长度像元数
    double pixWidth;    // 宽度像元数
    double pixX;        // 像元X
    double pixY;        // 像元Y
    double pixArea;     // 面积
    QString imagePath;  // 小图存储的地址
    NewDefectUnitData():
        id(0),
        type(0),
        time(""),
        pixLength(0),
        pixWidth(0),
        pixX(0),
        pixY(0),
        pixArea(0),
        imagePath(""){}

};

struct NewGlassResult{
    int currentFrameCount; //当前是第几帧
    std::vector<NewDefectUnitData> res;//每帧结果数据
    double pixGlassLength;  //这一帧长度
    double pixGlassWidth;   // 这一帧宽度
    QString FaceQimagePath;  // 图像保存
};


template <typename T>
class SafeDefinitionThreadSafeVector {
public:
    SafeDefinitionThreadSafeVector() {}

    void push(const T& item) {
        std::lock_guard<std::mutex> lock(mutex_);
        vector_.push_back(item);
    }

    bool empty() const {
        return vector_.empty();
    }

    void clear() {
        vector_.clear();
    }
public:
    std::vector<T> vector_;
    std::mutex mutex_;
};

//检出缺陷信息
struct regionInfor{
    cv::Mat region;
    QString path;
};

class __declspec(dllexport) HSTool
{
public:
    HSTool();
};

#endif // HSTOOL_H
