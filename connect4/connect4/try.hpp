
#ifndef _TRY_HPP
#define _TRY_HPP

#include <vector>
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


int heuristica(vector<int> s);
int eval4();

public:

Linea4(); // construir.
//~Linea4(); // opcional.
void printBoard(); // imprimir el tablero.

void move(int col, int player);
int movUser();
int moveAI();

bool isWinner(int player); // dice si hay ganador.
bool won();
void play(); // para empezar el juego.



};

#endif
