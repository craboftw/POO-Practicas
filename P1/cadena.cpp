#include "cadena.hpp"

//~~~~~~~~~~~~~~Constructores~~~~~~~~~~~~~~~~~~

Cadena::Cadena (size_t t, char c ): s_{new char[t+1]},tam_{t}{
    for(size_t i = 0; i < tam_; i++){
        s_ [i] = c;
    }
    s_[tam_] = '\0';
}

Cadena::Cadena (const Cadena& otra): s_{new char[otra.tam_+1]}, tam_{otra.tam_}{
    strcpy(s_,otra.s_);
    s_[tam_] = '\0';
}


Cadena::Cadena (Cadena&& otra): s_{otra.s_}, tam_{otra.tam_}{
    otra.s_ = new char[1];
    otra.s_[0] = '\0';
    otra.tam_ = 0;
}

Cadena::Cadena(const char* c): tam_{strlen(c)}{
    s_ = new char[tam_ + 1];
    strcpy(s_,c);
    s_[tam_] = '\0';
}

Cadena::~Cadena(){
    delete[] s_;
}


Cadena Cadena::substr(size_t indice, size_t tamano) const{
    if(indice >= tam_ || tamano > (tam_ - indice))
        throw std::out_of_range("Error: Indice fuera de rango en substr");
    
    char* aux = new char[tamano + 1];
    size_t j = 0;
    size_t fin = indice + tamano;
    
    while(indice < fin){
        aux[j] = s_[indice];
        ++indice;
        ++j;
    }
    
    aux[j] = '\0';
    
    Cadena devolver{aux};
    
    delete[] aux;
    
    return devolver;
}


const char* Cadena::c_str() const { return s_; }
/* explicit operator const char*() const {
        char nueva[tam_ + 1] ;
        for(size_t i = 0; i< tam_; i++){
            nueva[i] = s_[i];
        }
        nueva[tam_] = '\0';
        return nueva;
    }*/

size_t Cadena::length() const { return tam_; }


//~~~~~~~~~~~~~~Sobrecarga de operadores~~~~~~~~~~~~~~~~~~

Cadena& Cadena::operator=(const char* cad){
    tam_= strlen(cad);
    delete[] s_;
    s_ = new char[tam_ + 1];
    strcpy(s_, cad);
    s_[tam_] = '\0';
    return *this;
}

Cadena& Cadena::operator=(const Cadena& otra){
    if(this != &otra){
        if(tam_ != otra.tam_){
            delete[] s_;
            tam_= otra.tam_;
            s_ = new char[tam_ + 1];
        }
        strcpy(s_, otra.s_);
        s_[tam_] = '\0';
    }
    return *this;
}

Cadena& Cadena::operator=(Cadena&& otra){
    if(this != &otra){
        delete[] s_;
        s_ = otra.s_;
        tam_= otra.tam_;
        s_[tam_] = '\0';
        otra.s_ = new char [1];

        otra.s_[0] = '\0';
        otra.tam_ = 0;
    }
    return *this;
}

Cadena& Cadena::operator +=(const Cadena& otra){
    char *temporal= new char[tam_ + 1];
    strcpy(temporal, s_);
    delete[] s_;
    tam_ += otra.tam_;
    s_ = new char[tam_+1];
    sprintf(s_, "%s%s", temporal, otra.s_);
    delete[] temporal;
    
    return *this;
}

Cadena operator +(const Cadena& cadenaUno, const Cadena& cadenaDos){
    Cadena temporal {cadenaUno};
    temporal += cadenaDos;
    return temporal; }


bool operator ==(const Cadena& cad1, const Cadena& cad2){
    return strcmp(cad1.c_str(), cad2.c_str()) == 0 && cad1.length() == cad2.length();
}

bool operator !=(const Cadena& cad1, const Cadena& cad2){
    return !(cad1 == cad2);
}

bool operator <(const Cadena& cad1, const Cadena& cad2){
    return strcmp(cad1.c_str(), cad2.c_str()) < 0;
}

bool operator >(const Cadena& cad1, const Cadena& cad2){
    return strcmp(cad1.c_str(), cad2.c_str()) > 0;
}

bool operator <=(const Cadena& cad1, const Cadena& cad2){
    return (cad1 < cad2 || cad1 == cad2);
}

bool operator >=(const Cadena& cad1, const Cadena& cad2){
    return (!(cad1 < cad2) || cad1 == cad2);
}

char  Cadena::operator [](size_t indice)const { return s_[indice]; }
char& Cadena::operator [](size_t indice)      { return s_[indice]; }

char Cadena::at(size_t indice) const{
    if(indice >= tam_)
        throw std::out_of_range("Error. Indice fuera de rango en Cadena::at const");
    
    return s_[indice];
}
char& Cadena::at(size_t indice){
    if(indice >= tam_)
        throw std::out_of_range("Error. Indice fuera de rango en Cadena::at");
    
    return s_[indice];
}

std::ostream& operator <<(std::ostream& os, const Cadena& cad) noexcept{
    os << cad.c_str();
    return os;
}

std::istream& operator >>(std::istream& is, Cadena& cad) noexcept{
    char *temporal = new char[33]{'\0'};
    is>>std::setw(33)>>temporal;
    cad=Cadena{temporal};
    delete[] temporal;
    return is;
}

//~~~~~~~~~~~~~~Iteradores~~~~~~~~~~~~~~~~~~

Cadena::iterator Cadena::begin()              noexcept { return s_; }
Cadena::const_iterator Cadena::begin()  const noexcept { return s_; }
Cadena::iterator Cadena::end()                noexcept { return s_ + tam_; }
Cadena::const_iterator Cadena::end()    const noexcept { return s_ + tam_; }
Cadena::const_iterator Cadena::cbegin() const noexcept { return s_; }
Cadena::const_iterator Cadena::cend()   const noexcept { return s_ + tam_; }
Cadena::reverse_iterator Cadena::rbegin()     noexcept { return reverse_iterator(end()); }
Cadena::reverse_iterator Cadena::rend()       noexcept { return reverse_iterator(begin()); }

Cadena::const_reverse_iterator Cadena::crend()   const noexcept{ 
    return Cadena::const_reverse_iterator(cbegin()); }
Cadena::const_reverse_iterator Cadena::crbegin() const noexcept{ 
    return Cadena::const_reverse_iterator(cend()); }
Cadena::const_reverse_iterator Cadena::rend()    const noexcept{ 
    return Cadena::const_reverse_iterator(cbegin()); }
Cadena::const_reverse_iterator Cadena::rbegin()  const noexcept{ 
    return Cadena::const_reverse_iterator(cend()); }

