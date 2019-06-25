#ifndef ZIEMIA_H
#define ZIEMIA_H

#include "model.h"
#include "shaderprogram.h"

class Ziemia: public Model {
public:
    Ziemia();
    ~Ziemia();
    void drawSolid(GLuint &tex, ShaderProgram *sp);
};

#endif // ZIEMIA_H
