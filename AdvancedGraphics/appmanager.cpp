#include "appmanager.h"
#include <iostream>

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

void AppManager::SetMainWindow(MainWindow *mw)
{
    if(main_window == nullptr)
        main_window = mw;
    else
    {
        std::cout << "Main Window already set."<< std::endl;
    }
}

void AppManager::SetHierarchy(Hierarchy *h)
{
    if(hierarchy == nullptr)
        hierarchy = h;
    else
    {
        std::cout << "Hierarchy already set."<< std::endl;
    }
}

void AppManager::SetInspector(Inspector *i)
{
    if(inspector == nullptr)
        inspector = i;
    else
    {
        std::cout << "Inspector already set."<< std::endl;
    }
}

void AppManager::SetOpenGLWidget(OpenGLWidget *oglw)
{
    if(openGL_widget == nullptr)
        openGL_widget = oglw;
    else
    {
        std::cout << "OpenGL Widget already set."<< std::endl;
    }
}

MainWindow *AppManager::GetMainWindow()
{
    return main_window;
}

Hierarchy *AppManager::GetHierarchy()
{
    return hierarchy;
}

Inspector *AppManager::GetInspector()
{
    return inspector;
}

OpenGLWidget *AppManager::GetOpenGLWidget()
{
    return openGL_widget;
}
