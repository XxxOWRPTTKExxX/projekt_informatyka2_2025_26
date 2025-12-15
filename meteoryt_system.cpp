#include "meteoryt_system.h"
#include <cstdlib>

MeteorytSystem::MeteorytSystem(float w, float h)
    : windowWidth(w), windowHeight(h) {}

void MeteorytSystem::spawn(std::vector<Meteoryt>& meteoryty, float czasrespawnu) {
    if (spawnClock.getElapsedTime().asSeconds() > czasrespawnu) {
        float x = rand() % static_cast<int>(windowWidth - 40);
        meteoryty.emplace_back(x, -50, 15.0f, 50.0f);
        spawnClock.restart();
    }
}
bool MeteorytSystem::checkCollision(const Meteoryt& ball, const Ship& ship) {
    return ball.shape.getGlobalBounds().findIntersection(ship.shape.getGlobalBounds()).has_value();
}

void MeteorytSystem::update(std::vector<Meteoryt>& meteoryty, Ship& ship, float dt, float czasrespawnu) {

        spawn(meteoryty, czasrespawnu);

    for (size_t i = 0; i < meteoryty.size(); ++i) {
        meteoryty[i].update(dt);

        if (checkCollision(meteoryty[i], ship)) {
            ship.odejmijZycie(1);
            meteoryty.erase(meteoryty.begin() + i);
            --i;
            continue;
        }

        if (meteoryty[i].shape.getPosition().y > windowHeight + 50) {
            meteoryty.erase(meteoryty.begin() + i);
            --i;
        }
    }
}