#ifndef PLATFORM_H
#define PLATFORM_H

#include <SFML/Graphics.hpp>

class Platform{
public:
	sf::Vector2f position;
	sf::RectangleShape block;
	const int BLOCK_SIZE = 12;

	sf::Texture texture;
	sf::Sprite sprite;

	Platform(sf::Vector2f position, sf::Vector2f blockSize){
		loadTexture("spritesheets/tileset.png");
		this->position = position;
		this->block.setPosition(this->position);
		this->block.setSize(blockSize);
		block.setFillColor(sf::Color::Transparent);
		block.setTexture(&texture);
		sprite.setTexture(texture);
		sprite.setPosition(position);
	}

	void setTexture(const sf::Texture& texture){
		block.setTexture(&texture);
	}

	void loadTexture(std::string filename){
		if (!texture.loadFromFile(filename)){
			std::cerr << "Failed to load texture from " << filename << std::endl;
		}
		block.setTexture(&texture);
	}

	void assignTexture(char type){
		sf::IntRect texture_rect;
		texture_rect.width = BLOCK_SIZE;
		texture_rect.height = BLOCK_SIZE;

		switch (type) {
		case 'T':
			texture_rect.top = BLOCK_SIZE * 3;
			texture_rect.left = 0;
			break;
		case 'b':
			texture_rect.top = 0;
			texture_rect.left = BLOCK_SIZE;
			break;
		case '-':
			break;
		}
		block.setTextureRect(texture_rect);
		sprite.setTextureRect(texture_rect);
	}

	void draw(sf::RenderWindow* window){
		sprite.setScale(2.0f, 2.0f);
		window->draw(sprite);
	}

	sf::RectangleShape getBody(){
		return block;
	}

	sf::FloatRect getBounds() const{
		return block.getGlobalBounds();
	}
};

#endif // PLATFORM_H
