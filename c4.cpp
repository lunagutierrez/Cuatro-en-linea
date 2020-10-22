#include <iostream>	 // consola de la libreria standard (STL)
#include <vector>
using namespace std;

const int ROWS = 6, COL =7;
bool gameOver = false;
int beta;
int alpha = 0 - beta;
int turn;
int USER = 1;
int AI = 2;
int currentp = USER;

vector<vector<int> > board (ROWS, vector<int>(COL));

typedef unsigned int tColumnas[COL]; //siempre positivas

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

bool won(vector<vector<int> > &board, int p) { //recibe tablero y jugador
	int adjacent = 0; //contador de piezas contiguas

	//horizontal
	//vertical
	//diagonales

	return false; // Nnadie ha ganado
}

int heuristica(vector<unsigned int> v, unsigned int p) {
	int score = 0;
	unsigned int good = 0; // puntos a favor del jugador p
	unsigned int bad = 0; // puntos a favor del jugador p
	unsigned int blank = 0; // puntos neutros
	for (int i = 0; i < v.size(); i++) { //hago la cuenta de cuantos hay de cada uno
		good += (v[i] == p) ? 1 : 0; //si es verdadero va sumando 1
		bad += (v[i] == USER || v[i] == AI) ? 1 : 0;//si es verdadero va sumando 1
		empty += (v[i] == 0) ? 1 : 0;//si es verdadero va sumando 1
	}
	//bad es bad+good
	bad -= good;
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

int ValorMax(int p){ //Recibe el jugador, y retorna la columna en la que tiene que colocar la ficha para máximizar su puntaje
	int max = 0; //Se inicializa el puntaje máximo en cero
	int best_move; 
	for(int r = 0; r < ROWS; r++){ 
		for(int c = 0; c < COL; c++){ 
			if(board[r][c] != 0){ //primera casilla vacía de la columna c
				vector <vector<int>> board_copy = board; //se crea una copia del tablero de juego
				move(vector<vector<int> >& board_copy, c, p); //A esa copia se le agrega una ficha en la columna c
				int move_val = heuristica(board_copy,p); //Entero que retorna la evaluación del movimiento
				if(move_val > max){ //Si el valor del movimiento actual es mayor que el valor del máximo
					max = move_val; //El máximo es el valor del movimiento actual
					best_move = c; //El movimiento que maximiza es colocar ficha en la columna c
				}
			}
		}
	}
	return best_move; //Retornar el movimiento que maximiza el puntaje
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
			move(board, movUser(), 2); //cambiar movuser por movAI cuando exista el algoritmo
		}
		else if (turn == COL*ROWS) { // Si llego al num max de turnos
			gameover = true;
			cout <<
		}
		gameover = won(board, player); //Revisa si el jugador gano (esta seria tu funcion Alejandra)

		turn +=1; //voy incrementando los turnos
		turn = turn%2;//si es par el turno le toca al usuario
		cout << endl;

		printBoard(board); //print board after move
	}


	return 0;

}
