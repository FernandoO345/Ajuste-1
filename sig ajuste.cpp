#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Particion {
public:
    int id;
    int tamParti;
    bool ocupada;
    string nombreProceso;

    Particion(int _id, int _tamParti) : id(_id), tamParti(_tamParti), ocupada(false), nombreProceso("") {}
};

class Proceso {
public:
    string nombre;
    int tamProce;

    Proceso(const string& _nombre, int _tamProce) : nombre(_nombre), tamProce(_tamProce) {}
};

int main() {
    cout << "Ingrese la memoria total: ";
    int memoriaTotal;
    cin >> memoriaTotal;

   

    int espacioMemoria = memoriaTotal;

    int espacios_sin_asignar = 0;

    cout << "Ingrese la cantidad de particiones que habra: " << endl;
    int numParti;
    cin >> numParti;

    vector<Particion> particiones;

    for (int i = 0; i < numParti; i++) {
        cout << "Ingrese el tamano de la particion " << (i + 1) << ": ";
        int tamParti;
        cin >> tamParti;

        particiones.push_back(Particion(i + 1, tamParti));
    }

    cout << "Ingrese la cantidad de procesos que habra: ";
    int numProce;
    cin >> numProce;

    vector<Proceso> procesos;

    procesos.push_back(Proceso("Sistema Operativo", 100));

    for (int i = 0; i < numProce; i++) {
        cin.ignore();
        cout << "Ingrese el nombre del proceso " << (i + 1) << ": ";
        string nombreProceso;
        getline(cin, nombreProceso);

        cout << "Ingrese el tamano del proceso: ";
        int tamProce;
        cin >> tamProce;

        procesos.push_back(Proceso(nombreProceso, tamProce));
    }

    cout << "----------------------------------------" << endl;

    int ultima_asignacion = 0;

    for (int i = 0; i < procesos.size(); i++) {
        Proceso proceso = procesos[i];
        bool asignado = false;

        for (int j = ultima_asignacion; j < particiones.size(); j++) {
            Particion& particion = particiones[j];
            if (!particion.ocupada && particion.tamParti >= proceso.tamProce) {
                particion.ocupada = true;
                particion.nombreProceso = proceso.nombre;
                asignado = true;

                espacioMemoria -= proceso.tamProce;

                cout << proceso.nombre << " asignado a la Particion " << particion.id << endl;

                ultima_asignacion = j + 1;
                break;
            }
        }

        if (!asignado) {
            for (int j = 0; j < particiones.size(); j++) {
                Particion& particion = particiones[j];

                if (!particion.ocupada && particion.tamParti >= proceso.tamProce) {
                    particion.ocupada = true;
                    particion.nombreProceso = proceso.nombre;
                    asignado = true;

                    espacioMemoria -= proceso.tamProce;

                    cout << proceso.nombre << " asignado a la Particion " << particion.id << endl;
                    break;
                }
            }
        }

        if (!asignado) {
            cout << proceso.nombre << " No fuiste asignado a memoria" << endl;
            espacios_sin_asignar++;
        }
    }

    if (espacioMemoria > 0) {
        Particion nuevaParticion(particiones.size() + 1, espacioMemoria);
        particiones.push_back(nuevaParticion);
        cout << "Se creo una nueva particion con espacio de: " << espacioMemoria << endl;
    }

    cout << "Los espacios libres en memoria son de: " << espacios_sin_asignar << endl;
    cout << endl;
    cout << "Memoria total disponible: " << memoriaTotal << endl;
    cout << "La memoria disponible final es de: " << espacioMemoria << endl;

    return 0;
}


