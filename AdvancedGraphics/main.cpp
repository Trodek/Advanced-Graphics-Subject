#include "mainwindow.h"
#include <QApplication>
#include "render.h"

int main(int argc, char *argv[])
{    
    QApplication a(argc, argv);
    Render::Instance(); // initialize the render
    MainWindow w;
    w.show();

    return a.exec();
}
