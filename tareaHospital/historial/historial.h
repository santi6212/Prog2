#ifndef HISTORIALMEDICO_HPP
#define HISTORIALMEDICO_HPP

#include <string>

class HistorialMedico {
private:
    int idConsulta;
    std::string fecha;
    std::string hora;
    std::string diagnostico;
    std::string tratamiento;
    std::string medicamentos;
    int idDoctor;
    float costo;

public:
    HistorialMedico();
    ~HistorialMedico();

    void mostrarInformacion() const;
};

#endif
