/*
Niniejszy program jest wolnym oprogramowaniem; mo¿esz go
rozprowadzaæ dalej i / lub modyfikowaæ na warunkach Powszechnej
Licencji Publicznej GNU, wydanej przez Fundacjê Wolnego
Oprogramowania - wed³ug wersji 2 tej Licencji lub(wed³ug twojego
wyboru) którejœ z póŸniejszych wersji.

Niniejszy program rozpowszechniany jest z nadziej¹, i¿ bêdzie on
u¿yteczny - jednak BEZ JAKIEJKOLWIEK GWARANCJI, nawet domyœlnej
gwarancji PRZYDATNOŒCI HANDLOWEJ albo PRZYDATNOŒCI DO OKREŒLONYCH
ZASTOSOWAÑ.W celu uzyskania bli¿szych informacji siêgnij do
Powszechnej Licencji Publicznej GNU.

Z pewnoœci¹ wraz z niniejszym programem otrzyma³eœ te¿ egzemplarz
Powszechnej Licencji Publicznej GNU(GNU General Public License);
jeœli nie - napisz do Free Software Foundation, Inc., 59 Temple
Place, Fifth Floor, Boston, MA  02110 - 1301  USA
*/


#ifndef SHADERPROGRAM_H
#define SHADERPROGRAM_H

#include "GL/glew.h"
#include "stdio.h"



class ShaderProgram {
private:
	GLuint shaderProgram; //Uchwyt reprezentuj¹cy program cieniujacy
	GLuint vertexShader; //Uchwyt reprezentuj¹cy vertex shader
	GLuint geometryShader; //Uchwyt reprezentuj¹cy geometry shader
	GLuint fragmentShader; //Uchwyt reprezentuj¹cy fragment shader
	char* readFile(const char* fileName); //metoda wczytuj¹ca plik tekstowy do tablicy znaków
	GLuint loadShader(GLenum shaderType,const char* fileName); //Metoda wczytuje i kompiluje shader, a nastêpnie zwraca jego uchwyt
public:
	ShaderProgram(const char* vertexShaderFile,const char* geometryShaderFile,const char* fragmentShaderFile);
	~ShaderProgram();
	void use(); //W³¹cza wykorzystywanie programu cieniuj¹cego
	GLuint u(const char* variableName); //Pobiera numer slotu zwi¹zanego z dan¹ zmienn¹ jednorodn¹
	GLuint a(const char* variableName); //Pobiera numer slotu zwi¹zanego z danym atrybutem
};



#endif

