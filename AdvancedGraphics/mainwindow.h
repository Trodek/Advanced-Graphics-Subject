#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QAction>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    //File menu Actions
    QAction screenshot_action;
    QAction close_app;
    QAction undo;
    QAction redo;
    //----------------------

public slots:

    void OpenAboutGL();


private slots:
    void on_actionExit_triggered();
};

#endif // MAINWINDOW_H
