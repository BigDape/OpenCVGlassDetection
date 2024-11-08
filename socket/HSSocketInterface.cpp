#include "HSSocketInterface.h"
#include "SignalControlData.h"


// 创建对象的函数实现
SocketNameSpace::HSSocketInterface* createSocketObject()
{
    SocketNameSpace::HSSocketInterface* ptr = new SignalControlData(); ;
    return ptr;
}
