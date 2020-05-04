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
        Palabra() {                 //Constructor por defecto de la clase
            fila = 0;
            columna = 0;
            longitud = 0;
            palabra = "0";
            posicion = "0";
        }

        Palabra(string entrada) {       //Creamos el objeto a partir de una palabra de entrada
            this->longitud = entrada.length();
            for (int i = 0; i < entrada.length(); i++) if (entrada[i]> 'Z') entrada[i] -= 32;
            this->palabra = entrada;
            fila = 0;
            columna = 0;
            posicion = "0";
        }

        friend class SopaLetras;        //Permitimos que la clase SopaLetras pueda acceder a los componentes privados de la clase para facilitar los cálculos

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

        friend istream& operator >> (istream &is, Palabra &palabra);            //Sobrecarga del operador >>
};



//----------------------------------------------------------------------CLASE SOPA DE LETRAS----------------------------------------------------------------------------


class SopaLetras {
    private:
        char **sopa;        //Matriz de char para la sopa de letras
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
                for (int i = 0; i < fila.length(); i++) if (fila[i]> 'Z') fila[i] -= 32;    //Convertimos las letras en mayúsculas

                char **aux = this->sopa;        //Creamos un auxiliar
                this->sopa = new char* [this->nFilas + 1];  //Añadimos una nueva fila

                for (int f = 0; f <= this->nFilas; f++) {
                    *(this->sopa + f) = new char [nColumnas];   //Creamos las columnas en cada fila
                }

                for (int f = 0; f < this->nFilas; f++) {            //Copiamos los valores que ya teníamos en el auxiliar
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

        friend ostream& operator << (ostream &o, const SopaLetras &sopa);       //Sobrecarga del operador << para mostrar la sopa de letras

        bool comprobarPalabra(Palabra &buscar) {            //Método para comprobar si una palabra x se encuentra en la sopa de letras
            bool coincide, buscando = true;

            //-------------------------------------------------------Comprobación diagonal-------------------------------------------------
            for (int i = 0; i < nFilas - buscar.longitud + 1 && buscando; i++) {
                for (int j = 0; j < nColumnas - buscar.longitud + 1 && buscando; j++) { //Solo buscamos hasta cierta columna y fila, pues a partir de ahí la palabra no cabría en la sopa
                    coincide = true;

                    if (buscar.palabra[0] == *(*(this->sopa + i) + j)) {

                        for (int k = 0; k < buscar.longitud && coincide; k++) {
                            if (buscar.palabra[k] != *(*(this->sopa + i + k) + j + k)) coincide = false;
                        }
                        
                        if (coincide){      //Si coincide completamente dejamos de buscar
                            buscando = false;
                            buscar.fila = i + 1;
                            buscar.columna = j + 1;
                            buscar.posicion = "diagonal";
                        }
                    }
                }
            }

            //-------------------------------------------------------Comprobación horizontal hacia la dcha-------------------------------------------------
            for (int i = 0; i < nFilas && buscando; i++) {
                for (int j = 0; j < nColumnas - buscar.longitud + 1 && buscando; j++) { //Solo buscamos hasta cierta columna, pues a partir de ahí la palabra no cabría en la *(*this->sopa + i) + j)
                    coincide = true;

                    if (buscar.palabra[0] == *(*(this->sopa + i) + j)) {

                        for (int k = 0; k < buscar.longitud && coincide; k++) {
                            if (buscar.palabra[k] != *(*(this->sopa + i) + j + k)) coincide = false;
                        }

                        if (coincide){
                            buscando = false;
                            buscar.fila = i + 1;
                            buscar.columna = j + 1;
                            buscar.posicion = "horizontal hacia la derecha";
                        }
                    }
                }
            }

            //-------------------------------------------------------Comprobación horizontal hacia la izq-------------------------------------------------
            for (int i = 0; i < nFilas && buscando; i++) {
                for (int j = buscar.longitud - 1; j < nColumnas && buscando; j++) { //Solo buscamos hasta cierta columna, pues a partir de ahí la palabra no cabría en la *(*this->sopa + i) + j)
                    coincide = true;

                    if (buscar.palabra[0] == *(*(this->sopa + i) + j)) {

                        for (int k = 0; k < buscar.longitud && coincide; k++) {
                            if (buscar.palabra[k] != *(*(this->sopa + i) + j - k)) coincide = false;
                        }

                        if (coincide){
                            buscando = false;
                            buscar.fila = i + 1;
                            buscar.columna = j + 1;
                            buscar.posicion = "horizontal hacia la izquierda";
                        }
                    }
                }
            }

            //-------------------------------------------------------Comprobación vertical hacia abajo-------------------------------------------------
            for (int i = 0; i < nFilas - buscar.longitud + 1 && buscando; i++) {
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
                            buscar.posicion = "vertical hacia abajo";
                        }
                    }
                }
            }

            //-------------------------------------------------------Comprobación vertical hacia arriba-------------------------------------------------
            for (int i = buscar.longitud - 1; i < nFilas && buscando; i++) {
                for (int j = 0; j < nColumnas && buscando; j++) {       //Solo buscamos hasta cierta fila, pues a partir de ahí la palabra no cabría en la *(*this->sopa + i) + j)
                    coincide = true;

                    if (buscar.palabra[0] == *(*(this->sopa + i) + j)) {

                        for (int k = 0; k < buscar.longitud && coincide; k++) {
                            if (buscar.palabra[k] != *(*(this->sopa + i - k) + j)) coincide = false;
                        }

                        if (coincide){
                            buscando = false;
                            buscar.fila = i + 1;
                            buscar.columna = j + 1;
                            buscar.posicion = "vertical hacia arriba";
                        }
                    }
                }
            }

            return !buscando;
        }

};

//------------------------------------------------------------------------SOBRECARGA DE OPERADORES--------------------------------------------------------

istream& operator >> (istream &is, Palabra &palabra) {      //Operador >> par la clase Palabra
    cout << "\nIntroduzca la palabra:\n";
    is >> palabra.palabra;  //Leemos la palabra a buscar

    palabra.longitud = palabra.palabra.length();

    for (int i = 0; i < palabra.longitud; i++) if (palabra.palabra[i]> 'Z') palabra.palabra[i] -= 32;   //Pasamos a mayúscula

    palabra.fila = 0;       //Inicializamos el resto de variables como 0
    palabra.columna = 0;
    palabra.posicion = "0";

    is.ignore();    //Quitamos el salto de línea

    return is;  //Devolvemos el istream
}

ostream& operator << (ostream &o, const SopaLetras &sopa) {     //Operador << para la Sopa de Letras
    for (int f = 0; f < sopa.nFilas; f++) {     //Recorremos cada fila
        o << endl;
        for (int c = 0; c < sopa.nColumnas; c++) {
            o << *(*(sopa.sopa + f) + c) << " ";    //Decimos el elemento y añadimos un espacio
        }
    }
    o << endl;

    return o;
}

//-------------------------------------------------------------------------------INICIO DEL MAIN----------------------------------------------------------------

int main() {
    bool continuar;
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

        continuar = (opcion == "no")?false:true;

    } while (continuar);

    cout << "\nFinalizando...\n\n";
}