#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <vector>
#include <cmath>
#include "ship.h"
#include "pilka.h"
#include "meteoryt.h"
using namespace std;
using namespace sf;
#define MAX_LICZBA_POZIOMOW 3
std::vector<Meteoryt> meteoryty;
bool checkCollision(const Meteoryt& ball, const Ship& ship) {
    return ball.shape.getGlobalBounds().findIntersection(ship.shape.getGlobalBounds()).has_value();
}
sf::Clock spawnClock;

int main() {
    const float windowWidth = 800;
    const float windowHeight = 600;
    float czasrespawnu = 0.2f;
    sf::Clock clock;
    Ship ship(520,500,60, 60, 200, 200, 3);
    Pilka pilka(200, 200,100,100,40 );
    sf::RenderWindow window(
        sf::VideoMode(sf::Vector2u((unsigned)windowWidth, (unsigned)windowHeight)),"Arkanoid Demo (SFML 3.3)");
    window.setFramerateLimit(60);
    sf::Texture backgroundTexture;
    backgroundTexture.loadFromFile("../assets/tlo.jpg");
    sf::Sprite background(backgroundTexture);
    sf::Font font;
    font.openFromFile("arial.ttf");
    sf::Text text(font);
    text.setCharacterSize(24);
    text.setFillColor(sf::Color::White);
    sf::Clock survivalClock;
    sf::Text punktytekst(font);
    punktytekst.setCharacterSize(24);
    punktytekst.setFillColor(sf::Color::Magenta);
    punktytekst.setPosition(sf::Vector2f(1, 30));
    sf::Clock healthcoldown;

    bool gameOver = false;
    int punkty=0;
    while (window.isOpen()) {
        float dt = clock.restart().asSeconds();
        while (const std::optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>())
                window.close();
        }
        if (!gameOver) {
            if (sf::Keyboard::isKeyPressed(Keyboard::Key::A) || sf::Keyboard::isKeyPressed(Keyboard::Key::Left)) {
                ship.moveleft(dt);
            }
            if (sf::Keyboard::isKeyPressed(Keyboard::Key::D) || sf::Keyboard::isKeyPressed(Keyboard::Key::Right)) {
                ship.moveright(dt);
            }
            if (sf::Keyboard::isKeyPressed(Keyboard::Key::W) || sf::Keyboard::isKeyPressed(Keyboard::Key::Up)) {
                ship.moveup(dt);
            }
            if (sf::Keyboard::isKeyPressed(Keyboard::Key::S) || sf::Keyboard::isKeyPressed(Keyboard::Key::Down)) {
                ship.movedown(dt);
            }
            if (survivalClock.getElapsedTime().asSeconds()>= 1.0f) {
                punkty+=10;
                survivalClock.restart();
            }
            if (spawnClock.getElapsedTime().asSeconds() > czasrespawnu) {
                float x = rand() % (int)(windowWidth - 40);
                meteoryty.emplace_back(x, -50, 15.0f, 200.0f);  // x, y, radius, speed
                spawnClock.restart();
            }
            pilka.move(dt);
            for (int i = 0; i < meteoryty.size(); i++) {
                meteoryty[i].update(dt);

                // Kolizja z graczem
                if (checkCollision(meteoryty[i], ship)) {
                    ship.odejmijZycie(1);  // odejmij życie
                    meteoryty.erase(meteoryty.begin() + i);      // usuń kulkę
                    i--;
                    continue;
                }

                // Jeśli wypadnie poza ekran - usuń
                if (meteoryty[i].shape.getPosition().y > windowHeight + 50) {
                    meteoryty.erase(meteoryty.begin() + i);
                    i--;
                }
            }
            if (punkty>=100) {
                czasrespawnu=0.1f;
                for (auto& m : meteoryty) {
                    m.setSpeed(300.0f);
                }
            }
            if (punkty>=300) {
                czasrespawnu=0.05f;
                for (auto& m : meteoryty) {
                    m.setSpeed(400.0f);
                }
            }
            if (ship.getZycie() < 3) {
                if (healthcoldown.getElapsedTime().asSeconds() >= 10.0f) {
                    ship.dodajZycie(1);
                    healthcoldown.restart();
                }
            }
            else {
                healthcoldown.restart();
            }
            pilka.collideWalls(windowWidth, windowHeight );
            pilka.collideShip(ship);
            ship.clambToBounds(windowWidth, windowHeight);
            text.setString("Zycia: " + std::to_string(ship.getZycie()));
            punktytekst.setString("Punkty: " + std::to_string(punkty));
            if (ship.getZycie()==0) {
                gameOver=true;
                window.close();
            }
        }
    window.clear();
    window.draw(background);
    ship.draw(window);
        for (auto& s : meteoryty) {
            window.draw(s.shape);
        }
    window.draw(pilka.shape);
    window.draw(text);
        window.draw(punktytekst);
    window.display();
}



    return 0;
}