#ifndef POINT_H
#define POINT_H
#include "drawable/drawable.h"
#include "Camera/camera.h"
#include "glm/vec4.hpp"
#include "glm/mat4x4.hpp"


class Point : public Drawable
{
public:
    Point();
    Point(Camera* camera);

private:
    Camera* camera;

    glm::vec4 pointCoordinates;
    glm::vec4 transPointCoordinates;
    glm::vec4 leftEyeTransPointCoordinate;
    glm::vec4 rightEyeTransPointCoordinate;

    glm::mat4 localTransformationMatrix;
    glm::mat4 globalTransformationMatrix;

    void computeLocalTransformationMatrix();
    void computeGlobalTransformationMatrix();
    void transform();
    void draw();
};

#endif // POINT_H
