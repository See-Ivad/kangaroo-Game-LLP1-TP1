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
	float spawn_rate = 2; //normal de 2s
	int difficulty;

	Enemy(Vector2f position, Vector2f velocity, Vector2f bodySize, int difficulty)
	: Movable(position, velocity, bodySize), difficulty(difficulty){
		loadTexture("spritesheets/enemy.png");
		sprite.setTexture(texture);
		body.setFillColor(sf::Color::Blue);
	}

	void rng_test(int level){
		static std::random_device random;
		std::mt19937 rng(random());
		std::uniform_int_distribution<int> dist(0, 5);
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
};

#endif /* OPOSSUM_HPP_ */
