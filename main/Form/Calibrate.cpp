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
            qDebug() << "Failed to get function pointer. Error code: " << GetLastError() ;
            FreeLibrary(jsoncppDllHandle);
        } else {
            qDebug() << "Success to get  jsoncppDllHandle function pointer. ";
        }
        jsoncppPtr = createFunc();
    }
    //
    // 加载json文件内的数据，若没有则新建，若有则加载
    //
    Calibrate::InitCalibrateUI();
    connect(ui->saveBT,SIGNAL(clicked()),this,SLOT(SlotSaveClicked()));
    connect(ui->getBT,SIGNAL(clicked()),this,SLOT(SlotGetClicked()));
}

Calibrate::~Calibrate()
{
    delete ui;
}

void Calibrate::InitCalibrateUI()
{
    CalibrateJsonPath = QDir::currentPath() + QString("/Calibrate.json");
    qDebug()<<"CalibrateJsonPath ="<<CalibrateJsonPath;
    QFile inifile(CalibrateJsonPath);
    if (!inifile.exists()) {
        //写入默认json文件
        if (jsoncppPtr!=nullptr){
            jsoncppPtr->writeEmptyCalibrateToJson(CalibrateJsonPath);
            ui->camera1VPixLE->setText("0");
            ui->camera2VPixLE->setText("0");
            ui->camera3VPixLE->setText("0");
            ui->camera4VPixLE->setText("0");
            ui->camera12HPixLE->setText("0");
            ui->camera23HPixLE->setText("0");
            ui->camera34HPixLE->setText("0");
            return;
        } else {
            qDebug()<<"error: jsoncppPtr==nullptr";
        }
    } else {
        if (jsoncppPtr!=nullptr){
            CropArgPackage crop;
            jsoncppPtr->readCalibrateFromJson(CalibrateJsonPath,crop);
            if (crop.args.size()==4) {
                ui->camera1VPixLE->setText(QString::number(crop.args[0].topPixCrop));
                ui->camera2VPixLE->setText(QString::number(crop.args[1].topPixCrop));
                ui->camera3VPixLE->setText(QString::number(crop.args[2].topPixCrop));
                ui->camera4VPixLE->setText(QString::number(crop.args[3].topPixCrop));
                ui->camera12HPixLE->setText(QString::number(crop.args[0].rightPixCrop));
                ui->camera23HPixLE->setText(QString::number(crop.args[1].rightPixCrop));
                ui->camera34HPixLE->setText(QString::number(crop.args[2].rightPixCrop));
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
    arg0.topPixCrop = ui->camera1VPixLE->text().toInt();
    arg0.bottomPixCrop = 0;
    arg0.leftPixCrop = ui->camera12HPixLE->text().toInt();
    arg0.rightPixCrop = ui->camera12HPixLE->text().toInt();
    crop.args.push_back(arg0);
    CameraCropArg arg1;
    arg1.topPixCrop = ui->camera2VPixLE->text().toInt();
    arg1.bottomPixCrop = 0;
    arg1.leftPixCrop = ui->camera12HPixLE->text().toInt();
    arg1.rightPixCrop = ui->camera23HPixLE->text().toInt();
    crop.args.push_back(arg1);
    CameraCropArg arg2;
    arg2.topPixCrop = ui->camera3VPixLE->text().toInt();
    arg2.bottomPixCrop = 0;
    arg2.leftPixCrop = ui->camera23HPixLE->text().toInt();
    arg2.rightPixCrop = ui->camera34HPixLE->text().toInt();
    crop.args.push_back(arg2);
    CameraCropArg arg3;
    arg3.topPixCrop = ui->camera4VPixLE->text().toInt();
    arg3.bottomPixCrop = 0;
    arg3.leftPixCrop = ui->camera34HPixLE->text().toInt();
    arg3.rightPixCrop = 0;
    crop.args.push_back(arg3);

    if (jsoncppPtr!=nullptr) {
        jsoncppPtr->writeCalibrateToJson(CalibrateJsonPath,crop);
        PARAM.crops = crop;
        QString message = tr("Save Calibrate Json File success.");
        INFOMATION.criticalMessageBox(this,message);
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
            ui->camera1VPixLE->setText(QString::number(crop.args[0].topPixCrop));
            ui->camera2VPixLE->setText(QString::number(crop.args[1].topPixCrop));
            ui->camera3VPixLE->setText(QString::number(crop.args[2].topPixCrop));
            ui->camera4VPixLE->setText(QString::number(crop.args[3].topPixCrop));
            ui->camera12HPixLE->setText(QString::number(crop.args[0].rightPixCrop));
            ui->camera23HPixLE->setText(QString::number(crop.args[1].rightPixCrop));
            ui->camera34HPixLE->setText(QString::number(crop.args[2].rightPixCrop));
            PARAM.crops = crop;
            QString message = tr("Get Calibrate Json File success.");
            INFOMATION.criticalMessageBox(this,message);
            return;
        }
    } else {
        qDebug()<<"error: jsoncppPtr==nullptr";
        QString message = tr("Get Calibrate Json File fail.");
        INFOMATION.criticalMessageBox(this,message);
    }
}
