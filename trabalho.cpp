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
    if (prio != 'V' && prio != 'A' && prio != 'D' && prio != 'B') {
        cout << "Prioridade" << prio << " inválida. O paciente não foi adicionado." << endl;
        return;
    }

    entrada paciente = {senha, prio, hh, mm};

    if (hh < 0 || hh > 23 || mm < 0 || mm > 59) {
        cout << "Hora ou minuto de entrada inválidos (" << hh << ":" << mm << ")" << endl;
        return;
    }

    if (prio == 'V') filaV.push(paciente);
    else if (prio == 'A') filaA.push(paciente);
    else if (prio == 'D') filaD.push(paciente);
    else if (prio == 'B') filaB.push(paciente);

    int totalFila = filaV.size() + filaA.size() + filaD.size() + filaB.size();
    picoLotacao = max(picoLotacao, totalFila);

    cout << "Paciente " << senha << " adicionado a fila " << prio << "." << endl;
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
        espera = max(0, espera);
        esperaMaxima = max(esperaMaxima, espera);
        atendidos++;

        if (hh < 0 || hh > 23 || mm < 0 || mm > 59) {
             cout << "Hora de atendimento inválida (" << hh << ":" << mm << ")" << endl;
        }

        cout << setw(2) << setfill('0') << hh << " "
             << setw(2) << setfill('0') << mm << " "
             << ".. Paciente " << paciente.senha << " atendido com espera de " << espera << " min" << endl;
    } else {
        semPacientes(hh, mm);
    }
}

void exibir_dados() {
    cout << "- - - - - - - - - - - - - - - -" << endl;
    cout << ".. Pacientes ' V ' aguardando: " << filaV.size() << endl;
    cout << ".. Pacientes ' A ' aguardando: " << filaA.size() << endl;
    cout << ".. Pacientes ' D ' aguardando: " << filaD.size() << endl;
    cout << ".. Pacientes ' B ' aguardando: " << filaB.size() << endl;
    cout << ".. Pacientes Atendidos: " << atendidos << endl;
    cout << "- - - - - - - - - - - - - - - -" << endl;
}

int main() {
    string comando;

    cout << "- - - - - - - - MENU - - - - - - - -" << endl;
    cout << "        TRIAGEM HOSPITALAR" << endl;
    cout << ".. Para inserir um novo paciente digite C .." << endl;
    cout << ".. Para realizar um atendimento digite A ( 'hh mm' ).." << endl;
    cout << ".. Para exibir o estado atual das filas digite D .." << endl;
    cout << ".. Para encerrar o sistema digite Q .." << endl;
    cout << "- - - - - - - - - - - - - - - - - - -" << endl;

    while (cin >> comando) {
        if (comando == "C") {
            cout << ".. Senha do paciente (PX): ";
            string senha;
            cin >> senha;
            cout << ".. Prioridade do paciente (V - A - D - B): ";
            char prio;
            cin >> prio;
            cout << ".. Hora do atendimento ('hh mm'): ";
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
        } else {
            cout << "Comando inválido" << endl;
        }
    }

    return 0;}