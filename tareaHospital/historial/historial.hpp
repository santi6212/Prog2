#ifndef HISTORIAL_HPP
#define HISTORIAL_HPP

#include <cstring>
#include <fstream>

class HistorialMedico {
private:
    int idConsulta;
    int idPaciente;
    char fecha[11];        // YYYY-MM-DD
    char hora[6];          // HH:MM
    char diagnostico[200];
    char tratamiento[200];
    char medicamentos[150];
    int idDoctor;
    float costo;

public:
    // ===== Constructores =====
    HistorialMedico();
   HistorialMedico(int idConsulta, int idPaciente, const char* fecha, const char* hora,
                const char* diagnostico, const char* tratamiento,
                const char* medicamentos, int idDoctor, float costo);
    HistorialMedico(const HistorialMedico& other);
    ~HistorialMedico();

    // ===== Getters =====
    int getIdConsulta() const;
    int getIdPaciente() const; 
    const char* getFecha() const;
    const char* getHora() const;
    const char* getDiagnostico() const;
    const char* getTratamiento() const;
    const char* getMedicamentos() const;
    int getIdDoctor() const;
    float getCosto() const;

    // ===== Setters =====
    void setIdPaciente(int id);
    void setFecha(const char* nuevaFecha);
    void setHora(const char* nuevaHora);
    void setDiagnostico(const char* nuevo);
    void setTratamiento(const char* nuevo);
    void setMedicamentos(const char* nuevo);
    void setIdDoctor(int id);
    void setCosto(float nuevoCosto);

    // ===== Validaciones =====
    bool validarFecha() const;
    bool validarHora() const;
    bool validarDatos() const;

    // ===== Presentación =====
    void mostrarInformacion() const;

    // ===== Persistencia =====
    static size_t obtenerTamano();
    void guardarBinario(std::ofstream& out) const;
    void cargarBinario(std::ifstream& in);
};

#endif
