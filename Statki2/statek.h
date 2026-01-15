#pragma once
#include <vector>
using namespace std;

struct Pola {
	int x;
	int y;
};

class statek {
private:
	int rozmiarStatku;
	vector<Pola> polaStatku;
	vector<bool> trafienia;
public:
	statek(int);
	void ustawStatek(const vector<Pola>&);
	void ustawTrafienie(int, int);
	bool czyTrafiony(int, int);
	bool czyZatopiony();

	int pobierzRozmiar() const;


};
