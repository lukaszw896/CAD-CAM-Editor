#include "window.h"

#include <QtWidgets>
#include "ui_window.h"
#include "RenderWidget/oglwidget.h"

Window::Window(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Window)
{
    ui->setupUi(this);
}

Window::~Window()
{
    delete ui;
}
