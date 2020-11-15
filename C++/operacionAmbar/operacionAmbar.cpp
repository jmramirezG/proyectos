#include <iostream>
#include <fstream>

using namespace std;

const string archivo = "/mnt/c3096fe8-ceba-4048-b201-af08720979e4/Beneficios/OperacionAmbar";

class Beneficios {
    private:
        double beneficios;
        const double razonPrepo = 0.33333333333333333333334;
        const double razonMarco = 0.66666666666666666666667;

    public:

        Beneficios();

        void menu();

        void addBeneficio(double cantidad);

        double partePrepo() const;

        double parteMarco() const;

        friend ostream & operator<<(ostream &o, const Beneficios & beneficios);

        void guardarBeneficios(const string nombreArchivo);

};

Beneficios::Beneficios() {
    system("cp /mnt/c3096fe8-ceba-4048-b201-af08720979e4/Beneficios/OperacionAmbar /mnt/c3096fe8-ceba-4048-b201-af08720979e4/Beneficios/OperacionAmbarSeguro");
    ifstream txt;
    txt.open(archivo);
    txt >> beneficios;
    txt.close();
    cout << endl;
    system("rm -v /mnt/c3096fe8-ceba-4048-b201-af08720979e4/Beneficios/OperacionAmbar");
}

void Beneficios::menu() {
    bool fin = false;
    while (!fin) {
        cout << "\nElija la opción que prefiera:\n1.\tAñadir un beneficio.\n2.\tEnunciar dineros.\t\n3.\tSalir.\n";
        int opcion;
        cin >> opcion;
        if (opcion == 3) {
            cin.ignore(100000, '\n');
            guardarBeneficios(archivo);
            fin = true;
        } else if (opcion == 1) {
            double cant;
            cin.ignore(100000, '\n');
            cout << "\nIntroduzca la cantidad a añadir: ";
            cin >> cant;
            addBeneficio(cant);
        
        } else if (opcion == 2) {
            cout << "Llevamos obtenidos un total de " << beneficios << ".\nDe los cuales " << partePrepo();
            cout << " pertenecen a Prepo y " << parteMarco() << " pertenecen a Marco Aurelio.\n\n";
        }
        else {
            cin.ignore(100000, '\n');
            cout << "\nOpción incorrecta, introduzca de nuevo\n";
            opcion = 0;
        }
        if (!fin)
            cin.ignore(100000, '\n');
    }
}

void Beneficios::addBeneficio(double cantidad){
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
    o << " pertenecen a Prepo y " << beneficios.parteMarco() << " pertenecen a Marco Aurelio.\n\n";
    return o;
}

void Beneficios::guardarBeneficios(const string nombreArchivo) {
    ofstream txt;
    system("touch /mnt/c3096fe8-ceba-4048-b201-af08720979e4/Beneficios/OperacionAmbar");
    txt.open(nombreArchivo);
    txt << beneficios;
    txt.close();
}

int main() {
    Beneficios beneficios;
    beneficios.menu();
    cout << beneficios;
}
