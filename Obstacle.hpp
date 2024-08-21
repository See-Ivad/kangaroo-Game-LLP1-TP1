/*
 * Obstacle.hpp
 *
 *  Created on: 21 de ago. de 2024
 *      Author: user
 */

#ifndef OBSTACLE_HPP_
#define OBSTACLE_HPP_

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
using namespace sf;

class Obstacle{
protected:

	Vector2f position;
	RectangleShape body;

	public:

	Obstacle();

	Obstacle(Vector2f position, Vector2f bodySize){

		this->position = position;
		this->body.setPosition(this->position);
		this->body.setSize(bodySize);
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

	RectangleShape getBody(){
		return body;
	};

};



#endif /* OBSTACLE_HPP_ */
