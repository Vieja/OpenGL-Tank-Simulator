#ifndef KOLOS_H
#define KOLOS_H

#include "model.h"

class KoloS: public Model {
public:
    KoloS(vec3 starter);
    ~KoloS();
    vec3 start;
    void drawSolid(GLuint &tex,glm::mat4 &V);
};

#endif // KOLOS_H
