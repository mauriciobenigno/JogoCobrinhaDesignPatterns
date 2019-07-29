#ifndef CORPO_H
#define CORPO_H
#include "qpair.h"
#include "qlist.h"


/* SERÁ CRIADA UMA LISTA CONTENDO O TAMANHO E AS COORDENADAS DE ONDE  A COBRA ESTÁ
 * ATUALMENTE, A CADA ATUALIZAÇÃO É CHECADO SE A CABEÇA SE ENCONTRA EM ALGUMA DAS COOR
 * DENADAS DA CAUDA, CASO ESTEJA É DADO O FIM DO JOGO.
 *
 * O CORPO É FEITO DE UMA LISTA DE PAR COM DOIS INT'S
 * SENDO O PRIMEIRO INT A COORD X E O SEGUNDO A COORD Y
 *
 * O CORPO NÃO TERÁ O MESMO CARACTERE DO PRIMEIRO(CABEÇA)
 * FUTURAMENTE SERÁ TENTADA A IMPLEMENTAÇÃO GRAFICA
 * */


class Corpo
{
    int tamanho;

public:
    QList<QPair<int,int> > cauda;
    Corpo();
    void Aumentar(); // sempre que chamada essa função, será feito o aumento do cumpri
    // mento da cobra, sendo que a ultima posição deva ser repetida, enquando as
    // demais se deslocam uma posição

    int calculaPontuacaoMinima(); //esta vai verificar com base no cumprimento a
    //pontuação minina, sendo que a extra será calculada por fora e somada a pontuação
    //final


};

#endif // CORPO_H
