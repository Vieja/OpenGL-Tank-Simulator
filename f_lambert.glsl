#version 330


out vec4 pixelColor; //Zmienna wyjsciowa fragment shadera. Zapisuje sie do niej ostateczny (prawie) kolor piksela

//Zmienne interpolowane
in vec4 i_color;

void main(void) {
	pixelColor=i_color;
}
