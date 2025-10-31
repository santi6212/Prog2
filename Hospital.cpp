#include <iostream>
#include <cstring>
#include <ctime>
#include <iomanip>

using namespace std;

struct Hospital {
    char nombre[100];
    char direccion[150];
    char telefono[15];
    
    Paciente* pacientes;
    int cantidadPacientes;
    int capacidadPacientes;
    
    Doctor* doctores;
    int cantidadDoctores;
    int capacidadDoctores;
    
    Cita* citas;
    int cantidadCitas;
    int capacidadCitas;
    
    int siguienteIdPaciente;
    int siguienteIdDoctor;
    int siguienteIdCita;
    int siguienteIdConsulta;
};

struct Paciente {
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
    
    HistorialMedico* historial;
    int cantidadConsultas;
    int capacidadHistorial;
    
    int* citasAgendadas;
    int cantidadCitas;
    int capacidadCitas;
    
    char alergias[500];
    char observaciones[500];
    
    bool activo;
};

struct HistorialMedico {
    int idConsulta;
    char fecha[11];
    char hora[6];
    char diagnostico[200];
    char tratamiento[200];
    char medicamentos[150];
    int idDoctor;
    float costo;
};

struct Doctor {
    int id;
    char nombre[50];
    char apellido[50];
    char cedula[20];
    char especialidad[50];
    int aniosExperiencia;
    float costoConsulta;
    char horarioAtencion[50];
    char telefono[15];
    char email[50];
    
    int* pacientesAsignados;
    int cantidadPacientes;
    int capacidadPacientes;
    
    int* citasAgendadas;
    int cantidadCitas;
    int capacidadCitas;
    
    bool disponible;
};

struct Cita {
    int id;
    int idPaciente;
    int idDoctor;
    char fecha[11];
    char hora[6];
    char motivo[150];
    char estado[20];
    char observaciones[200];
    bool atendida;
};

//1.1 hospital


Hospital* startHospital (){
	Hospital* hospital = new Hospital;
	strcpy(hospital->nombre, "Hospital");
	strcpy(hospital->direccion, "La Rotaria");
	strcpy(hospital->telefono, "1234");
	
	
	hospital->capacidadPacientes = 10;
	hospital->pacientes = new Paciente[hospital->capacidadPacientes];
	hospital->cantidadPacientes = 0;

	hospital->capacidadDoctores = 10;
	hospital->doctores = new Doctor[hospital->capacidadDoctores];
	hospital->cantidadDoctores = 0;
	
	hospital->capacidadCitas = 20;
    hospital->citas = new Cita[hospital->capacidadCitas]; 
    hospital->cantidadCitas = 0;
    
    hospital->siguienteIdPaciente = 1;
    hospital->siguienteIdDoctor = 1;
    hospital->siguienteIdCita = 1;
	hospital->siguienteIdConsulta = 1;
	
 return hospital;
}

//delete delete
void deleteHospital(Hospital* hospital) {
    if (hospital) {
        delete[] hospital->pacientes;
        delete[] hospital->doctores;
        delete[] hospital->citas;
        delete hospital;
    }
}

//1.2 paciente

void startPaciente(Paciente* paciente){
	
	paciente->id = 0;
	strcpy(paciente->nombre, "");
	strcpy(paciente->apellido, "");
	strcpy(paciente->cedula, "");
	paciente->edad = 0;
	paciente->sexo = '\0';
	strcpy(paciente->tipoSangre, "");
	strcpy(paciente->telefono, "");
	strcpy(paciente->direccion, "");
	strcpy(paciente->email, "");
	
	paciente->cantidadConsultas=0;
	paciente->capacidadHistorial=0;

	paciente->capacidadCitas=20;
	paciente->cantidadCitas=0;

	strcpy(paciente->alergias, "");
	strcpy(paciente->observaciones, "");
	
	paciente->activo = true;
}

//1.3 historial

void startHistorial(HistorialMedico* historial){
	historial->idConsulta = 0;
	strcpy(historial->fecha, "");
	strcpy(historial->hora, "");
	strcpy(historial->diagnostico, "");
	strcpy(historial->medicamentos,"");
	strcpy(historial->tratamiento,"");
	historial->idDoctor = 0;
	historial->costo = 0.0f;
	
}

//1.4 doctor
void startDoctor(Doctor* doctor){
	doctor->id=0;
	strcpy(doctor->nombre, "");
	strcpy(doctor->apellido, "");
	strcpy(doctor->cedula, "");
	strcpy(doctor->especialidad, "");
	doctor->aniosExperiencia=0;
	doctor->costoConsulta=0;
	strcpy(doctor->horarioAtencion, "");
	strcpy(doctor->telefono, "");
	strcpy(doctor->email, "");
	
	doctor->pacientesAsignados=0;
	doctor->cantidadPacientes=0;
	doctor->capacidadPacientes=0;
	
	doctor->citasAgendadas=0;
	doctor->cantidadCitas=0;
	doctor->capacidadCitas=0;
	doctor->disponible = true;
}

//1.5 citas

