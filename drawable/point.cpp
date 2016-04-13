#include "point.h"
#include <GL/gl.h>

Point::Point()
{

}
Point::Point(Camera* camera)
{
    this->camera = camera;
    pointCoordinates = glm::vec4(0,0,0,1);
    id++;
    name = "Point_";
    name += std::to_string(id);
}

int Point::id =0;

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
    localTransPointCoordinates = localTransformationMatrix * pointCoordinates;

    if(!camera->isStereoscopic)
    {
        transPointCoordinates = camera->transformationMatrix * localTransPointCoordinates;
        transPointCoordinates.x = transPointCoordinates.x / transPointCoordinates.w;
        transPointCoordinates.y = transPointCoordinates.y / transPointCoordinates.w;
        transPointCoordinates.x /= camera->xRatio;
        transPointCoordinates.y /= camera->yRatio;
    }
    else
    {
        leftEyeTransPointCoordinate = camera->transformationMatrixLeftEye*localTransPointCoordinates;
        leftEyeTransPointCoordinate.x = leftEyeTransPointCoordinate.x / leftEyeTransPointCoordinate.w;
        leftEyeTransPointCoordinate.y = leftEyeTransPointCoordinate.y / leftEyeTransPointCoordinate.w;
        leftEyeTransPointCoordinate.x /= camera->xRatio;
        leftEyeTransPointCoordinate.y /= camera->yRatio;

        rightEyeTransPointCoordinate = camera->transformationMatrixRightEye*localTransPointCoordinates;
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
        if(!isSelected){
            glColor4f(1,1.0, 1.0,1.0);
        }
        else{
           glColor4f(0.3,1, 0.3,1.0);
        }
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
