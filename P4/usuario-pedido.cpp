#include "usuario-pedido.hpp"

void Usuario_Pedido::asocia(Usuario& u, Pedido& p){
    _UsuarioPedidos[&u].insert(&p);
    _PedidoUsuario.insert(std::make_pair(&p, &u));
}

void Usuario_Pedido::asocia(Pedido& p, Usuario u) { asocia(u,p); }

const Usuario_Pedido::Pedidos& Usuario_Pedido::pedidos(Usuario& u){ 
    return _UsuarioPedidos.find(&u)->second; }

const Usuario* Usuario_Pedido::cliente(Pedido& p){
   std::map<Pedido*, Usuario*>::const_iterator it = _PedidoUsuario.find(&p);
   if(it != _PedidoUsuario.end())
       return(it->second);
   else
       return(nullptr);
}

