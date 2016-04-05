#ifndef DRAWABLEOBJECTSDATA_H
#define DRAWABLEOBJECTSDATA_H

#include "drawable/torus.h"
#include "drawable/point.h"
#include "drawable/drawable.h"
#include "drawable/cursor.h"
#include "Camera/camera.h"
#include <algorithm>

class DrawableObjectsData
{

public:
        static DrawableObjectsData& getInstance();

    std::vector<Drawable*> drawableObjects;
    Cursor* cursor;
    Camera* camera;

    void addTorus(Torus*);
    void addPoint(Point*);
    void addCursor(Cursor*);

    void removeTorus(Torus*);
    void removePoint(Point*);

    private:

        std::vector<Torus*> torusList;
        std::vector<Point*> pointList;

        DrawableObjectsData();

        void initDrawableObjectsList();

};

#endif // DRAWABLEOBJECTSDATA_H
