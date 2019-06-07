#include <stdio.h>
#include <cstdlib>

#include "constants.h"
#include "koloS.h"
#include "loadModel.h"

#define koloS "modele/koloSv2.obj"

using namespace glm;

KoloS::KoloS(vec3 starter) {
    bool res = loadOBJ(koloS, this->vertices, this->uvs, this->normals, this->vCount);
    if(!res) {
        fprintf(stderr,"Blad - nie wczytano modelu - male kolo");
        exit(1);
    } else fprintf(stderr,"Male kolo - wczytano\n");
    start = starter;
    position = starter;
    przesunDoZera = vec3(0.0f,-3.29f,-0.91359f);
    angleX = -90.0f;
    angleY = 0.0f;
    angleZ = 0.0f;
    obrot = 0.0f;
    scale = vec3(1.0,1.0,1.0);
}

KoloS::~KoloS() {
    vertices.clear();
    uvs.clear();
    normals.clear();
}

void KoloS::drawSolid(GLuint &tex,mat4 &V) {
    glEnable(GL_NORMALIZE);
//    glEnableVertexAttribArray(GL_VERTEX_ARRAY);
//    glEnableVertexAttribArray(GL_NORMAL_ARRAY);
//    glEnableVertexAttribArray(GL_TEXTURE_COORD_ARRAY);
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_NORMAL_ARRAY);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);
    glBindTexture(GL_TEXTURE_2D,tex);

    mat4 M=mat4(1.0f);
    M=rotate(M,this-> angleX * PI / 180,vec3(1.0f, 0.0f, 0.0f));
    M=rotate(M,this-> angleY * PI / 180,vec3(0.0f, 1.0f, 0.0f));

    M=translate(M,this->position);

    M=translate(M,vec3(-start[0],-start[1],-start[2]));
    M=rotate(M,this-> angleZ * PI / 180,vec3(0.0f, 0.0f, 1.0f));
    M=translate(M,vec3(start[0],start[1],start[2]));

    M=translate(M,przesunDoZera);
    M=rotate(M,this-> obrot,vec3(1.0f, 0.0f, 0.0f));
    M=translate(M,-przesunDoZera);

    glLoadMatrixf(value_ptr(V*M));
//    glVertexAttribPointer(GL_VERTEX_ARRAY,3,GL_FLOAT,false,0,this->vertices[0]);
//    glVertexAttribPointer(GL_NORMAL_ARRAY,3,GL_FLOAT,false,sizeof(float)*3,this->normals[0]);
//    glVertexAttribPointer(GL_TEXTURE_COORD_ARRAY,2,GL_FLOAT,false,0,this->uvs[0]);
    glVertexPointer(3,GL_FLOAT,0,&(this->vertices[0]));
    glNormalPointer(GL_FLOAT,sizeof(float)*3,&(this->normals[0]));
    glTexCoordPointer(2,GL_FLOAT,0,&(this->uvs[0]));

    //glVertexPointer(3,GL_FLOAT,0,&(this->vertices[0]));
    //glNormalPointer(GL_FLOAT,sizeof(float)*3,&(this->normals[0]));
    //glTexCoordPointer(2,GL_FLOAT,0,&(this->uvs[0]));
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
//    glDisableVertexAttribArray(GL_VERTEX_ARRAY);
//    glDisableVertexAttribArray(GL_NORMAL_ARRAY);
//    glDisableVertexAttribArray(GL_TEXTURE_COORD_ARRAY);
    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_NORMAL_ARRAY);
    glDisableClientState(GL_TEXTURE_COORD_ARRAY);
}
