#ifndef PLAYER_HPP_
#define PLAYER_HPP_

#include "Movable.hpp"

#include <iostream>
#include <chrono>
using namespace std;

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
using namespace sf;

class Player: public Movable{
public:
	Texture kangaroo_texture;
	Sprite kangaroo_sprite;

	bool has_gloves = true;
	bool facing_left;
	bool is_crouching;

	Player(Vector2f position, Vector2f velocity, Vector2f bodySize)
	: Movable(position, velocity, bodySize), facing_left(false){
		loadTexture();
		kangaroo_sprite.setTexture(kangaroo_texture);
	}

	void loadTexture(){
		if(has_gloves){
			kangaroo_texture.loadFromFile("spritesheets/kangaroo.png");
		}
		else{
			kangaroo_texture.loadFromFile("spritesheets/no_gloves.png");
		}
		body.setTexture(&kangaroo_texture);
	}

	void changeSprites(){
		kangaroo_sprite.setPosition(position);

		textureRect.width = 24;
		textureRect.height = 24;

		if(velocity.x != 0.0f && velocity.y == 0.0f){
			textureRect.top = 0;
			updateSpritesheetPosition(48);
		}
		else if(velocity.y < 0.0f){
			textureRect.top = 0;
			textureRect.left = 120;
		}
		else if(velocity.y > 0.0f){
			textureRect.top = 0;
			textureRect.left = 144;
		}
		else if(sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){
			textureRect.left = 0;
			textureRect.top = 24;
		}
		else{
			textureRect.left = 0;
			textureRect.top = 0;
		}

		kangaroo_sprite.setTextureRect(textureRect);
	}

	bool controls(RenderWindow *rWindow){
		move(rWindow);
		is_crouching = false;

		if((sf::Keyboard::isKeyPressed(sf::Keyboard::W)
				|| sf::Keyboard::isKeyPressed(sf::Keyboard::Up)
				|| sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) && !testCollision(rWindow))
			velocity.y += tile_size * -24;

		if((sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
				&& !(sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down))){
			velocity.x = tile_size * -6;
			facing_left = true;
		}

		if((sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
				&& !(sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down))){
			velocity.x = tile_size * 6;
			facing_left = false;
		}

		if((sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down))){
			is_crouching = true;
			if(testCollision(rWindow))
				velocity.y = tile_size * 24;
		}

		return true;
	}

	void draw(RenderWindow &window){
		kangaroo_sprite.setScale(2.0f, 2.0f);
		if(facing_left == true){
			kangaroo_sprite.setScale(-2.0f, 2.0f);
			kangaroo_sprite.setPosition(kangaroo_sprite.getPosition().x + kangaroo_sprite.getGlobalBounds().width, kangaroo_sprite.getPosition().y);
		}
		window.draw(kangaroo_sprite);
	}
};

#endif /* PLAYER_HPP_ */

