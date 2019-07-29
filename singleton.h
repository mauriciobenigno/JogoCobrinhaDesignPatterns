#ifndef SINGLETON_H
#define SINGLETON_H
#include "cobrinha.h"
class Singleton
{
private:
    Cobrinha *instancia;
    bool declarado;
public:
    Singleton();
    Cobrinha* GetInstancia(int tam);

};

#endif // SINGLETON_H
