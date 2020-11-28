#include <iostream>

#include "connect4.hpp"
using namespace std;

int main(){

  int b;
  int h;

  cout << "Bienvenido a Cuatro en Linea" << endl;

  bool playing = true;
  // Empieza el juego:
  while(playing){
    Linea4 juego; // Llamo al objeto para crear el juego.
    cout << "Individual [0] o Multijugador [1]? ";
    cin >> b; // Escoger modalidad de juego.

    if(b == 0){ // Juego contra ordenador.
      juego.playAI();
      cout << endl << "Jugar de nuevo?" << endl;
      cout << "Ingrese [1] para volver a jugar, y cualquier otro valor para salir: ";
      cin >> h;
        if(h != 1){
          playing == false;
          break; // Termina el juego.
        }

    }else if(b == 1){ // Juego para dos jugadores.
      juego.play2players();
      cout << endl << "Jugar de nuevo?" << endl;
      cout << "Ingrese [1] para volver a jugar, y cualquier otro valor para salir: ";
      cin >> h;
        if(h != 1){
          playing == false;
          break; // Termina el juego.
        }
    }else{
      cout << "Ingrese 1 o 0." << endl; // Mensaje de aviso.
    }
  }

  // Despedida.
  cout << endl << "Gracias por jugar 4 en linea" << endl;
  cout << endl << "Hasta la proxima" << endl;
  return 0;
}
