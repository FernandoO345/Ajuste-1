#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Particion {
public:
    int id;
    int tamano;
    bool ocupada;
    string nombreProceso;

    Particion(int _id, int _tamano) : id(_id), tamano(_tamano), ocupada(false), nombreProceso("") {}
};

class Proceso {
public:
    string nombre;
    int tamano;

    Proceso(const string& _nombre, int _tamano) : nombre(_nombre), tamano(_tamano) {}
};

int calcularMemoriaSobrante(const vector<Particion>& particiones) {
    int memoriaSobrante = 0;
    for (size_t i = 0; i < particiones.size(); i++) {
        if (!particiones[i].ocupada) {
            memoriaSobrante += particiones[i].tamano;
        }
    }
    return memoriaSobrante;
}

int main() {
    int memoriaTotal = 2000;

    vector<Particion> particiones;
    vector<Proceso> procesos;

    int numParticiones, numProcesos;

    cout << "Ingrese la cantidad de particiones: ";
    cin >> numParticiones;

    cout << "Ingrese la cantidad de procesos: ";
    cin >> numProcesos;

    for (int i = 0; i < numParticiones; i++) {
        int tamano;
        cout << "Ingrese el tamano de la particion " << i + 1 << ": ";
        cin >> tamano;
        particiones.push_back(Particion(i + 1, tamano));
    }

    
    Proceso sistema("Sistema", 100);
    procesos.push_back(sistema);

    for (int i = 0; i < numProcesos; i++) {
        string nombre;
        int tamano;
        cout << "Ingrese el nombre del proceso " << i + 1 << ": ";
        cin >> nombre;
        cout << "Ingrese el tamaño del proceso " << i + 1 << ": ";
        cin >> tamano;
        procesos.push_back(Proceso(nombre, tamano));
    }

    int memoriaOcupadaTotal = 0; 
    
    for (int i = 0; i < procesos.size(); i++) {
        Proceso proceso = procesos[i];
        bool asignado = false;

        for (int j = 0; j < particiones.size(); j++) {
            Particion& particion = particiones[j];
            if (!particion.ocupada && particion.tamano >= proceso.tamano) {
                particion.ocupada = true;
                particion.nombreProceso = proceso.nombre;
                asignado = true;
                cout << proceso.nombre << " asignado a la particion " << particion.id << endl;
                memoriaOcupadaTotal += proceso.tamano; 
                break;
            }
        }

        if (!asignado) {
            cout << proceso.nombre << " no fue asignado a la memoria" << endl;
        }
    }

    int MS;
    int memoriaSobrante = calcularMemoriaSobrante(particiones);
     
    MS = memoriaTotal - memoriaOcupadaTotal;
    cout << "Memoria sobrante: " << MS << endl;

    return 0;
}


