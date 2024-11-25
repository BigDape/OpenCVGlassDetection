#include "SignalControlData.h"


// 更换寄存器地址
/*编码器脉冲滤波*/
#define ADDR1 0x0010
#define ADDR15 0x0460       // 光电信号脉冲滤波
#define ADDR63 0x0464       // 编码数产生拍照脉冲，已经对编码进行四倍频(压轮周长/编码器转数*4 = 值)
#define ADDR64 0x0468       // 编码器参数.编码器模式(0辊道/1压轮)
#define ADDR69 0x0050       // 第一个光电触发后，电磁阀降下的延迟时间
#define ADDR70 0x0054       // 第一个光电离开后，电磁阀升起的延迟时间
#define ADDR71 0x0058       // 第二个光电触发后，电磁阀降下的延迟时间
#define ADDR72 0x005C       // 第二个光电离开后，电磁阀升起的延迟时间
#define ADDR57 0x0014       // 压轮编码器A计数
#define ADDR58 0x0018       // 压轮编码器B计数
#define ADDR79 0x001C       // 查看错误拍照次数

#define ADDR24 0x0024       // 光源控制器参数.光场1发光时间
#define ADDR26 0x0028       // 光源控制器参数.光场2发光时间
#define ADDR28 0x002C       // 光源控制器参数.光场3发光时间
#define ADDR65 0x0020       // 光源同步信号延时寄存器
#define ADDR60 0x0030       // 拍照模式(0固定/1自动)
#define ADDR80 0x0040       // 光源相机使能信号1打开0关闭
#define ADDR35 0x0048       // 工作模式0工作/1测试
#define ADDR66 0x0068       // 光源脉冲结束点寄存器
#define ADDR67 0x0034       // 同步脉冲周期寄存器
#define ADDR18 0x0450       // 相机帧信号触发延时行数
#define ADDR61 0x0454       // 拍照结束延时行数
#define ADDR68 0x0044       // 帧信号输出



#define ADDR75 0x0070       // 第3个光电触发后，入口压轮的编码计数
#define ADDR76 0x0074       // 第4个光电触发后，出口压轮的编码计数
#define ADDR77 0x0078       // 第3个光电触发后，入口压轮的编码计数
#define ADDR78 0x007C       // 第4个光电触发后，出口压轮的编码计数



void SignalControlData::InitRegs(QString ip, int port)
{
    // 连接到服务器
    qDebug()<<"m_pSig_comm.ConnectToServer";
    m_pSig_comm.InitSock(ip.toStdString().c_str(),port);
    m_pSig_comm.ConnectToServer();

}

void SignalControlData::Trigger()
{
    // unsigned int temp1 = 0;
    // unsigned int temp2 = 1;
    // m_pSig_comm.SetRegs(ADDR38, ADDR38, &temp2);
    // m_pSig_comm.SetRegs(ADDR38, ADDR38, &temp1);
}

void SignalControlData::SetAllRegs(SignalControl data)
{
    // 有效地址
    m_pSig_comm.SetRegs(ADDR1, ADDR1, &data.EncodePulseFilterUs);
    m_pSig_comm.SetRegs(ADDR15, ADDR15, &data.PhotoelectricSensorFiltering);
    m_pSig_comm.SetRegs(ADDR18, ADDR18, &data.CameraFrameSignalTriggerDelay);
    m_pSig_comm.SetRegs(ADDR24, ADDR24, &data.LightField1GlowTime);
    m_pSig_comm.SetRegs(ADDR26, ADDR26, &data.LightField2GlowTime);
    m_pSig_comm.SetRegs(ADDR28, ADDR28, &data.LightField3GlowTime);
    m_pSig_comm.SetRegs(ADDR35, ADDR35, &data.WorkMode);

    m_pSig_comm.SetRegs(ADDR60, ADDR60, &data.PhotoMode);
    m_pSig_comm.SetRegs(ADDR61, ADDR61, &data.TimelapseAfterPhotoShootEnd);

    m_pSig_comm.SetRegs(ADDR63, ADDR63, &data.WheelEncoderPhotoPulse);
    m_pSig_comm.SetRegs(ADDR64, ADDR64, &data.EncoderMode);
    m_pSig_comm.SetRegs(ADDR65, ADDR65, &data.LightSignalSynchronizationDelayRegister);
    m_pSig_comm.SetRegs(ADDR66, ADDR66, &data.LightSourcePulseEndPointRegister);
    m_pSig_comm.SetRegs(ADDR67, ADDR67, &data.SyncPulsePeriodRegister);

    m_pSig_comm.SetRegs(ADDR69, ADDR69, &data.SolenoidValve1DownDelay);
    m_pSig_comm.SetRegs(ADDR70, ADDR70, &data.SolenoidValve1UpDelay);
    m_pSig_comm.SetRegs(ADDR71, ADDR71, &data.SolenoidValve2DownDelay);
    m_pSig_comm.SetRegs(ADDR72, ADDR72, &data.SolenoidValve2UpDelay);
    m_pSig_comm.SetRegs(ADDR80, ADDR80, &data.LightCameraEnable);
}

void SignalControlData::SetReg(unsigned short addr_s,
                               unsigned short addr_e,
                               unsigned int data)
{
    m_pSig_comm.SetRegs(addr_s,addr_e,&data);
}

void SignalControlData::GetRealTimeData(unsigned int& FrameSignal,
                                        unsigned int& CoderACount,
                                        unsigned int& CoderBCount,
                                        unsigned int& errorPhotoCount)
{

    m_pSig_comm.GetRegs(ADDR68, ADDR68, &FrameSignal);//帧信号
    m_pSig_comm.GetRegs(ADDR57, ADDR57, &CoderACount);//编码器A相计数
    m_pSig_comm.GetRegs(ADDR58, ADDR58, &CoderBCount);//编码器B相计数
    m_pSig_comm.GetRegs(ADDR79, ADDR79, &errorPhotoCount);//查看错误编码数

}

void SignalControlData::GetAllData(SignalControl& data)
{
    // 有效地址
    m_pSig_comm.GetRegs(ADDR1, ADDR1, &data.EncodePulseFilterUs);
    m_pSig_comm.GetRegs(ADDR15, ADDR15, &data.PhotoelectricSensorFiltering);
    m_pSig_comm.GetRegs(ADDR18, ADDR18, &data.CameraFrameSignalTriggerDelay);
    m_pSig_comm.GetRegs(ADDR24, ADDR24, &data.LightField1GlowTime);
    m_pSig_comm.GetRegs(ADDR26, ADDR26, &data.LightField2GlowTime);
    m_pSig_comm.GetRegs(ADDR28, ADDR28, &data.LightField3GlowTime);
    m_pSig_comm.GetRegs(ADDR35, ADDR35, &data.LightCameraEnable);
    m_pSig_comm.GetRegs(ADDR57, ADDR57, &data.WheelAEncoder);
    m_pSig_comm.GetRegs(ADDR58, ADDR58, &data.WheelBEncoder);

    m_pSig_comm.GetRegs(ADDR60, ADDR60, &data.PhotoMode);
    m_pSig_comm.GetRegs(ADDR61, ADDR61, &data.TimelapseAfterPhotoShootEnd);

    m_pSig_comm.GetRegs(ADDR63, ADDR63, &data.WheelEncoderPhotoPulse);
    m_pSig_comm.GetRegs(ADDR64, ADDR64, &data.EncoderMode);
    m_pSig_comm.GetRegs(ADDR65, ADDR65, &data.LightSignalSynchronizationDelayRegister);
    m_pSig_comm.GetRegs(ADDR66, ADDR66, &data.LightSourcePulseEndPointRegister);
    m_pSig_comm.GetRegs(ADDR67, ADDR67, &data.SyncPulsePeriodRegister);


    m_pSig_comm.GetRegs(ADDR68, ADDR68, &data.FrameSignalOutput);
    m_pSig_comm.GetRegs(ADDR69, ADDR69, &data.SolenoidValve1DownDelay);
    m_pSig_comm.GetRegs(ADDR70, ADDR70, &data.SolenoidValve1UpDelay);
    m_pSig_comm.GetRegs(ADDR71, ADDR71, &data.SolenoidValve2DownDelay);
    m_pSig_comm.GetRegs(ADDR72, ADDR72, &data.SolenoidValve2UpDelay);

    m_pSig_comm.GetRegs(ADDR79, ADDR79, &data.ErrorPhotoCount);
}

bool SignalControlData::TestIPConnect()
{
    return m_pSig_comm.IsOpen();
}


