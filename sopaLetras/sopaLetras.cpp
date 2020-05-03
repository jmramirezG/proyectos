#include <iostream>
#include <string>

using namespace std;

//---------------------------------------------------------------------------CLASE PALABRA-----------------------------------------------------------------------------------
class Palabra {
    private:
        string palabra;     //Palabra que vamos a buscar
        int fila;           //Fila y columna en la que la encontramos
        int columna;
        string posicion;        //Posición en la que la encontramos (horizontal, vertical...)
        int longitud;           //Logitud de la palabra, para evitar abusar de .length()

    public:
        Palabra() {
            fila = 0;
            columna = 0;
            longitud = 0;
            palabra = "0";
            posicion = "0";
        }

        Palabra(string entrada) {       //Creamos la clase a partir de una palabra de entrada
            this->longitud = entrada.length();
            for (int i = 0; i < entrada.length(); i++) if (entrada[i]> 'Z') entrada[i] -= 32;
            this->palabra = entrada;
            fila = 0;
            columna = 0;
            posicion = "0";
        }

        friend class SopaLetras;

        inline int devolverFila() const {
            return fila;
        }

        inline int devolverColumna() const {
            return columna;
        }

        inline string devolverPosicion() const {
            return posicion;
        }

        inline string devolverPalabra() const {
            return palabra;
        }

        friend istream& operator >> (istream &is, Palabra &palabra);
};


class SopaLetras {
    private:
        char **sopa;
        int nFilas;
        int nColumnas;
    
    public:
        SopaLetras() {
            this->nColumnas = 0;
            this->nFilas = 0;
            this->sopa = 0;
        }

        ~SopaLetras() {
            for (int f = 0; f < this->nFilas; f++) {
                delete [] *(this->sopa + f);
            }
            delete [] this->sopa;
        }

        void inicializarSopa() {
            this->sopa = 0;
            this->nColumnas = 0;
            this->nFilas = 0;

            cout << "\nIntroduzca la sopa de letras(un 0 para terminar):\n";
            string fila;
            getline(cin, fila);
            this->nColumnas = fila.length();       //Igualamos el número de columnas a la longitud de la fila
            while (fila != "0") {       //Cuando leamos un 0, paramos de introducir
                char **aux = this->sopa;
                this->sopa = new char* [this->nFilas + 1];

                for (int f = 0; f <= this->nFilas; f++) {
                    *(this->sopa + f) = new char [nColumnas];
                }

                for (int f = 0; f < this->nFilas; f++) {
                    for (int c = 0; c < this->nColumnas; c++) {
                        *(*(this->sopa + f) + c) = *(*(aux + f ) + c);
                    }
                }
                
                for (int f = 0; f < this->nFilas; f++) delete [] *(aux + f);       //Borramos puntero auxiliar
                delete [] aux;
                
                for (int c = 0; c < this->nColumnas; c++) *(*(this->sopa + this->nFilas) + c) = fila[c];     //Introducimos la siguiente fila

                this->nFilas++;    //Aumentamos el número de filas

                getline(cin, fila);     //Leemos la siguiente fila

            }
        }

        friend ostream& operator << (ostream &o, const SopaLetras &sopa);

        bool comprobarPalabra(Palabra &buscar) {
            bool coincide, buscando = true;


            for (int i = 0; i < nFilas - buscar.longitud && buscando; i++) {                              //Comprobación diagonal
                for (int j = 0; j < nColumnas - buscar.longitud && buscando; j++) {       //Solo buscamos hasta cierta columna y fila, pues a partir de ahí la palabra no cabría en la sopa
                    coincide = true;
                    if (buscar.palabra[0] == *(*(this->sopa + i) + j)) {
                        for (int k = 0; k < buscar.longitud && coincide; k++) {
                            if (buscar.palabra[k] != *(*(this->sopa + i + k) + j + k)) coincide = false;
                        }
                        if (coincide){
                            buscando = false;
                            buscar.fila = i + 1;
                            buscar.columna = j + 1;
                            buscar.posicion = "diagonal";
                        }
                    }
                }
            }

            for (int i = 0; i < nFilas && buscando; i++) {                              //Comprobación horizontal
                for (int j = 0; j < nColumnas - buscar.longitud && buscando; j++) {       //Solo buscamos hasta cierta columna, pues a partir de ahí la palabra no cabría en la *(*this->sopa + i) + j)
                    coincide = true;
                    if (buscar.palabra[0] == *(*(this->sopa + i) + j)) {
                        for (int k = 0; k < buscar.longitud && coincide; k++) {
                            if (buscar.palabra[k] != *(*(this->sopa + i) + j + k)) coincide = false;
                        }
                        if (coincide){
                            buscando = false;
                            buscar.fila = i + 1;
                            buscar.columna = j + 1;
                            buscar.posicion = "horizontal";
                        }
                    }
                }
            }

            for (int i = 0; i < nFilas - buscar.longitud && buscando; i++) {                              //Comprobación vertical
                for (int j = 0; j < nColumnas && buscando; j++) {       //Solo buscamos hasta cierta fila, pues a partir de ahí la palabra no cabría en la *(*this->sopa + i) + j)
                    coincide = true;
                    if (buscar.palabra[0] == *(*(this->sopa + i) + j)) {
                        for (int k = 0; k < buscar.longitud && coincide; k++) {
                            if (buscar.palabra[k] != *(*(this->sopa + i + k) + j)) coincide = false;
                        }
                        if (coincide){
                            buscando = false;
                            buscar.fila = i + 1;
                            buscar.columna = j + 1;
                            buscar.posicion = "vertical";
                        }
                    }
                }
            }

            return !buscando;
        }

};



istream& operator >> (istream &is, Palabra &palabra) {
    cout << "\nIntroduzca la palabra:\n";
    is >> palabra.palabra;
    palabra.longitud = palabra.palabra.length();
    for (int i = 0; i < palabra.longitud; i++) if (palabra.palabra[i]> 'Z') palabra.palabra[i] -= 32;
    palabra.fila = 0;
    palabra.columna = 0;
    palabra.posicion = "0";
    is.ignore();
    return is;

}

ostream& operator << (ostream &o, const SopaLetras &sopa) {
    for (int f = 0; f < sopa.nFilas; f++) {
        o << endl;
        for (int c = 0; c < sopa.nColumnas; c++) {
            o << *(*(sopa.sopa + f) + c) << " ";
        }
    }
    o << endl;
    return o;
}


int main() {
    bool continuar = true;
    string opcion;
    SopaLetras sopa;
    sopa.inicializarSopa();

    cout << sopa;




    do {
        Palabra Palabra;
        cin >> Palabra;


        if (sopa.comprobarPalabra(Palabra)) {
            cout << "\nLa palabra " << Palabra.devolverPalabra() <<  " ha sido encontrada.\nSe ubica en la fila " << Palabra.devolverFila() << " y en la columna " << Palabra.devolverColumna();
            cout << " en posición " << Palabra.devolverPosicion();
        } else cout << "\nNo se encontró la palabra " << Palabra.devolverPalabra();

        cout << "\nDesea introducir una nueva palabra? (si/no) :\n";       //Preguntamos si quiere introducir una palabra nueva para buscar
        getline(cin, opcion);

        continuar = (opcion == "no")?false:true;        //Si escribe "no", salimos, si no seguimos buscando

    } while (continuar);

    cout << "\nFinalizando...\n\n";
}