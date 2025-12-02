#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "paletka.h"
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

public:
    sf::CircleShape shape;
    Pilka(float startX, float startY, float velX, float velY, float r)
        :x(startX), y(startY), vx(velX), vy(velY), radius(r) {
        shape.setRadius(radius);
        shape.setOrigin(sf::Vector2f(radius, radius));
        shape.setPosition(sf::Vector2f(x,y));
        shape.setFillColor(sf::Color::White);
    }

    void move() {
        x+= vx;
        y+= vy;
        shape.setPosition(sf::Vector2f(x,y));
    }

    void bounceX() {
        vx=-vx;
    }
    void bounceY() {
        vy=-vy;
    }
    void setColor(const sf::Color& color) {
        shape.setFillColor(color);
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
    }
    bool collidePaddle(const Paletka& p) {
        float palX=p.getX();
        float palY=p.getY();
        float palW=p.getSzerokosc();
        float palH=p.getWysokosc();
        bool overlappedX = (x >= palX - palW / 2) && (x <= palX + palW / 2);
        bool touchedY = (y + radius >= palY - palH / 2) && (y - radius <= palY + palH / 2);

        if (overlappedX && touchedY) {
            vy = -std::abs(vy);
            y= (palY-palH/2) - radius;
            shape.setPosition(sf::Vector2f(x,y));
            return true;
        }
        return false;
    }

void draw (sf::RenderTarget& target) {
        target.draw(shape);
    }


    float getX() const {return x;}
    float getY() const {return y;}
    float getVx() const {return vx;}
    float getVy() const {return vy;}
    float getRadius() const {return radius;}
};