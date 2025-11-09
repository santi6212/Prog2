#include <iostream>
#include <cstring>
#include <ctime>
#include <iomanip>

#include <cstdlib>

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
    	for (int i = 0; i < hospital->cantidadPacientes; ++i) {
            deletePaciente(&hospital->pacientes[i]); 
        }
    	for (int i = 0; i < hospital->cantidadDoctores; ++i) {
             deleteDoctor(&hospital->doctores[i]); 
        }
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
	paciente->historial = new HistorialMedico[paciente->capacidadHistorial];
	paciente->capacidadHistorial=5;

	paciente->capacidadCitas=5;
	paciente->citasAgendadas = new int[paciente->capacidadCitas];
	paciente->cantidadCitas=0;

	strcpy(paciente->alergias, "");
	strcpy(paciente->observaciones, "");
	
	//a
	
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
void startCita(Cita* cita){
	cita->id=0;
	cita->idPaciente=0;
	cita->idDoctor=0;
	strcpy(cita->fecha, "");
	strcpy(cita->hora, "");
	strcpy(cita->motivo, "");
	strcpy(cita->estado, "agendada");
	strcpy(cita->observaciones, "");
	cita->atendida = false;
}

//2.1 a)crear paciente

Paciente* crearPaciente(Hospital* hospital, const char* nombre, const char* apellido, const char* cedula, int edad, char sexo) {
                        
if (buscarPacientePorCedula(hospital, cedula)!=nullptr){
	cerr<<"Ya existe ese paciente"<<endl;
	return nullptr;
}
if (hospital->cantidadPacientes>=hospital->capacidadPacientes){
	
	int nuevaCapacidad = hospital->capacidadPacientes*2;
	Paciente* nuevoArr = new Paciente[nuevaCapacidad];
	for (int i = 0; i < hospital->cantidadPacientes; ++i) {
        nuevoArr[i] = hospital->pacientes[i];
        
    }
    	delete[] hospital->pacientes;
        hospital->pacientes = nuevoArr;
        hospital->capacidadPacientes = nuevaCapacidad;
}
	int indice = hospital->cantidadPacientes;
    Paciente* nuevoPaciente = &hospital->pacientes[indice];
    
    startPaciente(nuevoPaciente);
    
    nuevoPaciente->id = hospital->siguienteIdPaciente;
    strcpy(nuevoPaciente->nombre, nombre);
    strcpy(nuevoPaciente->apellido, apellido);
    strcpy(nuevoPaciente->cedula, cedula);
    nuevoPaciente->edad = edad;
    nuevoPaciente->sexo = sexo;
    
    hospital->cantidadPacientes++;
    hospital->siguienteIdPaciente++;
    
    cout<<"Nuevo paciente registrado: "<<nuevoPaciente->id<<endl;
    return nuevoPaciente;
}

//b) buscar por cedula


Paciente* buscarPacientePorCedula(Hospital* hospital, const char* cedula){
    for (int i = 0; i < hospital -> cantidadPacientes; i++) {
        const char * cedulaPaciente = hospital -> pacientes[i].cedula;

        if (strcmp(cedulaPaciente, cedula) == 0) {
            return & hospital -> pacientes[i];
        }
    }
    return nullptr;
}

//c) buscar por id

Paciente* buscarPacientePorId(Hospital* hospital, int id){
	for (int i = 0; i < hospital->cantidadPacientes; i++) {
        if (hospital->pacientes[i].id == id) {
            return &hospital->pacientes[i];
        }
    }
    return nullptr;
}
	
//d) buscar por nombre

Paciente ** buscarPacientesPorNombre(Hospital * hospital, const char * nombre, int * cantidad) {
    if (!hospital || !nombre || !cantidad) {
        if (cantidad) * cantidad = 0;
        return nullptr;
    }

    Paciente ** resultados = new Paciente * [hospital -> cantidadPacientes];
    * cantidad = 0;

    char * nombreLower = new char[strlen(nombre) + 1];
    for (int i = 0; nombre[i]; i++) {
        nombreLower[i] = tolower(nombre[i]);
    }
    nombreLower[strlen(nombre)] = '\0';

    for (int i = 0; i < hospital -> cantidadPacientes; i++) {
        char * nombrePacienteLower = new char[strlen(hospital -> pacientes[i].nombre) + 1];
        for (int j = 0; hospital -> pacientes[i].nombre[j]; j++) {
            nombrePacienteLower[j] = tolower(hospital -> pacientes[i].nombre[j]);
        }
        nombrePacienteLower[strlen(hospital -> pacientes[i].nombre)] = '\0';
        if (strstr(nombrePacienteLower, nombreLower) != nullptr) {
            resultados[ * cantidad] = & hospital -> pacientes[i];
            ( * cantidad) ++;
        }

        delete[] nombrePacienteLower;
    }

    delete[] nombreLower;

    if ( * cantidad == 0) {
        delete[] resultados;
        return nullptr;
    }

    return resultados;
}

//e) actualizar

bool actualizarPaciente(Hospital* hospital, int id){
	Paciente* paciente = buscarPacientePorId(hospital, id);
      if (!paciente) {
        cout << "Error: No se encontró paciente con ID " << id << endl;
        return false;
    }

    cout << "\n=== ACTUALIZAR DATOS DEL PACIENTE ===" << endl;
    cout << "Paciente: " << paciente -> nombre << " " << paciente -> apellido << endl;
    cout << "ID: " << paciente -> id << endl;
    cout << "Deje en blanco para mantener el valor actual\n" << endl;

    char buffer[200];

    cout << "Nombre actual: " << paciente -> nombre << endl;
    cout << "Nuevo nombre: ";
    cin.ignore();
    cin.getline(buffer, sizeof(buffer));
    if (strlen(buffer) > 0) {

        bool soloEspacios = true;
        for (int i = 0; buffer[i]; i++) {
            if (!isspace(buffer[i])) {
                soloEspacios = false;
                break;
            }
        }
        if (!soloEspacios) {
            strcpy(paciente -> nombre, buffer);
        }
    }

    cout << "Apellido actual: " << paciente -> apellido << endl;
    cout << "Nuevo apellido: ";
    cin.getline(buffer, sizeof(buffer));
    if (strlen(buffer) > 0) {
        bool soloEspacios = true;
        for (int i = 0; buffer[i]; i++) {
            if (!isspace(buffer[i])) {
                soloEspacios = false;
                break;
            }
        }
        if (!soloEspacios) {
            strcpy(paciente -> apellido, buffer);
        }
    }

    cout << "Edad actual: " << paciente -> edad << endl;
    cout << "Nueva edad: ";
    cin.getline(buffer, sizeof(buffer));
    if (strlen(buffer) > 0) {
        int nuevaEdad = atoi(buffer);
        if (nuevaEdad > 0 && nuevaEdad <= 150) {
            paciente -> edad = nuevaEdad;
        } else {
            cout << "Edad no válida. Manteniendo valor actual." << endl;
        }
    }

    cout << "Sexo actual: " << paciente -> sexo << endl;
    cout << "Nuevo sexo (M/F): ";
    cin.getline(buffer, sizeof(buffer));
    if (strlen(buffer) > 0) {
        char nuevoSexo = toupper(buffer[0]);
        if (nuevoSexo == 'M' || nuevoSexo == 'F') {
            paciente -> sexo = nuevoSexo;
        } else {
            cout << "Sexo no válido. Use M o F. Manteniendo valor actual." << endl;
        }
    }

    cout << "Teléfono actual: " << paciente -> telefono << endl;
    cout << "Nuevo teléfono: ";
    cin.getline(buffer, sizeof(buffer));
    if (strlen(buffer) > 0) {
        strcpy(paciente -> telefono, buffer);
    }

    cout << "Dirección actual: " << paciente -> direccion << endl;
    cout << "Nueva dirección: ";
    cin.getline(buffer, sizeof(buffer));
    if (strlen(buffer) > 0) {
        strcpy(paciente -> direccion, buffer);
    }

    cout << "Email actual: " << paciente -> email << endl;
    cout << "Nuevo email: ";
    cin.getline(buffer, sizeof(buffer));
    if (strlen(buffer) > 0) {
        strcpy(paciente -> email, buffer);
    }

    cout << "Tipo de sangre actual: " << paciente -> tipoSangre << endl;
    cout << "Nuevo tipo de sangre: ";
    cin.getline(buffer, sizeof(buffer));
    if (strlen(buffer) > 0) {
        strcpy(paciente -> tipoSangre, buffer);
    }

    cout << "Alergias actuales: " << paciente -> alergias << endl;
    cout << "Nuevas alergias: ";
    cin.getline(buffer, sizeof(buffer));
    if (strlen(buffer) > 0) {
        strcpy(paciente -> alergias, buffer);
    }

    cout << "Observaciones actuales: " << paciente -> observaciones << endl;
    cout << "Nuevas observaciones: ";
    cin.getline(buffer, sizeof(buffer));
    if (strlen(buffer) > 0) {
        strcpy(paciente -> observaciones, buffer);
    }

    cout << "\nDatos del paciente actualizados correctamente." << endl;
    return true;
}
    
//f) eliminar

bool eliminarPaciente(Hospital* hospital, int id){


int eliminarIndice = -1;
for (int i = 0; i < hospital->cantidadPacientes; ++i) {
        if (hospital->pacientes[i].id == id) {
            eliminarIndice = i;
            break;
        }
    }
    if (eliminarIndice == -1) return false;

    Paciente* paciente = &hospital->pacientes[eliminarIndice];

    if (paciente->historial != nullptr) delete[] paciente->historial;
    if (paciente->citasAgendadas != nullptr) delete[] paciente->citasAgendadas;
    
    for (int i = eliminarIndice; i < hospital->cantidadPacientes - 1; ++i) {
        hospital->pacientes[i] = hospital->pacientes[i + 1];
    }
    //compacta array
    hospital->cantidadPacientes--;

    return true;
}

//g)listar
void listarPacientes(Hospital* hospital){
	if (hospital->cantidadPacientes == 0) {
        cout << "No hay pacientes registrados." << std::endl;
        return;
    }

    printf("| %-4s | %-25s | %-15s | %-5s | %-10s |\n", 
           "ID", "NOMBRE COMPLETO", "CÉDULA", "EDAD", "CONSULTAS");


    for (int i = 0; i < hospital->cantidadPacientes; ++i) {
        const Paciente& p = hospital->pacientes[i];
        
        char nombreCompleto[101];
        snprintf(nombreCompleto, 101, "%s %s", p.nombre, p.apellido);

        printf("| %-4d | %-25s | %-15s | %-5d | %-10d |\n", 
               p.id, nombreCompleto, p.cedula, p.edad, p.cantidadConsultas);
    }
}
	
	
//2.2Funciones de historial médico	
