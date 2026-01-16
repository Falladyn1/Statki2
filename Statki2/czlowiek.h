#pragma once
#include <iostream>
#include "gracz.h"

class czlowiek :
    public gracz
{
public:
    czlowiek();
    void wykonajRuch(gracz& przeciwnik);
};

