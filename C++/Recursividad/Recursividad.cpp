#include <iostream>

using namespace std;

const int tam = 10;

void mostrar(int matriz[tam][tam]) {
    cout << "\nLa matriz es: " << endl;
    for (int i = 0; i < tam; i++) {
        for (int j = 0; j< tam; j++) {
            cout << matriz[i][j] << " ";
        }
        cout << endl;
    }
}

int mayor(int array[], int pos = 0, int devuelto = 0) {
    if (array[pos] > devuelto) {
        devuelto = array[pos];
    }
    if (pos == tam-1) {
        return devuelto;
    } else {
        return mayor(array, pos+1, devuelto);
    }
}

void mayoresFila(int matriz[tam][tam]) {
    int mayores[tam];
    for (int i = 0; i < tam; i++) {
        mayores[i] = mayor(matriz[i]);
    }

    for (int i = 0; i < tam; i++) {
        cout << "\nEl mayor de la fila " << i+1 << " es: " << mayores[i];
    }
    cout << endl;

}

void iniciarMatriz(int matriz[tam][tam]) {
    for (int i = 0; i < tam; i++) {
        cout << "\nIntroduzca los elementos de la fila " << i+1 << " separados por espacios(" << tam << " en total): ";
        for (int j = 0; j < tam; j++) {
            cin >> matriz[i][j];
        }
    }
}


int main() {
    int matriz[tam][tam];
    iniciarMatriz(matriz);
    mostrar(matriz);
    mayoresFila(matriz);
}