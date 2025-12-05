#include "citas.hpp"
#include <iostream>
#include <cstring>
#include <cctype>

using namespace std;

// ================= CONSTRUCTORES =================

Cita::Cita()
    : id(0), idPaciente(0), idDoctor(0), atendida(false) {
    strcpy(fecha, "");
    strcpy(hora, "");
    strcpy(motivo, "");
    strcpy(estado, "agendada");
    strcpy(observaciones, "");
}

Cita::Cita(int id, int idPac, int idDoc,
           const char* f, const char* h, const char* mot)
    : id(id), idPaciente(idPac), idDoctor(idDoc), atendida(false) {

    strncpy(fecha, f, sizeof(fecha)-1);
    strncpy(hora, h, sizeof(hora)-1);
    strncpy(motivo, mot, sizeof(motivo)-1);
    strcpy(estado, "agendada");
    strcpy(observaciones, "");
}

Cita::Cita(const Cita& other)
    : id(other.id),
      idPaciente(other.idPaciente),
      idDoctor(other.idDoctor),
      atendida(other.atendida) {

    strcpy(fecha, other.fecha);
    strcpy(hora, other.hora);
    strcpy(motivo, other.motivo);
    strcpy(estado, other.estado);
    strcpy(observaciones, other.observaciones);
}

Cita::~Cita() {}


// ================= GETTERS =================

int Cita::getId() const { return id; }
int Cita::getIdPaciente() const { return idPaciente; }
int Cita::getIdDoctor() const { return idDoctor; }
const char* Cita::getFecha() const { return fecha; }
const char* Cita::getHora() const { return hora; }
const char* Cita::getMotivo() const { return motivo; }
const char* Cita::getEstado() const { return estado; }
const char* Cita::getObservaciones() const { return observaciones; }
bool Cita::estaAtendida() const { return atendida; }


// ================= SETTERS =================

void Cita::setFecha(const char* nuevaFecha) {
    strncpy(fecha, nuevaFecha, sizeof(fecha)-1);
}

void Cita::setHora(const char* nuevaHora) {
    strncpy(hora, nuevaHora, sizeof(hora)-1);
}

void Cita::setMotivo(const char* nuevoMotivo) {
    strncpy(motivo, nuevoMotivo, sizeof(motivo)-1);
}

void Cita::setEstado(const char* nuevoEstado) {
    strncpy(estado, nuevoEstado, sizeof(estado)-1);
}

void Cita::setObservaciones(const char* nuevo) {
    strncpy(observaciones, nuevo, sizeof(observaciones)-1);
}

void Cita::setAtendida(bool valor) {
    atendida = valor;
}


// ================= VALIDACIONES =================

bool Cita::validarFecha() const {
    // Formato esperado: YYYY-MM-DD
    if (strlen(fecha) != 10) return false;
    if (fecha[4] != '-' || fecha[7] != '-') return false;

    for (int i = 0; i < 10; i++) {
        if (i == 4 || i == 7) continue;
        if (!isdigit(fecha[i])) return false;
    }
    return true;
}

bool Cita::validarHora() const {
    // Formato esperado: HH:MM
    if (strlen(hora) != 5) return false;
    if (hora[2] != ':') return false;

    if (!isdigit(hora[0]) || !isdigit(hora[1]) ||
        !isdigit(hora[3]) || !isdigit(hora[4])) return false;

    int hh = (hora[0]-'0')*10 + (hora[1]-'0');
    int mm = (hora[3]-'0')*10 + (hora[4]-'0');

    return (hh >= 0 && hh < 24) && (mm >= 0 && mm < 60);
}

bool Cita::validarDatos() const {
    return idPaciente > 0 &&
           idDoctor > 0 &&
           validarFecha() &&
           validarHora() &&
           strlen(motivo) > 0;
}


// ================= GESTIÓN =================

void Cita::marcarComoAtendida() {
    strcpy(estado, "atendida");
    atendida = true;
}

void Cita::cancelar() {
    strcpy(estado, "cancelada");
    atendida = false;
}


// ================= PRESENTACIÓN =================

void Cita::mostrarInformacion() const {
    cout << "Cita ID " << id
         << " | Paciente: " << idPaciente
         << " | Doctor: " << idDoctor
         << " | Fecha: " << fecha
         << " | Hora: " << hora
         << " | Estado: " << estado
         << " | Motivo: " << motivo << endl;
}


// ================= PERSISTENCIA =================

size_t Cita::obtenerTamano() {
    return sizeof(Cita);
}

void Cita::guardarBinario(ofstream& out) const {
    out.write(reinterpret_cast<const char*>(this), sizeof(Cita));
}

void Cita::cargarBinario(ifstream& in) {
    in.read(reinterpret_cast<char*>(this), sizeof(Cita));
}
