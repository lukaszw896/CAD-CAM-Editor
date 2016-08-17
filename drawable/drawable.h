#ifndef DRAWABLE_H
#define DRAWABLE_H

#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>
#include "cmath"
#include <string>

enum DrawableType
{
    CURSOR,
    TORUS,
    POINT,
    BEZIERCURVE,
    BSPLINE,
    INTERPBSPLINE,
    BEZIERSURFACE
};

class Drawable
{
public:
    glm::vec4 transPointCoordinates;
    glm::vec3 localTransPointCoordinates;
    glm::vec4 leftEyeTransPointCoordinate;
    glm::vec4 rightEyeTransPointCoordinate;

    Drawable();
    void updateTranslationMatX();
    void updateTranslationMatY();
    void updateTranslationMatZ();
    void updateXRotationMat();
    void updateYRotationMat();
    void updateZRotationMat();

    std::string name;
    bool isSelected;

    int xRot;
    int yRot;
    int zRot;

    float xPos;
    float yPos;
    float zPos;

    glm::mat4 xRotationMatrix;
    glm::mat4 yRotationMatrix;
    glm::mat4 zRotationMatrix;

    glm::mat4 translationMatrix;

    void initTranslationMat();
    void initXRotationMat();
    void initYRotationMat();
    void initZRotationMat();

    virtual void draw();

};

#endif // DRAWABLE_H
