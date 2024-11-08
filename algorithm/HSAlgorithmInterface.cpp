#include "HSAlgorithmInterface.h"
#include "algorithm.h"

HSAlgorithmNamespace::HSAlgorithmInterface* createAlgorithmObject()
{
    HSAlgorithmNamespace::HSAlgorithmInterface* ptr = new Algorithm();
    return ptr;
}


