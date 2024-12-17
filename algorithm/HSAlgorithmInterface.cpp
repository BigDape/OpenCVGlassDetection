#include "HSAlgorithmInterface.h"
#include "OpenCVAlgorithm.h"

HSAlgorithmNamespace::HSAlgorithmInterface* createAlgorithmObject()
{
    HSAlgorithmNamespace::HSAlgorithmInterface* ptr = new OpenCVAlgorithm();
    return ptr;
}


