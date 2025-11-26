#include <iostream>
#include <cstring>
#include <ctime>
#include <iomanip>
#include <cctype> 
#include <cstdio>
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
	
	paciente->capacidadHistorial=5;
	paciente->historial = new HistorialMedico[paciente->capacidadHistorial];
	paciente->cantidadConsultas=0;

	paciente->capacidadCitas=5;
	paciente->citasAgendadas = new int[paciente->capacidadCitas];
	paciente->cantidadCitas=0;

	strcpy(paciente->alergias, "");
	strcpy(paciente->observaciones, "");
	
	//a
	
	paciente->activo = true;
}
void deletePaciente(Paciente* paciente) {
    if (paciente) {
        // Liberar historial
        if (paciente->historial) {
            delete[] paciente->historial;
            paciente->historial = nullptr;
        }
        // Liberar citasAgendadas
        if (paciente->citasAgendadas) {
            delete[] paciente->citasAgendadas;
            paciente->citasAgendadas = nullptr;
        }
    }
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
	
	
	doctor->capacidadPacientes=10;
	doctor->pacientesAsignados = new int[doctor->capacidadPacientes];
	doctor->cantidadPacientes=0;
	
	
	doctor->capacidadCitas=10;
	doctor->citasAgendadas = new int[doctor->capacidadCitas];
	doctor->cantidadCitas=0;
	doctor->disponible = true;
}
void deleteDoctor(Doctor* doctor) {
    if (doctor) {
        // Liberar pacientesAsignados
        if (doctor->pacientesAsignados) {
            delete[] doctor->pacientesAsignados;
            doctor->pacientesAsignados = nullptr;
        }
        // Liberar citasAgendadas
        if (doctor->citasAgendadas) {
            delete[] doctor->citasAgendadas;
            doctor->citasAgendadas = nullptr;
        }
    }
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


    if (eliminarIndice == -1) return false;


    deletePaciente(&hospital->pacientes[eliminarIndice]); 

    for (int i = eliminarIndice; i < hospital->cantidadPacientes - 1; ++i) {
  
        hospital->pacientes[i] = hospital->pacientes[i + 1];
    }

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
           "ID", "NOMBRE COMPLETO", "CEDULA", "EDAD", "CONSULTAS");


    for (int i = 0; i < hospital->cantidadPacientes; ++i) {
        const Paciente& p = hospital->pacientes[i];
        
        char nombreCompleto[101];
        snprintf(nombreCompleto, 101, "%s %s", p.nombre, p.apellido);

        printf("| %-4d | %-25s | %-15s | %-5d | %-10d |\n", 
               p.id, nombreCompleto, p.cedula, p.edad, p.cantidadConsultas);
    }
}
	
	
//2.2Funciones de historial médico	

void agregarConsultaAlHistorial(Paciente* paciente, HistorialMedico consulta) {
    if (paciente->cantidadConsultas >= paciente->capacidadHistorial) {
        cout << "Historial de paciente ID " << paciente->id<< " esta lleno. Redimensionando..." <<endl;
                  
  
        int nuevaCapacidad = paciente->capacidadHistorial * 2;
        
        HistorialMedico* nuevoHistorial = new HistorialMedico[nuevaCapacidad];
        
        for (int i = 0; i < paciente->cantidadConsultas; ++i) {
            nuevoHistorial[i] = paciente->historial[i];
        }
        

        delete[] paciente->historial;
        

        paciente->historial = nuevoHistorial;
        paciente->capacidadHistorial = nuevaCapacidad;
    }
    
    int indice = paciente->cantidadConsultas;
    

    paciente->historial[indice] = consulta; 
    

    paciente->cantidadConsultas++;

    
    cout << "Consulta agregada. Total: " << paciente->cantidadConsultas <<endl;
}

HistorialMedico* obtenerHistorialCompleto(Paciente* paciente, int* cantidad) {
    *cantidad = paciente->cantidadConsultas;
    
    return paciente->historial;
}

void mostrarHistorialMedico(Paciente* paciente) {
    if (paciente->cantidadConsultas == 0) {
        cout << "El paciente ID " << paciente->id << " no tiene consultas registradas." <<endl;
        return;
    }

    cout << "\n--- HISTORIAL MÉDICO DEL PACIENTE ID " << paciente->id << " (" 
              << paciente->nombre << " " << paciente->apellido << ") ---" << endl;
    
    printf("| %-4s | %-10s | %-5s | %-30s | %-15s | %-8s |\n", 
           "ID", "FECHA", "HORA", "DIAGNOSTICO", "DOCTOR ID", "COSTO");
    cout << "-----------------------------------------------------------------------------------" <<endl;

    for (int i = 0; i < paciente->cantidadConsultas; ++i) {
        const HistorialMedico& h = paciente->historial[i];
        
  
        printf("| %-4d | %-10s | %-5s | %-30s | %-15d | $%-7.2f |\n", 
               h.idConsulta, 
               h.fecha, 
               h.hora, 
               h.diagnostico, 
               h.idDoctor, 
               h.costo);
    }
    cout << "-----------------------------------------------------------------------------------" <<endl;
}

HistorialMedico* obtenerUltimaConsulta(Paciente* paciente) {
    if (paciente->cantidadConsultas == 0) {
        return nullptr;
    }
    
    // La última consulta está en el índice (cantidadConsultas - 1)
    return &paciente->historial[paciente->cantidadConsultas - 1];
}

//3 doctoresss

Doctor* buscarDoctorPorCedula(Hospital* hospital, const char* cedula) {
    for (int i = 0; i < hospital->cantidadDoctores; i++) {
        if (strcmp(hospital->doctores[i].cedula, cedula) == 0) { 
            return &hospital->doctores[i];
        }
    }
    return nullptr;
}

void expandirDoctores(Hospital* hospital) {
    int nuevaCapacidad = hospital->capacidadDoctores * 2;
    Doctor* nuevoArr = new Doctor[nuevaCapacidad];
    
    for (int i = 0; i < hospital->cantidadDoctores; ++i) {
        nuevoArr[i] = hospital->doctores[i];
    }
    
    delete[] hospital->doctores;
    hospital->doctores = nuevoArr;
    hospital->capacidadDoctores = nuevaCapacidad;
    
    cout << "Array de Doctores redimensionado a " << nuevaCapacidad << "." <<endl;
}
//crear
Doctor* crearDoctor(Hospital* hospital, const char* nombre, const char* apellido, const char* cedula,const char* especialidad, int aniosExperiencia, float costoConsulta) {


    if (buscarDoctorPorCedula(hospital, cedula) != nullptr) {
        cerr << "Ya existe un doctor con la cedula " << cedula << endl;
        return nullptr;
    }
    
    if (hospital->cantidadDoctores >= hospital->capacidadDoctores) {
        expandirDoctores(hospital);
    }
    
    int indice = hospital->cantidadDoctores;
    Doctor* nuevoDoctor = &hospital->doctores[indice];
    
    startDoctor(nuevoDoctor);
    nuevoDoctor->id = hospital->siguienteIdDoctor;
    strcpy(nuevoDoctor->nombre, nombre);
    strcpy(nuevoDoctor->apellido, apellido);
    strcpy(nuevoDoctor->cedula, cedula);
    strcpy(nuevoDoctor->especialidad, especialidad);
    nuevoDoctor->aniosExperiencia = aniosExperiencia;
    nuevoDoctor->costoConsulta = costoConsulta;
    hospital->cantidadDoctores++;
    hospital->siguienteIdDoctor++;
    
    cout << "Nuevo doctor registrado: " << nuevoDoctor->id << endl;
    return nuevoDoctor;
}
    //buscar por id
    
Doctor* buscarDoctorPorId(Hospital* hospital, int id) {
    for (int i = 0; i < hospital->cantidadDoctores; ++i) {
        if (hospital->doctores[i].id == id) {
            return &hospital->doctores[i];
        }
    }
    return nullptr;
}

	//por especialidad

Doctor** buscarDoctoresPorEspecialidad(Hospital* hospital,const char* especialidad, int* cantidad) {
	*cantidad = 0;
	int contador = 0;
    for (int i = 0; i < hospital->cantidadDoctores; ++i) {
        if (strcmp(hospital->doctores[i].especialidad, especialidad) == 0) { 
            contador++;
        }
    }
    if (contador == 0) {
        return nullptr;
    }
    Doctor** resultados = new Doctor*[contador];
    
    int indice_resultado = 0;
    for (int i = 0; i < hospital->cantidadDoctores; ++i) {
        if (strcmp(hospital->doctores[i].especialidad, especialidad) == 0) {
            resultados[indice_resultado] = &hospital->doctores[i];
            indice_resultado++;
        }
    }
    
    *cantidad = contador;
    return resultados;
}

//asignar paciente

void expandirPacientesAsignados(Doctor* doctor) {
    int nuevaCapacidad = doctor->capacidadPacientes * 2;
    int* nuevoArr = new int[nuevaCapacidad];
    
    for (int i = 0; i < doctor->cantidadPacientes; ++i) {
        nuevoArr[i] = doctor->pacientesAsignados[i];
    }
    
    delete[] doctor->pacientesAsignados;
    doctor->pacientesAsignados = nuevoArr;
    doctor->capacidadPacientes = nuevaCapacidad;
}

bool asignarPacienteADoctor(Doctor* doctor, int idPaciente) {
    for (int i = 0; i < doctor->cantidadPacientes; ++i) {
        if (doctor->pacientesAsignados[i] == idPaciente) {
            cerr << "El paciente ID " << idPaciente << " ya esta asignado a este doctor." <<endl;
            return false;
        }
    }
    if (doctor->cantidadPacientes >= doctor->capacidadPacientes) {
        expandirPacientesAsignados(doctor);
    }
    doctor->pacientesAsignados[doctor->cantidadPacientes] = idPaciente;
    doctor->cantidadPacientes++;
    
    cout << "? Paciente ID " << idPaciente << " asignado correctamente al Doctor ID " << doctor->id <<endl;
    return true;
}

//remover paciente

bool removerPacienteDeDoctor(Doctor* doctor, int idPaciente) {
    int indiceARemover = -1;
    
    for (int i = 0; i < doctor->cantidadPacientes; ++i) {
        if (doctor->pacientesAsignados[i] == idPaciente) {
            indiceARemover = i;
            break;
        }
    }
    
    if (indiceARemover == -1) {
        cerr << "El paciente ID " << idPaciente << " no está asignado a este doctor." <<endl;
        return false;
    }
    for (int i = indiceARemover; i < doctor->cantidadPacientes - 1; ++i) {
        doctor->pacientesAsignados[i] = doctor->pacientesAsignados[i + 1];
    }

    doctor->cantidadPacientes--;

	cout << "Paciente ID " << idPaciente << " removido de la lista del Doctor ID " << doctor->id <<endl;
    return true;
}

//listar pacientes

void listarPacientesDeDoctor(Hospital* hospital, int idDoctor) {
    Doctor* doctor = buscarDoctorPorId(hospital, idDoctor);
    if (doctor == nullptr) {
        cerr << "Doctor ID " << idDoctor << " no encontrado." << endl;
        return;
    }
    
    cout << "\n--- Pacientes Asignados al Dr(a). " << doctor->apellido << " (" << doctor->especialidad << ") ---" << endl;

    if (doctor->cantidadPacientes == 0) {
        cout << "No tiene pacientes asignados actualmente." << endl;
        return;
    }

    printf("| %-4s | %-25s | %-15s | %-5s |\n", 
           "ID", "NOMBRE COMPLETO", "CEDULA", "EDAD");
    cout << "--------------------------------------------------------" <<endl;

    for (int i = 0; i < doctor->cantidadPacientes; ++i) {
        int idPaciente = doctor->pacientesAsignados[i];
        Paciente* p = buscarPacientePorId(hospital, idPaciente);
        
        if (p) {
            char nombreCompleto[101];
            snprintf(nombreCompleto, 101, "%s %s", p->nombre, p->apellido);

            printf("| %-4d | %-25s | %-15s | %-5d |\n", 
                   p->id, nombreCompleto, p->cedula, p->edad);
        } else {
    
            printf("| %-4d | %-25s | %-15s | %-5s |\n", 
                   idPaciente, "(Paciente no encontrado)", "N/A", "N/A");
        }
    }
}

//listar doctores

void listarDoctores(Hospital* hospital) {
    if (hospital->cantidadDoctores == 0) {
        std::cout << "No hay doctores registrados." << std::endl;
        return;
    }

    cout << "\n=== LISTADO DE DOCTORES ===" <<endl;
    
    printf("| %-4s | %-25s | %-15s | %-15s | %-10s | %-8s |\n", 
           "ID", "NOMBRE COMPLETO", "CEDULA", "ESPECIALIDAD", "CONSULTA", "EXP.");
    cout << "----------------------------------------------------------------------------------" <<endl;

    for (int i = 0; i < hospital->cantidadDoctores; ++i) {
        const Doctor& d = hospital->doctores[i];
        
        char nombreCompleto[101];
        snprintf(nombreCompleto, 101, "%s %s", d.nombre, d.apellido);

        printf("| %-4d | %-25s | %-15s | %-15s | $%-8.2f | %-8d |\n", 
               d.id, nombreCompleto, d.cedula, d.especialidad, d.costoConsulta, d.aniosExperiencia);
    }
    cout << "----------------------------------------------------------------------------------" <<endl;
}

//eliminar doctor

bool eliminarDoctor(Hospital* hospital, int id) {
    int eliminarIndice = -1;
    for (int i = 0; i < hospital->cantidadDoctores; ++i) {
        if (hospital->doctores[i].id == id) {
            eliminarIndice = i;
            break;
        }
    }
    if (eliminarIndice == -1) return false;

    Doctor* doctor = &hospital->doctores[eliminarIndice];
    deleteDoctor(doctor);
    

    for (int i = eliminarIndice; i < hospital->cantidadDoctores - 1; ++i) {
        hospital->doctores[i] = hospital->doctores[i + 1];
    }
    
    hospital->cantidadDoctores--;
    
    cout << "? Doctor ID " << id << " eliminado correctamente." <<endl;
    return true;
}

//4 citas

Cita* agendarCita(Hospital* hospital, int idPaciente, int idDoctor,
                  const char* fecha, const char* hora, const char* motivo) {
    
    Paciente* paciente = buscarPacientePorId(hospital, idPaciente);
    Doctor* doctor = buscarDoctorPorId(hospital, idDoctor);
    
    // 1 & 2. Verificar existencia
    if (paciente == nullptr) {
        cerr << "Error: Paciente ID " << idPaciente << " no encontrado." << endl;
        return nullptr;
    }
    if (doctor == nullptr) {
        cerr << "Error: Doctor ID " << idDoctor << " no encontrado." << endl;
        return nullptr;
    }
    
    // 3 & 4. Validar formatos
    if (!validarFormatoFecha(fecha)) {
        cerr << "Error: Formato de fecha no válido (debe ser YYYY-MM-DD)." << endl;
        return nullptr;
    }
    if (!validarFormatoHora(hora)) {
        cerr << "Error: Formato de hora no válido (debe ser HH:MM)." << endl;
        return nullptr;
    }

    // 5. Verificar disponibilidad
    if (!verificarDisponibilidad(hospital, idDoctor, fecha, hora)) {
        cerr << "Error: Doctor ID " << idDoctor << " no está disponible el " << fecha << " a las " << hora << endl;
        return nullptr;
    }

    // Redimensionar si es necesario
    if (hospital->cantidadCitas >= hospital->capacidadCitas) {
        expandirCitas(hospital);
    }
    
    int indice = hospital->cantidadCitas;
    Cita* nuevaCita = &hospital->citas[indice];
    
    bool validarFormatoFecha(const char* fecha) {
    // Verifica el formato YYYY-MM-DD
    if (strlen(fecha) != 10) return false;
    if (fecha[4] != '-' || fecha[7] != '-') return false;
    // Se puede añadir más lógica (isdigit, rangos, etc.) pero esta es la base
    return true;
    }

    bool validarFormatoHora(const char* hora) {
    // Verifica el formato HH:MM
    if (strlen(hora) != 5) return false;
    if (hora[2] != ':') return false;
    // Se puede añadir más lógica (isdigit, rangos, etc.) pero esta es la base
    return true;
    }
    
    startCita(nuevaCita); // Inicializa con estado "agendada" y atendida=false
    
    nuevaCita->id = hospital->siguienteIdCita;
    nuevaCita->idPaciente = idPaciente;
    nuevaCita->idDoctor = idDoctor;
    strcpy(nuevaCita->fecha, fecha);
    strcpy(nuevaCita->hora, hora);
    strcpy(nuevaCita->motivo, motivo);

    agregarCitaAColeccion(&paciente->citasAgendadas, &paciente->cantidadCitas, &paciente->capacidadCitas, nuevaCita->id);
    agregarCitaAColeccion(&doctor->citasAgendadas, &doctor->cantidadCitas, &doctor->capacidadCitas, nuevaCita->id);
    
    hospital->cantidadCitas++;
    hospital->siguienteIdCita++;
    
    cout << "? Cita agendada (ID: " << nuevaCita->id << ") para el Dr. " << doctor->apellido << endl;
    return nuevaCita;
}

void expandirCitas(Hospital* hospital) {
    int nuevaCapacidad = hospital->capacidadCitas * 2;
    Cita* nuevoArr = new Cita[nuevaCapacidad];
    
    for (int i = 0; i < hospital->cantidadCitas; ++i) {
        nuevoArr[i] = hospital->citas[i];
    }
    
    delete[] hospital->citas;
    hospital->citas = nuevoArr;
    hospital->capacidadCitas = nuevaCapacidad;
    
    cout << "Array de Citas redimensionado a " << nuevaCapacidad << "." << endl;
}

bool verificarDisponibilidad(Hospital* hospital, int idDoctor, const char* fecha, const char* hora) {
    for (int i = 0; i < hospital->cantidadCitas; ++i) {
        const Cita& c = hospital->citas[i];
        
        if (strcmp(c.estado, "agendada") == 0) {
            
            if (c.idDoctor == idDoctor && 
                strcmp(c.fecha, fecha) == 0 && 
                strcmp(c.hora, hora) == 0) {
                
                return false;
            }
        }
    }
    return true; 
}

bool agregarCitaAColeccion(int** arrayCitas, int* cantidad, int* capacidad, int idCita) {
    
    if (*cantidad >= *capacidad) {
        *capacidad *= 2;
        int* nuevoArr = new int[*capacidad];
        
        for (int i = 0; i < *cantidad; ++i) {
            nuevoArr[i] = (*arrayCitas)[i];
        }
        
        delete[] *arrayCitas;
        *arrayCitas = nuevoArr;
    }

    
    (*arrayCitas)[*cantidad] = idCita;
    (*cantidad)++;
    return true;
}

bool removerIdDeColeccion(int* arrayCitas, int* cantidad, int idARemover) {
    int indiceARemover = -1;
    
    for (int i = 0; i < *cantidad; ++i) {
        if (arrayCitas[i] == idARemover) {
            indiceARemover = i;
            break;
        }
    }
    
    if (indiceARemover == -1) return false;

    for (int i = indiceARemover; i < *cantidad - 1; ++i) {
        arrayCitas[i] = arrayCitas[i + 1];
    }
    
    (*cantidad)--;
    return true;
}

// b) buscar cita
Cita* buscarCitaPorId(Hospital* hospital, int id) {
    for (int i = 0; i < hospital->cantidadCitas; ++i) {
        if (hospital->citas[i].id == id) {
            return &hospital->citas[i];
        }
    }
    return nullptr;
}

// c) cancelar cita
bool cancelarCita(Hospital* hospital, int idCita) {
    Cita* cita = buscarCitaPorId(hospital, idCita);
    if (cita == nullptr) {
        cerr << "Cita ID " << idCita << " no encontrada." << endl;
        return false;
    }
    
    if (strcmp(cita->estado, "cancelada") == 0) {
        cout << "La cita ID " << idCita << " ya estaba cancelada." << endl;
        return true;
    }

    // 1. Cambiar el estado de la cita
    strcpy(cita->estado, "cancelada");
    cout << "? Cita ID " << idCita << " marcada como cancelada." << endl;

    // 2. Remover ID de la cita de los arrays internos del Paciente y Doctor
    Paciente* paciente = buscarPacientePorId(hospital, cita->idPaciente);
    Doctor* doctor = buscarDoctorPorId(hospital, cita->idDoctor);
    
    if (paciente) {
        removerIdDeColeccion(paciente->citasAgendadas, &paciente->cantidadCitas, idCita);
    }
    if (doctor) {
        removerIdDeColeccion(doctor->citasAgendadas, &doctor->cantidadCitas, idCita);
    }

    return true;
}

bool atenderCita(Hospital* hospital, int idCita, const char* diagnostico,const char* tratamiento, const char* medicamentos) {
    
    // 1. Buscar la cita por ID y verificar estado
    Cita* cita = buscarCitaPorId(hospital, idCita);
    if (cita == nullptr) {
        cerr << "Error: Cita ID " << idCita << " no encontrada." << endl;
        return false;
    }
    
    if (strcmp(cita->estado, "agendada") != 0) {
        cerr << "Error: La cita ID " << idCita << " no esta en estado 'agendada' (estado actual: " << cita->estado << ")." << endl;
        return false;
    }
    
    // 2. Buscar Paciente y Doctor para obtener datos y actualizar el historial
    Paciente* paciente = buscarPacientePorId(hospital, cita->idPaciente);
    Doctor* doctor = buscarDoctorPorId(hospital, cita->idDoctor);

    if (paciente == nullptr || doctor == nullptr) {
        cerr << "Error: Paciente o Doctor asociado a la cita no encontrados." << endl;
        // La cita queda en estado "agendada" si no se puede completar.
        return false;
    }

    // 3. Crear el registro de HistorialMedico (Consulta)
    HistorialMedico nuevaConsulta;
    startHistorial(&nuevaConsulta);
    
    nuevaConsulta.idConsulta = hospital->siguienteIdConsulta;
    strcpy(nuevaConsulta.fecha, cita->fecha);
    strcpy(nuevaConsulta.hora, cita->hora);
    strcpy(nuevaConsulta.diagnostico, diagnostico);
    strcpy(nuevaConsulta.tratamiento, tratamiento);
    strcpy(nuevaConsulta.medicamentos, medicamentos);
    nuevaConsulta.idDoctor = doctor->id;
    nuevaConsulta.costo = doctor->costoConsulta; // Asignar el costo de la consulta del doctor

    // 4. Agregar la consulta al historial del paciente
    agregarConsultaAlHistorial(paciente, nuevaConsulta);
    hospital->siguienteIdConsulta++; // Incrementar el ID para la próxima consulta

    // 5. Actualizar la cita a "atendida" y marcar como atendida
    strcpy(cita->estado, "atendida");
    cita->atendida = true;
    
    // 6. Remover la cita de los arrays internos del Paciente y Doctor (Opcional, pero recomendado
    //    para mantener la lista de citas 'activas' limpia. Una cita 'atendida' ya no se considera 'agendada')
    removerIdDeColeccion(paciente->citasAgendadas, &paciente->cantidadCitas, idCita);
    removerIdDeColeccion(doctor->citasAgendadas, &doctor->cantidadCitas, idCita);


    cout << "   - Historial Medico (ID: " << nuevaConsulta.idConsulta << ") registrado." << endl;
    cout << "   - Paciente: " << paciente->nombre << " " << paciente->apellido << endl;
    cout << "   - Doctor: " << doctor->nombre << " " << doctor->apellido << endl;
    cout << "\n? Cita ID " << idCita << " atendida correctamente." << endl;
    
    return true;
}

// d) listar citas
void listarCitasDeDoctor(Hospital* hospital, int idDoctor) {
    Doctor* doctor = buscarDoctorPorId(hospital, idDoctor);
    if (doctor == nullptr) {
        cerr << "Error: Doctor ID " << idDoctor << " no encontrado." << endl;
        return;
    }

    cout << "\n--- CITAS AGENDADAS DEL DR. " << doctor->apellido << " (" << doctor->especialidad << ") ---" << endl;

    if (doctor->cantidadCitas == 0) {
        cout << "El doctor no tiene citas agendadas en su lista interna." << endl;
        return;
    }

    printf("| %-4s | %-10s | %-5s | %-25s | %-15s |\n", 
           "ID", "FECHA", "HORA", "PACIENTE", "ESTADO");
    cout << "----------------------------------------------------------------" << endl;

    for (int i = 0; i < doctor->cantidadCitas; ++i) {
        int idCita = doctor->citasAgendadas[i];
        Cita* c = buscarCitaPorId(hospital, idCita);
        
        if (c) {
            Paciente* p = buscarPacientePorId(hospital, c->idPaciente);
            char nombrePaciente[51];
            
            if (p) {
                snprintf(nombrePaciente, 51, "%s %s", p->nombre, p->apellido);
            } else {
                strcpy(nombrePaciente, "(Paciente Eliminado)");
            }
            
            printf("| %-4d | %-10s | %-5s | %-25s | %-15s |\n", 
                   c->id, c->fecha, c->hora, nombrePaciente, c->estado);
        }
    }
    cout << "----------------------------------------------------------------" << endl;
}

Cita** obtenerCitasDePaciente(Hospital* hospital, int idPaciente, int* cantidad) {
    *cantidad = 0;
    Paciente* paciente = buscarPacientePorId(hospital, idPaciente);
    
    if (paciente == nullptr || paciente->cantidadCitas == 0) {
        return nullptr;
    }
    
    int citasEncontradas = 0;
    // Creamos un array de punteros con el tamaño máximo posible (citas internas del paciente)
    Cita** resultados = new Cita*[paciente->cantidadCitas];

    // Iteramos sobre el array interno de IDs del paciente
    for (int i = 0; i < paciente->cantidadCitas; ++i) {
        int idCita = paciente->citasAgendadas[i];
        Cita* c = buscarCitaPorId(hospital, idCita);
        
        if (c != nullptr) {
            resultados[citasEncontradas] = c;
            citasEncontradas++;
        }
    }
    
    if (citasEncontradas == 0) {
        delete[] resultados;
        return nullptr;
    }
    
    // Retornamos el array y la cantidad real
    *cantidad = citasEncontradas;
    return resultados; 
}
Cita** obtenerCitasDeDoctor(Hospital* hospital, int idDoctor, int* cantidad) {
    *cantidad = 0;
    Doctor* doctor = buscarDoctorPorId(hospital, idDoctor);
    
    if (doctor == nullptr || doctor->cantidadCitas == 0) {
        return nullptr;
    }
    
    int citasEncontradas = 0;
    Cita** resultados = new Cita*[doctor->cantidadCitas];

    // Iteramos sobre el array interno de IDs del doctor
    for (int i = 0; i < doctor->cantidadCitas; ++i) {
        int idCita = doctor->citasAgendadas[i];
        Cita* c = buscarCitaPorId(hospital, idCita);
        
        if (c != nullptr) {
            resultados[citasEncontradas] = c;
            citasEncontradas++;
        }
    }
    
    if (citasEncontradas == 0) {
        delete[] resultados;
        return nullptr;
    }
    
    *cantidad = citasEncontradas;
    return resultados; 
}
Cita** obtenerCitasPorFecha(Hospital* hospital, const char* fecha, int* cantidad) {
    *cantidad = 0;
    
    if (!validarFormatoFecha(fecha)) {
        cerr << "Error: Formato de fecha no válido (debe ser YYYY-MM-DD)." << endl;
        return nullptr;
    }

    // Usamos el array principal de citas para buscar
    int maxResultados = hospital->cantidadCitas;
    if (maxResultados == 0) return nullptr;
    
    Cita** resultados = new Cita*[maxResultados];
    int citasEncontradas = 0;

    for (int i = 0; i < hospital->cantidadCitas; ++i) {
        Cita* c = &hospital->citas[i];
        
        if (strcmp(c->fecha, fecha) == 0) {
            resultados[citasEncontradas] = c;
            citasEncontradas++;
        }
    }

    if (citasEncontradas == 0) {
        delete[] resultados;
        return nullptr;
    }
    
    *cantidad = citasEncontradas;
    return resultados; 
}
void listarCitasPendientes(Hospital* hospital) {
    int contador = 0;
    cout << "\n=== LISTADO DE CITAS PENDIENTES ('Agendada') ===" << endl;
    
    printf("| %-4s | %-10s | %-5s | %-10s | %-10s | %-30s |\n",
           "ID", "FECHA", "HORA", "PACIENTE", "DOCTOR", "MOTIVO");
    cout << "----------------------------------------------------------------------------------" << endl;

    for (int i = 0; i < hospital->cantidadCitas; ++i) {
        Cita* c = &hospital->citas[i];
        
        if (strcmp(c->estado, "agendada") == 0) {
            Paciente* p = buscarPacientePorId(hospital, c->idPaciente);
            Doctor* d = buscarDoctorPorId(hospital, c->idDoctor);
            
            char nombrePaciente[11] = "N/A";
            char nombreDoctor[11] = "N/A";

            if (p) snprintf(nombrePaciente, 11, "P%d", p->id);
            if (d) snprintf(nombreDoctor, 11, "D%d (%s)", d->id, d->apellido);
            
            printf("| %-4d | %-10s | %-5s | %-10s | %-10s | %-30s |\n",
                   c->id, c->fecha, c->hora, nombrePaciente, nombreDoctor, c->motivo);
            contador++;
        }
    }
    
    if (contador == 0) {
        cout << "No hay citas pendientes actualmente." << endl;
    }
    cout << "----------------------------------------------------------------------------------" << endl;
}
bool verificarDisponibilidad(Hospital* hospital, int idDoctor,
                             const char* fecha, const char* hora) {
    for (int i = 0; i < hospital->cantidadCitas; ++i) {
        const Cita& c = hospital->citas[i];
        
        // Solo verificamos citas que están activas o agendadas
        if (strcmp(c.estado, "agendada") == 0) {
            
            if (c.idDoctor == idDoctor && 
                strcmp(c.fecha, fecha) == 0 && 
                strcmp(c.hora, hora) == 0) {
                
                return false; // No disponible
            }
        }
    }
    return true; // Disponible
}

//5)utilidades y helpers

Hospital* inicializarHospital(const char* nombre, int capacidadInicial) {
    Hospital* hospital = new Hospital;
    
    // Inicializar datos escalares
    strncpy(hospital->nombre, nombre, sizeof(hospital->nombre) - 1);
    hospital->nombre[sizeof(hospital->nombre) - 1] = '\0';
    
    hospital->siguienteIdPaciente = 1;
    hospital->siguienteIdDoctor = 1;
    hospital->siguienteIdCita = 1;
    hospital->siguienteIdConsulta = 1;
    
    // Inicializar arrays de Pacientes
    hospital->capacidadPacientes = capacidadInicial;
    hospital->cantidadPacientes = 0;
    hospital->pacientes = new Paciente[capacidadInicial];
    
    // Inicializar arrays de Doctores
    hospital->capacidadDoctores = capacidadInicial;
    hospital->cantidadDoctores = 0;
    hospital->doctores = new Doctor[capacidadInicial];
    
    // Inicializar arrays de Citas
    hospital->capacidadCitas = capacidadInicial * 2; // Una capacidad inicial más alta para citas
    hospital->cantidadCitas = 0;
    hospital->citas = new Cita[hospital->capacidadCitas];
    
    cout << "? Hospital '" << hospital->nombre << "' inicializado con capacidad " << capacidadInicial << "." << endl;
    return hospital;
}

void destruirHospital(Hospital* hospital) {
    if (hospital == nullptr) return;

    cout << "\n?? Iniciando liberación de memoria del Hospital '" << hospital->nombre << "'..." << endl;
    
    // 1 & 2. Liberar memoria dinámica de cada Paciente y luego el array de Pacientes
    for (int i = 0; i < hospital->cantidadPacientes; ++i) {
        // Liberar historial (array de HistorialMedico)
        if (hospital->pacientes[i].historial != nullptr) {
            delete[] hospital->pacientes[i].historial;
        }
        // Liberar citasAgendadas (array de int)
        if (hospital->pacientes[i].citasAgendadas != nullptr) {
            delete[] hospital->pacientes[i].citasAgendadas;
        }
    }
    delete[] hospital->pacientes;
    cout << "   -> Memoria de Pacientes liberada." << endl;

    // 3 & 4. Liberar memoria dinámica de cada Doctor y luego el array de Doctores
    for (int i = 0; i < hospital->cantidadDoctores; ++i) {
        // Liberar pacientesAsignados (array de int)
        if (hospital->doctores[i].pacientesAsignados != nullptr) {
            delete[] hospital->doctores[i].pacientesAsignados;
        }
        // Liberar citasAgendadas (array de int)
        if (hospital->doctores[i].citasAgendadas != nullptr) {
            delete[] hospital->doctores[i].citasAgendadas;
        }
    }
    delete[] hospital->doctores;
    cout << "   -> Memoria de Doctores liberada." << endl;
    
    // 5. Liberar array de Citas
    delete[] hospital->citas;
    cout << "   -> Memoria de Citas liberada." << endl;

    // 6. Liberar estructura Hospital
    delete hospital;
    cout << "? Hospital completamente destruido." << endl;
}

 void redimensionarArrayPacientes(Hospital* hospital) {
    int nuevaCapacidad = hospital->capacidadPacientes * 2;
    Paciente* nuevoArr = new Paciente[nuevaCapacidad];
    
    for (int i = 0; i < hospital->cantidadPacientes; ++i) {
        
        nuevoArr[i] = hospital->pacientes[i];
    }
    
    delete[] hospital->pacientes;
    hospital->pacientes = nuevoArr;
    hospital->capacidadPacientes = nuevaCapacidad;
    
    cout << "Array de Pacientes redimensionado a " << nuevaCapacidad << "." << endl;
}

void redimensionarArrayDoctores(Hospital* hospital) {
    int nuevaCapacidad = hospital->capacidadDoctores * 2;
    Doctor* nuevoArr = new Doctor[nuevaCapacidad];
    
    for (int i = 0; i < hospital->cantidadDoctores; ++i) {
       
        nuevoArr[i] = hospital->doctores[i];
    }
    
    delete[] hospital->doctores;
    hospital->doctores = nuevoArr;
    hospital->capacidadDoctores = nuevaCapacidad;
    
    cout << "Array de Doctores redimensionado a " << nuevaCapacidad << "." << endl;
}

void redimensionarArrayCitas(Hospital* hospital) {
    int nuevaCapacidad = hospital->capacidadCitas * 2;
    Cita* nuevoArr = new Cita[nuevaCapacidad];
    
    for (int i = 0; i < hospital->cantidadCitas; ++i) {
        nuevoArr[i] = hospital->citas[i];
    }
    
    delete[] hospital->citas;
    hospital->citas = nuevoArr;
    hospital->capacidadCitas = nuevaCapacidad;
    
    cout << "Array de Citas redimensionado a " << nuevaCapacidad << "." << endl;
}

//5.2validaciones

bool esBisiesto(int anio) {
    return (anio % 4 == 0 && anio % 100 != 0) || (anio % 400 == 0);
}

bool validarFecha(const char* fecha) {
    // 1. Verificar formato YYYY-MM-DD (longitud 10)
    if (strlen(fecha) != 10 || fecha[4] != '-' || fecha[7] != '-') {
        return false;
    }
    
    // 2. Extraer partes (YYYY, MM, DD)
    char anioStr[5], mesStr[3], diaStr[3];
    strncpy(anioStr, fecha, 4); anioStr[4] = '\0';
    strncpy(mesStr, fecha + 5, 2); mesStr[2] = '\0';
    strncpy(diaStr, fecha + 8, 2); diaStr[2] = '\0';

    int anio = atoi(anioStr);
    int mes = atoi(mesStr);
    int dia = atoi(diaStr);

    // Verificar que todas las partes sean números y no estén fuera de rango básico
    if (anio == 0 || mes == 0 || dia == 0) return false;

    // 3. Validar año, mes (1-12)
    if (mes < 1 || mes > 12) {
        return false;
    }

    // 4. Validar día según el mes (incluye bisiesto)
    int diasEnMes[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    
    if (mes == 2 && esBisiesto(anio)) {
        diasEnMes[2] = 29;
    }
    
    if (dia < 1 || dia > diasEnMes[mes]) {
        return false;
    }

    return true;
}

// 5.2 a) Validar formato y rango de Fecha (YYYY-MM-DD)
bool validarFormatoFecha(const char* fecha) {
    if (strlen(fecha) != 10 || fecha[4] != '-' || fecha[7] != '-') {
        return false;
    }
    
    char anioStr[5], mesStr[3], diaStr[3];
    strncpy(anioStr, fecha, 4); anioStr[4] = '\0';
    strncpy(mesStr, fecha + 5, 2); mesStr[2] = '\0';
    strncpy(diaStr, fecha + 8, 2); diaStr[2] = '\0';

    int anio = atoi(anioStr);
    int mes = atoi(mesStr);
    int dia = atoi(diaStr);

    if (mes < 1 || mes > 12) return false;

    int diasEnMes[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if (mes == 2 && esBisiesto(anio)) {
        diasEnMes[2] = 29;
    }
    
    if (dia < 1 || dia > diasEnMes[mes]) return false;

    return true;
}

// 5.2 b) Validar formato y rango de Hora (HH:MM)
bool validarFormatoHora(const char* hora) {
    if (strlen(hora) != 5 || hora[2] != ':') return false;

    if (!isdigit(hora[0]) || !isdigit(hora[1]) || !isdigit(hora[3]) || !isdigit(hora[4])) return false;

    int h = (hora[0] - '0') * 10 + (hora[1] - '0');
    int m = (hora[3] - '0') * 10 + (hora[4] - '0');

    if (h < 0 || h > 23) return false; 
    if (m < 0 || m > 59) return false; 

    return true;
}

bool validarHora(const char* hora) {
    // 1. Verificar formato HH:MM (longitud 5)
    if (strlen(hora) != 5 || hora[2] != ':') {
        return false;
    }

    // Verificar que los caracteres sean dígitos
    if (!isdigit(hora[0]) || !isdigit(hora[1]) || !isdigit(hora[3]) || !isdigit(hora[4])) {
        return false;
    }

    // 2. Validar hora (0-23) y minutos (0-59)
    int h = (hora[0] - '0') * 10 + (hora[1] - '0');
    int m = (hora[3] - '0') * 10 + (hora[4] - '0');

    if (h < 0 || h > 23) {
        return false; // Hora inválida
    }
    
    if (m < 0 || m > 59) {
        return false; // Minutos inválidos
    }

    return true;
}

int compararFechas(const char* fecha1, const char* fecha2) {
   
    int resultado = strcmp(fecha1, fecha2);

    if (resultado < 0) {
        return -1; // fecha1 es menor que fecha2
    } else if (resultado > 0) {
        return 1; // fecha1 es mayor que fecha2
    } else {
        return 0; // Las fechas son iguales
    }
}

bool validarCedula(const char* cedula) {
    // 1. Verificar que no esté vacía
    if (cedula == nullptr || strlen(cedula) == 0) {
        return false;
    }
    
    // 2. Verificar longitud máxima (asumiendo un max de 20 caracteres)
    if (strlen(cedula) > 20) {
        return false;
    }

    return true;
}

bool validarEmail(const char* email) {
    // 1. Verificar si está vacío
    if (email == nullptr || strlen(email) == 0) {
        return false;
    }

    // 2. Verificar presencia de '@' y '.'
    const char* at = strchr(email, '@');
    if (at == nullptr) {
        return false; // Falta '@'
    }

    const char* dot = strrchr(email, '.');
    if (dot == nullptr) {
        return false; // Falta '.'
    }

    // 3. Verificar orden y posición (básico)
    if (dot < at || at == email || dot == email + strlen(email) - 1 || dot == at + 1) {
        return false;
    }
    
    return true;
}

//5.3

char* copiarString(const char* origen) {
    // 1. Si origen es nullptr, retornar nullptr
    if (origen == nullptr) {
        return nullptr;
    }
    
    // 2. Calcular longitud e incluir el carácter nulo
    size_t longitud = strlen(origen);
    
    // 3. Crear nuevo array: new char[longitud + 1]
    char* destino = new char[longitud + 1];
    
    // 4. Copiar con strcpy()
    strcpy(destino, origen);
    
    // 5. Retornar puntero al nuevo string
    return destino;
    }

Paciente* copiarPaciente(Paciente* original) {
    if (original == nullptr) {
        return nullptr;
    }

    // 1. Crear nuevo paciente con new
    Paciente* copia = new Paciente;

    // 2. Copiar datos simples (primitivos y arrays estáticos)
    copia->id = original->id;
    strcpy(copia->nombre, original->nombre);
    strcpy(copia->apellido, original->apellido);
    strcpy(copia->cedula, original->cedula);
    strcpy(copia->email, original->email);
    strcpy(copia->telefono, original->telefono);
    
    // Copia los contadores y capacidades
    copia->cantidadHistorial = original->cantidadHistorial;
    copia->capacidadHistorial = original->capacidadHistorial;
    copia->cantidadCitas = original->cantidadCitas;
    copia->capacidadCitas = original->capacidadCitas;

    // 3. Crear nuevos arrays dinámicos (Deep Copy de historial)
    if (original->historial != nullptr && original->cantidadHistorial > 0) {
        copia->historial = new HistorialMedico[copia->capacidadHistorial];
        for (int i = 0; i < copia->cantidadHistorial; ++i) {
            // Se asume que HistorialMedico no contiene punteros y copia superficial es suficiente
            copia->historial[i] = original->historial[i]; 
        }
    } else {
        copia->historial = nullptr;
    }

    // 4. Crear nuevos arrays dinámicos (Deep Copy de citasAgendadas - IDs)
    if (original->citasAgendadas != nullptr && original->cantidadCitas > 0) {
        copia->citasAgendadas = new int[copia->capacidadCitas];
        for (int i = 0; i < copia->cantidadCitas; ++i) {
            copia->citasAgendadas[i] = original->citasAgendadas[i];
        }
    } else {
        copia->citasAgendadas = nullptr;
    }

    // 5. Retornar puntero al nuevo paciente
    return copia;
}

//6

void mostrarTitulo(const char* titulo) {
    int ancho = 80;
    cout << endl;
    cout << setfill('-') << setw(ancho) << "" << endl;
    cout << "¦" << setfill(' ') << setw((ancho - strlen(titulo)) / 2) << "" << titulo 
         << setw((ancho - strlen(titulo)) / 2 + ((ancho - strlen(titulo)) % 2)) << "¦" << endl;
    cout << setfill('-') << setw(ancho) << "" << endl;
    cout << setfill(' '); // Reset fill
}

/**
 * Lee una opción numérica del usuario, validando el rango.
 * Retorna la opción válida o -1 si hubo un error de entrada.
 */
int leerOpcion(int min, int max) {
    int opcion;
    cout << "\nIngrese su opción (" << min << "-" << max << "): ";
    if (!(cin >> opcion)) {
        cout << "? Error: Entrada no válida (solo números)." << endl;
        // Limpiar el buffer y restablecer el estado de cin
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return -1;
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Limpiar el buffer
    
    if (opcion < min || opcion > max) {
        cout << "? Error: Opción fuera de rango. Intente de nuevo." << endl;
        return -1;
    }
    return opcion;
}

// --- Menús (6.1 & 6.2) ---

void menuPacientes(Hospital* hospital);
void menuDoctores(Hospital* hospital);
void menuCitas(Hospital* hospital);

void menuPrincipal(Hospital* hospital) {
    int opcion;
    do {
        mostrarTitulo("SISTEMA DE GESTIÓN HOSPITALARIA");
        cout << "1. Gestión de Pacientes" << endl;
        cout << "2. Gestión de Doctores" << endl;
        cout << "3. Gestión de Citas" << endl;
        cout << "4. Salir" << endl;
        cout << setfill('-') << setw(80) << "" << endl;

        opcion = leerOpcion(1, 4);

        if (opcion == -1) continue;

        switch (opcion) {
            case 1: menuPacientes(hospital); break;
            case 2: menuDoctores(hospital); break;
            case 3: menuCitas(hospital); break;
            case 4: 
                cout << "\n?? Saliendo del sistema. ¡Hasta pronto!" << endl;
                destruirHospital(hospital); // Liberación crítica de memoria
                break;
        }
    } while (opcion != 4);
}

void menuPacientes(Hospital* hospital) {
    int opcion;
    do {
        mostrarTitulo("MENÚ DE GESTIÓN DE PACIENTES");
        cout << "1. Registrar nuevo paciente" << endl;
        cout << "2. Buscar paciente por cédula" << endl;
        cout << "3. Buscar paciente por nombre" << endl;
        cout << "4. Ver historial médico completo" << endl;
        cout << "5. Actualizar datos del paciente" << endl;
        cout << "6. Listar todos los pacientes" << endl;
        cout << "7. Eliminar paciente" << endl;
        cout << "0. Volver al menú principal" << endl;
        cout << setfill('-') << setw(80) << "" << endl;

        opcion = leerOpcion(0, 7);
        if (opcion == -1) continue;

        // Aquí iría la llamada a las funciones del Módulo 1 (Paciente)
        // Ejemplo (Asumiendo que existen):
        // switch (opcion) {
        //     case 1: ui_registrarPaciente(hospital); break;
        //     case 2: ui_buscarPacienteCedula(hospital); break;
        //     // ... otros casos ...
        // }

    } while (opcion != 0);
}

void menuDoctores(Hospital* hospital) {
    int opcion;
    do {
        mostrarTitulo("MENÚ DE GESTIÓN DE DOCTORES");
        cout << "1. Registrar nuevo doctor" << endl;
        cout << "2. Buscar doctor por ID" << endl;
        cout << "3. Buscar doctores por especialidad" << endl;
        cout << "4. Asignar paciente a doctor" << endl;
        cout << "5. Ver pacientes asignados a doctor" << endl;
        cout << "6. Listar todos los doctores" << endl;
        cout << "7. Eliminar doctor" << endl;
        cout << "0. Volver al menú principal" << endl;
        cout << setfill('-') << setw(80) << "" << endl;

        opcion = leerOpcion(0, 7);
        // Aquí iría la llamada a las funciones del Módulo 2 (Doctor)

    } while (opcion != 0);
}

void menuCitas(Hospital* hospital) {
    int opcion;
    do {
        mostrarTitulo("MENÚ DE GESTIÓN DE CITAS");
        cout << "1. Agendar nueva cita" << endl;
        cout << "2. Cancelar cita" << endl;
        cout << "3. Atender cita" << endl;
        cout << "4. Ver citas de un paciente" << endl;
        cout << "5. Ver citas de un doctor" << endl;
        cout << "6. Ver citas de una fecha" << endl;
        cout << "7. Ver citas pendientes" << endl;
        cout << "0. Volver al menú principal" << endl;
        cout << setfill('-') << setw(80) << "" << endl;

        opcion = leerOpcion(0, 7);
        

    } while (opcion != 0);
}

// --- Función Principal ---

int main() {
    // Inicialización del hospital
    Hospital* miHospital = inicializarHospital("Hospital Central", 10);

    // Bucle principal de la interfaz
    menuPrincipal(miHospital);

    // destruirHospital(miHospital) se llama dentro de menuPrincipal(case 4)
    
    return 0;
}
