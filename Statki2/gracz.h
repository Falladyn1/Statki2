#pragma once
#include "plansza.h"
#include "OkretPos.h"
#include "statek.h"
#include <vector>

class gracz {
protected://zmiana z private na protected zeby klasy SI i czlowiek mialy dostep do tych pol
    int rozmiaryStatkow[10] = { 4, 3, 3, 2, 2, 2, 1, 1, 1, 1 };

    vector<statek> flota;
    plansza<OkretPos*> statkiGracza;
    plansza<kratka> strzalyGracza;

public:
    static bool initRand;
    gracz();

    const plansza<OkretPos*>& pobierzPlanszeStatkow() const;
    plansza<kratka>& pobierzPlanszeStrzalow();

    void rozmiescStatkiLosowo();
    void rozmiescStatkiRecznie();

    OkretPos* sprawdzStrzalPrzeciwnika(int x, int y);

    virtual PolaS wykonajRuch() = 0;
};