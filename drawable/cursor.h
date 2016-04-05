#ifndef CURSOR_H
#define CURSOR_H
#include "drawable/drawable.h"
#include "Camera/camera.h"
#include "glm/vec4.hpp"
#include "glm/mat4x4.hpp"
#include <vector>

class Cursor: public Drawable
{
public:
    Cursor();
    Cursor(Camera* camera);
    float speedMovement;
    glm::vec4 getCursorPos();
private:
    float axisLength;

    Camera* camera;

    std::vector<glm::vec4> pointCoordinates;
    std::vector<glm::vec4> transPointCoordinates;
    std::vector<glm::vec4> leftEyeTransPointCoordinate;
    std::vector<glm::vec4> rightEyeTransPointCoordinate;

    glm::mat4 localTransformationMatrix;
    glm::mat4 globalTransformationMatrix;

    void computeLocalTransformationMatrix();
    void computeGlobalTransformationMatrix();
    void transform();
    void draw();
};

#endif // CURSOR_H
