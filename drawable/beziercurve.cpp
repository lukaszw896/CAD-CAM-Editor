#include "beziercurve.h"
#include <GL/gl.h>

BezierCurve::BezierCurve()
{

}

BezierCurve::BezierCurve(Camera *camera)
{
    this->camera = camera;
    drawPolygon = false;
    id++;
    name = "BezierCurve_";
    name += std::to_string(id);

    globalTransformationMatrix = camera->transformationMatrix;
}

int BezierCurve::id = 0;

void BezierCurve::draw()
{
    if(drawPolygon)
    {
        glPointSize(1);
        glBegin(GL_LINES);
        glColor4f(1,1.0, 1.0,1.0);
        if(pointVector.size()!=0){
            for(int i=0;i<pointVector.size()-1;i++)
            {
                glVertex2f(pointVector[i]->transPointCoordinates.x,pointVector[i]->transPointCoordinates.y);
                glVertex2f(pointVector[i+1]->transPointCoordinates.x,pointVector[i+1]->transPointCoordinates.y);
            }
        }
        glEnd();
    }

    curvePointsCoordinates.clear();
    sectionPointNum.clear();

    int numOfPointsInLastSection = 0;
    //calculate the number of points for each section
    if(pointVector.size() != 0)
    {
        int i = 0;
        if(pointVector.size() > 3)
        {
            sectionPointNum.push_back(polygonLength(pointVector[i],pointVector[i+1],pointVector[i+2],pointVector[i+3]));
            i=6;
            int tmp = pointVector.size();
            for(i;i<tmp;i+=3)
            {
                sectionPointNum.push_back(polygonLength(pointVector[i],pointVector[i-1],pointVector[i-2],pointVector[i-3]));
            }
            switch((2+pointVector.size()-i)%3)
            {
            case 0:
                numOfPointsInLastSection = 0;
                break;
            case 1:
                sectionPointNum.push_back(polygonLength(pointVector[i-3],pointVector[i-2]));
                numOfPointsInLastSection = 1;
                break;
            case 2:
                sectionPointNum.push_back(polygonLength(pointVector[i-3],pointVector[i-2],pointVector[i-1]));
                numOfPointsInLastSection = 2;
                break;
            }
        }
        else
        {
            switch(pointVector.size()%4)
            {
            case 0:
                numOfPointsInLastSection = 0;
                break;
            case 1:
                numOfPointsInLastSection = 0;
                break;
            case 2:
                numOfPointsInLastSection = 2;
                sectionPointNum.push_back(polygonLength(pointVector[0],pointVector[1]));
                break;
            case 3:
                numOfPointsInLastSection = 3;
                sectionPointNum.push_back(polygonLength(pointVector[0],pointVector[1],pointVector[2]));
                break;
            }
        }
    }
    //calculate sum of points for curve and resize vector
    numberOfPoints = 0;
    for(int i=0;i<sectionPointNum.size();i++)
    {
        numberOfPoints += sectionPointNum[i];
    }

    //curvePointsCoordinates.resize(numberOfPoints);

    //calculate position of each point and draw it
    glPointSize(1);
    glBegin(GL_POINTS);
    glColor4f(1,1.0, 1.0,1.0);
    int i=0;
    if(pointVector.size() > 3)
    {
        int tmp = sectionPointNum.size()-1;
        for(i=0;i<tmp;i++)
        {
            threeDimBezier0C(pointVector[i*3+0],pointVector[i*3+1],pointVector[i*3+2],pointVector[i*3+3],sectionPointNum[i]);
        }
        switch(numOfPointsInLastSection)
        {
           case 0:
            threeDimBezier0C(pointVector[i*3+0],pointVector[i*3+1],pointVector[i*3+2],pointVector[i*3+3],sectionPointNum[i]);
            break;

        case 1:
            oneDimBezier0C(pointVector[i*3+0],pointVector[i*3+1],sectionPointNum[i]);
            break;

        case 2:
            twoDimBezier0C(pointVector[i*3+0],pointVector[i*3+1],pointVector[i*3+2],sectionPointNum[i]);
            break;

        }
    }
    else
    {
        switch(numOfPointsInLastSection)
        {
           case 0:
            break;

        case 1:
         break;

        case 2:
            oneDimBezier0C(pointVector[i*3+0],pointVector[i*3+1],sectionPointNum[i]);
            break;

        case 3:
            twoDimBezier0C(pointVector[i*3+0],pointVector[i*3+1],pointVector[i*3+2],sectionPointNum[i]);
            break;

        }
    }

    glEnd();

    ////// Drawing BezierCurve

}
