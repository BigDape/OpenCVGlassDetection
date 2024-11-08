#ifndef MAINFORM_H
#define MAINFORM_H

#include <QVBoxLayout>
#include <QWidget>
#include <QTimer>
#include <QAction>
#include "mainwindow.h"

namespace Ui {
class MainForm;
}

class MainForm : public QWidget
{
    Q_OBJECT

public:
    explicit MainForm(QWidget* parent = nullptr);
    ~MainForm();

public slots:
    void showWindows();

private:
    Ui::MainForm* ui;
    MainWindow* main_window;
};

#endif // MAINFORM_H
