/* Autores: Luna Gutierrez, Ana Garzón, Alejandra Campo.*/

#ifndef _CONNECT4_HPP
#define _CONNECT4_HPP

#include <vector>
using namespace std;

const int ROWS = 6; // número de filas.
const int COL = 7; // número de columnas.
const int CELLS = 42; // número total de casillas
const int MAX = 1000; // constante maximizador
const int MIN = -1000; // constante minimizador.

class Linea4{
private:
  int board[ROWS][COL]; // el tablero es una matriz.
  int DEPTH; // nivel de profunidad
  int turn; // variable que guarda el turno actual.
  // Funciones de verificación, ya se puede acceder al tablero como atributo
  // de la clase
  bool VerificarV(int player, int b[ROWS][COL]); //verifica verticalmente si hay ganador.
  bool VerificarH(int player, int b[ROWS][COL]); //verifica horizontalmente si hay ganador.
  bool VerificarD(int player, int b[ROWS][COL]); //verifica diagonalmente (\)(/) si hay ganador.

  bool isWinner(int player, int b[ROWS][COL]); // Dice si hay ganador.

  void move(int b[ROWS][COL], int col, int player); // movimiento disponible.
  int movUser(); // movimiento del usuario de acuerdo a lo que ingrese.
  int moveAI(); // movimiento del computador de acuerdo al Winner_next() y miniMax()

  int heuristica(int s[4], int p); // función que orienta las acciones del computador.
  int eval4(int b[ROWS][COL], int p); // analiza el estado actual del tablero junto con la heuristica teniendo en cuenta cuatro casillas contiguas.
  vector<int> miniMax(int b[ROWS][COL], int d, int p, int alpha, int beta); // busca obtener la movimiento donde el computador tenga más posibilidades de ganar.

  bool isColumnFull(int column, int b[ROWS][COL]); // verifica si alguna columna está llena.
  int SelectColumn(int b[ROWS][COL]); // Selecciona al computador una columna aleatoria cuando el computador entre en un estado de pérdidas.
  int Winner_next(int player, int b[ROWS][COL]); // Realiza el movimiento ganador en la primera oportunidad que tenga el computador y bloquea al oponente.

  void printBoard(int b[ROWS][COL]); // imprimir el tablero.

public:

  Linea4(); // constructor.

  void playAI(); // para empezar el juego contra ordenador.
  void play2players(); // para empezar el juego contra otro usuario.

};

#endif
