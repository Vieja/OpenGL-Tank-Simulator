#include <stdio.h>
#include <cstdlib>

#include "ziemia.h"
#include "loadOBJ.h"
#include "shaderprogram.h"

#define model "modele/ziemia.obj"

using namespace glm;

Ziemia::Ziemia() {
    bool res = loadOBJ(model, this->vertices, this->uvs, this->normals, this->vertexCount);
    if(!res) {
        fprintf(stderr,"Blad - nie wczytano modelu - ziemia");
        exit(1);
    } else fprintf(stderr,"Ziemia - wczytano\n");
    position = vec3(0.0f,0.0f,-1.75f);
}

Ziemia::~Ziemia() {
    vertices.clear();
    uvs.clear();
    normals.clear();
}

void Ziemia::drawSolid(GLuint &tex, ShaderProgram *sp) {
    float *verts= &(this->vertices[0]);
    float *normals= &(this->normals[0]);
	float *texCoords= &(this->uvs[0]);
	unsigned int vertexCount= this->vertexCount;

    glm::mat4 M=glm::mat4(1.0f);
	M=glm::rotate(M,-90 * PI / 180,glm::vec3(1.0f,0.0f,0.0f));
	M=glm::translate(M,position);

	glUniformMatrix4fv(sp->u("M"),1,false,glm::value_ptr(M));

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
