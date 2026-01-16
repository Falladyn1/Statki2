#include "czlowiek.h"

using namespace std;

czlowiek::czlowiek() : gracz() {

}

void czlowiek::wykonajRuch(gracz& przeciwnik){
	char wierszZnak;
	int kolumnaLiczba;
	int wiersz, kolumna;

	while (true) {
		cout << "Podaj wspolrzedne strzalu (np. A2):";
		cin >> wierszZnak >> kolumnaLiczba;

		wierszZnak = toupper(wierszZnak);
		wiersz = wierszZnak - 'A';

		kolumna = kolumnaLiczba - 1;

		if (wiersz >= 0 && wiersz < 10 && kolumna >= 0 && kolumna < 10)
			break;
		else
			printf("Nieprawidlowe dane! Uzyj liter A-J i liczb 1-10.\n");
	}
	cout << "Strzelasz w: " << wierszZnak << kolumnaLiczba;
}
