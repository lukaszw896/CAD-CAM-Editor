#ifndef TORUS_H
#define TORUS_H
#include <glm/vec4.hpp> // glm::vec4
#include <vector>
#include "edge.h"
class Torus
{
public:
    Torus();

public:
    void initTorus();

    std::vector<glm::vec4> torusPoints;
    std::vector<glm::vec4> trousTransPoints;
    std::vector<Edge> edges;

    int    sectionsCount;
    int    ringsCount;

    float r1,r0;

};

#endif // TORUS_H
