#ifndef DOCTOR_HPP
#define DOCTOR_HPP

#include <cstring>
#include <vector>
#include <fstream>

class Doctor {
private:
    int id;
    char nombre[50];
    char apellido[50];
    char cedula[20];
    char especialidad[50];
    int aniosExperiencia;
    float costoConsulta;
    bool disponible;

    std::vector<int> pacientesAsignados;

public:
    // ===== Constructores =====
    Doctor();
    Doctor(int id, const char* nombre, const char* apellido, const char* cedula,
           const char* especialidad, int experiencia, float costo);
    Doctor(const Doctor& other);
    ~Doctor();

    // ===== Getters =====
    int getId() const;
    const char* getNombre() const;
    const char* getApellido() const;
    const char* getCedula() const;
    const char* getEspecialidad() const;
    int getAniosExperiencia() const;
    float getCostoConsulta() const;
    bool estaDisponible() const;

    const std::vector<int>& getPacientesAsignados() const;

    // ===== Setters =====
    void setNombre(const char* nuevo);
    void setApellido(const char* nuevo);
    void setCedula(const char* nuevo);
    void setEspecialidad(const char* nuevo);
    void setAniosExperiencia(int exp);
    void setCostoConsulta(float costo);
    void setDisponible(bool estado);

    // ===== Validaciones =====
    bool validarDatos() const;
    bool cedulaEsValida() const;
    bool especialidadEsValida() const;

    // ===== Gestión de pacientes asignados =====
    void asignarPaciente(int idPaciente);
    bool tienePacientes() const;

    // ===== Presentación =====
    void mostrarInformacionBasica() const;
    void mostrarInformacionCompleta() const;

    // ===== Persistencia =====
    static size_t obtenerTamano();
    void guardarBinario(std::ofstream& out) const;
    void cargarBinario(std::ifstream& in);
};

#endif
