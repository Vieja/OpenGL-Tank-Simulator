#include <stdio.h>
#include <cstdlib>

#include "gasiennica.h"
#include "loadOBJ.h"
#include "shaderprogram.h"

#define model "modele/gasiennica.obj"

using namespace glm;

Gasiennica::Gasiennica(vec3 starter) {
    bool res = loadOBJ(model, this->vertices, this->uvs, this->normals, this->vertexCount);
    if(!res) {
        fprintf(stderr,"Blad - nie wczytano modelu - gasiennica");
        exit(1);
    } else fprintf(stderr,"Gasiennica - wczytano\n");
    position = starter;
    start = starter;
    angleZ = 0.0f;
}

Gasiennica::~Gasiennica() {
    vertices.clear();
    uvs.clear();
    normals.clear();
}

void Gasiennica::drawSolid(GLuint &tex, ShaderProgram *sp) {
    float *verts= &(this->vertices[0]);
    float *normals= &(this->normals[0]);
	float *texCoords= &(this->uvs[0]);
	unsigned int vertexCount= this->vertexCount;

    mat4 M=glm::mat4(1.0f);
	M=rotate(M,-90 * PI / 180,vec3(1.0f,0.0f,0.0f));
	M=translate(M,position);

	M=translate(M,vec3(-start[0],-start[1],-start[2]));
    M=rotate(M,this-> angleZ * PI / 180,vec3(0.0f, 0.0f, 1.0f));
    M=translate(M,vec3(start[0],start[1],start[2]));

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
