#ifndef CITA_HPP
#define CITA_HPP

#include <string>

class Cita {
private:
    int id;
    int idPaciente;
    int idDoctor;
    std::string fecha;
    std::string hora;
    std::string motivo;
    std::string estado;
    bool atendida;

public:
    Cita();
    ~Cita();

    int getId() const;
    void cancelar();
    void atender();
    void mostrarInformacion() const;
};

#endif
