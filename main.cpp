#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <cmath>
#include "ship.h"
using namespace std;
using namespace sf;
#define MAX_LICZBA_POZIOMOW 3

int main() {
    const float windowWidth = 800;
    const float windowHeight = 600;
    sf::Clock clock;
    Ship ship(520,500,50, 50, 200, 200, 3);

    sf::RenderWindow window(
        sf::VideoMode(sf::Vector2u((unsigned)windowWidth, (unsigned)windowHeight)),"Arkanoid Demo (SFML 3.3)");
    window.setFramerateLimit(60);


    bool gameOver = false;

    while (window.isOpen()) {
        float dt = clock.restart().asSeconds();
        while (const std::optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>())
                window.close();
        }
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
            ship.clambToBounds(windowWidth, windowHeight);
            window.clear(sf::Color::White);
            ship.draw(window);
            window.display();

    }


    return 0;
}
