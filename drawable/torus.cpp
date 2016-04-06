#include "torus.h"
#include "cmath"
#include <GL/gl.h>

Torus::Torus(){

}

Torus::Torus(Camera* camera)
{
    this->camera = camera;
    sectionsCount = 20;
    ringsCount = 20;
    r1=0.25,
    r0=1.0;
    initTorus();
    id++;
    name =  "Torus_";
    name += std::to_string(id);
}

int Torus::id = 0;

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
       toursPointsLeftEye.clear();
       torusPointsRightEye.clear();
       edges.clear();
       edgesLeftEye.clear();
       edgesRightEye.clear();

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
       trousTransPoints.resize(torusPoints.size());
       torusPointsRightEye.resize(torusPoints.size());
       toursPointsLeftEye.resize(torusPoints.size());

       for(int i=0;i<trousTransPoints.size();i=i+4){

           edges.push_back(Edge(trousTransPoints[i],trousTransPoints[i+1]));
           edges.push_back(Edge(trousTransPoints[i+1],trousTransPoints[i+2]));
           edges.push_back(Edge(trousTransPoints[i+2],trousTransPoints[i+3]));
           edges.push_back(Edge(trousTransPoints[i+3],trousTransPoints[i]));

           edgesLeftEye.push_back(Edge(toursPointsLeftEye[i],toursPointsLeftEye[i+1]));
           edgesLeftEye.push_back(Edge(toursPointsLeftEye[i+1],toursPointsLeftEye[i+2]));
           edgesLeftEye.push_back(Edge(toursPointsLeftEye[i+2],toursPointsLeftEye[i+3]));
           edgesLeftEye.push_back(Edge(toursPointsLeftEye[i+3],toursPointsLeftEye[i]));

           edgesRightEye.push_back(Edge(torusPointsRightEye[i],torusPointsRightEye[i+1]));
           edgesRightEye.push_back(Edge(torusPointsRightEye[i+1],torusPointsRightEye[i+2]));
           edgesRightEye.push_back(Edge(torusPointsRightEye[i+2],torusPointsRightEye[i+3]));
           edgesRightEye.push_back(Edge(torusPointsRightEye[i+3],torusPointsRightEye[i]));
       }

   }

void Torus::computeLocalTransformationMatrix()
{
    localTransformationMatrix = zRotationMatrix*yRotationMatrix*xRotationMatrix*translationMatrix;
}

void Torus::computeGlobalTransformationMatrix()
{
    globalTransformationMatrix = camera->transformationMatrix * localTransformationMatrix;
}

void Torus::transformPoints()
{
    for(int i=0;i<torusPoints.size();i++){
        if(!camera->isStereoscopic){
            trousTransPoints[i] = globalTransformationMatrix*torusPoints[i];
            trousTransPoints[i].x = trousTransPoints[i].x / trousTransPoints[i].w;
            trousTransPoints[i].y = trousTransPoints[i].y / trousTransPoints[i].w;
            trousTransPoints[i].x /= camera->xRatio;
            trousTransPoints[i].y /= camera->yRatio;
        }
        else
        {
                toursPointsLeftEye[i] = camera->transformationMatrixLeftEye*localTransformationMatrix*torusPoints[i];
                toursPointsLeftEye[i].x = toursPointsLeftEye[i].x / toursPointsLeftEye[i].w;
                toursPointsLeftEye[i].y = toursPointsLeftEye[i].y / toursPointsLeftEye[i].w;
                toursPointsLeftEye[i].x /= camera->xRatio;
                toursPointsLeftEye[i].y /= camera->yRatio;

                torusPointsRightEye[i] = camera->transformationMatrixRightEye*localTransformationMatrix*torusPoints[i];
                torusPointsRightEye[i].x = torusPointsRightEye[i].x / torusPointsRightEye[i].w;
                torusPointsRightEye[i].y = torusPointsRightEye[i].y / torusPointsRightEye[i].w;
                torusPointsRightEye[i].x /= camera->xRatio;
                torusPointsRightEye[i].y /= camera->yRatio;
        }
    }
}

void Torus::draw()
{
    computeLocalTransformationMatrix();
    computeGlobalTransformationMatrix();
    transformPoints();

    glBegin(GL_LINES);
    if(!camera->isStereoscopic){
        glColor4f(1,1.0, 1.0,1.0);
        for(int i=0;i<edges.size();i++){

            if(!(edges[i].vertice1->w >=-0.06|| edges[i].vertice2->w >=-0.06)){
                glVertex2f(edges[i].vertice1->x,edges[i].vertice1->y);
                glVertex2f(edges[i].vertice2->x,edges[i].vertice2->y);
            }
        }

    }else
    {
        glColor3f(0.4,0.0, 0.0);
        for(int i=0;i<edgesLeftEye.size();i++){

            if(!(edgesLeftEye[i].vertice1->w >=-0.06|| edgesLeftEye[i].vertice2->w >=-0.06)){
                glVertex2f(edgesLeftEye[i].vertice1->x,edgesLeftEye[i].vertice1->y);
                glVertex2f(edgesLeftEye[i].vertice2->x,edgesLeftEye[i].vertice2->y);
            }
        }

    //glColor3f(0, 0, 1);
     glColor3f(0, 0.5, 0.5);
        for(int i=0;i<edgesRightEye.size();i++){

            if(!(edgesRightEye[i].vertice1->w >=-0.06|| edgesRightEye[i].vertice2->w >=-0.06)){
             glVertex2f(edgesRightEye[i].vertice1->x,edgesRightEye[i].vertice1->y);
             glVertex2f(edgesRightEye[i].vertice2->x,edgesRightEye[i].vertice2->y);
             }
        }
    }
    glEnd();
}

