#ifndef CUBE_H
#define CUBE_H

#include "model.h"

class Cube: public Model {
public:
    Cube(vec3 starter, vec3 kolo);
    ~Cube();
    vec3 start;
    vec3 ruchGasiennic;
    vec3 ustawKolo;
    float angleXX;
    void drawSolid(GLuint &tex,ShaderProgram *sp);
};

#endif // CUBE_H
