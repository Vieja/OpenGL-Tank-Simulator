#ifndef LUFA_H
#define LUFA_H

#include "model.h"
#include "shaderprogram.h"

class Lufa: public Model {
public:
    Lufa();
    ~Lufa();
    float podniesienie;
    void drawSolid(GLuint &tex, ShaderProgram *sp);
};

#endif // LUFA_H
