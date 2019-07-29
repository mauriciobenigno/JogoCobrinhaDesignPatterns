#include <QCoreApplication>
#include "iostream"
#include "qstring.h"
#include "cobrinha.h"
#include "qdebug.h"
#include "singleton.h"
#include <stdlib.h>
#include <conio.h>

#include "QTextStream"
using namespace std;

Cobrinha *A;
Singleton B;
Memento<int> *dificuldade;

void Iniciar()
{
    int num;
    cout<<"-------------[ MENU ]-------------"<<endl;
    cout<<"Digite o tamanho da Matriz: "<<endl;
    cin>>num;
    cout<<"----------------------------------"<<endl;
    A = B.GetInstancia(num);
    system("CLS");
    cout<<"-------------[ MENU ]-------------"<<endl;
    cout<<"Digite o nivel de dificuldade: \n1 - Expert\n2 - Normal\n3 - Easy\n4 - VeriEasy\n5 - Filinho da mamae"<<endl;
    cout<<"----------------------------------"<<endl;
    cin>>num;

    system("CLS");
    switch(num)
    {
        case 1:
           dificuldade=new Memento<int>(10);
        break;
        case 2:
           dificuldade=new Memento<int>(100);
        break;
        case 3:
           dificuldade=new Memento<int>(1000);
        break;
        case 4:
           dificuldade=new Memento<int>(2000);
        break;
        case 5:
            cout<<"-------------[ MENU ]-------------"<<endl;
            cout<<"QUERIA SER ESPERTO NÉ \n APRENDE A JOGAR MANE\n VOU TE ENSINAR DA MELHOR FORMA"<<endl;
            cout<<"----------------------------------"<<endl;

            Sleep(1000);
            system("CLS");
            cout<<"-------------[ MENU ]-------------"<<endl;
            cout<<"MUAHAHAHAHAHAHAHAHAHAH #SUAVAO"<<endl;
            cout<<"----------------------------------"<<endl;
            Sleep(1000);
            system("CLS");
           dificuldade=new Memento<int>(2);
        break;
    default:
        cout<<"-------------[ MENU ]-------------"<<endl;
        cout<<"VOCE NAO DIGITOU UM NUMERO VALIDO\n AGORA VAI JOGAR NO NIVEL INFERNAL"<<endl;
        cout<<"----------------------------------"<<endl;

        Sleep(1000);
        system("CLS");
        cout<<"-------------[ MENU ]-------------"<<endl;
        cout<<"MUAHAHAHAHAHAHAHAHAHAH #SUAVAO"<<endl;
        cout<<"----------------------------------"<<endl;
        Sleep(1000);
        system("CLS");
        dificuldade=new Memento<int>(2);
    }

    system("CLS");
}


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    Iniciar();
    A->Inicializar();
    QTextStream(stdout) <<A->AtualizarTela();

    for(;;)
    {
        Sleep(dificuldade->GetMemento());
        if(kbhit()!=0)
            A->SetarDirecao(_getch());
        try{
            A->AtualizaCobrinha();
            system("CLS");

                QTextStream(stdout) <<A->AtualizarTela();
            }
            catch(QString erro)
            {
                system("CLS");
                QTextStream(stdout) <<erro;
                break;
            }

    }

    return a.exec();
}
