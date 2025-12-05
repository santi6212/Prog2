#ifndef PACIENTES_HPP
#define PACIENTES_HPP

#include <cstring>
#include <vector>
#include <fstream>
#include "../historial/historial.hpp"

class Paciente {
private:
    int id;
    char nombre[50];
    char apellido[50];
    char cedula[20];
    int edad;
    char sexo;
    char tipoSangre[5];
    char telefono[15];
    char direccion[100];
    char email[50];
    char alergias[200];
    char observaciones[200];
    bool activo;

    std::vector<HistorialMedico> historial;

public:
    // ===== Constructores =====
    Paciente();
    Paciente(int id, const char* nombre, const char* apellido, const char* cedula);
    Paciente(const Paciente& other);
    ~Paciente();

    // ===== Getters =====
    int getId() const;
    const char* getNombre() const;
    const char* getApellido() const;
    const char* getCedula() const;
    int getEdad() const;
    char getSexo() const;
    const char* getTipoSangre() const;
    const char* getTelefono() const;
    const char* getDireccion() const;
    const char* getEmail() const;
    const char* getAlergias() const;
    const char* getObservaciones() const;
    bool estaActivo() const;

    const std::vector<HistorialMedico>& getHistorial() const;

    // ===== Setters =====
    void setNombre(const char* nuevo);
    void setApellido(const char* nuevo);
    void setCedula(const char* nuevo);
    void setEdad(int nuevaEdad);
    void setSexo(char nuevoSexo);
    void setTipoSangre(const char* nuevo);
    void setTelefono(const char* nuevo);
    void setDireccion(const char* nuevo);
    void setEmail(const char* nuevo);
    void setAlergias(const char* nuevo);
    void setObservaciones(const char* nuevo);
    void setActivo(bool estado);

    // ===== Validaciones =====
    bool validarDatos() const;
    bool cedulaEsValida() const;
    bool esMayorDeEdad() const;

    // ===== Historial =====
    void agregarConsulta(const HistorialMedico& consulta);
    bool tieneHistorial() const;

    // ===== Presentación =====
    void mostrarInformacionBasica() const;
    void mostrarInformacionCompleta() const;

    // ===== Persistencia =====
    static size_t obtenerTamano();
    void guardarBinario(std::ofstream& out) const;
    void cargarBinario(std::ifstream& in);
};
#endif
