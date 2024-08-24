#include "Movable.hpp"
#include "Obstacle.hpp"

#include <iostream>
using namespace std;

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

int main(){
	Vector2f windowSize(240,264);

	sf::RenderWindow window(sf::VideoMode(windowSize.y,windowSize.x), "Kangaroo");

	Vector2f position(windowSize.x/2, windowSize.y/2);
	Vector2f velocity(0.0,0.0);
	Vector2f size(24,24);
	Player player(position, velocity, size);

	while (window.isOpen()){
		sf::Event event;
		while (window.pollEvent(event)){//Iniciio do "Loop de eventos"
			if (event.type == sf::Event::Closed)
				window.close();
		}//Final do "loop de Eventos"

		player.controls(&window);

		window.clear();
		window.draw(player.getBody());
		window.display();
	}

	return 0;
}
