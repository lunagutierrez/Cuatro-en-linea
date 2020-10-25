
#ifndef _CONNECT4_HPP
#define _CONNECT4_HPP

#include <vector>
#include <cmath>
using namespace std;
const int ROWS = 6; // número de filas.
const int COL = 7; // número de columnas.

class Linea4{
private:
int board[ROWS][COL]; //el tablero es una matriz.
// int board[ROWS][COL]; //el tablero es una matriz.
bool gameOver = false;
int USER = 1;
int AI = 2;
int player = USER;
int turn;
int tColumnas[COL];

// Funciones de verificación, ya se puede acceder al tablero como atributo
// de la clase
bool VerificarV(int player); //verifica verticalmente si hay ganador.
bool VerificarH(int player); //verifica horizontalmente si hay ganador.
bool VerificarD1(int player); //verifica diagonalmente (\) si hay ganador.
bool VerificarD2(int player); //verifica diagonalmente (/) si hay ganador.


int heuristica(vector<int> s, int p);
int eval4(int b[ROWS][COL], int p);
int Min(); //Recibe el jugador cp(computer player) y el u(user) y retorna el movimiento de cp que minimiza el puntaje de u
int Max(); //Recibe el jugador, y retorna la columna en la que obtendría mayor puntaje para el siguiente turno


public:

Linea4(); // construir.
//~Linea4(); // opcional.
void printBoard(); // imprimir el tablero.

void move(int b[ROWS][COL], int col, int player);
int movUser();
int moveAI();
int MiniMax();

bool isColumnFull(int column); // si alguna columna está llena.
bool isWinner(int player); // dice si hay ganador.

void play(); // para empezar el juego.

};

#endif
