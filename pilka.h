#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "ship.h"
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Color.hpp>

class Pilka {
private:
    float x;
    float y;
    float vx;
    float vy;
    float radius;
    float startX_;
    float startY_;
    float startvelX_;
    float startvelY_;

public:
    sf::Texture texture;
    sf::CircleShape shape;
    Pilka(float startX, float startY, float velX, float velY, float r)
        :x(startX), y(startY), vx(velX), vy(velY), radius(r), startX_(startX), startY_(startY), startvelX_(velX), startvelY_(velY) {
        if (!texture.loadFromFile("../assets/kometa.png")) {
            std::cerr << "Blad: nie mozna zaladowac komety.png\n";
        }
        shape.setRadius(radius);
        shape.setOrigin(sf::Vector2f(radius, radius));
        shape.setPosition(sf::Vector2f(x,y));
        shape.setFillColor(sf::Color::White);
        shape.setTexture(&texture);
    }

    void move(float dt) {
        x+= vx*dt;
        y+= vy*dt;
        shape.setPosition(sf::Vector2f(x,y));
    }

    void bounceX() {
        vx=-vx;
    }
    void bounceY() {
        vy=-vy;
    }
void collideWalls(float width, float height) {
        if (x-radius<= 0) {
            x= radius;
            bounceX();
        }
        else if (x+ radius >= width) {
            x= width - radius;
            bounceX();
        }

        if (y-radius <=0) {
            y=radius;
            bounceY();
        }
        else if (y+ radius >= height) {
            y= height - radius;
            bounceY();
        }
        shape.setPosition(sf::Vector2f(x,y));
    }
    bool collideShip( Ship& s) {
        float palX=s.getX();
        float palY=s.getY();
        float palW=s.getSzerokosc();
        float palH=s.getWysokosc();
        bool overlappedX = (x >= palX - palW / 2) && (x <= palX + palW / 2);
        bool touchedY = (y + radius >= palY - palH / 2) && (y - radius <= palY + palH / 2);

        if (overlappedX && touchedY) {
            s.odejmijZycie(1);
            if (vy > 0) {
                y = palY + palH / 2 + radius;
            } else {
                y = palY - palH / 2 - radius;
            }
            return true;

        }
        return false;
    }

void draw (sf::RenderTarget& target) {
        target.draw(shape);
    }

    void reset() {
        x = startX_;
        y = startY_;
        vx = startvelX_;
        vy = startvelY_;
        shape.setPosition(sf::Vector2f( x, y));
    }
    void resetfromfile(const sf::Vector2f& pos, const sf::Vector2f& vel) {
        x = pos.x;
        y = pos.y;
        vx = vel.x;
        vy = vel.y;
        shape.setPosition(sf::Vector2f(x, y));
    }

    float getX() const {return x;}
    float getY() const {return y;}
    float getVx() const {return vx;}
    float getVy() const {return vy;}
    float getRadius() const {return radius;}
};