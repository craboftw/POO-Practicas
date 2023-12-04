#ifndef ARTICULO_HPP_
#define ARTICULO_HPP_
#include <iostream>
#include "cadena.hpp"
#include "fecha.hpp"
#include <set>

class Autor;

class Articulo{
public:
    typedef std::set<Autor*> Autores;
    class Autores_vacios {};
    Articulo(const Autores& autores, const Cadena& referencia, const Cadena& titulo, const Fecha& fecha, double precio);
    const Cadena& referencia() const noexcept { return _referencia; };
    const Cadena& titulo()     const noexcept { return _titulo; };
    const Fecha& f_publi()     const noexcept { return _fech_publi; }
    double precio()            const noexcept { return _precio; };
    double& precio()                          { return _precio; };
    const Autores& autores()   const noexcept { return _autores; };
    std::ostream& imprimirAutores(std::ostream& os, Autores autores) const;

    unsigned stock () const { return 0;}
    

    virtual void impresion_especifica(std::ostream& os) const = 0; 
    virtual ~Articulo();
protected:
    const Autores _autores;
    const Cadena _referencia, _titulo;
    const Fecha _fech_publi;
    double _precio;
};
inline Articulo::~Articulo() {};
std::ostream& operator<<(std::ostream& os, const Articulo& art); 


class ArticuloAlmacenable : public Articulo{
public:
    ArticuloAlmacenable(const Autores& autores, const Cadena& referencia, const Cadena& titulo, const Fecha& fecha, double precio, unsigned stock = 0);
    unsigned  stock() const noexcept { return _stock; };
    unsigned& stock()                { return _stock; };
    virtual void impresion_especifica(std::ostream& os) const = 0;
    virtual ~ArticuloAlmacenable();
protected:
    unsigned _stock;
};

inline ArticuloAlmacenable::~ArticuloAlmacenable() {};


class Libro : public ArticuloAlmacenable{
public:
    Libro(const Autores& autores, const Cadena& referencia, const Cadena& titulo, const Fecha& fecha, double precio, unsigned numPags, unsigned stock = 0);
    void impresion_especifica(std::ostream& os) const override;
    unsigned n_pag() const noexcept { return _num_pags; };
private:
    const unsigned _num_pags;
};


class Cederron : public ArticuloAlmacenable{
public:
    Cederron(const Autores& autores, const Cadena& referencia, const Cadena& titulo, const Fecha& fecha, double precio, unsigned tam, unsigned stock = 0);
    void impresion_especifica(std::ostream& os) const override;
    unsigned tam() const noexcept { return _tam; };
private:
    const unsigned _tam;
};

class LibroDigital : public Articulo{
public:
    LibroDigital(const Autores& autores, const Cadena& referencia, const Cadena& titulo, const Fecha& fecha, double precio, const Fecha& exp);
    const Fecha& f_expir() const noexcept { return _fech_expir; };
    void impresion_especifica(std::ostream& os) const override;
private:
    const Fecha _fech_expir;
};


class Revista : public ArticuloAlmacenable{
    public:
        Revista(const Autores& autores, const Cadena& referencia, const Cadena& titulo, const Fecha& fecha, double precio, unsigned num, unsigned peri, unsigned stock = 0): 
        ArticuloAlmacenable (autores, referencia, titulo, fecha, precio, stock), _numero(num), _periodicidad(peri){}
        unsigned numero() const noexcept       { return _numero; };
        unsigned periodicidad() const noexcept {return _periodicidad;}
        void impresion_especifica(std::ostream& os) const{
            os<< "Número: "<<_numero<<", Periodicidad: "<<_periodicidad<<" días."<<std::endl;
            os<< "\tPróximo número a partir de: "<<f_publi() + _periodicidad<< ".";
        }
    

    private:
        const unsigned _numero, _periodicidad;

};

class Autor{
public:
    Autor(const Cadena& nombre, const Cadena& apellido, const Cadena& direccion);
    const Cadena& nombre()    const noexcept { return _nombre; };
    const Cadena& apellidos() const noexcept { return _apellidos; };
    const Cadena& direccion() const noexcept { return _direccion; };
private:
    Cadena _nombre, _apellidos, _direccion;
};


#endif //ARTICULO_HPP_
