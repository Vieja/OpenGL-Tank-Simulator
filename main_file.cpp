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

#define GLM_FORCE_RADIANS
#define GLM_FORCE_SWIZZLE

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <stdlib.h>
#include <stdio.h>
#include "constants.h"
#include "lodepng.h"
#include "shaderprogram.h"
#include "myCube.h"
#include "myTeapot.h"
#include "allmodels.h"
#include "alltextures.h"
#include "camera.h"
#include <iostream>

Camera *kamera;
Kadlub *kadlub;
Wieza *wieza;
Lufa *lufa;
Ziemia *ziemia;
Niebo *niebo;
Gasiennica *gasiennicaL;
Gasiennica *gasiennicaP;
KoloS *koloSLp;
KoloS *koloSLt;
KoloS *koloSPp;
KoloS *koloSPt;

KoloL *koloLL1;
KoloL *koloLL2;
KoloL *koloLL3;
KoloL *koloLL4;
KoloL *koloLL5;

KoloL *koloLP1;
KoloL *koloLP2;
KoloL *koloLP3;
KoloL *koloLP4;
KoloL *koloLP5;

std::vector<Model*> modele;
std::vector<Model*> kolaLewe;
std::vector<Model*> kolaPrawe;
std::vector<Cube*> prostokaty;

float aspectRatio=1;
float speed_x=0;
float speed_y=0;
float predkoscJazdy=0;
float obrotWiezy=0;
float podniesienie=0;
float skret=0;

float theta=0;
float phi=0;
float radius=0;

ShaderProgram *sp;

//Uchwyty na tekstury
GLuint texZiemia;
GLuint texKadlub;
GLuint texWieza;
GLuint texBloczek;
GLuint texGasiennica;
GLuint texKolo;
GLuint texNiebo;

bool up_pressed = false;
bool down_pressed = false;
bool left_pressed = false;
bool right_pressed = false;
bool w_pressed = false;
bool a_pressed = false;
bool s_pressed = false;
bool d_pressed = false;
bool q_pressed = false;
bool e_pressed = false;
bool r_pressed = false;
bool f_pressed = false;


//Procedura obsługi błędów
void error_callback(int error, const char* description) {
	fputs(description, stderr);
}

void keyCallback(GLFWwindow* window,int key,int scancode,int action,int mods) {
    if (action==GLFW_PRESS) {
        if (key==GLFW_KEY_UP) up_pressed=true;
        if (key==GLFW_KEY_DOWN) down_pressed=true;
        if (key==GLFW_KEY_LEFT) left_pressed=true;
        if (key==GLFW_KEY_RIGHT) right_pressed=true;
        if (key==GLFW_KEY_W) w_pressed=true;
        if (key==GLFW_KEY_A) a_pressed=true;
        if (key==GLFW_KEY_S) s_pressed=true;
        if (key==GLFW_KEY_D) d_pressed=true;
        if (key==GLFW_KEY_Q) q_pressed=true;
        if (key==GLFW_KEY_E) e_pressed=true;
        if (key==GLFW_KEY_R) r_pressed=true;
        if (key==GLFW_KEY_F) f_pressed=true;
    }
    if (action==GLFW_RELEASE) {
        if (key==GLFW_KEY_UP) up_pressed=false;
        if (key==GLFW_KEY_DOWN) down_pressed=false;
        if (key==GLFW_KEY_LEFT) left_pressed=false;
        if (key==GLFW_KEY_RIGHT) right_pressed=false;
        if (key==GLFW_KEY_W) w_pressed=false;
        if (key==GLFW_KEY_A) a_pressed=false;
        if (key==GLFW_KEY_S) s_pressed=false;
        if (key==GLFW_KEY_D) d_pressed=false;
        if (key==GLFW_KEY_Q) q_pressed=false;
        if (key==GLFW_KEY_E) e_pressed=false;
        if (key==GLFW_KEY_R) r_pressed=false;
        if (key==GLFW_KEY_F) f_pressed=false;
    }
}

void windowResizeCallback(GLFWwindow* window,int width,int height) {
    if (height==0) return;
    aspectRatio=(float)width/(float)height;
    glViewport(0,0,width,height);
}

void wczytajModele(){
    kamera = new Camera;
    kadlub = new Kadlub();
    wieza = new Wieza();
    lufa = new Lufa();
    ziemia = new Ziemia();
    niebo = new Niebo();
    gasiennicaL = new Gasiennica(vec3(1.45f,0.1f,0.0f));
    gasiennicaP = new Gasiennica(vec3(-1.35f,0.1f,0.0f));

    koloSLp = new KoloS(vec3(1.45f,0.1f,0.0f));
    koloSLt = new KoloS(vec3(1.45f,0.1+6.201,0.0f));
    koloSPp = new KoloS(vec3(-1.35f,0.1,0.0f));
    koloSPt = new KoloS(vec3(-1.35f,0.1+6.201,0.0f));

    koloLL1 = new KoloL(vec3(1.45f,-2.1f-0.155f,0.0f));
    koloLL2 = new KoloL(vec3(1.45f,-0.98f-0.155f,0.0f));
    koloLL3 = new KoloL(vec3(1.45f,0.21f-0.155f,0.0f));
    koloLL4 = new KoloL(vec3(1.45f,1.21f-0.155f,0.0f));
    koloLL5 = new KoloL(vec3(1.45f,2.29f-0.155f,0.0f));

    koloLP1 = new KoloL(vec3(-1.35f,-2.1f-0.155f,0.0f));
    koloLP2 = new KoloL(vec3(-1.35f,-0.98f-0.155f,0.0f));
    koloLP3 = new KoloL(vec3(-1.35f,0.21f-0.155f,0.0f));
    koloLP4 = new KoloL(vec3(-1.35f,1.21f-0.155f,0.0f));
    koloLP5 = new KoloL(vec3(-1.35f,2.29f-0.155f,0.0f));

    //prosta gora
    for (int i=0; i<18;i++) {
        Cube *c = new Cube(vec3(1.45f,5.05f-i*0.35f,0.08f),vec3(0.0f,0.0f,0.0f));
        Cube *d = new Cube(vec3(-1.35f,5.05f-i*0.35f,0.08f),vec3(0.0f,0.0f,0.0f));
        prostokaty.push_back(c);
        prostokaty.push_back(d);
        modele.push_back(c);
        modele.push_back(d);
    }
    //prosta dol
    for (int i=18; i<32;i++) {
        Cube *c = new Cube(vec3(1.45f,4.25f-i*0.335f,-1.0f),vec3(0.0f,0.0f,0.0f));
        Cube *d = new Cube(vec3(-1.35f,4.25f-i*0.335f,-1.0f),vec3(0.0f,0.0f,0.0f));
        prostokaty.push_back(c);
        prostokaty.push_back(d);
        modele.push_back(c);
        modele.push_back(d);
    }
    //kolo tyl
    for (int i=32; i<36;i++) {
        Cube *c = new Cube(vec3(1.45f,5.05f,0.08f),vec3(1.45f,3.0f,-0.929f));
        Cube *d = new Cube(vec3(-1.35f,5.05f,0.08f),vec3(1.45f,3.0f,-0.929f));
        prostokaty.push_back(c);
        prostokaty.push_back(d);
        modele.push_back(c);
        modele.push_back(d);
    }
    //kolo przod
    for (int i=36; i<40;i++) {
        Cube *c = new Cube(vec3(1.45f,-1.2f,0.08f),vec3(1.45f,-3.2f,-0.929f));
        Cube *d = new Cube(vec3(-1.35f,-1.2f,0.08f),vec3(1.45f,-3.2f,-0.929f));
        prostokaty.push_back(c);
        prostokaty.push_back(d);
        modele.push_back(c);
        modele.push_back(d);
    }

    //pochylenie przod
    for (int i=40; i<44;i++) {
        Cube *c = new Cube(vec3(1.45f,-0.69f-(40-i)*0.33f,-1.79f),vec3(0.0f,0.0f,0.0f));
        Cube *d = new Cube(vec3(-1.35f,-0.69f-(40-i)*0.33f,-1.79f),vec3(0.0f,0.0f,0.0f));
        prostokaty.push_back(c);
        prostokaty.push_back(d);
        modele.push_back(c);
        modele.push_back(d);
    }
    //pochylenie tyl
    for (int i=44; i<48;i++) {
        Cube *c = new Cube(vec3(1.45f,4.65f+(44-i)*0.33f,-1.71f),vec3(0.0f,0.0f,0.0f));
        Cube *d = new Cube(vec3(-1.35f,4.65f+(44-i)*0.33f,-1.71f),vec3(0.0f,0.0f,0.0f));
        prostokaty.push_back(c);
        prostokaty.push_back(d);
        modele.push_back(c);
        modele.push_back(d);
    }

    modele.push_back(niebo);
    modele.push_back(kadlub);
    modele.push_back(wieza);
    modele.push_back(lufa);
    modele.push_back(gasiennicaL);
    modele.push_back(gasiennicaP);

    modele.push_back(koloSLp);
    modele.push_back(koloSLt);
    modele.push_back(koloSPp);
    modele.push_back(koloSPt);

    modele.push_back(koloLL1);
    modele.push_back(koloLL2);
    modele.push_back(koloLL3);
    modele.push_back(koloLL4);
    modele.push_back(koloLL5);

    modele.push_back(koloLP1);
    modele.push_back(koloLP2);
    modele.push_back(koloLP3);
    modele.push_back(koloLP4);
    modele.push_back(koloLP5);

    kolaLewe.push_back(koloSLp);
    kolaLewe.push_back(koloSLt);
    kolaLewe.push_back(koloLL1);
    kolaLewe.push_back(koloLL2);
    kolaLewe.push_back(koloLL3);
    kolaLewe.push_back(koloLL4);
    kolaLewe.push_back(koloLL5);

    kolaPrawe.push_back(koloSPp);
    kolaPrawe.push_back(koloSPt);
    kolaPrawe.push_back(koloLP1);
    kolaPrawe.push_back(koloLP2);
    kolaPrawe.push_back(koloLP3);
    kolaPrawe.push_back(koloLP4);
    kolaPrawe.push_back(koloLP5);
}

//Funkcja wczytująca teksturę
GLuint readTexture(const char* filename) {
    GLuint tex;
    glActiveTexture(GL_TEXTURE0);

    //Wczytanie do pamięci komputera
    std::vector<unsigned char> image;   //Alokuj wektor do wczytania obrazka
    unsigned width, height;   //Zmienne do których wczytamy wymiary obrazka
    //Wczytaj obrazek
    unsigned error = lodepng::decode(image, width, height, filename);

    //Import do pamięci karty graficznej
    glGenTextures(1,&tex); //Zainicjuj jeden uchwyt
    glBindTexture(GL_TEXTURE_2D, tex); //Uaktywnij uchwyt
    //Wczytaj obrazek do pamięci KG skojarzonej z uchwytem
    glTexImage2D(GL_TEXTURE_2D, 0, 4, width, height, 0,
    GL_RGBA, GL_UNSIGNED_BYTE, (unsigned char*) image.data());

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    return tex;
}

//Procedura inicjująca
void initOpenGLProgram(GLFWwindow* window) {
	//************Tutaj umieszczaj kod, który należy wykonać raz, na początku programu************
	glClearColor(0,0,0,1);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_TEXTURE_2D);
    glEnable(GL_NORMALIZE);
	glfwSetWindowSizeCallback(window,windowResizeCallback);
	glfwSetKeyCallback(window,keyCallback);

	sp=new ShaderProgram("vertex.glsl",NULL,"fragment.glsl");

    texZiemia=readTexture(tekstura_ziemia);
    texKadlub=readTexture(tekstura_kadlub);
    texWieza=readTexture(tekstura_wieza);
    texBloczek=readTexture(tekstura_bloczek);
    texGasiennica=readTexture(tekstura_gasiennica);
    texKolo=readTexture(tekstura_kolo);
    texNiebo=readTexture(tekstura_niebo);
}

//Zwolnienie zasobów zajętych przez program
void freeOpenGLProgram(GLFWwindow* window) {
    //************Tutaj umieszczaj kod, który należy wykonać po zakończeniu pętli głównej************
    glDeleteTextures(1,&texZiemia);
    glDeleteTextures(1,&texKadlub);
    glDeleteTextures(1,&texWieza);
    glDeleteTextures(1,&texBloczek);
    glDeleteTextures(1,&texGasiennica);
    glDeleteTextures(1,&texKolo);
    glDeleteTextures(1,&texNiebo);
    delete sp;
}

//Procedura rysująca zawartość sceny
void drawScene(GLFWwindow* window, float angle, float wheelL, float wheelP, float obrotWieza, float depression, float ruchNieba, float s, float t, float r) {
	//************Tutaj umieszczaj kod rysujący obraz******************l
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    kamera->findPointOnSphere(s, t, r);
    kamera->przesunDoModelu(kadlub->position[0],kadlub->position[2],kadlub->position[1]);

    glm::mat4 V=glm::lookAt(
    glm::vec3(kamera->x,kamera->y,kamera->z),
    glm::vec3(kadlub->position[0],-kadlub->position[2],-kadlub->position[1]),
    glm::vec3(0.0f,1.0f,0.0f));

    glm::mat4 P=glm::perspective(50.0f*PI/180.0f, aspectRatio, 0.01f, 50.0f); //Wylicz macierz rzutowania

    sp->use();//Aktywacja programu cieniującego
    //Przeslij parametry programu cieniującego do karty graficznej
    glUniformMatrix4fv(sp->u("P"),1,false,glm::value_ptr(P));
    glUniformMatrix4fv(sp->u("V"),1,false,glm::value_ptr(V));
    glUniform4f(sp->u("lp"),0,1000,0,1); //Współrzędne źródła światła
    //glUniform4f(sp->u("lp2"),0,-100,50,1);
    glUniform4f(sp->u("lp2"),0,0,100,1);

    glUniform1i(sp->u("textureMap0"),0);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D,texKadlub);

    glUniform1i(sp->u("textureMap1"),1);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D,texZiemia);

    kadlub->drawSolid(texKadlub, sp);

    wieza->obrot = obrotWieza;
    lufa->obrot = obrotWieza;
    lufa->podniesienie = depression;
    wieza->drawSolid(texWieza, sp);
    lufa->drawSolid(texWieza, sp);
    ziemia->drawSolid(texZiemia, sp);

    niebo->angleX = ruchNieba;
    niebo->drawSolid(texNiebo, sp);

    gasiennicaL->drawSolid(texGasiennica, sp);
    gasiennicaP->drawSolid(texGasiennica, sp);

    for(int i=0; i < kolaLewe.size(); i++){
        kolaLewe[i]->obrot = wheelL;
        kolaPrawe[i]->obrot = wheelP;
        kolaLewe[i]->drawSolid(texKolo, sp);
        kolaPrawe[i]->drawSolid(texKolo, sp);
    }

//    glEnableVertexAttribArray(sp->a("vertex"));  //Włącz przesyłanie danych do atrybutu vertex
//    glVertexAttribPointer(sp->a("vertex"),4,GL_FLOAT,false,0,verts); //Wskaż tablicę z danymi dla atrybutu vertex
//
//    glEnableVertexAttribArray(sp->a("normal"));  //Włącz przesyłanie danych do atrybutu normal
//    glVertexAttribPointer(sp->a("normal"),4,GL_FLOAT,false,0,normals); //Wskaż tablicę z danymi dla atrybutu normal
//
//    glEnableVertexAttribArray(sp->a("texCoord0"));  //Włącz przesyłanie danych do atrybutu texCoord0
//    glVertexAttribPointer(sp->a("texCoord0"),2,GL_FLOAT,false,0,texCoords); //Wskaż tablicę z danymi dla atrybutu texCoord0

//    glDrawArrays(GL_TRIANGLES,0,vertexCount); //Narysuj obiekt


    //TESSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSST

  //  M=glm::translate(M,glm::vec3(3.0f,3.0f,3.0f));
  //  glUniformMatrix4fv(sp->u("M"),1,false,glm::value_ptr(M));

  //  glActiveTexture(GL_TEXTURE0);
  //  glBindTexture(GL_TEXTURE_2D,texGasiennica);

  //   glDrawArrays(GL_TRIANGLES,0,vertexCount);


//    glDisableVertexAttribArray(sp->a("vertex"));  //Wyłącz przesyłanie danych do atrybutu vertex
//    glDisableVertexAttribArray(sp->a("normal"));  //Wyłącz przesyłanie danych do atrybutu normal
//    glDisableVertexAttribArray(sp->a("texCoord0"));  //Wyłącz przesyłanie danych do atrybutu texCoord0



    for(int i=0; i < 36; i++){
        if(predkoscJazdy!=0) prostokaty[i]->ruchGasiennic[1]-= predkoscJazdy/120;
        else if (a_pressed) {
            if (i % 2 == 0) {
                prostokaty[i]->ruchGasiennic[1]-= (-2*PI * 1/10) /120;
            } else {
                prostokaty[i]->ruchGasiennic[1]+= (-2*PI * 1/10) /120;
            }
        }
        else if (d_pressed) {
            if (i % 2 == 0) {
                prostokaty[i]->ruchGasiennic[1]+= (-2*PI * 1/10) /120;
            } else {
                prostokaty[i]->ruchGasiennic[1]-= (-2*PI * 1/10) /120;
                }
        }
        if(prostokaty[i]->ruchGasiennic[1] < -1.2f) {
                float tmp = prostokaty[i]->ruchGasiennic[1] -= -1.2f;
                prostokaty[i]->ruchGasiennic[1] = 5.05f+tmp;
        }
        if(prostokaty[i]->ruchGasiennic[1] > 5.05f) {
                float tmp = prostokaty[i]->ruchGasiennic[1] -= 5.05f;
                prostokaty[i]->ruchGasiennic[1] = -1.2f+tmp;
        }
        prostokaty[i]->drawSolid(texBloczek,sp);
    }

    for(int i=36; i < 64; i++){
        if(predkoscJazdy!=0) prostokaty[i]->ruchGasiennic[1]+= predkoscJazdy/120;
        else if (a_pressed) {
            if (i % 2 == 0) {
                prostokaty[i]->ruchGasiennic[1]+= (-2*PI * 1/10) /120;
            } else {
                prostokaty[i]->ruchGasiennic[1]-= (-2*PI * 1/10) /120;
            }
        }
        else if (d_pressed) {
            if (i % 2 == 0) {
                prostokaty[i]->ruchGasiennic[1]-= (-2*PI * 1/10) /120;
            } else {
                prostokaty[i]->ruchGasiennic[1]+= (-2*PI * 1/10) /120;
            }
        }
        if(prostokaty[i]->ruchGasiennic[1] < -0.45f) {
                float tmp = prostokaty[i]->ruchGasiennic[1] -= -0.45f;
                prostokaty[i]->ruchGasiennic[1] = 4.25f+tmp;
                prostokaty[i]->ruchGasiennic[2] = -1.1f;
        }
        if(prostokaty[i]->ruchGasiennic[1] > 4.25f) {
                float tmp = prostokaty[i]->ruchGasiennic[1] -= 4.25f;
                prostokaty[i]->ruchGasiennic[1] = -0.45f+tmp;
                prostokaty[i]->ruchGasiennic[2] = -1.1f;
        }
        prostokaty[i]->drawSolid(texBloczek,sp);
    }

    for(int i=64; i < 72; i++){
        int iter = i-80;
        float tmp;
        if (iter % 2 == 0) {
            iter = iter/2;
            tmp = wheelL*54.778f-( iter*40.0f );
        } else {
            iter = iter/2 + 1;
            tmp = wheelP*54.778f-( iter*40.0f );
        }
        while (tmp<-160 & tmp+160<0) tmp+=160;
        while (tmp>0 & tmp-160>-160) tmp-=160;
        prostokaty[i]->angleY = tmp;
        prostokaty[i]->drawSolid(texBloczek,sp);
    }

    for(int i=72; i < 80; i++){
        int iter = i-80;
        float tmp;
        if (iter % 2 == 0) {
            iter = iter/2;
            tmp = wheelL*54.778f-( iter*40.0f );
        } else {
            iter = iter/2 + 1;
            tmp = wheelP*54.778f+( iter*40.0f );
        }
        while (tmp>160 & tmp-160>0) tmp-=160;
        while (tmp<0 & tmp+160<160) tmp+=160;
        prostokaty[i]->angleY = tmp;
        prostokaty[i]->drawSolid(texBloczek,sp);
    }

    for(int i=80; i < 88; i++){
        if(predkoscJazdy!=0) prostokaty[i]->ruchGasiennic[1]+= predkoscJazdy/120;
        else if (a_pressed) {
            if (i % 2 == 0) {
                prostokaty[i]->ruchGasiennic[1]+= (-2*PI * 1/10) /120;
            } else {
                prostokaty[i]->ruchGasiennic[1]-= (-2*PI * 1/10) /120;
            }
        } else if (d_pressed) {
            if (i % 2 == 0) {
                prostokaty[i]->ruchGasiennic[1]-= (-2*PI * 1/10) /120;
            } else {
                prostokaty[i]->ruchGasiennic[1]+= (-2*PI * 1/10) /120;
            }
        }
        if(prostokaty[i]->ruchGasiennic[1] < -0.69f) {
            float tmp = prostokaty[i]->ruchGasiennic[1] += 0.69f;
            prostokaty[i]->ruchGasiennic[1] = 0.3f+tmp;
        }
        if(prostokaty[i]->ruchGasiennic[1] > 0.3f) {
            float tmp = prostokaty[i]->ruchGasiennic[1] -= 0.3f;
            prostokaty[i]->ruchGasiennic[1] = -0.69f+tmp;
        }
        prostokaty[i]->angleXX=-18.5f;
        prostokaty[i]->drawSolid(texBloczek,sp);
    }

    for(int i=88; i < 96; i++){
        if(predkoscJazdy!=0) prostokaty[i]->ruchGasiennic[1]+= predkoscJazdy/120;
        else if (a_pressed) {
            if (i % 2 == 0) {
                prostokaty[i]->ruchGasiennic[1]+= (-2*PI * 1/10) /120;
            } else {
                prostokaty[i]->ruchGasiennic[1]-= (-2*PI * 1/10) /120;
            }
        } else if (d_pressed) {
            if (i % 2 == 0) {
                prostokaty[i]->ruchGasiennic[1]-= (-2*PI * 1/10) /120;
            } else {
                prostokaty[i]->ruchGasiennic[1]+= (-2*PI * 1/10) /120;
            }
        }
        if(prostokaty[i]->ruchGasiennic[1] < 3.62f) {
                float tmp = prostokaty[i]->ruchGasiennic[1] -= 3.62f;
                prostokaty[i]->ruchGasiennic[1] = 4.65f+tmp;
        }
        if(prostokaty[i]->ruchGasiennic[1] > 4.65f) {
                float tmp = prostokaty[i]->ruchGasiennic[1] -= 4.65f;
                prostokaty[i]->ruchGasiennic[1] = 3.62f+tmp;
        }
        prostokaty[i]->angleXX=18.5f;
        prostokaty[i]->drawSolid(texBloczek,sp);
    }



    glfwSwapBuffers(window); //Przerzuć tylny bufor na przedni
}

void obsluzKlikniecie(float angle){
    //oblicz predkosc jazdy
    if (w_pressed) {
            if(predkoscJazdy<2*PI) predkoscJazdy+=(2*PI * 1/120);
    }
    else if (s_pressed) {
        if(predkoscJazdy> 2*PI * 1/70 ) predkoscJazdy-=(2*PI * 1/70);
        else if(predkoscJazdy > -PI) predkoscJazdy-=(2*PI * 1/120);
    }
    else {
        if(predkoscJazdy> 2*PI * 1/200 ) predkoscJazdy-=(2*PI * 1/200);
        else if(predkoscJazdy< -2*PI * 1/200 ) predkoscJazdy+=(2*PI * 1/200);
        else predkoscJazdy = 0;
    }

    //obroc wieze
    if (q_pressed) obrotWiezy=PI/8;
    else if (e_pressed) obrotWiezy=-PI/8;
    else obrotWiezy=0;

    //podnies/obniz lufe
    if (f_pressed) {
        if (lufa->podniesienie<2*PI/60) podniesienie=2*PI * 1/80;
        else podniesienie = 0;
    } else if (r_pressed) {
        if (lufa->podniesienie>-2*PI/60) podniesienie=-2*PI * 1/80;
        else podniesienie = 0;
    } else podniesienie=0;

    //obrot czolgu
    if (a_pressed) {
        skret=-15;
    } else if (d_pressed) {
        skret=15;
    }
    else skret=0;

    //ustal przesuniecie czolgu na osiach x i y
    float ruchx;
    float ruchy;

    if (angle>=0 & angle <90) {
        ruchx = (1-(angle/90)) * predkoscJazdy/100;
        ruchy = (angle/90) * predkoscJazdy/100;
    } else if (angle>=90 & angle <180) {
        ruchx = -1* ((angle-90)/90) * predkoscJazdy/100;
        ruchy = (1-((angle-90)/90)) * predkoscJazdy/100;
    } else if (angle>=180 & angle <270) {
        ruchx = -1* (1-((angle-180)/90)) * predkoscJazdy/100;
        ruchy = -1* ((angle-180)/90) * predkoscJazdy/100;
    } else {
        ruchx = (angle-270)/90 * predkoscJazdy/100;
        ruchy = -1* (1-((angle-270)/90)) * predkoscJazdy/100;
    }

    for(int i=0; i < modele.size(); i++) {
        modele[i]->position[1]-=ruchx;
        modele[i]->position[0]-=ruchy;
        modele[i]->angleZ=-angle;
    }

    //oblicz przesuniecie kamery
     if (up_pressed) {
        if(kamera->t < -2*PI/16)
            phi=+Vcamera;
        else phi=0;
    } else if (down_pressed) {
        if(kamera->t > -2*PI/4)
            phi=-Vcamera;
        else phi=0;
    }
    else phi=0;

    if (right_pressed) theta=-Vcamera;
    else if (left_pressed) theta=+Vcamera;
    else theta=0;
}

int main(void)
{
    wczytajModele();
	GLFWwindow* window; //Wskaźnik na obiekt reprezentujący okno

	glfwSetErrorCallback(error_callback);//Zarejestruj procedurę obsługi błędów

	if (!glfwInit()) { //Zainicjuj bibliotekę GLFW
		fprintf(stderr, "Nie można zainicjować GLFW.\n");
		exit(EXIT_FAILURE);
	}

	window = glfwCreateWindow(900, 900, "OpenGL", NULL, NULL);  //Utwórz okno 500x500 o tytule "OpenGL" i kontekst OpenGL.

	if (!window) //Jeżeli okna nie udało się utworzyć, to zamknij program
	{
		fprintf(stderr, "Nie można utworzyć okna.\n");
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	glfwMakeContextCurrent(window); //Od tego momentu kontekst okna staje się aktywny i polecenia OpenGL będą dotyczyć właśnie jego.
	glfwSwapInterval(1); //Czekaj na 1 powrót plamki przed pokazaniem ukrytego bufora

	if (glewInit() != GLEW_OK) { //Zainicjuj bibliotekę GLEW
		fprintf(stderr, "Nie można zainicjować GLEW.\n");
		exit(EXIT_FAILURE);
	}

	initOpenGLProgram(window); //Operacje inicjujące

	//Główna pętla
	float angle=0;
	float wheelL=0;
	float wheelP=0;
	float wieza=0;
	float depression=0;
	float ruchNieba=0;
	float s = 2*PI/4;
	float t = -2*PI/5;
	float r = 10.0f;
	glfwSetTime(0); //Zeruj timer
	while (!glfwWindowShouldClose(window)) //Tak długo jak okno nie powinno zostać zamknięte
	{
	    obsluzKlikniecie(angle);
        angle+=skret*glfwGetTime();
        if (angle<0) angle+=360;
        if (angle>360) angle-=360;

        if (predkoscJazdy!=0) {
            wheelL+=predkoscJazdy*glfwGetTime();
            wheelP+=predkoscJazdy*glfwGetTime();
        } else if (a_pressed) {
            wheelL+= -2*PI * 1/10 *glfwGetTime();
            wheelP+= 2*PI * 1/10 *glfwGetTime();
        } else if (d_pressed){
            wheelL+= 2*PI * 1/10 *glfwGetTime();
            wheelP+= -2*PI * 1/10 *glfwGetTime();
        }

        wieza+=obrotWiezy*glfwGetTime();
        depression+=podniesienie*glfwGetTime();

        //kat obrotu sfery nieba
        ruchNieba += 2*PI * 1/500 *glfwGetTime();
        if (ruchNieba > 2*PI) ruchNieba-=2*PI;

        //kat obrotu kamery
        s+=theta*glfwGetTime();
        t+=phi*glfwGetTime();
        r+=radius*glfwGetTime();

        glfwSetTime(0); //Zeruj timer
		drawScene(window,angle,wheelL,wheelP,wieza,depression,ruchNieba,s,t,r); //Wykonaj procedurę rysującą
		glfwPollEvents(); //Wykonaj procedury callback w zalezności od zdarzeń jakie zaszły.
	}

	freeOpenGLProgram(window);

	glfwDestroyWindow(window); //Usuń kontekst OpenGL i okno
	glfwTerminate(); //Zwolnij zasoby zajęte przez GLFW
	exit(EXIT_SUCCESS);
}
