#include "SI.h"
#include <cstdlib>
#include <vector>

using namespace std;

SI::SI() : gracz() {
}

PolaS SI::wykonajRuch() {
    int rozmiar = strzalyGracza.pobierzRozmiar();

    // Znajdowanie trafien X ktore nie sa #
    vector<PolaS> trafienia;
    for (int y = 0; y < rozmiar; y++) {
        for (int x = 0; x < rozmiar; x++) {
            if (strzalyGracza.sprawdz(x, y) == TRAFIONY) {
                trafienia.push_back({ x, y });
            }
        }
    }

    // wyznaczanie potencjalnych celi
    vector<PolaS> potencjalneCele;

    if (!trafienia.empty()) {
        bool poziom = false;
        bool pion = false;

        if (trafienia.size() > 1) {
            if (trafienia[0].x == trafienia[1].x) pion = true;
            else if (trafienia[0].y == trafienia[1].y) poziom = true;
        }

        // szukanie sasiadow
        for (const auto& t : trafienia) {
            vector<PolaS> kierunki = { {0, -1}, {0, 1}, {-1, 0}, {1, 0} };

            if (pion) {
                kierunki = { {0, -1}, {0, 1} }; // Tylko gora/dol
            }
            else if (poziom) {
                kierunki = { {-1, 0}, {1, 0} }; // Tylko lewo/prawo
            }

            for (auto k : kierunki) {
                int nx = t.x + k.x;
                int ny = t.y + k.y;

                if (nx >= 0 && nx < rozmiar && ny >= 0 && ny < rozmiar) {
                    if (strzalyGracza.sprawdz(nx, ny) == PUSTY) {
                        potencjalneCele.push_back({ nx, ny });
                    }
                }
            }
        }
    }

    // strzelanie
    if (!potencjalneCele.empty()) {
        int index = rand() % potencjalneCele.size();
        return potencjalneCele[index];
    }

    // jesli brak strzelaj losowo
    int x, y;
    do {
        x = rand() % rozmiar;
        y = rand() % rozmiar;
    } while (strzalyGracza.sprawdz(x, y) != PUSTY);

    return { x, y };
}