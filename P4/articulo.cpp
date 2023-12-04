#include "articulo.hpp"
#include <iomanip>

Articulo::Articulo(const Autores& autores, const Cadena& referencia, const Cadena& titulo, 
        const Fecha& fecha, double precio) :_autores(autores),_referencia(referencia),_titulo(titulo),_fech_publi(fecha),_precio(precio)
{
    if(_autores.empty()) 
        throw Autores_vacios{};
}

ArticuloAlmacenable::ArticuloAlmacenable(const Autores& autores, const Cadena& referencia, const Cadena& titulo, const Fecha& fecha, double precio, unsigned stock ) :
    Articulo(autores, referencia, titulo, fecha, precio),_stock(stock){}

Libro::Libro(const Autores& autores, const Cadena& referencia, const Cadena& titulo, const Fecha& fecha, double precio, unsigned numPags, unsigned stock ) :
    ArticuloAlmacenable(autores, referencia, titulo, fecha, precio, stock), _num_pags(numPags){}

Cederron::Cederron(const Autores& autores, const Cadena& referencia, const Cadena& titulo, 
const Fecha& fecha, double precio, unsigned tam, unsigned stock ) :
    ArticuloAlmacenable(autores, referencia, titulo, fecha, precio, stock), _tam(tam){}


LibroDigital::LibroDigital(const Autores& autores, const Cadena& referencia, const Cadena& titulo, const Fecha& fecha, double precio, const Fecha& exp) :
Articulo(autores, referencia, titulo, fecha, precio),_fech_expir(exp){}


Autor::Autor(const Cadena& nombre, const Cadena& apellido, const Cadena& direccion) : _nombre(nombre), _apellidos(apellido), _direccion(direccion){}

void Libro::impresion_especifica(std::ostream& os) const{
    os << n_pag() << " págs., " << stock() << " unidades.";
}

void Cederron::impresion_especifica(std::ostream& os) const{
    os << tam() << " MB, " << stock() << " unidades.";
}

void LibroDigital::impresion_especifica(std::ostream& os) const{
    os << "A la venta hasta el " << f_expir() << ".";
}


std::ostream& operator<<(std::ostream& os, const Articulo& art){
    os << "[" << art.referencia() << "] " 
       << "\"" << art.titulo() << "\", de ";

    for(auto pos = art.autores().begin(), aux = pos; pos != art.autores().end(); pos++, aux++)
    {
        if(pos == art.autores().begin())
            os << (*pos)->apellidos();
        else   
            os << ", " << (*pos)->apellidos(); 
    }

    os << ". " << art.f_publi().anno() 
       << ". " << std::fixed << std::setprecision(2) 
       << art.precio() << " €\n\t";
    art.impresion_especifica(os);
    return os;
}
