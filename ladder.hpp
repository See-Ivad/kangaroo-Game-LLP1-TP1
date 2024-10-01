#ifndef LADDER_HPP_
#define LADDER_HPP_

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
using namespace sf;

class Ladder : public Platform{
public:
	Ladder();

	Ladder(Vector2f position, Vector2f blockSize)
		: Platform(position, blockSize)
	{
		loadTexture("spritesheets/tileset.png");
		block.setFillColor(Color::Transparent);
		block.setTexture(&texture);
		sprite.setTexture(texture);
		sprite.setPosition(position);
	}
};

#endif /* LADDER_HPP_ */
