#ifndef GESTORARCHIVOS_HPP
#define GESTORARCHIVOS_HPP

#include "../pacientes/pacientes.h"
#include "../doctores/doctor.h"
#include "../citas/citas.h"

class GestorArchivos {
public:
    static bool guardarPaciente(const Paciente& p);
    static bool cargarPacientes(std::vector<Paciente>& lista);
    static bool guardarDoctor(const Doctor& d);
    static bool cargarDoctores(std::vector<Doctor>& lista);
    static bool guardarCita(const Cita& c);
    static bool cargarCitas(std::vector<Cita>& lista);
};

#endif
