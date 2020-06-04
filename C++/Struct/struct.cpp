#include <iostream>
#include <string>

using namespace std;

struct Pieza {
    string numPieza;
    string piezasRel;
    string muebles;
};

void anadirPiezas(Pieza mueble[], string piezas) {
    int contador = 0;
    int numPiezas = 1;
    for (int i = 0; i < piezas.length(); i++) {
        if (piezas[i] == ' ') {
            numPiezas++;
        }
    }
    for (int i = 0; i < numPiezas; i++) {
        for (int j = 0; j < contador; j++){
            mueble[i].piezasRel += piezas[j];
        }
        while (piezas[contador] != ' ' && contador<piezas.length()) {
            mueble[i].numPieza += piezas[contador];
            contador++;
        }
        contador++;
        for (int j = contador; j < piezas.length(); j++) {
            mueble[i].piezasRel += piezas[j];
        }
    }
}

Pieza * crearPiezas(string mueble, string piezas) {
    int numPiezas = 1;
    for (int i = 0; i < piezas.length(); i++) {
        if (piezas[i] == ' ') {
            numPiezas++;
        }
    }

    Pieza * array = new Pieza[numPiezas];
    
    for (int i = 0; i < numPiezas; i++) {
        array[i].muebles = mueble;
    }

    anadirPiezas(array, piezas);

    return array;
}

void mostrar(Pieza array[]) {
    int numPiezas = 1;
    for (int i = 0; i < array[0].piezasRel.length(); i++) {
        if (array[0].piezasRel[i] == ' ') {
            numPiezas++;
        }
    }

    cout << "\nLas piezas pertenecen al mueble: " << array[0].muebles << endl;
    for (int i = 0; i < numPiezas; i++) {
        cout << "\nPieza numero " << i+1 << ": " << array[i].numPieza;
        cout << "\nPiezas relacionadas: " << array[i].piezasRel << endl;
    }
}



int main() {
    cout << "\nIntroduzca el mueble: ";
    string mueble;
    getline(cin, mueble);
    cout << "\nIntroduzca las piezas que lo componen separadas por espacios:\n";
    string piezas;
    getline(cin, piezas);

    Pieza * array = crearPiezas(mueble, piezas);

    mostrar(array);

    delete [] array;
}