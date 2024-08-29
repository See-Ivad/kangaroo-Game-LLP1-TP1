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
	bool facing_left;
	bool is_crouching;

	Player(Vector2f position, Vector2f velocity, Vector2f bodySize)
	: Movable(position, velocity, bodySize), facing_left(false), is_crouching(false){
		loadTexture();
		sprite.setTexture(texture);
		body.setFillColor(sf::Color::Transparent);
	}

	void loadTexture(){
		if(has_gloves){
			texture.loadFromFile("spritesheets/kangaroo.png");
		}
		else{
			texture.loadFromFile("spritesheets/no_gloves.png");
		}
		body.setTexture(&texture);
	}

	bool controls(RenderWindow *rWindow){
		move(rWindow);

		if((sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
				&& velocity.y == 0)
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



	void draw(RenderWindow *window){
		sprite.setScale(2.0f, 2.0f);
		if(facing_left == true){
			sprite.setScale(-2.0f, 2.0f);
			sprite.setPosition(sprite.getPosition().x + (sprite.getGlobalBounds().width * 0.5), sprite.getPosition().y);
		}
		window->draw(sprite);
	}

	void update(RenderWindow *rWindow, vector<Platform> platforms){
		controls(rWindow);
		float deltaTime = deltaTimeGetter();
		sf::Vector2f movement(velocity.x * deltaTime, velocity.y * deltaTime);
		body.move(movement);

		// Checar colisões com plataformas
		for (int i = 0; i < platforms.size(); i++) {
			if (body.getGlobalBounds().intersects(platforms[i].getBounds())) {
				// Resolvendo a colisão vertical
				if (velocity.y > 0) { // O player está caindo
					body.setPosition(body.getPosition().x, platforms[i].getBounds().width);
					movement.x = 0;
					movement.y *= -1;
					body.move(movement);
					velocity.y = 0;
				}
			}
		}

		// Checar colisões com as bordas da janela
//		if (body.getPosition().x < 0) {
//			body.setPosition(0, body.getPosition().y);
//			velocity.x = 0;
//		}
//		if (body.getPosition().x + body.getSize().x > rWindow -> getSize().x) {
//			body.setPosition(rWindow -> getSize().x - body.getSize().x, body.getPosition().y);
//			velocity.x = 0;
//		}
//		if (body.getPosition().y < 0) {
//			body.setPosition(body.getPosition().x, 0);
//			velocity.y = 0;
//		}
//		if (body.getPosition().y + body.getSize().y > rWindow -> getSize().y) {
//			body.setPosition(body.getPosition().x, rWindow -> getSize().y - body.getSize().y);
//			velocity.y = 0;
//		}




		changeSprites();
		draw(rWindow);
	}
};

#endif /* PLAYER_HPP_ */

