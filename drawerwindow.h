#ifndef DRAWERWINDOW_H
#define DRAWERWINDOW_H


#include <QMainWindow>
#include <QMenu>
#include <QMenuBar>
#include <QAction>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QSlider>
#include <RenderWidget/oglwidget.h>

class DrawerWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit DrawerWindow(QWidget *parent = 0);

signals:

public slots:

protected:
   // void contextMenuEvent(QContextMenuEvent *event) Q_DECL_OVERRIDE;

private:
    void createActions();
    void createMenus();
    void initObjects();
    void initLayout();

    QWidget *centralWidget;

    QMenu *addMenu;
    QMenu *settingsMenu;
    QAction *addTorusAct;
    QAction *addPointAct;
    QAction *addCurveAct;
    QAction *stereoscopyAct;

    OGlWidget *oglWidget;
    QLabel *scaleLabel;
    QSlider *scaleSlider;

    QVBoxLayout *rightLayout;
    QHBoxLayout *leftLayout;
    QHBoxLayout *mainLayout;

};

#endif // DRAWERWINDOW_H
