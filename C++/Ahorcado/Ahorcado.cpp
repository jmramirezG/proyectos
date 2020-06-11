#include <iostream>
#include <string>
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

        char *falladas;

    public:
        Palabra() {         //Constructor por defecto
            letras = 0;
            oportunidades = 5;
            this->falladas = 0;
        }

        friend istream & operator>>(istream &i, Palabra &palabra);
        friend ostream & operator<<(ostream &o, Palabra &palabra);

        ~Palabra() {            //Destructor
            delete [] this->letras;
            delete [] this->falladas;
        }

        int comprobar(char const busqueda) {        //Comprueba un carácter
            bool coincide = false;

            for (int i = 0; i < this->palabra.length(); i++) {      //Recorre la palabra
                if (this->letras[i].letra == toupper(busqueda) && this->letras[i].acertada != true) {       //Si coincide y no se ha modificado antes
                    this->letras[i].acertada = true;        //Decimos que se ha adivinado
                    coincide = true;
                }
            }

            if (!coincide) {                //Si no hay coincidencias
                this->oportunidades--;  //Reducimos las oportunidades restantes
                char *aux = this->falladas;

                this->falladas = new char[5 - this->oportunidades];     //Añadimos la letra a las letras falladas
                for (int i = 1; i < 5 - this->oportunidades; i++) {
                    *(this->falladas + i) = *(aux + i - 1);
                }
                delete [] aux;      //Borramos el auxiliar
                *(this->falladas) = toupper(busqueda);
            }

            return this->oportunidades;     //Devolvemos las oportunidades restantes
        }

        const bool terminado() {            //Comprueba si hemos averiguado la palabra
            for (int i = 0; i < this->palabra.length(); i++) {
                if(this->letras[i].acertada == false) return false;
            }
            return true;
        }

        void Fallos() {         //Dice las letras falladas
            cout << "\nHa fallado las siguientes letras: ";
            for (int i = 0; i < 5 - this->oportunidades; i++) {
                cout << *(this->falladas + i) << " ";
            }
            cout << endl;
        }
};


istream & operator>>(istream &i, Palabra &palabra) {            //Permite introducir la palabra a adivinar
    
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

ostream & operator<<(ostream &o, Palabra &palabra) {                //Muestra las oportunidades restantes para la palabra
    o << "\nLe quedan " << palabra.oportunidades << " oportunidades para averiguar la palabra\n";

    for (int i = 0; i < palabra.palabra.length(); i++) {
        if (palabra.letras[i].acertada) {
            o << palabra.letras[i].letra << " ";
        } else o << "_ ";
    }

    return o;
}

int main() {
    inicio:         //Usamos goto para volver al inicio
    Palabra *palabra = new Palabra;     //Creamos la palabra en memoria dinámica
    cin >> *palabra;
    cin.ignore(1000, '\n');
    char letra;

    while (!(*palabra).terminado()) {
        cout << *palabra;
        cout << "Introduzca una letra: ";
        cin >> letra;
        cin.ignore(1000, '\n');

        if ((*palabra).comprobar(letra) == 0) {
            cout << "\n\n¡¡Se ha quedado sin oportunidades, ha perdido!!\n\n";      //Si nos quedamos sin oportunidades vamos al final
            goto fin;
        }

        (*palabra).Fallos();
    }
    cout << endl << endl << *palabra << "\n¡¡Enhorabuena!! Ha conseguido averiguar la palabra\n\n";

    fin:
    cout << "\nDesea introducir una nueva palabra (y/n)? ";
    char opcion;
    cin >> opcion;
    cin.ignore(1000, '\n');
    delete palabra;             //Borramos la palabra
    if (opcion == 'y') goto inicio;

    cout << "\n\nFinalizando...\n";
}