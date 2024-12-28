/********************************************************************************
 *  Puspose:
 *      LightControl.h 设置界面头文件
 *
 * Author:
 *      zhang shuanggui
 *
 * create time:
 *      2025/11/25
 *
 *******************************************************************************/
#ifndef LIGHTCONTROL_H
#define LIGHTCONTROL_H


#include <QHBoxLayout>
#include <QTreeWidget>
#include <QVBoxLayout>
#include <QWidget>
#include "HSTool.h"

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

    /**
     * @brief readRecipeToTable 读取json工单到表单中
     * @param filePath 文件路径
     */
    void readRecipeToTable(std::string filePath);
private:
    /**
     * @brief initWidget 初始化输入框类型
     */
    void initWidget();

    /**
     * @brief initLoadRecipe 初始化加载工单
     */
    void initLoadRecipe();

    /**
     * @brief initSocket 初始化socket通讯
     */
    void initSocket();

    /**
     * @brief initConnect 初始化connect
     */
    void initConnect();

    /**
     * @brief SendDataToSignal 系统初始化时，先发送一遍数据，不用再手动发送
     */
    void SendDataToSignal();

    /**
     * @brief writeCurrentRooterToJson 将当前的m_root写入到json文件中
     */
    void writeCurrentRooterToJson();

    /**
     * @brief writeEmptyAppIni 新建一个初始化文件app.ini
     * @param filePath 文件路径
     * @param recipeName 配置文件名
     */
    void writeEmptyAppIni(QString filePath, QString recipeName);

    /**
     * @brief getUiContentIntoStruct 将输入框中数据全部读取下来
     */
    void getUiContentIntoStruct();

    /**
     * @brief setUiContentFromStruct 将内存中数据写入输入框
     */
    void setUiContentFromStruct();

    /**
     * @brief getFrameSignal 实时获取帧信号
     */
    void getFrameSignal();

private slots:
    /**
     * @brief slotAllSet 全部设置下去
     */
    void slotAllSet();

    /**
     * @brief slotAllGet 全部获取
     */
    void slotAllGet();

    /**
     * @brief slotAllSave 全部保存
     */
    void slotAllSave();

    /**
     * @brief slotCreateRecipe 创建工单
     */
    void slotCreateRecipe();

    /**
     * @brief slotTestConnect 测试链接
     */
    void slotTestConnect();

    /**
     * @brief slotTrigger 触发
     */
    void slotTrigger();

    /**
     * @brief slotChangeRecipe 切换工单
     * @param index 工单下标
     */
    void slotChangeRecipe(int index);

private:
    Ui::LightControl* ui;
    SignalControl m_signalctrl;
    QTimer* m_timer; //实时获取帧信号
};

#endif // LIGHTCONTROL_H
