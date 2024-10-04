/*
 * infoBar.hpp
 *
 *  Created on: 4 de out. de 2024
 *      Author: vitor
 */

#ifndef INFOBAR_HPP
#define INFOBAR_HPP

#include <SFML/Graphics.hpp>
#include <string>
#include <sstream>
#include "game.hpp"

class InfoBar {
public:
    InfoBar(const sf::Font& font);

    void update(int lives, int points, int level);
    void draw(sf::RenderWindow& window);

private:
    sf::Text livesText;
    sf::Text pointsText;
    sf::Text levelText;

    template<typename T>
    std::string toString(const T& value);
};

#endif // INFOBAR_HPP
