#ifndef PACIENTE_HPP
#define PACIENTE_HPP

#include <string>
#include <vector>
#include "../historial/historial.h"

class Paciente {
private:
    int id;
    std::string nombre;
    std::string apellido;
    std::string cedula;
    int edad;
    char sexo;
    std::string telefono;
    std::string direccion;
    std::string email;
    bool activo;
    std::vector<HistorialMedico> historial;

public:
    Paciente();
    Paciente(int id, const std::string& nombre, const std::string& apellido, const std::string& cedula);
    Paciente(const Paciente& otro);
    ~Paciente();

    int getId() const;
    std::string getNombre() const;
    std::string getCedula() const;

    void setEdad(int nuevaEdad);
    void setEmail(const std::string& nuevoEmail);

    bool validarDatos() const;
    void mostrarInformacionBasica() const;
    void mostrarInformacionCompleta() const;

    void agregarConsulta(const HistorialMedico& consulta);
    const std::vector<HistorialMedico>& getHistorial() const;
};

#endif
