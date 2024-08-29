#ifndef PLATFORM_H
#define PLATFORM_H


#include <SFML/Graphics.hpp>
class Platform{
public:
	Vector2f position;
	RectangleShape block;
	const int block_size = 12;

	IntRect textureRect = block.getTextureRect();

	Texture texture;
	Sprite sprite;

	Platform(Vector2f position, Vector2f blockSize){
		this->position = position;
		this->block.setPosition(this->position);
		this->block.setSize(blockSize);
		block.setFillColor(sf::Color::Green);
	}

	void draw(RenderWindow *window){
		sprite.setScale(2.0f, 2.0f);
		window->draw(sprite);
	}

	RectangleShape getBody(){
		return block;
	}

	sf::FloatRect getBounds() const{
		return block.getGlobalBounds();
	}
};

#endif // PLATFORM_H
