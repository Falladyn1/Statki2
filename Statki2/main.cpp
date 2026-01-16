#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>
#include "plansza.h"
#include "statek.h"
#include "OkretPos.h"
#include "gracz.h"
#include "czlowiek.h"

using namespace std;


int main() {

    cout << "Tworze gracza 1 (Ty)..." << endl;
    czlowiek gracz1;

    cout << "Tworze gracza 2 (Przeciwnik)..." << endl;
    czlowiek gracz2;

    gracz1.rozmiescStatkiLosowo();
    gracz2.rozmiescStatkiLosowo();
    while (true) {
        cout << "\n--- TEST RUCHU ---" << endl;
        gracz1.wykonajRuch(gracz2);
    }

    return 0;
}