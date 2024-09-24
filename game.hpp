#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include "player.hpp"
#include "opossum.hpp"
#include "platforms.hpp"
#include "ladder.hpp"
#include <vector>

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
	Game(vector<string> mapMatrix) :
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

		enemies.push_back(Enemy(Vector2f(100, 100), Vector2f(0.0f, 0.0f), Vector2f(48, 48), level));

		for (int i = 0; i < mapMatrix.size(); i++){
			for(int j = 0; j < 20 ; j++){
				if(mapMatrix[i][j] == '#'){
					platforms.push_back(Platform(Vector2f (j*24, i*24),Vector2f (24, 24)));

					cout << "create platform" << endl;
				}
			}
		}

		for (int i = 0; i < mapMatrix.size(); i++){
			for(int j = 0; j < 20 ; j++){
				if(mapMatrix[i][j] == '@'){
					ladders.push_back(Ladder(Vector2f (j*24, i*24),Vector2f (24, 24)));

					cout << "create ladder" << endl;
				}
			}
		}

		//	        // Constructor body (if needed)
		//		        platforms.push_back(
		//						Platform(Vector2f(0, 21 * 24), Vector2f(20 * 24, 24)));//PLAT-0
		//
		//				platforms.push_back(
		//						Platform(Vector2f(0, 16 * 24), Vector2f(530, 24)));//PLAT1
		//
		//				platforms.push_back(
		//						Platform(Vector2f(615, 576), Vector2f(150, 24)));//PLAT1
		//
		//
		//				platforms.push_back(
		//						Platform(Vector2f(183, 396), Vector2f(600, 24)));//PLAT2
		//				platforms.push_back(
		//						Platform(Vector2f(0, 396), Vector2f(100, 24)));//PLAT2
		//
		//
		//				platforms.push_back(
		//						Platform(Vector2f(0, 216), Vector2f(530, 24)));//PLAT3
		//
		//				platforms.push_back(
		//						Platform(Vector2f(615, 216), Vector2f(150, 24)));//PLAT3
		//
		//
		//
		//
		//
		//				ladders.push_back(
		//						Ladder(Vector2f(540, 576), Vector2f(72, 180)));//ESCADA1
		//
		//				ladders.push_back(
		//						Ladder(Vector2f(108, 396), Vector2f(72, 180)));//ESCADA2
		//
		//				ladders.push_back(
		//						Ladder(Vector2f(540, 216), Vector2f(72, 180)));//ESCADA3
	}



	void render() {
		window.clear();
		window.draw(background_sprite);
		player.draw(&window);

		for(int i = 0; i < platforms.size(); i++){
			window.draw(platforms[i].getBody());
		}
		for(int i = 0; i < ladders.size(); i++){
			window.draw(ladders[i].getBody());
		}
		for (size_t i = 0; i < enemies.size(); i++){
			enemies[i].draw(&window);
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
