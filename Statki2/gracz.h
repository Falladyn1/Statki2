#pragma once
#include "plansza.h"
#include "OkretPos.h"
#include "statek.h"
#include <vector>

class gracz {
private:
    int rozmiaryStatkow[10] = { 4, 3, 3, 2, 2, 2, 1, 1, 1, 1 };


    plansza<kratka> statkiGracza;
    plansza<OkretPos*> strzalyGracza;

    void wstawStatekNaPlansze(int x, int y, int rozmiar, bool pionowo);

public:
    static bool initRand;
    gracz();

    void rozmiescStatkiLosowo();
    void rozmiescStatkiRecznie();

    const plansza<kratka>& pobierzPlanszeStatkow() const;
    const plansza<OkretPos*>& pobierzPlanszeStrzalow() const;

    /*virtual void WykonajRuch() = 0;*/

    int pobierzRozmiarPlanszy();
};