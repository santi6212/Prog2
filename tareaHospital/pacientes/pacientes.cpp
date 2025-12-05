#include "Pacientes.hpp"
#include <iostream>
#include <cstring>

using namespace std;

// ================= CONSTRUCTORES =================

Paciente::Paciente()
    : id(0), edad(0), sexo(' '), activo(true) {
    strcpy(nombre, "");
    strcpy(apellido, "");
    strcpy(cedula, "");
    strcpy(tipoSangre, "");
    strcpy(telefono, "");
    strcpy(direccion, "");
    strcpy(email, "");
    strcpy(alergias, "");
    strcpy(observaciones, "");
}

Paciente::Paciente(int id, const char* nom, const char* ape, const char* ced)
    : id(id), edad(0), sexo(' '), activo(true) {
    strncpy(nombre, nom, sizeof(nombre)-1);
    strncpy(apellido, ape, sizeof(apellido)-1);
    strncpy(cedula, ced, sizeof(cedula)-1);
}

Paciente::Paciente(const Paciente& other)
    : id(other.id), edad(other.edad), sexo(other.sexo), activo(other.activo),
      historial(other.historial) {

    strcpy(nombre, other.nombre);
    strcpy(apellido, other.apellido);
    strcpy(cedula, other.cedula);
    strcpy(tipoSangre, other.tipoSangre);
    strcpy(telefono, other.telefono);
    strcpy(direccion, other.direccion);
    strcpy(email, other.email);
    strcpy(alergias, other.alergias);
    strcpy(observaciones, other.observaciones);
}

Paciente::~Paciente() {}


// ================= GETTERS =================

int Paciente::getId() const { return id; }
const char* Paciente::getNombre() const { return nombre; }
const char* Paciente::getApellido() const { return apellido; }
const char* Paciente::getCedula() const { return cedula; }
int Paciente::getEdad() const { return edad; }
char Paciente::getSexo() const { return sexo; }
const char* Paciente::getTipoSangre() const { return tipoSangre; }
const char* Paciente::getTelefono() const { return telefono; }
const char* Paciente::getDireccion() const { return direccion; }
const char* Paciente::getEmail() const { return email; }
const char* Paciente::getAlergias() const { return alergias; }
const char* Paciente::getObservaciones() const { return observaciones; }
bool Paciente::estaActivo() const { return activo; }

const vector<HistorialMedico>& Paciente::getHistorial() const {
    return historial;
}


// ================= SETTERS =================

void Paciente::setNombre(const char* nuevo) { strncpy(nombre, nuevo, sizeof(nombre)-1); }
void Paciente::setApellido(const char* nuevo) { strncpy(apellido, nuevo, sizeof(apellido)-1); }
void Paciente::setCedula(const char* nuevo) { strncpy(cedula, nuevo, sizeof(cedula)-1); }

void Paciente::setEdad(int nuevaEdad) {
    if (nuevaEdad >= 0 && nuevaEdad <= 120)
        edad = nuevaEdad;
}

void Paciente::setSexo(char nuevoSexo) {
    nuevoSexo = toupper(nuevoSexo);
    if (nuevoSexo == 'M' || nuevoSexo == 'F')
        sexo = nuevoSexo;
}

void Paciente::setTipoSangre(const char* nuevo) { strncpy(tipoSangre, nuevo, sizeof(tipoSangre)-1); }
void Paciente::setTelefono(const char* nuevo) { strncpy(telefono, nuevo, sizeof(telefono)-1); }
void Paciente::setDireccion(const char* nuevo) { strncpy(direccion, nuevo, sizeof(direccion)-1); }
void Paciente::setEmail(const char* nuevo) { strncpy(email, nuevo, sizeof(email)-1); }
void Paciente::setAlergias(const char* nuevo) { strncpy(alergias, nuevo, sizeof(alergias)-1); }
void Paciente::setObservaciones(const char* nuevo) { strncpy(observaciones, nuevo, sizeof(observaciones)-1); }
void Paciente::setActivo(bool estado) { activo = estado; }


// ================= VALIDACIONES =================

bool Paciente::cedulaEsValida() const {
    return strlen(cedula) > 0 && strlen(cedula) < 20;
}

bool Paciente::esMayorDeEdad() const {
    return edad >= 18;
}

bool Paciente::validarDatos() const {
    return strlen(nombre) > 0 &&
           strlen(apellido) > 0 &&
           cedulaEsValida() &&
           edad > 0 &&
           (sexo == 'M' || sexo == 'F');
}


// ================= HISTORIAL =================

void Paciente::agregarConsulta(const HistorialMedico& consulta) {
    historial.push_back(consulta);
}

bool Paciente::tieneHistorial() const {
    return !historial.empty();
}


// ================= PRESENTACIÓN =================

void Paciente::mostrarInformacionBasica() const {
    cout << "Paciente ID " << id << ": "
         << nombre << " " << apellido
         << " | Cedula: " << cedula
         << " | Edad: " << edad
         << " | Sexo: " << sexo << endl;
}

void Paciente::mostrarInformacionCompleta() const {
    mostrarInformacionBasica();
    cout << "Telefono: " << telefono << endl;
    cout << "Direccion: " << direccion << endl;
    cout << "Email: " << email << endl;
    cout << "Tipo de sangre: " << tipoSangre << endl;
    cout << "Alergias: " << alergias << endl;
    cout << "Observaciones: " << observaciones << endl;
}


// ================= PERSISTENCIA =================

size_t Paciente::obtenerTamano() {
    return sizeof(Paciente);
}

void Paciente::guardarBinario(ofstream& out) const {
    out.write(reinterpret_cast<const char*>(this), sizeof(Paciente));
}

void Paciente::cargarBinario(ifstream& in) {
    in.read(reinterpret_cast<char*>(this), sizeof(Paciente));
}
