#ifndef FECHA_HPP_
#define FECHA_HPP_
#include <iostream>

class Fecha
{
public:
    //constructores
    explicit Fecha(int dia = 0, int mes = 0, int anno = 0);
    Fecha(const char* cadena);

    const char* cadena() const;
    
    //constantes de la clase
    static const int AnnoMinimo;
    static const int AnnoMaximo;

    //operador de asignacion sumas y restas
    Fecha& operator+=(int num);
    Fecha& operator-=(int num);
    Fecha operator+(int num) const;
    Fecha operator-(int num) const;

    //incrementos
    Fecha operator++(int);
    Fecha& operator++();

    //decrementos 
    Fecha operator--(int);
    Fecha& operator--();
    

    //observadores
    int dia() const noexcept;
    int mes() const noexcept;
    int anno() const noexcept;

    class Invalida
    {
    public:
        Invalida(const char* cadena) : mensaje{cadena} {};
        const char* por_que() const noexcept { return mensaje; };
    private:
        const char* mensaje;
    };
    
private:
    int dia_, mes_, anno_;
    void valida();
};


bool operator<(const Fecha& fecha1, const Fecha& fecha2) noexcept;
bool operator<=(const Fecha& fecha1, const Fecha& fecha2) noexcept;
bool operator>(const Fecha& fecha1, const Fecha& fecha2) noexcept;
bool operator>=(const Fecha& fecha1, const Fecha& fecha2) noexcept;
bool operator==(const Fecha& fecha1, const Fecha& fecha2) noexcept;
bool operator!=(const Fecha& fecha1, const Fecha& fecha2) noexcept;

std::istream& operator>>(std::istream& is, Fecha& f);
std::ostream& operator<<(std::ostream& os, const Fecha& f);


//OBSERVADORES
inline int Fecha::dia() const noexcept
{
    return dia_;
}

inline int Fecha::mes() const noexcept
{
    return mes_;
}

inline int Fecha::anno() const noexcept
{
    return anno_;
}

#endif 
