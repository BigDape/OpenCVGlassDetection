#ifndef HSLISTENER_H
#define HSLISTENER_H

#include <iostream>
#include <QMessageBox>
#include <QApplication>
#include <QListWidget>

#define INFOMATION HsListener::getInstance()

class HsListener
{
private: //构造和析构函数私有，防止外部声明
    explicit HsListener();
    virtual ~HsListener();
public:

    static HsListener& getInstance();
    /**
     * @brief criticalMessageBox 错误对话框
     * @param parent 当前界面指针
     * @param text 对话框内容
     */
    void criticalMessageBox(QWidget *parent,const QString& text);

    QString inputMessageBox(QWidget *parent,QString title,QString question, QString defaultVal = "");

    void informationMessageBox(QWidget *parent, QString title, QString question);

    void outputMessage(QListWidget* out,QString message);
};




#endif // HSLISTENER_H
