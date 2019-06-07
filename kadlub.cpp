#include <stdio.h>
#include <cstdlib>

#include "constants.h"
#include "kadlub.h"
#include "loadModel.h"

#define kadlub "modele/kadlub.obj"

using namespace glm;

Kadlub::Kadlub() {
    bool res = loadOBJ(kadlub, this->vertices, this->uvs, this->normals, this->vCount);
    if(!res) {
        fprintf(stderr,"Blad - nie wczytano modelu - kadlub");
        exit(1);
    } else fprintf(stderr,"Kadlub - wczytano\n");
    position = vec3(0.0f,0.0f,0.0f);
    przesunDoZera = vec3(0.0f,0.0f,-0.42221f);
    angleX = -90.0f;
    angleY = 0.0f;
    angleZ = 0.0f;
    scale = vec3(1.0,1.0,1.0);
}

Kadlub::~Kadlub() {
    vertices.clear();
    uvs.clear();
    normals.clear();
}

void Kadlub::drawSolid(GLuint &tex,mat4 &V) {
    glEnable(GL_NORMALIZE);
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_NORMAL_ARRAY);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);
    glBindTexture(GL_TEXTURE_2D,tex);

    mat4 M=mat4(1.0f);
    M=rotate(M,this-> angleX * PI / 180,vec3(1.0f, 0.0f, 0.0f));
    //M=rotate(M,this-> angleY * PI / 180,vec3(0.0f, 1.0f, 0.0f));

    M=translate(M,this->position);

    //M=translate(M,vec3(-this->position[1],-this->position[0],-this->position[2]));
    //M=translate(M,vec3(0.04573f,-0.18588f,-0.40285f));
    M=rotate(M,this-> angleZ * PI / 180,vec3(0.0f, 0.0f, 1.0f));
    //M=translate(M,vec3(this->position[1],this->position[0],this->position[2]));
    //M=translate(M,vec3(-0.04573f,0.18588f,0.40285f));

    //printf("%f,        %f\n",this->position[1],this->position[0]);




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