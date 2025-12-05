#ifndef CITAS_HPP
#define CITAS_HPP

#include <cstring>
#include <fstream>

class Cita {
private:
    int id;
    int idPaciente;
    int idDoctor;
    char fecha[11];     // YYYY-MM-DD
    char hora[6];       // HH:MM
    char motivo[150];
    char estado[20];    // agendada, cancelada, atendida
    char observaciones[200];
    bool atendida;

public:
    // ===== Constructores =====
    Cita();
    Cita(int id, int idPaciente, int idDoctor,
         const char* fecha, const char* hora, const char* motivo);
    Cita(const Cita& other);
    ~Cita();

    // ===== Getters =====
    int getId() const;
    int getIdPaciente() const;
    int getIdDoctor() const;
    const char* getFecha() const;
    const char* getHora() const;
    const char* getMotivo() const;
    const char* getEstado() const;
    const char* getObservaciones() const;
    bool estaAtendida() const;

    // ===== Setters =====
    void setFecha(const char* nuevaFecha);
    void setHora(const char* nuevaHora);
    void setMotivo(const char* nuevoMotivo);
    void setEstado(const char* nuevoEstado);
    void setObservaciones(const char* nuevo);
    void setAtendida(bool valor);

    // ===== Validaciones =====
    bool validarFecha() const;
    bool validarHora() const;
    bool validarDatos() const;

    // ===== Gestión =====
    void marcarComoAtendida();
    void cancelar();

    // ===== Presentación =====
    void mostrarInformacion() const;

    // ===== Persistencia =====
    static size_t obtenerTamano();
    void guardarBinario(std::ofstream& out) const;
    void cargarBinario(std::ifstream& in);
};
#endif
