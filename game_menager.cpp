#include "game.h"
#include "zapis.h"

// Obsługa menu głównego
void Game::handleMenu(Menu& menu, Score& score) {
    int menuResult = menu.run(g_window);

    switch (menuResult) {
        case 0: // Nowa gra
            resetGame();
            gameLoop(score);
            break;

        case 1: // Wczytaj
            if (Zapis::loadGame(ship, pilka, meteoryty, punkty)) {
                gameLoop(score);
            }
            break;

        case 2: // Wyniki
            score.showScores(g_window, font);
            break;

        case 3: // Escape
            g_window.close();
            break;
    }
}
        //Obsluga trudnosci gry
void Game::updateDifficulty() {
    if (punkty >= 1000) {
        czasrespawnu = 0.05f;
        for (auto& m : meteoryty) m.setSpeed(400.0f);
    } else if (punkty >= 600) {
        czasrespawnu = 0.15f;
        for (auto& m : meteoryty) m.setSpeed(250.0f);
    } else if (punkty >= 300) {
        czasrespawnu = 0.25f;
        for (auto& m : meteoryty) m.setSpeed(150.0f);
    } else {
        czasrespawnu = 0.5f;
        for (auto& m : meteoryty) m.setSpeed(100.0f);
    }
}
        // Aktualizacja punktow
void Game::updatepunkty() {
    if (clocksurvival.getElapsedTime().asSeconds() >= 1.0f) {
        punkty+=10;
        clocksurvival.restart();
    }
}
        // Obsluga przegranej
void Game::przegrana() {
    gameOver = true;
    wynik.addScore(punkty);
}
        // Reset gry do stanu poczatkowego
void Game::resetGame() {
    gameOver = false;
    punkty = 0;
    meteoryty.clear();
    ship.reset();
    pilka.reset();
    czasrespawnu = 0.5f;

    if (!backgroundMusic.openFromFile("../assets/background.ogg")) {
        std::cerr << "Nie ma muzyki!" << std::endl;
    } else {
        backgroundMusic.setLooping(true);
        backgroundMusic.play();
    }
}
        // Odtwarzanie muzyki po przegranej
    void Game::audiogameover() {
        if (!gameover.openFromFile("../assets/gameover.ogg")) {
            std::cerr << "Nie ma muzyki!" << std::endl;
        }
        backgroundMusic.setVolume(10);
        gameover.play();
        gameover.setVolume(200);
    }

void Game::checkGameOver() {
    if (ship.getZycie() <= 0) {
        if (!gameover.openFromFile("../assets/gameover.ogg")) {
            std::cerr << "Nie ma muzyki!" << std::endl;
        }
        backgroundMusic.setVolume(10);
        gameover.play();
        gameover.setVolume(200);

        gameOver = true;
        wynik.addScore(punkty);

        przegrana();
    }
}

