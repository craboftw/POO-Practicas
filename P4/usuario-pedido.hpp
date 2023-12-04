#ifndef usuario_pedido_hpp
#define usuario_pedido_hpp

#include <set>
#include <map>
#include "pedido.hpp"

class Pedido;
class Usuario;

class Usuario_Pedido{
public:
    typedef std::set<Pedido*> Pedidos;
    typedef std::map<Usuario*, Pedidos> UsuarioPedidos; 
    typedef std::map<Pedido*, Usuario*> PedidoUsuario; 
    
    void asocia(Usuario& u, Pedido& p);
    void asocia(Pedido& p, Usuario u);
    
    const Pedidos& pedidos(Usuario& u);
    const Usuario* cliente(Pedido& p);
private:
    UsuarioPedidos _UsuarioPedidos;
    PedidoUsuario _PedidoUsuario;
};

#endif 
