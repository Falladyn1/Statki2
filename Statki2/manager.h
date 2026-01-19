#pragma once
#include "gracz.h"
#include "SI.h"
#include "czlowiek.h"

class manager
{
	gracz* g1, * g2;
	~manager();
	manager();
	void utworzGraczy();
	void Start();
};

