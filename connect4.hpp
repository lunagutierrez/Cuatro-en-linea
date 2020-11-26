
#ifndef _CONNECT4_HPP
#define _CONNECT4_HPP

#include <vector>
using namespace std;

const int ROWS = 6; // número de filas.
const int COL = 7; // número de columnas.
const int CELLS = 42; //num total de casillas
const int MAX = 1000;
const int MIN = -1000;

class Linea4{
private:
  int board[ROWS][COL]; //el tablero es una matriz.
  int DEPTH;
  int turn;
  // Funciones de verificación, ya se puede acceder al tablero como atributo
  // de la clase
  bool VerificarV(int player, int b[ROWS][COL]); //verifica verticalmente si hay ganador.
  bool VerificarH(int player, int b[ROWS][COL]); //verifica horizontalmente si hay ganador.
  bool VerificarD(int player, int b[ROWS][COL]); //verifica diagonalmente (\) si hay ganador.

  bool isWinner(int player, int b[ROWS][COL]); // dice si hay ganador.

  void move(int b[ROWS][COL], int col, int player);
  int movUser();
  int moveAI();

  int heuristica(int s[4], int p);
  int eval4(int b[ROWS][COL], int p);
  vector<int> miniMax(int b[ROWS][COL], int d, int p, int alpha, int beta);

  bool isColumnFull(int column, int b[ROWS][COL]); // si alguna columna está llena.
  int SelectColumn(int b[ROWS][COL]);
  int Winner_next(int player, int b[ROWS][COL]);

  void printBoard(int b[ROWS][COL]); // imprimir el tablero.

public:

  Linea4(); // construir.

  void playAI(); // para empezar el juego contra ordenador.
  void play2players(); // para empezar el juego contra otro usuario.

};

#endif
