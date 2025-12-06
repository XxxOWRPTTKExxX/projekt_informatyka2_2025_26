#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <vector>
#include <cmath>
#include "ship.h"
#include "pilka.h"
#include "meteoryt.h"
#include "game.h"

Game::Game()
    :g_window(sf::VideoMode({800u, 600u}), "Gra demo na projekt (SFML 3)"),
    textpunktyzycia(font),
    punktytekst(font),
    ship(520,500,60, 60, 200, 200, 3),
    pilka(200,200,100,100,40)
{
    g_window.setFramerateLimit(60);
    backgroundTexture.loadFromFile("assets/tlo.jpg");
    backgroundRect.setSize(sf::Vector2f(windowWidth, windowHeight));
    backgroundRect.setTexture(&backgroundTexture);
    font.openFromFile("arial.ttf");
    textpunktyzycia.setFont(font);
    textpunktyzycia.setCharacterSize(24);
    textpunktyzycia.setFillColor(sf::Color::White);
    punktytekst.setFont(font);
    punktytekst.setCharacterSize(24);
    punktytekst.setFillColor(sf::Color::Magenta);
    punktytekst.setPosition(sf::Vector2f(1, 30));
    clock.restart();
    spawnclock.restart();
    healcoldown.restart();
    clocksurvival.restart();
}

void Game::run() {
    while (g_window.isOpen()) {
        processEvents();
        if (!gameOver) {
            float dt = clock.restart().asSeconds();
            update(dt);
        }
        render();
    }
}
void Game::processEvents() {
    while (const std::optional event = g_window.pollEvent()) {
        if (event->is<sf::Event::Closed>())
            g_window.close();
    }
}
void Game::update(float dt) {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left)) {
        ship.moveleft(dt);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)) {
        ship.moveright(dt);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up)) {
        ship.moveup(dt);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down)) {
        ship.movedown(dt);
    }
    if (clocksurvival.getElapsedTime().asSeconds() >= 1.0f) {
        punkty+=10;
        clocksurvival.restart();
    }
    if (spawnclock.getElapsedTime().asSeconds() > czasrespawnu) {
        float x = rand() % (int)(windowWidth - 40);
        meteoryty.emplace_back(x, -50, 15.0f, 200.0f);
        spawnclock.restart();
    }
    pilka.move(dt);
    for (int i = 0; i < meteoryty.size(); i++) {
        meteoryty[i].update(dt);
        if (checkCollision(meteoryty[i], ship)) {
            ship.odejmijZycie(1);  // odejmij życie
            meteoryty.erase(meteoryty.begin() + i);
            i--;
            continue;
        }
        if (meteoryty[i].shape.getPosition().y > windowHeight + 50) {
            meteoryty.erase(meteoryty.begin() + i);
            i--;
            continue;
        }
    }

    if (punkty >= 100) {
        czasrespawnu = 0.1f;
        for (auto& m : meteoryty) m.setSpeed(300.0f);
    }

    if (punkty >= 220) {
        czasrespawnu = 0.07f;
        for (auto& m : meteoryty) m.setSpeed(350.0f);
    }

    if (punkty >= 400) {
        czasrespawnu = 0.05f;
        for (auto& m : meteoryty) m.setSpeed(400.0f);
    }

    if (ship.getZycie() < 3) {
        if (healcoldown.getElapsedTime().asSeconds() >= 10.0f) {
            ship.dodajZycie(1);
            healcoldown.restart();
        }
    } else {
        healcoldown.restart();
    }
    pilka.collideWalls(windowWidth, windowHeight);
    pilka.collideShip(ship);

    ship.clambToBounds(windowWidth, windowHeight);

    textpunktyzycia.setString("Zycia: " + std::to_string(ship.getZycie()));
    punktytekst.setString("Punkty: " + std::to_string(punkty));
    if (ship.getZycie() <= 0) {
        gameOver = true;
    }

}

bool Game::checkCollision(const Meteoryt& ball, const Ship& ship) {
    return ball.shape.getGlobalBounds().findIntersection(ship.shape.getGlobalBounds()).has_value();
}

void Game::render() {
    g_window.clear();
    g_window.draw(backgroundRect);
    ship.draw(g_window);
    for (auto& s : meteoryty) {
        g_window.draw(s.shape);
    }
    g_window.draw(pilka.shape);
    g_window.draw(textpunktyzycia);
    g_window.draw(punktytekst);
    g_window.display();
}
