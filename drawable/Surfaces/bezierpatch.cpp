#include "bezierpatch.h"


BezierPatch::BezierPatch()
{

}

BezierPatch::BezierPatch(Camera *camera)
{
    this->camera = camera;
    pixelVector.resize(10000);
    u=0.25f;
    v=0.25f;

}

void BezierPatch::draw()
{
    glPointSize(-50/camera->zPos - (5.f-camera->rProjection)/5);
   /* for(int i=0;i<4;i++)
    {
        for(int j=0;j<4;j++)
        {
            controlPoints[i][j]->draw();
        }
    }*/
    float dt=0.01;
    /*float pixNum;
    if(camera->screenWidth > camera->screenHeight){
        pixNum = camera->screenHeight;
    }
    else{
        pixNum = camera->screenWidth;
    }
    float length = getMaxLength();
    dt = 1.0f/pixNum/length/2;*/
    glPointSize(1);
    glBegin(GL_POINTS);
    glColor3f(1.0,1.0,0.8);
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
                glVertex2f(pointToDraw.x,pointToDraw.y);
            }
            else{
                vec4 point2 = vec4(pointToDraw);
                glColor3f(0.4,0.0, 0.0);
                pointToDraw = camera->transformationMatrixLeftEye * pointToDraw;
                pointToDraw.x /= pointToDraw.w;
                pointToDraw.y /= pointToDraw.w;
                pointToDraw.x /= camera->xRatio;
                pointToDraw.y /= camera->yRatio;

                if(!(pointToDraw.w >=-0.06)) // clip
                    glVertex2f(pointToDraw.x, pointToDraw.y);

                glColor3f(0, 0.5, 0.5);
                point2 = camera->transformationMatrixRightEye * point2;
                point2.x /= point2.w;
                point2.y /= point2.w;
                point2.x /= camera->xRatio;
                point2.y /= camera->yRatio;

                if(!(point2.w >=-0.06)) // clip
                    glVertex2f(point2.x, point2.y);
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
                    glVertex2f(pointToDraw.x,pointToDraw.y);
                }
                else{
                    vec4 point2 = vec4(pointToDraw);
                    glColor3f(0.4,0.0, 0.0);
                    pointToDraw = camera->transformationMatrixLeftEye * pointToDraw;
                    pointToDraw.x /= pointToDraw.w;
                    pointToDraw.y /= pointToDraw.w;
                    pointToDraw.x /= camera->xRatio;
                    pointToDraw.y /= camera->yRatio;

                    if(!(pointToDraw.w >=-0.06)) // clip
                        glVertex2f(pointToDraw.x, pointToDraw.y);

                    glColor3f(0, 0.5, 0.5);
                    point2 = camera->transformationMatrixRightEye * point2;
                    point2.x /= point2.w;
                    point2.y /= point2.w;
                    point2.x /= camera->xRatio;
                    point2.y /= camera->yRatio;

                    if(!(point2.w >=-0.06)) // clip
                        glVertex2f(point2.x, point2.y);
                }
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

/*void calcU(float i, float bottomT, float upperT)
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
        }
        else{
            vec4 point2 = vec4(pointToDraw);
            pointToDraw = camera->transformationMatrixLeftEye * pointToDraw;
            pointToDraw.x /= pointToDraw.w;
            pointToDraw.y /= pointToDraw.w;
            pointToDraw.x /= camera->xRatio;
            pointToDraw.y /= camera->yRatio;

            point2 = camera->transformationMatrixRightEye * point2;
            point2.x /= point2.w;
            point2.y /= point2.w;
            point2.x /= camera->xRatio;
            point2.y /= camera->yRatio;
        }
    }
}
*/
