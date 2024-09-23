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
	const int TILE_SIZE = 24;
	bool facing_left = false;

	Clock animation_clock;
	const float FRAME_DURATION = 0.125f;
	IntRect texture_rect = body.getTextureRect();

	Texture texture;
	Sprite sprite;
public:
	Movable();

	Movable(Vector2f position, Vector2f velocity, Vector2f bodySize){
		this->position = position;
		this->velocity = velocity;
		this->body.setPosition(this->position);
		this->body.setSize(bodySize);
	}

	bool testCollision(RenderWindow *rWindow){ //with window
		FloatRect window(body.getSize().x,body.getSize().y,rWindow->getSize().x - (body.getSize().x * 2),rWindow->getSize().y - (body.getSize().y * 2));

		if(body.getGlobalBounds().intersects(window)){
			return true;
			cout << "colisao tela" << endl;
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

	void loadTexture(string string){
		texture.loadFromFile(string);
		body.setTexture(&texture);
	}

	void changeSprites(){
		sprite.setPosition(position);

		texture_rect.width = TILE_SIZE;
		texture_rect.height = TILE_SIZE;

		if(velocity.x != 0.0f && velocity.y == 0.0f){
			texture_rect.top = 0;
			updateSpritesheetPosition(TILE_SIZE * 2);
		}
		else if(velocity.y < 0.0f){
			texture_rect.top = 0;
			texture_rect.left = TILE_SIZE * 5;
		}
		else if(velocity.y > 0.0f){
			texture_rect.top = 0;
			texture_rect.left = TILE_SIZE * 6;
		}
		else{
			texture_rect.left = 0;
			texture_rect.top = 0;
		}
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){
			texture_rect.left = 0;
			texture_rect.top = TILE_SIZE * 1.5;
			texture_rect.height = TILE_SIZE / 2;
		}

		sprite.setTextureRect(texture_rect);

		if(facing_left){
			sprite.setScale(-2.0f, 2.0f);
		}
		else{
			sprite.setScale(2.0f, 2.0f);
		}
	}

	bool isFacingLeft(){
		return facing_left;
	}

	void setFacingLeft(bool left){
		facing_left = left;
	}


	bool move(RenderWindow *rWindow){
		float delta_time = deltaTimeGetter();
		float gravity = TILE_SIZE * 128 * delta_time;

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

	void updateSpritesheetPosition(int first_frame){
		int final_frame = first_frame + TILE_SIZE;

		if(animation_clock.getElapsedTime().asSeconds() > FRAME_DURATION){
			if(texture_rect.left == first_frame){
				texture_rect.left = final_frame;
			}
			else{
				texture_rect.left = first_frame;
			}

			animation_clock.restart();
		}
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

#endif /* MOVABLE_HPP_ */
