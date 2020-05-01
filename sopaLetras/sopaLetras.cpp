#include <iostream>
#include <string>

using namespace std;

int main() {
    char sopaLetras[10][10] = {
    'M', 'M', 'L', 'E', 'E', 'N', 'A', 'E', 'V', 'E',
    'E', 'R', 'H', 'O', 'N', 'G', 'O', 'S', 'T', 'R',
    'X', 'X', 'O', 'T', 'I', 'R', 'R', 'A', 'C', 'A',
    'I', 'S', 'A', 'P', 'P', 'O', 'T', 'A', 'P', 'S',
    'C', 'C', 'M', 'L', 'A', 'A', 'I', 'Z', 'O', 'T',
    'O', 'A', 'A', 'U', 'A', 'N', 'U', 'L', 'P', 'U',
    'S', 'O', 'M', 'B', 'R', 'E', 'R', 'O', 'M', 'P',
    'C', 'N', 'E', 'A', 'R', 'R', 'I', 'I', 'O', 'O',
    'W', 'O', 'J', 'E', 'N', 'O', 'C', 'P', 'Z', 'E',
    'A', 'A', 'Z', 'A', 'A', 'L', 'N', 'Y', 'T', 'D'
    };
    bool continuar, buscando, coincide;
    string palabra, posicion, opcion;
    int fila, columna;

    cout << "\nLa sopa de letras es:\n";        //Decimos la sopa de letras completa
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) cout << sopaLetras[i][j] << " ";
        cout << endl;
    }

    do {
        buscando = true;
        cout << "\nIntroduzca la palabra a buscar: ";
        getline(cin, palabra);
        
        for (int i = 0; i < palabra.length(); i++) if (palabra[i]> 'Z') palabra[i] -= 32;       //Si tenemos alguna minúscula en la palabra, la pasamos a mayúscula

        for (int i = 0; i < 10 - palabra.length() && buscando; i++) {           //Comprobación diagonal
            for (int j = 0; j < 10 - palabra.length() && buscando; j++) {   //Solo buscamos hasta cierta fila y columna, pues llegaría un momento que no cabría la palabra
                coincide = true;
                if (palabra[0] == sopaLetras[i][j]) {
                    for (int k = 0; k < palabra.length() && coincide; k++) {
                        if (palabra[k] != sopaLetras[i+k][j+k]) coincide = false;   //Si dejan de coincidir las letras, lo indicamos y salimos del for
                    }
                    if (coincide){          //Si coincide la palabra completa
                        buscando = false;   //Dejamos de buscar
                        fila = i+1;           //Guardamos las fila, columna y posición
                        columna = j+1;
                        posicion = "diagonal";
                    }
                }
            }
        }


        for (int i = 0; i < 10 && buscando; i++) {                              //Comprobación horizontal
            for (int j = 0; j < 10 - palabra.length() && buscando; j++) {       //Solo buscamos hasta cierta columna, pues a partir de ahí la palabra no cabría en la sopa
                coincide = true;
                if (palabra[0] == sopaLetras[i][j]) {
                    for (int k = 0; k < palabra.length() && coincide; k++) {
                        if (palabra[k] != sopaLetras[i][j+k]) coincide = false;
                    }
                    if (coincide){          //Si coincide la palabra completa
                        buscando = false;   //Dejamos de buscar
                        fila = i+1;           //Guardamos las fila, columna y posición
                        columna = j+1;
                        posicion = "horizontal";
                    }
                }
            }
        }


        for (int i = 0; i < 10 - palabra.length() && buscando; i++) {       //Comprobación vertical
            for (int j = 0; j < 10 && buscando; j++) {                  //Solo buscamos hasta cierta fila, pues a partir de ahí no cabría la palabra
                coincide = true;
                if (palabra[0] == sopaLetras[i][j]) {
                    for (int k = 0; k < palabra.length() && coincide; k++) {
                        if (palabra[k] != sopaLetras[i+k][j]) coincide = false;
                    }
                    if (coincide){          //Si coincide la palabra completa
                        buscando = false;   //Dejamos de buscar
                        fila = i+1;           //Guardamos las fila, columna y posición
                        columna = j+1;
                        posicion = "vertical";
                    }
                }
            }
        }


        if (!buscando) {        //Si salimos de algún bucle for antes de recorrerlo entero, significa que encontramos la palabra
            cout << "\nLa palabra " << palabra <<  " ha sido encontrada.\nSe ubica en la fila " << fila << " y en la columna " << columna << " en posición " << posicion << endl;
        } else cout << "\nNo se encontró la palabra " << palabra << endl;

        cout << "\nDesea introducir una nueva palabra? (si/no) ";       //Preguntamos si quiere introducir una palabra nueva para buscar
        getline(cin, opcion);

        continuar = (opcion == "no")?false:true;        //Si escribe "no", salimos, si no seguimos buscando

    } while (continuar);
    cout << "\nFinalizando...\n\n";
}