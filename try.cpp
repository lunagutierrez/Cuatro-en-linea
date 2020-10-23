#include <iostream>	 // consola de la libreria standard (STL)
#include <vector>
using namespace std;

const int ROWS = 6, COL =7;

vector<vector<int> > board (ROWS, vector<int>(COL));

typedef unsigned int tColumnas[COL];

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

int main(){

	tColumnas top;
	inicializarJuego(board, top);
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
		gameover = movWin(board, player); //Revisa si el jugador gano (esta seria tu funcion Alejandra)

		turn +=1; //voy incrementando los turnos
		turn = turn%2;//si es par el turno le toca al usuario
		cout << endl;

		printBoard(board); // print board after successful move
	}
	//
	// move(board, movUser(), 1);
	// printBoard(board);
	//
	// move(board, movUser(), 2);
	// printBoard(board);
	//
	// move(board, movUser(), 1);
	// printBoard(board);
	//
	// move(board, movUser(), 2);
	// printBoard(board);
	//
	// move(board, movUser(), 1);
	// printBoard(board);
	//
	// move(board, movUser(), 2);
	// printBoard(board);
	//
	// move(board, movUser(), 1);
	// printBoard(board);
	//
	// move(board, movUser(), 2);
	// printBoard(board);
	//
	// move(board, movUser(), 1);
	// printBoard(board);
	//
	// move(board, movUser(), 2);
	// printBoard(board);
	// move(board, movUser(), 1);
	// printBoard(board);
	//
	// move(board, movUser(), 2);
	// printBoard(board);
	//

	return 0;

}
