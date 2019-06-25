#ifndef LOADOBJ_H
#define LOADOBJ_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <stdlib.h>
#include <stdio.h>
#include <vector>


bool loadOBJ(const char * path,
             std::vector < float > & out_vertices,
             std::vector < float > & out_uvs,
             std::vector < float > & out_normals,
             int &vertexCount
            );

#endif

