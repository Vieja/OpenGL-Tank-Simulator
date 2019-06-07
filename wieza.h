#ifndef WIEZA_H
#define WIEZA_H

#include "model.h"

class Wieza: public Model {
public:
    Wieza();
    ~Wieza();
    void drawSolid(GLuint &tex,glm::mat4 &V);
};

#endif // WIEZA_H
