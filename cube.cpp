#include <stdio.h>
#include <cstdlib>

#include "cube.h"
#include "loadOBJ.h"
#include "shaderprogram.h"

#define model "modele/cuboid.obj"

using namespace glm;

Cube::Cube(vec3 starter, vec3 kolo) {
    bool res = loadOBJ(model, this->vertices, this->uvs, this->normals, this->vertexCount);
    if(!res) {
        fprintf(stderr,"Blad - nie wczytano modelu - cube");
        exit(1);
    }
    position = vec3(0.0,0.0,0.0);
    start = starter;
    ruchGasiennic = starter;
    przesunDoZera = vec3(0.0f,-3.29f,-0.91359f);
    angleZ = 0.0f;
    angleX = -90.0f;
    angleXX = 0.0f;
    angleY = 0.0f;
    ustawKolo = kolo;
}

Cube::~Cube() {
    vertices.clear();
    uvs.clear();
    normals.clear();
}

void Cube::drawSolid(GLuint &tex, ShaderProgram *sp) {
    float *verts= &(this->vertices[0]);
    float *normals= &(this->normals[0]);
	float *texCoords= &(this->uvs[0]);
	unsigned int vertexCount= this->vertexCount;

    mat4 M=mat4(1.0f);
	M=rotate(M,-90 * PI / 180,vec3(1.0f,0.0f,0.0f));
	M=translate(M,start);
	M=translate(M,position);

	M=translate(M,vec3(-start[0],-start[1],-start[2]));
    M=rotate(M,this-> angleZ * PI / 180,vec3(0.0f, 0.0f, 1.0f));

    M=translate(M,vec3(ustawKolo[0],ustawKolo[1],ustawKolo[2]));
    M=rotate(M,this-> angleY * PI / 180,vec3(1.0f, 0.0f, 0.0f));
    M=translate(M,vec3(-ustawKolo[0],-ustawKolo[1],-ustawKolo[2]));
    M=rotate(M,this-> angleXX * PI / 180,vec3(1.0f, 0.0f, 0.0f));
    M=translate(M,vec3(start[0],start[1],start[2]));

    M=translate(M,this->ruchGasiennic-this->start);

	glUniformMatrix4fv(sp->u("M"),1,false,value_ptr(M));

	glEnableVertexAttribArray(sp->a("vertex"));  //Włącz przesyłanie danych do atrybutu vertex
    glVertexAttribPointer(sp->a("vertex"),4,GL_FLOAT,false,0,verts); //Wskaż tablicę z danymi dla atrybutu vertex

    glEnableVertexAttribArray(sp->a("normal"));  //Włącz przesyłanie danych do atrybutu normal
    glVertexAttribPointer(sp->a("normal"),4,GL_FLOAT,false,0,normals); //Wskaż tablicę z danymi dla atrybutu normal

    glEnableVertexAttribArray(sp->a("texCoord0"));  //Włącz przesyłanie danych do atrybutu texCoord0
    glVertexAttribPointer(sp->a("texCoord0"),2,GL_FLOAT,false,0,texCoords); //Wskaż tablicę z danymi dla atrybutu texCoord0

	glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D,tex);

	glDrawArrays(GL_TRIANGLES,0,vertexCount);

	glDisableVertexAttribArray(sp->a("vertex"));  //Wyłącz przesyłanie danych do atrybutu vertex
    glDisableVertexAttribArray(sp->a("normal"));  //Wyłącz przesyłanie danych do atrybutu normal
    glDisableVertexAttribArray(sp->a("texCoord0"));  //Wyłącz przesyłanie danych do atrybutu texCoord0

}
