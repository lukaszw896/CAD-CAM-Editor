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
    glm::vec4 transPointCoordinates;
    glm::vec4 localTransPointCoordinates;
    glm::vec4 leftEyeTransPointCoordinate;
    glm::vec4 rightEyeTransPointCoordinate;
    void draw();
private:
    static int id;

    Camera* camera;

    glm::vec4 pointCoordinates;



    glm::mat4 localTransformationMatrix;
    glm::mat4 globalTransformationMatrix;

    void computeLocalTransformationMatrix();
    void computeGlobalTransformationMatrix();
    void transform();

};



#endif // POINT_H
