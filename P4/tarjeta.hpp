//  tarjeta.hpp

#ifndef TARJETA_HPP_
#define TARJETA_HPP_

#include <iomanip>
#include <algorithm>
#include "cadena.hpp"
#include "articulo.hpp"
#include "usuario.hpp"
#include <set>

class Usuario;

class EsDigito: public std::unary_function<char,bool>{
public:
    bool operator()(char c) const { return isdigit(c); }
};

class EsBlanco: public std::unary_function<char,bool>{
public:
    bool operator()(char c) const { return std::isspace(c); }
};

class Numero{
public:
    Numero(const Cadena& num);
    operator const char*() const;//conversion a cadena de caracteres constantes de bajo nivel
    Cadena num() const { return _numero; }
    enum Razon{LONGITUD, DIGITOS, NO_VALIDO};
    
    class Incorrecto{
    public:
        Incorrecto(const Numero::Razon r): _r(r) {}
        Numero::Razon razon() const { return _r; }
    private:
        Numero::Razon _r;
    };
    
private:
    Cadena _numero;
};

class Tarjeta{
public:
    friend class Usuario;
    enum Tipo {Otro, VISA, Mastercard, Maestro, JCB, AmericanExpress};
    Tarjeta(const Numero& num, Usuario& u, const Fecha& caducidad);
    Tarjeta(const Tarjeta& t) = delete;//no se puede copiar
    Tarjeta& operator=(const Tarjeta& t) = delete;//no se puede asignar
    ~Tarjeta();
    
    const Numero& numero() const;
    const Usuario* titular() const;
    const Fecha& caducidad() const;
          bool activa() const;
    bool activa(bool a) noexcept;
    Tipo tipo() const;
    
    
    class Caducada{
    public:
        Caducada(const Fecha& f): _fechacaducada(f) {}
        const Fecha& cuando() const { return _fechacaducada; }
    private:
        Fecha _fechacaducada;
    };
    
    class Num_duplicado{
    public:
        Num_duplicado(const Numero& num): _numero(num) {}
        const Numero& que() const { return _numero; }
    private:
        Numero _numero;
    };
    
    class Desactivada{
    public:
        Desactivada() {}
    };
    
private:
    void anula_titular();
    
    const Numero _numero;
    Usuario* const _usuario;
    const Fecha _caducidad;
    bool _activa;
    static std::set<Numero> _numeros;//necesario para comprobar que no haya numeros repetidos
};

std::ostream& operator <<(std::ostream& os, const Tarjeta& t);
std::ostream& operator <<(std::ostream& os, const Tarjeta::Tipo& tipo);
bool operator <(const Numero& num1, const Numero& num2);
//bool operator >(const Numero& num1, const Numero& num2);
bool operator <(const Tarjeta& t1, const Tarjeta& t2);
//bool operator >(const Tarjeta& t1, const Tarjeta& t2);

#endif /* tarjeta_hpp */
