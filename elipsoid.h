#ifndef ELIPSOID_H
#define ELIPSOID_H
#include <glm/vec4.hpp> // glm::vec4
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/common.hpp>
#include <glm/glm.hpp>
#include "cmath"
#include <vector>

#define NO_SOLUTION -1000;

using namespace glm;

class Elipsoid
{
public:
    Elipsoid();
    Elipsoid(float a, float b, float c);
    void calcDPMMat(glm::mat4 transMat);
    float intersectCalc(float x, float y, float cameraZ,vec4* c);
private:
    float a;
    float b;
    float c;

    float m;

    void updateRadius(float a, float b, float c);
    void initDiagMat();
    void updateDiagMat();
    glm::vec3 derivative(glm::vec3);
    //calculates

    glm::mat4 diagMat;
    //transposed invers of M times diagMat times invers of M
    glm::mat4 DPMMat;

};



#endif // ELIPSOID_H
