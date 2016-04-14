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
   for(int i=0;i<bezierCurveList.size();i++)
   {
       if(bezierCurveList[i]->isSelected)
       {
           bezierCurveList[i]->pointVector.push_back(point);
       }
   }

   pointList.push_back(point);
   drawableObjects.push_back(point);
}

void DrawableObjectsData::addTorus(Torus* torus)
{
    torusList.push_back(torus);
    drawableObjects.push_back(torus);
}
void DrawableObjectsData::addCursor(Cursor * cursor)
{
    this->cursor = cursor;
    drawableObjects.push_back(cursor);
}

void DrawableObjectsData::addBezierCurve(BezierCurve* bezierCurve)
{
    bezierCurveList.push_back(bezierCurve);
    drawableObjects.push_back(bezierCurve);
}

void DrawableObjectsData::addPointToBezierCurve(BezierCurve * bezierCurve, Point * point)
{
    bool add = true;
    for(int i=0;i<bezierCurve->pointVector.size();i++)
    {
        if(bezierCurve->pointVector[i]->name == point->name)
        {
            add = false;
        }
    }
    if(add)
    {
        bezierCurve->pointVector.push_back(point);
    }
}

void DrawableObjectsData::removeTorusByName(std::string name)
{
    for(int i=0; i<torusList.size();i++){
        if(torusList[i]->name == name)
        {
            removeTorus(torusList[i]);
            break;
        }
    }
}

void DrawableObjectsData::removePointByName(std::string name)
{
    for(int i=0;i<bezierCurveList.size();i++)
    {
        bezierCurveList[i]->removePointByName(name);
    }
    for(int i=0; i<pointList.size();i++){
        if(pointList[i]->name == name)
        {
            removePoint(pointList[i]);
            break;
        }
    }
}

void DrawableObjectsData::removeBezierCurveByName(std::string name)
{
    for(int i=0; i<bezierCurveList.size();i++){
        if(bezierCurveList[i]->name == name)
        {
            removeBezierCurves(bezierCurveList[i]);
            break;
        }
    }
}

void DrawableObjectsData::selectTorusByName(std::string name)
{
    for(int i=0; i<torusList.size();i++){
        if(torusList[i]->name == name)
        {
            torusList[i]->isSelected= true;
            break;
        }
    }
}

void DrawableObjectsData::selectPointByName(std::string name)
{
    for(int i=0; i<pointList.size();i++){
        if(pointList[i]->name == name)
        {
            pointList[i]->isSelected = true;
            break;
        }
    }
}

void DrawableObjectsData::selectBezierCurveByName(std::string name)
{
    for(int i=0; i<bezierCurveList.size();i++){
        if(bezierCurveList[i]->name == name)
        {
            bezierCurveList[i]->isSelected = true;
            break;
        }
    }
}

Point* DrawableObjectsData::getPointByName(string name)
{
    for(int i=0; i<pointList.size();i++){
        if(pointList[i]->name == name)
        {
            return pointList[i];
        }
    }
}

BezierCurve* DrawableObjectsData::getBezierCurveByName(string name)
{
    for(int i=0; i<bezierCurveList.size();i++){
        if(bezierCurveList[i]->name == name)
        {
            return bezierCurveList[i];
        }
    }
}

void DrawableObjectsData::deselectToruses()
{
    for(int i=0; i<torusList.size();i++){
        torusList[i]->isSelected= false;
    }
}

void DrawableObjectsData::deselectPoints()
{
    for(int i=0; i<pointList.size();i++){
        pointList[i]->isSelected = false;
    }
}

void DrawableObjectsData::deselectBezierCurves()
{
    for(int i=0; i<bezierCurveList.size();i++){
        bezierCurveList[i]->isSelected = false;
    }
}

void DrawableObjectsData::removePoint(Point * point)
{

    std::vector<Point*>::iterator position = std::find(pointList.begin(), pointList.end(), point);
        if (position != pointList.end()) // == myVector.end() means the element was not found
            pointList.erase(position);
        initDrawableObjectsList();
}

void DrawableObjectsData::removeTorus(Torus* torus)
{
    std::vector<Torus*>::iterator position = std::find(torusList.begin(), torusList.end(), torus);
        if (position != torusList.end()) // == myVector.end() means the element was not found
            torusList.erase(position);
        initDrawableObjectsList();
}

void DrawableObjectsData::removeBezierCurves(BezierCurve * bezierCurve)
{
    std::vector<BezierCurve*>::iterator position = std::find(bezierCurveList.begin(), bezierCurveList.end(), bezierCurve);
        if (position != bezierCurveList.end()) // == myVector.end() means the element was not found
            bezierCurveList.erase(position);
        initDrawableObjectsList();
}

void DrawableObjectsData::initDrawableObjectsList()
{
    drawableObjects.clear();
    drawableObjects.push_back(cursor);
    for(int i=0;i<pointList.size();i++)
    {
        drawableObjects.push_back(pointList.at(i));
    }

    for(int i=0;i<torusList.size();i++)
    {
        drawableObjects.push_back(torusList.at(i));
    }

    for(int i=0;i<bezierCurveList.size();i++)
    {
        drawableObjects.push_back(bezierCurveList.at(i));
    }

}

void DrawableObjectsData::moveCursorToTorusByName(std::string name)
{
    for(int i=0; i<torusList.size();i++){
        if(torusList[i]->name == name)
        {
            cursor->xPos = torusList[i]->xPos;
            cursor->yPos = torusList[i]->yPos;
            cursor->zPos = torusList[i]->zPos;
            cursor->updateTranslationMatX();
            cursor->updateTranslationMatY();
            cursor->updateTranslationMatZ();
            break;
        }
    }
}

void DrawableObjectsData::moveCursorToPointByName(std::string name)
{
    for(int i=0; i<pointList.size();i++){
        if(pointList[i]->name == name)
        {
            cursor->xPos = pointList[i]->xPos;
            cursor->yPos = pointList[i]->yPos;
            cursor->zPos = pointList[i]->zPos;
            cursor->updateTranslationMatX();
            cursor->updateTranslationMatY();
            cursor->updateTranslationMatZ();
            break;
        }
    }
}

Drawable* DrawableObjectsData::findObjectNearCursor()
{
    for(int i=1;i<drawableObjects.size();i++)
    {
       float distance;
       distance = sqrt(pow(cursor->xPos-drawableObjects[i]->xPos,2)
                       +pow(cursor->yPos-drawableObjects[i]->yPos,2)
                       +pow(cursor->zPos-drawableObjects[i]->zPos,2));
       if(distance<0.05f)
       {
           return drawableObjects[i];
       }
    }
    return NULL;
}

Point* DrawableObjectsData::findPointBySceneClick(QPoint screenPos, QPoint screenSize)
{
    double tmpXPos,tmpYPos;
    for(int i=0;i<pointList.size();i++){
        tmpXPos = screenSize.x() * (pointList[i]->transPointCoordinates.x+1.0)/2;
        tmpYPos = screenSize.y() - screenSize.y() * (pointList[i]->transPointCoordinates.y+1.0)/2;
        float distance = sqrt(pow(screenPos.x() - tmpXPos,2)+pow(screenPos.y() - tmpYPos,2));
        if(distance < 10)
        {
            return pointList[i];
        }
    }
    return NULL;
}
