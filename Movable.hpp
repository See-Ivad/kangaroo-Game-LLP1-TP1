#ifndef MOVABLE_HPP_
#define MOVABLE_HPP_

#include <iostream>
#include <cmath>
#include <chrono>
using namespace std;

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
using namespace sf;

class Movable{
protected:
	Vector2f position;
	Vector2f velocity;
	RectangleShape body;
	const int tile_size = 24;
public:
	Movable();

	Movable(Vector2f position, Vector2f velocity, Vector2f bodySize){
		this->position = position;
		this->velocity = velocity;
		this->body.setPosition(this->position);
		this->body.setSize(bodySize);
	}

	bool testCollision(RenderWindow *rWindow){
		FloatRect window(body.getSize().x,body.getSize().y,rWindow->getSize().x - (body.getSize().x * 2),rWindow->getSize().y - (body.getSize().y * 2));

		if(body.getGlobalBounds().intersects(window)){
			return true;
		}
		else{
			return false;
		}
	}

	bool testCollision(RectangleShape object){
		if(body.getGlobalBounds().intersects(object.getGlobalBounds())){
			return true;
		}
		else{
			return false;
		}
	}

	float deltaTimeGetter(){
		static auto last_frame_time = std::chrono::steady_clock::now();
		auto current_frame_time = std::chrono::steady_clock::now();

		std::chrono::duration<float> delta = current_frame_time - last_frame_time;
		last_frame_time = current_frame_time;

		return delta.count();
	}

	bool move(RenderWindow *rWindow){
		float delta_time = deltaTimeGetter();
		float gravity = tile_size * 128 * delta_time;

		if(testCollision(rWindow)){
			velocity.y += gravity;
		}
		position += velocity * delta_time;
		body.setPosition(position);

		velocity.x = 0;

		if(!testCollision(rWindow)){
			velocity.y = 0;
			velocity.x = 0;
		}

		return true;
	}

	void setOriginMiddle() {
		Vector2f sizeBody = body.getSize();
		body.setOrigin(sizeBody.x / 2, sizeBody.y / 2);
	}

	bool setVelocityY(int y){
		this->velocity.y = y;
		return true;
	}

	bool setVelocityX(int x){
		this->velocity.x = x;
		return true;
	}

	bool setVelocity(Vector2f velocity){
		this->velocity = velocity;
		return true;
	}

	bool setTexture(Texture *texture){
		body.setTexture(texture);

		return true;
	}

	Vector2f getPosition(){
		return position;
	}

	Vector2f getVelocity(){
		return velocity;
	}

	RectangleShape getBody(){
		return body;
	}
};

class Player: public Movable{
public:
	Texture kangaroo_texture;
	Sprite kangaroo_sprite;
	bool has_gloves = true;
	IntRect kangaroo_rectangle;
	Clock animation_clock;
	float frame_duration = 0.25f;

	Player(Vector2f position, Vector2f velocity, Vector2f bodySize)
	: Movable(position, velocity, bodySize){
		loadTexture();
		kangaroo_sprite.setTexture(kangaroo_texture);
		kangaroo_sprite.setScale(2, 2);
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


	void updateSpritesheetPosition(int first_frame){
	    int final_frame = first_frame + tile_size;

	    if(animation_clock.getElapsedTime().asSeconds() > frame_duration){
	        if(kangaroo_rectangle.left == first_frame){
	            kangaroo_rectangle.left = final_frame;
	        }
	        else{
	            kangaroo_rectangle.left = first_frame;
	        }

	        animation_clock.restart();
	    }
	}

	void changeSprites(){
		kangaroo_sprite.setPosition(position);

		kangaroo_rectangle.width = 24;
		kangaroo_rectangle.height = 24;

		if(velocity.x != 0.0f && velocity.y == 0.0f){
			updateSpritesheetPosition(48);
		}

		else{
			kangaroo_rectangle.left = 0;
			kangaroo_rectangle.top = 0;
		}

		kangaroo_sprite.setTextureRect(kangaroo_rectangle);
	}


	void draw(RenderWindow &window) {
		window.draw(kangaroo_sprite);
	}

	bool controls(RenderWindow *rWindow){
		move(rWindow);

		if((sf::Keyboard::isKeyPressed(sf::Keyboard::W)
				|| sf::Keyboard::isKeyPressed(sf::Keyboard::Up)
				|| sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) && !testCollision(rWindow))
			velocity.y += tile_size * -24;
		if((sf::Keyboard::isKeyPressed(sf::Keyboard::S)
				|| sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) && testCollision(rWindow))
			velocity.y = tile_size * 24;
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
			velocity.x = tile_size * -6;
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
			velocity.x = tile_size * 6;

		return true;
	}
};

#endif /* MOVABLE_HPP_ */
