#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>
#include "plansza.h"
#include "statek.h"
#include "OkretPos.h"
#include "gracz.h"

using namespace std;


int main() {
    gracz g;
    gracz w;

    cout << "Witaj Admirale!\n";
    cout << "1. Ustawienie RECZNE\n";
    cout << "2. Ustawienie LOSOWE\n";
    cout << "Wybierz opcje: ";

    int wybor;
    cin >> wybor;

    if (wybor == 1) {
        g.rozmiescStatkiRecznie();
        w.rozmiescStatkiLosowo();
    }
    else {
        cout << "Rozmieszczam losowo...\n";
        g.rozmiescStatkiLosowo();
        w.rozmiescStatkiLosowo();
    }

    cout << "\n===================================\n";
    cout << "GOTOWA PLANSZA STATKOW GRACZA:\n";
    cout << g.pobierzPlanszeStatkow() << endl;
    cout << w.pobierzPlanszeStatkow() << endl;
    /*cout << "===================================\n";
    cout << g.pobierzPlanszeStrzalow() << endl;
    cout << w.pobierzPlanszeStrzalow() << endl;*/

    return 0;
}