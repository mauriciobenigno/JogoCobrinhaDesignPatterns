#include "cobrinha.h"
#include "qdebug.h"

Cobrinha::Cobrinha(int tam)
{
    corpo = new Corpo;
    obstaculos = new Corpo;
    tela=new QString*[tam];
    direcao =new QChar('d');
    tamanho=tam;
    contador=0;
    bonus=0;
    contObstaculos=0;
    ganhouBonus=false;
    contTelaBonus=10;
    for(int i=0;i<tam;i++)
    {
        tela[i]=new QString[tam];
    }
}

void Cobrinha::SetTamanho(int t)
{
    tamanho=t;
}
int Cobrinha::GetTamanho()
{
    return tamanho;
}


QPair <int,int>* Cobrinha::CoordenadaRandomica()
{
    QPair<int,int>*coordenadas=new QPair<int,int>;
    int x;
    int y;
    QTime time = QTime::currentTime();
    qsrand((uint)time.msec());
    for (int id = 0; id < 10; id++)
    {
        x =((rand() % (tamanho)) + 0);
    }
    for (int id = 0; id < 10; id++)
    {
        y =((rand() % (tamanho)) + 0);
    }
    coordenadas->first=x;
    coordenadas->second=y;
    return coordenadas;
}


void Cobrinha::Inicializar()
{
    for(int i=0;i<tamanho;i++)
    {
        int count=0;
        for(int j=0;j<tamanho;j++)
        {
            //tela[i][j]="---";
            tela[i][j]="  ";
            count=j;
        }
        //tela[i][count]+="---\n";
        tela[i][count]+="  \n";
    }
    //COMO ESSA É A FUNÇÃO DE INICIALIZAÇÃO, O PONTO INICIAL SERÁ DEFINIDO AQUI

    // localização da cobra
    QPair <int,int>*cobrinha;
    cobrinha = this->CoordenadaRandomica();
    if(cobrinha->second == tamanho-1)
        tela[cobrinha->first][cobrinha->second] = " G\n";
    else
        tela[cobrinha->first][cobrinha->second] = " G";

    QPair<int,int> auxiliar;
    auxiliar.first=cobrinha->first;
    auxiliar.second=cobrinha->second;
    corpo->cauda.push_front(auxiliar);

    // Salando estado inicial
    posicaoinicial=new Memento<QPair<int,int> >(auxiliar);
    // localização da comida
    comida=this->CoordenadaRandomica();
    while(comida->first==cobrinha->first)
        comida=this->CoordenadaRandomica();

    if(comida->second == tamanho-1)
        tela[comida->first][comida->second] = " O\n";
    else
        tela[comida->first][comida->second] = " O";

}

void Cobrinha::AtualizaCobrinha()
{
    /* Caso a cobra ande para a alguma direção, ela deve eliminar seu ultimo Pair
     * no objeto corpo e deve adicionar ao inicio da lista as novas coordenadas com
     * base na direção e no seu ID*, assim seguindo seu caminho
     *
     * ID - Posição atual, caso seja 25, ela deve voltar para 0, assim não batendo numa
     * "parede" ao entrar em contato com um canto.
     *
     *
     * Com base na direção a qual está setada a cobrinha, nesta função será usado
     * o padrão de projeto State, sendo que vão haver 4 estados, todos eles executam
     * uma tarefa parecida, de verificação e movimentação, após o termino dessa tarefa e suas
     * modificações*.
     *
     * Modificações - Essas modificações serão feitas diretamente no atributo de tela e no
     * pair de corpos, por meio de passagem de referencia, assim garantindo que o objeto
     * seja mesmo modificado e logo após sua execução, mostrado a classe principal 'Cobrinha'
     *
     * */
    int auxiliar = direcao->toLatin1();
    if(auxiliar==99)// 99 = c - cima
    {
        //qDebug()<<"[Atualiza Cobrinha] Criou Obj Cima. ";
        Cima *Cim = new Cima(corpo,tamanho);
        delete Cim;
    }
    else if(auxiliar==98)// 98 = b - baixo
    {
        //qDebug()<<"[Atualiza Cobrinha] Criou Obj Baixo. ";
        Baixo *Bai = new Baixo(corpo,tamanho);
        delete Bai;
    }
    else if(auxiliar==100)//100 = d - direita
    {
        //qDebug()<<"[Atualiza Cobrinha] Criou Obj Direita. ";
        Direita *Dir = new Direita(corpo,tamanho);
        delete Dir;
    }
    else if(auxiliar==101)//101 = e - esquerda
    {
        //qDebug()<<"[Atualiza Cobrinha] Criou Obj Esquerda. ";
        Esquerda *Esq = new Esquerda(corpo,tamanho);
        delete Esq;
    }

    // colocar a verificação de comida e colisão aqui
    this->AjustaObstaculos();
    if(VerificaBonus()==true)
    {
        contador++;
    }
    this->AjustarTela();
    if(VerificaColisao()==true)
    {
        Sleep(2000);
        throw FimDeJogo();
    }

    // Após atualizar a cobrinha, atualizamos  a saída



}

QString Cobrinha::AtualizarTela()
{
    //this->AjustarTela();
   // qDebug()<<"[Atualiza Tela] Iniciou";
    QString saida;
    for(int i=0;i<tamanho;i++)
    {
        for(int j=0;j<tamanho;j++)
        {
            saida+=tela[i][j];
        }
    }
    //qDebug()<<"[Atualiza Tela] Terminou";
    if(contador==3)
    {
        QPair<int,int> *auxiliar=this->CoordenadaRandomica();


        while(this->PosicaoVazia(auxiliar->first,auxiliar->second)==false)
        {   delete auxiliar;
            auxiliar=this->CoordenadaRandomica();
        }
        QPair<int,int> auxiliar2;
        auxiliar2.first=auxiliar->first+0;
        auxiliar2.second=auxiliar->second+0;
        obstaculos->cauda.push_front(auxiliar2);
        contObstaculos++;
        ganhouBonus=true;
        bonus+=10;
        contador=0;
    }

    saida+="[STATUS] Tamanho: "+QString::number(corpo->cauda.size())+" Pontuacao Total: "+QString::number((corpo->cauda.size()*10)+bonus-10);
    saida+=" - por alimento: "+QString::number(corpo->cauda.size()*10-10)+" - por bonus: "+QString::number(bonus)+"\n";

    int auxiliar = direcao->toLatin1();
    saida+="[STATUS]";
    switch(auxiliar)
    {
        case 98:
            saida+="Direcao: baixo ";
            break;
        case 99:
            saida+="Direcao: cima ";
            break;
        case 100://d - baixo
            saida+="Direcao: direita ";
            break;
        case 101://w - cima
            saida+="Direcao: esquerda ";
            break;
     }
    saida+="- Posicao inicial: X "+QString::number(posicaoinicial->GetMemento().first+1)+" Y "+QString::number(posicaoinicial->GetMemento().second+1);
    saida+=" - Posicao Atual: X "+QString::number(corpo->cauda.at(0).first+1)+" Y "+QString::number(corpo->cauda.at(0).second+1);

    saida+="\n[STATUS] Obstaculos: "+QString::number(contObstaculos)+"\n";
   if(ganhouBonus==true)
   {
       if(contTelaBonus==0)
       {
           ganhouBonus=false;
           contTelaBonus=10;
       }
       else if(contTelaBonus!=0)
       {
           saida+="\n\n[UAAAAAAAL  ----- QUE LINDO ---- GANHOU BONUS  ----- PARABAINX ]\n";
           contTelaBonus--;
       }
       else
       {
           contTelaBonus--;
       }
    }
    return saida;
}
// void Cobrinha::SetarDirecao(QChar *d)
void Cobrinha::SetarDirecao(int tecla)
{
    int auxiliar = direcao->toLatin1();
    switch(tecla)
    {
        case 97://a - esquerda
            tecla=101;
            break;
        case 100://d - direita
            tecla=100;
            break;
        case 115://d - baixo
            tecla=98;
            break;
        case 119://w - cima
            tecla=99;
            break;
        case 120://x - baixo
            tecla=98;
            break;
     }

     //int auxiliar2 = d->toLatin1();
     //qDebug()<<"[Setar Direção] Direcao atual - "<<auxiliar<<", Direcao nova - "<<tecla;

     if(auxiliar==99&&tecla==98)
     {
         //qDebug()<<"[Setar Direção] Nenhuma direção setada, cima pra baixo não pode. ";
     }
     else if(auxiliar==98&&tecla==99)
     {
         //qDebug()<<"[Setar Direção] Nenhuma direção setada, baixo pra cima não pode. ";
     }
     else if(auxiliar==100&&tecla==101)
     {
         //qDebug()<<"[Setar Direção] Nenhuma direção setada, esquerda pra direita não pode. ";
     }
     else if(auxiliar==101&&tecla==100)
     {
         //qDebug()<<"[Setar Direção] Nenhuma direção setada, direita pra esquerda não pode. ";
     }
     else
     {
         if(tecla==99)// 99 = c - cima
         {
            // qDebug()<<"[Setar Direção] Direção setada - CIMA. ";
             direcao=new QChar('c');
         }
         else if(tecla==98)// 98 = b - baixo
         {
             //qDebug()<<"[Setar Direção] Direção setada - BAIXO. ";
             direcao=new QChar('b');
         }
         else if(tecla==100)//100 = d - direita
         {
             //qDebug()<<"[Setar Direção] Direção setada - DIREITA. ";
             direcao=new QChar('d');
         }
         else if(tecla==101)//101 = e - esquerda
         {
             //qDebug()<<"[Setar Direção] Direção setada - ESQUERDA. ";
             direcao=new QChar('e');
         }
     }
 }
 void Cobrinha::AjustarTela()
 {
     /*
      * AQUI SERÁ FEITA A FUNÇÃO QUE COLOCA A COBRA EM LUGARES DA TELA E APAGA ELA DE LUGARES ONDE
      * A MESMA NÃO SE ENCONTRA MAIS, LEMBRANDO QUE SÓ AJUSTA, NÃO FAZ IMPRESSÃO ALGUMA.
      * */
     //beta
     for(int i=0;i<tamanho;i++)
     {
         int count=0;
         for(int j=0;j<tamanho;j++)
         {
             tela[i][j]="  ";
             count=j;
         }
         tela[i][count]+="  \n";
     }
     QPair<int,int> auxiliar;

     // ajuste local dos obstaculos
     if(obstaculos->cauda.size()>0)
     {
         for(int i = 0; i<obstaculos->cauda.size()-1;i++)
         {
             auxiliar=obstaculos->cauda.at(i);
                 if(auxiliar.second==tamanho-1)// caso ela esteja no fim da linha
                    tela[auxiliar.first][auxiliar.second] = " T\n";
                 else
                    tela[auxiliar.first][auxiliar.second] = " T";
         }
     }

     //qDebug()<<"[Ajuste de Tela] Instanciou um par. ";
     //qDebug()<<"[Ajuste de Tela] Tamanho do corpo: "<<corpo->cauda.size();
     for(int i = 0; i<corpo->cauda.size();i++)
     {
         auxiliar=corpo->cauda.at(i);
         //qDebug()<<"[Ajuste de Tela] Coordenadas["<<i<<"] X,Y "<<auxiliar.first<<","<<auxiliar.second;
         if(i==0)//A cabeça eu decidi nomear com G
         {
             if(auxiliar.second==tamanho-1)// caso ela esteja no fim da linha
                tela[auxiliar.first][auxiliar.second] = " G\n";
             else
             {
                //qDebug()<<"[Ajuste de Tela] Setou nova coordenada. ";
                tela[auxiliar.first][auxiliar.second] = " G";
             }

         }
         else //O corpo com X
         {
             if(auxiliar.second==tamanho-1)// caso ela esteja no fim da linha
                tela[auxiliar.first][auxiliar.second] = " X\n";
             else
                tela[auxiliar.first][auxiliar.second] = " X";
         }
     }
     // ajuste local da comida
     if(comida->second == tamanho-1)
         tela[comida->first][comida->second] = " O\n";
     else
         tela[comida->first][comida->second] = " O";

}

bool Cobrinha::VerificaBonus()
{
    QPair<int,int>cabeca=corpo->cauda.first();
    if(cabeca.first==comida->first&&cabeca.second==comida->second)
    {
        //Tratar coordenad aprar não colidir com o corpo
        comida=this->CoordenadaRandomica();
        while(this->PosicaoVazia(comida->first,comida->second)==false)
            comida=this->CoordenadaRandomica();


        //tratar aqui
        return true;
    }
    else
    {
        corpo->cauda.pop_back();
        return false;
    }
    return true;
}
bool Cobrinha::VerificaColisao()
{
    if(obstaculos->cauda.isEmpty())
    {
        return false;
    }
    for(int i=0;i<obstaculos->cauda.size();i++)
    {
        if(corpo->cauda.first()==obstaculos->cauda.at(i))
        {
            return true;//houve colisão
        }
    }
    return false; //não houve colisão
}
void Cobrinha::AjustaObstaculos()
{
    QList<QPair <int,int> >temporario=obstaculos->cauda;
    obstaculos->cauda.clear();
    for(int i=0;i<contObstaculos;i++)
    {
        obstaculos->cauda.push_front(temporario.at(i));
    }
    for(int i=1;i<corpo->cauda.size();i++)
    {
        obstaculos->cauda.push_back(corpo->cauda.at(i));
    }
}
bool Cobrinha::PosicaoVazia(int x,int y)
{
    QPair <int,int> desbugar;
    for(int i=0;i<obstaculos->cauda.size();i++)
    {
        desbugar=obstaculos->cauda.at(i);
        if(desbugar.first==x&&desbugar.second==y)
            return false;
    }
    return true;
}

QString Cobrinha::FimDeJogo()
{
    QString saida;
    saida+="-------------[ FIM DE JOGO ]-------------";
    saida+="\nTamanho da cobra: "+QString::number(corpo->cauda.size());
    saida+="\nPontuacao por tamanho: "+QString::number((corpo->cauda.size()*10)-10);
    saida+="\nPontuacao por bonus: "+QString::number(bonus);
    saida+="\nQuantidade de obstaculos: "+QString::number(bonus/10);
    saida+="\nPosicao inicial: Linha "+QString::number(posicaoinicial->GetMemento().first+1)+" Coluna "+QString::number(posicaoinicial->GetMemento().second+1);
    saida+="\nPosicao final: Linha "+QString::number(corpo->cauda.at(0).first+1)+" Coluna "+QString::number(corpo->cauda.at(0).second+1);
    saida+="\n-------------[#SUAVAO]------------------\n";
    return saida;
}
