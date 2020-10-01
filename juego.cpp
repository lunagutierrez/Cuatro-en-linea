#include <iostream>

using namespace std;

const int n=6;
const int m=7;

bool sobranEspaciosLibres(int tablero[n][m])
{ for(int i = 0; i < 6; i++){
    for(int j = 0; j < 7; j++){
       if(tablero[i][j] == 0)
            {
                //Sobran espacios donde colocar fechas
                //cout<<"Hay espacios"<<endl;
                return true;
            }
        }
    }
    //No sobran mas espacios donde colocar fichas, juego empatado
    cout<<"No hay mas espacios: empate"<<endl;
    return false;
}

void ImprimirTablero(int tablero[n][m]){
    for(int i = 0; i < 6; i++){
        for(int j = 0; j < 7; j++){
            if(tablero[i][j] == 1){
                cout<<" O ";
            }
            else if(tablero[i][j] == 2){
                cout<<" X ";
            }
            else{
                cout<<" . ";
            }
        }
        cout<<endl;
    }
}

int ColocarFichaEn(int tablero[n][m], int columna){
  for(int i = 0; i < 6; i++){
    if(!(i+1 > 5)){
      if(tablero[i][columna] == 0 && tablero[i+1][columna] != 0 ){
                return i;
            }
        }
        else
        {    //Alcanzo la base del tablero
          if(tablero[i][columna] == 0)
            {
                return i;
            }
        }
    }
    return -1;
}

bool columnaATope(int tablero[n][m], int columna){
    if(tablero[0][columna] != 0)
    {
        cout<<"No hay espacio para colocar la ficha ahi"<<endl;
        return true;
    }
    return false;
}

bool ganador(int tablero[n][m], int fila, int columna, int jugador)
{
    //Vertical
    bool encontrado = false;
    int total = 0;
    for(int i = 0; i < n; i++)
    {
        //cout<<"i: "<<i<<endl;
        if(encontrado){
            if(tablero[i][columna] == jugador){
                total++;
            }
            else{
                encontrado = false;
                total = 0;
            }
        }
        if(tablero[i][columna] == jugador && !encontrado){
            encontrado = true;
            total++;
        }

        //cout<<"total: "<<total<<endl;
        if(total == 4){
            cout<<"El jugador "<<jugador<<" gana!"<<endl;
            return true;
        }
    }

    //Horizontal
    encontrado = false;
    total = 0;

    for(int i = 0; i < m; i++){
        //cout<<"i: "<<i<<endl;
        if(encontrado){
            if(tablero[fila][i] == jugador){
                total++;
            }
            else{
                encontrado = false;
                total = 0;
            }
        }
        if(tablero[fila][i] == jugador && !encontrado){
            encontrado = true;
            total++;
        }
        //cout<<"total: "<<total<<endl;
        if(total == 4){
            cout<<"El jugador "<<jugador<<" gana!"<<endl;
            return true;
        }
    }

    //Diagonal \
    //Obtener Coordenadas donde inicia la diagonal en base a fila - columna
    int nuevaFila = fila;
    int nuevaColumna = columna;
    encontrado = false;
    total = 0;

    //cout<<"Fila: "<<fila<<" Columna: "<<columna<<endl;

    while((nuevaFila != 0 || nuevaColumna != 0)){
        nuevaFila--;
        nuevaColumna--;
        //cout<<"nueva Fila: "<<nuevaFila<<" nueva Columna: "<<nuevaColumna<<endl;
        if(nuevaFila == 0 || nuevaColumna == 0)
        break;
    }
    //cout<<"nueva Fila: "<<nuevaFila<<" nueva Columna: "<<nuevaColumna<<endl;

    do{
        if(nuevaFila >= n)
        break;

        //cout<<"nueva Fila: "<<nuevaFila<<" nueva Columna: "<<nuevaColumna<<endl;
        if(encontrado){
            if(tablero[nuevaFila][nuevaColumna] == jugador){
                total++;
            }
            else{
                encontrado = false;
                total = 0;
            }
        }
        if(tablero[nuevaFila][nuevaColumna] == jugador && !encontrado){
            encontrado = true;
            total++;
        }

        //cout<<"total: "<<total<<endl;
        if(total == 4){
            cout<<"El jugador "<<jugador<<" gana!"<<endl;
            return true;
        }
        nuevaFila++;
        nuevaColumna++;

    }while(nuevaFila < n);

    //Diagonal /
    nuevaFila = fila;
    nuevaColumna = columna;
    encontrado = false;
    total = 0;

    //cout<<"Fila: "<<fila<<" Columna: "<<columna<<endl;

    while((nuevaFila != 0 || nuevaColumna != m)){
        nuevaFila--;
        nuevaColumna++;
        //cout<<"nueva Fila: "<<nuevaFila<<" nueva Columna: "<<nuevaColumna<<endl;
        if(nuevaFila == 0 || nuevaColumna == m)
        break;
    }
    //cout<<"nueva Fila: "<<nuevaFila<<" nueva Columna: "<<nuevaColumna<<endl;
    do{
        //cout<<"nueva Fila: "<<nuevaFila<<" nueva Columna: "<<nuevaColumna<<endl;
        if(nuevaFila >= n)
        break;

        //cout<<"nueva Fila: "<<nuevaFila<<" nueva Columna: "<<nuevaColumna<<endl;
        if(encontrado){
            if(tablero[nuevaFila][nuevaColumna] == jugador){
                total++;
            }
            else{
                encontrado = false;
                total = 0;
            }
        }
        if(tablero[nuevaFila][nuevaColumna] == jugador && !encontrado){
            encontrado = true;
            total++;
        }

        //cout<<"total: "<<total<<endl;
        if(total == 4){
            cout<<"El jugador "<<jugador<<" gana!"<<endl;
            return true;
        }

        nuevaFila++;
        nuevaColumna--;

    }while(nuevaFila < n);

    return false;
}

int main(){
    int matriz[n][m];

    //Preparamos el tablero del juego rellenandolo con 0's
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            matriz[i][j] = 0;
            //cout<<matriz[i][j]<<" ";
        }
        //cout<<" "<<endl;
    }

    //Logica
    int jugador = 0;
    int ultimo = 0;
    do{   int colocarColumna = -1;
        bool columnaTope = true;

        if(ultimo == 1){
            jugador = 2;
        }
        else{
            jugador = 1;
        }

        do{
            cout<<"Turno del jugador "<<jugador<<" - Elije un numero del 1 al 7: "; cin>>colocarColumna; cout<<endl;
            colocarColumna--;
            columnaTope = columnaATope(matriz,colocarColumna);
        }
        while((colocarColumna < 0 || colocarColumna > 7) || columnaTope);

        int colocarFila = ColocarFichaEn(matriz,colocarColumna);
        matriz[colocarFila][colocarColumna] = jugador;
        ImprimirTablero(matriz);

        //Revisar si hay un 4 en raya
        if(ganador(matriz,colocarFila,colocarColumna,jugador))
        {
            break;
        }
        ultimo = jugador;
        jugador++;
    }
    while(sobranEspaciosLibres(matriz));

    return 0;
}
