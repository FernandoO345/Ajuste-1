#include <iostream>
#include <string>
#include <limits>

using namespace std;

int findBestFitPartition(int processSize, int *memory, int *PARTITION_SIZES, int NUM_PARTITIONS);
bool areAllPartitionsOccupied(int *memory, int NUM_PARTITIONS);

int main() {
    int NUM_PARTITIONS;
    int *PARTITION_SIZES;
    int SYSTEM_PARTITION_SIZE;
    int TOTAL_MEMORY;
    int *memory;
    string *process_names;

    cout << "Ingrese la cantidad de particiones: ";
    cin >> NUM_PARTITIONS;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    PARTITION_SIZES = new int[NUM_PARTITIONS];
    for (int i = 0; i < NUM_PARTITIONS; i++) {
        cout << "Ingrese el tamano para la particion " << (i + 1) << ": ";
        cin >> PARTITION_SIZES[i];
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    cout << "Ingrese el tamano para la partición del sistema operativo: ";
    cin >> SYSTEM_PARTITION_SIZE;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    TOTAL_MEMORY = 0;
    for (int i = 0; i < NUM_PARTITIONS; i++) {
        TOTAL_MEMORY += PARTITION_SIZES[i];
    }
    TOTAL_MEMORY += SYSTEM_PARTITION_SIZE;

    memory = new int[NUM_PARTITIONS + 1];
    for (int i = 0; i < NUM_PARTITIONS + 1; i++) {
        memory[i] = -1;
    }

    process_names = new string[NUM_PARTITIONS + 1];
    for (int i = 0; i < NUM_PARTITIONS + 1; i++) {
        process_names[i] = "";
    }

    while (true) {
        cout << "Estado de la memoria: " << TOTAL_MEMORY << endl;
        cout << "Partición del sistema: Sistema Operativo (" << SYSTEM_PARTITION_SIZE << " MB)" << endl;

        for (int i = 0; i < NUM_PARTITIONS; i++) {
            if (memory[i] == -1) {
                cout << "Particion " << PARTITION_SIZES[i] << ": Libre" << endl;
            } else {
                cout << "Particion " << PARTITION_SIZES[i] << ": Proceso '" << process_names[i] << "' (" << memory[i] << " MB)" << endl;
            }
        }

        cout << "\n1. Asignar proceso a particion (Siguiente ajuste)" << endl;
        cout << "2. Liberar particion" << endl;
        cout << "3. Salir" << endl;

        int choice;
        cin >> choice;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        if (choice == 1) {
            cout << "Ingrese el tamano del proceso: ";
            int processSize;
            cin >> processSize;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            cout << "Ingrese el nombre del proceso: ";
            string processName;
            getline(cin, processName);

            if (processSize <= TOTAL_MEMORY) {
                int best_fit_index = findBestFitPartition(processSize, memory, PARTITION_SIZES, NUM_PARTITIONS);

                if (best_fit_index != -1) {
                    memory[best_fit_index] = processSize;
                    process_names[best_fit_index] = processName;
                    cout << "Proceso '" << processName << "' asignado a la particion " << best_fit_index << ": " << memory[best_fit_index] << " MB" << endl;
                    TOTAL_MEMORY -= processSize;
                } else {
                    cout << "No se pudo asignar el proceso a ninguna particion." << endl;
                }
            } else {
                cout << "El tamano del proceso excede la memoria total." << endl;
            }
        } else if (choice == 2) {
            cout << "Ingrese el indice de la particion a liberar: ";
            int partitionIndex;
            cin >> partitionIndex;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            if (partitionIndex >= 0 && partitionIndex < NUM_PARTITIONS && memory[partitionIndex] != -1) {
                process_names[partitionIndex] = "";
                TOTAL_MEMORY += memory[partitionIndex];
                memory[partitionIndex] = -1;
                cout << "Particion liberada." << endl;
            } else {
                cout << "Indice de particion invalido o la particion ya esta libre." << endl;
            }
        } else if (choice == 3) {
            break;
        } else {
            cout << "Opcion invalida." << endl;
        }

        // Crear una nueva partición con el sobrante acumulado si todas las particiones están ocupadas
        if (areAllPartitionsOccupied(memory, NUM_PARTITIONS)) {
            int accumulated_memory = 0;
            for (int i = 0; i < NUM_PARTITIONS + 1; i++) {
                if (memory[i] != -1) {
                    accumulated_memory += memory[i];
                }
            }

            int new_partition_size = accumulated_memory;
            if (new_partition_size > 0) {
                int *new_partition_sizes = new int[NUM_PARTITIONS + 1];
                for (int i = 0; i < NUM_PARTITIONS; i++) {
                    new_partition_sizes[i] = PARTITION_SIZES[i];
                }
                new_partition_sizes[NUM_PARTITIONS] = new_partition_size;
                delete[] PARTITION_SIZES;
                PARTITION_SIZES = new_partition_sizes;

                int *new_memory = new int[NUM_PARTITIONS + 2];
                for (int i = 0; i < NUM_PARTITIONS + 1; i++) {
                    new_memory[i] = memory[i];
                }
                new_memory[NUM_PARTITIONS + 1] = -1;
                delete[] memory;
                memory = new_memory;

                string *new_process_names = new string[NUM_PARTITIONS + 2];
                for (int i = 0; i < NUM_PARTITIONS + 1; i++) {
                    new_process_names[i] = process_names[i];
                }
                new_process_names[NUM_PARTITIONS + 1] = "";
                delete[] process_names;
                process_names = new_process_names;

                NUM_PARTITIONS++;
                cout << "Se creó una nueva particion de tamano " << new_partition_size << " MB." << endl;
                TOTAL_MEMORY += new_partition_size;
            }
        }
    }

    cout << "Saliendo del programa." << endl;

    delete[] PARTITION_SIZES;
    delete[] memory;
    delete[] process_names;

    return 0;
}

int findBestFitPartition(int processSize, int *memory, int *PARTITION_SIZES, int NUM_PARTITIONS) {
    int best_fit_index = -1;
    int smallest_free_space = numeric_limits<int>::max();

    for (int i = 0; i < NUM_PARTITIONS; i++) {
        if (memory[i] == -1 && PARTITION_SIZES[i] >= processSize) {
            int free_space = PARTITION_SIZES[i] - processSize;
            if (free_space < smallest_free_space) {
                best_fit_index = i;
                smallest_free_space = free_space;
            }
        }
    }

    return best_fit_index;
}

bool areAllPartitionsOccupied(int *memory, int NUM_PARTITIONS) {
    for (int i = 0; i < NUM_PARTITIONS + 1; i++) {
        if (memory[i] == -1) {
            return false;
        }
    }
    return true;
}
