/*
 * infoBar.cpp
 *
 *  Created on: 4 de out. de 2024
 *      Author: vitor
 */
#include "infoBar.hpp"

InfoBar::InfoBar(const sf::Font& font) {

    livesText.setFont(font);
    pointsText.setFont(font);
    levelText.setFont(font);

    livesText.setCharacterSize(24);
    pointsText.setCharacterSize(24);
    levelText.setCharacterSize(24);

    livesText.setFillColor(sf::Color::White);
    pointsText.setFillColor(sf::Color::White);
    levelText.setFillColor(sf::Color::White);

    livesText.setPosition(10, 10);
    pointsText.setPosition(10, 40);
    levelText.setPosition(10, 70);
}

void InfoBar::update(int lives, int points, int level) {
    livesText.setString("Lives: " + toString(lives));
    pointsText.setString("Points: " + toString(points));
    levelText.setString("Level: " + toString(level));
}

void InfoBar::draw(sf::RenderWindow& window) {
    window.draw(livesText);
    window.draw(pointsText);
    window.draw(levelText);
}

template<typename T>
std::string InfoBar::toString(const T& value) {
    std::ostringstream oss;
    oss << value;
    return oss.str();
}




