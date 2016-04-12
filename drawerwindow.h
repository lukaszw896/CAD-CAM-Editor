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
#include <CustomWidgets/oglwidget.h>
#include <CustomWidgets/objectlistswidget.h>
#include <Dialogs/settingsdialog.h>
#include "Data/drawableobjectsdata.h"

class DrawerWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit DrawerWindow(QWidget *parent = 0);

signals:
    void drawableDataChanged();

public slots:
    void updateCursorInfo(int screenWidth, int screenHeight);

protected:
   // void contextMenuEvent(QContextMenuEvent *event) Q_DECL_OVERRIDE;

private:

    DrawableObjectsData& drawableObjectsData = DrawableObjectsData::getInstance();

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
    ObjectListsWidget* objectListsWidget;
    SettingsDialog *settingsDialog;

    QLabel *scaleLabel;
    QSlider *scaleSlider;

    QVBoxLayout *rightLayout;
    QHBoxLayout *leftLayout;
    QHBoxLayout *mainLayout;

    QLabel *screenPosition;
    QLabel *xRealCord;
    QLabel *yRealCord;
    QLabel *zRealCord;

    void openStereoscopySettingsDialog();
    void addPoint();
    void addTorus();
    void addBezierCurve();

};

#endif // DRAWERWINDOW_H
