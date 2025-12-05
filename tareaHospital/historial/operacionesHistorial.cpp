#include "operacionesHistorial.hpp"
#include <iostream>
#include <cstring>

using namespace std;

namespace OperacionesHistorial {

// ================= BUSCAR CONSULTA POR ID =================

bool buscarConsultaPorID(int id, HistorialMedico& resultado) {
    vector<HistorialMedico> lista = GestorArchivos::leerTodoHistorial();

    for (auto& h : lista) {
        if (h.getIdConsulta() == id) {
            resultado = h;
            return true;
        }
    }
    return false;
}


// ================= REGISTRAR CONSULTA =================

void registrarConsulta(Hospital& hospital) {
    cout << "\n=== REGISTRAR CONSULTA MÉDICA ===\n";

    int idPaciente, idDoctor;
    string fecha, hora, diagnostico, tratamiento, medicamentos;
    float costo;

    cout << "ID del paciente: ";
    cin >> idPaciente;

    cout << "ID del doctor: ";
    cin >> idDoctor;

    cout << "Fecha (YYYY-MM-DD): ";
    cin >> fecha;

    cout << "Hora (HH:MM): ";
    cin >> hora;

    cout << "Diagnóstico: ";
    cin.ignore();
    getline(cin, diagnostico);

    cout << "Tratamiento: ";
    getline(cin, tratamiento);

    cout << "Medicamentos: ";
    getline(cin, medicamentos);

    cout << "Costo: ";
    cin >> costo;

    int nuevoID = hospital.generarIdConsulta();

    HistorialMedico h(
        nuevoID,
        idPaciente,                 // ? ahora sí guardamos el paciente
        fecha.c_str(),
        hora.c_str(),
        diagnostico.c_str(),
        tratamiento.c_str(),
        medicamentos.c_str(),
        idDoctor,
        costo
    );

    if (!h.validarDatos()) {
        cout << "Error: Datos inválidos. No se registró la consulta.\n";
        return;
    }

    GestorArchivos::guardarHistorial(h);

    cout << "Consulta registrada con ID " << nuevoID << endl;
}


// ================= MOSTRAR HISTORIAL DE UN PACIENTE =================

void mostrarHistorialPaciente() {
    cout << "\n=== HISTORIAL MÉDICO DEL PACIENTE ===\n";

    int idPaciente;
    cout << "Ingrese ID del paciente: ";
    cin >> idPaciente;

    vector<HistorialMedico> lista = GestorArchivos::leerTodoHistorial();

    bool encontrado = false;

    for (auto& h : lista) {
        if (h.getIdPaciente() == idPaciente) {   // ? ahora sí filtra bien
            h.mostrarInformacion();
            cout << "-----------------------------\n";
            encontrado = true;
        }
    }

    if (!encontrado) {
        cout << "Este paciente no tiene historial registrado.\n";
    }
}


// ================= LISTAR TODO EL HISTORIAL =================

void listarTodoHistorial() {
    cout << "\n=== HISTORIAL MÉDICO COMPLETO ===\n";

    vector<HistorialMedico> lista = GestorArchivos::leerTodoHistorial();

    if (lista.empty()) {
        cout << "No hay consultas registradas.\n";
        return;
    }

    for (auto& h : lista) {
        h.mostrarInformacion();
        cout << "-----------------------------\n";
    }
}

} // namespace OperacionesHistorial
