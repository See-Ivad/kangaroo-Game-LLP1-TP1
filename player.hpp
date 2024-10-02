#ifndef PLAYER_HPP_
#define PLAYER_HPP_

#include <iostream>
#include <chrono>
#include <Vector>

#include "movable.hpp"
#include "platforms.hpp"
#include "ladder.hpp"

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

using namespace std;
using namespace sf;

class Player: public Movable {
public:
	bool has_gloves = true;
	bool is_crouching;
	bool is_punching;
	bool grounded;

	SoundBuffer jump_buffer;
	Sound jump_sound;

	SoundBuffer punch_buffer;
	Sound punch_sound;

	Clock punch_clock;

	Player(Vector2f position, Vector2f velocity, Vector2f bodySize) :
		Movable(position, velocity, bodySize) {
		loadTexture("spritesheets/kangaroo.png");
		sprite.setTexture(texture);
		body.setFillColor(Color::Transparent);
		is_crouching = false;
		is_punching = false;
		grounded = false;

		jump_buffer.loadFromFile("audio/player_jump_S3K_62.wav");
		jump_sound.setBuffer(jump_buffer);

		punch_buffer.loadFromFile("audio/player_punch_S3K_4F.wav");
		punch_sound.setBuffer(punch_buffer);
	}

	void changeHitBoxSize() {
		sprite.setPosition(position);

		texture_rect.width = TILE_SIZE;
		texture_rect.height = TILE_SIZE;

		if (is_crouching) {
			texture_rect.top = TILE_SIZE * 1.5;
			texture_rect.left = 0;
			texture_rect.height = TILE_SIZE / 2;

			body.setScale(facing_left ? -2.0f : 2.0f, 1.0f);
			body.setPosition(position.x, position.y + (TILE_SIZE));
			sprite.setPosition(position.x, position.y + (TILE_SIZE));
		} else if (is_punching) {
			texture_rect.top = TILE_SIZE;
			texture_rect.left = TILE_SIZE * 2;
			texture_rect.width = TILE_SIZE * 1.5;

			body.setScale(facing_left ? -3.0f : 3.0f, 2.0f);

			body.setPosition(facing_left ? position.x - TILE_SIZE : position.x,
					position.y);
			sprite.setPosition(
					facing_left ? position.x - TILE_SIZE : position.x,
							position.y);
		}

		sprite.setTextureRect(texture_rect);
	}

	void punch_timer() {
		if (is_punching) {
			velocity.x = 0;
			if (punch_clock.getElapsedTime().asSeconds()
					>= FRAME_DURATION * 2) {
				is_punching = false;
			}
		}
	}

	bool controls(RenderWindow *rWindow, float deltaTime) {
		is_crouching = false;

		if ((Keyboard::isKeyPressed(Keyboard::A)
				|| Keyboard::isKeyPressed(Keyboard::Left))) {
			velocity.x = TILE_SIZE * -6;
			facing_left = true;
		}

		if ((Keyboard::isKeyPressed(Keyboard::D)
				|| Keyboard::isKeyPressed(Keyboard::Right)) && !is_crouching) {
			velocity.x = TILE_SIZE * 6;
			facing_left = false;
		}

		//crouch
		if ((Keyboard::isKeyPressed(Keyboard::S)
				|| Keyboard::isKeyPressed(Keyboard::Down)) && grounded) {
			is_crouching = true;
			velocity.x = 0;
		}

		//punch
		if ((Keyboard::isKeyPressed(Keyboard::RShift)
				|| Keyboard::isKeyPressed(Keyboard::LShift)) && !is_crouching
				&& !is_punching) {
			is_punching = true;

			punch_clock.restart();
			punch_sound.play();
		}

		punch_timer();

		//jump
		if ((Keyboard::isKeyPressed(sf::Keyboard::W)
				|| Keyboard::isKeyPressed(Keyboard::Up)
				|| Keyboard::isKeyPressed(Keyboard::Space)) && velocity.y == 0
				&& !is_crouching && grounded) {
			velocity.y += TILE_SIZE * -24;
			grounded = false;
			jump_sound.play();
		}

		return true;
	}

	bool move(RenderWindow *rWindow, float deltaTime, vector<Platform*> platforms, vector<Ladder*> escada){
		float gravity = 3.5f;

		if(!grounded){
		velocity.y += gravity;
		}

		if((Keyboard::isKeyPressed(Keyboard::E) || Keyboard::isKeyPressed(Keyboard::P)) && !is_crouching){
			bool collision = false;
			for(auto &Ladder : escada){
				if(testCollision(Ladder->getBody())){
					grounded = false;
					collision = true;
				}
			}
			if(collision)
				velocity.y += -4.f;
		}

		body.move(0.f,velocity.y * deltaTime);
		for(auto &platform : platforms){
			if(testCollision(rWindow) || testCollision(platform->getBody())){
				while(testCollision(rWindow) || testCollision(platform->getBody())){
					if(velocity.y >= 0.f){
						body.move(0.f,-1.f);
					}else{
						body.move(0.f,1.f);
					}
				}
				if(velocity.y >= 0.f)
					grounded = true;
				velocity.y = 0.f;
				position = body.getPosition();
			}
		}

		body.move(velocity.x * deltaTime,0.f);
		for(auto &platform : platforms){
			if(testCollision(rWindow) || testCollision(platform->getBody())){
				while(testCollision(rWindow) || testCollision(platform->getBody())){
					if(velocity.x >= 0.f){
						body.move(-1.f,0.f);
					}else{
						body.move(1.f,0.f);
					}
				}
				position = body.getPosition();
			}
		}

		velocity.x = 0;
		return true;
	}

	void player_update(RenderWindow *rWindow, vector<Platform*> platforms,vector<Ladder*> escada, float deltaTime){

		controls(rWindow, deltaTime);

		cout << "velocity y: " << velocity.y << endl;
		cout << "Delta time : " << deltaTime << endl;

		changeSpriteTextures();
		move(rWindow, deltaTime, platforms, escada);
		changeHitBoxSize();
		draw(rWindow);
	}
};

#endif /* PLAYER_HPP_ */
