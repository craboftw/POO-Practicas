#ifndef PEDIDO_HPP_
#define PEDIDO_HPP_
#include "tarjeta.hpp"
#include "fecha.hpp"

class Pedido_Articulo;
class Usuario_Pedido;

class Pedido{
public:
    
    class Vacio{
    public:
        Vacio(Usuario& us) : _user{&us} {};
        const Usuario& usuario() const noexcept { return *_user; };
    private:
        Usuario* const _user;
    };

    class Impostor{
    public:
        Impostor(Usuario& us) : _user{&us} {};
        const Usuario& usuario() const noexcept { return *_user; };
    private:
        Usuario* const _user;
    };

    class SinStock{
    public:
        SinStock(Articulo& articulo) : _art{&articulo} {};
        const Articulo& articulo() const noexcept { return *_art; };
    private:
        const Articulo* _art;
    };
  
    Pedido(Usuario_Pedido& usped, Pedido_Articulo& pedart, Usuario& us, const Tarjeta& tar, const Fecha& fch = Fecha());

   
    int numero()             const noexcept { return _num; };
    const Tarjeta* tarjeta() const noexcept { return _tarjeta; };
    const Fecha& fecha()     const noexcept { return _fecha; };
    double total()           const noexcept { return _total; };
    static int n_total_pedidos()   noexcept { return N_pedidos; };

private:
    int _num;
    const Tarjeta* _tarjeta;
    Fecha _fecha;
    double _total;
    static int N_pedidos;
};

std::ostream& operator<<(std::ostream& os, const Pedido& pedido);
#endif 