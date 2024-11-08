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
    //缺陷检测
    ui->Camera12PixelDeviationLE->setValidator(lineInt);
    ui->Camera23PixelDeviationLE->setValidator(lineInt);
    ui->Camera24PixelDeviationLE->setValidator(lineInt);
    ui->SilkToRollerDistLE->setValidator(lineInt);
    ui->ScratchAreaThresholdLE->setValidator(lineInt);
    ui->BubbleStoneAreaThresholdLE->setValidator(lineInt);
    ui->DirtyAreaThresholdLE->setValidator(lineInt);
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
    ui->EncodeUnitToDistLE->setValidator(lineInt);
    ui->EncodePulseFilterUsLE->setValidator(lineInt);
    ui->EncodeRevolutionLE->setValidator(lineInt);
    ui->RollerPerimeterUmLE->setValidator(lineInt);
    ui->ExpectSinglePixelAccuracyLE->setValidator(lineInt);
    ui->RollerMaxSpeedToRowCountLE->setValidator(lineInt);
    ui->EveryRowToEncodeCountLE->setValidator(lineInt);
    //控制器参数
    ui->PixelAccuracyUmLE->setValidator(lineInt);
    ui->PhotoelectricSignalPulseFilterLE->setValidator(lineInt);
    ui->CamareTrigerPulseContinueTime10nsLE->setValidator(lineInt);
    ui->PhotoelectricToCamareDistLE->setValidator(lineInt);
    ui->CamareFrameTrigerDelayRowCountLE->setValidator(lineInt);
    ui->FrameSignalContinueTimeLE->setValidator(lineInt);
    ui->ModuleEnableSignalLE->setValidator(lineInt);
    ui->CamarePhotoRowCountLE->setValidator(lineInt);
    ui->InnerRowFrequencyLE->setValidator(lineInt);
    ui->PhotoModeLE->setValidator(lineInt);
    ui->PhotoEndDelayRowCountLE->setValidator(lineInt);
    //光源控制器参数
    ui->LightField1DelayTimeLE->setValidator(lineInt);
    ui->LightField1GlowTimeLE->setValidator(lineInt);
    ui->LightField2DelayTimeLE->setValidator(lineInt);
    ui->LightField2GlowTimeLE->setValidator(lineInt);
    ui->LightField3DelayTimeLE->setValidator(lineInt);
    ui->LightField3GlowTimeLE->setValidator(lineInt);
    ui->LightField4DelayTimeLE->setValidator(lineInt);
    ui->LightField4GlowTimeLE->setValidator(lineInt);
    ui->SelectedLightFieldNumberLE->setValidator(lineInt);
    ui->HorizontalDarkfieldSelectRegisterLE->setValidator(lineInt);
    ui->SignalSwitchLE->setValidator(lineInt);
    ui->RowSignalSelectedLE->setValidator(lineInt);
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
    //自定义参数
    ui->SaveOriginImageCB->setCurrentIndex(m_signalctrl.SaveOriginImage);
    ui->SaveEntireImageCB->setCurrentIndex(m_signalctrl.SaveEntireImage);
    ui->SaveFlawImageCB->setCurrentIndex(m_signalctrl.SaveFlawImage);
    ui->SaveCropImageCB->setCurrentIndex(m_signalctrl.SaveCropImage);
    ui->XYLengthEnableCB->setCurrentIndex(m_signalctrl.XYLengthEnable);
    ui->FlawDefectEnableCB->setCurrentIndex(m_signalctrl.FlawDefectEnable);
    //缺陷检测
    ui->Camera12PixelDeviationLE->setText(QString::number(m_signalctrl.Camera12PixelDeviation));
    ui->Camera23PixelDeviationLE->setText(QString::number(m_signalctrl.Camera23PixelDeviation));
    ui->Camera24PixelDeviationLE->setText(QString::number(m_signalctrl.Camera24PixelDeviation));
    ui->SilkToRollerDistLE->setText(QString::number(m_signalctrl.SilkToRollerDist));
    ui->ScratchAreaThresholdLE->setText(QString::number(m_signalctrl.ScratchAreaThreshold));
    ui->BubbleStoneAreaThresholdLE->setText(QString::number(m_signalctrl.BubbleStoneAreaThreshold));
    ui->DirtyAreaThresholdLE->setText(QString::number(m_signalctrl.DirtyAreaThreshold));
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
    ui->EncodeUnitToDistLE->setText(QString::number(m_signalctrl.temp0));
    ui->EncodePulseFilterUsLE->setText(QString::number(m_signalctrl.temp1));
    ui->EncodeRevolutionLE->setText(QString::number(m_signalctrl.temp9));
    ui->RollerPerimeterUmLE->setText(QString::number(m_signalctrl.temp10));
    ui->ExpectSinglePixelAccuracyLE->setText(QString::number(m_signalctrl.temp11));
    ui->RollerMaxSpeedToRowCountLE->setText(QString::number(m_signalctrl.temp12));
    ui->EveryRowToEncodeCountLE->setText(QString::number(m_signalctrl.temp13));
    //控制器参数
    ui->PixelAccuracyUmLE->setText(QString::number(m_signalctrl.temp14));
    ui->PhotoelectricSignalPulseFilterLE->setText(QString::number(m_signalctrl.temp15));
    ui->CamareTrigerPulseContinueTime10nsLE->setText(QString::number(m_signalctrl.temp16));
    ui->PhotoelectricToCamareDistLE->setText(QString::number(m_signalctrl.temp17));
    ui->CamareFrameTrigerDelayRowCountLE->setText( QString::number(m_signalctrl.temp18));
    ui->FrameSignalContinueTimeLE->setText(QString::number(m_signalctrl.temp19));
    ui->ModuleEnableSignalLE->setText(QString::number(m_signalctrl.temp20));
    ui->CamarePhotoRowCountLE->setText(QString::number(m_signalctrl.temp21));
    ui->InnerRowFrequencyLE->setText(QString::number(m_signalctrl.temp22));
    ui->PhotoModeLE->setText(QString::number(m_signalctrl.tempAutoPhoto));
    ui->PhotoEndDelayRowCountLE->setText(QString::number(m_signalctrl.tempPhotoEndDelayLine));
    //光源控制器参数
    ui->LightField1DelayTimeLE->setText(QString::number(m_signalctrl.temp23));
    ui->LightField1GlowTimeLE->setText(QString::number(m_signalctrl.temp24));
    ui->LightField2DelayTimeLE->setText(QString::number(m_signalctrl.temp25));
    ui->LightField2GlowTimeLE->setText(QString::number(m_signalctrl.temp26));
    ui->LightField3DelayTimeLE->setText(QString::number(m_signalctrl.temp27));
    ui->LightField3GlowTimeLE->setText(QString::number(m_signalctrl.temp28));
    ui->LightField4DelayTimeLE->setText(QString::number(m_signalctrl.temp29));
    ui->LightField4GlowTimeLE->setText(QString::number(m_signalctrl.temp30));
    ui->SelectedLightFieldNumberLE->setText(QString::number(m_signalctrl.temp55));
    ui->HorizontalDarkfieldSelectRegisterLE->setText(QString::number(m_signalctrl.temp56));
    ui->CamareAndLightFieldControlCB->setCurrentIndex(m_signalctrl.temp35);
    ui->SignalSwitchLE->setText(QString::number(m_signalctrl.temp36));
    ui->RowSignalSelectedLE->setText(QString::number(m_signalctrl.temp37));

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
    PARAM.isSaveOriginImage = m_signalctrl.SaveOriginImage;
    PARAM.isSaveEntireImage = m_signalctrl.SaveEntireImage;
    PARAM.isSaveFlawImage = m_signalctrl.SaveFlawImage;
    PARAM.isSaveCropImage = m_signalctrl.SaveCropImage;
    PARAM.XYLengthEnable = m_signalctrl.XYLengthEnable;
    PARAM.FlawDefectEnable = m_signalctrl.FlawDefectEnable;
    PARAM.Camera12PixelDeviation = m_signalctrl.Camera12PixelDeviation;
    PARAM.Camera23PixelDeviation = m_signalctrl.Camera23PixelDeviation;
    PARAM.Camera24PixelDeviation = m_signalctrl.Camera24PixelDeviation;
    PARAM.SilkToRollerDist = m_signalctrl.SilkToRollerDist;
    PARAM.ScratchAreaThreshold = m_signalctrl.ScratchAreaThreshold;
    PARAM.BubbleStoneAreaThreshold = m_signalctrl.BubbleStoneAreaThreshold;
    PARAM.DirtyAreaThreshold = m_signalctrl.DirtyAreaThreshold;
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
    PARAM.EncodeUnitToDist = m_signalctrl.temp0;               // 编码器单位刻度对应距离
    PARAM.EncodePulseFilterUs = m_signalctrl.temp1;            // 编码脉冲滤
    PARAM.EncodeRevolution = m_signalctrl.temp9;                //编码器转数
    PARAM.RollerPerimeterUm = m_signalctrl.temp10;               //辊道周长
    PARAM.ExpectSinglePixelAccuracy = m_signalctrl.temp11;       //期望单个像素精度
    PARAM.RollerMaxSpeedToRowCount = m_signalctrl.temp12;        //辊道最大速度对应行频
    PARAM.EveryRowToEncodeCount = m_signalctrl.temp13;           //每行对应的编码计数
    PARAM.PixelAccuracyUm = m_signalctrl.temp14;                    //像素精度um
    PARAM.PhotoelectricSignalPulseFilter = m_signalctrl.temp15;     //光电信号脉冲滤波
    PARAM.CamareTrigerPulseContinueTime10ns = m_signalctrl.temp16;  //相机触发脉冲持续时间10ns
    PARAM.PhotoelectricToCamareDist = m_signalctrl.temp17;          //光电与相机距离行
    PARAM.CamareFrameTrigerDelayRowCount = m_signalctrl.temp18;     // 相机帧触发延时行数
    PARAM.FrameSignalContinueTime = m_signalctrl.temp19;            //帧信号持续时间
    PARAM.ModuleEnableSignal = m_signalctrl.temp20;                 //模块使能信号
    PARAM.CamarePhotoRowCount = m_signalctrl.temp21;                //相机拍照行数
    PARAM.InnerRowFrequency = m_signalctrl.temp22;                  //内部行频
    PARAM.PhotoMode = m_signalctrl.tempAutoPhoto;                          //拍照模式
    PARAM.PhotoEndDelayRowCount = m_signalctrl.tempPhotoEndDelayLine;              //拍照延时行数
    PARAM.LightField1DelayTime = m_signalctrl.temp23;            //光场1延时时间10ns
    PARAM.LightField1GlowTime = m_signalctrl.temp24;             //光场1发光时间10ns
    PARAM.LightField2DelayTime = m_signalctrl.temp25;            //光场2延时时间10ns
    PARAM.LightField2GlowTime = m_signalctrl.temp26;             //光场2发光时间10ns
    PARAM.LightField3DelayTime = m_signalctrl.temp27;            //光场3延时时间10ns
    PARAM.LightField3GlowTime= m_signalctrl.temp28;             //光场3发光时间10ns
    PARAM.LightField4DelayTime= m_signalctrl.temp29;            //光场4延时时间10ns
    PARAM.LightField4GlowTime= m_signalctrl.temp30;             //光场4发光时间10ns
    PARAM.SelectedLightFieldNumber = m_signalctrl.temp55;        //选择光场数量
    PARAM.HorizontalDarkfieldSelectRegister = m_signalctrl.temp56;  //横向暗场选择寄存器
    PARAM.CamareAndLightFieldControl = m_signalctrl.temp35;         //相机与光场控制
    PARAM.SignalSwitch = m_signalctrl.temp36;                       //信号切换
    PARAM.RowSignalSelected = m_signalctrl.temp37;                  //行信号源选择
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
        qDebug()<<"every row line = " << m_signalctrl.temp13;
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
    //自定义参数
    m_signalctrl.SaveOriginImage = ui->SaveOriginImageCB->currentIndex();
    m_signalctrl.SaveEntireImage = ui->SaveEntireImageCB->currentIndex();
    m_signalctrl.SaveFlawImage = ui->SaveFlawImageCB->currentIndex();
    m_signalctrl.SaveCropImage = ui->SaveCropImageCB->currentIndex();
    m_signalctrl.XYLengthEnable = ui->XYLengthEnableCB->currentIndex();
    m_signalctrl.FlawDefectEnable = ui->FlawDefectEnableCB->currentIndex();
    //缺陷检测
    m_signalctrl.Camera12PixelDeviation = ui->Camera12PixelDeviationLE->text().toInt();
    m_signalctrl.Camera23PixelDeviation = ui->Camera23PixelDeviationLE->text().toInt();
    m_signalctrl.Camera24PixelDeviation = ui->Camera24PixelDeviationLE->text().toInt();
    m_signalctrl.SilkToRollerDist = ui->SilkToRollerDistLE->text().toInt();
    m_signalctrl.ScratchAreaThreshold = ui->ScratchAreaThresholdLE->text().toInt();
    m_signalctrl.BubbleStoneAreaThreshold = ui->BubbleStoneAreaThresholdLE->text().toInt();
    m_signalctrl.DirtyAreaThreshold = ui->DirtyAreaThresholdLE->text().toInt();
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
    m_signalctrl.temp0 = ui->EncodeUnitToDistLE->text().toInt();
    m_signalctrl.temp1 = ui->EncodePulseFilterUsLE->text().toInt();
    m_signalctrl.temp9 = ui->EncodeRevolutionLE->text().toInt();
    m_signalctrl.temp10 = ui->RollerPerimeterUmLE->text().toInt();
    m_signalctrl.temp11 = ui->ExpectSinglePixelAccuracyLE->text().toInt();
    m_signalctrl.temp12 = ui->RollerMaxSpeedToRowCountLE->text().toInt();
    m_signalctrl.temp13 = ui->EveryRowToEncodeCountLE->text().toInt();
    //控制器参数
    m_signalctrl.temp14 = ui->PixelAccuracyUmLE->text().toInt();
    m_signalctrl.temp15 = ui->PhotoelectricSignalPulseFilterLE->text().toInt();
    m_signalctrl.temp16 = ui->CamareTrigerPulseContinueTime10nsLE->text().toInt();
    m_signalctrl.temp17 = ui->PhotoelectricToCamareDistLE->text().toInt();
    m_signalctrl.temp18 = ui->CamareFrameTrigerDelayRowCountLE->text().toInt();
    m_signalctrl.temp19 = ui->FrameSignalContinueTimeLE->text().toInt();
    m_signalctrl.temp20 = ui->ModuleEnableSignalLE->text().toInt();
    m_signalctrl.temp21 = ui->CamarePhotoRowCountLE->text().toInt();
    m_signalctrl.temp22 = ui->InnerRowFrequencyLE->text().toInt();
    m_signalctrl.tempAutoPhoto = ui->PhotoModeLE->text().toInt();
    m_signalctrl.tempPhotoEndDelayLine = ui->PhotoEndDelayRowCountLE->text().toInt();
    //光源控制器参数
    m_signalctrl.temp23 = ui->LightField1DelayTimeLE->text().toInt();
    m_signalctrl.temp24 = ui->LightField1GlowTimeLE->text().toInt();
    m_signalctrl.temp25 = ui->LightField2DelayTimeLE->text().toInt();
    m_signalctrl.temp26 = ui->LightField2GlowTimeLE->text().toInt();
    m_signalctrl.temp27 = ui->LightField3DelayTimeLE->text().toInt();
    m_signalctrl.temp28 = ui->LightField3GlowTimeLE->text().toInt();
    m_signalctrl.temp29 = ui->LightField4DelayTimeLE->text().toInt();
    m_signalctrl.temp30 = ui->LightField4GlowTimeLE->text().toInt();
    m_signalctrl.temp55 = ui->SelectedLightFieldNumberLE->text().toInt();
    m_signalctrl.temp56 = ui->HorizontalDarkfieldSelectRegisterLE->text().toInt();
    m_signalctrl.temp35 = ui->CamareAndLightFieldControlCB->currentIndex();
    m_signalctrl.temp36 = ui->SignalSwitchLE->text().toInt();
    m_signalctrl.temp37 = ui->RowSignalSelectedLE->text().toInt();
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
    //自定义参数
    ui->SaveOriginImageCB->setCurrentIndex(m_signalctrl.SaveOriginImage);
    ui->SaveEntireImageCB->setCurrentIndex(m_signalctrl.SaveEntireImage);
    ui->SaveFlawImageCB->setCurrentIndex(m_signalctrl.SaveFlawImage);
    ui->SaveCropImageCB->setCurrentIndex(m_signalctrl.SaveCropImage);
    ui->XYLengthEnableCB->setCurrentIndex(m_signalctrl.XYLengthEnable);
    ui->FlawDefectEnableCB->setCurrentIndex(m_signalctrl.FlawDefectEnable);
    //缺陷检测
    ui->Camera12PixelDeviationLE->setText(QString::number(m_signalctrl.Camera12PixelDeviation));
    ui->Camera23PixelDeviationLE->setText(QString::number(m_signalctrl.Camera23PixelDeviation));
    ui->Camera24PixelDeviationLE->setText(QString::number(m_signalctrl.Camera24PixelDeviation));
    ui->SilkToRollerDistLE->setText(QString::number(m_signalctrl.SilkToRollerDist));
    ui->ScratchAreaThresholdLE->setText(QString::number(m_signalctrl.ScratchAreaThreshold));
    ui->BubbleStoneAreaThresholdLE->setText(QString::number(m_signalctrl.BubbleStoneAreaThreshold));
    ui->DirtyAreaThresholdLE->setText(QString::number(m_signalctrl.DirtyAreaThreshold));
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
    ui->EncodeUnitToDistLE->setText(QString::number(m_signalctrl.temp0));
    ui->EncodePulseFilterUsLE->setText(QString::number(m_signalctrl.temp1));
    ui->EncodeRevolutionLE->setText(QString::number(m_signalctrl.temp9));
    ui->RollerPerimeterUmLE->setText(QString::number(m_signalctrl.temp10));
    ui->ExpectSinglePixelAccuracyLE->setText(QString::number(m_signalctrl.temp11));
    ui->RollerMaxSpeedToRowCountLE->setText(QString::number(m_signalctrl.temp12));
    ui->EveryRowToEncodeCountLE->setText(QString::number(m_signalctrl.temp13));
    //控制器参数
    ui->PixelAccuracyUmLE->setText(QString::number(m_signalctrl.temp14));
    ui->PhotoelectricSignalPulseFilterLE->setText(QString::number(m_signalctrl.temp15));
    ui->CamareTrigerPulseContinueTime10nsLE->setText(QString::number(m_signalctrl.temp16));
    ui->PhotoelectricToCamareDistLE->setText(QString::number(m_signalctrl.temp17));
    ui->CamareFrameTrigerDelayRowCountLE->setText( QString::number(m_signalctrl.temp18));
    ui->FrameSignalContinueTimeLE->setText(QString::number(m_signalctrl.temp19));
    ui->ModuleEnableSignalLE->setText(QString::number(m_signalctrl.temp20));
    ui->CamarePhotoRowCountLE->setText(QString::number(m_signalctrl.temp21));
    ui->InnerRowFrequencyLE->setText(QString::number(m_signalctrl.temp22));
    ui->PhotoModeLE->setText(QString::number(m_signalctrl.tempAutoPhoto));
    ui->PhotoEndDelayRowCountLE->setText(QString::number(m_signalctrl.tempPhotoEndDelayLine));
    //光源控制器参数
    ui->LightField1DelayTimeLE->setText(QString::number(m_signalctrl.temp23));
    ui->LightField1GlowTimeLE->setText(QString::number(m_signalctrl.temp24));
    ui->LightField2DelayTimeLE->setText(QString::number(m_signalctrl.temp25));
    ui->LightField2GlowTimeLE->setText(QString::number(m_signalctrl.temp26));
    ui->LightField3DelayTimeLE->setText(QString::number(m_signalctrl.temp27));
    ui->LightField3GlowTimeLE->setText(QString::number(m_signalctrl.temp28));
    ui->LightField4DelayTimeLE->setText(QString::number(m_signalctrl.temp29));
    ui->LightField4GlowTimeLE->setText(QString::number(m_signalctrl.temp30));
    ui->SelectedLightFieldNumberLE->setText(QString::number(m_signalctrl.temp55));
    ui->HorizontalDarkfieldSelectRegisterLE->setText(QString::number(m_signalctrl.temp56));
    ui->CamareAndLightFieldControlCB->setCurrentIndex(m_signalctrl.temp35);
    ui->SignalSwitchLE->setText(QString::number(m_signalctrl.temp36));
    ui->RowSignalSelectedLE->setText(QString::number(m_signalctrl.temp37));

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
    PARAM.isSaveOriginImage = m_signalctrl.SaveOriginImage;
    PARAM.isSaveEntireImage = m_signalctrl.SaveEntireImage;
    PARAM.isSaveFlawImage = m_signalctrl.SaveFlawImage;
    PARAM.isSaveCropImage = m_signalctrl.SaveCropImage;
    PARAM.XYLengthEnable = m_signalctrl.XYLengthEnable;
    PARAM.FlawDefectEnable = m_signalctrl.FlawDefectEnable;
    PARAM.Camera12PixelDeviation = m_signalctrl.Camera12PixelDeviation;
    PARAM.Camera23PixelDeviation = m_signalctrl.Camera23PixelDeviation;
    PARAM.Camera24PixelDeviation = m_signalctrl.Camera24PixelDeviation;
    PARAM.SilkToRollerDist = m_signalctrl.SilkToRollerDist;
    PARAM.ScratchAreaThreshold = m_signalctrl.ScratchAreaThreshold;
    PARAM.BubbleStoneAreaThreshold = m_signalctrl.BubbleStoneAreaThreshold;
    PARAM.DirtyAreaThreshold = m_signalctrl.DirtyAreaThreshold;
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
    PARAM.EncodeUnitToDist = m_signalctrl.temp0;               // 编码器单位刻度对应距离
    PARAM.EncodePulseFilterUs = m_signalctrl.temp1;            // 编码脉冲滤
    PARAM.EncodeRevolution = m_signalctrl.temp9;                //编码器转数
    PARAM.RollerPerimeterUm = m_signalctrl.temp10;               //辊道周长
    PARAM.ExpectSinglePixelAccuracy = m_signalctrl.temp11;       //期望单个像素精度
    PARAM.RollerMaxSpeedToRowCount = m_signalctrl.temp12;        //辊道最大速度对应行频
    PARAM.EveryRowToEncodeCount = m_signalctrl.temp13;           //每行对应的编码计数
    PARAM.PixelAccuracyUm = m_signalctrl.temp14;                    //像素精度um
    PARAM.PhotoelectricSignalPulseFilter = m_signalctrl.temp15;     //光电信号脉冲滤波
    PARAM.CamareTrigerPulseContinueTime10ns = m_signalctrl.temp16;  //相机触发脉冲持续时间10ns
    PARAM.PhotoelectricToCamareDist = m_signalctrl.temp17;          //光电与相机距离行
    PARAM.CamareFrameTrigerDelayRowCount = m_signalctrl.temp18;     // 相机帧触发延时行数
    PARAM.FrameSignalContinueTime = m_signalctrl.temp19;            //帧信号持续时间
    PARAM.ModuleEnableSignal = m_signalctrl.temp20;                 //模块使能信号
    PARAM.CamarePhotoRowCount = m_signalctrl.temp21;                //相机拍照行数
    PARAM.InnerRowFrequency = m_signalctrl.temp22;                  //内部行频
    PARAM.PhotoMode = m_signalctrl.tempAutoPhoto;                          //拍照模式
    PARAM.PhotoEndDelayRowCount = m_signalctrl.tempPhotoEndDelayLine;              //拍照延时行数
    PARAM.LightField1DelayTime = m_signalctrl.temp23;            //光场1延时时间10ns
    PARAM.LightField1GlowTime = m_signalctrl.temp24;             //光场1发光时间10ns
    PARAM.LightField2DelayTime = m_signalctrl.temp25;            //光场2延时时间10ns
    PARAM.LightField2GlowTime = m_signalctrl.temp26;             //光场2发光时间10ns
    PARAM.LightField3DelayTime = m_signalctrl.temp27;            //光场3延时时间10ns
    PARAM.LightField3GlowTime= m_signalctrl.temp28;             //光场3发光时间10ns
    PARAM.LightField4DelayTime= m_signalctrl.temp29;            //光场4延时时间10ns
    PARAM.LightField4GlowTime= m_signalctrl.temp30;             //光场4发光时间10ns
    PARAM.SelectedLightFieldNumber = m_signalctrl.temp55;        //选择光场数量
    PARAM.HorizontalDarkfieldSelectRegister = m_signalctrl.temp56;  //横向暗场选择寄存器
    PARAM.CamareAndLightFieldControl = m_signalctrl.temp35;         //相机与光场控制
    PARAM.SignalSwitch = m_signalctrl.temp36;                       //信号切换
    PARAM.RowSignalSelected = m_signalctrl.temp37;                  //行信号源选择
}

void LightControl::getFrameSignal()
{
    if (SocketObjectPtr == nullptr) {
        unsigned int FrameSignal;
        unsigned int AlmLightSignal;
        SocketObjectPtr->GetRealTimeData(FrameSignal,AlmLightSignal);
        PARAM.FrameSignal = FrameSignal;
    }
}

