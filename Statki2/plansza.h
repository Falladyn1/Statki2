#pragma once
#include <iostream>
#include <vector>
#include "statek.h"
using namespace std;

enum kratka {
	PUSTY, ZAJETY, TRAFIONY, ZATOPIONY, PUDLO
};

inline ostream& operator<<(ostream& os, const kratka& k) {
	char symbol;
	switch (k) {
	case PUSTY:     symbol = '.'; break;
	case ZAJETY:    symbol = 'O'; break;
	case TRAFIONY:  symbol = 'X'; break;
	case ZATOPIONY: symbol = '#'; break;
	case PUDLO:     symbol = '*'; break;
	default:        symbol = ' '; break;
	}
	return os << symbol;
}

template <class T>
class plansza {
	int rozmiarPola;
	T** pole;
public:
	plansza() {
		rozmiarPola = 0;
		pole = nullptr;
	}

	plansza(int);
	~plansza();
	T sprawdz(int, int) const;
	void ustawPole(int, int, T);
	void ustawWielePol(const vector<PolaS>, T);
	void wyczysc();
	int pobierzRozmiar() const;
	vector<PolaS> pobierzWolnePola();
	bool czyOtoczenieWolne(int, int) const;
};

template <class T>
plansza<T>::plansza(int r) {
	rozmiarPola = r;
	pole = new T * [rozmiarPola];
	for (int i = 0; i < rozmiarPola; i++) {
		pole[i] = new T[rozmiarPola];
		for (int j = 0; j < rozmiarPola; j++) {
			pole[i][j] = T{};
		}
	}
}

template <class T>
T plansza<T>::sprawdz(int x, int y) const {
	if (pole == nullptr) return T{};
	if (x >= 0 && x < rozmiarPola && y >= 0 && y < rozmiarPola)
		return pole[y][x];
	return T{};
}

template <class T>
void plansza<T>::ustawPole(int x, int y, T k) {
	if (x >= 0 && x < rozmiarPola && y >= 0 && y < rozmiarPola) {
		pole[y][x] = k;
	}
}
template <class T>
void plansza<T>::ustawWielePol(const vector<PolaS> pola, T wartosc) {
	for (size_t i = 0; i < pola.size(); i++) {
		int x = pola[i].x;
		int y = pola[i].y;
		ustawPole(x, y, wartosc);
	}
}

template <class T>
void plansza<T>::wyczysc() {
	for (int i = 0; i < rozmiarPola; i++) {
		for (int j = 0; j < rozmiarPola; j++) {
			pole[i][j] = T{};
		}
	}
}

template <class T>
plansza<T>::~plansza() {
	for (int i = 0; i < rozmiarPola; i++) {
		delete[] pole[i];
	}
	delete[] pole;
}

template <class T>
int plansza<T>::pobierzRozmiar() const {
	return rozmiarPola;
}

template <class T>
bool plansza<T>::czyOtoczenieWolne(int x, int y) const {
	for (int dy = -1; dy <= 1; dy++) {
		for (int dx = -1; dx <= 1; dx++) {

			int nx = x + dx;
			int ny = y + dy;

			if (nx >= 0 && nx < rozmiarPola && ny >= 0 && ny < rozmiarPola) {
				if (pole[ny][nx] != PUSTY) {
					return false;
				}
			}
		}
	}
	return true;
}

template <class T>
vector<PolaS> plansza<T>::pobierzWolnePola() {
	vector<PolaS> wynik;

	for (int y = 0; y < rozmiarPola; y++) {
		for (int x = 0; x < rozmiarPola; x++) {
			if (czyOtoczenieWolne(x, y)) {
				wynik.push_back({ x, y });
			}
		}
	}
	return wynik;
}

template <typename T>
ostream& operator<<(ostream& os, const plansza<T>& board) {
	int rozmiar = board.pobierzRozmiar();
	os << "   ";
	for (int j = 0; j < rozmiar; j++) os << char('A' + j) << " ";
	os << endl;

	for (int i = 0; i < rozmiar; i++) {
		if (i + 1 < 10) os << " " << i + 1 << " ";
		else os << i + 1 << " ";

		for (int j = 0; j < rozmiar; j++) {
			os << board.sprawdz(j, i) << " ";
		}
		os << endl;
	}
	return os;
}