#pragma once
#include <SFML/System/Vector2.hpp>
#include "meteoryt.h"
#include "ship.h"
#include "pilka.h"
#include <vector>
#include <fstream>
#include <iostream>

struct MeteorytData {
    float x, y;
    float speed;
};

class Zapis {
private:
    int zycie;
    sf::Vector2f shipPosition;
    sf::Vector2f ballPosition;
    sf::Vector2f ballVelocity;
    std::vector<MeteorytData> meteoryty;
    int punkty;

public:
    Zapis()=default;
    void capture(const Ship& ship, const Pilka& ball, const std::vector<Meteoryt>& met, int currentPunkty);
    int getZyciez() const {return zycie;}
    const sf::Vector2f& getShipposition() const {return shipPosition;}
    const sf::Vector2f& getBallPosition() const {return ballPosition;}
    const sf::Vector2f& getBallVelocity() const {return ballVelocity;}
    const std::vector<MeteorytData>& getMeteoryty() const {return meteoryty;}
    int getPunkty() const { return punkty; }

bool saveToFile(const std::string& zapisplik) const {
    std::ofstream file(zapisplik);
    if (!file.is_open()) {
        std::cerr << "Nie mozna otworzyc pliku do zapisu: " << zapisplik << "\n";
        return false;
    }

                                    // statek

    file << "SHIP " << shipPosition.x << " " << shipPosition.y << " " << zycie << "\n";

                                    //pilka
    file << "BALL " << ballPosition.x << " " << ballPosition.y << " "
         << ballVelocity.x << " " << ballVelocity.y << "\n";
            //punkty
        file << "POINTS " << punkty << "\n";
                                // meteoryty
    file << "METEORYTS_COUNT " << meteoryty.size() << "\n";

    for (const auto& m : meteoryty) {
        file << m.x << " " << m.y << " " << m.speed << "\n";
    }

    file.close();
    return true;
}
    bool loadFromFile(const std::string& zapisplik) {
        std::ifstream file(zapisplik);
        if (!file.is_open()) return false;

        std::string label;
        int meteCount;

        if (file >> label >> shipPosition.x >> shipPosition.y >> zycie) {} // SHIP
        if (file >> label >> ballPosition.x >> ballPosition.y >> ballVelocity.x >> ballVelocity.y) {} // BALL
        if (file >> label >> punkty) {} //Punkty
        if (file >> label >> meteCount) { // ilosc mete
            meteoryty.clear();
            for (int i = 0; i < meteCount; ++i) {
                MeteorytData m;
                file >> m.x >> m.y >> m.speed;
                meteoryty.push_back(m);
            }
        }

        file.close();
        return true;
    }

    void apply(Ship& s, Pilka& b, std::vector<Meteoryt>& met, int& gamePunkty) {
        s.resetfromfile(shipPosition, zycie);                       // reset statku
        b.resetfromfile(ballPosition, ballVelocity);
        s.setZycie(getZyciez());

        met.clear();
        for (const auto& m : meteoryty) {
            met.emplace_back(m.x, m.y, 15.0f, m.speed); // promień 15 przykładowo
        }
        gamePunkty = punkty;
    }
    //DODANE
    static bool saveGame(const Ship& ship, const Pilka& pilka, const std::vector<Meteoryt>& meteoryty, int punkty, const std::string& filename = "zapis.txt");
    static bool loadGame(Ship& ship, Pilka& pilka, std::vector<Meteoryt>& meteoryty, int& punkty, const std::string& filename = "zapis.txt");
    //DODANE
};


