#ifndef USUARIO_HPP_
#define USUARIO_HPP_
#include <iostream>
#include <unistd.h>
#include <map>
#include <unordered_map>
#include <unordered_set>
#include "cadena.hpp"
#include "articulo.hpp"

class Tarjeta; 
class Numero;


class Clave{
public:
    Clave(const char* cad);
    bool verifica(const char* cad) const;
    const Cadena& clave() const noexcept { return _contrasena; };
    enum Razon{CORTA,ERROR_CRYPT};

    class Incorrecta{
    public:
        Incorrecta(const Razon& r) : _r{r} {};
        const Razon& razon() const noexcept { return _r; };
    private:
        Razon _r;
    };

private:
    Cadena _contrasena;
};

class Articulo;

class Usuario{
public:
    typedef std::map<Numero, Tarjeta*> Tarjetas;
    typedef std::unordered_map<Articulo*, unsigned int> Articulos;
    typedef std::unordered_set<Cadena> Usuarios;

    class Id_duplicado{
    public:
        Id_duplicado(const Cadena& cad) : _cad{cad} {};
        const Cadena& idd() const noexcept { return _cad; };
    private:
        Cadena _cad;
    };

    Usuario(const Cadena& id, const Cadena& nombre, const Cadena& apellidos, const Cadena& dir, const Clave& clv);
    Usuario(const Usuario& us) = delete;
    Usuario& operator=(const Usuario& tar) = delete;

    const Cadena& id()         const noexcept { return _id; };
    const Cadena& nombre()     const noexcept { return _nombre; };
    const Cadena& apellidos()  const noexcept { return _apellidos; };
    const Cadena& direccion()  const noexcept { return _dir; };
    const Tarjetas& tarjetas() const noexcept { return _tarjeta; };
    const Articulos& compra()  const noexcept { return _carrito; };
    std::size_t n_articulos()  const noexcept { return _carrito.size(); };

    void es_titular_de(Tarjeta& tar);
    void no_es_titular_de(Tarjeta& tar);
    void compra(Articulo& art, std::size_t cantidad = 1);
    void vaciar_carro(){ _carrito.clear(); }

    ~Usuario();
    
    friend std::ostream& operator <<(std::ostream& os, const Usuario& us);
private:
    const Cadena _id, _nombre, _apellidos, _dir;
    Clave _contrasena;
    Tarjetas _tarjeta;
    Articulos _carrito;
    static Usuarios _usuarios;
};

std::ostream& mostrar_carro(std::ostream& os, const Usuario& us);

#endif //USUARIO_HPP_
