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
#include <QResizeEvent>
#include <CustomWidgets/oglwidget.h>
#include <CustomWidgets/objectlistswidget.h>
#include <Dialogs/settingsdialog.h>
#include <Dialogs/addc0flatsurfacedialog.h>
#include "Data/drawableobjectsdata.h"
#include "Data/fileio.h"

class DrawerWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit DrawerWindow(QWidget *parent = 0);

signals:
    void drawableDataChanged();
    void heightChanged(int);

public slots:
    void updateCursorInfo();
    void updatePatchParam(int);

protected:
   // void contextMenuEvent(QContextMenuEvent *event) Q_DECL_OVERRIDE;

private:
    int oldHeight= 200;
    DrawableObjectsData& drawableObjectsData = DrawableObjectsData::getInstance();
    FileIO* fileIO = new FileIO();

    void createActions();
    void createMenus();
    void initObjects();
    void initLayout();

    QWidget *centralWidget;

    QMenu * fileMenu;
    QMenu *addMenu;
    QMenu *settingsMenu;
    QMenu *addBezierSurfaceMenu;
    QAction *saveFileAct;
    QAction *openFileAct;
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
    QSlider *patchParamSlider;

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
    void openAddC0CylinderSurfaceDialog();
    void saveFile();
    void openFile();
    void addPoint();
    void addTorus();
    void addBezierCurve();
    void addBSpline();
    void addInterBSpline();

    void resizeEvent(QResizeEvent *);
   // void addBezierSurface();

};

#endif // DRAWERWINDOW_H
