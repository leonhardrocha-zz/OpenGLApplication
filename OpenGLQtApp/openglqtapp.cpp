#include "OpenGLQtApp.h"

OpenGLQtApp::OpenGLQtApp(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	glWidget = new GLWidget(this);

        // using the this pointer to emphase the location of the
        // member variable used.
        // NOTE: In the UI we defined a layout names verticalLayout
    ui.horizontalLayout->addWidget(glWidget);

    connect(ui.xSlider, SIGNAL(valueChanged(int)), glWidget, SLOT(setXRotation(int)));
    connect(glWidget, SIGNAL(xRotationChanged(int)), ui.xSlider, SLOT(setValue(int)));
    connect(ui.ySlider, SIGNAL(valueChanged(int)), glWidget, SLOT(setYRotation(int)));
    connect(glWidget, SIGNAL(yRotationChanged(int)), ui.ySlider, SLOT(setValue(int)));
    connect(ui.zSlider, SIGNAL(valueChanged(int)), glWidget, SLOT(setZRotation(int)));
    connect(glWidget, SIGNAL(zRotationChanged(int)), ui.zSlider, SLOT(setValue(int)));

    ui.xSlider->setValue(15 * 16);
    ui.ySlider->setValue(345 * 16);
    ui.zSlider->setValue(0 * 16);
}

OpenGLQtApp::~OpenGLQtApp()
{

}

void OpenGLQtApp::keyPressEvent(QKeyEvent *e)
{
    if (e->key() == Qt::Key_Escape)
        close();
    else
        QWidget::keyPressEvent(e);
}