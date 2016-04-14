#include "cursor.h"
#include <GL/gl.h>

Cursor::Cursor()
{

}

Cursor::Cursor(Camera* camera)
{
    this->camera = camera;
    axisLength = 0.02f;
    speedMovement = 0.05f;
    pointCoordinates.resize(6);
    transPointCoordinates.resize(6);
    leftEyeTransPointCoordinate.resize(6);
    rightEyeTransPointCoordinate.resize(6);


    pointCoordinates[0] = glm::vec4(-axisLength,0,0,1);
    pointCoordinates[1] = glm::vec4(axisLength,0,0,1);
    pointCoordinates[2] = glm::vec4(0,-axisLength,0,1);
    pointCoordinates[3] = glm::vec4(0,axisLength,0,1);
    pointCoordinates[4] = glm::vec4(0,0,-axisLength,1);
    pointCoordinates[5] = glm::vec4(0,0,axisLength,1);

    centerPos = glm::vec4(0,0,0,1);
}

void Cursor::computeLocalTransformationMatrix()
{
    localTransformationMatrix = zRotationMatrix*yRotationMatrix*xRotationMatrix*translationMatrix;
}

void Cursor::computeGlobalTransformationMatrix()
{
    globalTransformationMatrix = camera->transformationMatrix * localTransformationMatrix;
}

void Cursor::transform()
{
    centerOnScreenPos = globalTransformationMatrix * centerPos;
    centerOnScreenPos.x = centerOnScreenPos.x / centerOnScreenPos.w;
    centerOnScreenPos.y = centerOnScreenPos.y / centerOnScreenPos.w;
    centerOnScreenPos.x /= camera->xRatio;
    centerOnScreenPos.y /= camera->yRatio;
    if(!camera->isStereoscopic)
    {
        for(int i=0;i<6;i++){
        transPointCoordinates[i] = globalTransformationMatrix * pointCoordinates[i];
        transPointCoordinates[i].x = transPointCoordinates[i].x / transPointCoordinates[i].w;
        transPointCoordinates[i].y = transPointCoordinates[i].y / transPointCoordinates[i].w;
        transPointCoordinates[i].x /= camera->xRatio;
        transPointCoordinates[i].y /= camera->yRatio;
        }
    }
    else
    {
        for(int i=0;i<6;i++){
        leftEyeTransPointCoordinate[i] = camera->transformationMatrixLeftEye*localTransformationMatrix* pointCoordinates[i];
        leftEyeTransPointCoordinate[i].x = leftEyeTransPointCoordinate[i].x / leftEyeTransPointCoordinate[i].w;
        leftEyeTransPointCoordinate[i].y = leftEyeTransPointCoordinate[i].y / leftEyeTransPointCoordinate[i].w;
        leftEyeTransPointCoordinate[i].x /= camera->xRatio;
        leftEyeTransPointCoordinate[i].y /= camera->yRatio;

        rightEyeTransPointCoordinate[i] = camera->transformationMatrixRightEye*localTransformationMatrix* pointCoordinates[i];
        rightEyeTransPointCoordinate[i].x = rightEyeTransPointCoordinate[i].x / rightEyeTransPointCoordinate[i].w;
        rightEyeTransPointCoordinate[i].y = rightEyeTransPointCoordinate[i].y / rightEyeTransPointCoordinate[i].w;
        rightEyeTransPointCoordinate[i].x /= camera->xRatio;
        rightEyeTransPointCoordinate[i].y /= camera->yRatio;
        }
    }
}

void Cursor::draw()
{
    computeLocalTransformationMatrix();
    computeGlobalTransformationMatrix();
    transform();

    glBegin(GL_LINES);
    glLineWidth(2);
    if(!camera->isStereoscopic){
        if(!(transPointCoordinates[0].w>=-0.06)){
        glColor4f(1,0,0,1.0);
        glVertex2f(transPointCoordinates[0].x,transPointCoordinates[0].y);
        glVertex2f(transPointCoordinates[1].x,transPointCoordinates[1].y);
        glColor4f(0,1,0,1.0);
        glVertex2f(transPointCoordinates[2].x,transPointCoordinates[2].y);
        glVertex2f(transPointCoordinates[3].x,transPointCoordinates[3].y);
        glColor4f(0,0,1,1.0);
        glVertex2f(transPointCoordinates[4].x,transPointCoordinates[4].y);
        glVertex2f(transPointCoordinates[5].x,transPointCoordinates[5].y);
        }

    }else
    {
        glColor3f(0.4,0.0, 0.0);
        if(!(leftEyeTransPointCoordinate[0].w>=-0.06)){
            for(int i=0;i<6;i++){

                glVertex2f(leftEyeTransPointCoordinate[i].x,leftEyeTransPointCoordinate[i].y);
            }

            glColor3f(0, 0.5, 0.5);
            for(int i=0;i<6;i++){
                glVertex2f(rightEyeTransPointCoordinate[i].x,rightEyeTransPointCoordinate[i].y);
            }
        }
    }
    glEnd();
}

glm::vec4 Cursor::getCursorPos()
{
    return glm::vec4(xPos,yPos,zPos,1);
}
