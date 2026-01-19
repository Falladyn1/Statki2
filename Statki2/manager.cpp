#include "manager.h"

manager::manager() {
	g1 = 0;
	g2 = 0;
}

manager::~manager() {
	delete g1;
	delete g2;
}

void manager::utworzGraczy() {
	delete g1;
	delete g2;

	bool G1Poprawny = false;
	bool G2Poprawny = false;

	while(!G1Poprawny) {
		int wyborG1;
		cout << "Kto bedzie grac jako gracz 1? (1 - czlowiek, 2 - bot)";
		cin >> wyborG1;

		if (wyborG1 == 1) {
			g1 = new czlowiek();
			G1Poprawny = true;
		}
		else if (wyborG1 == 2) {
			g1 = new SI();
			G1Poprawny = true;
		}
		else{
			printf("Niepoprawny wybor");
		}
	}

	while (!G2Poprawny) {
		int wyborG2;
		cout << "Kto bedzie grac jako gracz 1? (1 - czlowiek, 2 - bot)";
		cin >> wyborG2;

		if (wyborG2 == 1) {
			g2 = new czlowiek();
			G2Poprawny = true;
		}
		else if (wyborG2 == 2) {
			g2 = new SI();
			G1Poprawny = true;
		}
		else {
			printf("Niepoprawny wybor");
		}
	}

}

void manager::Gra() {
	
}
	