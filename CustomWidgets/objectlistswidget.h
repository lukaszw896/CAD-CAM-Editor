#ifndef OBJECTLISTSWIDGET_H
#define OBJECTLISTSWIDGET_H

#include <QWidget>
#include <QGroupBox>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QListWidget>
#include <QMenu>
#include <QTreeWidget>
#include <QListWidgetItem>
#include <QAbstractAnimation>
#include <QScrollArea>
#include <QPushButton>
#include "drawable/point.h"
#include "drawable/torus.h"
#include "Data/drawableobjectsdata.h"
#include "Dialogs/namechangedialog.h"

class ObjectListsWidget : public QWidget
{
    Q_OBJECT
public:
    ObjectListsWidget();

public slots:
    void updateListsContent();
    void torusHasBeenSelected();
    void torusHasBeenDoubleClicked();
    void pointHasBeenSelected();
    void pointHasBeenDoubleClicked();

    void bezierCurveHasBeenClicked();
    void bSplineHasBeenClicked();
    void interBSplineHasBeenClicked();
    void bezierSurfaceHasBeenClicked();

    void deleteTorusButtonClicked();
    void deletePointButtonClicked();
    void deleteCurveButtonClicked();
    void deleteBSplineButtonClicked();
    void deleteInterBSplineButtonClicked();
    void deleteBezierSurfaceHasBeenClicked();

    void pointOnSceneSelection(Point*);
    void pointOnSceneDoubleClick(Point*);

    void showPointsContextMenu(const QPoint&);
    void showBezierCurvesContextMenu(const QPoint&);
    void showBSplineContextMenu(const QPoint&);
    void showInterBSplineContextMenu(const QPoint&);
    void showBezierSurfaceContextMenu(const QPoint&);

    void drawableHasBeenRenamed();

    //POINT LIST SLOTS

    void addToCurve(QAction*);
    void addToBSpline(QAction*);
    void addToInterBSpline(QAction*);
    void renamePoint();

    //BEZIER CURVE TREE WIDGET SLOTS
    void addBezierCurveListItem();
    void removeBezierCurve();
    void removePointFromBezierCurve();
    void turnOnOffBezierPolygon();

    //BSPLINE TREE WIDGET SLOTS
    void addBSplineListItem();
    void removeBSpline();
    void removePointFromBSpline();
    void turnOnOffBSplinePolygon();

    //INTERPLATED BSPLINE TREE WIDGET SLOTS
    void addInterBSplineListItem();
    void removeInterBSpline();
    void removePointFromInterBSpline();
    void turnOnOffInterBSplinePolygon();

    //BEZIER SURFACE TREE WIDGET SLOTS
    void removeBezierSurface();
    void turnOnBezierNet();

signals:



private:

    DrawableObjectsData& drawableObjectsData = DrawableObjectsData::getInstance();

    QScrollArea* scrollArea;

    QVBoxLayout* mainLayout;
    QVBoxLayout* widgetContainerLayout;
    QVBoxLayout* torusLayout;
    QVBoxLayout* pointLayout;
    QVBoxLayout* curveLayout;
    QVBoxLayout* bSplineLayout;
    QVBoxLayout* interBSplineLayout;
    QVBoxLayout* bezierSurfaceLayout;


    QLabel* torusListLabel;
    QLabel* pointListLabel;
    QLabel* bezierListLabel;
    QLabel* bSplineListLabel;
    QLabel* interBSplineListLabel;
    QLabel* bezierSurfaceListLabel;

    QListWidget* torusList;
    QListWidget* pointList;
    QTreeWidget* bezierCurveTreeList;
    QTreeWidget* bSplineCurveTreeList;
    QTreeWidget* interBSplineCurveTreeList;
    QTreeWidget* bezierSurfaceTreeList;

    NameChangeDialog* nameChangeDialog;

    void setupLayout();

    void addBezierCurveToList(BezierCurve* bezierCurve, QTreeWidget* parent, QString name);
    void addPointToCurve(QTreeWidgetItem* parent, QString name);

    void addBSplineTolist(BSpline* bSpline, QTreeWidget* parent, QString name);
    void addPointToBSpline(QTreeWidgetItem* parent, QString name);

    void addInterBSplineTolist(InterBSpline* interBSpline, QTreeWidget* parent, QString name);
    void addPointToInterBSpline(QTreeWidgetItem* parent, QString name);

    void addBezierSurfaceTolist(BezierSurface* bezierSurface, QTreeWidget* parent, QString name);
  //  void addPointToBezierSurface(QTreeWidgetItem* parent, QString name);
};

#endif // OBJECTLISTSWIDGET_H
