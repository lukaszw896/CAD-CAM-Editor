#ifndef DRAWABLEOBJECTSDATA_H
#define DRAWABLEOBJECTSDATA_H

#include "drawable/torus.h"
#include "drawable/point.h"
#include "drawable/drawable.h"
#include <algorithm>

class DrawableObjectsData
{

public:
        static DrawableObjectsData& getInstance();

    std::vector<Drawable*> drawableObjects;

    void addTorus(Torus*);
    void addPoint(Point*);

    void removeTorus(Torus*);
    void removePoint(Point*);

    private:

        std::vector<Torus*> torusList;
        std::vector<Point*> pointList;

        DrawableObjectsData();

        void initDrawableObjectsList();

};

#endif // DRAWABLEOBJECTSDATA_H
