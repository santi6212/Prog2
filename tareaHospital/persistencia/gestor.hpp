#ifndef GESTOR_HPP
#define GESTOR_HPP

#include <fstream>
#include <string>
#include <vector>

#include "../hospital/hospital.hpp"
#include "../pacientes/pacientes.hpp"
#include "../doctores/doctor.hpp"
#include "../citas/citas.hpp"
#include "../historial/historial.hpp"

class GestorArchivos {
public:

    // ===== Inicialización =====
    static void inicializarSistema();

    // ===== Hospital =====
    static void guardarHospital(const Hospital& h);
    static void cargarHospital(Hospital& h);

    // ===== Pacientes =====
    static void guardarPaciente(const Paciente& p);
    static std::vector<Paciente> leerTodosPacientes();
    static void sobrescribirPacientes(const std::vector<Paciente>& lista);

    // ===== Doctores =====
    static void guardarDoctor(const Doctor& d);
    static std::vector<Doctor> leerTodosDoctores();
    static void sobrescribirDoctores(const std::vector<Doctor>& lista);

    // ===== Citas =====
    static void guardarCita(const Cita& c);
    static std::vector<Cita> leerTodasCitas();
    static void sobrescribirCitas(const std::vector<Cita>& lista);

    // ===== Historial Médico =====
    static void guardarHistorial(const HistorialMedico& h);
    static std::vector<HistorialMedico> leerTodoHistorial();
    static void sobrescribirHistorial(const std::vector<HistorialMedico>& lista);
};

#endif
