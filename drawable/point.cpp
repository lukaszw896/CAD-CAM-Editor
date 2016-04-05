#include "point.h"
#include <GL/gl.h>

Point::Point()
{

}
Point::Point(Camera* camera)
{
    this->camera = camera;
    pointCoordinates = glm::vec4(0,0,0,1);
}

void Point::computeLocalTransformationMatrix()
{
    localTransformationMatrix = zRotationMatrix*yRotationMatrix*xRotationMatrix*translationMatrix;
}

void Point::computeGlobalTransformationMatrix()
{
    globalTransformationMatrix = camera->transformationMatrix * localTransformationMatrix;
}

void Point::transform()
{
    if(!camera->isStereoscopic)
    {
        transPointCoordinates = globalTransformationMatrix * pointCoordinates;
        transPointCoordinates.x = transPointCoordinates.x / transPointCoordinates.w;
        transPointCoordinates.y = transPointCoordinates.y / transPointCoordinates.w;
        transPointCoordinates.x /= camera->xRatio;
        transPointCoordinates.y /= camera->yRatio;
    }
    else
    {
        leftEyeTransPointCoordinate = camera->transformationMatrixLeftEye*localTransformationMatrix* pointCoordinates;
        leftEyeTransPointCoordinate.x = leftEyeTransPointCoordinate.x / leftEyeTransPointCoordinate.w;
        leftEyeTransPointCoordinate.y = leftEyeTransPointCoordinate.y / leftEyeTransPointCoordinate.w;
        leftEyeTransPointCoordinate.x /= camera->xRatio;
        leftEyeTransPointCoordinate.y /= camera->yRatio;

        rightEyeTransPointCoordinate = camera->transformationMatrixRightEye*localTransformationMatrix* pointCoordinates;
        rightEyeTransPointCoordinate.x = rightEyeTransPointCoordinate.x / rightEyeTransPointCoordinate.w;
        rightEyeTransPointCoordinate.y = rightEyeTransPointCoordinate.y / rightEyeTransPointCoordinate.w;
        rightEyeTransPointCoordinate.x /= camera->xRatio;
        rightEyeTransPointCoordinate.y /= camera->yRatio;
    }
}

void Point::draw()
{
    computeLocalTransformationMatrix();
    computeGlobalTransformationMatrix();
    transform();

    glBegin(GL_POINTS);
    if(!camera->isStereoscopic){
        glColor4f(1,1.0, 1.0,1.0);
        glVertex2f(transPointCoordinates.x,transPointCoordinates.y);

    }else
    {
        glColor3f(0.4,0.0, 0.0);
        glVertex2f(leftEyeTransPointCoordinate.x,leftEyeTransPointCoordinate.y);

    //glColor3f(0, 0, 1);
     glColor3f(0, 0.5, 0.5);
        glVertex2f(rightEyeTransPointCoordinate.x,rightEyeTransPointCoordinate.y);
    }
    glEnd();
}
