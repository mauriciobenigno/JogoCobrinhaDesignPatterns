#ifndef MEMENTO_H
#define MEMENTO_H

template <class TIPO>
class Memento{
private:
    TIPO estado;
public:
    Memento(TIPO est)
    {
        estado = est;
    }
    TIPO GetMemento()
    {
        return estado;
    }
};





#endif // MEMENTO_H
