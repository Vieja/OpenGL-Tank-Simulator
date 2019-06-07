#ifndef KADLUB_H
#define KADLUB_H

#include "model.h"

class Kadlub: public Model {
public:
    Kadlub();
    ~Kadlub();
    void drawSolid(GLuint &tex,glm::mat4 &V);
};

#endif // KADLUB_H
