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
#include <Dialogs/addc0flatsurfacedialog.h>
#include "Data/drawableobjectsdata.h"

class DrawerWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit DrawerWindow(QWidget *parent = 0);

signals:
    void drawableDataChanged();

public slots:
    void updateCursorInfo();

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
    QMenu *addBezierSurfaceMenu;
    QAction *addTorusAct;
    QAction *addPointAct;
    QAction *addCurveAct;
    QAction *addBSplineAct;
    QAction *addInterBSplineAct;
    QAction *addBezierFlatSurface;
    QAction *addBezierCylinderSurface;
    QAction *stereoscopyAct;

    OGlWidget *oglWidget;
    QGroupBox* cordsBox;
    ObjectListsWidget* objectListsWidget;
    SettingsDialog *settingsDialog;
    AddC0FlatSurfaceDialog *addC0FlatSurfaceDialog;

    QLabel *scaleLabel;
    QSlider *scaleSlider;

    QVBoxLayout *cordsLayout;
    QVBoxLayout *rightLayout;
    QHBoxLayout *leftLayout;
    QHBoxLayout *mainLayout;

    QLabel *screenPosition;
    QLabel *xRealCord;
    QLabel *yRealCord;
    QLabel *zRealCord;

    void openStereoscopySettingsDialog();
    void openAddC0FlatSurfaceDialog();
    void addPoint();
    void addTorus();
    void addBezierCurve();
    void addBSpline();
    void addInterBSpline();
   // void addBezierSurface();

};

#endif // DRAWERWINDOW_H
