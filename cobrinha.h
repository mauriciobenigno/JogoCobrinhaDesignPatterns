#ifndef COBRINHA_H
#define COBRINHA_H
#include "qstring.h"
#include "windows.h"
#include "qchar.h"
#include "corpo.h"
#include <QTime>
#include "QTextStream"


#include "state.h"
#include "memento.h"
//#include "singleton.h"



class Cobrinha
{
private:
    int tamanho;
    QChar *direcao; //sendo elas: c - cima, b - baixo, e - esquerda, d - direita
   // QChar direcao;
    Corpo *corpo;
    Corpo *obstaculos;
    int contObstaculos;
    QString **tela;
    QPair<int,int>*comida;
    int contador;
    int bonus;
    Memento <QPair<int,int> >*posicaoinicial;

    int contTelaBonus;
    bool ganhouBonus;
public:
    Cobrinha(int tam);
    QPair<int,int>* CoordenadaRandomica();
    QString AtualizarTela();
    void SetTamanho(int t);
    int GetTamanho();
    void AtualizaCobrinha(); //padrão de Projeto State
    void Inicializar();
    //void SetarDirecao(QChar *d);
    void SetarDirecao(int tecla);
    void AjustarTela();
    void AjustaObstaculos();
    bool VerificaBonus();
    bool VerificaColisao();
    bool PosicaoVazia(int x,int y);
    QString FimDeJogo();
};

#endif // COBRINHA_H
