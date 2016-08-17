#include "drawableobjectsdata.h"

DrawableObjectsData& DrawableObjectsData::getInstance()
{

        static DrawableObjectsData instance; // Guaranteed to be destroyed.
                                             // Instantiated on first use.
        return instance;
}

DrawableObjectsData::DrawableObjectsData(){}

void DrawableObjectsData::addObject(DrawableType drawableType, Drawable *drawable)
{
    assignDrawableObjectsListToContainer(drawableType);
    drawableObjectsContainer.push_back(drawable);
    allDrawableObjects.push_back(drawable);
    assignContainerToDrawableObjectsList();
}


void DrawableObjectsData::addPoint(Point* point)
{
   for(unsigned int i=0;i<pointList.size();i++)
   {
       if(pointList[i]->name == point->name)return;
   }

   for(unsigned int i=0;i<bezierCurveList.size();i++)
   {
       if(bezierCurveList[i]->isSelected)
       {
           ((BezierCurve*)bezierCurveList[i])->pointVector.push_back(point);
       }
   }

   for(unsigned int i=0;i<bSplineList.size();i++)
   {
       if(bSplineList[i]->isSelected)
       {
           ((BSpline*)bSplineList[i])->deBoorPoints.push_back(point);
       }
   }

   for( unsigned int i=0;i<interBSplineList.size();i++)
   {
       if(interBSplineList[i]->isSelected)
       {
           ((InterBSpline*)interBSplineList[i])->deBoorPoints.push_back(point);
       }
   }

   pointList.push_back(point);
   allDrawableObjects.push_back(point);
}

void DrawableObjectsData::addCursor(Cursor * cursor)
{
    this->cursor = cursor;
    allDrawableObjects.push_back(cursor);
}

void DrawableObjectsData::addBezierSurface(BezierSurface * bezierSurface)
{
    bezierSurfaceList.push_back(bezierSurface);
    allDrawableObjects.push_back(bezierSurface);

    if(!bezierSurface->isDeBoorControled){
        for(int i=0;i<bezierSurface->controlPoints.size();i++)
        {
            bezierSurface->controlPoints[i]->isRemovable = false;
            this->addPoint(bezierSurface->controlPoints[i]);
            /*pointList.push_back(bezierSurface->controlPoints[i]);
            drawableObjects.push_back(bezierSurface->controlPoints[i]);*/
        }
    }else{
        for(int i=0;i<bezierSurface->deBoorePoints.size();i++)
        {
            bezierSurface->deBoorePoints[i]->isRemovable = false;
            this->addPoint(bezierSurface->deBoorePoints[i]);
            //pointList.push_back(bezierSurface->deBoorePoints[i]);
           // drawableObjects.push_back(bezierSurface->deBoorePoints[i]);
        }
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

void DrawableObjectsData::removeObjectByName(DrawableType drawableType,string name)
{
    assignDrawableObjectsListToContainer(drawableType);
    for(unsigned int i=0;i<drawableObjectsContainer.size();i++)
    {
        if(drawableObjectsContainer[i]->name == name)
        {
            removeObject(drawableType,drawableObjectsContainer[i]);
        }
    }
    assignContainerToDrawableObjectsList();
}

void DrawableObjectsData::removePointByName(std::string name)
{
    for(int i=0;i<bezierCurveList.size();i++)
    {
        ((BezierCurve*)bezierCurveList[i])->removePointByName(name);
    }

    for(int i=0; i<bSplineList.size();i++)
    {
        ((BSpline*)bSplineList[i])->removePointByName(name);
    }

    for(int i=0; i<interBSplineList.size();i++)
    {
        ((InterBSpline*)interBSplineList[i])->removePointByName(name);
    }

    for(int i=0; i<pointList.size();i++){
        if(pointList[i]->name == name)
        {
            removeObject(POINT,pointList[i]);
            break;
        }
    }
}

void DrawableObjectsData::removeBezierSurfaceByName(std::string name)
{

    for(int i=0; i<bezierSurfaceList.size();i++){
        if(bezierSurfaceList[i]->name == name)
        {
            if(!((BezierSurface*)bezierSurfaceList[i])->isDeBoorControled){
                for(int j=0;j<((BezierSurface*)bezierSurfaceList[i])->controlPoints.size();j++)
                {
                    ((BezierSurface*)bezierSurfaceList[i])->controlPoints[j]->isRemovable = true;
                    removeObject(POINT,((BezierSurface*)bezierSurfaceList[i])->controlPoints[j]);
                }
            }else
            {
                for(int j=0;j<((BezierSurface*)bezierSurfaceList[i])->deBoorePoints.size();j++)
                {
                    ((BezierSurface*)bezierSurfaceList[i])->deBoorePoints[j]->isRemovable = true;
                    removeObject(POINT,((BezierSurface*)bezierSurfaceList[i])->deBoorePoints[j]);
                }
            }
            removeObject(BEZIERSURFACE,(BezierSurface*)bezierSurfaceList[i]);
            break;
        }
    }
}

void DrawableObjectsData::selectObjectByName(DrawableType drawableType, string name)
{
    assignDrawableObjectsListToContainer(drawableType);
    for(unsigned int i=0; i<drawableObjectsContainer.size();i++)
    {
        if(drawableObjectsContainer[i]->name == name){
            drawableObjectsContainer[i]->isSelected = true;
            break;
        }
    }
}

Drawable* DrawableObjectsData::getObjectByName(DrawableType drawableType, string name)
{
    assignDrawableObjectsListToContainer(drawableType);
    for(unsigned int i=0;i<drawableObjectsContainer.size();i++)
    {
        if(drawableObjectsContainer[i]->name == name)
        {
            return drawableObjectsContainer[i];
        }
    }
}

void DrawableObjectsData::deselectObjects(DrawableType drawableType)
{
    assignDrawableObjectsListToContainer(drawableType);
    for(unsigned int i=0; i<drawableObjectsContainer.size();i++)
    {
        drawableObjectsContainer[i]->isSelected = false;
    }
}

void DrawableObjectsData::removeObject(DrawableType drawableType, Drawable *drawable)
{
    assignDrawableObjectsListToContainer(drawableType);
    //TODO if(drawable->isRemovable){
    vector<Drawable*>::iterator position = find(drawableObjectsContainer.begin(),drawableObjectsContainer.end(),drawable);
    if(position != drawableObjectsContainer.end())
    {
        drawableObjectsContainer.erase(position);
    }
    assignContainerToDrawableObjectsList();
    initDrawableObjectsList();
}

void DrawableObjectsData::initDrawableObjectsList()
{
    allDrawableObjects.clear();
    allDrawableObjects.push_back(cursor);
    for(int i=0;i<pointList.size();i++)
    {
        allDrawableObjects.push_back(pointList.at(i));
    }

    for(int i=0;i<torusList.size();i++)
    {
        allDrawableObjects.push_back(torusList.at(i));
    }

    for(int i=0;i<bezierCurveList.size();i++)
    {
        allDrawableObjects.push_back(bezierCurveList.at(i));
    }

    for(int i=0;i<bSplineList.size();i++)
    {
        allDrawableObjects.push_back(bSplineList.at(i));
    }

    for(int i=0;i<interBSplineList.size();i++)
    {
        allDrawableObjects.push_back(interBSplineList.at(i));
    }

    for(int i=0;i<bezierSurfaceList.size();i++)
    {
        allDrawableObjects.push_back(bezierSurfaceList.at(i));
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
    for(int i=1;i<allDrawableObjects.size();i++)
    {
       float distance;
       distance = sqrt(pow(cursor->xPos-allDrawableObjects[i]->xPos,2)
                       +pow(cursor->yPos-allDrawableObjects[i]->yPos,2)
                       +pow(cursor->zPos-allDrawableObjects[i]->zPos,2));
       if(distance<0.05f)
       {
           return allDrawableObjects[i];
       }
    }
    return NULL;
}

Point* DrawableObjectsData::findPointBySceneClick(QPoint screenPos, QPoint screenSize)
{
    double tmpXPos,tmpYPos;
    for(int i=0;i<pointList.size();i++){
        tmpXPos = screenSize.x() * (((Point*)pointList[i])->transPointCoordinates.x+1.0)/2;
        tmpYPos = screenSize.y() - screenSize.y() * (((Point*)pointList[i])->transPointCoordinates.y+1.0)/2;
        float distance = sqrt(pow(screenPos.x() - tmpXPos,2)+pow(screenPos.y() - tmpYPos,2));
        if(distance < 10)
        {
             return (Point*)pointList[i];
        }
    }
    return NULL;
}


int DrawableObjectsData::getPointListIndex(Point * point)
{
    for(int i=0;i<pointList.size();i++)
    {
        if(pointList[i]->name == point->name) return i;
    }
    return -1;
}

void DrawableObjectsData::assignDrawableObjectsListToContainer(DrawableType drawableType)
{
    if(currentDrawableObject == drawableType)
    {
        return;
    }
    else
    {
        currentDrawableObject = drawableType;
        switch(currentDrawableObject)
        {
        case TORUS:
            drawableObjectsContainer = torusList;
            break;
        case POINT:
            drawableObjectsContainer = pointList;
            break;
        case BEZIERCURVE:
            drawableObjectsContainer = bezierCurveList;
            break;
        case BSPLINE:
            drawableObjectsContainer = bSplineList;
            break;
        case INTERPBSPLINE:
            drawableObjectsContainer = interBSplineList;
            break;
        case BEZIERSURFACE:
            drawableObjectsContainer = bezierSurfaceList;
            break;
       }
    }
}

void DrawableObjectsData::assignContainerToDrawableObjectsList()
{
    switch(currentDrawableObject)
    {
    case TORUS:
        torusList = drawableObjectsContainer;
        break;
    case POINT:
        pointList = drawableObjectsContainer;
        break;
    case BEZIERCURVE:
        bezierCurveList = drawableObjectsContainer;
        break;
    case BSPLINE:
        bSplineList = drawableObjectsContainer;
        break;
    case INTERPBSPLINE:
        interBSplineList = drawableObjectsContainer;
        break;
    case BEZIERSURFACE:
        bezierSurfaceList = drawableObjectsContainer;
        break;
   }
}
