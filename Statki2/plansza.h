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
	int rozmiarPola; // rozmiar*rozmiar
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
	void ustawWielePol(const vector<Pola>, T);
	void wyczysc();
	bool czyMoznaPostawic(int x, int y, int rozmiar, int pionowo);
	vector<Pola> pobierzDostepneMiejsca();
	int pobierzRozmiar() const;

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
void plansza<T>::ustawWielePol(const vector<Pola> pola, T wartosc) {
	for (int i = 0; i < pola.size(); i++) {
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

//template <class T>
//bool plansza<T>::czyMoznaPostawic(int x, int y, int rozmiar, int pionowo) {
//	int rozmiarPlanszy = rozmiarPola;
//
//	if (pionowo) {
//		if (y + rozmiar > rozmiarPlanszy) return false;
//	}
//	else {
//		if (x + rozmiar > rozmiarPlanszy) return false;
//	}
//
//	int startX = x - 1;
//	int startY = y - 1;
//	int koniecX = pionowo ? x + 1 : x + rozmiar;
//	int koniecY = pionowo ? y + rozmiar : y + 1;
//
//	for (int i = startY; i <= koniecY; i++) {
//		for (int j = startX; j <= koniecX; j++) {
//			if (i >= 0 && i < rozmiarPlanszy && j >= 0 && j < rozmiarPlanszy) {
//				if (sprawdz(j, i) != PUSTY) {
//					return false;
//				}
//			}
//		}
//	}
//	return true;
//}

//template <class T>
// vector<pair<int,int>> plansza<T>::pobierzDostepneMiejsca(int rozmiar, bool pionowo) {
//	 vector<pair<int, int>> wolnePola;
//
//	 for (int y = 0; y < rozmiarPola; y++) {
//		 for (int x = 0; x < rozmiarPola; x++) {
//			 if (czyMoznaPostawic(x, y, rozmiar, pionowo))
//				 wolnePola.push_back({ x, y });
//		 }
//	 }
//
//	 return wolnePola;
//}

template <class T>
vector<Pola> plansza<T>::pobierzDostepneMiejsca() {
	vector<Pola> wynik;

	for (int i = 0; i < rozmiarPola; i++) {
		for (int j = 0; j < rozmiarPola; j++) {
			if (pole[i][j] != PUSTY) {
				continue;
			}

		}
	}
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