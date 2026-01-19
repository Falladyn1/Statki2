#pragma once
#include "gracz.h"
#include "SI.h"
#include "czlowiek.h"

class manager
{
private:
	gracz *g1, *g2;
	int typG1;//1 - czlowiek, 2 - SI
	int typG2;
public:
	~manager();
	manager();
	void utworzGraczy();
	void Gra();
};

