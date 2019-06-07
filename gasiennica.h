#ifndef GASIENNICA_H
#define GASIENNICA_H

#include "model.h"

class Gasiennica: public Model {
public:
    Gasiennica(vec3 starter);
    ~Gasiennica();
    vec3 start;
    void drawSolid(GLuint &tex,glm::mat4 &V);
};

#endif // GASIENNICA_H
