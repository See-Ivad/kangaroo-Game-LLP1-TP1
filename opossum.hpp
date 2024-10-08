#ifndef OPOSSUM_HPP_
#define OPOSSUM_HPP_

#include <iostream>
#include <chrono>
#include <Vector>
#include <random>

#include "movable.hpp"
#include "platforms.hpp"

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

using namespace std;
using namespace sf;

class Enemy : public Movable{
protected:
//	float spawn_rate = 2.0; //normal de 2s
//	int difficulty;

	Vector2f shootDirection;
	bool isDead;

public:

	Enemy(Vector2f position, Vector2f velocity, Vector2f bodySize, Vector2f shootDirection)
	: Movable(position, velocity, bodySize, 1){

		this->shootDirection = shootDirection;
		this->isDead = false;
		loadTexture("spritesheets/enemy.png");
		sprite.setTexture(texture);
		body.setTexture(&texture,true);
		body.setFillColor(Color::White);

		if(this->shootDirection.x == -1 || velocity.x < 0)
			facing_left = true;
		texture_rect.top = 0;
		texture_rect.left = 0;
		texture_rect.height = 24;
		texture_rect.width = 24;

		body.setTextureRect(texture_rect);
	}

	void changeSpriteTextures(){
		sprite.setPosition(position);

		texture_rect.width = TILE_SIZE;
		texture_rect.height = TILE_SIZE;

		if(velocity.x != 0.0f && velocity.y == 0.0f){
			texture_rect.top = 0;
			updateSpritesheetPosition(TILE_SIZE * 2);
		}
		else if(velocity.y < 0.0f){
			texture_rect.top = 0;
			texture_rect.left = TILE_SIZE * 5;
		}
		else if(velocity.y > 0.0f){
			texture_rect.top = 0;
			texture_rect.left = TILE_SIZE * 6;
		}
		else{
			texture_rect.left = 0;
			texture_rect.top = 0;
		}
		sprite.setTextureRect(texture_rect);
		sprite.setScale(facing_left ? -1.5f : 1.5f, 1.5f);
	}

	bool move(RenderWindow *rWindow, float deltaTime, vector<Platform*> platforms, vector<Ladder*> ladders){

		isFloating(platforms, ladders);

		body.move(velocity.x * deltaTime,0.f);
		for(auto &platform : platforms){
			bool collision = false;
			if(testCollision(rWindow) || testCollision(platform->getBody())){
				if(testCollision(platform->getBody()))
				while(testCollision(rWindow) || testCollision(platform->getBody())){
					if(velocity.x >= 0.f){
						body.move(-1.f,0.f);
					}else{
						body.move(1.f,0.f);
					}
				}
				position = body.getPosition();
				collision = true;
			}
			if(collision){
				velocity.x *= -1.f;
				facing_left = !facing_left;
			}
		}

		return true;
	}

	Movable* shoot(){
		Vector2f appleVelocity = (shootDirection * 40.f);
		Movable * apple = new Movable(Vector2f(position.x + 6.f, position.y + 6.f ), appleVelocity, bodySize / 2.f, 1);
		return apple;
	}

	void update(RenderWindow *rWindow, vector<Platform*> platforms, vector<Ladder*> ladders, float deltaTime){

		move(rWindow, deltaTime, platforms, ladders);
		changeSpriteTextures();
	}

	void draw(RenderWindow *window){
		if(facing_left == true){
			sprite.setPosition(sprite.getPosition().x + (sprite.getGlobalBounds().width), sprite.getPosition().y);
		}
		window->draw(sprite);
//		window->draw(body);
	}

//	Enemy(Vector2f position, Vector2f velocity, Vector2f bodySize, int difficulty)
//	: Movable(position, velocity, bodySize), difficulty(difficulty){
//		loadTexture("spritesheets/enemy.png");
//		sprite.setTexture(texture);
//		body.setFillColor(Color::Transparent);
//	}
//
//	bool rng_test(int level){
//		static random_device random;
//		mt19937 rng(random());
//		uniform_int_distribution<int> dist(0, 5);
//		int test = dist(rng);
//
//		difficulty = (level / 3) + (level % 3);
//
//		if (animation_clock.getElapsedTime().asSeconds() > spawn_rate){
//			if(difficulty - test >= 0){
//				cout << "opossum generated! " << test << endl;
//				cout << "difficulty: " << difficulty << "\n" << endl;
//				animation_clock.restart();
//				return true;
//			}
//			else if(difficulty - test < 0){
//				cout << test << endl;
//				cout << "d.: " << difficulty << "\n" << endl;
//				animation_clock.restart();
//				return false;
//			}
//		}
//		return false;
//	}
};

#endif /* OPOSSUM_HPP_ */
