#include "operacionesDoctores.hpp"
#include <iostream>
#include <cstring>

using namespace std;

namespace OperacionesDoctores {

// ================= REGISTRAR DOCTOR =================

void registrarDoctor(Hospital& hospital) {
    cout << "\n=== REGISTRAR NUEVO DOCTOR ===\n";

    string nombre, apellido, cedula, especialidad;
    int experiencia;
    float costo;

    cout << "Nombre: ";
    cin >> nombre;

    cout << "Apellido: ";
    cin >> apellido;

    cout << "Cedula: ";
    cin >> cedula;

    cout << "Especialidad: ";
    cin >> especialidad;

    cout << "Años de experiencia: ";
    cin >> experiencia;

    cout << "Costo de consulta: ";
    cin >> costo;

    int nuevoID = hospital.generarIdDoctor();

    Doctor d(nuevoID, nombre.c_str(), apellido.c_str(), cedula.c_str(),
             especialidad.c_str(), experiencia, costo);

    if (!d.validarDatos()) {
        cout << "Error: Datos inválidos. Registro cancelado.\n";
        return;
    }

    GestorArchivos::guardarDoctor(d);

    cout << "Doctor registrado con ID " << nuevoID << endl;
}


// ================= BUSCAR POR ID =================

bool buscarDoctorPorID(int id, Doctor& resultado) {
    vector<Doctor> lista = GestorArchivos::leerTodosDoctores();

    for (auto& d : lista) {
        if (d.getId() == id) {
            resultado = d;
            return true;
        }
    }
    return false;
}


// ================= BUSCAR POR CÉDULA =================

bool buscarDoctorPorCedula(const char* cedula, Doctor& resultado) {
    vector<Doctor> lista = GestorArchivos::leerTodosDoctores();

    for (auto& d : lista) {
        if (strcmp(d.getCedula(), cedula) == 0) {
            resultado = d;
            return true;
        }
    }
    return false;
}


// ================= MODIFICAR DOCTOR =================

void modificarDoctor() {
    cout << "\n=== MODIFICAR DOCTOR ===\n";

    int id;
    cout << "Ingrese ID del doctor: ";
    cin >> id;

    vector<Doctor> lista = GestorArchivos::leerTodosDoctores();

    int indice = -1;
    for (int i = 0; i < lista.size(); i++) {
        if (lista[i].getId() == id) {
            indice = i;
            break;
        }
    }

    if (indice == -1) {
        cout << "Doctor no encontrado.\n";
        return;
    }

    Doctor& d = lista[indice];

    cout << "Modificando a: " << d.getNombre() << " " << d.getApellido() << endl;

    string nuevo;
    int nuevaExp;
    float nuevoCosto;

    cout << "Nuevo nombre (actual: " << d.getNombre() << "): ";
    cin >> nuevo;
    d.setNombre(nuevo.c_str());

    cout << "Nuevo apellido (actual: " << d.getApellido() << "): ";
    cin >> nuevo;
    d.setApellido(nuevo.c_str());

    cout << "Nueva especialidad (actual: " << d.getEspecialidad() << "): ";
    cin >> nuevo;
    d.setEspecialidad(nuevo.c_str());

    cout << "Nueva experiencia (actual: " << d.getAniosExperiencia() << "): ";
    cin >> nuevaExp;
    d.setAniosExperiencia(nuevaExp);

    cout << "Nuevo costo consulta (actual: " << d.getCostoConsulta() << "): ";
    cin >> nuevoCosto;
    d.setCostoConsulta(nuevoCosto);

    GestorArchivos::guardarDoctor(d); // Se agrega como nuevo registro

    cout << "Doctor actualizado correctamente.\n";
}


// ================= LISTAR TODOS =================

void listarTodos() {
    cout << "\n=== LISTA DE DOCTORES ===\n";

    vector<Doctor> lista = GestorArchivos::leerTodosDoctores();

    if (lista.empty()) {
        cout << "No hay doctores registrados.\n";
        return;
    }

    for (auto& d : lista) {
        d.mostrarInformacionBasica();
    }
}


// ================= LISTAR POR ESPECIALIDAD =================

void listarPorEspecialidad() {
    cout << "\n=== LISTAR DOCTORES POR ESPECIALIDAD ===\n";

    string esp;
    cout << "Ingrese especialidad: ";
    cin >> esp;

    vector<Doctor> lista = GestorArchivos::leerTodosDoctores();

    bool encontrado = false;

    for (auto& d : lista) {
        if (strcmp(d.getEspecialidad(), esp.c_str()) == 0) {
            d.mostrarInformacionBasica();
            encontrado = true;
        }
    }

    if (!encontrado) {
        cout << "No hay doctores con esa especialidad.\n";
    }
}

} // namespace OperacionesDoctores
