#ifndef HOSPITAL_HPP
#define HOSPITAL_HPP

#include <cstring>
#include <iostream>

class Hospital {
private:
    char nombre[100];
    char direccion[150];
    char telefono[20];

    // Contadores globales de IDs
    int siguienteIdPaciente;
    int siguienteIdDoctor;
    int siguienteIdCita;
    int siguienteIdConsulta;

public:
    // ===== Constructores =====
    Hospital();
    Hospital(const char* nombre, const char* direccion, const char* telefono);
    Hospital(const Hospital& other);
    ~Hospital();

    // ===== Getters =====
    const char* getNombre() const;
    const char* getDireccion() const;
    const char* getTelefono() const;

    int getSiguienteIdPaciente() const;
    int getSiguienteIdDoctor() const;
    int getSiguienteIdCita() const;
    int getSiguienteIdConsulta() const;

    // ===== Setters =====
    void setNombre(const char* nuevo);
    void setDireccion(const char* nuevo);
    void setTelefono(const char* nuevo);

    void setSiguienteIdPaciente(int id);
    void setSiguienteIdDoctor(int id);
    void setSiguienteIdCita(int id);
    void setSiguienteIdConsulta(int id);

    // ===== Generadores de ID =====
    int generarIdPaciente();
    int generarIdDoctor();
    int generarIdCita();
    int generarIdConsulta();

    // ===== Presentación =====
    void mostrarInformacion() const;

    // ===== Persistencia =====
    static size_t obtenerTamano();
    void guardarBinario(std::ofstream& out) const;
    void cargarBinario(std::ifstream& in);
};

#endif
