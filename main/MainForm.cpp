#include "MainForm.h"
#include "ui_MainForm.h"
#include <QLabel>

#pragma execution_character_set("utf-8")

#define TITLEBAR_HEIGHT 40

MainForm::MainForm(QWidget* parent)
    : QWidget(parent)
    , ui(new Ui::MainForm)
{
    ui->setupUi(this);
}

MainForm::~MainForm()
{
    delete ui;
}

void MainForm::showWindows()
{
    // 商标
    QLabel *m_pIconLabel = new QLabel(this);
    m_pIconLabel->setFixedSize(300, 56);
    m_pIconLabel->setPixmap(QPixmap(":/icons/hs.png"));
    m_pIconLabel->setAlignment(Qt::AlignTop | Qt::AlignLeft);
    // 标题
    QLabel* m_pTitleLabel = new QLabel(this);
    m_pTitleLabel->setFixedSize(300,56);
    m_pTitleLabel->setText("皓视在线缺陷检测");
    m_pTitleLabel->setStyleSheet("font: 75 24pt \"微软雅黑\"; color: rgb(0, 0, 200);");
    m_pTitleLabel->setAlignment(Qt::AlignTop | Qt::AlignCenter);
    m_pTitleLabel->move(800,0);
    // 获取主界面的大小
    // 获取当前屏幕对象
    QScreen *screen = QApplication::primaryScreen();
    if (!screen) {
        qWarning() << "无法获取主屏幕对象。";
    }
    // 获取屏幕分辨率
    QSize screenSize = screen->size();
    int width = screenSize.width();
    int height = screenSize.height();
    qDebug() << "当前屏幕分辨率：" << width << "x" << height;
    // 主界面
    main_window = new MainWindow(this);
    main_window->move(0,56);
    QWidget::showFullScreen();
}
