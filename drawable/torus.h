#ifndef TORUS_H
#define TORUS_H
#include <glm/vec4.hpp> // glm::vec4
#include <glm/mat4x4.hpp>
#include <vector>
#include "edge.h"
#include "drawable/drawable.h"
#include "Camera/camera.h"

using namespace std;
class Torus : public Drawable
{
public:
    Torus();
    Torus(Camera* camera);
    void initTorus();

    void computeLocalTransformationMatrix();
    void computeGlobalTransformationMatrix();
    void transformPoints();
    void draw();

    vector<glm::vec4> torusPoints;
    vector<glm::vec4> trousTransPoints;
    vector<glm::vec4> toursPointsLeftEye;
    vector<glm::vec4> torusPointsRightEye;

    vector<Edge> edges;
    vector<Edge> edgesLeftEye;
    vector<Edge> edgesRightEye;

    glm::mat4 localTransformationMatrix;
    glm::mat4 globalTransformationMatrix;


    int    sectionsCount;
    int    ringsCount;

    Camera* camera;

    float r1,r0;

};

#endif // TORUS_H
