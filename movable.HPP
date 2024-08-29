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
	const int tile_size = 24;

	Clock animation_clock;
	float frame_duration = 0.125f;
	IntRect textureRect = body.getTextureRect();

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

	bool testCollision(RenderWindow *rWindow){
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

		textureRect.width = tile_size;
		textureRect.height = tile_size;

		if(velocity.x != 0.0f && velocity.y == 0.0f){
			textureRect.top = 0;
			updateSpritesheetPosition(tile_size * 2);
		}
		else if(velocity.y < 0.0f){
			textureRect.top = 0;
			textureRect.left = tile_size * 5;
		}
		else if(velocity.y > 0.0f){
			textureRect.top = 0;
			textureRect.left = tile_size * 6;
		}
		else if(sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){
			textureRect.left = 0;
			textureRect.top = tile_size;
		}
		else{
			textureRect.left = 0;
			textureRect.top = 0;
		}

		sprite.setTextureRect(textureRect);
	}

	bool move(RenderWindow *rWindow){
		float delta_time = deltaTimeGetter();
		float gravity = tile_size * 128 * delta_time;

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
		int final_frame = first_frame + tile_size;

		if(animation_clock.getElapsedTime().asSeconds() > frame_duration){
			if(textureRect.left == first_frame){
				textureRect.left = final_frame;
			}
			else{
				textureRect.left = first_frame;
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
