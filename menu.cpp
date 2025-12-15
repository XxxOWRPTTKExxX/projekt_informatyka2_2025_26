#include "menu.h"
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <vector>
#include <cmath>

Menu::Menu(float width, float height)
    :textmenu(font)
{
    font.openFromFile("arial.ttf");


    selected=0;

    textmenu.setFont(font);
    textmenu.setString(" ------------- Menu Glowne -------------- ");
    textmenu.setCharacterSize(50);
    textmenu.setFillColor(sf::Color::Yellow);
    textmenu.setPosition(sf::Vector2f(width / 2 - 410, 30));

    std::string names[3]={
        "Nowa gra",
        "Wczytaj gre",
        "Lista wynikow"
    };
    for (int i=0; i<3; i++) {
        options.emplace_back(font);
        options[i].setString(names[i]);
        options[i].setCharacterSize(36);
        options[i].setPosition(sf::Vector2f(width / 2 - 120, 200 + i * 60));
        if (i == selected)
            options[i].setFillColor(sf::Color::Yellow);
        else
            options[i].setFillColor(sf::Color::Magenta);
    }

    if (!backgroundmenu.loadFromFile("../assets/tlo1.jpg")) {
        std::cerr << "Blad: nie mozna zaladowac tlo_menu.jpg\n";
    }
    backgroundRectmenu.setSize(sf::Vector2f(width, height));
    backgroundRectmenu.setTexture(&backgroundmenu);
}
int Menu::run(sf::RenderWindow& window) {

    while (window.isOpen()) {

        while (const std::optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>())
                window.close();

            if (const auto* key = event->getIf<sf::Event::KeyPressed>()) {
                options[selected].setFillColor(sf::Color::Magenta);
                if (key->code == sf::Keyboard::Key::Up || key->code == sf::Keyboard::Key::W) {
                    selected = (selected + 2) % 3;
                } else if (key->code == sf::Keyboard::Key::Down || key->code == sf::Keyboard::Key::S) {
                    selected = (selected + 1) % 3;
                } else if (key->code == sf::Keyboard::Key::Enter) {
                    return selected; // zwraca 0,1,2
                } else if (key->code == sf::Keyboard::Key::Escape) {
                    return 3; // specjalny kod dla wyjscia z gry
                }

                // Zaznacz nową opcję
                options[selected].setFillColor(sf::Color::Yellow);
            }
        }

        window.clear();
        window.draw(backgroundRectmenu);
        window.draw(textmenu);
        for (auto& t : options) window.draw(t);
        window.display();
    }

    return 0;
}