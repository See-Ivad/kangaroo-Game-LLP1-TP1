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

		const float targetFrameTime = 1.0f / 60.0f;
		return delta.count() / targetFrameTime;
	}

	bool move(RenderWindow *rWindow){
		float delta_time = deltaTimeGetter();
		float gravity = 3;

		if(testCollision(rWindow)){
			if(velocity.x < 0 && velocity.y > 0){
				velocity.x = ((sqrt((velocity.x * -1.0) + velocity.y) * -1.0) / 2);
				velocity.y = (sqrt((velocity.x * -1.0) + velocity.y) / 2);

				cout << "x = " << velocity.x << endl;
				cout << "y = " << velocity.y << endl;
			}
			if(velocity.x < 0 && velocity.y < 0){
				velocity.x = ((sqrt((velocity.x * -1.0) + (velocity.y * -1)) * -1.0) / 2);
				velocity.y = ((sqrt((velocity.x * -1.0) + (velocity.y * -1)) * -1.0) / 2);

				cout << "x = " << velocity.x << endl;
				cout << "y = " << velocity.y << endl;
			}
			if(velocity.x > 0 && velocity.y > 0){
				velocity.y = ((sqrt((velocity.y * 1.0) + velocity.x)) / 2);
				velocity.x = (sqrt((velocity.y * 1.0) + velocity.y) / 2);

				cout << "x = " << velocity.x << endl;
				cout << "y = " << velocity.y << endl;
			}
			if(velocity.x > 0 && velocity.y < 0){
				velocity.y = ((sqrt((velocity.y * -1.0) + velocity.x) * -1.0) / 2);
				velocity.x = (sqrt((velocity.y * -1.0) + velocity.x) / 2);

				cout << "x = " << velocity.x << endl;
				cout << "y = " << velocity.y << endl;
			}
			velocity.y += gravity;
			position = position + velocity * delta_time;
			body.setPosition(position);

			if(!testCollision(rWindow)){
				velocity.x *= -1;
				velocity.y *= -1;
				position += velocity;
				body.setPosition(position);
			}
			velocity.x = 0;
			velocity.y = 0;
		}
		return true;
	}

	bool setOriginMiddle(){
		Vector2f sizeBody(body.getSize());
		Vector2f medle(sizeBody.x/2,sizeBody.y/2);

		return true;
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

class Player : public Movable{
public:
	Player(Vector2f position, Vector2f velocity, Vector2f bodySize)
	: Movable(position, velocity, bodySize){
	}

	bool controls(RenderWindow *rWindow){
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
			velocity.y = -6;
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
			velocity.y = 1.5;
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
			velocity.x = -1.5;
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
			velocity.x = 1.5;

		move(rWindow);
		return true;
	}
};

#endif /* MOVABLE_HPP_ */
