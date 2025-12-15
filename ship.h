//
// Created by oliwi on 02.12.2025.
//
#pragma once
#include <SFML/Audio.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>


class Ship {
private:
    float x;
    float y;
    float szerokosc;
    float wysokosc;
    float vx;
    float vy;
    int zycie;
    sf::Texture texture;
    float startX_;
    float startY_;
    int startZycie_;
    sf::Music damage;
    sf::Clock healCooldown;


    public:
    sf::RectangleShape shape;
Ship(float startX, float startY, float startSzerokosc, float startWysokosc, float startVx, float startVy, float startzycie)
    :x(startX), y(startY), szerokosc(startSzerokosc), wysokosc(startWysokosc), vx(startVx), vy(startVy), zycie(startzycie), startX_(startX), startY_(startY), startZycie_(startzycie) {
    if (!damage.openFromFile("../assets/damage.ogg")) {
        std::cerr << "Blad: nie damage.wav\n";
    }
    damage.setVolume(90);
    if (!texture.loadFromFile("../assets/statek1.png")) {
        std::cerr << "Blad: nie ma statek.png\n";
    }
    shape.setSize(sf::Vector2f(szerokosc, wysokosc));
    shape.setOrigin(sf::Vector2f(szerokosc / 2, wysokosc / 2));
    shape.setPosition(sf::Vector2f(x, y));
    shape.setTexture(&texture);
}
                    //DODANE
    void updateHeal();
                    //DODANE

    sf::Color getColorByHealth() const;

    void moveleft(float dt)
    {
        x-=vx *dt;
        shape.setPosition(sf::Vector2f(x, y));
    }

    void moveright(float dt) {
    x+=vx *dt;
    shape.setPosition(sf::Vector2f(x, y));
}
    void moveup(float dt) {
    y-=vy *dt;
    shape.setPosition(sf::Vector2f(x, y));
}
    void movedown(float dt) {
    y+=vy *dt;
    shape.setPosition(sf::Vector2f(x, y));
}
                                                                 //DODANE
    inline void moveInput(float dt) {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A) ||
        sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left)) {
        moveleft(dt);
        }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D) ||
        sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)) {
        moveright(dt);
        }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W) ||
        sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up)) {
        moveup(dt);
        }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S) ||
        sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down)) {
        movedown(dt);
        }
                                                                  //DODANE
}
    void clambToBounds(float width, float height) {
    if (x < szerokosc / 2)
        x = szerokosc / 2;

    if (x > width - szerokosc / 2)
        x = width - szerokosc / 2;

    if (y < wysokosc / 2)
        y = wysokosc / 2;

    if (y > height - wysokosc / 2)
        y = height - wysokosc / 2;

    shape.setPosition(sf::Vector2f(x, y));
}
    void draw(sf::RenderTarget& target) {
    target.draw(shape);
}
    void odejmijZycie(int ile) {
    zycie -= ile;
    damage.play();
    if (zycie < 0) {
        zycie =0;
    }
}
    void dodajZycie(int ile1) {
    zycie += ile1;
    if (zycie > startZycie_) zycie=startZycie_;
}

    void reset() {
    x = startX_;
    y = startY_;
    zycie = startZycie_;
    shape.setPosition(sf::Vector2f(x, y));
}
    void resetfromfile(const sf::Vector2f& newPos, int z) {
    x = newPos.x;
    y = newPos.y;
    zycie = z;
    shape.setPosition(sf::Vector2f(x, y));
}
    void setZycie(int z) { zycie = z; }


    float getX() const{return x;}
    float getY() const{return y;}
    float getSzerokosc() const{return szerokosc;}
    float getWysokosc() const{return wysokosc;}
    int getZyciestart() const {return startZycie_;}
    int getZycie() const{return zycie;}
};