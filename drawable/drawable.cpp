#include "drawable.h"

Drawable::Drawable()
{
    xPos = 0;
    yPos = 0;
    zPos = 0.f;
    isSelected = false;
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

void Drawable::updateTranslationMatX()
{
    translationMatrix[3][0] = xPos;
}

void Drawable::updateTranslationMatY()
{
    translationMatrix[3][1] = yPos;
}

void Drawable::updateTranslationMatZ()
{
    translationMatrix[3][2] = zPos;
}

void Drawable::updateXRotationMat()
{
    xRotationMatrix[1][1] = cos((double)xRot/360.0f);
    xRotationMatrix[1][2] = sin((double)xRot/360.0f);
    xRotationMatrix[2][1] = -sin((double)xRot/360.0f);
    xRotationMatrix[2][2] = cos((double)xRot/360.0f);
}

void Drawable::updateYRotationMat()
{
    yRotationMatrix[0][0] = cos((double)yRot/360.0f);
    yRotationMatrix[2][0] = sin((double)yRot/360.0f);
    yRotationMatrix[0][2] = -sin((double)yRot/360.0f);
    yRotationMatrix[2][2] = cos((double)yRot/360.0f);
}

void Drawable::updateZRotationMat()
{
    zRotationMatrix[0][0] = cos((double)zRot/360.0f);
    zRotationMatrix[0][1] = sin((double)zRot/360.0f);
    zRotationMatrix[1][0] = -sin((double)zRot/360.0f);
    zRotationMatrix[1][1] = cos((double)zRot/360.0f);
}

void Drawable::draw()
{

}
