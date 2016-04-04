#ifndef WINDOW_H
#define WINDOW_H

#include <QWidget>

namespace Ui {
class Window;
}

class MyWindow : public QWidget
{
    Q_OBJECT

public:
    explicit MyWindow(QWidget *parent = 0);
    ~MyWindow();

   Ui::Window *ui;

   static MyWindow& getInstance();

   Ui::Window* getUi();




};

#endif // WINDOW_H
