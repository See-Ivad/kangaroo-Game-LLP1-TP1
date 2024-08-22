/*
 * Movable.hpp
 *
 *  Created on: 21 de ago. de 2024
 *      Author: user
 */

#ifndef MOVABLE_HPP_
#define MOVABLE_HPP_

#include <iostream>
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
	};

	bool testColide(RectangleShape object){

		if(body.getGlobalBounds().intersects(object.getGlobalBounds())){
			return true;
		}else{
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

	bool move(Vector2f vel){
		float delta_time = deltaTimeGetter();
		this->velocity = vel;
		position = position + vel * delta_time;
		body.setPosition(position);

		return true;
	};

	bool setOriginMedle(){
		Vector2f sizeBody(body.getSize());
		Vector2f medle(sizeBody.x/2,sizeBody.y/2);

		return true;
	}

	bool setTexture(Texture *texture){
		body.setTexture(texture);

		return true;
	};

	Vector2f getPosition(){
		return position;
	};

	Vector2f getVelocity(){
		return velocity;
	};

	RectangleShape getBody(){
		return body;
	};
};

class Player : public Movable {
public:
	void calculateGravity(float &jump_speed){
		float delta_time = deltaTimeGetter();
		float gravity = jump_speed * -0.5f * delta_time;
		jump_speed += gravity * delta_time;
	}

    void updatePosition() {
        if (Keyboard::isKeyPressed(Keyboard::Left)){
            move(Vector2f(-1.0f, 0.0f));
        }
    }
};


#endif /* MOVABLE_HPP_ */
