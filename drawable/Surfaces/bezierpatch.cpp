#include "bezierpatch.h"


BezierPatch::BezierPatch()
{

}

BezierPatch::BezierPatch(Camera *camera)
{
    this->camera = camera;
    pixelVector.resize(2000);
    leftEyePixelVector.resize(2000);
    rightEyePixelVector.resize(2000);
    u=0.25f;
    v=0.25f;
}

void BezierPatch::calculatePoints()
{
    float dt=0.06;
    pointCounter = 0;
    //draw columns
    for(float i=0;i<1.01f;i+=u)
    {
        for(float j=0;j<1.f;j+=dt)
        {
            pointToDraw = vec4(computePoint(i,j),1);
            if(!camera->isStereoscopic){
                pointToDraw = camera->transformationMatrix* pointToDraw;
                pointToDraw.x = pointToDraw.x / pointToDraw.w;
                pointToDraw.y = pointToDraw.y / pointToDraw.w;
                pointToDraw.x /= camera->xRatio;
                pointToDraw.y /= camera->yRatio;
                pixelVector[pointCounter] = vec4(pointToDraw);
                pointCounter++;

            }
            else{
                vec4 point2 = vec4(pointToDraw);
                pointToDraw = camera->transformationMatrixLeftEye * pointToDraw;
                pointToDraw.x /= pointToDraw.w;
                pointToDraw.y /= pointToDraw.w;
                pointToDraw.x /= camera->xRatio;
                pointToDraw.y /= camera->yRatio;
                leftEyePixelVector[pointCounter] = vec4(pointToDraw);

                point2 = camera->transformationMatrixRightEye * point2;
                point2.x /= point2.w;
                point2.y /= point2.w;
                point2.x /= camera->xRatio;
                point2.y /= camera->yRatio;
                rightEyePixelVector[pointCounter] = vec4(point2);
                pointCounter++;
            }
        }
    }

    for(float i=0;i<1.01f;i+=v)
    {
        for(float j=0;j<1.f;j+=dt)
        {
            pointToDraw = vec4(computePoint(j,i),1);
                if(!camera->isStereoscopic){
                    pointToDraw = camera->transformationMatrix* pointToDraw;
                    pointToDraw.x = pointToDraw.x / pointToDraw.w;
                    pointToDraw.y = pointToDraw.y / pointToDraw.w;
                    pointToDraw.x /= camera->xRatio;
                    pointToDraw.y /= camera->yRatio;
                    pixelVector[pointCounter] = vec4(pointToDraw);
                    pointCounter++;
                }
                else{
                    vec4 point2 = vec4(pointToDraw);
                    pointToDraw = camera->transformationMatrixLeftEye * pointToDraw;
                    pointToDraw.x /= pointToDraw.w;
                    pointToDraw.y /= pointToDraw.w;
                    pointToDraw.x /= camera->xRatio;
                    pointToDraw.y /= camera->yRatio;
                    leftEyePixelVector[pointCounter] = vec4(pointToDraw);

                    point2 = camera->transformationMatrixRightEye * point2;
                    point2.x /= point2.w;
                    point2.y /= point2.w;
                    point2.x /= camera->xRatio;
                    point2.y /= camera->yRatio;
                    rightEyePixelVector[pointCounter] = vec4(point2);
                    pointCounter++;
                }
        }
    }
}

void BezierPatch::draw()
{
    glPointSize(-50/camera->zPos - (5.f-camera->rProjection)/5);

    glPointSize(1);
    glBegin(GL_POINTS);
    glColor3f(1.0,1.0,0.8);
    //draw columns
    for(int i=0;i<pointCounter;i++){
        if(!camera->isStereoscopic){
            glVertex2f(pixelVector[i].x,pixelVector[i].y);
        }
        else{
            glColor3f(0.4,0.0, 0.0);
            if(!(pointToDraw.w >=-0.06)) // clip
                glVertex2f(leftEyePixelVector[i].x, leftEyePixelVector[i].y);

            glColor3f(0, 0.5, 0.5);
            if(!(rightEyePixelVector[i].w >=-0.06)) // clip
                glVertex2f(rightEyePixelVector[i].x, rightEyePixelVector[i].y);
        }
    }
    glEnd();
}

float BezierPatch::berBasis(int i, float u)
{
    switch(i)
    {
    case 0:
        return -u*u*u+3*u*u-3*u+1;
        break;
    case 1:
        return 3*u - 6*u*u + 3*u*u*u;
        break;
    case 2:
        return 3*u*u- 3*u*u*u;
        break;
    case 3:
        return u*u*u;
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
