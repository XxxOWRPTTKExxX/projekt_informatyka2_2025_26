#include "game.h"

    // Renderowanie gry, obrazy i obiekty
void Game::render() {
    g_window.clear();
    g_window.draw(backgroundRect);
    ship.draw(g_window);
    for (auto& m : meteoryty) {
        g_window.draw(m.shape);
    }
    g_window.draw(pilka.shape);
    g_window.draw(textpunktyzycia);
    g_window.draw(punktytekst);
    g_window.display();
}

