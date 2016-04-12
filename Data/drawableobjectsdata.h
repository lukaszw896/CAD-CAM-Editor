#ifndef DRAWABLEOBJECTSDATA_H
#define DRAWABLEOBJECTSDATA_H

#include "drawable/torus.h"
#include "drawable/point.h"
#include "drawable/drawable.h"
#include "drawable/cursor.h"
#include "drawable/beziercurve.h"
#include "Camera/camera.h"
#include <algorithm>
#include <string>
#include <math.h>
#include <QPoint>

class DrawableObjectsData
{

public:
        static DrawableObjectsData& getInstance();

    std::vector<Drawable*> drawableObjects;
    Cursor* cursor;
    Camera* camera;

    void addTorus(Torus*);
    void addPoint(Point*);
    void addBezierCurve(BezierCurve*);
    void addCursor(Cursor*);

    void removeTorusByName(std::string);
    void removePointByName(std::string);
    void removeBezierCurveByName(std::string);

    void selectTorusByName(std::string);
    void selectPointByName(std::string);
    void selectBezierCurveByName(std::string);

    void deselectToruses();
    void deselectPoints();
    void deselectBezierCurves();

    void removeTorus(Torus*);
    void removePoint(Point*);
    void removeBezierCurves(BezierCurve*);

    void moveCursorToTorusByName(std::string);
    void moveCursorToPointByName(std::string);

    Point* findPointBySceneClick(QPoint screenPos, QPoint screenSize);

    Drawable* findObjectNearCursor();

    std::vector<Torus*> torusList;
    std::vector<Point*> pointList;
    std::vector<BezierCurve*> bezierCurveList;
    private:

        DrawableObjectsData();

        void initDrawableObjectsList();

};

#endif // DRAWABLEOBJECTSDATA_H
