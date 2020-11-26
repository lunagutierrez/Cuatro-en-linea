#include <iostream>

#include "try.hpp"
using namespace std;

int main(){

  int b;
  int h;

  cout << "Bienvenido a Cuatro en Linea" << endl;

  bool playing = true;

  while(playing){
    Linea4 juego;
    cout << "Individual [0] o Multijugador [1]? ";
    cin >> b;

    if(b == 0){
      juego.playAI();
      cout << endl << "Jugar de nuevo?" << endl;
      cout << "Ingrese [1] para volver a jugar, y cualquier otro valor para salir: ";
      cin >> h;
        if(h != 1){
          playing == false;
          break;
        }

    }else if(b == 1){
      juego.play2players();
      cout << endl << "Jugar de nuevo?" << endl;
      cout << "Ingrese [1] para volver a jugar, y cualquier otro valor para salir: ";
      cin >> h;
        if(h != 1){
          playing == false;
          break;
        }
    }else{
      cout << "Ingrese 1 o 0" << endl;
    }
  }

  cout << endl << "Gracias por jugar 4 en linea" << endl;
  cout << endl << "Hasta la proxima" << endl;
  return 0;
}
