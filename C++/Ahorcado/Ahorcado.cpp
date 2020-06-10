#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>

using namespace std;

struct Letra {
    bool acertada;
    char letra;
};

class Palabra {
    private:
        string palabra;

        Letra *letras;

        int oportunidades;

    public:
        Palabra() {
            letras = 0;
            oportunidades = 5;
        }

        friend istream & operator>>(istream &i, Palabra &palabra);
        friend ostream & operator<<(ostream &o, Palabra &palabra);

        ~Palabra() {
            delete [] this->letras;
        }

        int comprobar(char letra) {
            bool coincide = false;

            letra = toupper(letra);

            for (int i = 0; i < this->palabra.length(); i++) {
                if (this->letras[i].letra == letra && this->letras[i].acertada == false) {
                    this->letras[i].acertada = true;
                    coincide = true;
                }
            }

            if (!coincide) this->oportunidades--;

            return this->oportunidades;
        }

        bool terminado() {
            for (int i = 0; i < this->palabra.length(); i++) {
                if(this->letras[i].acertada == false) return false;
            }
            return true;
        }
};


istream & operator>>(istream &i, Palabra &palabra) {
    cout << "\nIntroduzca la palabra que el otro jugador tiene que adivinar: ";
    i >> palabra.palabra;
    system("clear");
    palabra.letras = new Letra[palabra.palabra.length()];

    for (int i = 0; i < palabra.palabra.length(); i++) palabra.palabra[i] = toupper(palabra.palabra[i]);

    for (int i = 0; i < palabra.palabra.length(); i++) {
        palabra.letras[i].letra = palabra.palabra[i];
        palabra.letras[i].acertada = false;
    }

    return i;
}

ostream & operator<<(ostream &o, Palabra &palabra) {
    o << "\nLe quedan " << palabra.oportunidades << " oportunidades para averiguar la palabra\n";

    for (int i = 0; i < palabra.palabra.length(); i++) {
        if (palabra.letras[i].acertada) {
            o << palabra.letras[i].letra << " ";
        } else o << "_ ";
    }

    return o;
}

int main() {
    Palabra palabra;
    cin >> palabra;
    char letra;

    while (!palabra.terminado()) {
        cout << palabra;
        cout << "Introduzca una letra: ";
        cin >> letra;

        if (palabra.comprobar(letra) == 0) {
            cout << "\n\n¡¡Se ha quedado sin oportunidades, ha perdido!!\n\n";
            return 0;
        }
    }

    cout << endl << endl << palabra << "\n¡¡Enhorabuena!! Ha conseguido averiguar la palabra\n\n";
}