#include <iostream>
#include <string>

using namespace std;

string crearUsuario(string nombre, int tamanio) {
    for (int i = 0; i < nombre.length(); i++) {
        nombre[i] = tolower(nombre[i]);
    }
    string usuario;
    int contador = 0;
    for (int i = 0; i < nombre.length(); i++) {
        if (nombre[i] != ' ' && contador < tamanio) {
            usuario += nombre[i];
            contador++;
        }
        if (nombre[i] == ' ') {
            contador = 0;
        }
    }

    return usuario;
}

int main() {
    string nombre;
    cout << "Introduzca su nombre y apellidos: ";
    getline(cin, nombre);

    int tam;
    cout << "\nIntroduzca el tamaño que quiera: ";
    cin >> tam;

    cout << "\nSu nombre de usuario es: " << crearUsuario(nombre, tam) << endl;
}