#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QAction>

namespace Ui {
class MainWindow;
}
class Inspector;
class Hierarchy;
class TransformWidget;
class OpenGLWidget;

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    Hierarchy *m_Hierarchy;
    Inspector *m_Inspector;
    TransformWidget* m_Trans;
    OpenGLWidget* m_OpenGLWidget;
public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void Redraw();
   // void OpenaboutGL();
private slots:
    void on_actionExit_triggered();
    void on_actionSave_Scene_triggered();

    void on_actionLoad_Scene_triggered();

    void on_actionNew_Scene_triggered();

    void on_actionLoad_Texture_triggered();

    void on_actionLoad_Model_triggered();

    void on_actionLoad_Shader_triggered();

private:
    Ui::MainWindow *ui;
    //File Menu Actions
    QAction m_ScreenshotAction;
    QAction m_CloseApp;
    QAction m_Undo;
    QAction m_Redo;

};

#endif // MAINWINDOW_H
