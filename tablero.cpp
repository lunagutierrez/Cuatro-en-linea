#include <iostream>
#include <map>
#include <list>
#include <stdexcept>
using namespace std;

//Definicion de clase tablero

class Tablero{
private:
  int Nf = 6; //Número de filas
  int Nc = 7; //Número de columnas

  //arreglos por columnas
  array<int,6> col1;
  array<int,6> col2;
  array<int,6> col3;
  array<int,6> col4;
  array<int,6> col5;
  array<int,6> col6;
  array<int,6> col7;

  //arreglo con casillas disponibles
  array<int,7> disponibles;

  //mapa que guarda todas las casillas y su estado
  map <int, int> tab;
public:
  Tablero(); //Constructor de un tablero que contenga 42 celdas
  int codifica(int f, int c); //Toma la fila y la columna y genera un código único para cada celda
  int decodifica_fila(int cod); //Toma el código y retorna la fila
  int decodifica_columna(int cod); //Toma el código y retorna la columna
  bool col_llena(int c); //Retorna verdadero si a una columna ya no se le pueden añadir fichas
  int primera_vacia(int c); //Retorna el código de la primera celda vacía en una columna que no esté completamente llena
  void casillas_dis_next(); //determina las casillas en las que podrían caer la ficha del siguiente turno
  //array_vecinas(int cod); //retorna un arreglo con los valores que hay en las casillas vecinas a una casilla
  //int evaluar_jugada(int cod, int jugador); //FUNCIÓN CLAVE - RECURSIVA: Retorna el puntaje que se obtiene al colocar una ficha en una celda
  //bool tablero_lleno(); //Determina si el tablero está completamente lleno
  //void display_tablero(); //imprime el estado actual del tablero
};

Tablero::Tablero(){ //Constructor de un tablero que contenga 42 celdas
    for(int i = 0; i < Nc; i++){
        int h = codifica(1,i+1);
        col1[i] = h;
        tab[h] = 0;
    }
    for(int i = 0; i < Nc; i++){
        int h = codifica(2,i+1);
        col2[i] = h;
        tab[h] = 0;
    }
    for(int i = 0; i < Nc; i++){
        int h = codifica(3,i+1);
        col3[i] = h;
        tab[h] = 0;
    }
    for(int i = 0; i < Nc; i++){
        int h = codifica(4,i+1);
        col4[i] = h;
        tab[h] = 0;
    }
    for(int i = 0; i < Nc; i++){
        int h = codifica(5,i+1);
        col5[i] = h;
        tab[h] = 0;
    }
    for(int i = 0; i < Nc; i++){
        int h = codifica(6,i+1);
        col6[i] = h;
        tab[h] = 0;
    }
    for(int i = 0; i < Nc; i++){
        int h = codifica(7,i+1);
        col7[i] = h;
        tab[h] = 0;
    }
}

int Tablero::codifica(int f, int c){
  int n = Nc * f + c;
  return n;
}

int Tablero::decodifica_fila(int cod){
  int f = cod / Nc;
  return f;
}

int Tablero::decodifica_columna(int cod){
  int c = cod % Nc;
  return c;
}

bool Tablero::col_llena(int c){ //Determina si a una columna ya no se le pueden añadir fichas
  bool v = true;
  if(c == 1){
    for(int i = 0; i < 6; i++){
      int h = col1[i];
      if(tab[h] != 0){
        v = true;
      }else{
        return false;
      }
    }

  }else if(c == 2){
    for(int i = 0; i < 6; i++){
      int h = col2[i];
      if(tab[h] != 0){
        v = true;
      }else{
        return false;
      }
    }

  }else if(c == 3){
    for(int i = 0; i < 6; i++){
      int h = col3[i];
      if(tab[h] != 0){
        v = true;
      }else{
        return false;
      }
    }

  }else if(c == 4){
    for(int i = 0; i < 6; i++){
      int h = col4[i];
      if(tab[h] != 0){
        v = true;
      }else{
        return false;
      }
    }

  }else if(c == 5){
    for(int i = 0; i < 6; i++){
      int h = col5[i];
      if(tab[h] != 0){
        v = true;
      }else{
        return false;
      }
    }

  }else if(c == 6){
    for(int i = 0; i < 6; i++){
      int h = col6[i];
      if(tab[h] != 0){
        v = true;
      }else{
        return false;
      }
    }

  }else if(c == 7){
    for(int i = 0; i < 6; i++){
      int h = col7[i];
      if(tab[h] != 0){
        v = true;
      }else{
        return false;
      }
    }

  }else{
    throw runtime_error("Ingrese un valor entre 1 y 7");
  }
  return v;
}

int Tablero::primera_vacia(int c){
  if(col_llena(c)){
    throw runtime_error("La columna está llena");
  }else if(c == 1){
    for(int i = 0; i < 6; i++){
      int h = col1[i];
      if(tab[h] != 0)
        return tab[h];
      }
  }else if(c == 2){
    for(int i = 0; i < 6; i++){
      int h = col2[i];
      if(tab[h] != 0)
        return tab[h];
      }
  }else if(c == 3){
    for(int i = 0; i < 6; i++){
      int h = col3[i];
      if(tab[h] != 0)
        return tab[h];
      }
  }else if(c == 4){
    for(int i = 0; i < 6; i++){
      int h = col4[i];
      if(tab[h] != 0)
        return tab[h];
      }
  }else if(c == 5){
    for(int i = 0; i < 6; i++){
      int h = col5[i];
      if(tab[h] != 0)
        return tab[h];
      }
  }else if(c == 6){
    for(int i = 0; i < 6; i++){
      int h = col6[i];
      if(tab[h] != 0)
        return tab[h];
      }
  }else if(c == 7){
    for(int i = 0; i < 6; i++){
      int h = col7[i];
      if(tab[h] != 0)
        return tab[h];
      }
  }else{
    throw runtime_error("Ingrese un valor entre 1 y 7");
  }
  return -1;
} //determina la primera celda vacía en una columna que no esté completamente llena

void Tablero::casillas_dis_next(){
  int h = 0;
  for(int i = 0; i < Nc; i++){
    if (!col_llena(i+1)){
      disponibles[i] = primera_vacia(i+1);
    }else{
      disponibles[i] = -1;
    }
  }
} //determina las casillas en las que podría caer la ficha en el siguiente turno


int main() {
  return 0;
}
