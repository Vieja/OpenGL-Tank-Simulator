#ifndef KOLOL_H
#define KOLOL_H

#include "model.h"

class KoloL: public Model {
public:
    KoloL(vec3 starter);
    ~KoloL();
    vec3 start;
    void drawSolid(GLuint &tex,glm::mat4 &V);
};

#endif // KOLOL_H
