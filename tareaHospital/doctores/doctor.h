#ifndef DOCTOR_HPP
#define DOCTOR_HPP

#include <string>
#include <vector>

class Doctor {
private:
    int id;
    std::string nombre;
    std::string apellido;
    std::string cedula;
    std::string especialidad;
    int aniosExperiencia;
    float costoConsulta;
    bool disponible;
    std::vector<int> pacientesAsignados;

public:
    Doctor();
    Doctor(int id, const std::string& nombre, const std::string& apellido, const std::string& cedula);
    ~Doctor();

    int getId() const;
    std::string getNombre() const;
    void setDisponible(bool estado);

    void mostrarInformacion() const;
};

#endif
