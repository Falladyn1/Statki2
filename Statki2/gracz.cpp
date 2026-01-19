#include "gracz.h"
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

const plansza<OkretPos*>& gracz::pobierzPlanszeStatkow() const {
    return statkiGracza;
}

plansza<kratka>& gracz::pobierzPlanszeStrzalow() {
    return strzalyGracza;
}

OkretPos* gracz::sprawdzStrzalPrzeciwnika(int x, int y) {
    OkretPos* pole = statkiGracza.sprawdz(x, y);

    if (pole != nullptr) {
        if (pole->s != nullptr) {
            pole->s->ustawTrafienie(x, y);
            return new OkretPos(pole->s, x, y);
        }
        else {
            return new OkretPos(nullptr, x, y);
        }
    }

    statkiGracza.ustawPole(x, y, new OkretPos(nullptr, x, y));
    return new OkretPos(nullptr, x, y);
}

bool czyJestNaLiscie(const vector<PolaS>& lista, int x, int y) {
    for (int i = 0; i < lista.size(); i++) {
        if (lista[i].x == x && lista[i].y == y) return true;
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
    flota.clear();
    flota.reserve(10);
    statkiGracza.wyczysc();

    for (int i = 0; i < 10; i++) {
        int r = rozmiaryStatkow[i];
        vector<PolaS> wolnePola = statkiGracza.pobierzWolnePola();
        random_shuffle(wolnePola.begin(), wolnePola.end());
        bool postawiono = false;

        for (int j = 0; j < wolnePola.size(); j++) {
            PolaS start = wolnePola[j];
            bool orientacja = rand() % 2;
            bool kierunki[2] = { orientacja, !orientacja };

            for (int k = 0; k < 2; k++) {
                bool pionowo = kierunki[k];
                vector<PolaS> buforStatku;
                bool czyPasuje = true;

                for (int l = 0; l < r; l++) {
                    int x = pionowo ? start.x : start.x + l;
                    int y = pionowo ? start.y + l : start.y;

                    if (!czyJestNaLiscie(wolnePola, x, y)) {
                        czyPasuje = false;
                        break;
                    }
                    buforStatku.push_back({ x, y }); 
                }

                if (czyPasuje) {
                    statek s(r);
                    s.ustawStatek(buforStatku);
                    flota.push_back(s);

                    statek* wskaznikNaStatek = &flota.back();

                    for (int m = 0; m < buforStatku.size(); m++) {
                        PolaS punkt = buforStatku[m];
                        statkiGracza.ustawPole(punkt.x, punkt.y, new OkretPos(wskaznikNaStatek, punkt.x, punkt.y));
                    }

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
    flota.clear();
    flota.reserve(10);
    statkiGracza.wyczysc();

    for (int i = 0; i < 10; i++) {
        int dlugosc = rozmiaryStatkow[i];
        bool postawiono = false;

        while (!postawiono) {
            cout << "\n--- TWOJA PLANSZA ---\n" << statkiGracza;
            cout << "Ustaw statek o dlugosci: " << dlugosc << endl;

            char k;
            int w;
            bool pionowo;
            cout << "Podaj wspolrzedne (np. A 1) i orientacje (0-poziom, 1-pion): ";
            cin >> k >> w >> pionowo;

            int x = toupper(k) - 'A';
            int y = w - 1;

            if (x < 0 || x >= rozmiarPlanszy || y < 0 || y >= rozmiarPlanszy) {
                cout << "Bledne wspolrzedne!" << endl;
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
                for (int j = 0; j < dlugosc; j++) {
                    int cx = pionowo ? x : x + j;
                    int cy = pionowo ? y + j : y;

                    if (!statkiGracza.czyOtoczenieWolne(cx, cy)) {
                        kolizja = true;
                        break;
                    }
                    polaDoZajecia.push_back({ cx, cy });
                }
            }

            if (!kolizja) {
                statek s(dlugosc);
                s.ustawStatek(polaDoZajecia);
                flota.push_back(s);
                statek* wskaznikNaStatek = &flota.back();

                for (auto p : polaDoZajecia) {
                    statkiGracza.ustawPole(p.x, p.y, new OkretPos(wskaznikNaStatek, p.x, p.y));
                }

                postawiono = true;
            }
            else {
                cout << "Nie mozna tu postawic statku!" << endl;
            }
        }
    }
}

bool gracz::czyPrzegrana() const {
    for (int i = 0; i < flota.size(); i++) {
        if (flota[i].czyZatopiony() == false)
            return false;
    }
    return true;
}