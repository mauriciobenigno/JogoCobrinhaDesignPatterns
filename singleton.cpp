#include "singleton.h"

Singleton::Singleton()
{
     declarado=false;
}
Cobrinha* Singleton::GetInstancia(int tam)
{
    if(!declarado)
    {
        declarado=true;
        instancia=new Cobrinha(tam);
        return instancia;
    }
    return instancia;
}
