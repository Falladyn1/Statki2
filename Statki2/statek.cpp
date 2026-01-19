#include "statek.h"

statek::statek(int r) {
	rozmiarStatku = r;
	trafienia = vector<bool>(r, false);
}

void statek::ustawStatek(const vector<PolaS>& nowePola) {
	if (nowePola.size() == rozmiarStatku) {
		polaStatku = nowePola;
	}
}

void statek::ustawTrafienie(int x, int y) {
	if (polaStatku.empty()) return;

	for (int i = 0; i < rozmiarStatku; i++) {
		if (polaStatku[i].x == x && polaStatku[i].y == y) {
			trafienia[i] = true;
			return;
		}
	}
}

bool statek::czyTrafiony(int x, int y) const{
	if (polaStatku.empty()) return false;

	for (int i = 0; i < rozmiarStatku; i++) {
		if (polaStatku[i].x == x && polaStatku[i].y == y) {
			return trafienia[i];
		}
	}
	return false;
}

bool statek::czyZatopiony() const{
	for (bool t : trafienia) {
		if (!t) return false;
	}
	return true;
}

int statek::pobierzRozmiar() const {
	return rozmiarStatku;
}