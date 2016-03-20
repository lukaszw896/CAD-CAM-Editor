#ifndef DRAWABLE_H
#define DRAWABLE_H

#include <glm/mat4x4.hpp>

using namespace glm;

class Drawable
{
public:
    Drawable();
    void updateTranslationMat();
    void updateXRotationMat();
    void updateYRotationMat();
    void updateZRotationMat();

private:
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

};

#endif // DRAWABLE_H
