#include <iostream>
#include <string>

using namespace std;


bool comprobarHorizontal(char sopa [100] [100], string palabra, int &fila, int &columna) {
    bool buscando = true, coincide = true;
    for (int i = 0; i < fila && buscando; i++) {                              //Comprobación horizontal
        for (int j = 0; j < columna - palabra.length() && buscando; j++) {       //Solo buscamos hasta cierta columna, pues a partir de ahí la palabra no cabría en la sopa
            coincide = true;
            if (palabra[0] == sopa[i][j]) {
                for (int k = 0; k < palabra.length() && coincide; k++) {
                    if (palabra[k] != sopa[i][j+k]) coincide = false;
                }
                if (coincide) {
                    buscando = false;
                    fila = i + 1;
                    columna = j + 1;
                }
            }
        }
    }
    return !buscando;
}

bool comprobarVertical(char sopa [100] [100], string palabra, int &fila, int &columna) {
    bool buscando = true, coincide = true;
    for (int i = 0; i < fila - palabra.length() && buscando; i++) {                              //Comprobación vertical
        for (int j = 0; j < columna && buscando; j++) {       //Solo buscamos hasta cierta fila, pues a partir de ahí la palabra no cabría en la sopa
            coincide = true;
            if (palabra[0] == sopa[i][j]) {
                for (int k = 0; k < palabra.length() && coincide; k++) {
                    if (palabra[k] != sopa[i+k][j]) coincide = false;
                }
                if (coincide){
                    buscando = false;
                    fila = i + 1;
                    columna = j + 1;
                }
            }
        }
    }
    return !buscando;
}

bool comprobarDiagonal(char sopa [100] [100], string palabra, int &fila, int &columna) {
    bool buscando = true, coincide = true;
    for (int i = 0; i < fila - palabra.length() && buscando; i++) {                              //Comprobación diagonal
        for (int j = 0; j < columna - palabra.length() && buscando; j++) {       //Solo buscamos hasta cierta columna y fila, pues a partir de ahí la palabra no cabría en la sopa
            coincide = true;
            if (palabra[0] == sopa[i][j]) {
                for (int k = 0; k < palabra.length() && coincide; k++) {
                    if (palabra[k] != sopa[i+k][j+k]) coincide = false;
                }
                if (coincide){
                    buscando = false;
                    fila = i + 1;
                    columna = j + 1;
                }
            }
        }
    }
    return !buscando;
}


void mostrar(char matriz[100][100], int filas, int columnas) {
    cout << "\nLa sopa de letras es:\n";        //Decimos la sopa de letras completa
    for (int i = 0; i < filas; i++) {
        for (int j = 0; j < columnas; j++) cout << matriz[i][j] << " ";
        cout << endl;
    }
}

int main() {
    char sopaLetras[100][100];
    bool continuar, coincide;
    string palabra, posicion, opcion, filas;
    int fila = 0, columna;
    cout << "\nIntroduzca la sopa de letras: ";
    getline(cin, filas);
    while (filas != "0") {
        columna = filas.length();
        for (int i = 0; i < columna; i++) sopaLetras[fila] [i] = filas [i];
        fila++;
        getline(cin,filas);
    }
    int guardarF = fila, guardarC = columna;
    mostrar(sopaLetras, guardarF, guardarC);

    do {
        coincide = false;
        fila = guardarF;
        columna = guardarC;
        cout << "\nIntroduzca la palabra a buscar: ";
        getline(cin, palabra);
        
        for (int i = 0; i < palabra.length(); i++) if (palabra[i]> 'Z') palabra[i] -= 32;       //Si tenemos alguna minúscula en la palabra, la pasamos a mayúscula

        if (comprobarVertical(sopaLetras, palabra, fila, columna)) coincide = true;

        if (!coincide) if (comprobarHorizontal(sopaLetras, palabra, fila, columna)) coincide = true;

        if (!coincide) if (comprobarDiagonal(sopaLetras, palabra, fila, columna)) coincide = true;


        if (coincide) {        //Si salimos de algún bucle for antes de recorrerlo entero, significa que encontramos la palabra
            cout << "\nLa palabra " << palabra <<  " ha sido encontrada.\nSe ubica en la fila " << fila << " y en la columna " << columna << endl;
        } else cout << "\nNo se encontró la palabra " << palabra << endl;

        cout << "\nDesea introducir una nueva palabra? (si/no) ";       //Preguntamos si quiere introducir una palabra nueva para buscar
        getline(cin, opcion);

        continuar = (opcion == "no")?false:true;        //Si escribe "no", salimos, si no seguimos buscando

    } while (continuar);
    cout << "\nFinalizando...\n\n";
}