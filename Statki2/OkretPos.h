#pragma once
#include "statek.h"
#include <iostream>

using namespace std;

class OkretPos
{
public:
    statek* s;
    int x;
    int y;

    OkretPos(statek* _s, int _x, int _y) {
        s = _s;
        x = _x;
        y = _y;
    }

};

inline ostream& operator<<(ostream& os, const OkretPos* p) {
    if (p == nullptr || p->s == nullptr) {
        os << ".";
    }
    else if (p->s->czyZatopiony()) {
        os << "#";
    }
    else if (p->s->czyTrafiony(p->x, p->y)) {
        os << "X";
    }
    else {
        os << "O";
    }
    return os;
}