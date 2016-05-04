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

   for(int i=0;i<bSplineList.size();i++)
   {
       if(bSplineList[i]->isSelected)
       {
           bSplineList[i]->deBoorPoints.push_back(point);
       }
   }

   for(int i=0;i<interBSplineList.size();i++)
   {
       if(interBSplineList[i]->isSelected)
       {
           interBSplineList[i]->deBoorPoints.push_back(point);
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

void DrawableObjectsData::addBSpline(BSpline * bSpline)
{
    bSplineList.push_back(bSpline);
    drawableObjects.push_back(bSpline);
}

void DrawableObjectsData::addInterBSpline(InterBSpline * interBSpline)
{
    interBSplineList.push_back(interBSpline);
    drawableObjects.push_back(interBSpline);
}

void DrawableObjectsData::addBezierSurface(BezierSurface * bezierSurface)
{
    bezierSurfaceList.push_back(bezierSurface);
    drawableObjects.push_back(bezierSurface);

    for(int i=0;i<bezierSurface->controlPoints.size();i++)
    {
        pointList.push_back(bezierSurface->controlPoints[i]);
        drawableObjects.push_back(bezierSurface->controlPoints[i]);
    }
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

void DrawableObjectsData::addPointToBSpline(BSpline * bSpline, Point * point)
{
    bool add = true;
    for(int i=0;i<bSpline->deBoorPoints.size();i++)
    {
        if(bSpline->deBoorPoints[i]->name == point->name)
        {
            add = false;
        }
    }
    if(add)
    {
        bSpline->deBoorPoints.push_back(point);
    }
}

void DrawableObjectsData::addPointToInterBSpline(InterBSpline * interBSpline, Point * point)
{
    bool add = true;
    for(int i=0;i<interBSpline->deBoorPoints.size();i++)
    {
        if(interBSpline->deBoorPoints[i]->name == point->name)
        {
            add = false;
        }
    }
    if(add)
    {
        interBSpline->deBoorPoints.push_back(point);
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

    for(int i=0; i<bSplineList.size();i++)
    {
        bSplineList[i]->removePointByName(name);
    }

    for(int i=0; i<interBSplineList.size();i++)
    {
        interBSplineList[i]->removePointByName(name);
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

void DrawableObjectsData::removeBSplineByName(std::string name)
{
    for(int i=0; i<bSplineList.size();i++){
        if(bSplineList[i]->name == name)
        {
            removeBSpline(bSplineList[i]);
            break;
        }
    }
}

void DrawableObjectsData::removeInterBSplineByName(std::string name)
{
    for(int i=0; i<interBSplineList.size();i++){
        if(interBSplineList[i]->name == name)
        {
            removeInterBSpline(interBSplineList[i]);
            break;
        }
    }
}

void DrawableObjectsData::removeBezierSurfaceByName(std::string name)
{

    for(int i=0; i<bezierSurfaceList.size();i++){
        if(bezierSurfaceList[i]->name == name)
        {
            for(int j=0;j<bezierSurfaceList[i]->controlPoints.size();j++)
            {
                removePoint(bezierSurfaceList[i]->controlPoints[j]);
            }
            removeBezierSurface(bezierSurfaceList[i]);
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

void DrawableObjectsData::selectBSplineByName(std::string name)
{
    for(int i=0; i<bSplineList.size();i++){
        if(bSplineList[i]->name == name)
        {
            bSplineList[i]->isSelected = true;
            break;
        }
    }
}

void DrawableObjectsData::selectInterBSplineByName(std::string name)
{
    for(int i=0; i<interBSplineList.size();i++){
        if(interBSplineList[i]->name == name)
        {
            interBSplineList[i]->isSelected = true;
            break;
        }
    }
}

void DrawableObjectsData::selectBezierSurfaceByName(std::string name)
{
    for(int i=0; i<bezierSurfaceList.size();i++){
        if(bezierSurfaceList[i]->name == name)
        {
            bezierSurfaceList[i]->isSelected = true;
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

BSpline* DrawableObjectsData::getBSplineByName(std::string name)
{
    for(int i=0; i<bSplineList.size();i++){
        if(bSplineList[i]->name == name)
        {
            return bSplineList[i];
        }
    }
}

InterBSpline* DrawableObjectsData::getInterBSplineByName(std::string name)
{
    for(int i=0; i<interBSplineList.size();i++){
        if(interBSplineList[i]->name == name)
        {
            return interBSplineList[i];
        }
    }
}

BezierSurface* DrawableObjectsData::getBezierSurfaceByName(std::string name)
{
    for(int i=0; i<bezierSurfaceList.size();i++){
        if(bezierSurfaceList[i]->name == name)
        {
            return bezierSurfaceList[i];
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

void DrawableObjectsData::deselectBSplines()
{
    for(int i=0; i<bSplineList.size();i++){
        bSplineList[i]->isSelected = false;
    }
}

void DrawableObjectsData::deselectInterBSplines()
{
    for(int i=0; i<interBSplineList.size();i++){
        interBSplineList[i]->isSelected = false;
    }
}

void DrawableObjectsData::deselectBezierSurface()
{
    for(int i=0; i<bezierSurfaceList.size();i++){
        bezierSurfaceList[i]->isSelected = false;
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

void DrawableObjectsData::removeBSpline(BSpline * bSpline)
{
    std::vector<BSpline*>::iterator position = std::find(bSplineList.begin(), bSplineList.end(), bSpline);
        if (position != bSplineList.end()) // == myVector.end() means the element was not found
            bSplineList.erase(position);
            initDrawableObjectsList();
}

void DrawableObjectsData::removeInterBSpline(InterBSpline * interBSpline)
{
    std::vector<InterBSpline*>::iterator position = std::find(interBSplineList.begin(), interBSplineList.end(), interBSpline);
        if (position != interBSplineList.end()) // == myVector.end() means the element was not found
            interBSplineList.erase(position);
            initDrawableObjectsList();
}

void DrawableObjectsData::removeBezierSurface(BezierSurface * bezierSurface)
{
    std::vector<BezierSurface*>::iterator position = std::find(bezierSurfaceList.begin(), bezierSurfaceList.end(), bezierSurface);
        if (position != bezierSurfaceList.end()) // == myVector.end() means the element was not found
            bezierSurfaceList.erase(position);
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

    for(int i=0;i<bSplineList.size();i++)
    {
        drawableObjects.push_back(bSplineList.at(i));
    }

    for(int i=0;i<interBSplineList.size();i++)
    {
        drawableObjects.push_back(interBSplineList.at(i));
    }

    for(int i=0;i<bezierSurfaceList.size();i++)
    {
        drawableObjects.push_back(bezierSurfaceList.at(i));
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
