#include "score.h"
#include <fstream>
#include <algorithm>

Score::Score(const std::string& filename)
    : filename(filename) {}

void Score::addScore(int score) {
    std::ofstream file(filename, std::ios::app);
    if (file.is_open()) {
        file << score << "\n";
        file.close();
    }
}

std::vector<int> Score::getScores() {
    std::ifstream file(filename);
    std::vector<int> scores;
    int value;

    while (file >> value)
        scores.push_back(value);

    std::sort(scores.begin(), scores.end(), std::greater<int>());

    return scores;
}
void Score::showScores(sf::RenderWindow& window, const sf::Font& font) {
    sf::Text title(font, "Lista wynikow");
    title.setCharacterSize(50);
    title.setFillColor(sf::Color::Yellow);
    title.setPosition(sf::Vector2f(200, 50));
    std::vector<int> scores = getScores();
    std::vector<sf::Text> lines;

    for (int i = 0; i < scores.size(); i++) {
        sf::Text t(font);
        t.setCharacterSize(36);
        t.setFillColor(sf::Color::White);
        t.setString(std::to_string(i+1) + ". " + std::to_string(scores[i]));
        t.setPosition(sf::Vector2f(250, 150 + i * 50));
        lines.push_back(t);
    }
    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) window.close();

            if (const auto* key = event->getIf<sf::Event::KeyPressed>()) {
                if (key->code == sf::Keyboard::Key::Escape) {
                    return;
                }
            }
        }

        window.clear();
        window.draw(title);
        for (auto& t : lines) window.draw(t);
        window.display();
    }

}
