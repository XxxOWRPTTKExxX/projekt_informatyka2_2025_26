#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "game.h"


Game::Game()
    :g_window(sf::VideoMode({800u, 600u}), "Gra na projekt (SFML 3)"),
    textpunktyzycia(font),
    punktytekst(font),
    wynik("Wyniki.txt:"),
    ship(520,500,60, 60, 200, 200, 8),
    pilka(200,200,400,-100,40),
    meteorytSystem(windowWidth, windowHeight),
    menu(windowWidth, windowHeight),
    score()
{
    g_window.setFramerateLimit(60);
    backgroundTexture.loadFromFile("../assets/tlo.jpg");
    backgroundRect.setSize(sf::Vector2f(windowWidth, windowHeight));
    backgroundRect.setTexture(&backgroundTexture);
    font.openFromFile("arial.ttf");
    textpunktyzycia.setFont(font);
    textpunktyzycia.setCharacterSize(24);
    punktytekst.setFont(font);
    punktytekst.setCharacterSize(24);
    punktytekst.setFillColor(sf::Color::Magenta);
    punktytekst.setPosition(sf::Vector2f(1, 30));
    clock.restart();
    spawnclock.restart();
    healcoldown.restart();
    clocksurvival.restart();
}

void Game::gameLoop(Score& score)
{
    backgroundMusic.setVolume(100);
    while (g_window.isOpen()) {


       if ( handleEvents()) {
           return;
       }


        if (gameOver) {
            score.addScore(punkty);
            return;
        }


        float dt = clock.restart().asSeconds();
        update(dt);
        render();

    }
}

void Game::run() {

        while (g_window.isOpen()) {
            //osobny plik game_menager.cpp do menegmentu menu
            handleMenu(menu, score);
        }

}
void Game::update(float dt) {

                        // dodane
    ship.moveInput(dt);
                        // dodane

                    // dodane
    updatepunkty();
                    // dodane

            // dodane, rysowanie i sprawdzanie kolizji meteorytu ma swoją klase              Zrobione //meteoryty osobna klasa
    meteorytSystem.update(meteoryty, ship, dt, czasrespawnu);
            // dodane


    pilka.move(dt);


                            //DODANE
    updateDifficulty();
                            //DODANE

                        //DODANE                                                       Zrobione // dodawanie zyc daj w osobnym plik
   ship.updateHeal();
                        //DODANE

    pilka.collideWalls(windowWidth, windowHeight);
    pilka.collideShip(ship);
    ship.clambToBounds(windowWidth, windowHeight);
    textpunktyzycia.setString("Zycia: " + std::to_string(ship.getZycie()));
    punktytekst.setString("Punkty: " + std::to_string(punkty));


        // co zrobic gdy przegramy
    checkGameOver();

                                                         //DODANe
    textpunktyzycia.setFillColor(ship.getColorByHealth());
                                                          //DODANe
}

//kolizje w meteoryt system                 Zrobione

//usuniecie void render, przeniesione do gamerender.cpp             Zrobione