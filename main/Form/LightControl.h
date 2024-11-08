#ifndef LIGHTCONTROL_H
#define LIGHTCONTROL_H


#include <QHBoxLayout>
#include <QTreeWidget>
#include <QVBoxLayout>
#include <QWidget>
#include "HSTool.h"
#include "HSJsoncppInterface.h"

#define SYSTEMNAME "app.ini"

QT_BEGIN_NAMESPACE
namespace Ui {
class LightControl;
}
QT_END_NAMESPACE

namespace SocketNameSpace {
    class HSSocketInterface;
}


class LightControl : public QWidget
{
    Q_OBJECT

public:
    explicit LightControl( QWidget* parent = nullptr);
    ~LightControl();
    // 读取json工单到表单中
    void readRecipeToTable(std::string filePath);
private:
    /**
     * @brief initWidget 初始化输入框类型
     */
    void initWidget();
    void initLoadRecipe();
    void initSocket();
    void initConnect();
    // 将当前的m_root写入到json文件中
    void writeCurrentRooterToJson();
    // 新建一个初始化文件app.ini
    void writeEmptyAppIni(QString filePath, QString recipeName);
    // 将输入框中数据全部读取下来
    void getUiContentIntoStruct();
    // 将内存中数据写入输入框
    void setUiContentFromStruct();
    // 实时获取帧信号
    void getFrameSignal();
private slots:
    void slotAllSet();
    void slotAllGet();
    void slotAllSave();
    void slotCreateRecipe();
    void slotTestConnect();
    void slotTrigger();
    void slotChangeRecipe(int index);


private:
    Ui::LightControl* ui;
    QTimer* timer;
    std::shared_ptr<QTimer> timer1;
    SignalControl m_signalctrl;
    SocketNameSpace::HSSocketInterface* SocketObjectPtr;
    HSJsoncppNamespace::HSJsoncppInterface* jsoncppPtr;
    HMODULE jsoncppDllHandle;
    HMODULE socketDllHandle;
    QTimer* m_timer; //实时获取帧信号
};

#endif // LIGHTCONTROL_H
