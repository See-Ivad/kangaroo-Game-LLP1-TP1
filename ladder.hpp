#ifndef LADDER_HPP_
#define LADDER_HPP_

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
using namespace sf;

class Ladder{
protected:
	Vector2f position;
	RectangleShape body;
public:
	Ladder();

	Ladder(Vector2f position, Vector2f bodySize){
		this->position = position;
		this->body.setPosition(this->position);
		this->body.setSize(bodySize);
	}

	bool setOriginMedle(){
		Vector2f sizeBody(body.getSize());
		Vector2f medle(sizeBody.x/2,sizeBody.y/2);

		return true;
	}

	bool setTexture(Texture *texture){
		body.setTexture(texture);

		return true;
	}
	Vector2f getPosition(){
		return position;
	}
	RectangleShape getBody(){
		return body;
	}
};

#endif /* LADDER_HPP_ */
