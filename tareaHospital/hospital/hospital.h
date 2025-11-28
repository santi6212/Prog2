#ifndef HOSPITAL_HPP
#define HOSPITAL_HPP

#include <string>

class Hospital {
private:
    std::string nombre;
    std::string direccion;
    std::string telefono;

public:
    Hospital();
    Hospital(const std::string& nom, const std::string& dir, const std::string& tel);
    ~Hospital();

    void mostrarInfo() const;
};

#endif
