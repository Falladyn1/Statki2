#pragma once
#include "gracz.h"

class SI : public gracz {
public:
    SI();
    void wykonajRuch(gracz& przeciwnik);
};