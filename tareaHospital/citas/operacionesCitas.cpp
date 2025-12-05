#include "operacionesCitas.hpp"
#include <iostream>
#include <cstring>

using namespace std;

namespace OperacionesCitas {

// ================= BUSCAR CITA POR ID =================

bool buscarCitaPorID(int id, Cita& resultado) {
    vector<Cita> lista = GestorArchivos::leerTodasCitas();

    for (auto& c : lista) {
        if (c.getId() == id) {
            resultado = c;
            return true;
        }
    }
    return false;
}


// ================= AGENDAR CITA =================

void agendarCita(Hospital& hospital) {
    cout << "\n=== AGENDAR NUEVA CITA ===\n";

    int idPaciente, idDoctor;
    string fecha, hora, motivo;

    cout << "ID del paciente: ";
    cin >> idPaciente;

    cout << "ID del doctor: ";
    cin >> idDoctor;

    cout << "Fecha (YYYY-MM-DD): ";
    cin >> fecha;

    cout << "Hora (HH:MM): ";
    cin >> hora;

    cout << "Motivo: ";
    cin.ignore();
    getline(cin, motivo);

    int nuevoID = hospital.generarIdCita();

    Cita c(nuevoID, idPaciente, idDoctor,
           fecha.c_str(), hora.c_str(), motivo.c_str());

    if (!c.validarDatos()) {
        cout << "Error: Datos inválidos. No se pudo agendar la cita.\n";
        return;
    }

    GestorArchivos::guardarCita(c);

    cout << "Cita agendada con ID " << nuevoID << endl;
}


// ================= CANCELAR CITA =================

void cancelarCita() {
    cout << "\n=== CANCELAR CITA ===\n";

    int id;
    cout << "Ingrese ID de la cita: ";
    cin >> id;

    vector<Cita> lista = GestorArchivos::leerTodasCitas();

    int indice = -1;
    for (int i = 0; i < lista.size(); i++) {
        if (lista[i].getId() == id) {
            indice = i;
            break;
        }
    }

    if (indice == -1) {
        cout << "Cita no encontrada.\n";
        return;
    }

    Cita& c = lista[indice];
    c.cancelar();

    // Guardar como nuevo registro (simple append)
    GestorArchivos::guardarCita(c);

    cout << "Cita cancelada correctamente.\n";
}


// ================= ATENDER CITA =================

void atenderCita() {
    cout << "\n=== ATENDER CITA ===\n";

    int id;
    cout << "Ingrese ID de la cita: ";
    cin >> id;

    vector<Cita> lista = GestorArchivos::leerTodasCitas();

    int indice = -1;
    for (int i = 0; i < lista.size(); i++) {
        if (lista[i].getId() == id) {
            indice = i;
            break;
        }
    }

    if (indice == -1) {
        cout << "Cita no encontrada.\n";
        return;
    }

    Cita& c = lista[indice];
    c.marcarComoAtendida();

    GestorArchivos::guardarCita(c);

    cout << "Cita marcada como atendida.\n";
}


// ================= LISTAR TODAS =================

void listarTodas() {
    cout << "\n=== LISTA DE CITAS ===\n";

    vector<Cita> lista = GestorArchivos::leerTodasCitas();

    if (lista.empty()) {
        cout << "No hay citas registradas.\n";
        return;
    }

    for (auto& c : lista) {
        c.mostrarInformacion();
    }
}

} // namespace OperacionesCitas
