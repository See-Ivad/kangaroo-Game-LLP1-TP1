#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include "player.hpp"
#include "opossum.hpp"
#include "platforms.hpp"
#include "ladder.hpp"
#include <vector>

using namespace std;
using namespace sf;

class Game{
private:
	Vector2f windowSize;
	RenderWindow window;

	Vector2f position;
	Vector2f velocity;
	Vector2f size;
	Player player;
	vector<Platform *> platforms;
	vector<Ladder> ladders;
	vector<Enemy *> enemies;

	Texture background_texture;
	Sprite background_sprite;
	int level;
	int points;

	Music game_theme;

public:
	Game(vector<string> mapMatrix) :
		windowSize(480, 552),
		window(VideoMode(windowSize.x, windowSize.y), "Rescue The Kangaroo!"),
		position(windowSize.x * 3 / 20, windowSize.y * 17 / 22),
		velocity(0.0f, 0.0f),
		size(48, 48),
		player(position, velocity, size),
		level(0),
		points(0)
	{
		background_texture.loadFromFile("spritesheets/background.png");
		background_sprite.setTexture(background_texture);
		background_sprite.setScale(2.0f, 2.0f);

		loadPlatforms(mapMatrix);
		game_theme.openFromFile("audio/04-angel_island_zone-act_2.ogg");
	}

	void loadPlatforms(const vector<string>& mapMatrix){
		for(size_t i = 0; i < mapMatrix.size(); ++i){
			for(size_t j = 0; j < 20; ++j){
				if(mapMatrix[i][j] != 'X'){
					Platform * platform = new Platform(Vector2f(j * 24, i * 24), Vector2f(24, 24));
					platform->assignTexture(mapMatrix[i][j]);
					platforms.push_back(platform);
					//cout << "platform created at (" << j * 24 << ", " << i * 24 << ")" << endl;
				}
			}
		}
	}

	void drawPlatforms(RenderWindow& window){
		for(auto& platform : platforms){
			platform->draw(&window);
		}
	}

	void render(){
		window.clear();
		window.draw(background_sprite);
		player.draw(&window);
		drawPlatforms(window);

		window.display();
	}

	void run(){
		game_theme.setLoop(true);
		game_theme.play();

		while (window.isOpen()){
			Event event;
			while (window.pollEvent(event)){
				if (event.type == Event::Closed)
					window.close();
			}

			player.player_update(&window, platforms);
			render();
		}
	}

	void finish(){
		for(unsigned int i = 0; i < platforms.size(); i++){
			delete platforms.at(i);
		}
	}
};

#endif // GAME_H
