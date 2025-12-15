#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <vector>
#include <cmath>
#include <fstream>
#include "ship.h"
#include "pilka.h"
#include "meteoryt.h"
#include "Score.h"
#include "menu.h"
#include "meteoryt_system.h"
#include "zapis.h"


class Game {
public:
    Game();
    void run();

private:
    void update(float dt);
    void render();
    void handleMenu(Menu& menu, Score& score);
    void updateDifficulty();
    void updatepunkty();
    void przegrana();
    bool handleEvents();
    void resetGame();
    void checkGameOver();
    void audiogameover();
    void gameLoop(Score& score);
    bool checkCollision(const Meteoryt& ball, const Ship& ship);

    Score wynik;
    sf::Music backgroundMusic;
    sf::Music gameover;

    sf::RenderWindow g_window;
    sf::Texture backgroundTexture;
    sf::RectangleShape backgroundRect;

    sf::Font font;
    sf::Text textpunktyzycia;
    sf::Text punktytekst;

    Ship ship;
    Pilka pilka;
    std::vector<Meteoryt> meteoryty;

    sf::Clock clock;
    sf::Clock spawnclock;
    sf::Clock healcoldown; //przeniesione
    sf::Clock clocksurvival;


    float czasrespawnu= 0.5f;
    int punkty=0;
    bool gameOver= false;

    const float windowWidth = 800;
    const float windowHeight = 600;
    MeteorytSystem meteorytSystem;
    Menu menu;
    Score score;

};
