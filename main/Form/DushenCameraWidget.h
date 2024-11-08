#ifndef DUSHENCAMERAWIDGET_H
#define DUSHENCAMERAWIDGET_H

#include <QWidget>
#include <QGraphicsScene>
#include "MyGraphicsitem.h"
#include "HSCameraInterface.h"

namespace Ui {
class DushenCameraWidget;
}


class DushenCameraWidget : public QWidget
{
    Q_OBJECT

public:
    /**
     * @brief DushenCameraWidget构造函数
     * @param parent父窗口指针
     * @param CameraName 相机名称
     * @param CameraNum 相机个数
     * @param args 相机参数
     */
    explicit DushenCameraWidget(QWidget* parent);
    virtual ~DushenCameraWidget();
    void InitDushenCameraWidget(CameraNameSpace::HSCameraInterface* cameraPtr, DushenCameraArgs args);
    void AutoOpen();
    void StartCamera();
    void StopCamera();

private slots:
    void on_pushButton_Scan_clicked(); //点击扫描
    void on_pushButton_Open_clicked();
    void on_pushButton_Property_clicked();
    void on_combox_trigger_changed(Qt::CheckState s);
    void on_pushButton_Save_clicked();
    void on_pushButton_Saveini_clicked();
    void on_pushButton_Loadini_clicked();
    void on_pushButton_MultiFieldSelect_clicked();
    void slot_StartCamera();
    void slot_ShowImage(QImage image);
    void slot_ShowFrameRate(QString FrameRate);

private:
    Ui::DushenCameraWidget* ui;
    CameraNameSpace::HSCameraInterface* CameraObject; // dll组件接口对象
    int CameraCounts = 0;                                             // 扫描到相机个数
    std::vector<QString> CameraName;                                  // 相机名字
    QString RealCameraName;                                           // 相机的真实名称
    int m_CameraNum;                                                  // 下发参数相机的个数
    MyGraphicsItem* loadedPixmapItem;
    QGraphicsScene* scene;
    int CameraFieldNum;                                               // 光场总数
    int m_currentField;                                               // 当前选中的场
signals:
    void sig_SaveCameraName(QString CameraNum, QString CameraName);
};

#endif // DUSHENCAMERAWIDGET_H
