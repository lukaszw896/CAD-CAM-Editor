#include "window.h"
#include <QApplication>
#include <QDesktopWidget>
#include <QtGui>
#include <QtCore>
#include <QPushButton>
#include <QGridLayout>
#include <QLabel>
#include <QTextBlock>
//#include "RenderWidget/oglwidget.h"
#include "ui_window.h"
#include "uiaccess.h"
#include "drawerwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    /*MyWindow& w = MyWindow::getInstance();
    w.resize(w.sizeHint());
        int desktopArea = QApplication::desktop()->width() *
                         QApplication::desktop()->height();
        int widgetArea = w.width() * w.height();
        w.setWindowTitle("CAD/CAM Editor");

        if (((float)widgetArea / (float)desktopArea) < 0.75f)
            w.show();
        else
            w.showMaximized();

    UiAccess& uiAccess = UiAccess::getInstance();
    uiAccess.ui = w.getUi();

    QListWidgetItem *item = new QListWidgetItem();
    item->setText(QString("test"));
    uiAccess.ui->drawableObjectsList->addItem(item);

    w.show();*/
    QFile f(":qdarkstyle/style.qss");
    if (!f.exists())
    {
        printf("Unable to set stylesheet, file not found\n");
    }
    else
    {
        f.open(QFile::ReadOnly | QFile::Text);
        QTextStream ts(&f);
        qApp->setStyleSheet(ts.readAll());
    }

    DrawerWindow window;

    window.show();


    return a.exec();
}
