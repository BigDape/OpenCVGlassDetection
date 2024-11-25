#ifndef CALIBRATE_H
#define CALIBRATE_H

#include <QWidget>
#include "HSJsoncppInterface.h"

namespace Ui {
class Calibrate;
}

class Calibrate : public QWidget
{
    Q_OBJECT

public:
    explicit Calibrate(QWidget *parent = nullptr);
    ~Calibrate();

private:
    void InitCalibrateUI();
    bool CheckParam(CropArgPackage crop);

private slots:
    void SlotSaveClicked();
    void SlotGetClicked();
    void SlotAboutClicked();

private:
    Ui::Calibrate *ui;
    HSJsoncppNamespace::HSJsoncppInterface* jsoncppPtr = nullptr;
    HMODULE jsoncppDllHandle;
    QString CalibrateJsonPath; //标定json文件路径
};

#endif // CALIBRATE_H
