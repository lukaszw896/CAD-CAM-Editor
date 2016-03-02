#ifndef TORUS_H
#define TORUS_H
#include <glm/vec4.hpp> // glm::vec4
#include <vector>
class Torus
{
public:
    Torus();

public:
    void initTorus();

    std::vector<glm::vec4> torusPoints;
    std::vector<glm::vec4> trousTransPoints;

    int    sectionsCount;
    int    ringsCount;

    float r1,r0;

};

#endif // TORUS_H
