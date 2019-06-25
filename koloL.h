#ifndef KOLOL_H
#define KOLOL_H

#include "model.h"
#include "shaderprogram.h"

class KoloL: public Model {
public:
    KoloL(vec3 starter);
    ~KoloL();
    void drawSolid(GLuint &tex, ShaderProgram *sp);
};

#endif // KOLOL_H
