#include "game.h"

bool Game::handleEvents() {
    while (auto event = g_window.pollEvent()) {

        if (event->is<sf::Event::Closed>()) {
            g_window.close();
            return true;
        }

        if (auto* key = event->getIf<sf::Event::KeyPressed>()) {

            if (key->code == sf::Keyboard::Key::Escape) {
                return true;
            }

            // Zapis gry
            if (key->code == sf::Keyboard::Key::Z) {
                Zapis::saveGame(ship, pilka, meteoryty, punkty);
            }
        }
    }
    return false;
}