/********************************************************************************
 *  Puspose:
 *      MainForm.h 主界面开始加载声明文件
 *
 * Author:
 *      zhang shuanggui
 *
 * create time:
 *      2025/12/27
 *
 *******************************************************************************/

#ifndef MAINFORM_H
#define MAINFORM_H

/////////////////////////////////////////////////////////////////////////////////////
///  @brief 引用的头文件
///
#include <QVBoxLayout>
#include <QWidget>
#include <QTimer>
#include <QAction>
#include "mainwindow.h"


////////////////////////////////////////////////////////////////////////////////////
///  @brief MainForm类的声明
///
namespace Ui {
class MainForm;
}

/**
 * @brief The MainForm class
 */
class MainForm : public QWidget
{
    Q_OBJECT

public:
    /**
     * @brief MainForm 显示声明构造函数
     * @param parent 构造参数，默认为nullptr
     */
    explicit MainForm(QWidget* parent = nullptr);

    /**
     * @brief MainForm 析构函数
     */
    ~MainForm();

public slots:
    /**
     * @brief showWindows 登录成功加载的槽函数
     */
    void showWindows();

private:
    Ui::MainForm* ui;               /* ui对象 */
    MainWindow* main_window;        /* 成员对象 */
};

#endif // MAINFORM_H
