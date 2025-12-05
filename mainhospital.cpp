#include "hospital/hospital.hpp"
#include "persistencia/gestor.hpp"
#include <iostream>
#include "pacientes/operacionesPacientes.hpp"
#include "doctores/operacionesDoctores.hpp"
#include "citas/operacionesCitas.hpp"
#include "historial/operacionesHistorial.hpp"
#include <locale.h>
#include <windows.h>
using namespace std;

// ===== Declaración de menús =====
void menuPrincipal(Hospital& hospital);
void menuPacientes(Hospital& hospital);
void menuDoctores(Hospital& hospital);
void menuCitas(Hospital& hospital);
void menuHistorial(Hospital& hospital);

// ================================================================
// =========================== MAIN ===============================
// ================================================================

int main() {
    
    setlocale(LC_ALL, "Spanish");
    GestorArchivos::inicializarSistema();

    // Cargar hospital o crearlo si no existe
    Hospital hospital;
    GestorArchivos::cargarHospital(hospital);

    menuPrincipal(hospital);

  
    GestorArchivos::guardarHospital(hospital);

    cout << "\n? Datos guardados. Saliendo del sistema...\n";
    return 0;
}

// ================================================================
// ========================= MENÚ PRINCIPAL ========================
// ================================================================

void menuPrincipal(Hospital& hospital) {
    int opcion;

    do {
    	system("cls");
        cout << "\n=============================================\n";
        cout << "     SISTEMA DE GESTIÓN HOSPITALARIA v3\n";
        cout << "=============================================\n";
        cout << "1. Gestión de Pacientes\n";
        cout << "2. Gestión de Doctores\n";
        cout << "3. Gestión de Citas\n";
        cout << "4. Historial Médico\n";
        cout << "5. Información del Hospital\n";
        cout << "6. Salir\n";
        cout << "Seleccione una opción: ";
        cin >> opcion;

        switch (opcion) {
            case 1: menuPacientes(hospital); 
            system("pause");
			break;
            case 2: menuDoctores(hospital); 
            system("pause");
			break;
            case 3: menuCitas(hospital);
			system("pause");
			break;
            case 4: menuHistorial(hospital); 
			system("pause");
			break;
            case 5: hospital.mostrarInformacion(); 
			system("pause");
			break;
            case 6: cout << "Saliendo...\n"; 
			break;
            default: cout << "Opción inválida.\n";
        }

    } while (opcion != 6);
}

// ================================================================
// ========================= MENÚ PACIENTES ========================
// ================================================================

void menuPacientes(Hospital& hospital) {
    int opcion;

    do {
    	system("cls");
        cout << "\n=== GESTIÓN DE PACIENTES ===\n";
        cout << "1. Registrar paciente\n";
        cout << "2. Buscar por ID\n";
        cout << "3. Buscar por cédula\n";
        cout << "4. Modificar paciente\n";
        cout << "5. Eliminar paciente\n";
        cout << "6. Listar todos\n";
        cout << "7. Ver historial médico\n";
        cout << "8. Volver\n";
        cout << "Opción: ";
        cin >> opcion;

        switch (opcion) {
            case 1: OperacionesPacientes::registrarPaciente(hospital); 
            system("pause");
			break;
            case 2: {
                int id;
                cout << "ID: ";
                cin >> id;
                Paciente p;
                if (OperacionesPacientes::buscarPacientePorID(id, p))
                    p.mostrarInformacionCompleta();
                else
                    cout << "Paciente no encontrado.\n";
                    system("pause");
                break;
            }
            case 3: {
                char ced[20];
                cout << "Cédula: ";
                cin >> ced;
                Paciente p;
                if (OperacionesPacientes::buscarPacientePorCedula(ced, p))
                    p.mostrarInformacionCompleta();
                else
                    cout << "Paciente no encontrado.\n";
                    system("pause");
                break;
            }
            case 4: OperacionesPacientes::modificarPaciente(); 
            system("pause");
			break;
            case 5: OperacionesPacientes::eliminarPaciente(); 
			system("pause");
			break;
            case 6: OperacionesPacientes::listarTodos(); 
			system("pause");
			break;
            case 7: OperacionesPacientes::mostrarHistorialPaciente(); 
			system("pause");
			break;
            case 8: break;
            default: cout << "Opción inválida.\n";
        }

    } while (opcion != 8);
}

// ================================================================
// ========================= MENÚ DOCTORES =========================
// ================================================================

void menuDoctores(Hospital& hospital) {
    int opcion;

    do {
    	system("cls");
        cout << "\n=== GESTIÓN DE DOCTORES ===\n";
        cout << "1. Registrar doctor\n";
        cout << "2. Buscar por ID\n";
        cout << "3. Buscar por cédula\n";
        cout << "4. Modificar doctor\n";
        cout << "5. Listar todos\n";
        cout << "6. Listar por especialidad\n";
        cout << "7. Volver\n";
        cout << "Opción: ";
        cin >> opcion;

        switch (opcion) {
            case 1: OperacionesDoctores::registrarDoctor(hospital); 
			system("pause");
			break;
            case 2: {
                int id;
                cout << "ID: ";
                cin >> id;
                Doctor d;
                if (OperacionesDoctores::buscarDoctorPorID(id, d))
                    d.mostrarInformacionCompleta();
                else
                    cout << "Doctor no encontrado.\n";
                    system("pause");
                break;
            }
            case 3: {
                char ced[20];
                cout << "Cédula: ";
                cin >> ced;
                Doctor d;
                if (OperacionesDoctores::buscarDoctorPorCedula(ced, d))
                    d.mostrarInformacionCompleta();
                else
                    cout << "Doctor no encontrado.\n";
                    system("pause");
                break;
            }
            case 4: OperacionesDoctores::modificarDoctor(); 
			system("pause");
			break;
            case 5: OperacionesDoctores::listarTodos(); 
			system("pause");
			break;
            case 6: OperacionesDoctores::listarPorEspecialidad(); 
			system("pause");
			break;
            case 7: break;
            default: cout << "Opción inválida.\n";
        }

    } while (opcion != 7);
}

// ================================================================
// ========================== MENÚ CITAS ===========================
// ================================================================

void menuCitas(Hospital& hospital) {
    int opcion;

    do {
    	system("cls");
        cout << "\n=== GESTIÓN DE CITAS ===\n";
        cout << "1. Agendar cita\n";
        cout << "2. Cancelar cita\n";
        cout << "3. Atender cita\n";
        cout << "4. Listar todas\n";
        cout << "5. Volver\n";
        cout << "Opción: ";
        cin >> opcion;

        switch (opcion) {
            case 1: OperacionesCitas::agendarCita(hospital); 
			system("pause");
			break;
            case 2: OperacionesCitas::cancelarCita(); 
			system("pause");
			break;
            case 3: OperacionesCitas::atenderCita(); 
			system("pause");
			break;
            case 4: OperacionesCitas::listarTodas(); 
			system("pause");
			break;
            case 5: break;
            default: cout << "Opción inválida.\n";
        }

    } while (opcion != 5);
}

// ================================================================
// ======================== MENÚ HISTORIAL =========================
// ================================================================

void menuHistorial(Hospital& hospital) {
    int opcion;

    do {
    	system("cls");
        cout << "\n=== HISTORIAL MÉDICO ===\n";
        cout << "1. Registrar consulta\n";
        cout << "2. Ver historial de un paciente\n";
        cout << "3. Listar todo el historial\n";
        cout << "4. Volver\n";
        cout << "Opción: ";
        cin >> opcion;

        switch (opcion) {
            case 1: OperacionesHistorial::registrarConsulta(hospital); 
			system("pause");
			break;
            case 2: OperacionesHistorial::mostrarHistorialPaciente(); 
			system("pause");
			break;
            case 3: OperacionesHistorial::listarTodoHistorial(); 
			system("pause");
			break;
            case 4: break;
            default: cout << "Opción inválida.\n";
        }

    } while (opcion != 4);
}
