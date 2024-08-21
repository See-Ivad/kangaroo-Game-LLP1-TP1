/*
 * Movable.hpp
 *
 *  Created on: 21 de ago. de 2024
 *      Author: user
 */

#ifndef MOVABLE_HPP_
#define MOVABLE_HPP_

#include <iostream>
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

	bool move(Vector2f vel){
		this->velocity = vel;
		position = position + vel;
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
    void updatePosition() {
        if (Keyboard::isKeyPressed(Keyboard::Left)){
            move(Vector2f(-1.0f, 0.0f));
        }
    }
};


#endif /* MOVABLE_HPP_ */
