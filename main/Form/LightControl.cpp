#include "LightControl.h"
#include "ui_LightControl.h"
#include <QTimer>
#include <QDir>
#include <windows.h>
#include <QSettings>
#include "../Global.h"
#include "../HsListener.h"
#include "HSSocketInterface.h"

typedef HSJsoncppNamespace::HSJsoncppInterface* (*createJsoncppObjectFunc1)();
typedef SocketNameSpace::HSSocketInterface* (*createSocketObjectFunc1)();

LightControl::LightControl( QWidget* parent)
    : QWidget(parent)
    , ui(new Ui::LightControl)
    , SocketObjectPtr(nullptr)
    , jsoncppPtr(nullptr)
{
    ui->setupUi(this);
    //
    // 动态加载jsoncpp组件
    //
    if (jsoncppPtr==nullptr) {
        QString exePath = QCoreApplication::applicationDirPath();
        QString dllPath = exePath + "/../jsoncpp/jsoncpp.dll";
        jsoncppDllHandle = LoadLibrary(dllPath.toStdWString().c_str());
        if (!jsoncppDllHandle) {
            qFatal() << "Failed to load DLL. Error code: " << GetLastError();
        }
        // 获取创建数据库对象的函数指针
        createJsoncppObjectFunc1 createFunc = (createJsoncppObjectFunc1)GetProcAddress(jsoncppDllHandle, "createJsoncppObject");
        if (!createFunc) {
            qDebug() << "Failed to get function pointer. Error code: " << GetLastError() ;
            FreeLibrary(jsoncppDllHandle);
        } else {
            qDebug() << "Success to get  jsoncppDllHandle function pointer. ";
        }
        jsoncppPtr = createFunc();
    }
    //
    // 动态加载通讯组件
    //
    if (SocketObjectPtr == nullptr) {
        QString exePath = QCoreApplication::applicationDirPath();
        QString dllPath = exePath + "/../socket/socket.dll";
        socketDllHandle = LoadLibrary(dllPath.toStdWString().c_str());
        if (!socketDllHandle) {
            qFatal() << "Failed to load DLL. Error code: " << GetLastError();
        }
        // 获取创建数据库对象的函数指针
        createSocketObjectFunc1 createFunc = (createSocketObjectFunc1)GetProcAddress(socketDllHandle, "createSocketObject");
        if (!createFunc) {
            qFatal() << "Failed to get function pointer. Error code: " << GetLastError() ;
            FreeLibrary(socketDllHandle);
        } else {
            qDebug() << "Success to get  socketDllHandle function pointer. ";
        }
        SocketObjectPtr = createFunc();
    }
    LightControl::initWidget();// 初始化窗口
    LightControl::initLoadRecipe();// 加载工单
    LightControl::initSocket();
    LightControl::initConnect();
    LightControl::SendDataToSignal();
    // 实时获取帧信号确定玻璃是否结束
    m_timer = new QTimer();
    connect(m_timer, &QTimer::timeout, this, &LightControl::getFrameSignal);
    m_timer->start(10);
}

//析构函数
LightControl::~LightControl()
{
    //将工单上的文件写入ini文件
    QString currentRecipe = ui->RecipeCB->currentText();
    QString iniPath = QDir::currentPath() + QString("/") + SYSTEMNAME;
    PARAM.SetParamterIntoIniFile(iniPath,"recipe",currentRecipe);

    if (jsoncppPtr!= nullptr) {
        FreeLibrary(jsoncppDllHandle);
    }
    if (SocketObjectPtr != nullptr) {
        FreeLibrary(socketDllHandle);
    }
    delete ui;
}


// 初始化输入框输入类型
void LightControl::initWidget()
{
    // 初始化工单下拉框
    QString recipeDir = QDir::currentPath() + QString("/") + "Recipes";
    qDebug()<<"recipeDir ="<<recipeDir;
    QDir dir(recipeDir);
    QFileInfoList fileList = dir.entryInfoList(QStringList() << "*.json");
    ui->RecipeCB->clear();
    for(auto fileInfo:fileList) {
        ui->RecipeCB->addItem(fileInfo.baseName());
    }

    //输入框确定类型
    QDoubleValidator* lineDouble = new QDoubleValidator(0, 100000, 3, nullptr);
    QIntValidator* lineInt = new QIntValidator(0, 1000000000, nullptr);
    QRegularExpressionValidator* lineIP = new QRegularExpressionValidator(QRegularExpression("((25[0-5]|2[0-4][0-9]|1[0-9][0-9]|[1-9][0-9]|[0-9])[\\.]){3}(25[0-5]|2[0-4][0-9]|1[0-9][0-9]|[1-9][0-9]|[0-9])"));
    QRegularExpressionValidator* linePort = new QRegularExpressionValidator(QRegularExpression("((6553[0-5])|[655[0-2][0-9]|65[0-4][0-9]{2}|6[0-4][0-9]{3}|[1-5][0-9]{4}|[1-9][0-9]{3}|[1-9][0-9]{2}|[1-9][0-9]|[0-9])"));
    //系统参数
    ui->CameraNumLE->setValidator(lineInt);
    ui->ServerIPLE->setValidator(lineIP);
    ui->PortLE->setValidator(linePort);
    //自定义参数
    //尺寸测量
    ui->YAccuracyLE->setValidator(lineDouble);
    ui->XCamera0AccuracyLE->setValidator(lineDouble);
    ui->XCamera1AccuracyLE->setValidator(lineDouble);
    //相机参数
    ui->Camera0FrameLE->setValidator(lineInt);
    ui->Camera0PhotoRowLE->setValidator(lineInt);
    ui->Camera0ExposureTimeLE->setValidator(lineInt);
    ui->Camera0GainLE->setValidator(lineInt);
    ui->Camera1FrameLE->setValidator(lineInt);
    ui->Camera1PhotoRowLE->setValidator(lineInt);
    ui->Camera1ExposureTimeLE->setValidator(lineInt);
    ui->Camera1GainLE->setValidator(lineInt);
    ui->Camera2FrameLE->setValidator(lineInt);
    ui->Camera2PhotoRowLE->setValidator(lineInt);
    ui->Camera2ExposureTimeLE->setValidator(lineInt);
    ui->Camera2GainLE->setValidator(lineInt);
    ui->Camera3FrameLE->setValidator(lineInt);
    ui->Camera3PhotoRowLE->setValidator(lineInt);
    ui->Camera3ExposureTimeLE->setValidator(lineInt);
    ui->Camera3GainLE->setValidator(lineInt);
    //编码器参数
    ui->EncodePulseFilterUsLE->setValidator(lineInt);
    ui->PhotoelectricSensorFilteringLE->setValidator(lineInt);
    ui->WheelEncoderPhotoPulseLE->setValidator(lineInt);
    ui->EncoderModeLE->setValidator(lineInt);
    ui->SolenoidValve1DownDelayLE->setValidator(lineInt);
    ui->SolenoidValve1UpDelayLE->setValidator(lineInt);
    ui->SolenoidValve2DownDelayLE->setValidator(lineInt);
    ui->SolenoidValve2UpDelayLE->setValidator(lineInt);
    ui->WheelAEncoderLE->setValidator(lineInt);
    ui->WheelBEncoderLE->setValidator(lineInt);
    ui->ErrorPhotoCountLE->setValidator(lineInt);
    //光源控制器参数
    ui->LightField1GlowTimeLE->setValidator(lineInt);
    ui->LightField2GlowTimeLE->setValidator(lineInt);
    ui->LightField3GlowTimeLE->setValidator(lineInt);
    ui->LightField4GlowTimeLE->setValidator(lineInt);
    ui->LightSignalSynchronizationDelayRegisterLE->setValidator(lineInt);
    ui->PhotoModeLE->setValidator(lineInt);
    ui->LightCameraEnableLE->setValidator(lineInt);
    ui->WorkModeLE->setValidator(lineInt);
    ui->LightSourcePulseEndPointRegisterLE->setValidator(lineInt);
    ui->SyncPulsePeriodRegisterLE->setValidator(lineInt);
    ui->CameraFrameSignalTriggerDelayLE->setValidator(lineInt);
    ui->TimelapseAfterPhotoShootEndLE->setValidator(lineInt);
    ui->SelectedLightFieldNumberLE->setValidator(lineInt);
    ui->FrameSignalOutputLE->setValidator(lineInt);
}

void LightControl::initLoadRecipe()
{
    QString iniPath = QDir::currentPath() + QString("/") + SYSTEMNAME;
    qDebug()<<"iniPath ="<<iniPath;
    QFile inifile(iniPath);
    if (!inifile.exists()) {
        LightControl::writeEmptyAppIni(iniPath, "default");
    }
    QString needLoadJsonFile = PARAM.GetParamterFromIniFile(iniPath,"system/recipe");//需要加载的工单名称system模块的recipe配置文件
    qDebug()<<"needLoadJsonFile ="<<needLoadJsonFile;
    if (ui->RecipeCB->findText(needLoadJsonFile) != -1) { //找到json工单
        ui->RecipeCB->setCurrentText(needLoadJsonFile);
        QString neddLoadJsonFileName = QDir::currentPath() + QString("/Recipes/") + needLoadJsonFile + QString(".json");
        LightControl::readRecipeToTable(neddLoadJsonFileName.toStdString());
    } else { //未找到
        QString message = tr("Not find in RecipeCB Items, now create new file. =>")+ needLoadJsonFile;
        INFOMATION.criticalMessageBox(this,message);
    }
}

void LightControl::initSocket()
{
    // 获取通讯处理模块
    if (SocketObjectPtr != NULL) {
        QString iniPath = QDir::currentPath() + QString("/") + SYSTEMNAME;
        QString IP = PARAM.GetParamterFromIniFile(iniPath,"system/serverIp");
        QString Port = PARAM.GetParamterFromIniFile(iniPath,"system/RegParaPort");
        SocketObjectPtr->InitRegs(IP,Port.toUInt());
    } 
}

void LightControl::initConnect()
{
    connect(ui->AllSet,SIGNAL(clicked()),this,SLOT(slotAllSet()));                              // 下发
    connect(ui->AllGet,SIGNAL(clicked()),this,SLOT(slotAllGet()));                              // 获取
    connect(ui->AllSave,SIGNAL(clicked()),this,SLOT(slotAllSave()));                            // 保存
    connect(ui->CreateRecipe,SIGNAL(clicked()),this, SLOT(slotCreateRecipe()));                 // 创建工单
    connect(ui->TestConnectBT,SIGNAL(clicked()), this, SLOT(slotTestConnect()));                // 测试连接
    connect(ui->Trigger,SIGNAL(clicked()), this, SLOT(slotTrigger()));                          // 触发
    connect(ui->RecipeCB, SIGNAL(currentIndexChanged(int)), this, SLOT(slotChangeRecipe(int))); // 切换工单
}

void LightControl::SendDataToSignal()
{
    if (SocketObjectPtr != nullptr) {
        SocketObjectPtr->SetAllRegs(m_signalctrl);
    }
}

// 读取json工单到表单中
void LightControl::readRecipeToTable(std::string filePath)
{
    jsoncppPtr->readRecipeFromJson(QString(filePath.c_str()), m_signalctrl);
    //系统参数
    ui->SystemNameLE->setText(m_signalctrl.systemName);
    ui->CameraNumLE->setText(QString::number(m_signalctrl.CamareNumber));
    ui->Camera0NameLE->setText(m_signalctrl.Camare0Name);
    ui->Camera1NameLE->setText(m_signalctrl.Camare1Name);
    ui->Camera2NameLE->setText(m_signalctrl.Camare2Name);
    ui->Camera3NameLE->setText(m_signalctrl.Camare3Name);
    ui->ServerIPLE->setText(m_signalctrl.ServerIP);
    ui->PortLE->setText(QString::number(m_signalctrl.ServerPort));
    //尺寸测量
    ui->YAccuracyLE->setText(QString::number(m_signalctrl.YAccuracy));
    ui->XCamera0AccuracyLE->setText(QString::number(m_signalctrl.XCamera0Accuracy));
    ui->XCamera1AccuracyLE->setText(QString::number(m_signalctrl.XCamera1Accuracy));
    //相机参数
    ui->Camera0FrameLE->setText(QString::number(m_signalctrl.Camera0Frame));
    ui->Camera0PhotoRowLE->setText(QString::number(m_signalctrl.Camera0PhotoRow));
    ui->Camera0ExposureTimeLE->setText(QString::number(m_signalctrl.Camera0ExposureTime));
    ui->Camera0GainLE->setText(QString::number(m_signalctrl.Camera0Gain));
    ui->Camera1FrameLE->setText(QString::number(m_signalctrl.Camera1Frame));
    ui->Camera1PhotoRowLE->setText(QString::number(m_signalctrl.Camera1PhotoRow));
    ui->Camera1ExposureTimeLE->setText(QString::number(m_signalctrl.Camera1ExposureTime));
    ui->Camera1GainLE->setText(QString::number(m_signalctrl.Camera1Gain));
    ui->Camera2FrameLE->setText(QString::number(m_signalctrl.Camera2Frame));
    ui->Camera2PhotoRowLE->setText(QString::number(m_signalctrl.Camera2PhotoRow));
    ui->Camera2ExposureTimeLE->setText(QString::number(m_signalctrl.Camera2ExposureTime));
    ui->Camera2GainLE->setText(QString::number(m_signalctrl.Camera2Gain));
    ui->Camera3FrameLE->setText(QString::number(m_signalctrl.Camera3Frame));
    ui->Camera3PhotoRowLE->setText(QString::number(m_signalctrl.Camera3PhotoRow));
    ui->Camera3ExposureTimeLE->setText(QString::number(m_signalctrl.Camera3ExposureTime));
    ui->Camera3GainLE->setText(QString::number(m_signalctrl.Camera3Gain));
    //编码器参数
    ui->EncodePulseFilterUsLE->setText(QString::number(m_signalctrl.EncodePulseFilterUs));
    ui->PhotoelectricSensorFilteringLE->setText(QString::number(m_signalctrl.PhotoelectricSensorFiltering));
    ui->WheelEncoderPhotoPulseLE->setText(QString::number(m_signalctrl.WheelEncoderPhotoPulse));
    ui->EncoderModeLE->setText(QString::number(m_signalctrl.EncoderMode));
    ui->SolenoidValve1DownDelayLE->setText(QString::number(m_signalctrl.SolenoidValve1DownDelay));
    ui->SolenoidValve1UpDelayLE->setText(QString::number(m_signalctrl.SolenoidValve1UpDelay));
    ui->SolenoidValve2DownDelayLE->setText(QString::number(m_signalctrl.SolenoidValve2DownDelay));
    ui->SolenoidValve2UpDelayLE->setText(QString::number(m_signalctrl.SolenoidValve2UpDelay));
    ui->WheelAEncoderLE->setText(QString::number(m_signalctrl.WheelAEncoder));
    ui->WheelBEncoderLE->setText(QString::number(m_signalctrl.WheelBEncoder));
    ui->ErrorPhotoCountLE->setText(QString::number(m_signalctrl.ErrorPhotoCount));
    //光源控制器参数
    ui->LightField1GlowTimeLE->setText(QString::number(m_signalctrl.LightField1GlowTime));
    ui->LightField2GlowTimeLE->setText(QString::number(m_signalctrl.LightField2GlowTime));
    ui->LightField3GlowTimeLE->setText(QString::number(m_signalctrl.LightField3GlowTime));
    ui->LightField4GlowTimeLE->setText(QString::number(m_signalctrl.LightField4GlowTime));
    ui->LightSignalSynchronizationDelayRegisterLE->setText(QString::number(m_signalctrl.LightSignalSynchronizationDelayRegister));
    ui->PhotoModeLE->setText(QString::number(m_signalctrl.PhotoMode));
    ui->LightCameraEnableLE->setText(QString::number(m_signalctrl.LightCameraEnable));
    ui->WorkModeLE->setText(QString::number(m_signalctrl.WorkMode));
    ui->LightSourcePulseEndPointRegisterLE->setText(QString::number(m_signalctrl.LightSourcePulseEndPointRegister));
    ui->SyncPulsePeriodRegisterLE->setText(QString::number(m_signalctrl.SyncPulsePeriodRegister));
    ui->CameraFrameSignalTriggerDelayLE->setText(QString::number(m_signalctrl.CameraFrameSignalTriggerDelay));
    ui->TimelapseAfterPhotoShootEndLE->setText(QString::number(m_signalctrl.TimelapseAfterPhotoShootEnd));
    ui->SelectedLightFieldNumberLE->setText(QString::number(m_signalctrl.SelectedLightFieldNumber));
    ui->FrameSignalOutputLE->setText(QString::number(m_signalctrl.FrameSignalOutput));

    //
    // 初始化全局变量
    //
    PARAM.SystemName = m_signalctrl.systemName;
    PARAM.camDefineNum = m_signalctrl.CamareNumber;
    PARAM.Camera0Name = m_signalctrl.Camare0Name;
    PARAM.Camera1Name = m_signalctrl.Camare1Name;
    PARAM.Camera2Name = m_signalctrl.Camare2Name;
    PARAM.Camera3Name = m_signalctrl.Camare3Name;
    PARAM.serverIp = m_signalctrl.ServerIP;
    PARAM.serverPort = m_signalctrl.ServerPort;
    PARAM.YAccuracy = m_signalctrl.YAccuracy;
    PARAM.XCamera0Accuracy = m_signalctrl.XCamera0Accuracy;
    PARAM.XCamera1Accuracy = m_signalctrl.XCamera1Accuracy;
    PARAM.Camera0Frame = m_signalctrl.Camera0Frame;
    PARAM.Camera0PhotoRow = m_signalctrl.Camera0PhotoRow;
    PARAM.Camera0ExposureTime = m_signalctrl.Camera0ExposureTime;
    PARAM.Camera0Gain = m_signalctrl.Camera0Gain;
    PARAM.Camera1Frame = m_signalctrl.Camera1Frame;
    PARAM.Camera1PhotoRow = m_signalctrl.Camera1PhotoRow;
    PARAM.Camera1ExposureTime = m_signalctrl.Camera1ExposureTime;
    PARAM.Camera1Gain = m_signalctrl.Camera1Gain;
    PARAM.Camera2Frame = m_signalctrl.Camera2Frame;
    PARAM.Camera2PhotoRow = m_signalctrl.Camera2PhotoRow;
    PARAM.Camera2ExposureTime = m_signalctrl.Camera2ExposureTime;
    PARAM.Camera2Gain = m_signalctrl.Camera2Gain;
    PARAM.Camera3Frame = m_signalctrl.Camera3Frame;
    PARAM.Camera3PhotoRow = m_signalctrl.Camera3PhotoRow;
    PARAM.Camera3ExposureTime = m_signalctrl.Camera3ExposureTime;
    PARAM.Camera3Gain = m_signalctrl.Camera3Gain;
    PARAM.EncodePulseFilterUs = m_signalctrl.EncodePulseFilterUs;   // 编码器参数--编码脉冲滤波
    PARAM.PhotoelectricSensorFiltering = m_signalctrl.PhotoelectricSensorFiltering;// 编码器参数--光电传感器滤波
    PARAM.WheelEncoderPhotoPulse = m_signalctrl.WheelEncoderPhotoPulse;   //  编码器参数--压轮编码器产生拍照脉冲(四倍频)
    PARAM.EncoderMode = m_signalctrl.EncoderMode;              // 编码器参数--编码器模式(0辊道/1压轮)
    PARAM.SolenoidValve1DownDelay = m_signalctrl.SolenoidValve1DownDelay;  // 编码器参数--光电1触发电磁阀降下延时(ms)
    PARAM.SolenoidValve1UpDelay = m_signalctrl.SolenoidValve1UpDelay;    // 编码器参数--光电1离开电磁阀升起延时(ms)
    PARAM.SolenoidValve2DownDelay = m_signalctrl.SolenoidValve2DownDelay;  // 编码器参数--光电2触发电磁阀降下延时(ms)
    PARAM.SolenoidValve2UpDelay = m_signalctrl.SolenoidValve2UpDelay;// 编码器参数--光电2离开电磁阀升起延时(ms)
    PARAM.WheelAEncoder = m_signalctrl.WheelAEncoder;             // 编码器参数--压轮编码器A相计数
    PARAM.WheelBEncoder = m_signalctrl.WheelBEncoder;         // 编码器参数--压轮编码器B相计数
    PARAM.ErrorPhotoCount = m_signalctrl.ErrorPhotoCount;       // 编码器参数--查看错误拍照次数
    PARAM.LightField1GlowTime = m_signalctrl.LightField1GlowTime;   // 光源控制器参数--光场1发光时间10ns
    PARAM.LightField2GlowTime = m_signalctrl.LightField2GlowTime;   // 光源控制器参数--光场2发光时间10ns
    PARAM.LightField3GlowTime = m_signalctrl.LightField3GlowTime;   // 光源控制器参数--光场3发光时间10ns
    PARAM.LightField4GlowTime = m_signalctrl.LightField4GlowTime;    // 光源控制器参数--光场4发光时间10ns
    PARAM.LightSignalSynchronizationDelayRegister = m_signalctrl.LightSignalSynchronizationDelayRegister;// 光源控制器参数--光源信号同步信号延时寄存器
    PARAM.PhotoMode = m_signalctrl.PhotoMode;             // 光源控制器参数--拍照模式
    PARAM.LightCameraEnable = m_signalctrl.LightCameraEnable;     // 光源控制器参数--光源相机使能信号
    PARAM.WorkMode = m_signalctrl.WorkMode;              // 光源控制器参数--工作模式(0工作/1测试)
    PARAM.LightSourcePulseEndPointRegister = m_signalctrl.LightSourcePulseEndPointRegister;// 光源控制器参数--光源脉冲结束点寄存器
    PARAM.SyncPulsePeriodRegister = m_signalctrl.SyncPulsePeriodRegister; //光源控制器参数--同步脉冲周期寄存器
    PARAM.CameraFrameSignalTriggerDelay = m_signalctrl.CameraFrameSignalTriggerDelay;// 光源控制器参数--相机帧信号触发延时行数(行)
    PARAM.TimelapseAfterPhotoShootEnd = m_signalctrl.TimelapseAfterPhotoShootEnd;// 光源控制器参数--拍照结束延时行数(行)
    PARAM.SelectedLightFieldNumber = m_signalctrl.SelectedLightFieldNumber;// 光源控制器参数--选择光场的数量
    PARAM.FrameSignalOutput = m_signalctrl.FrameSignalOutput;// 光源控制器参数--帧信号输出
}

// 全部数据下发
void LightControl::slotAllSet()
{
    if (SocketObjectPtr != nullptr) {
        LightControl::getUiContentIntoStruct();
        SocketObjectPtr->SetAllRegs(m_signalctrl);
        INFOMATION.informationMessageBox(this,tr("information"),QString(tr("All set success.")));
    } else {
        INFOMATION.informationMessageBox(this,tr("information"),QString(tr("All set fail.")));
    }
}


void LightControl::slotAllSave()
{
    // 将所有页的设置数据获取下来
    LightControl::getUiContentIntoStruct();
    // 将数据存储到json文件中
    QString filename = ui->RecipeCB->currentText();
    QString dirPath = QCoreApplication::applicationDirPath() + QString("/Recipes/");
    QString currentfilename = dirPath + filename + QString(".json");
    qDebug()<<"slotAllSave path ="<<currentfilename;
    jsoncppPtr->writeRecipeToJson(currentfilename,m_signalctrl);
    INFOMATION.informationMessageBox(this,tr("information"),QString(tr("Save recipe success.")));
}

//新建工单
void LightControl::slotCreateRecipe()
{
    // 询问用户名称
    QDateTime current_date_time = QDateTime::currentDateTime();
    QString current_date = current_date_time.toString("yyyy_MM_dd_hh_mm_ss");
    QString defaultRecipeFileName = current_date;
    QString newRecipeFileName = INFOMATION.inputMessageBox(this,"新建工单","请输入新建工单名称",defaultRecipeFileName);
    // 创建目录和文件
    QString recipeDir = QCoreApplication::applicationDirPath() + QString("/Recipes/");
    QDir dir;
    if (!dir.exists(recipeDir)) {
        if (!dir.mkpath(recipeDir)) {
            qDebug() << "Failed to create directory.";
        }
    }
    QString newjsonfile = newRecipeFileName + QString(".json");
    QString recipeFileName = recipeDir + newjsonfile;
    QFile file(recipeFileName);
    if (file.open(QIODevice::WriteOnly)) {
        file.close();
        qDebug() << "Empty file created successfully.";
    } else {
        qDebug() << "Failed to create empty file." ;
    }
    jsoncppPtr->writeEmptyRecipeToJson(recipeFileName);  //创建空白名单
    LightControl::readRecipeToTable(recipeFileName.toStdString());
    ui->RecipeCB->addItem(newRecipeFileName);
    ui->RecipeCB->setCurrentText(newRecipeFileName);
    INFOMATION.informationMessageBox(this,tr("information"),QString(tr("Create recipe success.")));
}

void LightControl::slotAllGet()
{
    if (SocketObjectPtr!= nullptr) {
        SocketObjectPtr->GetAllData(m_signalctrl);
        LightControl::setUiContentFromStruct();
        INFOMATION.informationMessageBox(this,tr("information"),QString(tr("Get data success.")));
    } else {
        INFOMATION.informationMessageBox(this,tr("information"),QString(tr("Get data fail.")));
    }
}

void LightControl::slotTestConnect()
{
    if(SocketObjectPtr!= nullptr) {
        if( SocketObjectPtr->TestIPConnect()) {
            QString ipinfor = QString("测试") + PARAM.serverIp + QString(":") + QString::number(PARAM.serverPort);
            INFOMATION.informationMessageBox(this,QString("测试结果"),ipinfor + QString("已连接"));
        } else {
            QString ipinfor = QString("测试") + PARAM.serverIp + QString(":") + QString::number(PARAM.serverPort);
            INFOMATION.informationMessageBox(this,QString("测试结果"),ipinfor + QString("未连接"));
        }
    }
}

void LightControl::slotTrigger()
{
    if (SocketObjectPtr!= nullptr) {
        SocketObjectPtr->Trigger();
        INFOMATION.informationMessageBox(this,tr("information"),QString(tr("Trigger success.")));
    } else {
        INFOMATION.informationMessageBox(this,tr("information"),QString(tr("Trigger fail.")));
    }
}

void LightControl::slotChangeRecipe(int index)
{
    qDebug()<<"index ="<<index;
    QString needLoadJsonFile = QDir::currentPath() + QString("/Recipes/") + ui->RecipeCB->currentText();
    QDir dir(QDir::currentPath() + QString("/Recipes/"));
    QFileInfoList fileList = dir.entryInfoList(QStringList() << "*.json");
    if (fileList.size() == 0) { //没有找到任何json工单
        INFOMATION.informationMessageBox(this,QString("信息"),QDir::currentPath() + QString("/Recipes/") + QString("目录为空或者错误"));
    } else {                    //找到了json工单
        //遍历文件夹
        for(auto fileInfo:fileList) {
            qDebug()<<"fileInfo.baseName() ="<<fileInfo.baseName() <<",ui->RecipeCB->currentText()="<<ui->RecipeCB->currentText();
            if(fileInfo.baseName() == ui->RecipeCB->currentText()) {
                QString jsonFullName = needLoadJsonFile + QString(".json");
                LightControl::readRecipeToTable(jsonFullName.toStdString());
                INFOMATION.informationMessageBox(this,QString("信息"),QString("切换工单成功"));
                return;
            }
        }
        INFOMATION.informationMessageBox(this,QString("信息"),QString("切换工单失败"));
    }
}

// 新建一个初始化文件app.ini
void LightControl::writeEmptyAppIni(QString filePath, QString recipeName)
{
    QDir dir;
    if (!dir.exists(filePath.left(filePath.lastIndexOf('/')))) {
        if (!dir.mkpath(filePath.left(filePath.lastIndexOf('/')))) {
            qDebug() << "Failed to create directory.";
        }
    }

    QSettings settings(filePath, QSettings::IniFormat);
    settings.beginGroup("system");
    settings.setValue("recipe", recipeName);
    settings.setValue("serverIp", "192.168.1.200");
    settings.setValue("RegParaPort", "7002");
    settings.endGroup();
    qDebug() << "INI file created and written successfully.";
}

// 将输入框中数据全部读取下来
void LightControl::getUiContentIntoStruct()
{
    //系统参数
    m_signalctrl.systemName = ui->SystemNameLE->text();
    m_signalctrl.CamareNumber = ui->CameraNumLE->text().toInt();
    m_signalctrl.Camare0Name = ui->Camera0NameLE->text();
    m_signalctrl.Camare1Name = ui->Camera1NameLE->text();
    m_signalctrl.Camare2Name = ui->Camera2NameLE->text();
    m_signalctrl.Camare3Name = ui->Camera3NameLE->text();
    m_signalctrl.ServerIP = ui->ServerIPLE->text();
    m_signalctrl.ServerPort = ui->PortLE->text().toInt();
    //尺寸测量
    m_signalctrl.YAccuracy = ui->YAccuracyLE->text().toDouble();
    m_signalctrl.XCamera0Accuracy = ui->XCamera0AccuracyLE->text().toDouble();
    m_signalctrl.XCamera1Accuracy = ui->XCamera1AccuracyLE->text().toDouble();
    //相机参数
    m_signalctrl.Camera0Frame = ui->Camera0FrameLE->text().toInt();
    m_signalctrl.Camera0PhotoRow = ui->Camera0PhotoRowLE->text().toInt();
    m_signalctrl.Camera0ExposureTime = ui->Camera0ExposureTimeLE->text().toInt();
    m_signalctrl.Camera0Gain = ui->Camera0GainLE->text().toInt();
    m_signalctrl.Camera1Frame = ui->Camera1FrameLE->text().toInt();
    m_signalctrl.Camera1PhotoRow = ui->Camera1PhotoRowLE->text().toInt();
    m_signalctrl.Camera1ExposureTime = ui->Camera1ExposureTimeLE->text().toInt();
    m_signalctrl.Camera1Gain = ui->Camera1GainLE->text().toInt();
    m_signalctrl.Camera2Frame = ui->Camera2FrameLE->text().toInt();
    m_signalctrl.Camera2PhotoRow = ui->Camera2PhotoRowLE->text().toInt();
    m_signalctrl.Camera2ExposureTime = ui->Camera2ExposureTimeLE->text().toInt();
    m_signalctrl.Camera2Gain = ui->Camera2GainLE->text().toInt();
    m_signalctrl.Camera3Frame = ui->Camera3FrameLE->text().toInt();
    m_signalctrl.Camera3PhotoRow = ui->Camera3PhotoRowLE->text().toInt();
    m_signalctrl.Camera3ExposureTime = ui->Camera3ExposureTimeLE->text().toInt();
    m_signalctrl.Camera3Gain = ui->Camera3GainLE->text().toInt();
    //编码器参数
    m_signalctrl.EncodePulseFilterUs = ui->EncodePulseFilterUsLE->text().toInt();
    m_signalctrl.PhotoelectricSensorFiltering = ui->PhotoelectricSensorFilteringLE->text().toInt();
    m_signalctrl.WheelEncoderPhotoPulse = ui->WheelEncoderPhotoPulseLE->text().toInt();
    m_signalctrl.EncoderMode = ui->EncoderModeLE->text().toInt();
    m_signalctrl.SolenoidValve1DownDelay = ui->SolenoidValve1DownDelayLE->text().toInt();
    m_signalctrl.SolenoidValve1UpDelay = ui->SolenoidValve1UpDelayLE->text().toInt();
    m_signalctrl.SolenoidValve2DownDelay = ui->SolenoidValve2DownDelayLE->text().toInt();
    m_signalctrl.SolenoidValve2UpDelay = ui->SolenoidValve2UpDelayLE->text().toInt();
    m_signalctrl.WheelAEncoder = ui->WheelAEncoderLE->text().toInt();
    m_signalctrl.WheelBEncoder = ui->WheelBEncoderLE->text().toInt();
    m_signalctrl.ErrorPhotoCount = ui->ErrorPhotoCountLE->text().toInt();
    //光源控制器参数
    m_signalctrl.LightField1GlowTime = ui->LightField1GlowTimeLE->text().toInt();
    m_signalctrl.LightField2GlowTime = ui->LightField2GlowTimeLE->text().toInt();
    m_signalctrl.LightField3GlowTime = ui->LightField3GlowTimeLE->text().toInt();
    m_signalctrl.LightField4GlowTime = ui->LightField4GlowTimeLE->text().toInt();
    m_signalctrl.LightSignalSynchronizationDelayRegister = ui->LightSignalSynchronizationDelayRegisterLE->text().toInt();
    m_signalctrl.PhotoMode = ui->PhotoModeLE->text().toInt();
    m_signalctrl.LightCameraEnable = ui->LightCameraEnableLE->text().toInt();
    m_signalctrl.WorkMode = ui->WorkModeLE->text().toInt();
    m_signalctrl.LightSourcePulseEndPointRegister = ui->LightSourcePulseEndPointRegisterLE->text().toInt();
    m_signalctrl.SyncPulsePeriodRegister = ui->SyncPulsePeriodRegisterLE->text().toInt();
    m_signalctrl.CameraFrameSignalTriggerDelay = ui->CameraFrameSignalTriggerDelayLE->text().toInt();
    m_signalctrl.TimelapseAfterPhotoShootEnd = ui->TimelapseAfterPhotoShootEndLE->text().toInt();
    m_signalctrl.SelectedLightFieldNumber = ui->SelectedLightFieldNumberLE->text().toInt();
    m_signalctrl.FrameSignalOutput = ui->FrameSignalOutputLE->text().toInt();
}

void LightControl::setUiContentFromStruct()
{
    //系统参数
    ui->SystemNameLE->setText(m_signalctrl.systemName);
    ui->CameraNumLE->setText(QString::number(m_signalctrl.CamareNumber));
    ui->Camera0NameLE->setText(m_signalctrl.Camare0Name);
    ui->Camera1NameLE->setText(m_signalctrl.Camare1Name);
    ui->Camera2NameLE->setText(m_signalctrl.Camare2Name);
    ui->Camera3NameLE->setText(m_signalctrl.Camare3Name);
    ui->ServerIPLE->setText(m_signalctrl.ServerIP);
    ui->PortLE->setText(QString::number(m_signalctrl.ServerPort));
    //尺寸测量
    ui->YAccuracyLE->setText(QString::number(m_signalctrl.YAccuracy));
    ui->XCamera0AccuracyLE->setText(QString::number(m_signalctrl.XCamera0Accuracy));
    ui->XCamera1AccuracyLE->setText(QString::number(m_signalctrl.XCamera1Accuracy));
    //相机参数
    ui->Camera0FrameLE->setText(QString::number(m_signalctrl.Camera0Frame));
    ui->Camera0PhotoRowLE->setText(QString::number(m_signalctrl.Camera0PhotoRow));
    ui->Camera0ExposureTimeLE->setText(QString::number(m_signalctrl.Camera0ExposureTime));
    ui->Camera0GainLE->setText(QString::number(m_signalctrl.Camera0Gain));
    ui->Camera1FrameLE->setText(QString::number(m_signalctrl.Camera1Frame));
    ui->Camera1PhotoRowLE->setText(QString::number(m_signalctrl.Camera1PhotoRow));
    ui->Camera1ExposureTimeLE->setText(QString::number(m_signalctrl.Camera1ExposureTime));
    ui->Camera1GainLE->setText(QString::number(m_signalctrl.Camera1Gain));
    ui->Camera2FrameLE->setText(QString::number(m_signalctrl.Camera2Frame));
    ui->Camera2PhotoRowLE->setText(QString::number(m_signalctrl.Camera2PhotoRow));
    ui->Camera2ExposureTimeLE->setText(QString::number(m_signalctrl.Camera2ExposureTime));
    ui->Camera2GainLE->setText(QString::number(m_signalctrl.Camera2Gain));
    ui->Camera3FrameLE->setText(QString::number(m_signalctrl.Camera3Frame));
    ui->Camera3PhotoRowLE->setText(QString::number(m_signalctrl.Camera3PhotoRow));
    ui->Camera3ExposureTimeLE->setText(QString::number(m_signalctrl.Camera3ExposureTime));
    ui->Camera3GainLE->setText(QString::number(m_signalctrl.Camera3Gain));
    //编码器参数
    ui->EncodePulseFilterUsLE->setText(QString::number(m_signalctrl.EncodePulseFilterUs));
    ui->PhotoelectricSensorFilteringLE->setText(QString::number(m_signalctrl.PhotoelectricSensorFiltering));
    ui->WheelEncoderPhotoPulseLE->setText(QString::number(m_signalctrl.WheelEncoderPhotoPulse));
    ui->EncoderModeLE->setText(QString::number(m_signalctrl.EncoderMode));
    ui->SolenoidValve1DownDelayLE->setText(QString::number(m_signalctrl.SolenoidValve1DownDelay));
    ui->SolenoidValve1UpDelayLE->setText(QString::number(m_signalctrl.SolenoidValve1UpDelay));
    ui->SolenoidValve2DownDelayLE->setText(QString::number(m_signalctrl.SolenoidValve2DownDelay));
    ui->SolenoidValve2UpDelayLE->setText(QString::number(m_signalctrl.SolenoidValve2UpDelay));
    ui->WheelAEncoderLE->setText(QString::number(m_signalctrl.WheelAEncoder));
    ui->WheelBEncoderLE->setText(QString::number(m_signalctrl.WheelBEncoder));
    ui->ErrorPhotoCountLE->setText(QString::number(m_signalctrl.ErrorPhotoCount));
    //光源控制器参数
    ui->LightField1GlowTimeLE->setText(QString::number(m_signalctrl.LightField1GlowTime));
    ui->LightField2GlowTimeLE->setText(QString::number(m_signalctrl.LightField2GlowTime));
    ui->LightField3GlowTimeLE->setText(QString::number(m_signalctrl.LightField3GlowTime));
    ui->LightField4GlowTimeLE->setText(QString::number(m_signalctrl.LightField4GlowTime));
    ui->LightSignalSynchronizationDelayRegisterLE->setText(QString::number(m_signalctrl.LightSignalSynchronizationDelayRegister));
    ui->PhotoModeLE->setText(QString::number(m_signalctrl.PhotoMode));
    ui->LightCameraEnableLE->setText(QString::number(m_signalctrl.LightCameraEnable));
    ui->WorkModeLE->setText(QString::number(m_signalctrl.WorkMode));
    ui->LightSourcePulseEndPointRegisterLE->setText(QString::number(m_signalctrl.LightSourcePulseEndPointRegister));
    ui->SyncPulsePeriodRegisterLE->setText(QString::number(m_signalctrl.SyncPulsePeriodRegister));
    ui->CameraFrameSignalTriggerDelayLE->setText(QString::number(m_signalctrl.CameraFrameSignalTriggerDelay));
    ui->TimelapseAfterPhotoShootEndLE->setText(QString::number(m_signalctrl.TimelapseAfterPhotoShootEnd));
    ui->SelectedLightFieldNumberLE->setText(QString::number(m_signalctrl.SelectedLightFieldNumber));
    ui->FrameSignalOutputLE->setText(QString::number(m_signalctrl.FrameSignalOutput));

    //
    // 初始化全局变量
    //
    //
    // 初始化全局变量
    //
    PARAM.SystemName = m_signalctrl.systemName;
    PARAM.camDefineNum = m_signalctrl.CamareNumber;
    PARAM.Camera0Name = m_signalctrl.Camare0Name;
    PARAM.Camera1Name = m_signalctrl.Camare1Name;
    PARAM.Camera2Name = m_signalctrl.Camare2Name;
    PARAM.Camera3Name = m_signalctrl.Camare3Name;
    PARAM.serverIp = m_signalctrl.ServerIP;
    PARAM.serverPort = m_signalctrl.ServerPort;
    PARAM.YAccuracy = m_signalctrl.YAccuracy;
    PARAM.XCamera0Accuracy = m_signalctrl.XCamera0Accuracy;
    PARAM.XCamera1Accuracy = m_signalctrl.XCamera1Accuracy;
    PARAM.Camera0Frame = m_signalctrl.Camera0Frame;
    PARAM.Camera0PhotoRow = m_signalctrl.Camera0PhotoRow;
    PARAM.Camera0ExposureTime = m_signalctrl.Camera0ExposureTime;
    PARAM.Camera0Gain = m_signalctrl.Camera0Gain;
    PARAM.Camera1Frame = m_signalctrl.Camera1Frame;
    PARAM.Camera1PhotoRow = m_signalctrl.Camera1PhotoRow;
    PARAM.Camera1ExposureTime = m_signalctrl.Camera1ExposureTime;
    PARAM.Camera1Gain = m_signalctrl.Camera1Gain;
    PARAM.Camera2Frame = m_signalctrl.Camera2Frame;
    PARAM.Camera2PhotoRow = m_signalctrl.Camera2PhotoRow;
    PARAM.Camera2ExposureTime = m_signalctrl.Camera2ExposureTime;
    PARAM.Camera2Gain = m_signalctrl.Camera2Gain;
    PARAM.Camera3Frame = m_signalctrl.Camera3Frame;
    PARAM.Camera3PhotoRow = m_signalctrl.Camera3PhotoRow;
    PARAM.Camera3ExposureTime = m_signalctrl.Camera3ExposureTime;
    PARAM.Camera3Gain = m_signalctrl.Camera3Gain;
    PARAM.EncodePulseFilterUs = m_signalctrl.EncodePulseFilterUs;   // 编码器参数--编码脉冲滤波
    PARAM.PhotoelectricSensorFiltering = m_signalctrl.PhotoelectricSensorFiltering;// 编码器参数--光电传感器滤波
    PARAM.WheelEncoderPhotoPulse = m_signalctrl.WheelEncoderPhotoPulse;   //  编码器参数--压轮编码器产生拍照脉冲(四倍频)
    PARAM.EncoderMode = m_signalctrl.EncoderMode;              // 编码器参数--编码器模式(0辊道/1压轮)
    PARAM.SolenoidValve1DownDelay = m_signalctrl.SolenoidValve1DownDelay;  // 编码器参数--光电1触发电磁阀降下延时(ms)
    PARAM.SolenoidValve1UpDelay = m_signalctrl.SolenoidValve1UpDelay;    // 编码器参数--光电1离开电磁阀升起延时(ms)
    PARAM.SolenoidValve2DownDelay = m_signalctrl.SolenoidValve2DownDelay;  // 编码器参数--光电2触发电磁阀降下延时(ms)
    PARAM.SolenoidValve2UpDelay = m_signalctrl.SolenoidValve2UpDelay;// 编码器参数--光电2离开电磁阀升起延时(ms)
    PARAM.WheelAEncoder = m_signalctrl.WheelAEncoder;             // 编码器参数--压轮编码器A相计数
    PARAM.WheelBEncoder = m_signalctrl.WheelBEncoder;         // 编码器参数--压轮编码器B相计数
    PARAM.ErrorPhotoCount = m_signalctrl.ErrorPhotoCount;       // 编码器参数--查看错误拍照次数
    PARAM.LightField1GlowTime = m_signalctrl.LightField1GlowTime;   // 光源控制器参数--光场1发光时间10ns
    PARAM.LightField2GlowTime = m_signalctrl.LightField2GlowTime;   // 光源控制器参数--光场2发光时间10ns
    PARAM.LightField3GlowTime = m_signalctrl.LightField3GlowTime;   // 光源控制器参数--光场3发光时间10ns
    PARAM.LightField4GlowTime = m_signalctrl.LightField4GlowTime;    // 光源控制器参数--光场4发光时间10ns
    PARAM.LightSignalSynchronizationDelayRegister = m_signalctrl.LightSignalSynchronizationDelayRegister;// 光源控制器参数--光源信号同步信号延时寄存器
    PARAM.PhotoMode = m_signalctrl.PhotoMode;             // 光源控制器参数--拍照模式
    PARAM.LightCameraEnable = m_signalctrl.LightCameraEnable;     // 光源控制器参数--光源相机使能信号
    PARAM.WorkMode = m_signalctrl.WorkMode;              // 光源控制器参数--工作模式(0工作/1测试)
    PARAM.LightSourcePulseEndPointRegister = m_signalctrl.LightSourcePulseEndPointRegister;// 光源控制器参数--光源脉冲结束点寄存器
    PARAM.SyncPulsePeriodRegister = m_signalctrl.SyncPulsePeriodRegister; //光源控制器参数--同步脉冲周期寄存器
    PARAM.CameraFrameSignalTriggerDelay = m_signalctrl.CameraFrameSignalTriggerDelay;// 光源控制器参数--相机帧信号触发延时行数(行)
    PARAM.TimelapseAfterPhotoShootEnd = m_signalctrl.TimelapseAfterPhotoShootEnd;// 光源控制器参数--拍照结束延时行数(行)
    PARAM.SelectedLightFieldNumber = m_signalctrl.SelectedLightFieldNumber;// 光源控制器参数--选择光场的数量
    PARAM.FrameSignalOutput = m_signalctrl.FrameSignalOutput;// 光源控制器参数--帧信号输出
}

void LightControl::getFrameSignal()
{
    if (SocketObjectPtr == nullptr) {
        unsigned int FrameSignal;
        unsigned int CoderACount;
        unsigned int CoderBCount;
        unsigned int errorPhotoCount;
        SocketObjectPtr->GetRealTimeData(FrameSignal,CoderACount,CoderBCount,errorPhotoCount);
        PARAM.FrameSignalOutput = FrameSignal;
        PARAM.WheelAEncoder = CoderACount;
        PARAM.WheelBEncoder = CoderBCount;
        PARAM.ErrorPhotoCount = errorPhotoCount;
    }
}

