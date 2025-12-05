#ifndef OPERACIONES_PACIENTES_HPP
#define OPERACIONES_PACIENTES_HPP

#include "../hospital/hospital.hpp"
#include "../pacientes/pacientes.hpp"
#include "../persistencia/gestor.hpp"
#include <vector>

namespace OperacionesPacientes {

    // Registrar un nuevo paciente
    void registrarPaciente(Hospital& hospital);

    // Buscar paciente por ID (en archivo)
    bool buscarPacientePorID(int id, Paciente& resultado);

    // Buscar paciente por cédula
    bool buscarPacientePorCedula(const char* cedula, Paciente& resultado);

    // Modificar datos de un paciente
    void modificarPaciente();

    // Eliminar paciente (lógico)
    void eliminarPaciente();

    // Listar todos los pacientes
    void listarTodos();

    // Mostrar historial médico de un paciente
    void mostrarHistorialPaciente();
}

#endif
