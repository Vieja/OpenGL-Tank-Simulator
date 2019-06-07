/*
Niniejszy program jest wolnym oprogramowaniem; możesz go
rozprowadzać dalej i / lub modyfikować na warunkach Powszechnej
Licencji Publicznej GNU, wydanej przez Fundację Wolnego
Oprogramowania - według wersji 2 tej Licencji lub(według twojego
wyboru) którejś z późniejszych wersji.

Niniejszy program rozpowszechniany jest z nadzieją, iż będzie on
użyteczny - jednak BEZ JAKIEJKOLWIEK GWARANCJI, nawet domyślnej
gwarancji PRZYDATNOŚCI HANDLOWEJ albo PRZYDATNOŚCI DO OKREŚLONYCH
ZASTOSOWAŃ.W celu uzyskania bliższych informacji sięgnij do
Powszechnej Licencji Publicznej GNU.

Z pewnością wraz z niniejszym programem otrzymałeś też egzemplarz
Powszechnej Licencji Publicznej GNU(GNU General Public License);
jeśli nie - napisz do Free Software Foundation, Inc., 59 Temple
Place, Fifth Floor, Boston, MA  02110 - 1301  USA
*/

#ifndef MODEL_H
#define MODEL_H

#include <GL/glew.h>
#include <vector>
#include <glm/glm.hpp>
#include <GLFW/glfw3.h>
#include "constants.h"
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>


using namespace glm;

class Model {
    public:
        std::vector< float > vertices;
        std::vector< float > uvs;
        std::vector< float > normals;
        unsigned int vCount;
        vec3 position;
        vec3 positionAfterTurn;
        vec3 przesunDoZera;
        vec3 rotation;
        vec3 scale;
        float angleX;
        float angleY;
        float angleZ;
        float obrot;
        virtual ~Model(){};
        virtual void drawSolid(GLuint &tex,mat4 &V)=0;
};

#endif
