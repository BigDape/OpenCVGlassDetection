#include "SignalControlData.h"



#define ADDR0 0x0070    // 编码器单位刻度对应距离(um)
#define ADDR1 0x0010    // 编码脉冲滤波(us)
#define ADDR2 0x0860    // 编码器计数结束标志
#define ADDR3 0x0864    // 编码器计数
#define ADDR4 0x0868    // 编码器触发行计数
#define ADDR5 0x086C    // 编码器4倍频计数
#define ADDR6 0x0870    // 编码器单位时间脉冲计数
#define ADDR7 0x01D4    // 编码器计数时间(0.5s)
#define ADDR8 0x001C    // 编码通道
#define ADDR9 0x00F0    // 编码器转数
#define ADDR10 0x00F4   // 辊道周长(um)
#define ADDR11 0x00F8   // 期望单个像素精度(um)
#define ADDR12 0x00FC   // 辊道最大速度对应行频
#define ADDR13 0x01D8   // 每行对应的编码计数
#define ADDR14 0x0074   // 像素精度(um)
#define ADDR15 0x007C   // 光电信号脉冲滤波(us)
#define ADDR16 0x0090   // 相机触发脉冲持续时间(10ns)
#define ADDR17 0x0094   // 光电相机距离(行)
#define ADDR18 0x00C8   // 相机帧信号触发延时行数(行)
#define ADDR19 0x00CC   // 帧信号持续时间(10ns)
#define ADDR20 0x00D0   // 模块使能信号
#define ADDR21 0x00D8   // 相机拍照行数(行)
#define ADDR22 0x00DC   // 内部行频
#define ADDR23 0x0098   // 光场1延时时间(10ns)
#define ADDR24 0x009C   // 光场1发光时间(10ns)
#define ADDR25 0x00A0   // 光场2延时时间(10ns)
#define ADDR26 0x00A4   // 光场2发光时间(10ns)
#define ADDR27 0x00A8   // 光场3延时时间(10ns)
#define ADDR28 0x00AC   // 光场3发光时间(10ns)
#define ADDR29 0x00B0   // 光场4延时时间(10ns)
#define ADDR30 0x00B4   // 光场4发光时间(10ns)
#define ADDR31 0x00B8   // 光场5延时时间(10ns)
#define ADDR32 0x00BC   // 光场5发光时间(10ns)
#define ADDR33 0x00C0   // 光场6延时时间(10ns)
#define ADDR34 0x00C4   // 光场6发光时间(10ns)
#define ADDR35 0x0040   // 相机与光场控制
#define ADDR36 0x00D4   // 信号切换
#define ADDR37 0x01D0   // 行信号源选择
#define ADDR38 0x00E0   // 内部产生光电信号
#define ADDR39 0x00E4
#define ADDR40 0x00E8   // 帧信号为1时执行，为0时结束
#define ADDR41 0x00EC
#define ADDR42 0x0078   // 上位机反馈信号
#define ADDR43 0x0100   // 光场7延时时间(10ns)
#define ADDR44 0x0104   // 光场7发光时间(10ns)
#define ADDR45 0x0108   // 光场8延时时间(10ns)
#define ADDR46 0x010C   // 光场8发光时间(10ns)
#define ADDR47 0x0110   // 光场9延时时间(10ns)
#define ADDR48 0x0114   // 光场9发光时间(10ns)
#define ADDR49 0x0118   // 光场10延时时间(10ns)
#define ADDR50 0x011C   // 光场10发光时间(10ns)
#define ADDR51 0x0120   // 光场11延时时间(10ns)
#define ADDR52 0x0124   // 光场11发光时间(10ns)
#define ADDR53 0x0128   // 光场12延时时间(10ns)
#define ADDR54 0x012C   // 光场12发光时间(10ns)
#define ADDR55 0x0130   // 选择光场的数量
#define ADDR56 0x0134   // 横向暗场选择寄存器
#define ADDR57 0x0874  //编码器脉冲计数1
#define ADDR58 0x0878  //编码器脉冲计数2
#define ADDR59 0x01DC  //固定或自动拍照模式
#define ADDR60 0x01E0  //相机结束延时行数
#define ADDR61 0x087C  //压轮编码值可读标志
#define ADDR62 0x0844  //压轮编码器四倍频计数

void SignalControlData::InitRegs(QString ip, int port)
{
    // 连接到服务器
    qDebug()<<"m_pSig_comm.ConnectToServer";
    // m_pSig_comm.ConnectToServer(ip,port);
    m_pSig_comm.InitSock(ip.toStdString().c_str(),port);
    m_pSig_comm.ConnectToServer();
}

void SignalControlData::Trigger()
{
    unsigned int temp1 = 0;
    unsigned int temp2 = 1;
    m_pSig_comm.SetRegs(ADDR38, ADDR38, &temp2);
    m_pSig_comm.SetRegs(ADDR38, ADDR38, &temp1);
}

void SignalControlData::SetAllRegs(SignalControl data)
{
    m_pSig_comm.SetRegs(ADDR0, ADDR0, &data.temp0);
    m_pSig_comm.SetRegs(ADDR1, ADDR1, &data.temp1);
    m_pSig_comm.SetRegs(ADDR7, ADDR7, &data.temp7);
    m_pSig_comm.SetRegs(ADDR8, ADDR8, &data.temp8);
    m_pSig_comm.SetRegs(ADDR9, ADDR9, &data.temp9);
    m_pSig_comm.SetRegs(ADDR10, ADDR10, &data.temp10);
    m_pSig_comm.SetRegs(ADDR11, ADDR11, &data.temp11);
    m_pSig_comm.SetRegs(ADDR12, ADDR12, &data.temp12);

    m_pSig_comm.SetRegs(ADDR14, ADDR14, &data.temp14);
    m_pSig_comm.SetRegs(ADDR15, ADDR15, &data.temp15);
    m_pSig_comm.SetRegs(ADDR16, ADDR16, &data.temp16);
    m_pSig_comm.SetRegs(ADDR17, ADDR17, &data.temp17);
    m_pSig_comm.SetRegs(ADDR18, ADDR18, &data.temp18);
    m_pSig_comm.SetRegs(ADDR19, ADDR19, &data.temp19);
    m_pSig_comm.SetRegs(ADDR20, ADDR20, &data.temp20);
    m_pSig_comm.SetRegs(ADDR21, ADDR21, &data.temp21);
    m_pSig_comm.SetRegs(ADDR22, ADDR22, &data.temp22);

    m_pSig_comm.SetRegs(ADDR23, ADDR23, &data.temp23);
    m_pSig_comm.SetRegs(ADDR24, ADDR24, &data.temp24);
    m_pSig_comm.SetRegs(ADDR25, ADDR25, &data.temp25);
    m_pSig_comm.SetRegs(ADDR26, ADDR26, &data.temp26);
    m_pSig_comm.SetRegs(ADDR27, ADDR27, &data.temp27);
    m_pSig_comm.SetRegs(ADDR28, ADDR28, &data.temp28);
    m_pSig_comm.SetRegs(ADDR29, ADDR29, &data.temp29);
    m_pSig_comm.SetRegs(ADDR30, ADDR30, &data.temp30);
    m_pSig_comm.SetRegs(ADDR31, ADDR31, &data.temp31);
    m_pSig_comm.SetRegs(ADDR32, ADDR32, &data.temp32);
    m_pSig_comm.SetRegs(ADDR33, ADDR33, &data.temp33);
    m_pSig_comm.SetRegs(ADDR34, ADDR34, &data.temp34);
    m_pSig_comm.SetRegs(ADDR35, ADDR35, &data.temp35);
    m_pSig_comm.SetRegs(ADDR36, ADDR36, &data.temp36);
    m_pSig_comm.SetRegs(ADDR37, ADDR37, &data.temp37);

    m_pSig_comm.SetRegs(ADDR43, ADDR43, &data.temp43);
    m_pSig_comm.SetRegs(ADDR44, ADDR44, &data.temp44);
    m_pSig_comm.SetRegs(ADDR45, ADDR45, &data.temp45);
    m_pSig_comm.SetRegs(ADDR46, ADDR46, &data.temp46);
    m_pSig_comm.SetRegs(ADDR47, ADDR47, &data.temp47);
    m_pSig_comm.SetRegs(ADDR48, ADDR48, &data.temp48);
    m_pSig_comm.SetRegs(ADDR49, ADDR49, &data.temp49);
    m_pSig_comm.SetRegs(ADDR50, ADDR50, &data.temp50);
    m_pSig_comm.SetRegs(ADDR51, ADDR51, &data.temp51);
    m_pSig_comm.SetRegs(ADDR52, ADDR52, &data.temp52);
    m_pSig_comm.SetRegs(ADDR53, ADDR53, &data.temp53);
    m_pSig_comm.SetRegs(ADDR54, ADDR54, &data.temp54);
    m_pSig_comm.SetRegs(ADDR55, ADDR55, &data.temp55);
    m_pSig_comm.SetRegs(ADDR56, ADDR56, &data.temp56);

    m_pSig_comm.SetRegs(ADDR59, ADDR59, &data.tempAutoPhoto);
    m_pSig_comm.SetRegs(ADDR60, ADDR60, &data.tempPhotoEndDelayLine);
}

void SignalControlData::SetReg(unsigned short addr_s,
                               unsigned short addr_e,
                               unsigned int data)
{
    m_pSig_comm.SetRegs(addr_s,addr_e,&data);
}

void SignalControlData::GetRealTimeData(unsigned int& FrameSignal, unsigned int& AlmLightSignal)
{
    //帧信号
    m_pSig_comm.GetRegs(ADDR40, ADDR40, &FrameSignal);//1表示控制器在控制帧信号，随后为0

    //报警灯
    if (AlmLightSignal ==  true) {
          AlmLightSignal = false;
          uint lightnum = AlmLightSignal;
          m_pSig_comm.SetRegs(ADDR41, ADDR41, &lightnum);
    }
}

void SignalControlData::GetAllData(SignalControl& data)
{
    m_pSig_comm.GetRegs(ADDR0, ADDR0, &data.temp0);
    m_pSig_comm.GetRegs(ADDR1, ADDR1, &data.temp1);
    m_pSig_comm.GetRegs(ADDR2, ADDR2, &data.temp2);
    m_pSig_comm.GetRegs(ADDR3, ADDR3, &data.temp3);
    m_pSig_comm.GetRegs(ADDR4, ADDR4, &data.temp4);
    m_pSig_comm.GetRegs(ADDR5, ADDR5, &data.temp5);
    m_pSig_comm.GetRegs(ADDR6, ADDR6, &data.temp6);
    m_pSig_comm.GetRegs(ADDR7, ADDR7, &data.temp7);
    m_pSig_comm.GetRegs(ADDR8, ADDR8, &data.temp8);
    m_pSig_comm.GetRegs(ADDR9, ADDR9, &data.temp9);
    m_pSig_comm.GetRegs(ADDR10, ADDR10, &data.temp10);
    m_pSig_comm.GetRegs(ADDR11, ADDR11, &data.temp11);
    m_pSig_comm.GetRegs(ADDR12, ADDR12, &data.temp12);
    m_pSig_comm.GetRegs(ADDR13, ADDR13, &data.temp13);

    m_pSig_comm.GetRegs(ADDR14, ADDR14, &data.temp14);
    m_pSig_comm.GetRegs(ADDR15, ADDR15, &data.temp15);
    m_pSig_comm.GetRegs(ADDR16, ADDR16, &data.temp16);
    m_pSig_comm.GetRegs(ADDR17, ADDR17, &data.temp17);
    m_pSig_comm.GetRegs(ADDR19, ADDR19, &data.temp19);
    m_pSig_comm.GetRegs(ADDR20, ADDR20, &data.temp20);
    m_pSig_comm.GetRegs(ADDR21, ADDR21, &data.temp21);
    m_pSig_comm.GetRegs(ADDR22, ADDR22, &data.temp22);

    m_pSig_comm.GetRegs(ADDR23, ADDR23, &data.temp23);
    m_pSig_comm.GetRegs(ADDR24, ADDR24, &data.temp24);
    m_pSig_comm.GetRegs(ADDR25, ADDR25, &data.temp25);
    m_pSig_comm.GetRegs(ADDR26, ADDR26, &data.temp26);
    m_pSig_comm.GetRegs(ADDR27, ADDR27, &data.temp27);
    m_pSig_comm.GetRegs(ADDR28, ADDR28, &data.temp28);
    m_pSig_comm.GetRegs(ADDR29, ADDR29, &data.temp29);
    m_pSig_comm.GetRegs(ADDR30, ADDR30, &data.temp30);
    m_pSig_comm.GetRegs(ADDR31, ADDR31, &data.temp31);
    m_pSig_comm.GetRegs(ADDR32, ADDR32, &data.temp32);
    m_pSig_comm.GetRegs(ADDR33, ADDR33, &data.temp33);
    m_pSig_comm.GetRegs(ADDR34, ADDR34, &data.temp34);
    m_pSig_comm.GetRegs(ADDR35, ADDR35, &data.temp35);
    m_pSig_comm.GetRegs(ADDR36, ADDR36, &data.temp36);
    m_pSig_comm.GetRegs(ADDR37, ADDR37, &data.temp37);

    m_pSig_comm.GetRegs(ADDR43, ADDR43, &data.temp43);
    m_pSig_comm.GetRegs(ADDR44, ADDR44, &data.temp44);
    m_pSig_comm.GetRegs(ADDR45, ADDR45, &data.temp45);
    m_pSig_comm.GetRegs(ADDR46, ADDR46, &data.temp46);
    m_pSig_comm.GetRegs(ADDR47, ADDR47, &data.temp47);
    m_pSig_comm.GetRegs(ADDR48, ADDR48, &data.temp48);
    m_pSig_comm.GetRegs(ADDR49, ADDR49, &data.temp49);
    m_pSig_comm.GetRegs(ADDR50, ADDR50, &data.temp50);
    m_pSig_comm.GetRegs(ADDR51, ADDR51, &data.temp51);
    m_pSig_comm.GetRegs(ADDR52, ADDR52, &data.temp52);
    m_pSig_comm.GetRegs(ADDR53, ADDR53, &data.temp53);
    m_pSig_comm.GetRegs(ADDR54, ADDR54, &data.temp54);
    m_pSig_comm.GetRegs(ADDR55, ADDR55, &data.temp55);
    m_pSig_comm.GetRegs(ADDR56, ADDR56, &data.temp56);

    m_pSig_comm.GetRegs(ADDR59, ADDR59, &data.tempAutoPhoto);
    m_pSig_comm.GetRegs(ADDR60, ADDR60, &data.tempPhotoEndDelayLine);
}

bool SignalControlData::TestIPConnect()
{
    return m_pSig_comm.IsOpen();
}


