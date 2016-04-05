#include "drawableobjectsdata.h"

DrawableObjectsData& DrawableObjectsData::getInstance()
{

        static DrawableObjectsData instance; // Guaranteed to be destroyed.
                                             // Instantiated on first use.
        return instance;
}

DrawableObjectsData::DrawableObjectsData(){}


void DrawableObjectsData::addPoint(Point* point)
{
   pointList.push_back(point);
   drawableObjects.push_back(point);
}

void DrawableObjectsData::addTorus(Torus* torus)
{
    torusList.push_back(torus);
    drawableObjects.push_back(torus);
}

void DrawableObjectsData::removePoint(Point * point)
{

    std::vector<Point*>::iterator position = std::find(pointList.begin(), pointList.end(), point);
        if (position != pointList.end()) // == myVector.end() means the element was not found
            pointList.erase(position);
}

void DrawableObjectsData::removeTorus(Torus* torus)
{
    std::vector<Torus*>::iterator position = std::find(torusList.begin(), torusList.end(), torus);
        if (position != torusList.end()) // == myVector.end() means the element was not found
            torusList.erase(position);
}

void DrawableObjectsData::initDrawableObjectsList()
{
    drawableObjects.clear();
    for(int i=0;i<pointList.size();i++)
    {
        drawableObjects.push_back(pointList.at(i));
    }

    for(int i=0;i<torusList.size();i++)
    {
        drawableObjects.push_back(torusList.at(i));
    }
}
