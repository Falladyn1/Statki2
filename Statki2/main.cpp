#include <iostream>
#include <ctime>
#include "czlowiek.h"
#include "si.h"

using namespace std;

int main() {
    srand(time(NULL));

    czlowiek gracz;
    SI komputer;

    gracz.rozmiescStatkiLosowo();
    komputer.rozmiescStatkiLosowo();

    cout << "\n--- TWOJA FLOTA ---" << endl;
    cout << gracz.pobierzPlanszeStatkow();

    cout << "\n--- RADAR (STRZALY) ---" << endl;
    cout << gracz.pobierzPlanszeStrzalow();

    gracz.wykonajRuch(komputer);


    cout << "\n[Tura Komputera]" << endl;
    komputer.wykonajRuch(gracz);

    cout << "\nTwoja flota po ataku:" << endl;
    cout << gracz.pobierzPlanszeStatkow();
    return 0;
}