#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}
class Inspector;
class Hierarchy;
class ShapeDrawerWidget;
class TransformWidget;

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    Hierarchy *m_Hierarchy;
    Inspector *m_Inspector;
    ShapeDrawerWidget *m_ShapeDrawer;
    TransformWidget* m_Trans;

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void Redraw();

private:
    Ui::MainWindow *ui;

};

#endif // MAINWINDOW_H
