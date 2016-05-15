#ifndef POINT_H
#define POINT_H
#include "drawable/drawable.h"
#include "Camera/camera.h"
#include "glm/vec4.hpp"
#include "glm/vec3.hpp"
#include "glm/mat4x4.hpp"

using namespace glm;

class Point : public Drawable
{
public:
    Point();
    Point(Camera* camera);
    Point(vec3);
    glm::vec4 transPointCoordinates;
    glm::vec3 localTransPointCoordinates;
    glm::vec4 leftEyeTransPointCoordinate;
    glm::vec4 rightEyeTransPointCoordinate;
    bool isRemovable;
    void transform();
    void draw();
private:
    static int id;

    Camera* camera;

    glm::vec4 pointCoordinates;



    glm::mat4 localTransformationMatrix;
    glm::mat4 globalTransformationMatrix;

    void computeLocalTransformationMatrix();
    void computeGlobalTransformationMatrix();


};



#endif // POINT_H
