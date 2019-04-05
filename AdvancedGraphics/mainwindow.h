#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QAction>

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
   // void OpenaboutGL();
private slots:
    void on_actionExit_triggered();
private:
    Ui::MainWindow *ui;
    //File Menu Actions
    QAction m_ScreenshotAction;
    QAction m_CloseApp;
    QAction m_Undo;
    QAction m_Redo;

};

#endif // MAINWINDOW_H
