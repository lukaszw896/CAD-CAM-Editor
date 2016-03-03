#ifndef EDGE_H
#define EDGE_H

#include <glm/vec4.hpp> // glm::vec4

class Edge
{
public:
    Edge();

    Edge(glm::vec4 &vertice1,glm::vec4 &vertice2){
        this->vertice1 = &vertice1;
        this->vertice2 = &vertice2;
    }

public:

    glm::vec4* vertice1;
    glm::vec4* vertice2;
};

#endif // EDGE_H
