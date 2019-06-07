#include <stdio.h>
#include <cstdlib>
#include <math.h>

#include "constants.h"
#include "cube.h"
#include "loadModel.h"

#define cube "modele/cuboid.obj"

using namespace glm;

Cube::Cube(vec3 starter,vec3 kolo) {
    bool res = loadOBJ(cube, this->vertices, this->uvs, this->normals, this->vCount);
    if(!res) {
        fprintf(stderr,"Blad - nie wczytano modelu - cube");
        exit(1);
    }
    start = starter;
    position = vec3(0.0,0.0,0.0);
    ruchGasiennic = starter;
    angleX = -90.0f;
    angleXX = 0.0f;
    angleY = 0.0f;
    ustawKolo = kolo;
    scale = vec3(1.0,1.0,1.0);
}

Cube::~Cube() {
    vertices.clear();
    uvs.clear();
    normals.clear();
}

void Cube::drawSolid(GLuint &tex,mat4 &V) {
    glEnable(GL_NORMALIZE);
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_NORMAL_ARRAY);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);
    glBindTexture(GL_TEXTURE_2D,tex);

    mat4 M=mat4(1.0f);
    M=rotate(M,this-> angleX * PI / 180,vec3(1.0f, 0.0f, 0.0f));

    //M=translate(M,vec3(ustawKolo[0]-(start[0]-position[0]),ustawKolo[1]-(start[1]-position[1]),ustawKolo[2]-(start[2]-position[2])));
//    M=translate(M,vec3(ustawKolo[0],ustawKolo[1],ustawKolo[2]));
//    M=rotate(M,this-> angleY * PI / 180,vec3(1.0f, 0.0f, 0.0f));
//    M=translate(M,vec3(-ustawKolo[0],-ustawKolo[1],-ustawKolo[2]));
    //M=translate(M,vec3(-ustawKolo[0]+(start[0]-position[0]),-ustawKolo[1]+(start[1]-position[1]),-ustawKolo[2]+(start[2]-position[2])));

    M=translate(M,this->start);

    M=translate(M,this->position);

    M=translate(M,vec3(-start[0],-start[1],-start[2]));
    M=rotate(M,this-> angleZ * PI / 180,vec3(0.0f, 0.0f, 1.0f));

    M=translate(M,vec3(ustawKolo[0],ustawKolo[1],ustawKolo[2]));
    M=rotate(M,this-> angleY * PI / 180,vec3(1.0f, 0.0f, 0.0f));
    M=translate(M,vec3(-ustawKolo[0],-ustawKolo[1],-ustawKolo[2]));

    M=rotate(M,this-> angleXX * PI / 180,vec3(1.0f, 0.0f, 0.0f));

    M=translate(M,vec3(start[0],start[1],start[2]));




    M=translate(M,this->ruchGasiennic-this->start);



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
