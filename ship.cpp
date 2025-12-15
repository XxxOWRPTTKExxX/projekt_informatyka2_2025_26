#include "ship.h"
#include <stdio.h>

void Ship::updateHeal() {
    if (zycie < startZycie_) {
        if (healCooldown.getElapsedTime().asSeconds() >= 10.f) {
            dodajZycie(1);
            healCooldown.restart();
        }
    } else {
        healCooldown.restart();
    }
}

sf::Color Ship::getColorByHealth() const {
    switch (zycie) {
        case 8: return sf::Color(200, 200, 200); // szary
        case 7: return sf::Color::White;
        case 6: return sf::Color::Cyan;
        case 5: return sf::Color::Yellow;
        case 4: return sf::Color::Magenta;
        case 3: return sf::Color::Blue;
        case 2: return sf::Color::Green;
        case 1: return sf::Color::Red;
        default: return sf::Color::Transparent;
    }
}