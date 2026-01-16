#pragma once
#include <vector>
using namespace std;

struct PolaS {
	int x;
	int y;
};

class statek {
private:
	int rozmiarStatku;
	vector<PolaS> polaStatku;
	vector<bool> trafienia;
public:
	statek(int);
	void ustawStatek(const vector<PolaS>&);
	void ustawTrafienie(int, int);
	bool czyTrafiony(int, int);
	bool czyZatopiony();
	int pobierzRozmiar() const;
};