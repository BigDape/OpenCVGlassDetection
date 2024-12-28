/********************************************************************************
 *  Puspose:
 *      main.cpp 软件主函数，由此开始执行软件加载任务
 *
 * Author:
 *      zhang shuanggui
 *
 * create time:
 *      2025/12/27
 *
 *******************************************************************************/


////////////////////////////////////////////////////////////////////////////////////
///  @brief 引用的头文件
///
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
#include <log4qt/logger.h>
#include <log4qt/logmanager.h>
#include <log4qt/propertyconfigurator.h>


//////////////////////////////////////////////////////////////////////////////////////
///  @brief 引用系统静态库，前提条件是已安装windows sdk
///
#pragma comment(lib,"DbgHelp.lib")


///////////////////////////////////////////////////////////////////////////////////////
///  @brief 引用函数
///
/**
 * @brief CreateDumpFile 将系统抛出的异常信息保存到指定路径里面
 * @param lpstrDumpFilePathName 保存dmp文件的路径地址
 * @param pException OS抛出的异常信息
 */
void CreateDumpFile(LPCWSTR lpstrDumpFilePathName, EXCEPTION_POINTERS *pException)
{
    //
    // windows系统函数，异常信息核心转储
    //
    HANDLE hDumpFile = CreateFile(lpstrDumpFilePathName, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
    //
    // Dump信息
    //
    MINIDUMP_EXCEPTION_INFORMATION dumpInfo;
    dumpInfo.ExceptionPointers = pException;
    dumpInfo.ThreadId = GetCurrentThreadId();
    dumpInfo.ClientPointers = TRUE;
    //
    // 系统函数，写入Dump文件内容
    //
    MiniDumpWriteDump(GetCurrentProcess(), GetCurrentProcessId(), hDumpFile, MiniDumpNormal, &dumpInfo, NULL, NULL);
    CloseHandle(hDumpFile);//关闭文件句柄
}

/**
 * @brief ApplicationCrashHandler 处理Unhandled Exception的回调函数，指定路径创建dmp文件
 * @param pException 系统异常
 * @return EXCEPTION_EXECUTE_HANDLER
 */
LONG ApplicationCrashHandler(EXCEPTION_POINTERS *pException)
{
    int processID = GetCurrentProcessId();
    QString dmpPath = "D:/" + QString::number(processID)+".dmp";// 这里是指定的dmp路径
    qDebug()<<dmpPath;
    CreateDumpFile(dmpPath.toStdWString().data(),pException);
    return EXCEPTION_EXECUTE_HANDLER;
}


/////////////////////////////////////////////////////////////////////////////////////////
/// \brief main 软件入口
/// \param argc 系统参数个数
/// \param argv 系统参数内容
/// \return 系统返回值
///
int main(int argc, char *argv[])
{
    //
    // 注册异常处理函数,使用VS打开D盘的dmp文件，定位软件崩溃点
    //
    SetUnhandledExceptionFilter((LPTOP_LEVEL_EXCEPTION_FILTER)ApplicationCrashHandler);
    QApplication a(argc, argv);

    //
    // 加载log4qt日志配置文件
    //
    Log4Qt::PropertyConfigurator::configure(a.applicationDirPath() + "/log.conf");

    //
    // 软件国际化，英译汉123456
    //
    QTranslator translator;
    const QStringList uiLanguages = QLocale::system().uiLanguages();
    for (const QString &locale : uiLanguages) {
        const QString baseName = "hikvision_" + QLocale(locale).name();
        if (translator.load(":/i18n/" + baseName)) {
            a.installTranslator(&translator);
            break;
        }
    }

    //
    // 登录成功后加载主界面, admin
    //
    Login w;
    MainForm AppForm;
    QObject::connect(&w,SIGNAL(LoginSuccessSignal()),&AppForm, SLOT(showWindows()));
    w.show();
    //AppForm.showWindows();
    return a.exec();
}
