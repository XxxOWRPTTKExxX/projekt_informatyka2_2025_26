
#include <iostream>
#include "zapis.h"


void Zapis::capture(const Ship& ship, const Pilka& ball, const std::vector<Meteoryt>& met, int currentPunkty) {
    shipPosition = sf::Vector2f(ship.getX(), ship.getY());
    ballPosition = sf::Vector2f(ball.getX(), ball.getY());
    ballVelocity = sf::Vector2f(ball.getVx(), ball.getVy());
    zycie = ship.getZycie();
    punkty = currentPunkty;

    meteoryty.clear();
    for (const auto& m : met) {
        MeteorytData data;
        data.x = m.getX();
        data.y = m.getY();
        data.speed = m.getSpeed();
        meteoryty.push_back(data);
    }
}

bool Zapis::saveGame(const Ship& ship, const Pilka& pilka, const std::vector<Meteoryt>& meteoryty, int punkty, const std::string& filename)
{
    Zapis save;
    save.capture(ship, pilka, meteoryty, punkty);
    if (save.saveToFile(filename)) {
        std::cout << "Zapisano!\n";
        return true;
    }
    return false;
}

bool Zapis::loadGame(Ship& ship, Pilka& pilka, std::vector<Meteoryt>& meteoryty, int& punkty, const std::string& filename)
{
    Zapis load;
    if (!load.loadFromFile(filename)) {
        std::cerr << "Nie udaol sie wczytac zapisu!\n";
        return false;
    }

    load.apply(ship, pilka, meteoryty, punkty);
    std::cout << "Gra wczytana!\n";
    return true;
}