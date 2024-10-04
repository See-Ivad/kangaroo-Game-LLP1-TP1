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
	bool hasGloves = true;
	bool tryingCrouching;
	bool isCrouching;
	bool isPunching;
	bool tryingPunching;
	bool isClimbing;
	bool tryingClimb;
	bool isGrounded;
	bool bouncingFrame;

	SoundBuffer jump_buffer;
	Sound jump_sound;

	SoundBuffer punch_buffer;
	Sound punch_sound;

	Clock punch_clock;

	Player(Vector2f position, Vector2f velocity, Vector2f bodySize) :
		Movable(position, velocity, bodySize) {
		loadTexture("spritesheets/kangaroo.png");
		sprite.setTexture(texture);
		body.setFillColor(Color::White);
		this->bodySize = bodySize;
		tryingCrouching = false;
		isCrouching = false;
		isPunching = false;
		tryingPunching = false;
		isGrounded = false;
		isClimbing = false;
		tryingClimb = false;
		bouncingFrame = false;

		jump_buffer.loadFromFile("audio/player_jump_S3K_62.wav");
		jump_sound.setBuffer(jump_buffer);

		punch_buffer.loadFromFile("audio/player_punch_S3K_4F.wav");
		punch_sound.setBuffer(punch_buffer);
	}

	void changeSpriteTextures(){
//		sprite.setPosition(position);

		if(isClimbing){

			texture_rect.top = TILE_SIZE;

			if(updateSpritesheetPosition(TILE_SIZE * 4) && !bouncingFrame)
				bouncingFrame = true;

		}else if(!isCrouching || !isPunching){
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
			sprite.setTextureRect(texture_rect);
		}
		sprite.setScale(facing_left ? -2.0f : 2.0f, 2.0f);
	}

	void changeHitBoxSize() {
		sprite.setPosition(body.getPosition());

		if(isClimbing && !bouncingFrame){
			texture_rect.top = TILE_SIZE;
			texture_rect.left = TILE_SIZE * 4;
			bouncingFrame = true;

		} else if(!tryingCrouching && isCrouching){

			texture_rect.width = TILE_SIZE;
			texture_rect.height = TILE_SIZE;

			body.setOrigin(0,bodySize.y / 2);
			body.setSize(Vector2f(bodySize.x,bodySize.y));
			body.setOrigin(0,0);
			body.setPosition(position.x, position.y - (bodySize.y/2));

			isCrouching = false;

		} else if (tryingCrouching && !isCrouching) {

			texture_rect.top = TILE_SIZE * 1.5;
			texture_rect.left = 0;
			texture_rect.height = TILE_SIZE / 2;

			body.setOrigin(0,bodySize.y / 2);
			body.setSize(Vector2f(bodySize.x,bodySize.y/2));
			body.setOrigin(0,body.getOrigin().y-body.getSize().y);
			body.setPosition(position.x, position.y + (body.getSize().y));

			isCrouching = true;

		} else if (tryingPunching || isPunching) {
			texture_rect.top = TILE_SIZE;
			texture_rect.left = TILE_SIZE * 2;
			texture_rect.width = TILE_SIZE * 1.5;



//			isPunching = true;
//			tryingPunching = false;
//			body.setScale(facing_left ? -3.0f : 3.0f, 2.0f);
//
//			body.setPosition(facing_left ? position.x - TILE_SIZE : position.x,
//					position.y);
//			sprite.setPosition(
//					facing_left ? position.x - TILE_SIZE : position.x,
//							position.y);
		}
//		cout << "Top : " << texture_rect.top << endl;
//		cout << "left : " << texture_rect.left << endl;
//		cout << "height : " << texture_rect.height << endl;
		sprite.setTextureRect(texture_rect);
		position = body.getPosition();
	}

	void punch_timer() {
		if (isPunching) {
			velocity.x = 0;
			if (punch_clock.getElapsedTime().asSeconds()
					>= FRAME_DURATION * 2) {
				isPunching = false;
			}
		}
	}

	bool controls(RenderWindow *rWindow, float deltaTime) {
		tryingCrouching = false;

		if ((Keyboard::isKeyPressed(Keyboard::A)
				|| Keyboard::isKeyPressed(Keyboard::Left))) {
			velocity.x = TILE_SIZE * -6;
			facing_left = true;
		}

		if ((Keyboard::isKeyPressed(Keyboard::D)
				|| Keyboard::isKeyPressed(Keyboard::Right)) && !tryingCrouching) {
			velocity.x = TILE_SIZE * 6;
			facing_left = false;
		}

		//crouch
		if ((Keyboard::isKeyPressed(Keyboard::S)
				|| Keyboard::isKeyPressed(Keyboard::Down)) && isGrounded) {
			tryingCrouching = true;
			velocity.x = 0;
		}

		//punch
		if ((Keyboard::isKeyPressed(Keyboard::RShift)
				|| Keyboard::isKeyPressed(Keyboard::LShift)) && !tryingCrouching
				&& !isPunching) {
			isPunching = true;
			punch_clock.restart();
			punch_sound.play();
		}

		punch_timer();

		//jump
		if ((Keyboard::isKeyPressed(sf::Keyboard::W)
				|| Keyboard::isKeyPressed(Keyboard::Up)
				|| Keyboard::isKeyPressed(Keyboard::Space)) && velocity.y == 0
				&& !tryingCrouching && isGrounded) {
			velocity.y += TILE_SIZE * -18;
			isGrounded = false;
			jump_sound.play();
		}

		if((Keyboard::isKeyPressed(Keyboard::E) || Keyboard::isKeyPressed(Keyboard::P)) && !tryingCrouching)
			tryingClimb = true;
		else
			tryingClimb = false;

		return true;
	}


	void isFloating(vector<Platform*> platforms, vector<Ladder*> ladders){

		FloatRect testDummy = body.getGlobalBounds();
		testDummy.top += 5;
		int i = 0;
		if((testDummy.top + testDummy.height) <= 552){
			for(auto &platform : platforms)
				if(platform->getBody().getGlobalBounds().intersects(testDummy))
					i++;
			for(auto &ladder : ladders)
				if((ladder->getBody().getGlobalBounds().intersects(testDummy)) && ladder->halfSolid)
					i++;

			if(i==0)
				isGrounded = false;
		}
	}

	bool move(RenderWindow *rWindow, float deltaTime, vector<Platform*> platforms, vector<Ladder*> ladders){
		float gravity = 4.0f;

		isFloating(platforms, ladders);

		if(!isGrounded){
			velocity.y += gravity;
		}

		if(tryingClimb){
			bool collision = false;
			for(auto &Ladder : ladders){
				if(testCollision(Ladder->getBody())){
					isGrounded = false;
					isClimbing = true;
					collision = true;
				}
			}
			if(collision)
				velocity.y += -4.f;
			else
				isClimbing = false;
		}else{
			isClimbing = false;
		}

		body.move(0.f,velocity.y * deltaTime);
		for(auto &platform : platforms){
			if(testCollision(rWindow) || testCollision(platform->getBody())){
				if(testCollision(platform->getBody()))
						cout << "colisao plataforma" << endl;
				while(testCollision(rWindow) || testCollision(platform->getBody())){
					if(velocity.y >= 0.f){
						body.move(0.f,-1.f);
					}else{
						body.move(0.f,1.f);
					}
				}

				if(velocity.y >= 0.f)
					isGrounded = true;

				velocity.y = 0.f;
				position = body.getPosition();
			}
		}

		body.move(velocity.x * deltaTime,0.f);
		for(auto &platform : platforms){
			if(testCollision(rWindow) || testCollision(platform->getBody())){
				if(testCollision(platform->getBody()))
						cout << "colisao plataforma" << endl;
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
		changeSpriteTextures();
		move(rWindow, deltaTime, platforms, escada);
		changeHitBoxSize();
		draw(rWindow);
	}
};

#endif /* PLAYER_HPP_ */
