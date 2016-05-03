#include "bezierpatch.h"

BezierPatch::BezierPatch()
{

}

BezierPatch::BezierPatch(Camera *camera)
{
    this->camera = camera;
    width = 0.2f;
    height = 0.2f;
    u=0.25f;
    v=0.25f;

  /*  float widthDT = width / 3;
    float heightDT = height / 3;

    int m=0,n=0;
    for(float i = -(width/(float)2);i< width/(float)2+widthDT/2;i+=widthDT,m++)
    {
        n=0;
        for(float j = -(height/(float)2);j< height/(float)2+heightDT/2;j+=heightDT,n++)
        {
            controlPoints[m][n] = new Point(camera);
            controlPoints[m][n]->xPos = i;
            controlPoints[m][n]->updateTranslationMatX();
            controlPoints[m][n]->yPos = j;
            controlPoints[m][n]->updateTranslationMatY();
        }
    }*/
}

void BezierPatch::draw()
{
    for(int i=0;i<4;i++)
    {
        for(int j=0;j<4;j++)
        {
            controlPoints[i][j]->draw();
        }
    }
    float dt=0.01;
    glPointSize(1);
    glBegin(GL_POINTS);

    //draw columns
    for(float i=0;i<1.01f;i+=u)
    {
        for(float j=0;j<1.f;j+=dt)
        {
            pointToDraw = computePoint(i,j);
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
            pointToDraw = computePoint(j,i);
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
        return pow((1-u),3);
        break;
    case 1:
        return 3*u*pow(1-u,2);
        break;
    case 2:
        return 3*u*u*(1-u);
        break;
    case 3:
        return pow(u,3);
        break;
    }
}

vec4 BezierPatch::computePoint(float u, float v)
{
    tmp = vec4(0,0,0,0);

    for(int i=0;i<4;i++)
    {
        for(int j=0;j<4;j++)
        {
            tmp += controlPoints[i][j]->localTransPointCoordinates*berBasis(i,u)*berBasis(j,v);
        }
    }
    tmp.w = 1;
    return tmp;
}

