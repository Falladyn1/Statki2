#include <iostream>
#include <ctime>
#include "czlowiek.h"
#include "si.h"

using namespace std;

int main() {
    czlowiek gracz;
    SI komputer;

    cout << "Rozmieszczanie statkow..." << endl;
    gracz.rozmiescStatkiLosowo();
    komputer.rozmiescStatkiLosowo();

    bool graTrwa = true;
    while (graTrwa) {
        cout << "\n--- TWOJA TURA ---" << endl;
        cout << gracz.pobierzPlanszeStatkow();
        cout << gracz.pobierzPlanszeStrzalow();

        PolaS celGracza = gracz.wykonajRuch();

        OkretPos* wynikGracza = komputer.sprawdzStrzalPrzeciwnika(celGracza.x, celGracza.y);

        gracz.pobierzPlanszeStrzalow().ustawPole(celGracza.x, celGracza.y, wynikGracza);

        if (wynikGracza->s) cout << "Trafiles!" << endl;
        else cout << "Pudlo." << endl;


        cout << "\n--- TURA KOMPUTERA ---" << endl;

        PolaS celSI = komputer.wykonajRuch();
        cout << "Komputer strzela w: " << char('A' + celSI.x) << celSI.y + 1 << endl;

        OkretPos* wynikSI = gracz.sprawdzStrzalPrzeciwnika(celSI.x, celSI.y);

        komputer.pobierzPlanszeStrzalow().ustawPole(celSI.x, celSI.y, wynikSI);

        if (wynikSI->s) cout << "Komputer trafil!" << endl;
        else cout << "Komputer spudlowal." << endl;

    }

    return 0;
}