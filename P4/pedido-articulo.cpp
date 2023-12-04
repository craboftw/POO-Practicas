#include "pedido-articulo.hpp"
#include <iomanip>

LineaPedido::LineaPedido(double precio, unsigned cantidad) : _precio(precio), _cantidad(cantidad) {}

std::ostream& operator <<(std::ostream& os, const LineaPedido& linea){
   os << std::fixed << std::setprecision(2) << linea.precio_venta() << " €\t" << linea.cantidad();
   return os;
}

//PedidoArticulo
Pedido_Articulo::Pedidos Pedido_Articulo::ventas(Articulo& art){
   return _articulo_pedido[&art];
}

const Pedido_Articulo::ItemsPedido& Pedido_Articulo::detalle(Pedido& ped){
   return pedido_articulo_[&ped];
}

void Pedido_Articulo::pedir(Pedido& ped, Articulo& art, double precio, unsigned cantidad){
   pedido_articulo_[&ped].insert(std::make_pair(&art, LineaPedido(precio, cantidad)));
   _articulo_pedido[&art].insert(std::make_pair(&ped, LineaPedido(precio, cantidad)));
}

void Pedido_Articulo::pedir(Articulo& art, Pedido& ped, double precio, unsigned cantidad){
   pedir(ped, art, precio, cantidad);
}

std::ostream& Pedido_Articulo::mostrarDetallePedidos(std::ostream& os){
   double total = 0;
   for(auto pos = pedido_articulo_.begin(); pos != pedido_articulo_.end(); pos++)
   {
      os << "Pedido núm. " << pos->first->numero() << std::endl 
         << "Cliente: " << pos->first->tarjeta()->titular()->nombre() << std::setw(10) << std::setfill(' ')
         << "Fecha: " << pos->first->fecha() 
         << std::endl << pos->second << std::endl;
      total += pos->first->total();
   }
   os << "TOTAL VENTAS\t" << std::fixed << std::setprecision(2) << total << " €" << std::endl;
   return os;
}

std::ostream& Pedido_Articulo::mostrarVentasArticulos(std::ostream& os){
   for(auto pos = _articulo_pedido.begin(); pos != _articulo_pedido.end(); pos++)
   {
      os << "\nVentas de " << "[" << pos->first->referencia() << "] \"" 
         << pos->first->titulo() << "\"" << std::endl 
         << pos->second << std::endl;
   }
   return os;
}

std::ostream& operator <<(std::ostream& os, const Pedido_Articulo::ItemsPedido& art){
   os <<"\nPVP\tCantidad\tArtículo\n" 
      << std::setw(75) << std::setfill('=') << "\n";
   double total = 0;
   for(auto pos = art.begin(); pos != art.end(); pos++)
   {
      os << std::endl << pos->second.precio_venta() << " €" << std::setw(5) << std::setfill(' ') << pos->second.cantidad() << std::setw(5) << std::setfill(' ')
         << "[" << pos->first->referencia() << "] \"" << pos->first->titulo() << "\"" << std::endl;
      total += pos->second.precio_venta() * pos->second.cantidad();
   }
   os << std::setw(75) << std::setfill('=') 
      << "\nTotal\t" << std::fixed << std::setprecision(2) << total << " €" << std::endl;
       
   return os;
}

std::ostream& operator <<(std::ostream& os, const Pedido_Articulo::Pedidos& ped){
   os << "[Pedidos: " << ped.size() << "]\n" 
      << std::setw(103) << std::setfill('=')
      << "\nPVP\tCantidad\tFecha de venta\n"
      << std::setw(75) << std::setfill('=') << "\n";
   double total = 0;
   std::size_t cantTotal = 0;
   for(auto pos = ped.begin(); pos != ped.end(); pos++)
   {
      os << std::endl << std::fixed << std::setprecision(2) << pos->second.precio_venta() << " €" 
         << std::setw(5) << std::setfill(' ') << pos->second.cantidad() << "\t"
         << pos->first->fecha() << std::endl;
      total += pos->second.precio_venta() * pos->second.cantidad();
      cantTotal += pos->second.cantidad();
   }
   os << std::setw(75) << std::setfill('=') << "\n"
      << std::fixed << std::setprecision(2) << total << " €" << std::setw(5) << std::setfill(' ') << cantTotal;
   return os;
}
