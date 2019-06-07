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

#ifndef TEAPOT_H
#define TEAPOT_H

//Utah teapot model made out of triangles
//Contains arrays
//vertices - vertex positions in homogenous coordinates
//normals -vertex normals in homogenous coordinates (flat shading)
//vertexNormals - vertex normals in homogenous coordinates (smooth shading)
//texCoords -  texturing coordinates
//colors - vertex colors (rgba)
//TBN friendly
//Culling GL_CW

#include "model.h"

namespace Models {


	namespace TeapotInternal {
		extern float vertices[];
		extern float normals[];
		extern float vertexNormals[];
		extern float texCoords[];
		extern float colors[];
		extern unsigned int vertexCount;
	}

	class Teapot: public Model {
		public:
			Teapot();
			virtual ~Teapot();
			virtual void drawSolid(bool smooth=true);
	};

	extern Teapot teapot;

}
#endif
