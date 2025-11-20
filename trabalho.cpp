#include <iostream>
#include <string>
#include <queue>
#include <iomanip>
#include <algorithm>

using namespace std;

int atendidos = 0;
int V = 0, A = 0, D = 0, B = 0;
int esperaMaxima = 0;
int picoLotacao = 0;

struct entrada {
    string senha;
    char prio;
    int hh;
    int mm;
};

queue<entrada> filaV, filaA, filaD, filaB;

void semPacientes(int hh, int mm) {
    cout << setw(2) << setfill('0') << hh << " "
         << setw(2) << setfill('0') << mm << " Sem pacientes aguardando atendimento" << endl;
}

void novo_paciente(string senha, char prio, int hh, int mm) {
    entrada paciente = {senha, prio, hh, mm};

    if (prio == 'V') filaV.push(paciente);
    else if (prio == 'A') filaA.push(paciente);
    else if (prio == 'D') filaD.push(paciente);
    else if (prio == 'B') filaB.push(paciente);

    int totalFila = filaV.size() + filaA.size() + filaD.size() + filaB.size();
    picoLotacao = max(picoLotacao, totalFila);
}

void atender(int hh, int mm) {
    entrada paciente;
    bool encontrado = false;

    if (!filaV.empty()) { paciente = filaV.front(); filaV.pop(); V++; encontrado = true; }
    else if (!filaA.empty()) { paciente = filaA.front(); filaA.pop(); A++; encontrado = true; }
    else if (!filaD.empty()) { paciente = filaD.front(); filaD.pop(); D++; encontrado = true; }
    else if (!filaB.empty()) { paciente = filaB.front(); filaB.pop(); B++; encontrado = true; }

    if (encontrado) {
        int espera = (hh - paciente.hh) * 60 + (mm - paciente.mm);
        esperaMaxima = max(esperaMaxima, espera);
        atendidos++;
        cout << setw(2) << setfill('0') << hh << " "
             << setw(2) << setfill('0') << mm << " "
             << "Paciente " << paciente.senha << " atendido com espera de " << espera << " min" << endl;
    } else {
        semPacientes(hh, mm);
    }
}

void exibir_dados() {
    cout << "V:" << filaV.size() << " A:" << filaA.size()
         << " D:" << filaD.size() << " B:" << filaB.size()
         << " | Atendidos:" << atendidos << endl;
}

int char_test(int ch) {
    return ch > 127;
}

int main() {
    string comando;

    cout << "---- MENU ----" << endl;
    cout << "-- TRIAGEM HOSPITALAR --" << endl;
    cout << "Para inserir um novo paciente digite C" << endl;
    cout << "Para realizar um atendimento digite A" << endl;
    cout << "Para exibir as informações sobre fila digite D" << endl;
    cout << "Para encerrar o sistema digite Q" << endl;

    while (cin >> comando) {
        if (comando == "C") {
            //cout << "Senha: " << endl;
            string senha;
            cin >> senha;
            //cout << "Prioridade: " << endl;
            char prio;
            cin >> prio;
            //cout << "Hora(formato 'hh mm'): " << endl;
            int hh, mm;
            cin >> hh >> mm;
            novo_paciente(senha, prio, hh, mm);
        } else if (comando == "A") {
            int hh, mm;
            cin >> hh >> mm;
            atender(hh, mm);
        } else if (comando == "D") {
            exibir_dados();
        } else if (comando == "Q") {
            cout << "--- RELATÓRIO FINAL ---" << endl;
            cout << "Total atendidos: " << atendidos << endl;
            cout << "Por prioridade: V=" << V << " A=" << A << " D=" << D << " B=" << B << endl;
            cout << "Pico de lotação: " << picoLotacao << endl;
            cout << "Espera máxima: " << esperaMaxima << " min" << endl;
            break;
        }
    }

    return 0;}