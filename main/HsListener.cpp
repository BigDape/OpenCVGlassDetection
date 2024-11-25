#include "HsListener.h"
#include <QDebug>				// 调试函数 头文件
#include <QColorDialog> 		// 1.颜色对话框 头文件
#include <QFileDialog>			// 2.文件对话框 头文件
#include <QFontDialog>			// 3.字体对话框 头文件
#include <QInputDialog>			// 4.输入对话框 头文件
#include <QMessageBox>			// 5.消息色对话框 头文件
#include <QProgressDialog>		// 6.进度条对话框 头文件
#include <QErrorMessage>		// 7.错误信息对话框 头文件
#include <QString>
#include <QDateTime>

HsListener::HsListener(){}

HsListener::~HsListener(){}

HsListener& HsListener::getInstance()
{
    static HsListener listener;
    return listener;
}

void HsListener::criticalMessageBox(QWidget *parent,const QString& text)
{
    // 创建错误对话框
    QMessageBox::critical(parent, // 父窗口，这里使用nullptr表示没有父窗口
                           "错误", // 对话框标题
                           text, // 显示的文本
                           QMessageBox::Ok, // 按钮，这里是Ok按钮
                           QMessageBox::NoButton // 默认按钮设置为无
                          );
}

QString HsListener::inputMessageBox(QWidget *parent,
                                    QString title,
                                    QString question,
                                    QString defaultVal)
{
    //创建输入对话框
    bool ok = false;
    // 获取字符串
    QString string = QInputDialog::getText(parent,
                                           title,
                                           question,
                                           QLineEdit::Normal,
                                           defaultVal,
                                           &ok);
    if(ok)
         qDebug() << "string:" << string;
     return string;
}

void HsListener::informationMessageBox(QWidget *parent,
                                       QString title,
                                       QString question)
{
    // 提示对话框
    int ret2 = QMessageBox::information(parent, title, question, QMessageBox::Ok);
    qDebug() << ret2;

}

void HsListener::outputMessage(QListWidget* out,QString message)
{
    QString currentTime = QTime::currentTime().toString("hh:mm:ss");
    QString newMessage = " [" + currentTime + "] " + message;
    QListWidgetItem* item = new QListWidgetItem(newMessage);
    QFont font;
    font.setFamily("微软雅黑");
    font.setPointSize(12);
    item->setFont(font);
    _mutex.lock();
    int index = out->count();
    out->insertItem(index, item);
    _mutex.unlock();
    qDebug()<<"outputMessage:" << newMessage;
}


