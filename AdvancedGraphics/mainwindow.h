#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "hierarchy.h"
#include "collapsewidget.h"
#include "gameobject.h"
#include "inspector.h"
#include "scene.h"


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    Hierarchy *m_Hierarchy;
    Inspector *m_Inspector;
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
