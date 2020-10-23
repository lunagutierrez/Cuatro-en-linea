#include "c4.hpp"



const int COL = 7;
const bool gameOver = false;
int beta;
int alpha = 0 - beta;

int difficulty;
int filled = 0; //contador de casillas llenas

typedef unsigned int tColumnas[COL];
vector<vector<int>> board(ROWS, vector<int>(COL));

void printBoard(vector<vector<int> > &b) {
	for (int i = 0; i < COL; i++) {
		cout << " " << i;
	}
	cout << endl << "---------------" << endl;
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
			if (k + 1 == COL) { cout << "|"; }
		}
		cout << endl;
	}
	cout << "---------------" << endl;
	cout << endl;
}

void inicializarJuego(vector<vector<int> > board, tColumnas top){
	//inicializa un tablero vacio
	for (int j = 0; j < COL; j++) {
		board[0][j] = 0;
		top[j] = 0;
	}
	for (int i = 1; i< ROWS; i++)
		for (int j = 0; j < COL; j++)
			board[i][j] = 0;
}


void move(vector<vector<int> >& board, int col, int player){
  // toma el tablero, la columna y el jugador
  for (int i = 0; i < ROWS; i++) {
		if (board[i][col] == 0) { // Lo pone en la fila disponible
			board[i][col] = player; // posiciona la pieza
			break;
		}
	}
}

int movUser(){
  int mov;
  cout << "Es tu turno..." << endl;
  while(true){//repita el proceso hasta que se ingrese un valor valido
    cout << "Ingrese la columna en la que desea poner su ficha: ";
    cin >> mov; //tomo como input en donde la pondra

    if (!(0 <= mov && mov < COL)) // si no esta en el rango de columnas
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

int movAI(){
  cout << "Es mi turno..." << endl;
  //toma el tablero, el nivel de dificultad, alpha, beta y el jugador actual
  return miniMax(board, dificculty, alpha, beta, 2)[1];
  //retorna la columna que garantiza la mejor jugada
}



bool movWin(vector<vector<int>>&b, int p){


	
}

array<int, 2> miniMax(vector<vector<int>> &b, int dif, int a, int b, int player){
//alpha es la mejor opcion para maximizar
//beta es la mejor opcion para el jugador a minimizar

  if(dif == 0 || dif >= )
  //si ya he analizado cada nivel del arbol o he llegado a una hoja
    return array<int, 2>{score(b, 2), -1};

  if(player == 2){ //si el jugador es el AI
    //tendremos que maximizar sus acciones
    array<int, 2> curr =  {score(b, 2), -1}; //dado que maximizamos necesitamos el menor valor posible

  }else{// si es el usuario minimizamos las acciones

  }
}

int score(vector<vector<int> > &b, int player){
  int score = 0; //lo inicializo en 0
}





void play(){
  cout << "Juguemos 4 en linea!" << endl;
  cout << "Escoge el nivel de dificultad: " << endl;
  cin >> difficulty;

  printBoard(board);

  bool gameover = false;//inicializador del juego
  int player = 1; //jugador actual
	int turn = 0; //count para los turnos

	while (!gameover){
    if(turn == 0){ // Mueve el usuario en el primer turno
      move(board, movUser(), 1);
    }
    else if (turn == 1){ // Mueve el AI
      move(board, movAI(), 2);
    }
    else if (turn == COL*ROWS) { // Si llego al num max de turnos
      gameover = true;
    }
    gameover = movWin(board, player); //Revisa si el jugador gano

    turn +=1; //voy incrementando los turnos
    turn = turn%2;//si es par el turno le toca al usuario
		cout << endl;

		printBoard(board); // print board after successful move
	}

}


//defs funcs
