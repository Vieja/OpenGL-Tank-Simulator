#ifndef MODEL_H
#define MODEL_H

#include <GL/glew.h>
#include <vector>
#include <glm/glm.hpp>
#include <GLFW/glfw3.h>
#include "constants.h"
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "shaderprogram.h"

using namespace glm;

class Model {
    public:
        int vertexCount;
        std::vector< float > vertices;
        std::vector< float > uvs;
        std::vector< float > normals;
        virtual ~Model(){};
        vec3 position;
        vec3 przesunDoZera;
        vec3 rotation;
        vec3 scale;
        float angleX;
        float angleY;
        float angleZ;
        float obrot;
        virtual void drawSolid(GLuint &tex, ShaderProgram *sp)=0;
};



#endif // MODEL_H
