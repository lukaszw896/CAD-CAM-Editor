#include "camera.h"

Camera::Camera()
{
    rProjection = 4.f;
    eyeDist = 0.10f;
    zPos = -10.f;
    isStereoscopic = false;

    initProjectionMat(rProjection);
    initProjectionMatLeftEye(rProjection,eyeDist);
    initProjectionMatRightEye(rProjection,eyeDist);
    initScaleMat();
    updateTranslationMatZ();
}

void Camera::computeTransformationMatrix()
{
    //*identityMat
    if(!isStereoscopic){
         transformationMatrix = projectionMatrix*translationMatrix*scaleMatrix * zRotationMatrix* yRotationMatrix* xRotationMatrix;
    }
    else
    {
        transformationMatrixLeftEye = projectionMatrixLeftEye*translationMatrix*scaleMatrix *zRotationMatrix* yRotationMatrix* xRotationMatrix;
        transformationMatrixRightEye = projectionMatrixRightEye*translationMatrix*scaleMatrix *zRotationMatrix* yRotationMatrix* xRotationMatrix;
    }
}

void Camera::initIdentityMat()
{
    for(int i=0;i<4;i++)
    {
        for(int j=0;j<4;j++)
        {
            if(i==j){
                identityMat[i][j] = 1.0f;
            }
            else{
                identityMat[i][j] = 0.0f;
            }
        }
    }
}

void Camera::initProjectionMat(float r)
{
    for(int i=0;i<4;i++)
    {
        for(int j=0;j<4;j++)
        {

                projectionMatrixLeftEye[i][j] = 0.0f;

        }
    }

    projectionMatrix[0][0] = 1.0f;
    projectionMatrix[1][1] = 1.0f;
    projectionMatrix[3][3] = 1.0f;
    projectionMatrix[2][3] = 1.0f/r;
}

void Camera::initProjectionMatLeftEye(float r, float e)
{
    for(int i=0;i<4;i++)
    {
        for(int j=0;j<4;j++)
        {

                projectionMatrixLeftEye[i][j] = 0.0f;

        }
    }

    projectionMatrixLeftEye[0][0] = 1.0f;
    projectionMatrixLeftEye[1][1] = 1.0f;
    projectionMatrixLeftEye[3][3] = 1.0f;
    projectionMatrixLeftEye[2][3] = 1.0f/r;

    projectionMatrixLeftEye[2][0] = -e/(2*r);
}

void Camera::initProjectionMatRightEye(float r, float e)
{
    for(int i=0;i<4;i++)
    {
        for(int j=0;j<4;j++)
        {

                projectionMatrixRightEye[i][j] = 0.0f;

        }
    }

    projectionMatrixRightEye[0][0] = 1.0f;
    projectionMatrixRightEye[1][1] = 1.0f;
    projectionMatrixRightEye[3][3] = 1.0f;
    projectionMatrixRightEye[2][3] = 1.0f/r;

    projectionMatrixRightEye[2][0] = e/(2*r);
}

void Camera::initScaleMat()
{
    for(int i=0;i<4;i++)
    {
        for(int j=0;j<4;j++)
        {
            if(i==j){
                scaleMatrix[i][j] = 1.0f;
            }
            else{
                scaleMatrix[i][j] = 0.0f;
            }
        }
    }
}

void Camera::updateScaleMatrix(float s)
{
    scaleMatrix[0][0] = s;
    scaleMatrix[1][1] = s;
    scaleMatrix[2][2] = s;
}


