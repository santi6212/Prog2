#ifndef OPERACIONES_CITAS_HPP
#define OPERACIONES_CITAS_HPP

#include "../hospital/hospital.hpp"
#include "../citas/citas.hpp"
#include "../persistencia/gestor.hpp"
#include "../pacientes/pacientes.hpp"
#include "../doctores/doctor.hpp"
#include <vector>

namespace OperacionesCitas {

    // Agendar una nueva cita
    void agendarCita(Hospital& hospital);

    // Cancelar una cita
    void cancelarCita();

    // Marcar cita como atendida
    void atenderCita();

    // Listar todas las citas
    void listarTodas();

    // Buscar cita por ID
    bool buscarCitaPorID(int id, Cita& resultado);

}

#endif
