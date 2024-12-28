/********************************************************************************
 *  Puspose:
 *      Calibrate.h 标定界面头文件
 *
 * Author:
 *      zhang shuanggui
 *
 * create time:
 *      2025/11/25
 *
 *******************************************************************************/
#ifndef CALIBRATE_H
#define CALIBRATE_H

#include <QWidget>
#include <HSTool.h>

namespace Ui {
class Calibrate;
}

class Calibrate : public QWidget
{
    Q_OBJECT

public:
    /**
     * @brief Calibrate 显式构造函数
     * @param parent
     */
    explicit Calibrate(QWidget *parent = nullptr);

    /**
     * @brief Calibrate 析构函数
     */
    ~Calibrate();

private:
    /**
     * @brief InitCalibrateUI 初始化标定界面
     */
    void InitCalibrateUI();

    /**
     * @brief CheckParam 检查参数
     * @param crop 标定参数
     * @return true 参数合格 false 参数不合格
     */
    bool CheckParam(CropArgPackage crop);

private slots:
    /**
     * @brief SlotSaveClicked 点击保存按钮的槽函数
     */
    void SlotSaveClicked();

    /**
     * @brief SlotGetClicked 点击获取按钮的槽函数
     */
    void SlotGetClicked();

    /**
     * @brief SlotAboutClicked 点击关于获取按钮的槽函数
     */
    void SlotAboutClicked();

private:
    Ui::Calibrate *ui;
    QString CalibrateJsonPath; //标定json文件路径
};

#endif // CALIBRATE_H
