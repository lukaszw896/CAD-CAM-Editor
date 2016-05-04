#ifndef DRAWABLEOBJECTSDATA_H
#define DRAWABLEOBJECTSDATA_H

#include "drawable/torus.h"
#include "drawable/point.h"
#include "drawable/drawable.h"
#include "drawable/cursor.h"
#include "drawable/beziercurve.h"
#include "drawable/bspline.h"
#include "drawable/interbspline.h"
#include "drawable/Surfaces/beziersurface.h"
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
    void addBSpline(BSpline*);
    void addInterBSpline(InterBSpline*);
    //
    void addBezierSurface(BezierSurface*);

    void addPointToBezierCurve(BezierCurve*, Point*);
    void addPointToBSpline(BSpline*, Point*);
    void addPointToInterBSpline(InterBSpline*,Point*);
    void addCursor(Cursor*);

    void removeTorusByName(std::string);
    void removePointByName(std::string);
    void removeBezierCurveByName(std::string);
    void removeBSplineByName(std::string);
    void removeInterBSplineByName(std::string);
    //
    void removeBezierSurfaceByName(std::string);

    void selectTorusByName(std::string);
    void selectPointByName(std::string);
    void selectBezierCurveByName(std::string);
    void selectBSplineByName(std::string);
    void selectInterBSplineByName(std::string);
    //
    void selectBezierSurfaceByName(std::string);

    Point* getPointByName(string);
    BezierCurve* getBezierCurveByName(std::string);
    BSpline* getBSplineByName(std::string);
    InterBSpline* getInterBSplineByName(std::string);
    //
    BezierSurface* getBezierSurfaceByName(std::string);

    void deselectToruses();
    void deselectPoints();
    void deselectBezierCurves();
    void deselectBSplines();
    void deselectInterBSplines();
    //
    void deselectBezierSurface();

    void removeTorus(Torus*);
    void removePoint(Point*);
    void removeBezierCurves(BezierCurve*);
    void removeBSpline(BSpline*);
    void removeInterBSpline(InterBSpline*);
    //
    void removeBezierSurface(BezierSurface*);

    void moveCursorToTorusByName(std::string);
    void moveCursorToPointByName(std::string);

    Point* findPointBySceneClick(QPoint screenPos, QPoint screenSize);

    Drawable* findObjectNearCursor();

    std::vector<Torus*> torusList;
    std::vector<Point*> pointList;
    std::vector<BezierCurve*> bezierCurveList;
    std::vector<BSpline*> bSplineList;
    std::vector<InterBSpline*> interBSplineList;
    vector<BezierSurface*> bezierSurfaceList;

    private:

        DrawableObjectsData();

        void initDrawableObjectsList();

};

#endif // DRAWABLEOBJECTSDATA_H
