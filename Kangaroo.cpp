#include "Movable.hpp"
#include "Obstacle.hpp"

#include <iostream>
using namespace std;

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

int main(){
    Vector2f windowSize(480, 528);

    sf::RenderWindow window(sf::VideoMode(windowSize.x, windowSize.y), "Kangaroo");

    Vector2f position(windowSize.x * 3 / 20, windowSize.y * 17 / 22);
    Vector2f velocity(0.0f, 0.0f);
    Vector2f size(48, 48);
    Player player(position, velocity, size);

    while (window.isOpen()){
        sf::Event event;
        while(window.pollEvent(event)){
            if(event.type == sf::Event::Closed)
                window.close();
        }

        player.controls(&window);
        player.changeSprites();

        window.clear();
        player.draw(window);
        window.display();
    }

    return 0;
}

