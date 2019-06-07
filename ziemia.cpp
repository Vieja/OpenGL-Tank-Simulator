#include <stdio.h>
#include <cstdlib>

#include "constants.h"
#include "ziemia.h"
#include "loadModel.h"

#define ziemia "modele/ziemia.obj"

using namespace glm;

Ziemia::Ziemia() {
    bool res = loadOBJ(ziemia, this->vertices, this->uvs, this->normals, this->vCount);
    if(!res) {
        fprintf(stderr,"Blad - nie wczytano modelu - ziemia");
        exit(1);
    } else fprintf(stderr,"Ziemia - wczytano\n");
    position = vec3(0.0f,0.0f,-1.75f);
    //przesunDoZera = vec3(-0.00106f,-0.98469f,0.67054);
    angleX = -90.0f;
    angleY = 0.0f;
    angleZ = 0.0f;
    obrot = 0.0f;
    scale = vec3(1.0,1.0,1.0);
}

Ziemia::~Ziemia() {
    vertices.clear();
    uvs.clear();
    normals.clear();
}

void Ziemia::drawSolid(GLuint &tex,mat4 &V) {
    glEnable(GL_NORMALIZE);
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_NORMAL_ARRAY);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);
    glBindTexture(GL_TEXTURE_2D,tex);

    mat4 M=mat4(1.0f);
    M=rotate(M,this-> angleX * PI / 180,vec3(1.0f, 0.0f, 0.0f));
    M=rotate(M,this-> angleY * PI / 180,vec3(0.0f, 1.0f, 0.0f));

    M=translate(M,this->position);

    glLoadMatrixf(value_ptr(V*M));
    glVertexPointer(3,GL_FLOAT,0,&(this->vertices[0]));
    glNormalPointer(GL_FLOAT,sizeof(float)*3,&(this->normals[0]));
    glTexCoordPointer(2,GL_FLOAT,0,&(this->uvs[0]));
    float ambient[] = {0,0,0,1};
    float emision[] = {0,0,0,1};
    float diffuse[] = {0.5,0.5,0.5,1};
    float specular[] = {0.5,0.5,0.5,1};
    float shininess = 50;
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient);
    glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, emision);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular);
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shininess);
    glDrawArrays(GL_TRIANGLES,0,this->vCount);
    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_NORMAL_ARRAY);
    glDisableClientState(GL_TEXTURE_COORD_ARRAY);
}
