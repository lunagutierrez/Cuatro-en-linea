#ifndef _TABLERO_HPP
#define _TABLERO_HPP

#include <vector>
const int NUM_ROWS = 6; // número de filas.
const int NUM_COLS = 7; // número de columnas.

class Linea4{
private:


  int board[NUM_ROWS][NUM_COLS]; //el tablero es una matriz.
  bool turno; // True para jugador 1, false para jugador 2.


  // Funciones de verificación, ya se puede acceder al tablero como atributo
  // de la clase
  bool VerificarV(int player); //verifica verticalmente si hay ganador.
  bool VerificarH(int player); //verifica horizontalmente si hay ganador.
  bool VerificarD1(int player); //verifica diagonalmente (\) si hay ganador.
  bool VerificarD2(int player); //verifica diagonalmente (/) si hay ganador.


public:
Linea4(); // construir.
//~Linea4(); // opcional.
void printBoard(); // imprimir el tablero.
bool getTurn(); // obtener el turno.
void setTurn(bool val); //cambiar el turno del jugador.

bool isColumnFull(int column); // si alguna columna está llena.
bool isGameFinished(); // verifica si hay espacios en los cuales jugar.
int addFicha(int column, bool turno); // agregar ficha teniendo encuenta el turno.
bool isWinner(int jugador); // dice si hay ganador.

void play(); // para empezar el juego.

};

#endif
