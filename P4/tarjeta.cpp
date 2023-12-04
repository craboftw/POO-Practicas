//  tarjeta.cpp

#include "tarjeta.hpp"

//********************NUMERO****************************
bool luhn(const Cadena& numero);

Numero::Numero(const Cadena& num): _numero(num)
{
    Cadena::iterator it_fin = std::remove_if(_numero.begin(), _numero.end(), EsBlanco()); //Tambien se puede usar una funcion anonima
    if(it_fin != _numero.end())
    {
        _numero = _numero.substr(0, it_fin - _numero.begin());
    }
    if(std::find_if(_numero.begin(), _numero.end(), not1(EsDigito())) != _numero.end()) throw Incorrecto(Razon::DIGITOS);
    if(_numero.length() > 19 || _numero.length() < 13) throw Incorrecto(Razon::LONGITUD);
    if(!luhn(_numero)) throw Incorrecto(Razon::NO_VALIDO);
}

Numero::operator const char *() const { return _numero.c_str(); }

bool operator <(const Numero& num1, const Numero& num2) { return strcmp(num1, num2) < 0; }
//bool operator >(const Numero& num1, const Numero& num2) { return !(num1 < num2); }

//********************TARJETA****************************
std::set<Numero> Tarjeta::_numeros; //es necesario iniciar el set de numeros para que no se produzcan errores

Tarjeta::Tarjeta(const Numero& num, Usuario& u, const Fecha& caducidad): _numero(num), _usuario(&u), _caducidad(caducidad), _activa(true){
    
    Fecha hoy;
    
    if(_caducidad < hoy)//si la fecha de caducidad es menor a la del dia actual
        throw Tarjeta::Caducada(_caducidad);
    
    std::pair<std::set<Numero>::iterator,bool> pair = _numeros.insert(_numero);
    
    if(!pair.second)//si ya existia previamente ese numero, lanzamos la excepcion
        throw Tarjeta::Num_duplicado(_numero);
        
    _usuario->es_titular_de(*this);
}

Tarjeta::~Tarjeta()
{
    if(_usuario != nullptr){
        const_cast<Usuario*>(_usuario)->no_es_titular_de(*this);
    }
    
    this->_numeros.erase(_numero);
}

const Numero& Tarjeta::numero() const { return _numero; }

const Usuario* Tarjeta::titular() const { return _usuario; }

const Fecha& Tarjeta::caducidad() const { return _caducidad; }

bool Tarjeta::activa() const { return _activa; }

bool Tarjeta::activa(bool a) noexcept { 
    if(a != _activa){
        _activa = a;
    }
        return a;
}
    


void Tarjeta::anula_titular()
{
    _activa = false;
    const_cast<Usuario*&>(_usuario) = nullptr;
}

Tarjeta::Tipo Tarjeta::tipo() const {
    
    Tarjeta::Tipo tipo;
    
    if(_numero[0] == '3'){
        if((_numero[0] == '3' && _numero[1] == '4') || (_numero[0] == '3' && _numero[1] == '7'))
            tipo = Tarjeta::AmericanExpress;
        else tipo = Tarjeta::JCB;
    }
    else if(_numero[0] == '4')
        tipo = Tarjeta::VISA;
    else if(_numero[0] == '5')
        tipo = Tarjeta::Mastercard;
    else if(_numero[0] == '6')
        tipo = Tarjeta::Maestro;
    else tipo = Tarjeta::Otro;
    
    return tipo;
}

std::ostream& operator <<(std::ostream& os, const Tarjeta& t)
{
    os << t.tipo() << std::endl << t.numero() << std::endl;
    
    Cadena aux = t.titular()->nombre(); //Pasamos el nombre a una cadena auxiliar
    int i=0;
    
    while(aux[i]!='\0'){
        if (islower(aux[i]))
            aux[i]=toupper(aux[i]);
        i++;
    }
    os << aux << " ";
    
    i = 0;
    
    aux = t.titular()->apellidos(); //Pasamos los apellidos a una cadena auxiliar
    while(aux[i]!='\0'){
        if (islower(aux[i]))
            aux[i]=toupper(aux[i]);
        i++;
    }
    os << aux << std::endl;
    
    //Limpiamos fecha
    os << "Caduca: " << std::setfill ('0') << std::setw (2) << t.caducidad().mes() << "/" << std::setw (2) << (t.caducidad().anno() % 100) << std::endl;
    
    return os;
    
}

std::ostream& operator <<(std::ostream& os, const Tarjeta::Tipo& tipo)
{
    switch(tipo){
        case Tarjeta::VISA: os << "VISA"; break;
        case Tarjeta::Mastercard: os << "Mastercard"; break;
        case Tarjeta::Maestro: os << "Maestro"; break;
        case Tarjeta::JCB: os << "JCB"; break;
        case Tarjeta::AmericanExpress: os << "AmericanExpress"; break;
        case Tarjeta::Otro: os << "Tipo indeterminado"; break;
        default: os << "Error, tarjeta desconocida";
    }
    
    return os;
    
}

bool operator <(const Tarjeta& t1, const Tarjeta& t2) { return t1.numero() < t2.numero(); }
//bool operator >(const Tarjeta& t1, const Tarjeta& t2) { return !(t1 < t2); }
