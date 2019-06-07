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

#ifndef TORUS_H
#define TORUS_H

//Torus model made out of triangles
//Contains arrays:
//vertices - vertex positions in homogenous coordinates
//normals - vertex normals in homogenous coordinates
//texCoords - texturing coordinates


#include "model.h"


namespace Models {

	using namespace std;
	using namespace glm;

	class Torus: public Model {

		public:
			Torus();
			Torus(float R,float r,float mainDivs,float tubeDivs);
			virtual ~Torus();
			virtual void drawSolid(bool smooth=true);

		private:
			vector<vec4> internalVertices;
			vector<vec4> internalFaceNormals;
			vector<vec4> internalVertexNormals;

			inline float d2r(float deg);
			vec4 generateTorusPoint(float R,float r,float alpha,float beta);
			vec4 computeVertexNormal(float alpha,float beta);
			vec4 computeFaceNormal(vector<vec4> &face);
			void generateTorusFace(vector<vec4> &vertices, vector<vec4> &vertexNormals, vec4 &faceNormal,float R,float r,float alpha,float beta,float step_alpha,float step_beta);
			void buildTorus(float R,float r,float mainDivs,float tubeDivs);

	};

	extern Torus torus;

}

#endif
