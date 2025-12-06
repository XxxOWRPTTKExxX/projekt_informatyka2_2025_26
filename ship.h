//
// Created by oliwi on 02.12.2025.
//
#pragma once
#include <stdio.h>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Color.hpp>
using namespace std;

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
    public:
    sf::RectangleShape shape;
Ship(float startX, float startY, float startSzerokosc, float startWysokosc, float startVx, float startVy, float startzycie)
    :x(startX), y(startY), szerokosc(startSzerokosc), wysokosc(startWysokosc), vx(startVx), vy(startVy), zycie(startzycie) {
    if (!texture.loadFromFile("../assets/statek1.png")) {
        std::cerr << "Blad: nie mozna zaladowac statek.png\n";
    }
    shape.setSize(sf::Vector2f(szerokosc, wysokosc));
    shape.setOrigin(sf::Vector2f(szerokosc / 2, wysokosc / 2));
    shape.setPosition(sf::Vector2f(x, y));
    shape.setTexture(&texture);
}
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
    if (zycie < 0) zycie =0;
}
    void dodajZycie(int ile1) {
    zycie += ile1;
    if (zycie > 3) zycie=3;
}
    float getX() const{return x;}
    float getY() const{return y;}
    float getSzerokosc() const{return szerokosc;}
    float getWysokosc() const{return wysokosc;}
    int getZycie() const{return zycie;}
};