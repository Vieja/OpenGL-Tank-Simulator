#ifndef LUFA_H
#define LUFA_H

#include "model.h"

class Lufa: public Model {
public:
    Lufa();
    ~Lufa();
    float podniesienie;
    void drawSolid(GLuint &tex,glm::mat4 &V);
};

#endif // LUFA_H
