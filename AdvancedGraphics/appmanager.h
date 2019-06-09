#ifndef APPMANAGER_H
#define APPMANAGER_H

#include "mainwindow.h"
#include "hierarchy.h"
#include "inspector.h"
#include "openglwidget.h"
#include <QObject>

class AppManager : public QObject
{
    Q_OBJECT
public:
    AppManager();

    static AppManager *Instance();

    void SetMainWindow(MainWindow* mw);
    void SetHierarchy(Hierarchy* h);
    void SetInspector(Inspector* i);
    void SetOpenGLWidget(OpenGLWidget* oglw);

    MainWindow* GetMainWindow();
    Hierarchy* GetHierarchy();
    Inspector* GetInspector();
    OpenGLWidget* GetOpenGLWidget();

private:
     static AppManager* instance;

     MainWindow* main_window = nullptr;
     Hierarchy* hierarchy = nullptr;
     Inspector* inspector = nullptr;
     OpenGLWidget* openGL_widget = nullptr;
};

#endif // APPMANAGER_H
