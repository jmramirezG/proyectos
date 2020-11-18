#include <iostream>
#include <fstream>

using namespace std;

const string archivo = "/mnt/c3096fe8-ceba-4048-b201-af08720979e4/Beneficios/OperacionAmbar";
const string contador = "/mnt/c3096fe8-ceba-4048-b201-af08720979e4/Beneficios/contador";

class Beneficios {
    private:
        double beneficios;
        int operaciones;
        const double razonPrepo = 1.0/3.0;
        const double razonMarco = 2.0/3.0;

    public:

        Beneficios();

        void menu();

        void addBeneficio(double cantidad);

        double partePrepo() const;

        double parteMarco() const;

        friend ostream & operator<<(ostream &o, const Beneficios & beneficios);

        void guardarBeneficios();

};

Beneficios::Beneficios() {
    system("cp /mnt/c3096fe8-ceba-4048-b201-af08720979e4/Beneficios/OperacionAmbar /mnt/c3096fe8-ceba-4048-b201-af08720979e4/Beneficios/OperacionAmbarSeguro");
    ifstream txt;
    ifstream cont;
    cont.open(contador);
    txt.open(archivo);
    txt >> beneficios;
    cont >> operaciones;
    txt.close();
    cont.close();
}

void Beneficios::menu() {
    bool fin = false;
    while (!fin) {

        cout << "\nElija la opción que prefiera:\n1.\tAñadir un beneficio.\n2.\tEnunciar dineros.\t\n3.\tSalir.\n4.\tBorrar beneficios.\n";
        int opcion;
        cin >> opcion;

        switch (opcion) {
            case 1:
                double cant;
                cin.ignore(100000, '\n');
                cout << "\nIntroduzca la cantidad a añadir: ";
                cin >> cant;
                addBeneficio(cant);
                guardarBeneficios();
                break;

            case 2:
                cout << "\n\nLlevamos obtenidos un total de " << beneficios << ".\n" << partePrepo();
                cout << " pertenecen a Prepo y " << parteMarco() << " pertenecen a Marco Aurelio.";
                if (beneficios != 0)
                    cout << "\nLa media de pagos es de " << beneficios/operaciones << " euros por persona.\n\n";
                break;

            case 3:
                cin.ignore(100000, '\n');
                guardarBeneficios();
                fin = true;
                break;

            case 4:
                cout << "\n\nESTÁ SEGURO DE QUE DESEA BORRAR LOS BENEFICIOS? (Y/N)\n";
                char respuesta;
                cin >> respuesta;
                respuesta = toupper(respuesta);
                if (respuesta == 'Y') {
                    system("clear");
                    cout << "------------------------------Beneficios borrados-------------------------------";
                    beneficios = 0;
                    operaciones = 0;
                } else
                    cout << "\nBeneficios no borrados\n";
                break;

            default:
                cin.ignore(100000, '\n');
                cout << "\nOpción incorrecta, introduzca de nuevo\n";
                opcion = 0;
                break;
        }

        if (!fin)
            cin.ignore(100000, '\n');
    }
}

void Beneficios::addBeneficio(double cantidad){
    operaciones++;
    beneficios += cantidad;
}

double Beneficios::partePrepo() const {
    return beneficios * razonPrepo;
}

double Beneficios::parteMarco() const {
    return beneficios * razonMarco;
}

ostream & operator<<(ostream & o, const Beneficios & beneficios) {
    o << "Llevamos obtenidos un total de " << beneficios.beneficios << ".\nDe los cuales " << beneficios.partePrepo();
    o << " pertenecen a Prepo y " << beneficios.parteMarco() << " pertenecen a Marco Aurelio.";
    if (beneficios.beneficios != 0)
        o << "\nLa media de pagos es de " << beneficios.beneficios/beneficios.operaciones << " euros por persona.\n\n";
    return o;
}

void Beneficios::guardarBeneficios() {
    ofstream cont;
    ofstream txt;
    system("rm /mnt/c3096fe8-ceba-4048-b201-af08720979e4/Beneficios/OperacionAmbar");
    system("touch /mnt/c3096fe8-ceba-4048-b201-af08720979e4/Beneficios/OperacionAmbar");
    system("rm /mnt/c3096fe8-ceba-4048-b201-af08720979e4/Beneficios/contador");
    system("touch /mnt/c3096fe8-ceba-4048-b201-af08720979e4/Beneficios/contador");
    txt.open(archivo);
    cont.open(contador);
    cont << operaciones;
    txt << beneficios;
    txt.close();
    cont.close();
}

int main() {
    Beneficios beneficios;
    beneficios.menu();
    cout << beneficios;
}
