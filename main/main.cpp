#include <QApplication>
#include <QLocale>
#include <QTranslator>
#include <stdlib.h>
#include <QDebug>
#include <QDir>
#include <QTranslator>
#include <QObject>
#include <QProcessEnvironment>
#include "Form/Login.h"
#include "MainForm.h"
#include <Windows.h>
#include <DbgHelp.h>
#pragma comment(lib,"DbgHelp.lib")

// 创建Dump文件
void CreateDumpFile(LPCWSTR lpstrDumpFilePathName, EXCEPTION_POINTERS *pException)
{
    HANDLE hDumpFile = CreateFile(lpstrDumpFilePathName, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
    // Dump信息
    MINIDUMP_EXCEPTION_INFORMATION dumpInfo;
    dumpInfo.ExceptionPointers = pException;
    dumpInfo.ThreadId = GetCurrentThreadId();
    dumpInfo.ClientPointers = TRUE;
    // 写入Dump文件内容
    MiniDumpWriteDump(GetCurrentProcess(), GetCurrentProcessId(), hDumpFile, MiniDumpNormal, &dumpInfo, NULL, NULL);
    CloseHandle(hDumpFile);
}
// 处理Unhandled Exception的回调函数
LONG ApplicationCrashHandler(EXCEPTION_POINTERS *pException)
{
    int processID = GetCurrentProcessId();
    QString dmpPath = "D:/" + QString::number(processID)+".dmp";
    qDebug()<<dmpPath;
    CreateDumpFile(dmpPath.toStdWString().data(),pException);
    return EXCEPTION_EXECUTE_HANDLER;
}

int main(int argc, char *argv[])
{
    //注册异常处理函数,使用VS打开D盘的dmp文件，查看崩溃在哪一行
    SetUnhandledExceptionFilter((LPTOP_LEVEL_EXCEPTION_FILTER)ApplicationCrashHandler);
    QApplication a(argc, argv);
    // 软件国际化
    QTranslator translator;
    const QStringList uiLanguages = QLocale::system().uiLanguages();
    for (const QString &locale : uiLanguages) {
        const QString baseName = "hikvision_" + QLocale(locale).name();
        if (translator.load(":/i18n/" + baseName)) {
            a.installTranslator(&translator);
            break;
        }
    }
    // 登录成功后加载主界面
    Login w;
    MainForm AppForm;
    //QObject::connect(&w,SIGNAL(LoginSuccessSignal()),&AppForm, SLOT(showWindows()));
    //w.show();
    AppForm.showWindows();
    return a.exec();
}
