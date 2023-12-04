#include "fecha.hpp"
#include <ctime>
#include <locale>
#include <iostream>
#include <cstdio>

//~~~~~~~~~~~~~~Variables Constantes~~~~~~~~~~~~~~~~~~
const int Fecha::AnnoMinimo{1902};
const int Fecha::AnnoMaximo{2037};

void Fecha::valida(){
    int mes[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    bool bisiesto = anno_ % 4 == 0 && (anno_ % 100 != 0 || anno_ % 400 == 0);
    if(bisiesto)
        mes[1]++;
    if (anno_ < AnnoMinimo || anno_ > AnnoMaximo)
        throw Invalida{"Año inválido"};
    if(mes_ < 1 || mes_ > 12)
        throw Invalida{"Mes inválido"};
    if(dia_ < 1 || dia_ > mes[mes_ - 1])
        throw Invalida{"Día inválido"};
}

const char* Fecha::cadena() const {
    setlocale(LC_TIME, "es_ES.utf8");
    static char cadenaFecha[100];
    std::tm descompuesto = {};
    descompuesto.tm_mday = dia_;
    descompuesto.tm_mon = mes_ - 1;
    descompuesto.tm_year = anno_ - 1900;
    
    mktime(&descompuesto);
    strftime(cadenaFecha, sizeof cadenaFecha, "%A %e de %B de %Y", &descompuesto);
    return cadenaFecha;
}

//~~~~~~~~~~~~~~Constructores~~~~~~~~~~~~~~~~~~

Fecha::Fecha(int dia /*= 0*/, int mes /*= 0*/, int anno /*= 0*/) : dia_{dia}, mes_{mes}, anno_{anno} {
    std::time_t tiempo_calendario = std::time(nullptr);
    std::tm* tiempo_descompuesto = std::localtime(&tiempo_calendario);
    if(dia_ == 0)
        dia_ = tiempo_descompuesto->tm_mday;
    if(mes_ == 0)
        mes_ = tiempo_descompuesto->tm_mon + 1;
    if(anno_ == 0)
        anno_ = tiempo_descompuesto->tm_year + 1900;
    valida();
}

Fecha::Fecha(const char* cadena) {
    if(std::sscanf(cadena, "%d/%d/%d", &dia_, &mes_, &anno_) != 3)
        throw Invalida{"La fecha no sigue el formato dd/mm/aaa"};
    else
    {
        std::time_t tiempo_calendario = std::time(nullptr);
        std::tm* tiempo_descompuesto = std::localtime(&tiempo_calendario);
        if(dia_ == 0)
            dia_ = tiempo_descompuesto->tm_mday;
        if(mes_ == 0)
            mes_ = tiempo_descompuesto->tm_mon + 1;
        if(anno_ == 0)
            anno_ = tiempo_descompuesto->tm_year + 1900;
        valida();
    }
}


//~~~~~~~~~~~~~~Sobrecarga de operadores~~~~~~~~~~~~~~~~~~

Fecha& Fecha::operator+= (int num) {
    std::tm descompuesto = {};
    descompuesto.tm_mday = dia_ + num;
    descompuesto.tm_mon = mes_ - 1;
    descompuesto.tm_year = anno_ - 1900;
    
    mktime(&descompuesto);
    dia_ = descompuesto.tm_mday;
    mes_ = descompuesto.tm_mon + 1;
    anno_ = descompuesto.tm_year + 1900;
    valida();
    return *this;
}

Fecha& Fecha::operator-= (int num) {
    *this += -num;
    return *this;
}

Fecha Fecha::operator+ (int num) const {
    Fecha fecha{*this};
    fecha += num;
    return fecha;
}

Fecha Fecha::operator- (int num) const {
    Fecha fecha{*this};
    fecha += -num;
    return fecha;
}

Fecha Fecha::operator++ (int){ //postincremento
 
    Fecha fecha{*this};
    *this += 1;
    return fecha;
}

Fecha& Fecha::operator++ (){ //preincremento

    *this += 1;
    return *this;
}

Fecha Fecha::operator-- (int){ //postdecremento
    Fecha fecha{*this};
    *this += -1;
    return fecha;
}

Fecha& Fecha::operator-- (){ //predecremento

    *this += -1;
    return *this;
}

bool operator< (const Fecha& fecha1, const Fecha& fecha2) noexcept{
    if(fecha1.anno() < fecha2.anno())
        return true;
    else if(fecha1.anno() == fecha2.anno() && fecha1.mes() < fecha2.mes())
        return true;
    else if(fecha1.anno() == fecha2.anno() && fecha1.mes() == fecha2.mes() && fecha1.dia() < fecha2.dia())
        return true;
    else 
        return false;
}

bool operator<= (const Fecha& fecha1, const Fecha& fecha2) noexcept{
    return !(fecha1 > fecha2);
}


bool operator> (const Fecha& fecha1, const Fecha& fecha2) noexcept{
    return (fecha2 < fecha1);
}


bool operator>= (const Fecha& fecha1, const Fecha& fecha2) noexcept{
    return !(fecha1 < fecha2);
}


bool operator== (const Fecha& fecha1, const Fecha& fecha2) noexcept{
    return (fecha1.anno() == fecha2.anno() && fecha1.mes() == fecha2.mes() && fecha1.dia() == fecha2.dia());
}


bool operator!= (const Fecha& fecha1, const Fecha& fecha2) noexcept{
    return !(fecha1 == fecha2);
}


std::istream& operator>> (std::istream& is, Fecha& f){
    char cad[11]; //con char* cad = new char[11] salta valgrind
    is.getline(cad, 11);
    try
    {
        f = Fecha(cad);
    }
    catch(const Fecha::Invalida& error)
    {
        is.setstate(std::ios_base::failbit);
        throw; //relanzamiento a nivel superior
    }
    return is;
}


std::ostream& operator<< (std::ostream& os, const Fecha& f){
    os << f.cadena();
    return os;
}
