#include <QtWidgets>
#include <QtOpenGL>

#include "oglwidget.h"


void OGlWidget::initIdentityMat()
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

void OGlWidget::initTranslationMat(float x, float y, float z)
{
    for(int i=0;i<4;i++)
    {
        for(int j=0;j<4;j++)
        {
            if(i==j){
                translationMatrix[i][j] = 1.0f;
            }
            else{
                translationMatrix[i][j] = 0.0f;
            }
        }
    }

    translationMatrix[3][0] = x;
    translationMatrix[3][1] = y;
    translationMatrix[3][2] = z;

}

void OGlWidget::initProjectionMat(float r)
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

void OGlWidget::initProjectionMatLeftEye(float r, float e)
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

void OGlWidget::initProjectionMatRightEye(float r, float e)
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

void OGlWidget::initXRotationMat(int angle){
    for(int i=0;i<4;i++){
        for(int j=0;j<4;j++){
            if(i==j) xRotationMatrix[i][j] = 1.f;
            else xRotationMatrix[i][j] =0.f;
        }
    }
    xRotationMatrix[1][1] = cos((double)angle/360.0f);
    xRotationMatrix[1][2] = sin((double)angle/360.0f);
    xRotationMatrix[2][1] = -sin((double)angle/360.0f);
    xRotationMatrix[2][2] = cos((double)angle/360.0f);
}

void OGlWidget::initYRotationMat(int angle){
    for(int i=0;i<4;i++){
        for(int j=0;j<4;j++){
            if(i==j) yRotationMatrix[i][j] = 1.f;
            else yRotationMatrix[i][j] =0.f;
        }
    }
    yRotationMatrix[0][0] = cos((double)angle/360.0f);
    yRotationMatrix[2][0] = sin((double)angle/360.0f);
    yRotationMatrix[0][2] = -sin((double)angle/360.0f);
    yRotationMatrix[2][2] = cos((double)angle/360.0f);
}

void OGlWidget::initZRotationMat(int angle){
    for(int i=0;i<4;i++){
        for(int j=0;j<4;j++){
            if(i==j) zRotationMatrix[i][j] = 1.f;
            else zRotationMatrix[i][j] =0.f;
        }
    }
    zRotationMatrix[0][0] = cos((double)angle/360.0f);
    zRotationMatrix[0][1] = sin((double)angle/360.0f);
    zRotationMatrix[1][0] = -sin((double)angle/360.0f);
    zRotationMatrix[1][1] = cos((double)angle/360.0f);
}

void OGlWidget::initScaleMat(float s)
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

    scaleMatrix[0][0] = s;
    scaleMatrix[1][1] = s;
    scaleMatrix[2][2] = s;

}
