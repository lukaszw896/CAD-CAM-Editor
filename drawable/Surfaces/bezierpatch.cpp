#include "bezierpatch.h"


BezierPatch::BezierPatch()
{

}

BezierPatch::BezierPatch(Camera *camera)
{
    this->camera = camera;

    u=0.25f;
    v=0.25f;

}

void BezierPatch::draw()
{
    glPointSize(-50/camera->zPos - (5.f-camera->rProjection)/5);
    for(int i=0;i<4;i++)
    {
        for(int j=0;j<4;j++)
        {
            controlPoints[i][j]->draw();
        }
    }
    float dt=0.008;
    glPointSize(1);
    glBegin(GL_POINTS);

    //draw columns
    for(float i=0;i<1.01f;i+=u)
    {
        for(float j=0;j<1.f;j+=dt)
        {
            pointToDraw = vec4(computePoint(i,j),1);
            pointToDraw = camera->transformationMatrix* pointToDraw;
            pointToDraw.x = pointToDraw.x / pointToDraw.w;
            pointToDraw.y = pointToDraw.y / pointToDraw.w;
            pointToDraw.x /= camera->xRatio;
            pointToDraw.y /= camera->yRatio;
            glVertex2f(pointToDraw.x,pointToDraw.y);
        }
    }

    for(float i=0;i<1.01f;i+=v)
    {
        for(float j=0;j<1.f;j+=dt)
        {
            pointToDraw = vec4(computePoint(j,i),1);
            pointToDraw = camera->transformationMatrix* pointToDraw;
            pointToDraw.x = pointToDraw.x / pointToDraw.w;
            pointToDraw.y = pointToDraw.y / pointToDraw.w;
            pointToDraw.x /= camera->xRatio;
            pointToDraw.y /= camera->yRatio;
            glVertex2f(pointToDraw.x,pointToDraw.y);
        }
    }

    //draw rows
    glEnd();
}

float BezierPatch::berBasis(int i, float u)
{
    switch(i)
    {
    case 0:
        return -u*u*u+3*u*u-3*u+1;
        //return pow((1-u),3);
        break;
    case 1:
        return 3*u - 6*u*u + 3*u*u*u;
        ///return 3*u*pow(1-u,2);
        break;
    case 2:
        return 3*u*u- 3*u*u*u;
        //return 3*u*u*(1-u);
        break;
    case 3:
        return u*u*u;
       // return pow(u,3);
        break;
    }
}

vec3 BezierPatch::computePoint(float u, float v)
{
    tmp = vec3(0,0,0);
    for(int i=0;i<4;i++)
    {
        for(int j=0;j<4;j++)
        {

                tmp += controlPoints[i][j]->localTransPointCoordinates*berBasis(i,u)*berBasis(j,v);
        }
    }
    return tmp;
}

