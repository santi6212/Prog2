#ifndef VALIDACIONES_HPP
#define VALIDACIONES_HPP

#include <string>

class Validaciones {
public:
    static bool validarCedula(const char* cedula);
    static bool validarEmail(const char* email);
    static bool validarFecha(const char* fecha);
    static bool validarHora(const char* hora);
};

#endif
