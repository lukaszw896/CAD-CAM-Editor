#include "drawable.h"

Drawable::Drawable()
{
    initTranslationMat();
    initXRotationMat();
    initYRotationMat();
    initZRotationMat();
}

void Drawable::initTranslationMat()
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
}

void Drawable::initXRotationMat()
{
    for(int i=0;i<4;i++){
        for(int j=0;j<4;j++){
            if(i==j) xRotationMatrix[i][j] = 1.f;
            else xRotationMatrix[i][j] =0.f;
        }
    }
    xRotationMatrix[1][1] = cos(0.f);
    xRotationMatrix[1][2] = sin(0.f);
    xRotationMatrix[2][1] = -sin(0.f);
    xRotationMatrix[2][2] = cos(0.f);
}

void Drawable::initYRotationMat()
{
    for(int i=0;i<4;i++){
        for(int j=0;j<4;j++){
            if(i==j) yRotationMatrix[i][j] = 1.f;
            else yRotationMatrix[i][j] =0.f;
        }
    }
    yRotationMatrix[0][0] = cos(0.f);
    yRotationMatrix[2][0] = sin(0.f);
    yRotationMatrix[0][2] = -sin(0.f);
    yRotationMatrix[2][2] = cos(0.f);
}

void Drawable::initZRotationMat()
{
    for(int i=0;i<4;i++){
        for(int j=0;j<4;j++){
            if(i==j) zRotationMatrix[i][j] = 1.f;
            else zRotationMatrix[i][j] =0.f;
        }
    }
    zRotationMatrix[0][0] = cos(0.f);
    zRotationMatrix[0][1] = sin(0.f);
    zRotationMatrix[1][0] = -sin(0.f);
    zRotationMatrix[1][1] = cos(0.f);
}

void Drawable::updateTranslationMatX(float x)
{
    translationMatrix[3][0] = x;
}

void Drawable::updateTranslationMatY(float y)
{
    translationMatrix[3][1] = y;
}

void Drawable::updateTranslationMatZ(float z)
{
    translationMatrix[3][2] = z;
}

void Drawable::updateXRotationMat(float angle)
{
    xRotationMatrix[1][1] = cos((double)angle/360.0f);
    xRotationMatrix[1][2] = sin((double)angle/360.0f);
    xRotationMatrix[2][1] = -sin((double)angle/360.0f);
    xRotationMatrix[2][2] = cos((double)angle/360.0f);
}

void Drawable::updateYRotationMat(float angle)
{
    yRotationMatrix[0][0] = cos((double)angle/360.0f);
    yRotationMatrix[2][0] = sin((double)angle/360.0f);
    yRotationMatrix[0][2] = -sin((double)angle/360.0f);
    yRotationMatrix[2][2] = cos((double)angle/360.0f);
}

void Drawable::updateZRotationMat(float angle)
{
    zRotationMatrix[0][0] = cos((double)angle/360.0f);
    zRotationMatrix[0][1] = sin((double)angle/360.0f);
    zRotationMatrix[1][0] = -sin((double)angle/360.0f);
    zRotationMatrix[1][1] = cos((double)angle/360.0f);
}
