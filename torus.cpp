#include "torus.h"
#include "cmath"

Torus::Torus()
{
    sectionsCount = 100;
    ringsCount = 60;
    r1=0.25,
    r0=1.0;
}

void Torus::initTorus()
{
    /*
     *http://paulbourke.net/geometry/torus/
     *
    x = cos(theta) * [ r0 + r1 * cos(phi) ]
    y = sin(theta) * [ r0 + r1 * cos(phi) ]
    z = r1 * sin(phi)
    */

       torusPoints.clear();

       float du = (2 * M_PI) / ringsCount;
       float dv = (2 * M_PI) / sectionsCount;
       float phi = 0;
       float theta = 0;

       while(phi < 2*M_PI){
           theta = 0;
           while(theta < 2*M_PI){
               glm::vec4 vertex = glm::vec4((r0 + r1 * cos(phi)) * (cos((theta))),
                                            (r0 + r1 * cos((phi)))* (sin((theta))),
                                            (r1 * sin(phi)),
                                            1.0f);
               phi+=du;
               glm::vec4 vertex1 = glm::vec4((r0 + r1 * cos(phi)) * (cos((theta))),
                                             (r0 + r1 * cos((phi)))* (sin((theta))),
                                             (r1 * sin(phi)),
                                             1.0f);
               theta+=dv;
               glm::vec4 vertex2 = glm::vec4((r0 + r1 * cos(phi)) * (cos((theta))),
                                             (r0 + r1 * cos((phi)))* (sin((theta))),
                                             (r1 * sin(phi)),
                                             1.0f);
               phi -= du;
               glm::vec4 vertex3 = glm::vec4((r0 + r1 * cos(phi)) * (cos((theta))),
                                             (r0 + r1 * cos((phi)))* (sin((theta))),
                                             (r1 * sin(phi)),
                                             1.0f);
               torusPoints.push_back(vertex);
               torusPoints.push_back(vertex1);
               torusPoints.push_back(vertex2);
               torusPoints.push_back(vertex3);

           }
           phi += du;
       }
       du+1;
   }

