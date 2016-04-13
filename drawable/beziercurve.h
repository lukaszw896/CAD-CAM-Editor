#ifndef BEZIERCURVE_H
#define BEZIERCURVE_H
#include "drawable/drawable.h"
#include "point.h"
#include "Camera/camera.h"
#include "glm/vec4.hpp"
#include "glm/mat4x4.hpp"
#include <vector>
#include <GL/gl.h>
using namespace std;
using namespace glm;

class BezierCurve: public Drawable
{
public:
    BezierCurve();
    BezierCurve(Camera* camera);
    vector<Point*> pointVector;
private:

    static int id;
    bool drawPolygon;

    Camera* camera;



    vector<glm::vec4> curvePointsCoordinates;
    vector<glm::vec4> curveTransPointsCooridnates;
    vector<int> sectionPointNum;

    glm::vec4 leftEyeCurveTransPointCoordinate;
    glm::vec4 rightEyeCurveTransPointCoordinate;

    glm::vec4 pointToDraw;

   // glm::mat4 localTransformationMatrix;
    ///In this case I need only camera transformation matrix because any transformation is made of points building curve
    glm::mat4 globalTransformationMatrix;

    int numberOfPoints;

    int twoPointsDist(Point* p1, Point* p2)
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

        //some synchronization is needed...
        if(p1 == NULL || p2 ==NULL)
        {
            return 0;
        }

        return inPixVal *sqrt(pow(p1->transPointCoordinates.x - p2->transPointCoordinates.x,2) +
                              pow(p1->transPointCoordinates.y - p2->transPointCoordinates.y,2) +
                              pow(p1->transPointCoordinates.z - p2->transPointCoordinates.z,2) );
    }

    int polygonLength(Point* p1, Point* p2 )
    {
        return twoPointsDist(p1,p2);
    }

    int polygonLength(Point* p1, Point* p2, Point* p3 )
    {
        return (twoPointsDist(p1,p2) + twoPointsDist(p2,p3) + twoPointsDist(p3,p1));
    }

    int polygonLength(Point* p1, Point* p2, Point* p3, Point* p4 )
    {
        return (twoPointsDist(p1,p2) + twoPointsDist(p2,p3) + twoPointsDist(p3,p4) + twoPointsDist(p4,p1));
    }

    void oneDimBezier0C(Point* p1, Point* p2, int pointNum)
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

    void twoDimBezier0C(Point* p1, Point* p2, Point* p3, int pointNum)
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

    void threeDimBezier0C(Point* p1, Point* p2, Point* p3, Point* p4, int pointNum)
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

    void transform();
    void draw();
};

#endif // BEZIERCURVE_H
