#ifndef HSLISTENER_H
#define HSLISTENER_H

#include <QMessageBox>
#include <QApplication>
#include <QListWidget>
#include <mutex>

#define INFOMATION HsListener::getInstance()

class HsListener
{
private:
    /**
     * @brief HsListener 显式构造函数
     */
    explicit HsListener();

    /**
     * @brief HsListener 显式构造函数
     */
    virtual ~HsListener();
public:
    /**
     * @brief getInstance 对外接口，可以显示获取到监听对象
     * @return
     */
    static HsListener& getInstance();

    /**
     * @brief criticalMessageBox 错误对话框
     * @param parent 当前界面指针
     * @param text 对话框内容
     */
    void criticalMessageBox(QWidget *parent,const QString& text);

    /**
     * @brief inputMessageBox 输入交互对话框
     * @param [in] parent 父窗口指针
     * @param [in] title 对话框的标题
     * @param [in] question 对话框种显示的信息
     * @param [in] defaultVal 对话框的默认输入值
     * @return 用户输入的字符串
     */
    QString inputMessageBox(QWidget *parent,QString title,QString question, QString defaultVal = "");

    /**
     * @brief informationMessageBox 提醒式对话框
     * @param [in] parent 父窗口指针
     * @param [in] title 对话框标题
     * @param [in] question 对话框内容
     */
    void informationMessageBox(QWidget *parent, QString title, QString question);

    /**
     * @brief outputMessage 日志输出接口
     * @param [in] out 日志对象组件
     * @param [in] message 一行日志输出的内容
     */
    void outputMessage(QListWidget* out,QString message);
private:
    std::mutex _mutex;
};




#endif // HSLISTENER_H
