#ifndef STATE_H
#define STATE_H
#include "qdebug.h"
#include "cobrinha.h"


   /* Temos as variaveis cobra e Tela, sendo elas
    *
    * cobra: Servirá para a manipulação do corpo da cobra, mandando comando para atribuição
    * para novas coordenadas e verificação de coordenadas atuais para tratar colisões.
    *
    * Tela: Servirá para a atualização dos dados da Tela, assim fazendo sua parte para que
    * na atualização de tela, a cobra apareça conforme tem de aparecer.
    * */


class Cima{

public:
    /* Movimentação - Cima
     * Seguindo a logica, quando a cobra estiver direcionada pra cima, só podemos variar o seu
     * sentido vertical, em nosso programa temos os sentidos X (linhas- horiznontal)
     * e Y (colunas - vertical).
     *  */
    Cima(Corpo *cobra,int tamanho)
    {
        QPair <int,int>auxiliar = cobra->cauda.front();
        //sendo o argumento second o eixo Y
        if(auxiliar.first==0)//caso a cabeça da cobra esteja em cima
        {
            auxiliar.first=tamanho-1;
            cobra->cauda.push_front(auxiliar);
        }
        else
        {
            auxiliar.first--;
            cobra->cauda.push_front(auxiliar);
        }
    }
};

class Baixo{
public:
    Baixo(Corpo *cobra,int tamanho)
    {
        QPair <int,int>auxiliar = cobra->cauda.front();
        //sendo o argumento second o eixo Y
        if(auxiliar.first==tamanho-1)//caso a cabeça da cobra esteja em baixo
        {
            auxiliar.first=0;
            cobra->cauda.push_front(auxiliar);
        }
        else
        {
            auxiliar.first++;
            cobra->cauda.push_front(auxiliar);
        }
    }
};

class Esquerda{
public:
    Esquerda(Corpo *cobra,int tamanho)
    {
       // qDebug()<<"[OBJ - ESQUERDA] Iniciou operação Esquerda!";
        QPair <int,int>auxiliar = cobra->cauda.front();
        //sendo o argumento second o eixo Y
        //qDebug()<<"[Obj - Esquerda] Coordenadas X,Y "<<auxiliar.first<<","<<auxiliar.second;
        if(auxiliar.second==0)//caso a cabeça da cobra esteja a direita
        {
            //qDebug()<<"[OBJ - ESQUERDA] Passou parede!";
            auxiliar.second=tamanho-1;
            cobra->cauda.push_front(auxiliar);
        }
        else
        {
            //qDebug()<<"[OBJ - ESQUERDA] avançou!";
            auxiliar.second--;
            cobra->cauda.push_front(auxiliar);
        }
       // qDebug()<<"[OBJ - ESQUERDA] Terminou trabalhos da Esquerda!";
    }
};

class Direita{
public:
    Direita(Corpo *cobra,int tamanho)
    {
        //qDebug()<<"[OBJ - DIREITA] Iniciou operação Direita!";
        QPair <int,int>auxiliar = cobra->cauda.front();
        //sendo o argumento second o eixo Y
        //qDebug()<<"[Obj - Direita] Coordenadas X,Y "<<auxiliar.first<<","<<auxiliar.second;
        if(auxiliar.second==tamanho-1)//caso a cabeça da cobra esteja a direita
        {
           // qDebug()<<"[OBJ - DIREITA] Passou parede!";
            auxiliar.second=0;
            cobra->cauda.push_front(auxiliar);
        }
        else
        {
          // qDebug()<<"[OBJ - DIREITA] avançou!";
           auxiliar.second++;
           cobra->cauda.push_front(auxiliar);
        }
        //qDebug()<<"[OBJ - DIREITA] Terminou trabalhos da Direita!";
    }
};

#endif // STATE_H
