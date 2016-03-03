#include "window.h"
#include <QApplication>
#include <QDesktopWidget>
#include <QtGui>
#include <QtCore>
#include <QPushButton>
#include <QGridLayout>
#include <QLabel>
#include <QTextBlock>
#include "oglwidget.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Window w;
    w.resize(w.sizeHint());
        int desktopArea = QApplication::desktop()->width() *
                         QApplication::desktop()->height();
        int widgetArea = w.width() * w.height();
        w.setWindowTitle("CAD/CAM Editor");

      /*  QGridLayout *layout = new QGridLayout;
        QLabel *netDensityLabel = new QLabel("Net density");
        QTextBlock *netDensityTextBlock = new QTextBlock;
        QPushButton *applyButton = new QPushButton("Apply");

        OGlWidget *myOGlWidget = new OGlWidget;

        layout->addWidget(myOGlWidget,0,0,3,1);
        layout->addWidget(netDensityLabel,0,1,1,1);
        //layout->addWidget(netDensityTextBlock,1,1,1,1);
        layout->addWidget(applyButton,2,1,1,1);

{
        w.setLayout(layout);
*/
        if (((float)widgetArea / (float)desktopArea) < 0.75f)
            w.show();
        else
            w.showMaximized();
    //w.show();
    return a.exec();
}
