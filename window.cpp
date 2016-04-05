#include "window.h"

#include <QtWidgets>
#include "ui_window.h"
#include "CustomWidgets/oglwidget.h"

MyWindow::MyWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Window)
{
    ui->setupUi(this);
}

MyWindow::~MyWindow()
{
    delete ui;
}

Ui::Window* MyWindow::getUi()
{
    return this->ui;
}

MyWindow& MyWindow::getInstance(){

    static MyWindow instance;

    return instance;
}


