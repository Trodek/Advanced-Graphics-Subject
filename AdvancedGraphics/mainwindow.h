#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}
class Inspector;
class Hierarchy;
class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    Hierarchy *m_Hierarchy;
    Inspector *m_Inspector;
public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private:
    Ui::MainWindow *ui;

};

#endif // MAINWINDOW_H
