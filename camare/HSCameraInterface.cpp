#include "HSCameraInterface.h"
#include "DushenBasicFunc.h"


// 创建对象的函数实现
    CameraNameSpace::HSCameraInterface* createCameraObject()
    {
        CameraNameSpace::HSCameraInterface* ptr = new DushenBasicFunc();
        return ptr;
    }


