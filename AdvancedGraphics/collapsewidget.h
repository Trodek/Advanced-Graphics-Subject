#ifndef COLLAPSEWIDGET_H
#define COLLAPSEWIDGET_H

#include <QWidget>

namespace Ui {
class CollapseWidget;
}

class CollapseWidget : public QWidget
{
    Q_OBJECT

public:
    explicit CollapseWidget(QWidget *parent = 0);
    ~CollapseWidget();

private:
    Ui::CollapseWidget *ui;
};

#endif // COLLAPSEWIDGET_H

/*
 * std::cout « "OpenGL version:" « std::endt; std::cout « glGetString(GL_VERSION) « std::endl << std::endt;
std::cout « "OpenGL renderer:" « std::endl; std::cout cc glGetString(GL_RENDERER) « std::endl « std::endl;
std::cout cc "OpenGL vendor:" cc std::endl; std::cout « glGetString(GL_VENDOR) cc std::endl « std::endl;
std::cout « "OpenGL &St version:" « std::endl << std::endt; std::cout « glGetString(GL_SNADING_LANGUAGE_VERSION) « std::endl;
std::cout « "OpenGL extensions:" « std::endl; GLint num_extensions; glGetIntegerv(GLNOM_EXTENSIONS, denum_extensions); for (int i = El; i < num_extensions; ++1) const unsigned char *str = glGetStringi(GL_EXTENSIONS, GLuint(i)); std::cout « str « " "; std::cout « std::endl;
// Information about the surface std::cout « contextO->formatO. std::cout « context()->format(). std::cout « context()->format(). std::cout « context()->format(). std::cout cc context()->format().
format redBufferSize() « std::endl; greenBufferSize() « std::endt; blueBufferSize() « std::endl; alphaBufferSize() <c std::endl; depthBufferSize() << std::endl;
*/
