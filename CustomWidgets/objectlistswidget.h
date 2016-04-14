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

    void deleteTorusButtonClicked();
    void deletePointButtonClicked();
    void deleteCurveButtonClicked();

    void pointOnSceneSelection(Point*);
    void pointOnSceneDoubleClick(Point*);

    void showPointsContextMenu(const QPoint&);
    void showBezierCurvesContextMenu(const QPoint&);

    void drawableHasBeenRenamed();

    //POINT LIST SLOTS

    void addToCurve(QAction*);
    void renamePoint();

    //BEZIER CURVE TREE WIDGET SLOTS
    void addBezierCurveListItem();
    void removeBezierCurve();
    void removePointFromBezierCurve();
    void turnOnOffPolygon();

signals:



private:

    DrawableObjectsData& drawableObjectsData = DrawableObjectsData::getInstance();

    QVBoxLayout* mainLayout;
    QVBoxLayout* torusLayout;
    QVBoxLayout* pointLayout;
    QVBoxLayout* curveLayout;


    QGroupBox* torusGroupBox;
    QGroupBox* pointGroupBox;
    QGroupBox* curveGroupBox;

    QListWidget* torusList;
    QListWidget* pointList;
    QTreeWidget* bezierCurveTreeList;

    QPushButton* deleteTorusButton;
    QPushButton* deletePointButton;
    QPushButton* deleteCurveButton;

    NameChangeDialog* nameChangeDialog;


    void setupGroupBoxes();
    void setupLayout();
    void setupButtons();

    void addBezierCurveToList(BezierCurve* bezierCurve, QTreeWidget* parent, QString name);
    void addPointToCurve(QTreeWidgetItem* parent, QString name);
};

#endif // OBJECTLISTSWIDGET_H
