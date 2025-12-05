#include "doctor.hpp"
#include <iostream>
#include <cstring>

using namespace std;

// ================= CONSTRUCTORES =================

Doctor::Doctor()
    : id(0), aniosExperiencia(0), costoConsulta(0.0f), disponible(true) {
    strcpy(nombre, "");
    strcpy(apellido, "");
    strcpy(cedula, "");
    strcpy(especialidad, "");
}

Doctor::Doctor(int id, const char* nom, const char* ape, const char* ced,
               const char* esp, int exp, float costo)
    : id(id), aniosExperiencia(exp), costoConsulta(costo), disponible(true) {

    strncpy(nombre, nom, sizeof(nombre)-1);
    strncpy(apellido, ape, sizeof(apellido)-1);
    strncpy(cedula, ced, sizeof(cedula)-1);
    strncpy(especialidad, esp, sizeof(especialidad)-1);
}

Doctor::Doctor(const Doctor& other)
    : id(other.id),
      aniosExperiencia(other.aniosExperiencia),
      costoConsulta(other.costoConsulta),
      disponible(other.disponible),
      pacientesAsignados(other.pacientesAsignados) {

    strcpy(nombre, other.nombre);
    strcpy(apellido, other.apellido);
    strcpy(cedula, other.cedula);
    strcpy(especialidad, other.especialidad);
}

Doctor::~Doctor() {}


// ================= GETTERS =================

int Doctor::getId() const { return id; }
const char* Doctor::getNombre() const { return nombre; }
const char* Doctor::getApellido() const { return apellido; }
const char* Doctor::getCedula() const { return cedula; }
const char* Doctor::getEspecialidad() const { return especialidad; }
int Doctor::getAniosExperiencia() const { return aniosExperiencia; }
float Doctor::getCostoConsulta() const { return costoConsulta; }
bool Doctor::estaDisponible() const { return disponible; }

const vector<int>& Doctor::getPacientesAsignados() const {
    return pacientesAsignados;
}


// ================= SETTERS =================

void Doctor::setNombre(const char* nuevo) { strncpy(nombre, nuevo, sizeof(nombre)-1); }
void Doctor::setApellido(const char* nuevo) { strncpy(apellido, nuevo, sizeof(apellido)-1); }
void Doctor::setCedula(const char* nuevo) { strncpy(cedula, nuevo, sizeof(cedula)-1); }
void Doctor::setEspecialidad(const char* nuevo) { strncpy(especialidad, nuevo, sizeof(especialidad)-1); }

void Doctor::setAniosExperiencia(int exp) {
    if (exp >= 0 && exp <= 80)
        aniosExperiencia = exp;
}

void Doctor::setCostoConsulta(float costo) {
    if (costo >= 0)
        costoConsulta = costo;
}

void Doctor::setDisponible(bool estado) {
    disponible = estado;
}


// ================= VALIDACIONES =================

bool Doctor::cedulaEsValida() const {
    return strlen(cedula) > 0 && strlen(cedula) < 20;
}

bool Doctor::especialidadEsValida() const {
    return strlen(especialidad) > 0;
}

bool Doctor::validarDatos() const {
    return strlen(nombre) > 0 &&
           strlen(apellido) > 0 &&
           cedulaEsValida() &&
           especialidadEsValida() &&
           aniosExperiencia >= 0 &&
           costoConsulta >= 0;
}


// ================= GESTIÓN DE PACIENTES ASIGNADOS =================

void Doctor::asignarPaciente(int idPaciente) {
    pacientesAsignados.push_back(idPaciente);
}

bool Doctor::tienePacientes() const {
    return !pacientesAsignados.empty();
}


// ================= PRESENTACIÓN =================

void Doctor::mostrarInformacionBasica() const {
    cout << "Doctor ID " << id << ": "
         << nombre << " " << apellido
         << " | Cedula: " << cedula
         << " | Especialidad: " << especialidad << endl;
}

void Doctor::mostrarInformacionCompleta() const {
    mostrarInformacionBasica();
    cout << "Experiencia: " << aniosExperiencia << " años" << endl;
    cout << "Costo consulta: $" << costoConsulta << endl;
    cout << "Disponible: " << (disponible ? "Sí" : "No") << endl;
    cout << "Pacientes asignados: " << pacientesAsignados.size() << endl;
}


// ================= PERSISTENCIA =================

size_t Doctor::obtenerTamano() {
    return sizeof(Doctor);
}

void Doctor::guardarBinario(ofstream& out) const {
    out.write(reinterpret_cast<const char*>(this), sizeof(Doctor));
}

void Doctor::cargarBinario(ifstream& in) {
    in.read(reinterpret_cast<char*>(this), sizeof(Doctor));
}
