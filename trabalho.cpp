#include <iostream>
#include <queue>
#include <iomanip>

using namespace std;

queue<entrada> filaV;
queue<entrada> filaA;
queue<entrada> filaD;
queue<entrada> filaB;

struct entrada{
    int senha;
    char prio;
    int hh;
    int mm;
};

void novo_paciente(){
    entrada auxiliar;
    cin >> auxiliar.senha;
    cin >> auxiliar.prio;
    cin >> auxiliar.hh;
    cin >> auxiliar.mm;

    if (auxiliar.prio == 'V'){
        filaV.push(auxiliar);
    } else if (auxiliar.prio == 'A'){
        filaA.push(auxiliar);
    } else if (auxiliar.prio == 'D'){
        filaD.push(auxiliar);
    } else(auxiliar.prio == 'B');{
        filaB.push(auxiliar);
    }
}

int main(){

    queue<entrada> fila;

    cout << "---- MENU ----" << endl;
    cout << "-- TRIAGEM HOSPITALAR --" << endl;
    cout << "Para inserir um novo paciente digite C" << endl;
    cout << "Para realizar um atendimento digite A" << endl;
    cout << "Para exibir as informações sobre fila digite D" << endl;
    cout << "Para encerrar o sistema digite Q" << endl;

    string opcao = "M";

    while (opcao != "Q"){

        cin >> opcao;

        if(opcao == "C"){
            novo_paciente();
            break;
        } else if(opcao == "A"){

            break;
        } else(opcao == "D");{

            break;
        }
        
    }


    return 0;
}