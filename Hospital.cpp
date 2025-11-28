#include <iostream>
#include <cstring>
#include <ctime>
#include <iomanip>
#include <cctype> 
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <fstream>
#include <limits>
#include <stdexcept>
#include <windows.h>
using namespace std;
inline void setText(char* dest, const char* src, size_t maxLen) {
    if (!src) { dest[0] = '\0'; return; }
    strncpy(dest, src, maxLen - 1);
    dest[maxLen - 1] = '\0';
}
class Validaciones {
public:
    static bool esBisiesto(int anio) {
        return (anio % 4 == 0 && anio % 100 != 0) || (anio % 400 == 0);
    }

    static bool validarFecha(const char* fecha) {
        if (strlen(fecha) != 10 || fecha[4] != '-' || fecha[7] != '-') return false;

        char anioStr[5], mesStr[3], diaStr[3];
        strncpy(anioStr, fecha, 4); anioStr[4] = '\0';
        strncpy(mesStr, fecha + 5, 2); mesStr[2] = '\0';
        strncpy(diaStr, fecha + 8, 2); diaStr[2] = '\0';

        int anio = atoi(anioStr);
        int mes = atoi(mesStr);
        int dia = atoi(diaStr);

        if (mes < 1 || mes > 12) return false;

        int diasEnMes[] = {0,31,28,31,30,31,30,31,31,30,31,30,31};
        if (mes == 2 && esBisiesto(anio)) diasEnMes[2] = 29;

        return dia >= 1 && dia <= diasEnMes[mes];
    }

    static bool validarHora(const char* hora) {
        if (strlen(hora) != 5 || hora[2] != ':') return false;
        if (!isdigit(hora[0]) || !isdigit(hora[1]) || !isdigit(hora[3]) || !isdigit(hora[4])) return false;

        int h = (hora[0]-'0')*10 + (hora[1]-'0');
        int m = (hora[3]-'0')*10 + (hora[4]-'0');
        return (h >= 0 && h < 24) && (m >= 0 && m < 60);
    }

    static int compararFechas(const char* f1, const char* f2) {
        int r = strcmp(f1, f2);
        if (r < 0) return -1;
        if (r > 0) return 1;
        return 0;
    }

    static bool validarCedula(const char* cedula) {
        return cedula && strlen(cedula) > 0 && strlen(cedula) <= 20;
    }

    static bool validarEmail(const char* email) {
        if (!email || strlen(email) == 0) return false;
        const char* at = strchr(email, '@');
        const char* dot = strrchr(email, '.');
        if (!at || !dot) return false;
        return dot > at && at != email && dot != email + strlen(email) - 1;
    }
};
class HistorialMedico {
public:
    int idConsulta;
    char fecha[11];
    char hora[6];
    char diagnostico[200];
    char tratamiento[200];
    char medicamentos[150];
    int idDoctor;
    float costo;

    HistorialMedico() : idConsulta(0), idDoctor(0), costo(0.0f) {
        strcpy(fecha, "");
        strcpy(hora, "");
        strcpy(diagnostico, "");
        strcpy(tratamiento, "");
        strcpy(medicamentos, "");
    }

    void guardarBinario(ofstream& out) const {
        out.write(reinterpret_cast<const char*>(this), sizeof(HistorialMedico));
    }

    void cargarBinario(ifstream& in) {
        in.read(reinterpret_cast<char*>(this), sizeof(HistorialMedico));
    }
};
//1.2 paciente

class Paciente {
public:
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

	vector<HistorialMedico> historial;
	 
    Paciente() : id(0), edad(0), sexo(' '), activo(true) {
        strcpy(nombre, "");
        strcpy(apellido, "");
        strcpy(cedula, "");
        strcpy(tipoSangre, "");
        strcpy(telefono, "");
        strcpy(direccion, "");
        strcpy(email, "");
        strcpy(alergias, "");
        strcpy(observaciones, "");
    }

    void guardarBinario(ofstream& out) const {
    out.write(reinterpret_cast<const char*>(this), sizeof(Paciente));
    int tam = historial.size();
    out.write(reinterpret_cast<const char*>(&tam), sizeof(int));
    for (const auto& h : historial) h.guardarBinario(out);
}

	void cargarBinario(ifstream& in) {
    in.read(reinterpret_cast<char*>(this), sizeof(Paciente));
    int tam;
    in.read(reinterpret_cast<char*>(&tam), sizeof(int));
    historial.clear();
    for (int i = 0; i < tam; ++i) {
        HistorialMedico h;
        h.cargarBinario(in);
        historial.push_back(h);
    }
}
};


//1.4 doctor
class Doctor {
public:
    int id;
    char nombre[50];
    char apellido[50];
    char cedula[20];
    char especialidad[50];
    int aniosExperiencia;
    float costoConsulta;
    bool disponible;

	 vector<int> pacientesAsignados;
	
    Doctor() : id(0), aniosExperiencia(0), costoConsulta(0.0f), disponible(true) {
        strcpy(nombre, "");
        strcpy(apellido, "");
        strcpy(cedula, "");
        strcpy(especialidad, "");
    }

    void guardarBinario(ofstream& out) const {
        out.write(reinterpret_cast<const char*>(this), sizeof(Doctor));
    }

    void cargarBinario(ifstream& in) {
        in.read(reinterpret_cast<char*>(this), sizeof(Doctor));
    }
};
//1.5 citas
class Cita {
public:
    int id;
    int idPaciente;
    int idDoctor;
    char fecha[11];
    char hora[6];
    char motivo[150];
    char estado[20];
    char observaciones[200];
    bool atendida;

    Cita() : id(0), idPaciente(0), idDoctor(0), atendida(false) {
        strcpy(fecha, "");
        strcpy(hora, "");
        strcpy(motivo, "");
        strcpy(estado, "agendada");
        strcpy(observaciones, "");
    }

    void guardarBinario(ofstream& out) const {
        out.write(reinterpret_cast<const char*>(this), sizeof(Cita));
    }

    void cargarBinario(ifstream& in) {
        in.read(reinterpret_cast<char*>(this), sizeof(Cita));
    }
};
//hospital
class Hospital {
private:
    char nombre[100];
    char direccion[150];
    char telefono[15];

    vector<Paciente> pacientes;
    vector<Doctor> doctores;
    vector<Cita> citas;

    int siguienteIdPaciente;
    int siguienteIdDoctor;
    int siguienteIdCita;
    int siguienteIdConsulta;

public:
    Hospital(const char* nom="Hospital", const char* dir="La Rotaria", const char* tel="1234")
        : siguienteIdPaciente(1), siguienteIdDoctor(1),
          siguienteIdCita(1), siguienteIdConsulta(1) {
        strcpy(nombre, nom);
        strcpy(direccion, dir);
        strcpy(telefono, tel);
    }

    void mostrarInfo() const {
        cout << "=== " << nombre << " ===" << endl;
        cout << "Direccion: " << direccion << endl;
        cout << "Telefono: " << telefono << endl;
        cout << "Pacientes registrados: " << pacientes.size() << endl;
        cout << "Doctores registrados: " << doctores.size() << endl;
        cout << "Citas registradas: " << citas.size() << endl;
    }

// ---------- Validaciones ----------
    bool validarCedula(const char* ced) const {
        if (!ced || !*ced) return false;
        if (strlen(ced) > 19) return false;
        return true;
    }
    bool validarSexo(char s) const {
        s = toupper(static_cast<unsigned char>(s));
        return s=='M' || s=='F';
    }
    bool validarEdad(int e) const { return e > 0 && e <= 150; }
    
//pacientes

 Paciente& crearPaciente(const char* nom, const char* ape, const char* ced, int edad, char sexo) {
        Paciente p;
        p.id = siguienteIdPaciente++;
        strncpy(p.nombre, nom, sizeof(p.nombre)-1);
        strncpy(p.apellido, ape, sizeof(p.apellido)-1);
        strncpy(p.cedula, ced, sizeof(p.cedula)-1);
        p.edad = edad;
        p.sexo = sexo;
        pacientes.push_back(p);
        return pacientes.back();
    }

    // Buscar por ID ? devuelve índice
    int buscarPacientePorId(int id) const {
        for (size_t i = 0; i < pacientes.size(); ++i) {
            if (pacientes[i].id == id) return static_cast<int>(i);
        }
        return -1; // no encontrado
    }

    // Buscar por cédula ? devuelve índice
    int buscarPacientePorCedula(const char* ced) const {
        for (size_t i = 0; i < pacientes.size(); ++i) {
            if (strcmp(pacientes[i].cedula, ced) == 0) return static_cast<int>(i);
        }
        return -1;
    }
    // ---------- Actualizar (interactivo) ----------
  bool actualizarPacienteInteractivo(int id) {
    int idx = buscarPacientePorId(id);
    if (idx == -1) {
        cout << "Error: No se encontró paciente con ID " << id << endl;
        return false;
    }
    Paciente& paciente = pacientes[idx];

    cout << "\n=== ACTUALIZAR DATOS DEL PACIENTE ===\n";
    cout << "Paciente: " << paciente.nombre << " " << paciente.apellido << "\n";
    cout << "Deje en blanco para mantener el valor actual\n\n";

    char buffer[256];

    auto leerCampo = [&](const char* etiqueta, char* campo, size_t maxLen) {
        cout << etiqueta << " actual: " << campo << "\nNuevo: ";
        cin.getline(buffer, sizeof(buffer));
        if (strlen(buffer) > 0) setText(campo, buffer, maxLen);
    };

    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // limpiar

    leerCampo("Nombre", paciente.nombre, sizeof(paciente.nombre));
    leerCampo("Apellido", paciente.apellido, sizeof(paciente.apellido));

    cout << "Edad actual: " << paciente.edad << "\nNueva edad: ";
    cin.getline(buffer, sizeof(buffer));
    if (strlen(buffer) > 0) {
        int e = atoi(buffer);
        if (validarEdad(e)) paciente.edad = e;
        else cout << "Edad no válida. Manteniendo valor actual.\n";
    }

    cout << "Sexo actual: " << paciente.sexo << "\nNuevo sexo (M/F): ";
    cin.getline(buffer, sizeof(buffer));
    if (strlen(buffer) > 0) {
        char s = toupper(static_cast<unsigned char>(buffer[0]));
        if (validarSexo(s)) paciente.sexo = s;
        else cout << "Sexo no válido. Manteniendo valor actual.\n";
    }

    leerCampo("Telefono", paciente.telefono, sizeof(paciente.telefono));
    leerCampo("Direccion", paciente.direccion, sizeof(paciente.direccion));
    leerCampo("Email", paciente.email, sizeof(paciente.email));
    leerCampo("Tipo de sangre", paciente.tipoSangre, sizeof(paciente.tipoSangre));
    leerCampo("Alergias", paciente.alergias, sizeof(paciente.alergias));
    leerCampo("Observaciones", paciente.observaciones, sizeof(paciente.observaciones));

    cout << "\nDatos del paciente actualizados correctamente.\n";
    return true;
}

   // Eliminar paciente
    bool eliminarPaciente(int id) {
        int idx = buscarPacientePorId(id);
        if (idx == -1) return false;
        pacientes.erase(pacientes.begin() + idx);
        return true;
    }
    // ---------- Listar ----------
    void listarPacientes() const {
        if (pacientes.empty()) {
            cout << "No hay pacientes registrados.\n";
            return;
        }
        printf("| %-4s | %-25s | %-15s | %-5s | %-8s |\n",
               "ID", "NOMBRE COMPLETO", "CEDULA", "EDAD", "SEXO");
        for (const auto& p : pacientes) {
            char nombreCompleto[101];
            snprintf(nombreCompleto, sizeof(nombreCompleto), "%s %s", p.nombre, p.apellido);
            printf("| %-4d | %-25s | %-15s | %-5d | %-8c |\n",
                   p.id, nombreCompleto, p.cedula, p.edad, p.sexo);
        }
    }
    
//historial

// Agregar consulta
void agregarConsultaAlHistorial(Paciente& paciente, const HistorialMedico& consulta) {
    paciente.historial.push_back(consulta);
    cout << "Consulta agregada. Total: " << paciente.historial.size() << endl;
}

// Obtener historial completo
vector<HistorialMedico>& obtenerHistorialCompleto(Paciente& paciente) {
    return paciente.historial;
}

// Mostrar historial
void mostrarHistorialMedico(const Paciente& paciente) {
    if (paciente.historial.empty()) {
        cout << "El paciente ID " << paciente.id << " no tiene consultas registradas." << endl;
        return;
    }

    cout << "\n--- HISTORIAL MÉDICO DEL PACIENTE ID " << paciente.id
         << " (" << paciente.nombre << " " << paciente.apellido << ") ---" << endl;

    printf("| %-4s | %-10s | %-5s | %-30s | %-15s | %-8s |\n",
           "ID", "FECHA", "HORA", "DIAGNOSTICO", "DOCTOR ID", "COSTO");
    cout << "-----------------------------------------------------------------------------------" << endl;

    for (const auto& h : paciente.historial) {
        printf("| %-4d | %-10s | %-5s | %-30s | %-15d | $%-7.2f |\n",
               h.idConsulta, h.fecha, h.hora, h.diagnostico, h.idDoctor, h.costo);
    }
    cout << "-----------------------------------------------------------------------------------" << endl;
}

// Obtener última consulta
HistorialMedico* obtenerUltimaConsulta(Paciente& paciente) {
    if (paciente.historial.empty()) return nullptr;
    return &paciente.historial.back();
}
    // ---------- Persistencia específica de pacientes ----------
    void guardarPacientesBin() const {
        ofstream out("pacientes.bin", ios::binary);
        for (const auto& p : pacientes) p.guardarBinario(out);
        out.close();
    }
    void cargarPacientesBin() {
        pacientes.clear();
    ifstream in("pacientes.bin", ios::binary);
    while (in.peek() != EOF) {
        Paciente p;
        p.cargarBinario(in);   // <-- usa el método correcto
        pacientes.push_back(p);
        if (p.id >= siguienteIdPaciente) siguienteIdPaciente = p.id + 1;
    }
    in.close();
    }

    // Guardar todo en binario
    void guardarTodo() const {
        ofstream outPac("pacientes.bin", ios::binary);
        for (const auto& p : pacientes) p.guardarBinario(outPac);
        outPac.close();

        ofstream outDoc("doctores.bin", ios::binary);
        for (const auto& d : doctores) d.guardarBinario(outDoc);
        outDoc.close();

        ofstream outCit("citas.bin", ios::binary);
        for (const auto& c : citas) c.guardarBinario(outCit);
        outCit.close();
    }

    // Cargar todo desde binario
    void cargarTodo() {
        pacientes.clear();
        doctores.clear();
        citas.clear();

        ifstream inPac("pacientes.bin", ios::binary);
        Paciente p;
        while (inPac.read(reinterpret_cast<char*>(&p), sizeof(Paciente))) {
            pacientes.push_back(p);
        }
        inPac.close();

        ifstream inDoc("doctores.bin", ios::binary);
        Doctor d;
        while (inDoc.read(reinterpret_cast<char*>(&d), sizeof(Doctor))) {
            doctores.push_back(d);
        }
        inDoc.close();

        ifstream inCit("citas.bin", ios::binary);
        Cita c;
        while (inCit.read(reinterpret_cast<char*>(&c), sizeof(Cita))) {
            citas.push_back(c);
        }
        inCit.close();
    }
    
    //doctor

    Doctor& crearDoctor(const char* nombre, const char* apellido, const char* cedula,
                        const char* especialidad, int aniosExperiencia, float costoConsulta) {
        // Validar duplicado
        for (auto& d : doctores) {
            if (strcmp(d.cedula, cedula) == 0) {
                cerr << "Ya existe un doctor con la cédula " << cedula << endl;
                throw runtime_error("Doctor duplicado");
            }
        }

        Doctor d;
        d.id = siguienteIdDoctor++;
        strncpy(d.nombre, nombre, sizeof(d.nombre)-1);
        strncpy(d.apellido, apellido, sizeof(d.apellido)-1);
        strncpy(d.cedula, cedula, sizeof(d.cedula)-1);
        strncpy(d.especialidad, especialidad, sizeof(d.especialidad)-1);
        d.aniosExperiencia = aniosExperiencia;
        d.costoConsulta = costoConsulta;

        doctores.push_back(d);
        return doctores.back();
    }

    Doctor* buscarDoctorPorId(int id) {
        for (auto& d : doctores) {
            if (d.id == id) return &d;
        }
        return nullptr;
    }

    Doctor* buscarDoctorPorCedula(const char* cedula) {
        for (auto& d : doctores) {
            if (strcmp(d.cedula, cedula) == 0) return &d;
        }
        return nullptr;
    }

    void listarDoctores() const {
        if (doctores.empty()) {
            cout << "No hay doctores registrados.\n";
            return;
        }
        printf("| %-4s | %-25s | %-15s | %-15s | %-10s | %-8s |\n",
               "ID", "NOMBRE COMPLETO", "CEDULA", "ESPECIALIDAD", "CONSULTA", "EXP.");
        for (const auto& d : doctores) {
            char nombreCompleto[101];
            snprintf(nombreCompleto, 101, "%s %s", d.nombre, d.apellido);
            printf("| %-4d | %-25s | %-15s | %-15s | $%-8.2f | %-8d |\n",
                   d.id, nombreCompleto, d.cedula, d.especialidad, d.costoConsulta, d.aniosExperiencia);
        }
    }

    void guardarDoctoresBin() const {
        ofstream out("doctores.bin", ios::binary);
        for (const auto& d : doctores) d.guardarBinario(out);
        out.close();
    }

    void cargarDoctoresBin() {
       doctores.clear();
    ifstream in("doctores.bin", ios::binary);
    while (in.peek() != EOF) {
        Doctor d;
        d.cargarBinario(in);   // usar método de la clase
        if (!in) break;        // evita push_back si la lectura falló
        doctores.push_back(d);
        if (d.id >= siguienteIdDoctor) siguienteIdDoctor = d.id + 1;
    }
    in.close();
    }
    
    //citas
    
    // Agendar cita
    Cita* agendarCita(int idPaciente, int idDoctor,
                      const char* fecha, const char* hora, const char* motivo) {
                      	
  if (!Validaciones::validarFecha(fecha)) {
        cerr << "Error: Fecha inválida (YYYY-MM-DD)." << endl;
        return nullptr;
    }
    if (!Validaciones::validarHora(hora)) {
        cerr << "Error: Hora inválida (HH:MM)." << endl;
        return nullptr;
    }
    if (!verificarDisponibilidad(idDoctor, fecha, hora)) {
        cerr << "Error: Doctor ocupado en ese horario." << endl;
        return nullptr;
    }
    
        Cita c;
        c.id = siguienteIdCita++;
        c.idPaciente = idPaciente;
        c.idDoctor = idDoctor;
        strncpy(c.fecha, fecha, sizeof(c.fecha)-1);
        strncpy(c.hora, hora, sizeof(c.hora)-1);
        strncpy(c.motivo, motivo, sizeof(c.motivo)-1);
        citas.push_back(c);
        return &citas.back();
    }

    // Buscar cita por ID
    Cita* buscarCitaPorId(int id) {
        for (auto& c : citas) {
            if (c.id == id) return &c;
        }
        return nullptr;
    }

    // Cancelar cita
    bool cancelarCita(int idCita) {
        Cita* cita = buscarCitaPorId(idCita);
        if (!cita) return false;
        strcpy(cita->estado, "cancelada");
        return true;
    }

    // Atender cita
    bool atenderCita(int idCita) {
        Cita* cita = buscarCitaPorId(idCita);
        if (!cita) return false;
        strcpy(cita->estado, "atendida");
        cita->atendida = true;
        return true;
    }

    // Listar citas
    void listarCitas() const {
        if (citas.empty()) {
            cout << "No hay citas registradas.\n";
            return;
        }
        printf("| %-4s | %-10s | %-5s | %-10s | %-10s | %-15s |\n",
               "ID", "FECHA", "HORA", "PACIENTE", "DOCTOR", "MOTIVO");
        cout << "-------------------------------------------------------------------------------\n";
        for (const auto& c : citas) {
            printf("| %-4d | %-10s | %-5s | %-10d | %-10d | %-15s |\n",
                   c.id, c.fecha, c.hora, c.idPaciente, c.idDoctor, c.motivo);
        }
    }

    // Guardar en binario
    void guardarCitasBin() const {
        ofstream out("citas.bin", ios::binary);
        for (const auto& c : citas) c.guardarBinario(out);
        out.close();
    }

    // Cargar desde binario
    void cargarCitasBin() {
       citas.clear();
    ifstream in("citas.bin", ios::binary);
    while (in.peek() != EOF) {
        Cita c;
        c.cargarBinario(in);   // usar método de la clase
        if (!in) break;        // evita push_back si la lectura falló
        citas.push_back(c);
        if (c.id >= siguienteIdCita) siguienteIdCita = c.id + 1;
    }
    in.close();
    }
    
    bool verificarDisponibilidad(int idDoctor, const char* fecha, const char* hora) {
    for (const auto& c : citas) {
        if (strcmp(c.estado, "agendada") == 0 &&
            c.idDoctor == idDoctor &&
            strcmp(c.fecha, fecha) == 0 &&
            strcmp(c.hora, hora) == 0) {
            return false; // Ya ocupado
        }
    }
    return true; // Disponible
}

bool validarFormatoFecha(const char* fecha) {
    // Formato esperado: YYYY-MM-DD
    if (strlen(fecha) != 10) return false;
    if (fecha[4] != '-' || fecha[7] != '-') return false;

    // Verificar que los demás caracteres sean dígitos
    for (int i = 0; i < 10; ++i) {
        if (i == 4 || i == 7) continue;
        if (!isdigit(fecha[i])) return false;
    }
    return true;
}

bool validarFormatoHora(const char* hora) {
    // Formato esperado: HH:MM
    if (strlen(hora) != 5) return false;
    if (hora[2] != ':') return false;

    if (!isdigit(hora[0]) || !isdigit(hora[1]) ||
        !isdigit(hora[3]) || !isdigit(hora[4])) return false;

    int hh = (hora[0]-'0')*10 + (hora[1]-'0');
    int mm = (hora[3]-'0')*10 + (hora[4]-'0');

    return (hh >= 0 && hh < 24) && (mm >= 0 && mm < 60);
}


};

//6

void menuPacientes(Hospital* hospital);
void menuDoctores(Hospital* hospital);
void menuCitas(Hospital* hospital);

// Funciones auxiliares para mostrar títulos y leer opciones
void mostrarTitulo(const string& titulo) {
    cout << "\n" << setfill('=') << setw(80) << "" << endl;
    cout << titulo << endl;
    cout << setfill('=') << setw(80) << "" << endl;
}

int leerOpcion(int min, int max) {
    int opcion;
    cout << "Seleccione una opcion: ";
    if (!(cin >> opcion)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return -1;
    }
    if (opcion < min || opcion > max) {
        cout << "Opcion invalida.\n";
        return -1;
    }
    return opcion;
}

// ---------------- MENÚ PRINCIPAL ----------------
void menuPrincipal(Hospital* hospital) {
    int opcion;
    do {
    	system("cls");
        hospital->mostrarInfo();
        mostrarTitulo("SISTEMA DE GESTION HOSPITALARIA");
        cout << "1. Gestion de Pacientes\n";
        cout << "2. Gestion de Doctores\n";
        cout << "3. Gestion de Citas\n";
        cout << "4. Salir\n";
        cout << setfill('-') << setw(80) << "" << endl;

        opcion = leerOpcion(1, 4);
        if (opcion == -1) continue;

        switch (opcion) {
            case 1: menuPacientes(hospital); break;
            case 2: menuDoctores(hospital); break;
            case 3: menuCitas(hospital); break;
            case 4: cout << "\n? Saliendo del sistema. ¡Hasta pronto!\n"; 
			 system("pause");
			break;
        }
        
    } while (opcion != 4);
}

// ---------------- MENÚ PACIENTES ----------------
void menuPacientes(Hospital* hospital) {
    int opcion;
    do {
    	system("cls");
        mostrarTitulo("MENU DE GESTIÓN DE PACIENTES");
        cout << "1. Registrar nuevo paciente\n";
        cout << "2. Buscar paciente por cédula\n";
        cout << "3. Listar todos los pacientes\n";
        cout << "4. Eliminar paciente\n";
        cout << "0. Volver al menu principal\n";
        cout << setfill('-') << setw(80) << "" << endl;

        opcion = leerOpcion(0, 4);
        if (opcion == -1) continue;

        switch (opcion) {
            case 1: {
                string nombre, apellido, cedula;
                int edad; char sexo;
                cout << "Nombre: "; cin >> nombre;
                cout << "Apellido: "; cin >> apellido;
                cout << "Cedula: "; cin >> cedula;
                cout << "Edad: "; cin >> edad;
                cout << "Sexo (M/F): "; cin >> sexo;
                hospital->crearPaciente(nombre.c_str(), apellido.c_str(), cedula.c_str(), edad, sexo);
                hospital->guardarPacientesBin();
                system("pause");
                break;
            }
            case 2: {
                string cedula;
                cout << "Ingrese cedula: "; cin >> cedula;
                int idx = hospital->buscarPacientePorCedula(cedula.c_str());
                if (idx != -1) cout << "Paciente encontrado.\n";
                else cout << "No existe paciente con esa cédula.\n";
                system("pause");
                break;
            }
            case 3: hospital->listarPacientes(); 
			system("pause");
			break;
            case 4: {
                int id;
                cout << "ID del paciente a eliminar: "; cin >> id;
                if (hospital->eliminarPaciente(id)) cout << "Paciente eliminado.\n";
                else cout << "Paciente no encontrado.\n";
                hospital->guardarPacientesBin();
                system("pause");
                break;
            }
        }
    } while (opcion != 0);
}

// ---------------- MENÚ DOCTORES ----------------
void menuDoctores(Hospital* hospital) {
    int opcion;
    do {
    	system("cls");
        mostrarTitulo("MENÚ DE GESTIÓN DE DOCTORES");
        cout << "1. Registrar nuevo doctor\n";
        cout << "2. Buscar doctor por ID\n";
        cout << "3. Listar todos los doctores\n";
        cout << "0. Volver al menú principal\n";
        cout << setfill('-') << setw(80) << "" << endl;

        opcion = leerOpcion(0, 3);
        if (opcion == -1) continue;

        switch (opcion) {
            case 1: {
                string nombre, apellido, cedula, especialidad;
                int exp; float costo;
                cout << "Nombre: "; cin >> nombre;
                cout << "Apellido: "; cin >> apellido;
                cout << "Cedula: "; cin >> cedula;
                cout << "Especialidad: "; cin >> especialidad;
                cout << "Años de experiencia: "; cin >> exp;
                cout << "Costo consulta: "; cin >> costo;
                hospital->crearDoctor(nombre.c_str(), apellido.c_str(), cedula.c_str(),
                                      especialidad.c_str(), exp, costo);
                hospital->guardarDoctoresBin();
                system("pause");
                break;
            }
            case 2: {
                int id;
                cout << "Ingrese ID del doctor: "; cin >> id;
                Doctor* d = hospital->buscarDoctorPorId(id);
                if (d) cout << "Doctor encontrado: " << d->nombre << " " << d->apellido << endl;
                else cout << "No existe doctor con ese ID.\n";
                system("pause");
                break;
            }
            case 3: hospital->listarDoctores(); 
            system("pause");
			break;
        }
    } while (opcion != 0);
}

// ---------------- MENÚ CITAS ----------------
void menuCitas(Hospital* hospital) {
    int opcion;
    do {
    	system("cls");
        mostrarTitulo("MENU DE GESTIÓN DE CITAS");
        cout << "1. Agendar nueva cita\n";
        cout << "2. Cancelar cita\n";
        cout << "3. Atender cita\n";
        cout << "4. Listar todas las citas\n";
        cout << "0. Volver al menú principal\n";
        cout << setfill('-') << setw(80) << "" << endl;

        opcion = leerOpcion(0, 4);
        if (opcion == -1) continue;

        switch (opcion) {
            case 1: {
                int idPaciente, idDoctor; string fecha, hora, motivo;
                cout << "ID Paciente: "; cin >> idPaciente;
                cout << "ID Doctor: "; cin >> idDoctor;
                cout << "Fecha (YYYY-MM-DD): "; cin >> fecha;
                cout << "Hora (HH:MM): "; cin >> hora;
                cout << "Motivo: "; cin.ignore(); getline(cin, motivo);
                Cita* c = hospital->agendarCita(idPaciente, idDoctor,
                                                fecha.c_str(), hora.c_str(), motivo.c_str());
                if (c) {
                    cout << "? Cita agendada con ID " << c->id << endl;
                    hospital->guardarCitasBin();
                }
                system("pause");
                break;
            }
            case 2: {
                int idCita; cout << "ID de la cita a cancelar: "; cin >> idCita;
                if (hospital->cancelarCita(idCita)) cout << "Cita cancelada.\n";
                else cout << "No se encontro la cita.\n";
                hospital->guardarCitasBin();
                system("pause");
                break;
            }
            case 3: {
                int idCita; cout << "ID de la cita a atender: "; cin >> idCita;
                if (hospital->atenderCita(idCita)) cout << "Cita atendida.\n";
                else cout << "No se encontro la cita.\n";
                hospital->guardarCitasBin();
                system("pause");
                break;
            }
            case 4: hospital->listarCitas(); 
			system("pause");
			break;
        }
    } while (opcion != 0);
}


int main() {
    // Crear hospital
    Hospital hospital("Hospital Central de Morioh", "La Rotaria", "0412-1999087");

    // Cargar datos previos desde ficheros binarios
    hospital.cargarPacientesBin();
    hospital.cargarDoctoresBin();
    hospital.cargarCitasBin();

    // Mostrar información inicial
    hospital.mostrarInfo();

    // Lanzar menú principal
    menuPrincipal(&hospital);

    // Guardar todo antes de salir
    hospital.guardarPacientesBin();
    hospital.guardarDoctoresBin();
    hospital.guardarCitasBin();

    cout << "\n? Datos guardados correctamente. Programa finalizado.\n";
    
    return 0;
}
