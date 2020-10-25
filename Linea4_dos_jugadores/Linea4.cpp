#include<iostream>
#include <string>
#include <vector>
#include "Linea4.hpp"

using namespace std;

Linea4::Linea4(){
  for(int f = 0; f < NUM_ROWS; f++){
    for(int c = 0;c < NUM_COLS; c++){
      board[f][c] = 0; // inicializar el tablero en ceros.
    }
  }
  turno = true; // inicializar el turno
}

void Linea4::printBoard(){
  cout << "--------------------" << endl;
  for(int i = 0; i < NUM_ROWS; i++){
    for(int j = 0; j < NUM_COLS; j++){
      if(board[i][j] == 1){ // codifico el trablero. 1 es 'O'
        cout <<" O ";}
      else if(board[i][j] == 2){ // codifico el trablero. 2 es 'X'
          cout <<" X ";
      }else{
          cout <<" . ";
            }
          }
        cout << endl;
    }
  cout << "--------------------" << endl;
}


bool Linea4::getTurn(){
  return turno; // obtengo el turno actual
}

void Linea4::setTurn(bool val){
  turno  = val; // modifico el turno dependiendo de quién juega.
}

bool Linea4::isColumnFull(int column){
  for(int fila = 0; fila < NUM_ROWS; fila++){
      if(board[fila][column] == 0){
        return false;
      }
    }
  return true; //retorna true cuando alguna columna está llena de fichas.
}

bool Linea4::isGameFinished(){
  for(int col = 0; col < NUM_COLS; col++){
      if(!isColumnFull(col)){ //si la columna todavía no está llena se puede seguir jugando.
        return false;
      }
    }
  return true;
}

int Linea4::addFicha(int column, bool turno){
  if(isColumnFull(column)){
    cout << "The column is full." << endl;
    return -1;
  }
  for(int fila = NUM_ROWS-1; fila >= 0; fila--){
    if(board[fila][column] == 0){
      if(turno == 1){ // coloca la ficha del jugador 1 dependiendo del turno.
        board[fila][column] = 1;
        return 1; // codificación
      }else{
        board[fila][column] = 2; // coloca la ficha del jugador 2 dependiendo del turno.
        return 2; // codificación
      }
    }
  }
}

bool Linea4::isWinner(int player){
  /*
  Funcion que verifica si el jugador player ganó la partida
  Dentro la función del juego se verificará por separado jugador 1 y jugador 2
  */
  // 1. Se verifica verticalmente si hay 4 fichas alineadas
  if(VerificarV(player) == true){
    cout << "We have a winner. Player "<< player << " wins!";
    return true;
  }else if(VerificarH(player) == true){
    // 2. Se verifica horizontalmente si hay 4 fichas alineadas
    cout << "We have a winner. Player "<< player << " wins!";
    return true;

  }else if(VerificarD1(player) == true){
    // 3. Se verifica en diagonal \ si hay 4 fichas alineadas
    cout << "We have a winner. Player "<< player << " wins!";
    return true;

  }else if(VerificarD2(player) == true){
    // 4. Se verifica en diagonal / si hay 4 fichas alineadas
    cout << "We have a winner. Player "<< player << " wins!";
    return true;
  }else{
    //Si en ningun caso se encontro 4 en linea, se retorna false
    return false;
  }

}

void Linea4::play() {
  int player = 0;
  int last_play = 0;
  printBoard();
  while(!isGameFinished()){ // el juego se realiza mientras haya espacios donde colocar fichas.
    int column_selected = -1;
    bool column_to_max = true;
    if(last_play == 1){
      player = 2;
    }else{
      player = 1;
    }
    do{
    cout << "Turno del jugador "<< player <<" - Ingrese un numero del 1 al 7: ";
    cin >> column_selected; // el jugador ingresa la columna donde quiera empezar.
    cout << endl;
    column_selected--; // realiza el decremento para que ingrese la ficha en la columna adecuado, de acuerdo a los índices de C++.

    while(column_selected < 0 || column_selected >= NUM_COLS){
      cout << "Number is not allowed!" << endl << endl;
      cout << "Turno del jugador "<< player <<" - Ingrese un numero del 1 al 7: ";
      cin >> column_selected;
      cout << endl;
      column_selected--;
    }

    column_to_max = isColumnFull(column_selected); //Si la columna seleccionada está llena.
    }
    while((column_selected < 0 || column_selected > NUM_COLS) || column_to_max);

    addFicha(column_selected, getTurn()); // agrega la ficha en la columna que el jugador seleccione y el turno que tenga.
    printBoard();

    if(isWinner(1)){ // va verficando si hay ganador del jugador 1.
    break;
    }else if(isWinner(2)){ // va verficando si hay ganador del jugador 1.
      break;
    }

    last_play = player; // cambia el valor del número asociado al jugador en la partida.
    setTurn(!getTurn()); // cambia el turno para el juego sepa que tiene que colocar el símbolo X, O.
    player++;
  }
}


//==============================================================================
// FUNCIONES PRIVADAS
bool Linea4::VerificarV(int player){
  // Funcion que verifica verticalmente en todas las columnas.
  // si hay  fichas 4 en linea de player.
  bool num_found = false; // el booleando que confirma si encontró el número del jugador.
  int aligned = 0; // contador de fichas del mismo jugador que están alineadas.
  for(int col = 0; col < NUM_COLS; col++){
    for(int row = NUM_ROWS-1; row >= 0; row--){
      if(num_found){ //  si el número del jugador ya fue encontrado, se vertifica si en la casilla actual también se encuentra el mismo número.
        if(board[row][col] == player){
          aligned++;
        }else{
          num_found = false;
          aligned = 0;
        }
      }
      if(board[row][col] == player && !num_found){ //si el numero no fue encuentrado pero en la casilla actual se encuentra el número de player.
        num_found = true;
        aligned++;
      }
      if(aligned == 4){ //si el contador es igual a 4, hay ganador.
        return true;
      }
    }
  }
  // Si no encontró nada
  return false;
}
//------------------------------------------------------------------------------
bool Linea4::VerificarH(int player){
  // Funcion que verifica horizontalmente en todas las columnas.
  // si hay  fichas 4 en linea de player.
  bool num_found = false; // el booleando que confirma si encontró el número del jugador.
  int aligned = 0; // contador de fichas del mismo jugador que están alineadas.
  for(int row = NUM_ROWS-1; row >= 0; row--){
    for(int col = 0; col < NUM_COLS; col++){
      if(num_found){
        if(board[row][col] == player){ //  si el número del jugador ya fue encontrado, se vertifica si en la casilla actual también se encuentra el mismo número.
          aligned++;
        }else{
          num_found = false;
          aligned = 0;
        }
      }
      if(board[row][col] == player && !num_found){ //si el numero no fue encuentrado pero en la casilla actual se encuentra el número de player.
        num_found = true;
        aligned++;
      }
      if(aligned == 4){ //si el contador es igual a 4, hay ganador.
        return true;
      }
    }
  }
  // Si no encontró nada
  return false;

}
//------------------------------------------------------------------------------
bool Linea4::VerificarD1(int player){
/*
  0,0,0,0,0,0,0
  0,0,0,0,0,0,0
  1,0,0,0,0,0,0
  2,1,0,0,0,0,0
  2,2,1,0,0,0,0
  2,2,2,1,0,0,0
*/
// MITAD INFERIOR
// 1. Verificamos las diagonales posibles de 4 casillas alineadas (de fila 0 a fila 2).
//    pegados al lado izquierdo del tablero.
  int ini_col = 0;
  for(int ini_row = 0; ini_row < 3; ini_row++){
    int row = ini_row;
    int col = 0;

    bool num_found = false;
    int aligned = 0;
    while(row < NUM_ROWS){
      if(num_found){
        if(board[row][col] == player){
          aligned++;
        }else{
          num_found = false;
          aligned = 0;
        }
      }
      if(!num_found && board[row][col] == player){
        num_found = true;
        aligned++;
      }
      if(aligned == 4){
        return true;
      }
      col++;
      row++;
    }
  }
//  MITAD SUPERIOR
// 2. Verificamos las diagonales posibles de 4 casillas alineadas (columna 1 a columna 3).
//    pegados a la parte de arriba del tablero.
  int ini_row = 0;
  for(ini_col = 1; ini_col < 4; ini_col++){
    int row = 0;
    int col = ini_col;
    bool num_found = false;
    int aligned = 0;
    while(row < NUM_ROWS){
      if(num_found){
        if(board[row][col] == player){
          aligned++;
        }else{
          num_found = false;
          aligned = 0;
        }
      }
      if(!num_found && board[row][col] == player){
        num_found = true;
        aligned++;
      }
      if(aligned == 4){
        return true;
      }
      col++;
      row++;
    }
  }
  return false;
}
//------------------------------------------------------------------------------
bool Linea4::VerificarD2(int player){
/*
  0,0,0,0,0,0,0
  0,0,0,0,0,0,0
  0,0,0,0,0,0,1
  0,0,0,0,0,1,0
  0,0,0,0,1,0,0
  0,0,0,1,0,0,0
*/
// 1. Verificamos las diagonales posibles de 4 casillas alineadas (de fila 0 a fila 2).
//    pegados al lado izquierdo del tablero.
  int ini_col = NUM_COLS-1;
  for(int ini_row = 0; ini_row < 3; ini_row++){
    int row = ini_row;
    int col = NUM_COLS-1;

    bool num_found = false;
    int aligned = 0;
    while(row < NUM_ROWS){
      if(num_found){
        if(board[row][col] == player){
          aligned++;
        }else{
          num_found = false;
          aligned = 0;
        }
      }
      if(!num_found && board[row][col] == player){
        num_found = true;
        aligned++;
      }
      if(aligned == 4){
        return true;
      }
      col--;
      row++;
    }
  }
// 2. Verificamos las diagonales posibles de 4 casillas alineadas (columna 6 a columna 4).
//    pegados a la parte de arriba del tablero.
  int ini_row = 0;
  for(ini_col = NUM_COLS-2; ini_col >= 3; ini_col--){
    int row = 0;
    int col = ini_col;
    bool num_found = false;
    int aligned = 0;
    while(row < NUM_ROWS){
      if(num_found){
        if(board[row][col] == player){
          aligned++;
        }else{
          num_found = false;
          aligned = 0;
        }
      }
      if(!num_found && board[row][col] == player){
        num_found = true;
        aligned++;
      }
      if(aligned == 4){
        return true;
      }
      col--;
      row++;
    }
  }
  return false;
}
//------------------------------------------------------------------------------
