#include "pacientes.hpp"
#include "../utilidades/validacion.hpp"
#include <iostream>

Paciente::Paciente() : id(0), edad(0), sexo(' '), activo(true) {}
Paciente::Paciente(int id, const std::string& nombre, const std::string& apellido, const std::string& cedula)
    : id(id), nombre(nombre), apellido(apellido), cedula(cedula), edad(0), sexo(' '), activo(true) {}
Paciente::Paciente(const Paciente& otro) = default;
Paciente::~Paciente() = default;

int Paciente::getId() const { return id; }
std::string Paciente::getNombre() const { return nombre; }
std::string Paciente::getCedula() const { return cedula; }

void Paciente::setEdad(int nuevaEdad) {
    if (nuevaEdad > 0 && nuevaEdad <= 120) edad = nuevaEdad;
}

void Paciente::setEmail(const std::string& nuevoEmail) {
    if (Validaciones::validarEmail(nuevoEmail.c_str())) email = nuevoEmail;
}

bool Paciente::validarDatos() const {
    return Validaciones::validarCedula(cedula.c_str()) && edad > 0;
}

void Paciente::mostrarInformacionBasica() const {
    std::cout << "Paciente " << id << ": " << nombre << " " << apellido << " (" << cedula << ")\n";
}

void Paciente::mostrarInformacionCompleta() const {
    mostrarInformacionBasica();
    std::cout << "Edad: " << edad << " Sexo: " << sexo << " Email: " << email << "\n";
}

void Paciente::agregarConsulta(const HistorialMedico& consulta) {
    historial.push_back(consulta);
}

const std::vector<HistorialMedico>& Paciente::getHistorial() const {
    return historial;
}
