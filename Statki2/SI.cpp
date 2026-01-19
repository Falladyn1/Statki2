#include "SI.h"
#include <cstdlib>
#include <iostream>

using namespace std;

SI::SI() : gracz() {
}

PolaS SI::wykonajRuch() {
    int rozmiar = strzalyGracza.pobierzRozmiar();
    int x, y;

    do {
        x = rand() % rozmiar;
        y = rand() % rozmiar;
    } while (strzalyGracza.sprawdz(x, y) != PUSTY);

    return { x, y };
}