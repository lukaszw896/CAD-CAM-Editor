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

using namespace std;
class DrawableObjectsData
{
public:
    static DrawableObjectsData& getInstance();

    vector<Drawable*> allDrawableObjects;
    DrawableType currentDrawableObject;


    vector<Drawable*> drawableObjectsContainer;
    Cursor* cursor;
    Camera* camera;
    vector<Drawable*> torusList;
    vector<Drawable*> pointList;
    vector<Drawable*> bezierCurveList;
    vector<Drawable*> bSplineList;
    vector<Drawable*> interBSplineList;
    vector<Drawable*> bezierSurfaceList;

    void addObject(DrawableType drawableType, Drawable* drawable);
    void addPoint(Point*);
    void addBezierSurface(BezierSurface*);
    void addPointToBezierCurve(BezierCurve*, Point*);
    void addPointToBSpline(BSpline*, Point*);
    void addPointToInterBSpline(InterBSpline*,Point*);
    void addCursor(Cursor*);

    void removeObjectByName(DrawableType drawableType,string name);
    void removePointByName(std::string);
    void removeBezierSurfaceByName(std::string);

    void selectObjectByName(DrawableType drawableType, string name);

    Drawable* getObjectByName(DrawableType drawableType, string name);

    void deselectObjects(DrawableType drawableType);

    void removeObject(DrawableType drawableType, Drawable* drawable);

    void moveCursorToTorusByName(std::string);
    void moveCursorToPointByName(std::string);

    Point* findPointBySceneClick(QPoint screenPos, QPoint screenSize);

    Drawable* findObjectNearCursor();

    int getPointListIndex(Point*);

    void updatePatchParam(int n)
    {
        for(int i=0;i<bezierSurfaceList.size();i++)
        {
            for(int j=0;j<((BezierSurface*)bezierSurfaceList[i])->patches.size();j++)
            {
                ((BezierSurface*)bezierSurfaceList[i])->patches[j]->u = 1.0f/n;
                ((BezierSurface*)bezierSurfaceList[i])->patches[j]->v = 1.0f/n;
            }
        }
    }

private:
    DrawableObjectsData();

    void initDrawableObjectsList();
    void assignDrawableObjectsListToContainer(DrawableType drawableType);
    void assignContainerToDrawableObjectsList();

};

#endif // DRAWABLEOBJECTSDATA_H
