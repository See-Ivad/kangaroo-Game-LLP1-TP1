//============================================================================
// Name        : Kangaroo.cpp
// Author      : dfg
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include "Movable.hpp"
#include "Obstacle.hpp"

#include <iostream>
using namespace std;

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

int main() {

	Vector2f windowSize(200,200);

    sf::RenderWindow window(sf::VideoMode(windowSize.y,windowSize.x), "Hello World");

    Vector2f position(windowSize.x/2, windowSize.y/2);
    Vector2f velocity(0.0,0.0);
    Vector2f size(10,10);
    Movable player(position, velocity, size);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.draw(player.getBody());
        window.display();
    }

	return 0;
}
