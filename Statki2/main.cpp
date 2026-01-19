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

        kratka wynikKratka = PUDLO;
        if (wynikGracza->s != nullptr) {
            wynikKratka = TRAFIONY;
        }

        gracz.pobierzPlanszeStrzalow().ustawPole(celGracza.x, celGracza.y, wynikKratka);

        if (wynikGracza->s) cout << "Trafiles!" << endl;
        else cout << "Pudlo." << endl;

        delete wynikGracza;

        cout << "\n--- TURA KOMPUTERA ---" << endl;

        PolaS celSI = komputer.wykonajRuch();
        cout << "Komputer strzela w: " << char('A' + celSI.x) << celSI.y + 1 << endl;

        OkretPos* wynikSI = gracz.sprawdzStrzalPrzeciwnika(celSI.x, celSI.y);

        kratka wynikKratkaSI = (wynikSI->s != nullptr) ? TRAFIONY : PUDLO;
        komputer.pobierzPlanszeStrzalow().ustawPole(celSI.x, celSI.y, wynikKratkaSI);

        if (wynikSI->s) cout << "Komputer trafil!" << endl;
        else cout << "Komputer spudlowal." << endl;

        delete wynikSI;
    }

    return 0;
}