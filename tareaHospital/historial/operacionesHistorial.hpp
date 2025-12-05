#ifndef OPERACIONES_HISTORIAL_HPP
#define OPERACIONES_HISTORIAL_HPP

#include "../hospital/hospital.hpp"
#include "../historial/historial.hpp"
#include "../persistencia/gestor.hpp"
#include "../pacientes/pacientes.hpp"
#include <vector>

namespace OperacionesHistorial {

    // Registrar una nueva consulta médica
    void registrarConsulta(Hospital& hospital);

    // Mostrar historial completo de un paciente
    void mostrarHistorialPaciente();

    // Buscar consulta por ID
    bool buscarConsultaPorID(int id, HistorialMedico& resultado);

    // Listar todas las consultas del sistema
    void listarTodoHistorial();

}

#endif
