#include "manager.h"
#include <iostream>
#include <windows.h>

using namespace std;

manager::manager() {
	g1 = 0;
	g2 = 0;
	typG1 = 0;
	typG2 = 0;
}

manager::~manager() {
	delete g1;
	delete g2;
}

void manager::utworzGraczy() {
	if (g1 != NULL) delete g1;
	if (g2 != NULL) delete g2;
	g1 = 0;
	g2 = 0;

	bool G1Poprawny = false;
	bool G2Poprawny = false;

	while (!G1Poprawny) {
		cout << "Kto bedzie grac jako gracz 1? (1 - czlowiek, 2 - SI): ";
		cin.exceptions(ios::failbit | ios::badbit);
		try {
			cin >> typG1;

			if (typG1 == 1) {
				g1 = new czlowiek();
				G1Poprawny = true;
			}
			else if (typG1 == 2) {
				g1 = new SI();
				G1Poprawny = true;
			}
		}
		catch (const ios_base::failure& e) {
			cout << "Wyjatek " << e.what() << "\n";
			cin.clear();
			cin.ignore(1000, '\n');
		}
	}

	while (!G2Poprawny) {
		cout << "Kto bedzie grac jako gracz 2? (1 - czlowiek, 2 - SI): ";
		cin.exceptions(ios::failbit | ios::badbit);
		try {
			cin >> typG2;

			if (typG2 == 1) {
				g2 = new czlowiek();
				G2Poprawny = true;
			}
			else if (typG2 == 2) {
				g2 = new SI();
				G2Poprawny = true;
			}
		}
		catch (const ios_base::failure& e) {
			cout << "Wyjatek " << e.what() << "\n";
			cin.clear();
			cin.ignore(1000, '\n');
		}
	}
}

void manager::Gra() {
	char ponownaGra = 't';
	try {
		do {
			utworzGraczy();
			cout << "---FAZA PRZYGOTOWAN---" << endl;

			cout << "Gracz 1 przygotowuje flote" << endl;
			if (typG1 == 1) {
				int wybor = 0;
				cin.exceptions(ios::failbit | ios::badbit);
				while (wybor != 1 && wybor != 2) {
					try {
						cout << "Jak chcesz ustawic statki (1 - losowo, 2 - recznie): ";
						cin >> wybor;
					}
					catch (const ios_base::failure& e) {
						cout << "Wyjatek " << e.what() << "\n";
						cin.clear();
						cin.ignore(1000, '\n');
					}
				}
				if (wybor == 1) g1->rozmiescStatkiLosowo();
				else g1->rozmiescStatkiRecznie();
			}
			else {
				cout << "SI rozmieszcza statki losowo..." << endl;
				g1->rozmiescStatkiLosowo();
			}
			//system("cls");

			cout << "Gracz 2 przygotowuje flote" << endl;
			if (typG2 == 1) {
				int wybor = 0;
				cin.exceptions(ios::failbit | ios::badbit);
				while (wybor != 1 && wybor != 2) {
					try {
						cout << "Jak chcesz ustawic statki (1 - losowo, 2 - recznie): ";
						cin >> wybor;
					}
					catch (const ios_base::failure& e) {
						cout << "Wyjatek " << e.what() << "\n";
						cin.clear();
						cin.ignore(1000, '\n');
					}
				}
				if (wybor == 1) g2->rozmiescStatkiLosowo();
				else g2->rozmiescStatkiRecznie();
			}
			else {
				cout << "SI rozmieszcza statki losowo..." << endl;
				g2->rozmiescStatkiLosowo();
			}
			//system("cls");

			bool graTrwa = true;
			gracz* aktualnyGracz = g1;
			gracz* przeciwnik = g2;
			int nrGracza = 1;
			int typAktualnegoGracza = typG1;

			while (graTrwa) {
				cout << "\n========================================" << endl;
				cout << " TURA GRACZA " << nrGracza << endl;
				cout << "========================================" << endl;

				if (typAktualnegoGracza == 1) {
					cout << "TWOJE STATKI:" << endl;
					cout << aktualnyGracz->pobierzPlanszeStatkow();
					cout << "TWOJE STRZALY:" << endl;
					cout << aktualnyGracz->pobierzPlanszeStrzalow();
				}

				PolaS cel = aktualnyGracz->wykonajRuch();
				OkretPos* wynikTrafienia = przeciwnik->sprawdzStrzalPrzeciwnika(cel.x, cel.y);

				kratka stanKratki = PUDLO;
				if (wynikTrafienia->s != 0) {
					if (wynikTrafienia->s->czyZatopiony()) {
						stanKratki = ZATOPIONY;

						vector <PolaS> polaStatku = wynikTrafienia->s->pobierzPolaS();

						aktualnyGracz->pobierzPlanszeStrzalow().ustawWielePol(polaStatku, ZATOPIONY);
					}
					else {
						stanKratki = TRAFIONY;
					}
				}

				aktualnyGracz->pobierzPlanszeStrzalow().ustawPole(cel.x, cel.y, stanKratki);

				//system("cls");
				cout << "Gracz " << nrGracza << " strzela w " << char('A' + cel.x) << cel.y + 1 << endl;

				if (wynikTrafienia->s != 0) {
					cout << "TRAFIONY!" << endl;
					if (wynikTrafienia->s->czyZatopiony()) cout << "I ZATOPIONY!" << endl;
				}
				else {
					cout << "Pudlo." << endl;
				}
				delete wynikTrafienia;
				//Sleep(2000);

				if (przeciwnik->czyPrzegrana()) {
					cout << "\n\nGRATULACJE! Gracz " << nrGracza << " WYGRYWA!" << endl;
					graTrwa = false;
				}
				else {
					if (typG1 == 1 && typG2 == 1) {
						cout << "Koniec tury. Przekaz sterowanie." << endl;
						system("pause");
						//system("cls");
					}

					if (aktualnyGracz == g1) {
						aktualnyGracz = g2;
						przeciwnik = g1;
						nrGracza = 2;
						typAktualnegoGracza = typG2;
					}
					else {
						aktualnyGracz = g1;
						przeciwnik = g2;
						nrGracza = 1;
						typAktualnegoGracza = typG1;
					}
				}
			}
			cin.exceptions(ios::failbit | ios::badbit);
			try {
				cout << "\nCzy chcesz zagrac ponownie? (t - tak, n - nie): ";
				cin >> ponownaGra;
			}
			catch (const ios_base::failure& e) {
				cout << "Wyjatek " << e.what() << "\n";
				cin.clear();
				cin.ignore(1000, '\n');
			}
		} while (ponownaGra == 't' || ponownaGra == 'T');
	}
	catch (RozkladOkretowError) {
		cout << "nie da sie rozmiescic tych okretow";
	}
}
