#include "mainwindow.h"
#include <QApplication>
#include "render.h"
#include "resourcemanager.h"

int main(int argc, char *argv[])
{    
    QApplication a(argc, argv);
    ResourceManager::Instance();
    Render::Instance(); // initialize the render
    MainWindow w;
    w.show();

    return a.exec();
}
