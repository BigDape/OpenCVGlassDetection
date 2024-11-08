#include "HSDatabaseInterface.h"
#include "database.h"

HSDatabaseNamespace::HSDatabaseInterface* createDatabaseObject()
{
    static HSDatabaseNamespace::HSDatabaseInterface* instance = DataBase::GetInstance();
    return instance;
}
