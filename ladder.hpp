#ifndef LADDER_HPP_
#define LADDER_HPP_

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
using namespace sf;

class Ladder{
protected:
	Vector2f position;
	RectangleShape body;
	int BLOCK_SIZE = 12; //numero aleatorio
public:
	Ladder();

	Ladder(Vector2f position, Vector2f bodySize){
		this->position = position;
		this->body.setPosition(this->position);
		this->body.setSize(bodySize);
	}

	void assignTexture(char type){
			IntRect texture_rect;
			texture_rect.width = BLOCK_SIZE;
			texture_rect.height = BLOCK_SIZE;

			switch (type) {
			//tree trunks
			case 'T':
				texture_rect.top = BLOCK_SIZE * 3;
				texture_rect.left = 0;
				break;
			case 't':
				texture_rect.top = BLOCK_SIZE * 3;
				texture_rect.left = BLOCK_SIZE;
				break;

			case 'C':
				texture_rect.top = BLOCK_SIZE * 4;
				texture_rect.left = 0;
				break;
			case 'c':
				texture_rect.top = BLOCK_SIZE * 4;
				texture_rect.left = BLOCK_SIZE;
				break;

			case 'D':
				texture_rect.top = BLOCK_SIZE * 3;
				texture_rect.left = BLOCK_SIZE * 3;
				break;
			case 'd':
				texture_rect.top = BLOCK_SIZE * 3;
				texture_rect.left = BLOCK_SIZE * 4;
				break;

				//main leaf texture
			case 'L':
				texture_rect.top = BLOCK_SIZE * 2;
				texture_rect.left = BLOCK_SIZE * 16;
				break;

				//no background leaves
			case '1':
				texture_rect.top = BLOCK_SIZE * 4;
				texture_rect.left = BLOCK_SIZE * 14;
				break;
			case '2':
				texture_rect.top = BLOCK_SIZE * 4;
				texture_rect.left = BLOCK_SIZE * 16;
				break;
			case '3':
				texture_rect.top = BLOCK_SIZE * 4;
				texture_rect.left = BLOCK_SIZE * 18;
				break;
			case '4':
				texture_rect.top = BLOCK_SIZE * 2;
				texture_rect.left = BLOCK_SIZE * 14;
				break;

				//leaves + trees
			case '@': //2
				texture_rect.top = BLOCK_SIZE * 4;
				texture_rect.left = BLOCK_SIZE * 28;
				break;
			case '&': //7
				texture_rect.top = 0;
				texture_rect.left = BLOCK_SIZE * 26;
				break;
			case '*': //8
				texture_rect.top = 0;
				texture_rect.left = BLOCK_SIZE * 28;
				break;
			case '(': //9
				texture_rect.top = 0;
				texture_rect.left = BLOCK_SIZE * 30;
				break;


			case 'b':
				texture_rect.top = 0;
				texture_rect.left = BLOCK_SIZE;
				break;
			case '-':
				break;
			}

			body.setTextureRect(texture_rect);
		}

	void draw(RenderWindow* window){
			body.setScale(2.0f, 2.0f);
			window->draw(body);
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
