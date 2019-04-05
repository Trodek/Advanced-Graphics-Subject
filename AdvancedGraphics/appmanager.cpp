#include "appmanager.h"

AppManager* AppManager::instance = nullptr;
AppManager::AppManager()
{

}

AppManager *AppManager::Instance()
{
    if(instance == nullptr)
    {
        instance = new AppManager();
    }

    return instance;
}
