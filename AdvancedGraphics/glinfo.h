#ifndef GLINFO_H
#define GLINFO_H

#include <QWidget>

namespace Ui {
class GLinfo;
}

class GLinfo : public QWidget
{
    Q_OBJECT

public:
    explicit GLinfo(QWidget *parent = 0);
    ~GLinfo();

private:
    Ui::GLinfo *ui;
};

#endif // GLINFO_H
