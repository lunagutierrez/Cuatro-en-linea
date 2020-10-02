#ifndef _C4_HPP
#define _C4_HPP
using namespace std;
#include <string>
#include <vector>
#include <array>
#include <iostream>

void printBoard(vector<vector<int>> &b); //imprime el tablero
void move(vector<vector<int>>&b, int col, int p); //permite hacer el movimiento para el jugador
int moveAI(); //movimiento del computador
int movUser(); //movimiento para el usuario y las restricciones para asegurar que lo ingresado sea valido
bool movWin(vector<vector<int>>&b, int p); // revisa si la movida es ganadora
vector<vector<int>> copyBoard(vector<vector<int>> b); //hace una copia del estado actual del tablero
int segmentscore(vector< int> pos,  int p);//puntaje de 4 casillas
int value(vector<vector<int>> b,  int p); //puntaje del tablero (revisa ver, hor y diag)
array <int, 2> miniMax(vector<vector<int> >&b , int dif, int alpha, int beta,  int p); //algoritmo minimax recursivo
//usamos un arreglo para hacer parejas  en lugar de un vector ya que es mas
//rapido debido a que su tamano es constante
int foo( int favor, int contra, int nada);//le doy puntajes a las que son seguidas (preguntarle a Carlos si es verdaderamente necesario)

#endif


//connect4

//OneDrive\Documentos\MACC 2020-2\Algoritmos\c++\Proyecto
//g++ connec4_1.cpp -o connect4
