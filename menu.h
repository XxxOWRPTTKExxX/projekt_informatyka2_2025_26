#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include <cmath>

class Menu {
public:
    Menu(float width, float height);
    int run(sf::RenderWindow& window);
private:
    int selected;
    sf::Font font;
    sf::Text textmenu;
    std::vector<sf::Text> options;
    sf::Texture backgroundmenu;
    sf::RectangleShape backgroundRectmenu;
};