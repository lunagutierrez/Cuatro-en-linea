#include <iostream>	 // consola de la libreria standard (STL)
#include <vector>
#include "try.hpp"
using namespace std;

Linea4::Linea4(){
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
				cout << "0";
				break; // nada
			case 1:
				cout << "1";
				break; // para un Jugador
			case 2:
				cout << "2";
				break; // Otro jugador
			}
			if (k + 1 == COL) { cout << "|"; }
		}
		cout << endl;
	}
	cout << "---------------" << endl;
	for (int i = 0; i < COL; i++) {
		cout << " " << i;
	}
	cout << endl;
}

void Linea4::move(int col, int player){
  // toma el tablero, la columna y el jugador
  for (int i = 0; i < ROWS; i++) {
		if (board[i][col] == 0) { // Lo pone en la fila disponible
			board[i][col] = player; // posiciona la pieza
			break;
		}
	}
}

int Linea4::movUser(){
  int mov;
  cout << "Es tu turno..." << endl;
  while(true){//repita el proceso hasta que se ingrese un valor valido
    cout << "Ingrese la columna en la que desea poner su ficha: ";
    cin >> mov; //tomo como input en donde la pondra

    if (!(0 <= mov && mov < COL))
      cout << "Esa no es una columna valida" << endl; //se puede hacer con un except

    else if (board[ROWS - 1][mov] != 0) { // En caso de que la columna ya este llena
			cout << "Esa columna ya esta llena" << endl; //se puede hacer con un except

    }else { //si pasa cualquier otra cosa
			break;
		}
		cout << endl;
	}
	return mov;
}

int Linea4::heuristica(vector<int> s) {
	int score = 0;
	unsigned int good = 0; // puntos a favor de p
	unsigned int bad = 0; // puntos a favor del otro jugador p
	unsigned int blank = 0; // puntos neutros

	for (int i = 0; i < s.size(); i++) { //hago la cuenta de cuantos hay de cada uno
		if (s[i] == player){
			good+=1;
		}else if (s[i] == AI || s[i] == USER){
			bad+=1;
		}else if(s[i] == 0){
			blank+=1;
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

int Linea4::eval4(){ //toma el estado actual del tablero y el jugador en turno
	int puntos = 0;//contador el puntaje inicializado en 0
	vector<int> r(COL);//vector que define las filas
	vector<int> c(ROWS); //vector que define las columnas
	vector<int> segm(4); //revisa en segmentos de a 4 espacios

// ver
	for (int y = 0; y < COL; y++){
		for (int x = 0; x < ROWS; x++){
			c[x] = board[x][y]; //columna con un elem en cada fila
		}

		for (int i = 0; i < 4; i++){//4 casillas
			for (int x = 0; x < ROWS - 3; x++){//estoy dentro de los limites
				segm[i] = c[x + i];//casillas contiguas en la columna
			}
			puntos += heuristica(segm);//puntaje para ese jugador en ese segmento vertical
		}
	}

//hor
	for (int x = 0; x < ROWS; x++){
		for (int y = 0; y < COL; y++){
			r[x] = board[x][y]; //esta es una fila que contiene un elem por cada columna
		}
		for (int i = 0; i < 4; i++){//tomo 4 espacios
			for (int y = 0; y < COL - 3; y++){//asi no me salgo del tablero
				segm[i] = r[y + i];
			}//Son las posibles 4 contiguas en esa fila
			puntos += heuristica(segm); //puntaje para ese jugador en ese segmento
		}
	}

	//diag de arriba a abajo
		for (int x = 0; x < ROWS - 3; x++){
			for (int y = 0; y < COL; y++){
				r[y] = board[x][y];
			}
			for (int i = 0; i < 4; i++){
				for (int y = 0; y < COL - 3; y++){
					segm[i] = board[x + 3 - i][y + i]; //si no funciona prueba con -i en ambos lados
				}
				puntos += heuristica(segm);//puntaje para ese jugador en ese segmento
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
			puntos += heuristica(segm);//puntaje para ese jugador en ese segmento
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

int Linea4::MiniMax(int p, int u){
  //Función que define si es más conveniente minimizar la jugada del oponente o maximizar la propia
  int MinMove = Min(p,u);
  int MaxMove = Max(p);
  int copy_board_min [][];
  int copy_board_max [][];
  move(copy_board_min, MinMove, p);
  move(copy_board_max, MaxMove, p);
  int absMinVal = abs(eval4(copy_board_min));
  int absMaxVal = abs(eval4(copy_board_max));
  int best_move;
  if(absMaxVal > absMinVal){
    best_move = MaxMove;
  }else{
    best_move = MinMove;
  }
  return best_move;
}

//==============================================================================
// FUNCIONES PRIVADAS
bool Linea4::VerificarV(int player){
  // Funcion que verifica verticalmente en todas las columnas.
  // si hay  fichas 4 en linea de player.
  bool num_found = false; // el booleando que confirma si encontró el número del jugador.
  int aligned = 0; // contador de fichas del mismo jugador que están alineadas.
  for(int col = 0; col < COL; col++){
    for(int row = ROWS-1; row >= 0; row--){
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
  for(int row = ROWS-1; row >= 0; row--){
    for(int col = 0; col < COL; col++){
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
    while(row < ROWS){
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
    while(row < ROWS){
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
  int ini_col = COL-1;
  for(int ini_row = 0; ini_row < 3; ini_row++){
    int row = ini_row;
    int col = COL-1;

    bool num_found = false;
    int aligned = 0;
    while(row < ROWS){
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
  for(ini_col = COL-2; ini_col >= 3; ini_col--){
    int row = 0;
    int col = ini_col;
    bool num_found = false;
    int aligned = 0;
    while(row < ROWS){
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
			move(movUser(), 1);
		}
		else if (player == AI){ // Mueve el AI
			move(movUser(), 2); //cambiar movuser por movAI cuando exista el algoritmo
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
			cout << "Usuario gana(1)!"<<endl;
		}else if(player == USER){
			cout << "AI gana(2)!" <<endl;
		}
	}
}

int Linea4::Min(int p, int u){
  //Recibe el jugador p y el u y retorna el movimiento de p que minimiza el puntaje de u
	int min = 0; //Se inicializa el puntaje máximo en cero
	int best_move;
  int move_val;
  int copy_board [][];
	for(int c = 0; c < COL; c++){
    if (!isColumnFull){
      copy_board = board;
      move(copy_board, c, p);
      move_val = eval4(copy_board); //Entero que retorna la evaluación del movimiento ¡MODIFICAR!
        if(move_val < min){ //Si el valor del movimiento actual es menor que el valor del minimo
          min = move_val; //El mínimo es el valor del movimiento actual
					best_move = c; //El movimiento que minimiza es colocar ficha en la columna c
        }
      }
	 }
	return best_move; //Retornar el movimiento que mínimiza el puntaje del oponente
}

int Linea4::Max(int p){
  //Recibe el jugador, y retorna la columna en la que obtendría mayor puntaje para el siguiente juego
	int max = 0; //Se inicializa el puntaje máximo en cero
	int best_move;
  int move_val;
  int copy_board [][];
	for(int r = 0; r < ROWS; r++){
      if (!isColumnFull){
          copy_board = board;
          move(copy_board, c, p);
				  move_val = eval4(copy_board); //Entero que retorna la evaluación del movimiento ¡MODIFICAR!
				  if(move_val > max){ //Si el valor del movimiento actual es mayor que el valor del máximo
            max = move_val; //El máximo es el valor del movimiento actual
					  best_move = c; //El movimiento que maximiza es colocar ficha en la columna
          }
        }
	    }
  
	return best_move; //Retornar el movimiento que maximiza el puntaje
}
