#version 330


//Zmienne interpolowane

in vec4 l[8]; //interpolowany wektor "do światła" w przestrzeni oka
in vec4 n; //interpolowany wektor normalny w przestrzeni oka
in vec4 v; //interpolowany wektor "do obserwatora" w przestrzeni oka
in vec2 iTexCoord0; //interpolowane współrzędne teksturowania dla tekstury w textureMap0
in vec2 iTexCoord1; //interpolowane współrzędne teksturowania dla tekstury w textureMap1

uniform sampler2D textureMap0; //Jednostka teksturująca 0
uniform sampler2D textureMap1; //Jednostka teksturująca 1

out vec4 pixelColor; //Zmienna wyjsciowa fragment shadera. Zapisuje sie do niej ostateczny (prawie) kolor piksela

void main(void) {
    vec4 ml[8];
    vec4 mr[8];
    float nl[8];
    float rv[8];
    vec4 kd=mix(texture(textureMap0,iTexCoord0),texture(textureMap1,iTexCoord1),0.02);  //Kolor materia?u dla ?wiat?a  rozpraszanego
    vec4 ld=vec4(0.4,0.4,0.4,1); //Kolor ?wiat?a  rozpraszanego
    vec4 ks=vec4(0.5,0.5,0.5,1); //Kolor odbi? materia?u
    vec4 ls=vec4(0.05,0.05,0.05,1); //Kolor ?wiat?a odbijanego

    vec4 mn=normalize(n);
    vec4 mv=normalize(v);
    for (int i=0;i<8;i++) {
        ml[i]=normalize(l[i]);
        mr[i]=reflect(-ml[i],mn); //Wektor kierunku odbicia w przestrzeni oka
        nl[i]=clamp(dot(mn,ml[i]),0,1); //cos k?ta pomi?dzy wektorami n i l
        rv[i]=pow(clamp(dot(mr[i],mv),0,1),100); //cos k?ta pomi?dzy wektorami r i v podniesiony do pot?gi (wyk?adnik Phonga)
    }
    vec4 temp = vec4(0,0,0,0);
    for (int i=0;i<8;i++) {
        //if (i==2) ld=vec4(0.1,0.1,0.1,1);
        temp=vec4(temp.rgb + kd.rgb*ld.rgb*nl[i] + ks.rgb*ls.rgb*rv[i],kd.a);
    }
	pixelColor=temp;
}
