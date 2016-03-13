#ifndef TORUS_H
#define TORUS_H
#include <glm/vec4.hpp> // glm::vec4
#include <vector>
#include "edge.h"
using namespace std;
using namespace glm;
class Torus
{
public:
    Torus();

public:
    void initTorus();

    vector<vec4> torusPoints;
    vector<vec4> trousTransPoints;
    vector<vec4> toursPointsLeftEye;
    vector<vec4> torusPointsRightEye;

    vector<Edge> edges;
    vector<Edge> edgesLeftEye;
    vector<Edge> edgesRightEye;


    int    sectionsCount;
    int    ringsCount;

    float r1,r0;

};

#endif // TORUS_H
