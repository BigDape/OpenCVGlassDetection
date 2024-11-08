#include "DushenCameraWidget.h"
#include "ui_DushenCameraWidget.h"
#include <QThread>
#include <Windows.h>
#include <QDebug>
#include "MyGraphicsitem.h"

DushenCameraWidget::DushenCameraWidget(QWidget* parent)
    : QWidget(parent)
    , ui(new Ui::DushenCameraWidget)
{
    ui->setupUi(this);
}

DushenCameraWidget::~DushenCameraWidget()
{
    //防止下次开启相机无法采集
    // if (CameraObject->IsScanned(RealCameraName)) {
    //     if (CameraObject->IsStarted(RealCameraName)) {
    //         CameraObject->StopFunc(RealCameraName);
    //         CameraObject->Closefunc(RealCameraName);
    //     } else if (CameraObject->IsOpened(RealCameraName)) {
    //         CameraObject->Closefunc(RealCameraName);
    //     }
    // }
    delete ui;
}

void DushenCameraWidget::InitDushenCameraWidget(CameraNameSpace::HSCameraInterface* cameraPtr, DushenCameraArgs args)
{
    ui->tabWidget->setCurrentIndex(0); // 选择第一页
    RealCameraName = args.camName;
    m_CameraNum = args.camNumber;
    CameraFieldNum = args.fieldnumberset; // 光场的总数
    //
    // 初始化相机操作对象
    //
    CameraObject = cameraPtr;
    CameraObject->InitCamera(args);
    CameraCounts = CameraObject->getCameraCounts();
    CameraName = CameraObject->getCameraFriendlyNames();
    //在下拉框中添加相机名称
    for (int i = 0; i < CameraCounts; i++) {
        if(i < (int)(CameraName.size() -1)) {
            ui->comboBox_Devices->addItem(CameraName[i]);
        } else {
            qDebug() <<"inner error!";
        }
    }
    //
    // 打开相机，按钮不能操作
    //
    ui->pushButton_Start->setEnabled(false);
    ui->pushButton_trigger->setEnabled(false);
    ui->pushButton_Property->setEnabled(false);
    ui->pushButton_Saveini->setEnabled(false);
    ui->pushButton_Loadini->setEnabled(false);
    ui->pushButton_Save->setEnabled(false);
    ui->comboBox_MultiFieldSelect->setEnabled(false);
    ui->pushButton_MultiFieldSelect->setEnabled(false);
    //
    // 设置中文名称
    //
    ui->tabWidget->setTabText(0, "显示");
    ui->tabWidget->setTabText(1, "设置");
    ui->cbx_SoftTrigger->setText("触发使能");
    ui->pushButton_trigger->setText("触发");
    ui->pushButton_Scan->setText("扫描");
    ui->pushButton_Property->setText("属性");
    ui->pushButton_Open->setText("打开");
    ui->pushButton_Start->setText("准备采集");
    ui->pushButton_Save->setText("保存");
    ui->pushButton_Loadini->setText("加载配置");
    ui->pushButton_Saveini->setText("保存配置");
    ui->pushButton_MultiFieldSelect->setText("选择");
    ui->lbl_multifield->setText("图片场选择并展示");
    //
    // 光场下拉框填充数据
    //
    for (int i = 0; i < CameraFieldNum; i++) {
        QString Text = QString::number(i);
        ui->comboBox_MultiFieldSelect->addItem(Text);
    }
    m_currentField = ui->comboBox_MultiFieldSelect->currentText().toInt();// 获取当前场的数量

    //todo:点击成功或者失败要有弹窗
    connect(ui->pushButton_Scan,SIGNAL(clicked()),this,SLOT(on_pushButton_Scan_clicked()));                         // 点击扫描按钮扫描连接上的相机
    connect(ui->cbx_SoftTrigger,SIGNAL(checkStateChanged(Qt::CheckState)),this,SLOT(on_combox_trigger_changed(Qt::CheckState)));           // 触发选择框
    connect(ui->pushButton_Open,SIGNAL(clicked()),this,SLOT(on_pushButton_Open_clicked()));                         // 打开按钮
    connect(ui->pushButton_Start, SIGNAL(clicked()), this, SLOT(slot_StartCamera()));                               // 开始按钮
    connect(ui->pushButton_Property, SIGNAL(clicked()), this, SLOT(on_pushButton_Property_clicked()));              // 属性窗口
    connect(ui->pushButton_Save, SIGNAL(clicked()), this, SLOT(on_pushButton_Save_clicked()));                      // 保存全部
    connect(ui->pushButton_Saveini, SIGNAL(clicked()), this, SLOT(on_pushButton_Saveini_clicked()));                // 保存ini文件
    connect(ui->pushButton_Loadini, SIGNAL(clicked()), this, SLOT(on_pushButton_Loadini_clicked()));                // 加载ini文件
    connect(ui->pushButton_MultiFieldSelect,SIGNAL(clicked()),this,SLOT(on_pushButton_MultiFieldSelect_clicked())); // 点击选择按钮选择光场
    //
    // 自动打开当前相机的
    //
    DushenCameraWidget::AutoOpen();
}

void DushenCameraWidget::AutoOpen()
{
    if (CameraObject->IsScanned(RealCameraName) && !CameraObject->IsOpened(RealCameraName)) {
        if (!CameraObject->SearchCamera(RealCameraName)) {
            RealCameraName = CameraObject->getCurrentCameraFriendlyName();
            qDebug() << "Default Camera Not matched , use The First Selection";
        }
        CameraNameSpace::HSCameraError result = CameraObject->OpenFunc(RealCameraName);
        if (result == CameraNameSpace::HSCameraError::SUCCESS) {
            ui->pushButton_Open->setText("关闭");
            ui->lbl_CameraName->setText(RealCameraName);
            ui->pushButton_Start->setEnabled(true);
            ui->pushButton_Property->setEnabled(true);
            ui->pushButton_Saveini->setEnabled(true);
            ui->pushButton_Loadini->setEnabled(true);
            ui->pushButton_Save->setEnabled(true);
            ui->comboBox_MultiFieldSelect->setEnabled(true);
            ui->pushButton_MultiFieldSelect->setEnabled(true);
            CameraObject->LoadIni(RealCameraName);//加载ini配置文件
            if (CameraObject->IsOpened(RealCameraName)) {
                ui->cbx_SoftTrigger->setChecked(true);
            }
            //todo:自动更新数据，包括界面上的图片和帧率
        }
    }
}

void DushenCameraWidget::on_pushButton_Scan_clicked()
{
    CameraObject->ScanFunc(RealCameraName);
    ui->comboBox_Devices->clear();
    CameraCounts = CameraObject->getCameraCounts();
    CameraName = CameraObject->getCameraFriendlyNames();
    //在下拉框中添加相机名称
    for (int i = 0; i < CameraCounts; i++) {
        if(i < (int)(CameraName.size() -1)) {
            ui->comboBox_Devices->addItem(CameraName[i]);
        } else {
            qDebug() <<"inner error!";
        }
    }
}

void DushenCameraWidget::on_pushButton_Open_clicked()
{
    if (!CameraObject->IsScanned(RealCameraName)) {
        qDebug() << "Not Scanned";
        return;
    }
    if (!CameraObject->IsOpened(RealCameraName)) {
        //todo:切换名称时，怎么处理
        CameraNameSpace::HSCameraError result = CameraObject->OpenFunc(RealCameraName);

        if (result == CameraNameSpace::HSCameraError::SUCCESS) {//ui->comboBox_Devices->currentText()
            loadedPixmapItem = new MyGraphicsItem();
            scene->addItem(loadedPixmapItem);

//            connect(CameraBase.get(), SIGNAL(sig_DeliverImage(QImage)), this, SLOT(slot_ShowImage(QImage)));
//            connect(CameraBase.get(), SIGNAL(sig_DeliverFrameRate(QString)), this, SLOT(slot_ShowFrameRate(QString)));

            ui->pushButton_Open->setText("关闭");
            ui->lbl_CameraName->setText(ui->comboBox_Devices->currentText());
            ui->pushButton_Start->setEnabled(true);
            ui->pushButton_Property->setEnabled(true);
            ui->pushButton_Saveini->setEnabled(true);
            ui->pushButton_Loadini->setEnabled(true);
            ui->pushButton_Save->setEnabled(true);
            ui->comboBox_MultiFieldSelect->setEnabled(true);
            ui->pushButton_MultiFieldSelect->setEnabled(true);
            CameraObject->LoadIni(RealCameraName);
        }
    } else {
        CameraObject->Closefunc(RealCameraName);
//        CameraBase->slot_Closefunc(ui->lbl_CameraName->text());
//        disconnect(CameraBase.get(), SIGNAL(sig_DeliverImage(QImage)), this, SLOT(slot_ShowImage(QImage)));
        scene->removeItem(loadedPixmapItem);
        delete loadedPixmapItem;

        ui->pushButton_Open->setText("打开");
        ui->pushButton_Start->setEnabled(false);
        ui->pushButton_Property->setEnabled(false);
        ui->pushButton_Saveini->setEnabled(false);
        ui->pushButton_Loadini->setEnabled(false);
        ui->pushButton_Save->setEnabled(true);
        ui->comboBox_MultiFieldSelect->setEnabled(false);
        ui->pushButton_MultiFieldSelect->setEnabled(false);
    }
}

void DushenCameraWidget::on_pushButton_Property_clicked()
{
    HWND id = (HWND)this->winId();
    CameraObject->ShowProperty(RealCameraName,id);
}

void DushenCameraWidget::slot_ShowImage(QImage image)
{
    scene = new QGraphicsScene();
    ui->graphicsView_Image->setScene(scene);
    loadedPixmapItem->loadImage(image);
    int nwidth = ui->graphicsView_Image->width(), nheight = ui->graphicsView_Image->height();
    loadedPixmapItem->setQGraphicsViewWH(nwidth, nheight);
    ui->graphicsView_Image->setSceneRect((QRectF(-(nwidth / 2), -(nheight / 2), nwidth, nheight)));
}

void DushenCameraWidget::slot_ShowFrameRate(QString FrameRate)
{
    ui->lbl_FrameInfo->setText(FrameRate);
}

void DushenCameraWidget::on_combox_trigger_changed(Qt::CheckState s)
{
    qDebug()<<"Qt::CheckState s="<<s;
    if (s == Qt::Checked) {
        CameraObject->setSoftTriggerFlag(true);
    } else {
        CameraObject->setSoftTriggerFlag(false);
    }
    CameraObject->TriggerFunc(RealCameraName);
}

void DushenCameraWidget::on_pushButton_Save_clicked()
{
    //todo:保存到json文件
}

void DushenCameraWidget::on_pushButton_Saveini_clicked()
{
    CameraNameSpace::HSCameraError result = CameraObject->SaveIni(RealCameraName);
    if (result == CameraNameSpace::HSCameraError::SUCCESS) {
        qDebug() << "Save Ini Success ";
    } else {
        qDebug() << "Save Ini Failed";
    }

}

void DushenCameraWidget::on_pushButton_MultiFieldSelect_clicked()
{ 
    if (!CameraObject->IsStarted(RealCameraName)) {
        CameraObject->setFieldSelectedView(ui->comboBox_MultiFieldSelect->currentText().toInt());
    }
}

void DushenCameraWidget::slot_StartCamera()
{
    QString BText = ui->pushButton_Start->text();
    if(BText == "开始") {
        DushenCameraWidget::StartCamera();
    } else if(BText == "停止") {
        DushenCameraWidget::StopCamera();
    } else {
        qDebug()<<BText;
    }


}

void DushenCameraWidget::on_pushButton_Loadini_clicked()
{
    CameraObject->LoadIni(RealCameraName);
}

void DushenCameraWidget::StartCamera()
{
    if (CameraObject->IsOpened(RealCameraName)) {
        CameraObject->setSoftTriggerFlag(ui->cbx_SoftTrigger->isChecked() ? true : false);
        if (!CameraObject->IsStarted(RealCameraName)) {
            CameraObject->StartFunc(RealCameraName);
            ui->pushButton_Start->setText("停止");
            ui->pushButton_Open->setEnabled(false);
            ui->cbx_SoftTrigger->setEnabled(false);
            if (ui->cbx_SoftTrigger->isChecked()) {
                ui->pushButton_trigger->setEnabled(true);
                ui->pushButton_trigger->setText("单次触发");
            } else {
                ui->pushButton_trigger->setText("连续触发");
            }
            ui->comboBox_MultiFieldSelect->setEnabled(false);
            ui->pushButton_MultiFieldSelect->setEnabled(false);
        } else {
           //log_singleton::Write_Log("相机未启动", Log_Level::Error);
        }
    } else {
           // log_singleton::Write_Log("相机未打开", Log_Level::Error);
    }
}

void DushenCameraWidget::StopCamera()
{
    if (CameraObject->IsOpened(RealCameraName)){
        CameraObject->setSoftTriggerFlag(ui->cbx_SoftTrigger->isChecked() ? true : false);
        if (CameraObject->IsStarted(RealCameraName)) {
            CameraObject->StopFunc(RealCameraName);
            ui->pushButton_Start->setText("开始");
            ui->pushButton_Open->setEnabled(true);
            ui->cbx_SoftTrigger->setEnabled(true);
            ui->pushButton_trigger->setEnabled(false);
            ui->comboBox_MultiFieldSelect->setEnabled(true);
            ui->pushButton_MultiFieldSelect->setEnabled(true);
        }
    }
}

