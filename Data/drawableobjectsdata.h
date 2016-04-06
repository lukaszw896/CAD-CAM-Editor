#ifndef DRAWABLEOBJECTSDATA_H
#define DRAWABLEOBJECTSDATA_H

#include "drawable/torus.h"
#include "drawable/point.h"
#include "drawable/drawable.h"
#include "drawable/cursor.h"
#include "Camera/camera.h"
#include <algorithm>
#include <string>

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

    void removeTorusByName(std::string);
    void removePointByName(std::string);
    void selectTorusByName(std::string);
    void selectPointByName(std::string);
    void deselectToruses();
    void deselectPoints();
    void removeTorus(Torus*);
    void removePoint(Point*);

    std::vector<Torus*> torusList;
    std::vector<Point*> pointList;
    private:



        DrawableObjectsData();

        void initDrawableObjectsList();

};

#endif // DRAWABLEOBJECTSDATA_H
