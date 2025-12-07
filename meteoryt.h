#pragma once
#include <SFML/Graphics.hpp>

class Meteoryt {
private:
   inline static sf::Texture texture;
public:
    sf::CircleShape shape;
    float speed;
    Meteoryt(float startX, float startY, float radius, float speed)
        : speed(speed)
    {
        texture.loadFromFile("../assets/meteor.png");
        shape.setRadius(radius);
        shape.setPosition(sf::Vector2f(startX, startY));
        shape.setTexture(&texture);
    }

    void update(float dt) {
        shape.move(sf::Vector2f(0, speed * dt));
    }
    void setSpeed(float newSpeed) { speed = newSpeed; }
    float getSpeed() const {return speed;}
    float getX() const {return shape.getPosition().x;}
    float getY() const {return shape.getPosition().y;}
};
