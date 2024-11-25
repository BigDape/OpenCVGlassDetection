#include "Calibrate.h"
#include "ui_Calibrate.h"
#include <windows.h>
#include <QDir>
#include "../HsListener.h"
#include "../Global.h"

typedef HSJsoncppNamespace::HSJsoncppInterface* (*createJsoncppObjectFunc2)();

Calibrate::Calibrate(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Calibrate)
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
        createJsoncppObjectFunc2 createFunc = (createJsoncppObjectFunc2)GetProcAddress(jsoncppDllHandle, "createJsoncppObject");
        if (!createFunc) {
            qDebug() << "Calibrate: Failed to get function pointer. Error code: " << GetLastError() ;
            FreeLibrary(jsoncppDllHandle);
        } else {
            qDebug() << "Calibrate :Success to get  jsoncppDllHandle function pointer. ";
        }
        jsoncppPtr = createFunc();
    }
    //
    // 加载json文件内的数据，若没有则新建，若有则加载
    //
    Calibrate::InitCalibrateUI();
    connect(ui->saveBT,SIGNAL(clicked()),this,SLOT(SlotSaveClicked()));
    connect(ui->getBT,SIGNAL(clicked()),this,SLOT(SlotGetClicked()));
    connect(ui->aboutBT,SIGNAL(clicked()), this, SLOT(SlotAboutClicked()));
}

Calibrate::~Calibrate()
{
    delete ui;
}

void Calibrate::InitCalibrateUI()
{
    CalibrateJsonPath = QDir::currentPath() + QString("/Calibrate.json");
    qDebug()<<"CalibrateJsonPath = "<<CalibrateJsonPath;
    QFile inifile(CalibrateJsonPath);
    if (!inifile.exists()) {
        //写入默认json文件
        if (jsoncppPtr != nullptr ){
            jsoncppPtr->writeEmptyCalibrateToJson(CalibrateJsonPath);
            ui->camera0topPixLE->setText("0");
            ui->camera0bottomPixLE->setText("0");
            ui->camera0leftPixLE->setText("0");
            ui->camera0rightPixLE->setText("0");
            ui->camera1topPixLE->setText("0");
            ui->camera1bottomPixLE->setText("0");
            ui->camera1leftPixLE->setText("0");
            ui->camera1rightPixLE->setText("0");
            CropArgPackage crop;
            crop.cameracount = 2;
            CameraCropArg arg0,arg1,arg2,arg3;
            crop.args.push_back(arg0);
            crop.args.push_back(arg1);
            crop.args.push_back(arg2);
            crop.args.push_back(arg3);
            PARAM.crops = crop;
        } else {
            qDebug()<<"error: jsoncppPtr==nullptr";
        }
    } else {
        if (jsoncppPtr!=nullptr){
            CropArgPackage crop;
            crop.cameracount = 2;
            jsoncppPtr->readCalibrateFromJson(CalibrateJsonPath,crop);
            if (crop.args.size()==4) {
                ui->camera0topPixLE->setText(QString::number(crop.args[0].topPixCrop));
                ui->camera0bottomPixLE->setText(QString::number(crop.args[0].bottomPixCrop));
                ui->camera0leftPixLE->setText(QString::number(crop.args[0].leftPixCrop));
                ui->camera0rightPixLE->setText(QString::number(crop.args[0].rightPixCrop));
                ui->camera1topPixLE->setText(QString::number(crop.args[1].topPixCrop));
                ui->camera1bottomPixLE->setText(QString::number(crop.args[1].bottomPixCrop));
                ui->camera1leftPixLE->setText(QString::number(crop.args[1].leftPixCrop));
                ui->camera1rightPixLE->setText(QString::number(crop.args[1].rightPixCrop));
                PARAM.crops = crop;
                return;
            }
        } else {
            qDebug()<<"error: jsoncppPtr==nullptr";
        }
    }
    // QString message = tr("Not find in RecipeCB Items, now create new file. ");
    // INFOMATION.criticalMessageBox(this,message);
}

void Calibrate::SlotSaveClicked()
{
    CropArgPackage crop;
    CameraCropArg arg0;
    arg0.topPixCrop = ui->camera0topPixLE->text().toInt();
    arg0.bottomPixCrop = ui->camera0bottomPixLE->text().toInt();
    arg0.leftPixCrop = ui->camera0leftPixLE->text().toInt();
    arg0.rightPixCrop = ui->camera0rightPixLE->text().toInt();
    crop.args.push_back(arg0);
    CameraCropArg arg1;
    arg1.topPixCrop = ui->camera1topPixLE->text().toInt();
    arg1.bottomPixCrop = ui->camera1bottomPixLE->text().toInt();
    arg1.leftPixCrop = ui->camera1leftPixLE->text().toInt();
    arg1.rightPixCrop = ui->camera1rightPixLE->text().toInt();
    crop.args.push_back(arg1);
    CameraCropArg arg2;
    crop.args.push_back(arg2);
    CameraCropArg arg3;
    crop.args.push_back(arg3);
    if ( !Calibrate::CheckParam(crop)) {
        QString message = tr("Check Param is error, Save Calibrate Json File fail.");
        INFOMATION.criticalMessageBox(this,message);
        return;
    }
    if (jsoncppPtr!=nullptr) {
        jsoncppPtr->writeCalibrateToJson(CalibrateJsonPath,crop);
        PARAM.crops = crop;
        QString message = tr("Save Calibrate Json File success.");
        INFOMATION.informationMessageBox(this,"",message);
        return;
    }
    QString message = tr("Save Calibrate Json File fail.");
    INFOMATION.criticalMessageBox(this,message);
    return;
}

void Calibrate::SlotGetClicked()
{
    if (jsoncppPtr!=nullptr){
        CropArgPackage crop;
        jsoncppPtr->readCalibrateFromJson(CalibrateJsonPath,crop);
        if (crop.args.size()==4) {
            ui->camera0topPixLE->setText(QString::number(crop.args[0].topPixCrop));
            ui->camera0bottomPixLE->setText(QString::number(crop.args[0].bottomPixCrop));
            ui->camera0leftPixLE->setText(QString::number(crop.args[0].leftPixCrop));
            ui->camera0rightPixLE->setText(QString::number(crop.args[0].rightPixCrop));
            ui->camera1topPixLE->setText(QString::number(crop.args[1].topPixCrop));
            ui->camera1bottomPixLE->setText(QString::number(crop.args[1].bottomPixCrop));
            ui->camera1leftPixLE->setText(QString::number(crop.args[1].leftPixCrop));
            ui->camera1rightPixLE->setText(QString::number(crop.args[1].rightPixCrop));
            PARAM.crops = crop;
            QString message = tr("Get Calibrate Json File success.");
            INFOMATION.informationMessageBox(this,"获取",message);
            return;
        }
    } else {
        qDebug()<<"error: jsoncppPtr==nullptr";
        QString message = tr("Get Calibrate Json File fail.");
        INFOMATION.criticalMessageBox(this,message);
    }
}

void Calibrate::SlotAboutClicked()
{
    QString message = "标定每个相机的每一帧图像从上下左右裁剪的像素，要求裁剪的图像高度不能小于200像素。";
    INFOMATION.informationMessageBox(this,"关于",message);
}

bool Calibrate::CheckParam(CropArgPackage crop)
{

    if ( crop.args[0].topPixCrop + crop.args[0].bottomPixCrop > 200) {
        return false;
    }
    if (crop.args[1].topPixCrop + crop.args[1].bottomPixCrop > 200) {
        return false;
    }
    if (crop.args[0].topPixCrop + crop.args[0].bottomPixCrop != crop.args[1].topPixCrop + crop.args[1].bottomPixCrop) {
        return false;
    }
    if (crop.args[0].topPixCrop < 0 || crop.args[0].bottomPixCrop < 0 || crop.args[0].leftPixCrop < 0 || crop.args[0].rightPixCrop < 0) {
        return false;
    }
    if (crop.args[1].topPixCrop < 0 || crop.args[1].bottomPixCrop < 0 || crop.args[1].leftPixCrop < 0 || crop.args[1].rightPixCrop < 0) {
        return false;
    }
    if (crop.args[0].leftPixCrop > 8196 || crop.args[0].rightPixCrop > 8196) {
        return false;
    }
    if (crop.args[1].leftPixCrop > 8196 || crop.args[1].rightPixCrop > 8196) {
        return false;
    }
    return true;
}




