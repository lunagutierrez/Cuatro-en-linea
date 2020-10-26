#include <iostream>	 // consola de la libreria standard (STL)
#include <vector>
#include<string>
#include "connect4.hpp"
using namespace std;

Linea4::Linea4(){//constructor del juego
  for(int f = 0; f < ROWS; f++){
    for(int c = 0;c < COL; c++){
      board[f][c] = 0; // inicializar el tablero en ceros.
    }
  }
  turn = true; // inicializar el turno
}

void Linea4::printBoard(){

	cout << endl << ". . . . . . . ." << endl;
	for (int j = 0; j < ROWS; j++){
		for (int k = 0; k < COL; k++){
			cout << "|";
			switch (board[ROWS - j - 1][k]){
			case 0:
				cout << " ";
				break; // nada
			case 1:
				cout << "X";
				break; // para un Jugador
			case 2:
				cout << "O";
				break; // Otro jugador
			}
			if (k + 1 == COL) { cout << "|"; }
		}
		cout << endl;
	}
	cout << "---------------" << endl;
	for (int i = 0; i < COL; i++) {
		cout << " " << i; //imprimo el numero de la casilla
	}
	cout << endl;
}

bool Linea4::isColumnFull(int column){
  for(int fila = 0; fila < ROWS; fila++){
      if(board[fila][column] == 0){ //si no hay nada en esa casilla
        return false;
      }
    }
  return true; //retorna true cuando alguna columna está llena de fichas.
}

void Linea4::move(int b[ROWS][COL],int col, int player){
  // toma el tablero, la columna y el jugador
  for (int i = 0; i < ROWS; i++) {
		if(!isColumnFull(col)){//mientras esa columna no este llena
			if (b[i][col] == 0) { // Lo pone en la primera fila disponible
				b[i][col] = player; // posiciona la pieza en esa casilla
				break;
			}
		}
	}
}

int Linea4::movUser(){

  cout << "Es tu turno..." << endl;
	int movim;

  while(true){//repita el proceso hasta que se ingrese un valor valido
    cout << "Ingrese la columna en la que desea poner su ficha: ";
    cin >> movim; //tomo como input en donde la pondra

		if(isalpha(movim)){
			cout << "Ingrese un numero entre 0 y 6" << endl;
		}
		if (!(movim >= 0 && movim < COL)){
      cout << "Esa no es una columna valida" << endl; //se puede hacer con un except
    }else if (isColumnFull(movim)) { // En caso de que la columna ya este llena
			cout << "Esa columna ya esta llena" << endl; //se puede hacer con un except
		cout << endl;
		}else{
			break;
		}
	}
	return movim;
}

int Linea4::moveAI(){
	cout << "Es mi turno..." << endl;
		return MiniMax();
}

int Linea4::heuristica(vector<int> s, int p){

  unsigned int blank = 0; // puntos neutros
  unsigned int bad = 0; // puntos a favor del otro jugador p
  unsigned int good = 0; // puntos a favor de p

	int score = 0;

	for (int i = 0; i < s.size(); i++) { //hago la cuenta de cuantos hay de cada uno
		if (s[i] == p){//Si en esa casilla hay una ficha del jugador
			good+=1;//sumo a fichas a favor
		}else if(s[i] == 0){
			blank+=1;
		}else{
			bad+=1;
		}
	}

	if (good == 4)
		score += 1001;  //prefiere ganar que bloquear
	else if (good == 3 && blank == 1)
		score += 500;
	else if (good == 2 && blank == 2)
		score += 50;
	else if (bad == 2 && blank == 2)
		score -= 51;  //prefiere bloquear
	else if (bad == 3 && blank == 1)
		score -= 501;  //prefiere bloquear
	else if (bad == 4)
		score -= 1000;

	return score;
}

int Linea4::eval4(int b[ROWS][COL], int p){ //toma el estado actual del tablero y el jugador en turno
	int puntos = 0;//contador el puntaje inicializado en 0
	vector<int> r(COL);//vector que define las filas
	vector<int> c(ROWS); //vector que define las columnas
	vector<int> segm(4); //revisa en segmentos de a 4 espacios

// ver
	for (int y = 0; y < COL; y++){
		for (int x = 0; x < ROWS; x++){
			c[x] = b[x][y]; //columna con un elem en cada fila
		}

		for (int i = 0; i < 4; i++){//4 casillas
			for (int x = 0; x < ROWS - 3; x++){//estoy dentro de los limites
				segm[i] = c[x + i];//casillas contiguas en la columna
			}
			puntos += heuristica(segm, p);//puntaje para ese jugador en ese segmento vertical
		}
	}

//hor
	for (int x = 0; x < ROWS; x++){
		for (int y = 0; y < COL; y++){
			r[x] = b[x][y]; //esta es una fila que contiene un elem por cada columna
		}
		for (int i = 0; i < 4; i++){//tomo 4 espacios
			for (int y = 0; y < COL - 3; y++){//asi no me salgo del tablero
				segm[i] = r[y + i];
			}//Son las posibles 4 contiguas en esa fila
			puntos += heuristica(segm, p); //puntaje para ese jugador en ese segmento
		}
	}

	//diag de arriba a abajo
		for (int x = 0; x < ROWS - 3; x++){
			for (int y = 0; y < COL; y++){
				r[y] = b[x][y];
			}
			for (int i = 0; i < 4; i++){
				for (int y = 0; y < COL - 3; y++){
					segm[i] = b[x + 3 - i][y + i]; //si no funciona prueba con -i en ambos lados
				}
				puntos += heuristica(segm, p);//puntaje para ese jugador en ese segmento
			}
		}

// diag de abajo a arriba
	for (int x = 0; x < ROWS - 3; x++){
		for (int y = 0; y < COL; y++){
			r[y] = board[x][y];//fila
		}
		for (int i = 0; i < 4; i++){
			for (int y = 0; y < COL - 3; y++){//estoy en los limites del tablero
				segm[i] = board[x + i][y + i];
			}
			puntos += heuristica(segm, p);//puntaje para ese jugador en ese segmento
		}
	}
	return puntos;
}

bool Linea4::isWinner(int player){
  /*
  Funcion que verifica si el jugador player ganó la partida
  Dentro la función del juego se verificará por separado jugador 1 y jugador 2
  */
  // 1. Se verifica verticalmente si hay 4 fichas alineadas
  if(VerificarV(player) == true){

    return true;
  }else if(VerificarH(player) == true){
    // 2. Se verifica horizontalmente si hay 4 fichas alineadas

    return true;

  }else if(VerificarD(player) == true){
    // 3. Se verifica en diagonal \ si hay 4 fichas alineadas

    return true;
  }else{
    //Si en ningun caso se encontro 4 en linea, se retorna false
    return false;
  }

}

int Linea4::MiniMax(){
  //Función que define si es más conveniente minimizar la jugada del oponente o maximizar la propia
  int MinMove = Min();
  int MaxMove = Max();
	int copy_board_min [ROWS][COL];
  int copy_board_max [ROWS][COL];
	for(int i = 0; i < ROWS; i++){
		for(int j = 0; j <COL; j++){
			copy_board_min[i][j] = board[i][j];
			copy_board_max[i][j] = board[i][j];
		}
	}

  move(copy_board_min, MinMove, AI);
  move(copy_board_max, MaxMove, AI);
	//cout << "move minimax" << endl;
  int absMinVal = abs(eval4(copy_board_min, USER));
	//cout <<"eval 4 min" <<eval4(copy_board_min, USER) << endl;
  int absMaxVal = abs(eval4(copy_board_max, AI));
	//cout <<"eval 4 max" <<eval4(copy_board_max, AI) << endl;
  int best_move;
  if(absMaxVal >= absMinVal){
    best_move = MinMove;
  }else{
    best_move = MaxMove;
  }
  return best_move;
}

//==============================================================================
// FUNCIONES PRIVADAS
bool Linea4::VerificarV(int player){
  // Funcion que verifica verticalmente en todas las columnas.
  // si hay  fichas 4 en linea de player.
 // el booleando que confirma si encontró el número del jugador.
  int aligned = 0; // contador de fichas del mismo jugador que están alineadas.

  for (int c = 0; c < COL; c++){
		for (int r = 0; r < ROWS - 3; r++){
			for (int i = 0; i < 4; i++){ // se necesitan 4 fichas
				if (board[r + i][c] == player){
					aligned++;//sumo al contador de fichas contiguas
				}
				if (aligned == 4){//si hay 4 en linea
					return true;//alguien gano
				}
			}
			aligned = 0;// vuelvo a dejar el contador en 0
		}
	}

	return false; //si no, nadie ha ganado
}
//------------------------------------------------------------------------------
bool Linea4::VerificarH(int player){
  // Funcion que verifica horizontalmente en todas las columnas.
  // si hay  fichas 4 en linea de player.

  int aligned = 0; // contador de fichas del mismo jugador que están alineadas.

  for (int c = 0; c < COL - 3; c++){ // for cada columna sin salirnos del rango
		for (int r = 0; r < ROWS; r++){ // for cada fila
			for (int i = 0; i < 4; i++){ // se necesitan 4 fichas
				if (board[r][c + i] == player){
					aligned++; //sumo al contador de fichas contiguas
				}
				if (aligned == 4){//si hay 4 en linea
					return true;//hay un ganador
				}
			}
			aligned = 0;// vuelvo a dejar el contador en 0
		}
	}
  return false; //si no, nadie ha ganado
}
//------------------------------------------------------------------------------
bool Linea4::VerificarD(int player){
  int aligned = 0;//contador de fichas contiguas del mismo jugador
  // diagonales
  	//de der a izq
	for (int c = 0; c < COL - 3; c++){
		for (int r = 0; r < ROWS - 3; r++){
			for (int i = 0; i < 4; i++){// se necesitan 4 fichas
				if (board[r + i][c + i] == player){
					aligned++;//sumo al contador de fichas contiguas
				}
				if (aligned == 4){
					return true;//alguien gano
				}
			}
			aligned = 0;// vuelvo a dejar el contador en 0
		}
	}

	//de izq a der
	for (int c = 0; c < COL - 3; c++){//el -3 asegura que no me salgo del tablero
		for (int r = 3; r < ROWS; r++){
			for (int i = 0; i < 4; i++){// se necesitan 4 fichas
				if (board[r - i][c + i] == player){
					aligned++;//sumo al contador de fichas contiguas
				}
				if (aligned == 4){
					return true;//alguien gano
				}
			}
			aligned = 0;// vuelvo a dejar el contador en 0
		}
	}

  return false; //si no, nadie ha ganado
}
//---------------------------------------------------------------------------

int Linea4::Min(){
  //Recibe el jugador p y el u y retorna el movimiento de p que minimiza el puntaje de u
	int min = 0; //Se inicializa el puntaje máximo en cero
	int best_move = 3; // el mejor mov inicial es en el medio
  int move_val;
  int copy_board [ROWS][COL];

	for(int c = 0; c < COL; c++){
    if (!isColumnFull(c)){

			for(int i = 0; i < ROWS; i++){
    		for(int j = 0; j <COL; j++){
      		copy_board[i][j] = board[i][j];
    		}
			}

      move(copy_board, c, AI);
      move_val = eval4(copy_board, USER); //Entero que retorna la evaluación del movimiento ¡MODIFICAR!
        if(move_val < min){ //Si el valor del movimiento actual es menor que el valor del minimo
          min = move_val; //El mínimo es el valor del movimiento actual
					best_move = c; //El movimiento que minimiza es colocar ficha en la columna c
        }
      }
	 }
	// cout << "mov que min: " << best_move<<endl;
	return best_move; //Retornar el movimiento que mínimiza el puntaje del oponente
}

int Linea4::Max(){
  //Recibe el jugador, y retorna la columna en la que obtendría mayor puntaje para el siguiente juego
	int max = 0; //Se inicializa el puntaje máximo en cero
	int best_move = 3; // el mejor mov inicial es en el medio
  int move_val;
  int copy_board [ROWS][COL];
	for(int c = 0; c < COL; c++){
      if (!isColumnFull(c)){
				for(int i = 0; i < ROWS; i++){
					for(int j = 0; j <COL; j++){
						copy_board[i][j] = board[i][j];
					}
				}
        move(copy_board, c, AI);
				move_val = eval4(copy_board, AI); //Entero que retorna la evaluación del movimiento ¡MODIFICAR!
				if(move_val > max){ //Si el valor del movimiento actual es mayor que el valor del máximo
        	max = move_val; //El máximo es el valor del movimiento actual
					best_move = c; //El movimiento que maximiza es colocar ficha en la columna
        }
      }
	}
	//cout << "mov que max: " << best_move<<endl;
	return best_move; //Retornar el movimiento que maximiza el puntaje
}

void Linea4::play(){
	cout << "Juguemos 4 en linea!" << endl;
	// cout << "Escoge el nivel de dificultad: " << endl;
	// cin >> dif;

	printBoard();

	bool gameover = false;//inicializador del juego
	int player = 1; //jugador actual
	int turn = 0; //count para los turnos

	while (!gameover){
		if(player == USER){ // Mueve el usuario en el primer turno
			move(board,movUser(), 1);
		}
		else if (player == AI){ // Mueve el AI
			move(board,moveAI(), 2); //cambiar movuser por movAI cuando exista el algoritmo
		}
		else if (turn == COL*ROWS){ // Si llego al num max de turnos
			gameover = true;
		}

		gameover = isWinner(player); //Revisa si el jugador gano (esta seria tu funcion Alejandra)

		if(player == 1){
			player = 2;
		}else{
			player = 1;
		}

		turn +=1; //voy incrementando los turnos

		//turn = turn%2;//si es par el turno le toca al usuario
		cout << endl;

		printBoard(); //imprimo el tablero tras cada mov
	}
	if (turn == COL*ROWS) { // Si es empate
		cout << "Empate" << endl;
	}else { // Si alguien gana

		if (player == AI){
			cout << "Usuario gana(X)!"<<endl;
		}else if(player == USER){
			cout << "AI gana(O)!" <<endl;
		}
	}
}
