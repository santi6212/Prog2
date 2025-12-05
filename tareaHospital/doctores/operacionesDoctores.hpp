#ifndef OPERACIONES_DOCTORES_HPP
#define OPERACIONES_DOCTORES_HPP

#include "../hospital/hospital.hpp"
#include "../doctores/doctor.hpp"
#include "../persistencia/gestor.hpp"
#include <vector>

namespace OperacionesDoctores {

    // Registrar un nuevo doctor
    void registrarDoctor(Hospital& hospital);

    // Buscar doctor por ID
    bool buscarDoctorPorID(int id, Doctor& resultado);

    // Buscar doctor por cédula
    bool buscarDoctorPorCedula(const char* cedula, Doctor& resultado);

    // Modificar datos de un doctor
    void modificarDoctor();

    // Listar todos los doctores
    void listarTodos();

    // Listar doctores por especialidad
    void listarPorEspecialidad();

}

#endif
