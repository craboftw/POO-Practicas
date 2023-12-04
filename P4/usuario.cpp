#include "usuario.hpp"
#include "tarjeta.hpp"
#include "cadena.hpp"
#include <unistd.h>
#include <utility>
#include <random>
#include <cstring>
#include <unordered_set>
#include <iomanip>
#include <set>

//Clave

Clave::Clave(const char* cad){
    if(strlen(cad) < 5)
        throw Clave::Incorrecta(Clave::CORTA);
    
    static std::random_device gen;
    static std::uniform_int_distribution<std::size_t> dist(0, 63); 
    char const caracteres[] = "./ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";
    char salt[2] = { caracteres[dist(gen)], caracteres[dist(gen)]};
    char* cifrada = crypt(cad, salt); 
    if(cifrada == nullptr) 
        throw Clave::Incorrecta(Razon::ERROR_CRYPT);
    if(strlen(cifrada) < 13)
        throw Clave::Incorrecta(Razon::ERROR_CRYPT);
    _contrasena = cifrada;
}


bool Clave::verifica(const char* cad) const{
    return strcmp(crypt(cad, _contrasena.c_str()), _contrasena.c_str()) == 0;
}

//Usuario

std::unordered_set<Cadena> Usuario::_usuarios;

Usuario::Usuario(const Cadena& id, const Cadena& nombre, const Cadena& apellidos, const Cadena& dir, const Clave& clv) : 
    _id(id),_nombre(nombre),_apellidos(apellidos),_dir(dir),_contrasena(clv){
    if(!_usuarios.insert(id).second)
        throw Id_duplicado{id};
}


void Usuario::es_titular_de(Tarjeta& tar){
    if(this == tar.titular())
        _tarjeta.insert(std::pair<Numero, Tarjeta*>(tar.numero(), &tar));
}

void Usuario::no_es_titular_de(Tarjeta& tar){
    tar.anula_titular();
    _tarjeta.erase(tar.numero());
}

void Usuario::compra(Articulo& art, std::size_t cantidad){
    if(cantidad == 0)
        _carrito.erase(&art);
    else
    {
        if(_carrito.find(&art) == _carrito.end())
            _carrito.insert(std::pair<Articulo *, unsigned int>(&art, cantidad));
        else
            _carrito.find(&art)->second = cantidad;
    }
}


std::ostream& operator <<(std::ostream& os, const Usuario& us){
    os << us.id() << " [" << us._contrasena.clave()
       << "] " << us.nombre() << us.apellidos() << std::endl << us.direccion() << std::endl
       << "Tarjetas:" << std::endl;

    for(auto pos = us._tarjeta.begin(); pos != us._tarjeta.end(); pos++)
        os << *pos->second << std::endl;
    return os;
}


std::ostream& mostrar_carro(std::ostream& os, const Usuario& us)
{
    os << "Carrito de compra de " << us.id() << " [Artículos: "<< us.n_articulos() << "]" << std::endl
       << "Cant. Artículo"<< std::endl
       << std::setw(75) << std::setfill('=') << '\n';

    for (auto pos = us.compra().begin(); pos != us.compra().end(); pos++)
    {
        os << pos->second << "\t" << "[" << pos->first->referencia() << "] \"" 
           << pos->first->titulo() << "\", " << pos->first->f_publi().anno() << ". " << std::setprecision(2) << std::fixed << pos->first->precio() << " €" << '\n';
    }
    return os;
}

Usuario::~Usuario(){
    for(auto pos = _tarjeta.begin(); pos != _tarjeta.end(); pos++)
        pos->second->anula_titular();
    _usuarios.erase(_id);
}
