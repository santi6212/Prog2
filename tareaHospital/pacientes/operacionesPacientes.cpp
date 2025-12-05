#include "operacionesPacientes.hpp"
#include <iostream>
#include <cstring>

using namespace std;

namespace OperacionesPacientes {

// ================= REGISTRAR PACIENTE =================

void registrarPaciente(Hospital& hospital) {
    cout << "\n=== REGISTRAR NUEVO PACIENTE ===\n";

    string nombre, apellido, cedula;
    int edad;
    char sexo;

    cout << "Nombre: ";
    cin >> nombre;

    cout << "Apellido: ";
    cin >> apellido;

    cout << "Cedula: ";
    cin >> cedula;

    cout << "Edad: ";
    cin >> edad;

    cout << "Sexo (M/F): ";
    cin >> sexo;

    int nuevoID = hospital.generarIdPaciente();

    Paciente p(nuevoID, nombre.c_str(), apellido.c_str(), cedula.c_str());
    p.setEdad(edad);
    p.setSexo(sexo);

    if (!p.validarDatos()) {
        cout << "Error: Datos inválidos. Registro cancelado.\n";
        return;
    }

    GestorArchivos::guardarPaciente(p);

    cout << "Paciente registrado con ID " << nuevoID << endl;
}


// ================= BUSCAR POR ID =================

bool buscarPacientePorID(int id, Paciente& resultado) {
    vector<Paciente> lista = GestorArchivos::leerTodosPacientes();

    for (auto& p : lista) {
        if (p.getId() == id) {
            resultado = p;
            return true;
        }
    }
    return false;
}


// ================= BUSCAR POR CÉDULA =================

bool buscarPacientePorCedula(const char* cedula, Paciente& resultado) {
    vector<Paciente> lista = GestorArchivos::leerTodosPacientes();

    for (auto& p : lista) {
        if (strcmp(p.getCedula(), cedula) == 0) {
            resultado = p;
            return true;
        }
    }
    return false;
}


// ================= MODIFICAR PACIENTE =================

void modificarPaciente() {
    cout << "\n=== MODIFICAR PACIENTE ===\n";

    int id;
    cout << "Ingrese ID del paciente: ";
    cin >> id;

    vector<Paciente> lista = GestorArchivos::leerTodosPacientes();

    int indice = -1;
    for (int i = 0; i < lista.size(); i++) {
        if (lista[i].getId() == id) {
            indice = i;
            break;
        }
    }

    if (indice == -1) {
        cout << "Paciente no encontrado.\n";
        return;
    }

    Paciente& p = lista[indice];

    cout << "Modificando a: " << p.getNombre() << " " << p.getApellido() << endl;

    string nuevo;
    int nuevaEdad;
    char nuevoSexo;

    cout << "Nuevo nombre (actual: " << p.getNombre() << "): ";
    cin >> nuevo;
    p.setNombre(nuevo.c_str());

    cout << "Nuevo apellido (actual: " << p.getApellido() << "): ";
    cin >> nuevo;
    p.setApellido(nuevo.c_str());

    cout << "Nueva edad (actual: " << p.getEdad() << "): ";
    cin >> nuevaEdad;
    p.setEdad(nuevaEdad);

    cout << "Nuevo sexo (M/F) (actual: " << p.getSexo() << "): ";
    cin >> nuevoSexo;
    p.setSexo(nuevoSexo);

    // ? Guardar cambios correctamente
    GestorArchivos::sobrescribirPacientes(lista);

    cout << "Paciente actualizado correctamente.\n";
}


// ================= ELIMINAR PACIENTE =================

void eliminarPaciente() {
    cout << "\n=== ELIMINAR PACIENTE ===\n";

    int id;
    cout << "Ingrese ID del paciente: ";
    cin >> id;

    vector<Paciente> lista = GestorArchivos::leerTodosPacientes();

    int indice = -1;
    for (int i = 0; i < lista.size(); i++) {
        if (lista[i].getId() == id) {
            indice = i;
            break;
        }
    }

    if (indice == -1) {
        cout << "Paciente no encontrado.\n";
        return;
    }

    Paciente& p = lista[indice];
    p.setActivo(false);

    GestorArchivos::sobrescribirPacientes(lista);

    cout << "Paciente marcado como inactivo.\n";
}


// ================= LISTAR TODOS =================

void listarTodos() {
    cout << "\n=== LISTA DE PACIENTES ===\n";

    vector<Paciente> lista = GestorArchivos::leerTodosPacientes();

    if (lista.empty()) {
        cout << "No hay pacientes registrados.\n";
        return;
    }

    for (auto& p : lista) {
        p.mostrarInformacionBasica();
    }
}


// ================= MOSTRAR HISTORIAL =================

void mostrarHistorialPaciente() {
    cout << "\n=== HISTORIAL MÉDICO ===\n";

    int id;
    cout << "Ingrese ID del paciente: ";
    cin >> id;

    Paciente p;
    if (!buscarPacientePorID(id, p)) {
        cout << "Paciente no encontrado.\n";
        return;
    }

    if (!p.tieneHistorial()) {
        cout << "Este paciente no tiene historial médico.\n";
        return;
    }

    cout << "\nHistorial del paciente " << p.getNombre() << " " << p.getApellido() << endl;

    for (auto& consulta : p.getHistorial()) {
        consulta.mostrarInformacion();
        cout << "-----------------------------\n";
    }
}

} // namespace
