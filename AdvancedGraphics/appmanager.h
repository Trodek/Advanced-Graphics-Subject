#ifndef APPMANAGER_H
#define APPMANAGER_H

#include "mainwindow.h"
#include "hierarchy.h"
#include "inspector.h"

class AppManager
{
public:
    AppManager();

     static AppManager *Instance();


private:
     static AppManager* instance;

     MainWindow* main_window = nullptr;
     Hierarchy* hierarchy = nullptr;
     Inspector* inspector = nullptr;
};

#endif // APPMANAGER_H
