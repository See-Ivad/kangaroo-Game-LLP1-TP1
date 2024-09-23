#ifndef OPOSSUM_HPP_
#define OPOSSUM_HPP_

#include <iostream>
#include <chrono>
#include <Vector>
#include <random>

#include "movable.hpp"
#include "platforms.hpp"
using namespace std;

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
using namespace sf;

class Enemy : public Movable{
public:
	float spawn_rate = 0.1; //normal de 1 segundo
	int difficulty;

	Enemy(Vector2f position, Vector2f velocity, Vector2f bodySize, int difficulty)
	: Movable(position, velocity, bodySize), difficulty(difficulty){
		loadEnemyTexture();
		sprite.setTexture(texture);
		body.setFillColor(sf::Color::Transparent);
	}

	void loadEnemyTexture(){
		texture.loadFromFile("spritesheets/kangaroo.png"); //teste
		body.setTexture(&texture);
	}

	void rng_test(int level){
		static std::random_device random;
		std::mt19937 rng(random());
		std::uniform_int_distribution<int> dist(0, 6);
		int test = dist(rng);

		difficulty = (level / 3) + (level % 3);

		if (animation_clock.getElapsedTime().asSeconds() > spawn_rate){
			if(difficulty - test >= 0){
				cout << "opossum generated! " << test << endl;
				cout << "difficulty: " << difficulty << "\n" << endl;
			}
//			else if(difficulty - test < 0){
//				cout << test << endl;
//				cout << "difficulty: " << difficulty << "\n" << endl;
//			}
			animation_clock.restart();
		}
	}

	void draw(RenderWindow *window){
		sprite.setScale(2.0f, 2.0f);
		if (facing_left == true) {
			sprite.setScale(-2.0f, 2.0f);
			sprite.setPosition(sprite.getPosition().x + (sprite.getGlobalBounds().width * 0.5), sprite.getPosition().y);
		}
		window->draw(sprite);
	}

	void update(RenderWindow *rWindow, vector<Platform> platforms){
		float deltaTime = deltaTimeGetter();
		sf::Vector2f movement(velocity.x * deltaTime, velocity.y * deltaTime);
		body.move(movement);
	}
};

#endif /* OPOSSUM_HPP_ */
