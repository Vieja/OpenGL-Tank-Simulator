#version 330

//Zmienne jednorodne
uniform mat4 P;
uniform mat4 V;
uniform mat4 M;
uniform vec4 lp[8]; //Współrzędne źródła światła w przestrzeni świata

//Atrybuty
in vec4 vertex; //wspolrzedne wierzcholka w przestrzeni modelu
in vec4 normal; //wspolrzedne wektora normalnego w przestrzeni modelu
in vec2 texCoord0; //współrzędna teksturowania

//Zmienne interpolowane
out vec4 l[8];
out vec4 n;
out vec4 v;

out vec2 iTexCoord0;
out vec2 iTexCoord1;

void main(void) {
    for (int i=0;i<8;i++) {
        l[i]=normalize(V*(lp[i]-M*vertex)); //Wektor "do światła" w przestrzeni oka
    }
    n=normalize(V*M*normal); //Wektor normalny w przestrzeni oka
    v=normalize(vec4(0,0,0,1)-V*M*vertex); //Wektor "do obserwatora" w przestrzeni oka

    iTexCoord0=texCoord0; //Zapewnienie interpolacji współrzędnych teksturowania podanych poprzez atrybut
    iTexCoord1=(n.xy+1)/2; //Wyliczenie współrzędnych do environment mapping

    gl_Position=P*V*M*vertex;
}
