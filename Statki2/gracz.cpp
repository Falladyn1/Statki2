#include "gracz.h"
#include "plansza.h"
#include <cstdlib> 
#include <ctime>
#include <vector>
#include <algorithm>
#include <cctype>

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
        if (p.x == x && p.y == y)
            return true;
    }
    return false;
}

bool parsujWspolrzedne(char k, int w, int rozmiarPlanszy, int& outX, int& outY) {
    int x = toupper(k) - 'A';
    int y = w - 1;

    if (x >= 0 && x < rozmiarPlanszy && y >= 0 && y < rozmiarPlanszy) {
        outX = x;
        outY = y;
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
                    break;
                }
            }
            if (postawiono) break;
        }
    }
}

void gracz::rozmiescStatkiRecznie() {
    int rozmiarPlanszy = statkiGracza.pobierzRozmiar();

    for (int dlugosc : rozmiaryStatkow) {
        bool postawiono = false;

        while (!postawiono) {
            cout << "\n--- TWOJA PLANSZA ---\n";
            cout << statkiGracza;
            cout << "Ustaw statek o dlugosci: " << dlugosc << endl;

            char k;
            int w;
            bool pionowo;

            cout << "Podaj wspolrzedne (np. A 1) i orientacje (0-poziom, 1-pion): ";
            cin >> k >> w >> pionowo;

            if (cin.fail()) {
                cin.clear();
                cin.ignore(1000, '\n');
                cout << "Blad wczytywania! Sprobuj ponownie." << endl;
                continue;
            }

            int x, y;
            if (!parsujWspolrzedne(k, w, rozmiarPlanszy, x, y)) {
                cout << "Nieprawidlowe wspolrzedne lub poza plansza!" << endl;
                continue;
            }

            bool kolizja = false;
            vector<PolaS> polaDoZajecia;

            if (pionowo) {
                if (y + dlugosc > rozmiarPlanszy) kolizja = true;
            }
            else {
                if (x + dlugosc > rozmiarPlanszy) kolizja = true;
            }

            if (!kolizja) {
                for (int i = 0; i < dlugosc; i++) {
                    int cx = pionowo ? x : x + i;
                    int cy = pionowo ? y + i : y;

                    if (!statkiGracza.czyOtoczenieWolne(cx, cy)) {
                        kolizja = true;
                        break;
                    }
                    polaDoZajecia.push_back({ cx, cy });
                }
            }

            if (!kolizja) {
                statkiGracza.ustawWielePol(polaDoZajecia, ZAJETY);
                postawiono = true;
            }
            else {
                cout << "Blad! Statek nie miesci sie lub dotyka innego statku." << endl;
            }
        }
    }
    cout << "\n--- GOTOWE ---\n";
    cout << statkiGracza;
}