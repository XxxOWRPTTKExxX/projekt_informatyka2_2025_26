#pragma once
#include <vector>
#include <SFML/System/Clock.hpp>
#include "meteoryt.h"
#include "ship.h"

class MeteorytSystem {
public:
    MeteorytSystem(float windowWidth, float windowHeight);

    void update(std::vector<Meteoryt>& meteoryty, Ship& ship, float dt, float czasrespawnu);

private:
    void spawn(std::vector<Meteoryt>& meteoryty, float czasrespawnu);
    bool checkCollision(const Meteoryt& ball, const Ship& ship);
    sf::Clock spawnClock;
    float windowWidth;
    float windowHeight;
};