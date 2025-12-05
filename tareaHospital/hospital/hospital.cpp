#include "hospital.hpp"
#include <fstream>
#include <iostream>
#include <cstring>

using namespace std;

// ================= CONSTRUCTORES =================

Hospital::Hospital()
    : siguienteIdPaciente(1),
      siguienteIdDoctor(1),
      siguienteIdCita(1),
      siguienteIdConsulta(1) {

    strcpy(nombre, "Hospital General de Morioh");
    strcpy(direccion, "La Rotaria");
    strcpy(telefono, "0414-6990457");
}

Hospital::Hospital(const char* nom, const char* dir, const char* tel)
    : siguienteIdPaciente(1),
      siguienteIdDoctor(1),
      siguienteIdCita(1),
      siguienteIdConsulta(1) {

    strncpy(nombre, nom, sizeof(nombre)-1);
    strncpy(direccion, dir, sizeof(direccion)-1);
    strncpy(telefono, tel, sizeof(telefono)-1);
}

Hospital::Hospital(const Hospital& other)
    : siguienteIdPaciente(other.siguienteIdPaciente),
      siguienteIdDoctor(other.siguienteIdDoctor),
      siguienteIdCita(other.siguienteIdCita),
      siguienteIdConsulta(other.siguienteIdConsulta) {

    strcpy(nombre, other.nombre);
    strcpy(direccion, other.direccion);
    strcpy(telefono, other.telefono);
}

Hospital::~Hospital() {}


// ================= GETTERS =================

const char* Hospital::getNombre() const { return nombre; }
const char* Hospital::getDireccion() const { return direccion; }
const char* Hospital::getTelefono() const { return telefono; }

int Hospital::getSiguienteIdPaciente() const { return siguienteIdPaciente; }
int Hospital::getSiguienteIdDoctor() const { return siguienteIdDoctor; }
int Hospital::getSiguienteIdCita() const { return siguienteIdCita; }
int Hospital::getSiguienteIdConsulta() const { return siguienteIdConsulta; }


// ================= SETTERS =================

void Hospital::setNombre(const char* nuevo) { strncpy(nombre, nuevo, sizeof(nombre)-1); }
void Hospital::setDireccion(const char* nuevo) { strncpy(direccion, nuevo, sizeof(direccion)-1); }
void Hospital::setTelefono(const char* nuevo) { strncpy(telefono, nuevo, sizeof(telefono)-1); }

void Hospital::setSiguienteIdPaciente(int id) { siguienteIdPaciente = id; }
void Hospital::setSiguienteIdDoctor(int id) { siguienteIdDoctor = id; }
void Hospital::setSiguienteIdCita(int id) { siguienteIdCita = id; }
void Hospital::setSiguienteIdConsulta(int id) { siguienteIdConsulta = id; }


// ================= GENERADORES DE ID =================

int Hospital::generarIdPaciente() {
    return siguienteIdPaciente++;
}

int Hospital::generarIdDoctor() {
    return siguienteIdDoctor++;
}

int Hospital::generarIdCita() {
    return siguienteIdCita++;
}

int Hospital::generarIdConsulta() {
    return siguienteIdConsulta++;
}


// ================= PRESENTACIÓN =================

void Hospital::mostrarInformacion() const {
    cout << "\n=== INFORMACIÓN DEL HOSPITAL ===\n";
    cout << "Nombre: " << nombre << endl;
    cout << "Direccion: " << direccion << endl;
    cout << "Telefono: " << telefono << endl;

    cout << "\n--- Contadores de IDs ---\n";
    cout << "Siguiente ID Paciente: " << siguienteIdPaciente << endl;
    cout << "Siguiente ID Doctor: " << siguienteIdDoctor << endl;
    cout << "Siguiente ID Cita: " << siguienteIdCita << endl;
    cout << "Siguiente ID Consulta: " << siguienteIdConsulta << endl;
}


// ================= PERSISTENCIA =================

size_t Hospital::obtenerTamano() {
    return sizeof(Hospital);
}

void Hospital::guardarBinario(ofstream& out) const {
    out.write(reinterpret_cast<const char*>(this), sizeof(Hospital));
}

void Hospital::cargarBinario(ifstream& in) {
    in.read(reinterpret_cast<char*>(this), sizeof(Hospital));
}
