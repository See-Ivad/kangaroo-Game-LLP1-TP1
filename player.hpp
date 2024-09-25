#ifndef PLAYER_HPP_
#define PLAYER_HPP_

#include <iostream>
#include <chrono>
#include <Vector>

#include "movable.hpp"
#include "platforms.hpp"
using namespace std;

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
using namespace sf;

class Player: public Movable{
public:
	bool has_gloves = true;
	bool is_crouching;
	bool is_punching;

	Player(Vector2f position, Vector2f velocity, Vector2f bodySize)
	: Movable(position, velocity, bodySize){
		loadTexture("spritesheets/kangaroo.png");
		sprite.setTexture(texture);
		body.setFillColor(sf::Color::Transparent);
		is_crouching = false;
		is_punching = false;
	}

	void changeHitBoxSize(){
		sprite.setPosition(position);

		texture_rect.width = TILE_SIZE;
		texture_rect.height = TILE_SIZE;

		if(is_crouching){
			texture_rect.top = TILE_SIZE * 1.5;
			texture_rect.left = 0;
		}
		else if(is_punching){
			texture_rect.top = TILE_SIZE;
			texture_rect.left = TILE_SIZE * 2;
		}

		sprite.setTextureRect(texture_rect);
	}

	bool controls(RenderWindow *rWindow){
		move(rWindow);
		is_crouching = false;
		is_punching = false;

		if((Keyboard::isKeyPressed(sf::Keyboard::W) || Keyboard::isKeyPressed(Keyboard::Up) || Keyboard::isKeyPressed(Keyboard::Space))
				&& velocity.y == 0)
			velocity.y += TILE_SIZE * -24;



		if((Keyboard::isKeyPressed(Keyboard::A) || Keyboard::isKeyPressed(Keyboard::Left))){
			velocity.x = TILE_SIZE * -6;
			facing_left = true;
		}

		if((Keyboard::isKeyPressed(Keyboard::D) || Keyboard::isKeyPressed(Keyboard::Right))
				&& !is_crouching){
			velocity.x = TILE_SIZE * 6;
			facing_left = false;
		}

		//actions
		if((Keyboard::isKeyPressed(Keyboard::S) || Keyboard::isKeyPressed(Keyboard::Down))){
			is_crouching = true;
			velocity.x = 0;
			if(testCollision(rWindow))
				velocity.y = TILE_SIZE * 24;
		}

		if((Keyboard::isKeyPressed(Keyboard::RShift) || Keyboard::isKeyPressed(Keyboard::LShift))){
			is_punching = true;
			velocity.x = 0;
		}

		return true;
	}

	//	void draw(RenderWindow *window){
	//		if(facing_left == true){
	//
	//			sprite.setPosition(sprite.getPosition().x + (sprite.getGlobalBounds().width * 0.5), sprite.getPosition().y);
	//		}
	//		window->draw(sprite);
	//	}

	void player_update(RenderWindow *rWindow, vector<Platform> platforms){
		controls(rWindow);
		float deltaTime = deltaTimeGetter();
		sf::Vector2f movement(velocity.x * deltaTime, velocity.y * deltaTime);
		body.move(movement);
		changeSpriteTextures();
		changeHitBoxSize();
		draw(rWindow);
	}
};

#endif /* PLAYER_HPP_ */

