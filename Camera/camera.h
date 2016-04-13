#ifndef CAMERA_H
#define CAMERA_H

#include "drawable/drawable.h"
#include "glm/mat4x4.hpp"


class Camera : public Drawable
{
public:
    Camera();

    void computeTransformationMatrix();
    void initIdentityMat();
    void initProjectionMat(float r);
    void initProjectionMatLeftEye(float r, float e);
    void initProjectionMatRightEye(float r, float e);
    void initScaleMat();
    void updateScaleMatrix(float s);

    float xRatio;
    float yRatio;

    float scale;

    glm::mat4 identityMat;

    glm::mat4 scaleMatrix;
    glm::mat4 projectionMatrix;

    glm::mat4 projectionMatrixLeftEye;
    glm::mat4 projectionMatrixRightEye;

    glm::mat4 transformationMatrix;

    glm::mat4 transformationMatrixLeftEye;
    glm::mat4 transformationMatrixRightEye;

    float rProjection;
    float eyeDist;

    bool isStereoscopic;

    int screenWidth = 500;
    int screenHeight = 500;

};

#endif // CAMERA_H
