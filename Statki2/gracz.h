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
public:
    static bool initRand;
    gracz();

    const plansza<kratka>& pobierzPlanszeStatkow() const;
    const plansza<OkretPos*>& pobierzPlanszeStrzalow() const;

    void rozmiescStatkiLosowo();
    void rozmiescStatkiRecznie();

    

    virtual void wykonajRuch(gracz&) = 0;
};