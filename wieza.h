#ifndef WIEZA_H
#define WIEZA_H

#include "model.h"
#include "shaderprogram.h"

class Wieza: public Model {
public:
    Wieza();
    ~Wieza();
    void drawSolid(GLuint &tex, ShaderProgram *sp);
};

#endif // WIEZA_H
