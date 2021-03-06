/*
	Clon del videojuego de Snake codigo original de DeividCoptero.
*/
#include <iostream>
#include<conio.h>
#include<windows.h>
#include<stdlib.h>
// Se definen las teclas direccionales.
#define ARRIBA 72
#define IZQUIERDA 75
#define DERECHA 77
#define ABAJO 80
#define ESC 27

// Logo del juego.
char inicio[50][100]=
{
	"                                                                      ",
	"       * *           **** **   * **** *  *  ****                      ",
	"        *            *    * *  * *  * ***   *                         ",
	"        *            *    *  * * **** *  *  ***                       ",
	"      *****          *    *   ** *  * *   * *                         ",
	"     * *** *     *****    *    * *  * *   * ****                      ",
	"    *********                                                         ",
	"    *********                                                         ",
	"     *******           ***********               ****************     ",
	"     *******          **************            ******************    ",
	"      *******        ****************          ******************     ",
	"       *******      ******     *******        *******                 ",
	"        *******    ******       *******      ******                   ",
	"         ***************         *****************                    ",
	"          *************           ***************                     ",
	"           ***********             *************                      ",
	"                                                                      ",
};

// Variables globales.
int cuerpo[200][2];
int n = 1;
int tam = 4;
int x = 10;
int y = 12;
int dir = 3;
int xc = 30, yc = 15;
char tecla;
int velocidad = 160, h = 1;
int score = 0;
int pos = 1;

// Funcion para pocicionar el cursor.
void gotoxy(int x, int y){
	HANDLE hCon;
	COORD dwPos;
	dwPos.X = x;
	dwPos.Y = y;
	hCon = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hCon, dwPos);
}
// Menu inicial con el splash de la serpiente.
void menu_inicial(){
	for(int i=0; i<17; i++){
		for(int j=0; j<71; j++){
			if(inicio[i][j]=='*'){
				gotoxy(j+5, i+5); printf("%c", inicio[i][j]);
			}
		}
	}
	tecla = getch();
	for(int i=0; i<17; i++){
		for(int j=0; j<71; j++){
			if(inicio[i][j]=='*'){
				gotoxy(j+5, i+5); printf(" ");
			}
		}
	}
}
// Funcion para pintar
void pintar(){
	// Lineas horizontales
	for(int i=2; i<78; i++){
		gotoxy(i, 3); printf("%c", 205);
		gotoxy(i, 23); printf("%c", 205);
	}
	// Lineas verticales
	for(int i=4; i<23; i++){
		gotoxy(2, i); printf("%c", 186);
		gotoxy(77, i); printf("%c", 186);
	}
	// Esquinas
	gotoxy(2, 3); printf("%c", 201);
	gotoxy(2, 23); printf("%c", 200);
	gotoxy(77, 3); printf("%c", 187);
	gotoxy(77, 23); printf("%c", 188);
}
void guardar_posicion(){
	cuerpo[n][0] = x;
	cuerpo[n][1] = y;
	n++;
	if(n == tam)
		n = 1;
	
}
// Funcion para dibujar el cuerpo de la serpiente.
void dibujar_cuerpo(){
	for(int i = 1; i<tam; i++){
		gotoxy(cuerpo[i][0], cuerpo[i][1]); printf("*");
	}
}
// Funcion para borrar el cuerpo de la serpiente.
void borrar_cuerpo(){
		gotoxy(cuerpo[n][0], cuerpo[n][1]); printf(" ");
}
// Funcion para leer las teclas direccionales.
void teclear(){
	if(kbhit()){
		tecla = getch();
		switch(tecla){
			case ARRIBA:
				if(dir != 2)
					dir = 1;
				break;
			case ABAJO:
				if(dir != 1)
					dir = 2;
				break;
			case DERECHA:
				if(dir != 4)
					dir = 3;
				break;
			case IZQUIERDA:
				if(dir != 3)
					dir = 4;
				break;
		}
	}
}
// Funcion para incrementar la velocidad de la serpiente.
void cambiar_velocidad(){
	if(score == h*20){
		velocidad -=10;
		h++;
	}
}
// Funcion para dibujar la comida en pantalla.
void comida(){
	if(x == xc && y == yc){
		printf("\a");
		xc = (rand()%73)+4;
		yc = (rand()%19)+4;
		tam++; // Se aumenta el tama�o de la serpiente.
		score +=10;
		gotoxy(xc, yc); printf("%c", 4);
		cambiar_velocidad();
	}
}
// Game over.
bool game_over(){
	if(y==3 || y==23 || x==2 || x==77){
		printf("\a \a \a");
		return false;
	}
	for(int j=tam-1; j>0; j--){
		if(cuerpo[j][0]==x && cuerpo[j][1]==y){
			printf("\a \a \a");
			return false;
		}
	}
	return true;
}
// Funcion para mostrar el score en pantalla.
void puntos(){
	gotoxy(3,1); printf("<Score: %d>", score);
}
// Funcion principal.
int main() {
	pintar();
	menu_inicial();
	gotoxy(xc, yc); printf("%c", 4);
	while(tecla != ESC && game_over()){
		borrar_cuerpo();
		guardar_posicion();
		dibujar_cuerpo();
		comida();
		puntos();
		teclear();
		teclear();
		if(dir == 1)
			y--;
		if(dir == 2)
			y++;
		if(dir == 3)
			x++;
		if(dir == 4)
			x--;
		Sleep(velocidad);
	}
	pintar();
	system("pause>null");
	return 0;
}
