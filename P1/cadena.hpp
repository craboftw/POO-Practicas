//  cadena.hpp

#ifndef CADENA_HPP_
#define CADENA_HPP_

#include <iostream>
#include <ctime>
#include <locale>
#include <iterator>
#include <iomanip>
#include <exception>
#include <stdexcept>
#include <cstring>
#include <cstdio>

class Cadena{
public:
    Cadena(size_t t = 0, char c = ' ');
    Cadena(const Cadena& cad);//constructor de copia
    Cadena(Cadena&& cad);//constructor de movimiento
    Cadena(const char* a); //constructor de conversion
    Cadena substr(size_t indice, size_t tamano) const; 
    
    size_t     length() const; //observadora: devuelve longitud
    const char* c_str() const; //observadora: devuelve la cadena

    explicit operator const char* () const { return s_; }

    ~Cadena(); //destructor
    
    Cadena& operator =(const Cadena& cad);//asignacion de copia
    Cadena& operator =(Cadena&& cad);     //asignacion de movimiento
    Cadena& operator =(const char* cad);
    Cadena& operator+=(const Cadena& cad);
    
    char  operator [](size_t i) const; //observador
    char& operator [](size_t i); //modificador

  
    char  at(size_t indice) const;
    char& at(size_t indice);
    
    //iteradores
    typedef char* iterator;
    typedef const char* const_iterator;
    typedef std::reverse_iterator<iterator> reverse_iterator;
    typedef std::reverse_iterator<const_iterator> const_reverse_iterator;
    
    iterator               begin()         noexcept;
    const_iterator         begin()   const noexcept;
    iterator               end()           noexcept;
    const_iterator         end()     const noexcept;
    const_iterator         cbegin()  const noexcept;
    const_iterator         cend()    const noexcept;
    reverse_iterator       rbegin()        noexcept;
    reverse_iterator       rend()          noexcept;
    const_reverse_iterator rbegin()  const noexcept;
    const_reverse_iterator crbegin() const noexcept;
    const_reverse_iterator crend()   const noexcept;
    const_reverse_iterator rend()    const noexcept;
    
private:
    char* s_;
    size_t tam_;
};

//operadores
Cadena operator + (const Cadena&, const Cadena&);
bool  operator == (const Cadena&, const Cadena&);
bool  operator != (const Cadena&, const Cadena&);
bool  operator <  (const Cadena&, const Cadena&);
bool  operator >  (const Cadena&, const Cadena&);
bool  operator <= (const Cadena&, const Cadena&);
bool  operator >= (const Cadena&, const Cadena&);

std::ostream& operator <<(std::ostream& os, const Cadena& cad) noexcept;
std::istream& operator >>(std::istream& is, Cadena& cad) noexcept;

namespace std {
    template <> struct hash<Cadena> {
        size_t operator() (const Cadena& cad) const
        {
            return hash<string>{}(cad.c_str());
        }
    };
}

#endif 

