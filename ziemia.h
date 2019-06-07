#ifndef ZIEMIA_H
#define ZIEMIA_H

#include "model.h"

class Ziemia: public Model {
public:
    Ziemia();
    ~Ziemia();
    void drawSolid(GLuint &tex,glm::mat4 &V);
};
#endif // ZIEMIA_H
