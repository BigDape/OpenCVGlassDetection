#include "HSJsoncppInterface.h"
#include "jsoncpp.h"

HSJsoncppNamespace::HSJsoncppInterface* createJsoncppObject()
{
    HSJsoncppNamespace::HSJsoncppInterface* ptr = new Jsoncpp();
    return ptr;
}
