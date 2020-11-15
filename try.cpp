
#include <iostream>	 // consola de la libreria standard (STL)
#include <climits>
#include "try.hpp"

int turn;
const int USER = 1;
const int AI = 2;



unsigned int DEPTH = 3;

Linea4::Linea4(){//constructor del juego
  for(int f = 0; f < ROWS; f++){
    for(int c = 0;c < COL; c++){
      board[f][c] = 0; // inicializar el tablero en ceros.
    }
  }
}

void Linea4::printBoard(int b[ROWS][COL]){

    cout << endl << ". . . . . . . ." << endl;
    for (int j = 0; j < ROWS; j++){
      for (int k = 0; k < COL; k++){
        cout << "|";
        switch (b[ROWS - j - 1][k]){
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
        if (k + 1 == COL){
          cout << "|";
        }
      }
      cout << endl;
    }
    cout << "---------------" << endl;
    for (int i = 0; i < COL; i++){
      cout << " " << i; //imprimo el numero de la casilla
    }
    cout << endl;
}

bool Linea4::isColumnFull(int column, int b[ROWS][COL]){
  for(int fila = 0; fila < ROWS; fila++){
      if(b[fila][column] == 0){ //si no hay nada en esa casilla
        return false;
      }
    }
  return true; //retorna true cuando alguna columna está llena de fichas.
}

void Linea4::move(int b[ROWS][COL],int col, int player){
// toma el tablero, la columna y el jugador
  for (int i = 0; i < ROWS; i++){
    if(!isColumnFull(col, b)){//mientras esa columna no este llena
      if (b[i][col] == 0){ // Lo pone en la primera fila disponible
        b[i][col] = player; // posiciona la pieza en esa casilla
        break;
      }
    }
  }
}

int Linea4::movUser(){

    cout << "Es tu turno..." << endl;
    int col;

    while(true){//repita el proceso hasta que se ingrese un valor valido
      cout << "Ingrese la columna en la que desea poner su ficha: ";
      cin >> col; //tomo como input en donde la pondra

      if(!cin){// en caso de que el input no sea un entero
        cin.clear();
        cin.ignore(INT_MAX, '\n');
        cout << "Ingrese un numero entre 0 y 6" << endl;
      }
      else if (!(col >= 0 && col < COL)){
        cout << "Esa no es una columna valida" << endl; //se puede hacer con un except
      }else if (isColumnFull(col, board)){ // En caso de que la columna ya este llena
        cout << "Esa columna ya esta llena" << endl; //se puede hacer con un except
      cout << endl;
      }else{
        break;
      }
    }
    return col;
  }

int Linea4::moveAI(){
  int col = miniMax(board, DEPTH, AI)[0]; //retorna la columna
  cout << "Es mi turno, voy a poner en la columna: " << col << endl;
  return col;
}

int Linea4::heuristica(int s[4], int p){

  unsigned int blank = 0; // puntos neutros
  unsigned int bad = 0; // puntos a favor del otro jugador p
  unsigned int good = 0; // puntos a favor de p

  int score = 0;

  for (int i = 0; i < 4; i++){ //hago la cuenta de cuantos hay de cada uno
    if (s[i] == p){//Si en esa casilla hay una ficha del jugador
      good+=1;//sumo a fichas a favor
    }else if(s[i] == 0){
      blank+=1;
    }else{
      bad+=1;
    }
  }

  if (good == 4)
    score += 1000;  //prefiere ganar que bloquear
  else if (good == 3 && blank == 1)
    score += 500;
  else if (good == 2 && blank == 2)
    score += 50;
  else if (bad == 2 && blank == 2)
    score -= 51;  //prefiere bloquear
  else if (bad == 3 && blank == 1)
    score -= 501;  //prefiere bloquear
  else if (bad == 4)
    score -= 999;

  return score;
}

int Linea4::eval4(int b[ROWS][COL], int p){ //toma el estado actual del tablero y el jugador en turno

  int col[ROWS];//arreglo que define las columnas
  int row[COL]; //arreglo que define las filas
	int segm[4]; //arreglo para revisar en segmentos de a 4 espacios

  int puntos = 0;//contador del puntaje inicializado en 0

  int x;
  int y;
  int i;

	// vert (misma col)
	for (x = 0; x < COL; x++){
	 for (y = 0; y < ROWS; y++){
		 col[y] = b[y][x];//arreglo que define la columna
	 }
	 for (y = 0; y < ROWS - 3; y++){ // al restarle 3, cuando le sumo i quedo dentro del rango del tablero
		 for (i = 0; i < 4; i++){//las 4 casillas
			 segm[i] = col[y + i];//voy sumando para crear el segmento vertical de 4 casillas
		 }
		 puntos += heuristica(segm, p); //al puntaje le sumo el valor del analisis de ese segmento
	 }
	}

  //hor (misma fila)
	for (y = 0; y < ROWS; y++){
		for (x = 0; x < COL; x++){
			row[x] = b[y][x];//arreglo que defina una fila
		}
    for (x = 0; x < COL - 3; x++){
			for (int i = 0; i < 4; i++){ //las 4 casillas
				segm[i] = row[x + i]; //crea cada posible segmento horizontal
			}
			puntos += heuristica(segm, p); //al puntaje le sumo el valor del analisis de ese segmento
		}
  }

    for (y = 0; y < ROWS-3; y++){
  		for (x = 0; x < COL; x++){
  			row[x] = b[y][x];//arreglo que defina una fila
  		}

  //Diagonales
    //Diagonal \ izq arriba a der abajo
		for (x = 0; x < COL - 3; x++){
			for (i = 0; i < 4; i++){//las 4 casillas
				segm[i] = b[y - i + 3][x + i]; //segmento que empieza a la izquierda arriba
                                       //y desciende a medida que i va aumentando
			}
			puntos += heuristica(segm, p); //puntaje para ese \ segmento
		}

	  // Diagonal / izq abajo a der arriba
    for (x = 0; x < COL - 3; x++){
			for (int i = 0; i < 4; i++){//las 4 casillas
				segm[i] = b[y + i][x + i]; //segmento que empieza abajo a la izq y
                                   //va aumentando proporcionalmente en filas y columnas
        }
			puntos += heuristica(segm, p); //puntaje para el segmento /
		}
	}

	return puntos; //retorno el puntaje tras el analisis
}

bool Linea4::isWinner(int player, int b[ROWS][COL]){
  /*
  Funcion que verifica si el jugador player ganó la partida
  Dentro la función del juego se verificará por separado jugador 1 y jugador 2
  */
  // 1. Se verifica verticalmente si hay 4 fichas alineadas
  if(VerificarV(player, b) == true){
    //cout << "We have a winner. Player "<< player << " wins!";
    return true;
  }else if(VerificarH(player, b) == true){
    // 2. Se verifica horizontalmente si hay 4 fichas alineadas
    //cout << "We have a winner. Player "<< player << " wins!";
    return true;

  }else if(VerificarD(player, b) == true){
    // 3. Se verifica en diagonal \ si hay 4 fichas alineadas
    //cout << "We have a winner. Player "<< player << " wins!";
    return true;
  }else{
    //Si en ningun caso se encontro 4 en linea, se retorna false
    return false;
  }
}

vector<int> Linea4::miniMax(int b[ROWS][COL], int d, int p){
  //vector de 2 enteros {columna, puntaje}
  //alpha es la mejor opcion para maximizar
  //beta es la mejor opcion para el jugador a minimizar

  if (d == 0){
    // retorno el puntaje para esa situacion
    return vector <int> {7, eval4(b, AI)};
  }

  //mini
  if(p == USER){//si es el jugador a minimizar
    vector<int> bestMov = {7, INT_MAX}; //vamos a minimizar al oponente
    if (isWinner(AI, b)){
      return bestMov; //Si va a ganar el AI ese va a ser el mejor mov
    }

    for (int c = 0; c < COL; c++){
      if (!isColumnFull(c, b)){ // si es posible poner una ficha ahi

        int copyBoard [ROWS][COL];//copia del estado actual del tablero
        for(int i = 0; i < ROWS; i++){
          for(int j = 0; j < COL; j++){
            copyBoard[i][j] = b[i][j];
          }
        }

        move(copyBoard, c, p); //pruebo ese movimiento en la copia
        int score = miniMax(copyBoard, d - 1, AI)[1]; // mi puntaje va a ser el del siguiente nivel

        if (score < bestMov[1]){
          bestMov = {c, score};
        }

      }
    }
    return bestMov;//retorno la mejor opcion posible

  //max
  }else{ // si es el jugador a maximizar
    vector<int> bestMov = {7, INT_MIN}; // Para maximizar comenzamos con el menor valor posible y una col cualquiera
	  
    for (int c = 0; c < COL; c++){ //para cada columna
      if (!isColumnFull(c, b)){ //si es posible hacer un movimiento

        int copyBoard [ROWS][COL];//copia del estado actual del tablero
        for(int i = 0; i < ROWS; i++){
          for(int j = 0; j <COL; j++){
            copyBoard[i][j] = b[i][j];
          }

        }
        move(copyBoard, c, p); //pruebo ese movimiento
        int score = miniMax(copyBoard, d - 1, USER)[1]; //Encuentro el valor asociado al siguiente nivel
        if (score > bestMov[1]){ // Si el puntaje es mejor
          bestMov = {c, score}; // se convierte en mi nuevo mov posible
        }
      }
    }
    return bestMov; //retorno ese mejor movimiento posible

  }
}

//==============================================================================
// FUNCIONES PRIVADAS
bool Linea4::VerificarV(int player, int b[ROWS][COL]){
  // Funcion que verifica verticalmente en todas las columnas.
  // si hay  fichas 4 en linea de player.
  // el booleando que confirma si encontró el número del jugador.
  int aligned = 0; // contador de fichas del mismo jugador que están alineadas.

  for (int c = 0; c < COL; c++){
    for (int r = 0; r < ROWS - 3; r++){
      for (int i = 0; i < 4; i++){ // se necesitan 4 fichas
        if (b[r + i][c] == player){
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
bool Linea4::VerificarH(int player, int b[ROWS][COL]){
// Funcion que verifica horizontalmente en todas las columnas.
// si hay  fichas 4 en linea de player.

  int aligned = 0; // contador de fichas del mismo jugador que están alineadas.

  for (int c = 0; c < COL - 3; c++){ // for cada columna sin salirnos del rango
    for (int r = 0; r < ROWS; r++){ // for cada fila
      for (int i = 0; i < 4; i++){ // se necesitan 4 fichas
        if (b[r][c + i] == player){
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
bool Linea4::VerificarD(int player, int b[ROWS][COL]){
  int aligned = 0;//contador de fichas contiguas del mismo jugador
  // diagonales
    //de der a izq
  for (int c = 0; c < COL - 3; c++){
    for (int r = 0; r < ROWS - 3; r++){
      for (int i = 0; i < 4; i++){// se necesitan 4 fichas
        if (b[r + i][c + i] == player){
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
        if (b[r - i][c + i] == player){
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
//JUEGO PARA UN JUGADOR
//---------------------------------------------------------------------------

void Linea4::playAI(){
  cout << "Juguemos 4 en linea!" << endl;
  turn = 0;
  // cout << "Escoge el nivel de dificultad: " << endl;
  // cin >> dif;
  printBoard(board);

  bool gameover = false;//inicializador del juego
  int player = USER; //jugador actual
  //int turn = 0; //count para los turnos
  int c;

  while (!gameover){
    if(player == USER){ // Mueve el usuario en el primer turno
      move(board, movUser(), 1);
      cout << "turno:" << turn;
    }
    else if (player == AI){ // Mueve el AI
      move(board, moveAI(), 2); //cambiar movuser por movAI cuando exista el algoritmo
      cout << "turno:" << turn;
    }
    else if (turn == CELLS-1){ // Si llego al num max de turnos
      gameover = true;
      break;
    }


    c = 0;
    for(int i = 0; i < COL; i++){
      if (isColumnFull(i,board)){
          c++;
      }
    }

    if(c == 7){
      gameover = true;
    }else{
      gameover = isWinner(player, board); //Revisa si el jugador gano (esta seria tu funcion Alejandra)
    }

    if(player == 1){
      player = 2;
    }else{
      player = 1;
    }

    turn +=1; //voy incrementando los turnos

    //turn = turn%2;//si es par el turno le toca al usuario
    cout << endl;

    printBoard(board); //imprimo el tablero tras cada mov
  }


  if(!(isWinner(1, board) != 0 || isWinner(2, board) != 0)){
    cout << endl << "Empate" << endl;

  }else{ // Si alguien gana

    if (player == AI){
      cout << "Usuario gana(X)!"<<endl;
    }else if(player == USER){
      cout << "AI gana(O)!" <<endl;
    }
  }
}

//---------------------------------------------------------------------------
//JUEGO PARA DOS JUGADORES
//---------------------------------------------------------------------------

void Linea4::play2players(){
  cout << "Juguemos 4 en linea!" << endl;
  turn = 0;
  // cout << "Escoge el nivel de dificultad: " << endl;
  // cin >> dif;
  printBoard(board);

  bool gameover = false;//inicializador del juego
  int player = USER; //jugador actual
  //int turn = 0; //count para los turnos
  int c;

  while (!gameover){
    if(player == USER){ // Mueve el usuario en el primer turno
      move(board, movUser(), 1);
      cout << "turno:" << turn;
    }
    else if (player == AI){ // Mueve el AI
      move(board, movUser(), 2); //cambiar movuser por movAI cuando exista el algoritmo
      cout << "turno:" << turn;
    }

    c = 0;
    for(int i = 0; i < COL; i++){
      if (isColumnFull(i,board)){
        c++;
      }
    }

    if(c == 7){
      gameover = true;
    }else{
      gameover = isWinner(player, board); //Revisa si el jugador gano (esta seria tu funcion Alejandra)
    }

    if(player == 1){
      player = 2;
    }else{
      player = 1;
    }

    turn +=1; //voy incrementando los turnos

    //turn = turn%2;//si es par el turno le toca al usuario
    cout << endl;

    printBoard(board); //imprimo el tablero tras cada mov
  }


  if(!(isWinner(1, board) != 0 || isWinner(2, board) != 0)){
    cout << endl << "Empate" << endl;

  }else{ // Si alguien gana
    if (player == AI){
      cout << "Gana Usuario 1 (X)!"<<endl;
    }else if(player == USER){
      cout << "Gana Usuario 2 (O)!" <<endl;
    }
  }
}
