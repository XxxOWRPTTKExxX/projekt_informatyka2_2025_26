// Created by oliwi on 24.11.2025.
#include <iostream>
#include "zapis.h"


void Zapis::capture(const Ship& ship, const Pilka& ball, const std::vector<Meteoryt>& met) {
    shipPosition = sf::Vector2f(ship.getX(), ship.getY());
    ballPosition = sf::Vector2f(ball.getX(), ball.getY());
    ballVelocity = sf::Vector2f(ball.getVx(), ball.getVy());
    zycie = ship.getZycie();

    meteoryty.clear();
    for (const auto& m : met) {
        MeteorytData data;
        data.x = m.getX();
        data.y = m.getY();
        data.speed = m.getSpeed();
        meteoryty.push_back(data);
    }
}
