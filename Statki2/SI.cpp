#include "SI.h"
#include <cstdlib>
#include <iostream>

using namespace std;

SI::SI() : gracz() {
}

void SI::wykonajRuch(gracz& przeciwnik) {
    int rozmiar = strzalyGracza.pobierzRozmiar();
    int x, y;

    do {
        x = rand() % rozmiar;
        y = rand() % rozmiar;
    } while (strzalyGracza.sprawdz(x, y) != nullptr);

    cout << "SI: " << char('A' + x) << " " << y + 1 << " -> ";

    OkretPos* wynik = przeciwnik.sprawdzStrzalPrzeciwnika(x, y);
    strzalyGracza.ustawPole(x, y, wynik);

    if (wynik->s != nullptr) {
        cout << "Trafiony!" << endl;
    }
    else {
        cout << "Pudlo." << endl;
    }
}