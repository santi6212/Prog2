#include "hospital/hospital.h"
#include "pacientes/pacientes.h"
#include "doctores/doctor.h"
#include "citas/citas.h"
#include "persistencia/gestor.h"
#include <iostream>

using namespace std;

void menuPrincipal(Hospital& hospital);

int main() {
    Hospital hospital("Hospital General", "Calle Principal #123", "555-1234");

    // Menú principal
    menuPrincipal(hospital);

    cout << "\n? Datos guardados. Programa finalizado.\n";
    return 0;
}
