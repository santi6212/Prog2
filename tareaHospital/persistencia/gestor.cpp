#include "gestor.hpp"
#include <iostream>
#include <fstream>

using namespace std;

// ======================= INICIALIZACIÓN =======================

void GestorArchivos::inicializarSistema() {
    // Si los archivos no existen, se crean vacíos
    ofstream("pacientes.dat", ios::binary | ios::app).close();
    ofstream("doctores.dat", ios::binary | ios::app).close();
    ofstream("citas.dat", ios::binary | ios::app).close();
    ofstream("historial.dat", ios::binary | ios::app).close();
    ofstream("hospital.dat", ios::binary | ios::app).close();
}

// ======================= HOSPITAL =======================

void GestorArchivos::guardarHospital(const Hospital& h) {
    ofstream out("hospital.dat", ios::binary | ios::trunc);
    if (!out) return;
    out.write(reinterpret_cast<const char*>(&h), sizeof(Hospital));
}

void GestorArchivos::cargarHospital(Hospital& h) {
    ifstream in("hospital.dat", ios::binary);
    if (!in) return;
    in.read(reinterpret_cast<char*>(&h), sizeof(Hospital));
}

// ======================= PACIENTES =======================

void GestorArchivos::guardarPaciente(const Paciente& p) {
    ofstream out("pacientes.dat", ios::binary | ios::app);
    out.write(reinterpret_cast<const char*>(&p), sizeof(Paciente));
}

vector<Paciente> GestorArchivos::leerTodosPacientes() {
    vector<Paciente> lista;
    ifstream in("pacientes.dat", ios::binary);

    Paciente p;
    while (in.read(reinterpret_cast<char*>(&p), sizeof(Paciente))) {
        lista.push_back(p);
    }
    return lista;
}

void GestorArchivos::sobrescribirPacientes(const vector<Paciente>& lista) {
    ofstream out("pacientes.dat", ios::binary | ios::trunc);
    for (const auto& p : lista)
        out.write(reinterpret_cast<const char*>(&p), sizeof(Paciente));
}

// ======================= DOCTORES =======================

void GestorArchivos::guardarDoctor(const Doctor& d) {
    ofstream out("doctores.dat", ios::binary | ios::app);
    out.write(reinterpret_cast<const char*>(&d), sizeof(Doctor));
}

vector<Doctor> GestorArchivos::leerTodosDoctores() {
    vector<Doctor> lista;
    ifstream in("doctores.dat", ios::binary);

    Doctor d;
    while (in.read(reinterpret_cast<char*>(&d), sizeof(Doctor))) {
        lista.push_back(d);
    }
    return lista;
}

void GestorArchivos::sobrescribirDoctores(const vector<Doctor>& lista) {
    ofstream out("doctores.dat", ios::binary | ios::trunc);
    for (const auto& d : lista)
        out.write(reinterpret_cast<const char*>(&d), sizeof(Doctor));
}

// ======================= CITAS =======================

void GestorArchivos::guardarCita(const Cita& c) {
    ofstream out("citas.dat", ios::binary | ios::app);
    out.write(reinterpret_cast<const char*>(&c), sizeof(Cita));
}

vector<Cita> GestorArchivos::leerTodasCitas() {
    vector<Cita> lista;
    ifstream in("citas.dat", ios::binary);

    Cita c;
    while (in.read(reinterpret_cast<char*>(&c), sizeof(Cita))) {
        lista.push_back(c);
    }
    return lista;
}

void GestorArchivos::sobrescribirCitas(const vector<Cita>& lista) {
    ofstream out("citas.dat", ios::binary | ios::trunc);
    for (const auto& c : lista)
        out.write(reinterpret_cast<const char*>(&c), sizeof(Cita));
}

// ======================= HISTORIAL MÉDICO =======================

void GestorArchivos::guardarHistorial(const HistorialMedico& h) {
    ofstream out("historial.dat", ios::binary | ios::app);
    out.write(reinterpret_cast<const char*>(&h), sizeof(HistorialMedico));
}

vector<HistorialMedico> GestorArchivos::leerTodoHistorial() {
    vector<HistorialMedico> lista;
    ifstream in("historial.dat", ios::binary);

    HistorialMedico h;
    while (in.read(reinterpret_cast<char*>(&h), sizeof(HistorialMedico))) {
        lista.push_back(h);
    }
    return lista;
}

void GestorArchivos::sobrescribirHistorial(const vector<HistorialMedico>& lista) {
    ofstream out("historial.dat", ios::binary | ios::trunc);
    for (const auto& h : lista)
        out.write(reinterpret_cast<const char*>(&h), sizeof(HistorialMedico));
}
