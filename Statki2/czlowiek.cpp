#include "czlowiek.h"
#include <cctype>

using namespace std;

czlowiek::czlowiek() : gracz() {
}

void czlowiek::wykonajRuch(gracz& przeciwnik) {
    int rozmiar = strzalyGracza.pobierzRozmiar();
    int x = -1, y = -1;
    bool ruchPoprawny = false;

    while (!ruchPoprawny) {
        cout << "Podaj cel (np. A 1): ";
        char k;
        int w;
        cin >> k >> w;

        x = toupper(k) - 'A';
        y = w - 1;

        if (x >= 0 && x < rozmiar && y >= 0 && y < rozmiar) {
            if (strzalyGracza.sprawdz(x, y) == nullptr) {
                ruchPoprawny = true;
            }
            else {
                cout << "To pole jest juz zajete." << endl;
            }
        }
        else {
            cout << "Bledne wspolrzedne." << endl;
        }
    }

    OkretPos* wynik = przeciwnik.sprawdzStrzalPrzeciwnika(x, y);
    strzalyGracza.ustawPole(x, y, wynik);

    if (wynik->s == nullptr) {
        cout << "-> Pudlo." << endl;
    }
    else {
        cout << "-> Trafiony." << endl;
    }
}