#pragma once
#include <vector>
#include <string>
#include <SFML/Graphics.hpp>

class Score {
public:
    Score(const std::string& filename = "Wyniki.txt");

    void addScore(int score);
    std::vector<int> getScores();  // zwraca posortowane malejąco
    void showScores(sf::RenderWindow& window, const sf::Font& font);

private:
    std::string filename;
};