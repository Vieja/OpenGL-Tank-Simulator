#include <stdio.h>
#include <cstdlib>

#include "niebo.h"
#include "loadOBJ.h"
#include "shaderprogram.h"

#define model "modele/niebo.obj"

using namespace glm;

Niebo::Niebo() {
    bool res = loadOBJ(model, this->vertices, this->uvs, this->normals, this->vertexCount);
    if(!res) {
        fprintf(stderr,"Blad - nie wczytano modelu - niebo");
        exit(1);
    } else fprintf(stderr,"Niebo - wczytano\n");
    position = vec3(0.0f,0.0f,0.0f);
    scale = vec3(40.0f,40.0f,40.0f);
    angleX = 0.0f;
}

Niebo::~Niebo() {
    vertices.clear();
    uvs.clear();
    normals.clear();
}

void Niebo::drawSolid(GLuint &tex, ShaderProgram *sp) {
    float *verts= &(this->vertices[0]);
    float *normals= &(this->normals[0]);
	float *texCoords= &(this->uvs[0]);
	unsigned int vertexCount= this->vertexCount;

    glm::mat4 M=glm::mat4(1.0f);
	M=glm::translate(M,vec3(position[0],position[2],-position[1]));
	M=glm::scale(M,scale);
	M=rotate(M,90 * PI / 180,vec3(1.0,0.0,0.0));
	M=rotate(M,angleX,vec3(0.0,0.0,1.0));

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
