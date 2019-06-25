#ifndef KOLOS_H
#define KOLOS_H

#include "model.h"
#include "shaderprogram.h"

class KoloS: public Model {
public:
    KoloS(vec3 starter);
    ~KoloS();
    void drawSolid(GLuint &tex, ShaderProgram *sp);
};

#endif // KOLOS_H
