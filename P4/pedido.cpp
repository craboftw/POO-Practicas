#include "pedido.hpp"
#include "usuario-pedido.hpp"
#include "pedido-articulo.hpp"
#include <unordered_map>
#include <iomanip>

int Pedido::N_pedidos = 0;

Pedido::Pedido(Usuario_Pedido& usped, Pedido_Articulo& pedart, Usuario& us, const Tarjeta& tar, const Fecha& fch ) :
    _num(N_pedidos + 1), 
    _tarjeta(&tar), 
    _fecha(fch), 
    _total(0){

    if(us.n_articulos() == 0) throw Vacio(us);

    if(&us != _tarjeta->titular()) throw Impostor(us);

    if(_fecha > _tarjeta->caducidad()) throw Tarjeta::Caducada{_tarjeta->caducidad()};

    if(!_tarjeta->activa()) throw Tarjeta::Desactivada{};

    Usuario::Articulos::iterator pos;
    Usuario::Articulos carrito = us.compra();
    for(pos = carrito.begin(); pos != carrito.end(); pos++)  {

        if(ArticuloAlmacenable* art = dynamic_cast<ArticuloAlmacenable*>(pos->first))
        {
            if(art->stock() < pos->second)
            {
                const_cast <Usuario::Articulos&> (us.compra()).clear(); //vaciamos carro
                
                throw SinStock{*pos->first}; 
            }
            


        }
    }
    
    for(pos = carrito.begin(); pos != carrito.end(); pos++){
        if(ArticuloAlmacenable* art = dynamic_cast<ArticuloAlmacenable*>(pos->first))
        {   art->stock() -= pos->second;
            pedart.pedir(*this, *pos->first, pos->first->precio(), pos->second);
            _total += pos->second * pos->first->precio(); //cantidad*precio
            us.compra(*pos->first, 0);
        }
        else if(LibroDigital* lib = dynamic_cast<LibroDigital*>(pos->first))
        {
            if(lib->f_expir() < fch) //si la fecha de expiracion del libro es anterior a la fecha del pedido
            {
                Usuario::Articulos::iterator aux = pos;
                us.compra(*aux->first, 0); //lo quito del carro

                if(us.n_articulos() == 0) //si despues de quitar el libro del carro se queda vacio
                    throw Vacio{us};
            }
            else //fecha correcta
            {
                Usuario::Articulos::iterator aux = pos;
                pedart.pedir(*this, *pos->first, pos->first->precio(), pos->second);
                _total += pos->second * pos->first->precio(); //cantidad*precio
                us.compra(*aux->first, 0);
            }
        }
        else
            throw std::logic_error("Tipo no conocido.");
    }
    usped.asocia(us, *this);
    N_pedidos += 1;
}

std::ostream& operator<<(std::ostream& os, const Pedido& pedido){
    os << "Núm. pedido: " << pedido.numero() << std::endl
       << "Fecha: " << pedido.fecha() << std::endl 
       << "Pagado con: " << pedido.tarjeta()->tipo() << " n.º: " << pedido.tarjeta()->numero() << std::endl 
       << "Importe: " << std::fixed << std::setprecision(2) << pedido.total() << " €" << std::endl;
    return os;
}