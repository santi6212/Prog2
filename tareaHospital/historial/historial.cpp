#include "historial.hpp"
#include <iostream>
#include <cstring>
#include <cctype>

using namespace std;

// ================= CONSTRUCTORES =================

HistorialMedico::HistorialMedico()
    : idConsulta(0), idPaciente(0), idDoctor(0), costo(0.0f)
{
    strcpy(fecha, "");
    strcpy(hora, "");
    strcpy(diagnostico, "");
    strcpy(tratamiento, "");
    strcpy(medicamentos, "");
}

HistorialMedico::HistorialMedico(int id, int idPac, const char* f, const char* h,
                                 const char* diag, const char* trat,
                                 const char* meds, int idDoc, float c)
    : idConsulta(id), idPaciente(idPac), idDoctor(idDoc), costo(c)
{
    strncpy(fecha, f, sizeof(fecha) - 1);
    fecha[sizeof(fecha) - 1] = '\0';

    strncpy(hora, h, sizeof(hora) - 1);
    hora[sizeof(hora) - 1] = '\0';

    strncpy(diagnostico, diag, sizeof(diagnostico) - 1);
    diagnostico[sizeof(diagnostico) - 1] = '\0';

    strncpy(tratamiento, trat, sizeof(tratamiento) - 1);
    tratamiento[sizeof(tratamiento) - 1] = '\0';

    strncpy(medicamentos, meds, sizeof(medicamentos) - 1);
    medicamentos[sizeof(medicamentos) - 1] = '\0';
}

HistorialMedico::HistorialMedico(const HistorialMedico& other)
    : idConsulta(other.idConsulta),
      idPaciente(other.idPaciente),
      idDoctor(other.idDoctor),
      costo(other.costo)
{
    strcpy(fecha, other.fecha);
    strcpy(hora, other.hora);
    strcpy(diagnostico, other.diagnostico);
    strcpy(tratamiento, other.tratamiento);
    strcpy(medicamentos, other.medicamentos);
}

HistorialMedico::~HistorialMedico() {}


// ================= GETTERS =================

int HistorialMedico::getIdConsulta() const { return idConsulta; }
int HistorialMedico::getIdPaciente() const { return idPaciente; }
const char* HistorialMedico::getFecha() const { return fecha; }
const char* HistorialMedico::getHora() const { return hora; }
const char* HistorialMedico::getDiagnostico() const { return diagnostico; }
const char* HistorialMedico::getTratamiento() const { return tratamiento; }
const char* HistorialMedico::getMedicamentos() const { return medicamentos; }
int HistorialMedico::getIdDoctor() const { return idDoctor; }
float HistorialMedico::getCosto() const { return costo; }


// ================= SETTERS =================

void HistorialMedico::setIdPaciente(int id) { idPaciente = id; }

void HistorialMedico::setFecha(const char* nuevaFecha) {
    strncpy(fecha, nuevaFecha, sizeof(fecha) - 1);
    fecha[sizeof(fecha) - 1] = '\0';
}

void HistorialMedico::setHora(const char* nuevaHora) {
    strncpy(hora, nuevaHora, sizeof(hora) - 1);
    hora[sizeof(hora) - 1] = '\0';
}

void HistorialMedico::setDiagnostico(const char* nuevo) {
    strncpy(diagnostico, nuevo, sizeof(diagnostico) - 1);
    diagnostico[sizeof(diagnostico) - 1] = '\0';
}

void HistorialMedico::setTratamiento(const char* nuevo) {
    strncpy(tratamiento, nuevo, sizeof(tratamiento) - 1);
    tratamiento[sizeof(tratamiento) - 1] = '\0';
}

void HistorialMedico::setMedicamentos(const char* nuevo) {
    strncpy(medicamentos, nuevo, sizeof(medicamentos) - 1);
    medicamentos[sizeof(medicamentos) - 1] = '\0';
}

void HistorialMedico::setIdDoctor(int id) { idDoctor = id; }

void HistorialMedico::setCosto(float nuevoCosto) {
    if (nuevoCosto >= 0)
        costo = nuevoCosto;
}


// ================= VALIDACIONES =================

bool HistorialMedico::validarFecha() const {
    if (strlen(fecha) != 10) return false;
    if (fecha[4] != '-' || fecha[7] != '-') return false;

    for (int i = 0; i < 10; i++) {
        if (i == 4 || i == 7) continue;
        if (!isdigit(fecha[i])) return false;
    }
    return true;
}

bool HistorialMedico::validarHora() const {
    if (strlen(hora) != 5) return false;
    if (hora[2] != ':') return false;

    if (!isdigit(hora[0]) || !isdigit(hora[1]) ||
        !isdigit(hora[3]) || !isdigit(hora[4])) return false;

    int hh = (hora[0] - '0') * 10 + (hora[1] - '0');
    int mm = (hora[3] - '0') * 10 + (hora[4] - '0');

    return (hh >= 0 && hh < 24) && (mm >= 0 && mm < 60);
}

bool HistorialMedico::validarDatos() const {
    return idPaciente > 0 &&
           idDoctor > 0 &&
           validarFecha() &&
           validarHora() &&
           strlen(diagnostico) > 0 &&
           costo >= 0;
}


// ================= PRESENTACIÓN =================

void HistorialMedico::mostrarInformacion() const {
    cout << "Consulta ID: " << idConsulta << endl;
    cout << "Paciente ID: " << idPaciente << endl;
    cout << "Doctor ID: " << idDoctor << endl;
    cout << "Fecha: " << fecha << endl;
    cout << "Hora: " << hora << endl;
    cout << "Diagnóstico: " << diagnostico << endl;
    cout << "Tratamiento: " << tratamiento << endl;
    cout << "Medicamentos: " << medicamentos << endl;
    cout << "Costo: $" << costo << endl;
}


// ================= PERSISTENCIA =================

size_t HistorialMedico::obtenerTamano() {
    return sizeof(HistorialMedico);
}

void HistorialMedico::guardarBinario(ofstream& out) const {
    out.write(reinterpret_cast<const char*>(this), sizeof(HistorialMedico));
}

void HistorialMedico::cargarBinario(ifstream& in) {
    in.read(reinterpret_cast<char*>(this), sizeof(HistorialMedico));
}
