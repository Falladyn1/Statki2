#include "gracz.h"
#include "plansza.h"
#include <cstdlib> 
#include <ctime>
#include <vector>
#include <algorithm>

bool gracz::initRand = false;

gracz::gracz() : statkiGracza(10), strzalyGracza(10) {
    if (initRand == false) {
        srand(time(NULL));
        initRand = true;
    }
}

const plansza<kratka>& gracz::pobierzPlanszeStatkow() const {
    return statkiGracza;
}

const plansza<OkretPos*>& gracz::pobierzPlanszeStrzalow() const {
    return strzalyGracza;
}

bool czyJestNaLiscie(const vector<PolaS>& lista, int x, int y) {
    for (const PolaS p : lista) {
        if (p.x == x & p.y == y)
            return true;
    }
    return false;
}

void gracz::rozmiescStatkiLosowo() {
    for (int r : rozmiaryStatkow){
        vector<PolaS> wolnePola = statkiGracza.pobierzWolnePola();
        random_shuffle(wolnePola.begin(), wolnePola.end());

        bool postawiono = false;

        for (PolaS start : wolnePola) {
            bool orientacja = rand() % 2;
            bool kierunki[2] = { orientacja, !orientacja };

            for (bool pionowo : kierunki) {
                
                vector<PolaS> buforStatku;
                bool czyPasuje = true;

                for (int i = 0; i < r; i++) {
                    int x = pionowo ? start.x : start.x + i;
                    int y = pionowo ? start.y + i : start.y;

                    if (!czyJestNaLiscie(wolnePola, x, y)) {
                        czyPasuje = false;
                        break;
                    }
                    buforStatku.push_back({ x, y });
                }

                if (czyPasuje) {
                    statkiGracza.ustawWielePol(buforStatku, ZAJETY);
                    postawiono = true;
                    break; // Przerywamy pêtlê kierunków
                }
            }
            if (postawiono) break;
        }
    }
}