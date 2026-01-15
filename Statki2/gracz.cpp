#include "gracz.h"
#include "plansza.h"
#include <cstdlib> 
#include <ctime>  

bool gracz::initRand = false;

gracz::gracz() : statkiGracza(10), strzalyGracza(10) {
    initRand = true;
}

const plansza<kratka>& gracz::pobierzPlanszeStatkow() const {
    return statkiGracza;
}

const plansza<OkretPos*>& gracz::pobierzPlanszeStrzalow() const {
    return strzalyGracza;
}

//void gracz::rozmiescStatkiLosowo() {
//	if (!initRand) {
//		srand(time(NULL));
//		initRand = true;
//	}
//
//	bool calaFlotaUstawiona = false;
//
//	while (!calaFlotaUstawiona) {
//
//		statkiGracza.wyczysc();
//		for (size_t i = 0; i < flota.size(); i++) {
//			delete flota[i]; 
//		}
//		flota.clear();
//
//		bool bladPodczasUstawiania = false;
//		int iloscStatkow = sizeof(rozmiaryStatkow) / sizeof(int);
//
//		for (int i = 0; i < iloscStatkow; i++) {
//			int rozmiar = rozmiaryStatkow[i];
//
//			vector<MozliwyRuch> kandydaci;
//
//			vector<pair<int, int> > polaPion = statkiGracza.pobierzDostepneMiejsca(rozmiar, true);
//			for (size_t k = 0; k < polaPion.size(); k++) {
//				MozliwyRuch ruch;
//				ruch.x = polaPion[k].first;
//				ruch.y = polaPion[k].second;
//				ruch.pionowo = true;
//				kandydaci.push_back(ruch);
//			}
//
//			vector<pair<int, int> > polaPoziom = statkiGracza.pobierzDostepneMiejsca(rozmiar, false);
//			for (size_t k = 0; k < polaPoziom.size(); k++) {
//				MozliwyRuch ruch;
//				ruch.x = polaPoziom[k].first;
//				ruch.y = polaPoziom[k].second;
//				ruch.pionowo = false;
//				kandydaci.push_back(ruch);
//			}
//
//			if (kandydaci.empty()) {
//				bladPodczasUstawiania = true;
//				break;
//			}
//
//			int losowyIndex = rand() % kandydaci.size();
//			MozliwyRuch wybrany = kandydaci[losowyIndex];
//
//			wstawStatekNaPlansze(wybrany.x, wybrany.y, rozmiar, wybrany.pionowo);
//		}
//
//		if (!bladPodczasUstawiania) {
//			calaFlotaUstawiona = true;
//		}
//	}
//}
//
//void gracz::rozmiescStatkiRecznie() {
//	statkiGracza.wyczysc();
//	for (size_t i = 0; i < flota.size(); i++) {
//		delete flota[i];
//	}
//	flota.clear();
//
//	int iloscStatkow = sizeof(rozmiaryStatkow) / sizeof(int);
//
//	for (int i = 0; i < iloscStatkow; i++) {
//		int rozmiar = rozmiaryStatkow[i];
//		bool ustawiony = false;
//
//		cout << "\nAKTUALNA PLANSZA:\n";
//		cout << statkiGracza;
//
//		while (!ustawiony) {
//			cout << "Ustaw statek o dlugosci " << rozmiar << ".\n";
//			cout << "Podaj wspolrzedne (np. A 1) i orientacje (0-poziom, 1-pion): ";
//
//			char kolumna;
//			int wiersz;
//			int orientacja;
//
//			if (!(cin >> kolumna >> wiersz >> orientacja)) {
//				cout << ">>> Bledne dane! Sprobuj ponownie.\n";
//				cin.clear();
//				cin.ignore(1000, '\n');
//				continue;
//			}
//
//			int x = -1;
//			if (kolumna >= 'a' && kolumna <= 'z') x = kolumna - 'a';
//			else if (kolumna >= 'A' && kolumna <= 'Z') x = kolumna - 'A';
//
//			int y = wiersz - 1;
//			bool pionowo = (orientacja == 1);
//
//			if (x < 0 || x > 9 || y < 0 || y > 9 || (orientacja != 0 && orientacja != 1)) {
//				cout << ">>> Bledne dane! (Zly zakres lub orientacja)\n";
//				continue;
//			}
//
//			if (statkiGracza.czyMoznaPostawic(x, y, rozmiar, pionowo)) {
//				wstawStatekNaPlansze(x, y, rozmiar, pionowo);
//				ustawiony = true;
//				cout << ">>> Statek ustawiony!\n";
//			}
//			else {
//				cout << ">>> Nie mozna tu postawic statku (kolizja lub brak miejsca)!\n";
//			}
//		}
//	}
//	cout << "\nWSZYSTKIE STATKI USTAWIONE!\n";
//	cout << statkiGracza;
//}
//
//void gracz::wstawStatekNaPlansze(int x, int y, int rozmiar, bool pionowo) {
//    statek* nowyStatek = new statek(rozmiar);
//    vector<Pola> polaStatku;
//
//    for (int i = 0; i < rozmiar; i++) {
//        int obecnyX = pionowo ? x : x + i;
//        int obecnyY = pionowo ? y + i : y;
//
//        statkiGracza.ustawPole(obecnyX, obecnyY, ZAJETY);
//
//        polaStatku.push_back({ obecnyX, obecnyY });
//    }
//
//    nowyStatek->ustawStatek(polaStatku);
//    flota.push_back(nowyStatek);
//}

