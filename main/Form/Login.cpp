#include "Login.h"
#include "ui_Login.h"
#include <QMessageBox>
#include "../MainForm.h"
#include "../mainwindow.h"

Login::Login(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Login)
{
    ui->setupUi(this);
    // 设置背景图片
//    QPalette pal = this->palette();
//    pal.setBrush(QPalette::Background,QBrush(QPixmap(":/toolbar/icons/login2.png").scaled(this->size())));
//    setPalette(pal);
    // 设置窗口标题
    this->setWindowTitle(tr("login"));
    // 设置密文登录
    ui->passwdLE->setEchoMode(QLineEdit::Password);
    connect(ui->loginBT,SIGNAL(clicked()),this,SLOT(LoginSlot()));
}

Login::~Login()
{
    delete ui;
}

void Login::LoginSlot()
{
    if (ui->userLE->text() == "admin" && ui->passwdLE->text() == "123456"){
        this->close();
        emit LoginSuccessSignal();
    } else {
        QMessageBox::warning(this,tr("login fail"),tr("Username or password entered incorrectly"),QMessageBox::Ok);
        ui->passwdLE->clear();
        ui->userLE->clear();
        ui->userLE->setFocus();
    }
}

