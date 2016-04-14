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

void BezierCurve::removePointByName(string name)
{
    for(int i=0; i<pointVector.size();i++){
        if(pointVector[i]->name == name)
        {
            std::vector<Point*>::iterator position = std::find(pointVector.begin(), pointVector.end(), pointVector[i]);
                if (position != pointVector.end()) // == myVector.end() means the element was not found
                    pointVector.erase(position);
            break;
        }
    }
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

int BezierCurve::twoPointsDist(Point* p1, Point* p2)
{
    int inPixVal = 0;

    if(camera->screenWidth > camera->screenHeight)
    {
        inPixVal = camera->screenHeight;
    }
    else
    {
        inPixVal = camera->screenWidth;
    }

    return inPixVal *sqrt(pow(p1->transPointCoordinates.x - p2->transPointCoordinates.x,2) +
                          pow(p1->transPointCoordinates.y - p2->transPointCoordinates.y,2) +
                          pow(p1->transPointCoordinates.z - p2->transPointCoordinates.z,2) );
}

void BezierCurve::oneDimBezier0C(Point* p1, Point* p2, int pointNum)
{
    float distanceT = 1.f/(float)pointNum;
    float t = 0.f;

    for(int i=0;i<pointNum;i++)
    {

           float x = (p1->localTransPointCoordinates.x * (1-t)) + (p2->localTransPointCoordinates.x * t);
           float y = (p1->localTransPointCoordinates.y * (1-t)) + (p2->localTransPointCoordinates.y * t);
           float z = (p1->localTransPointCoordinates.z * (1-t)) + (p2->localTransPointCoordinates.z * t);

           pointToDraw = vec4(x,y,z,1);
           pointToDraw = camera->transformationMatrix * pointToDraw;
           pointToDraw.x /= pointToDraw.w;
           pointToDraw.y /= pointToDraw.w;
           pointToDraw.x /= camera->xRatio;
           pointToDraw.y /= camera->yRatio;
           glVertex2f(pointToDraw.x,pointToDraw.y);
           t += distanceT;
    }

}

void BezierCurve::twoDimBezier0C(Point* p1, Point* p2, Point* p3, int pointNum)
{
    float distanceT = 1.f/(float)pointNum;
    float t = 0.f;

    for(int i=0;i<pointNum;i++)
    {

        float t2 = t*t;

            float B0 = pow(1-t, 2);
            float B1 = (2*t - 2*t2);
            float B2 = t2;

            float x = (p1->localTransPointCoordinates.x * B0) + (p2->localTransPointCoordinates.x * B1) + (p3->localTransPointCoordinates.x * B2);
            float y = (p1->localTransPointCoordinates.y * B0) + (p2->localTransPointCoordinates.y* B1) + (p3->localTransPointCoordinates.y * B2);
            float z = (p1->localTransPointCoordinates.z * B0) + (p2->localTransPointCoordinates.z * B1) + (p3->localTransPointCoordinates.z * B2);

           pointToDraw = vec4(x,y,z,1);
           pointToDraw = camera->transformationMatrix * pointToDraw;
           pointToDraw.x /= pointToDraw.w;
           pointToDraw.y /= pointToDraw.w;
           pointToDraw.x /= camera->xRatio;
           pointToDraw.y /= camera->yRatio;
           glVertex2f(pointToDraw.x,pointToDraw.y);
           t += distanceT;
    }
}

void BezierCurve::threeDimBezier0C(Point* p1, Point* p2, Point* p3, Point* p4, int pointNum)
{
        float distanceT = 1.f/(float)pointNum;
        float t = 0.f;

        for(int i=0;i<pointNum;i++)
        {

            float t2 = t*t;

                float x = pow(1-t, 3) * p1->localTransPointCoordinates.x +
                          pow(1-t, 2) * 3*t * p2->localTransPointCoordinates.x +
                        (1-t) * 3 *t *t * p3->localTransPointCoordinates.x +
                        t*t*t*p4->localTransPointCoordinates.x;
                float y = pow(1-t, 3) * p1->localTransPointCoordinates.y +
                          pow(1-t, 2) * 3*t * p2->localTransPointCoordinates.y +
                          (1-t) * 3 *t *t * p3->localTransPointCoordinates.y +
                          t*t*t*p4->localTransPointCoordinates.y;
                float z = pow(1-t, 3) * p1->localTransPointCoordinates.z +
                          pow(1-t, 2) * 3*t * p2->localTransPointCoordinates.z +
                          (1-t) * 3 *t *t * p3->localTransPointCoordinates.z +
                          t*t*t*p4->localTransPointCoordinates.z;

               pointToDraw = vec4(x,y,z,1);
               pointToDraw = camera->transformationMatrix * pointToDraw;
               pointToDraw.x /= pointToDraw.w;
               pointToDraw.y /= pointToDraw.w;
               pointToDraw.x /= camera->xRatio;
               pointToDraw.y /= camera->yRatio;
               glVertex2f(pointToDraw.x,pointToDraw.y);
               t += distanceT;
        }
}
