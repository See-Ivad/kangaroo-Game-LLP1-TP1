#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include "player.hpp"
#include "opossum.hpp"
#include "platforms.hpp"
#include "ladder.hpp"
#include <vector>

using namespace sf;

class Game{
private:
	Vector2f windowSize;
	sf::RenderWindow window;

	Vector2f position;
	Vector2f velocity;
	Vector2f size;
	Player player;
	vector<Platform> platforms;
	vector<Ladder> ladders;
	vector<Enemy> enemies;

	sf::Texture background_texture;
	sf::Sprite background_sprite;
	int level;
	int points;

public:
	Game(std::vector<std::string> mapMatrix) :
		windowSize(480, 552),
		window(sf::VideoMode(windowSize.x, windowSize.y), "Rescue The Kangaroo!"),
		position(windowSize.x * 3 / 20, windowSize.y * 17 / 22),
		velocity(0.0f, 0.0f),
		size(48, 48),
		player(position, velocity, size),
		level(0),
		points(0)
	{
		background_texture.loadFromFile("spritesheets/background.png");
		background_sprite.setTexture(background_texture);
		background_sprite.setScale(2.0f, 2.0f);

		enemies.push_back(Enemy(sf::Vector2f(0, 0), sf::Vector2f(0.0f, 0.0f), sf::Vector2f(48, 48), level));
		loadPlatforms(mapMatrix);
	}

	void loadPlatforms(const std::vector<std::string>& mapMatrix){
		for(size_t i = 0; i < mapMatrix.size(); ++i){
			for(size_t j = 0; j < 20; ++j){
				if(mapMatrix[i][j] == 'T' || mapMatrix[i][j] == 'b' || mapMatrix[i][j] == '-'){
					Platform platform(sf::Vector2f(j * 24, i * 24), sf::Vector2f(24, 24));
					platform.assignTexture(mapMatrix[i][j]);
					platforms.push_back(platform);
					std::cout << "platform created at (" << j * 24 << ", " << i * 24 << ")" << std::endl;
				}
			}
		}
	}

	void drawPlatforms(sf::RenderWindow& window){
		for(auto& platform : platforms){
			platform.draw(&window);
		}
	}

	void render(){
		window.clear();
		window.draw(background_sprite);
		player.draw(&window);
		drawPlatforms(window);

		for(auto& enemy : enemies){
			enemy.draw(&window);
		}

		window.display();
	}

	void run(){
		while (window.isOpen()){
			sf::Event event;
			while (window.pollEvent(event)){
				if (event.type == sf::Event::Closed)
					window.close();
			}

			player.player_update(&window, platforms);
			for (auto& enemy : enemies){
				enemy.rng_test(level);
			}
			render();
		}
	}
};

#endif // GAME_H
