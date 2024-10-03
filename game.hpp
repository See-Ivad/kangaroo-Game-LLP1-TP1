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
	RenderWindow * window;

	Vector2f position;
	Vector2f velocity;
	Vector2f size;
	Player player;
	vector<Platform *> platforms;
	vector<Ladder *> ladders;
	vector<Enemy *> enemies;
	vector<string> mapMatrix;

	Texture background_texture;
	Sprite background_sprite;

	int level;
	int lives;
	int points;

	Music game_theme;

public:
	Game(RenderWindow* rWindow) :
		windowSize(480, 552),
		position(windowSize.x * 3 / 20, windowSize.y * 19 / 22),
		velocity(0.0f, 0.0f),
		size(48, 48),
		player(position, velocity, size),
		level(0),
		lives(3),
		points(0)
	{
		window = rWindow;

		if(!background_texture.loadFromFile("spritesheets/background.png")){
			std::cerr << "Unable to open \"spritesheets/background.png\"" << std::endl;
			std::exit(EXIT_FAILURE);
		}
		background_sprite.setTexture(background_texture);
		background_sprite.setScale(2.0f, 2.0f);

		defineMapMatrix();
		loadPlatforms();

		if(!game_theme.openFromFile("audio/04-angel_island_zone-act_2.ogg")){
			std::cerr << "Unable to open \"audio/04-angel_island_zone-act_2.ogg\"" << std::endl;
			std::exit(EXIT_FAILURE);
		}
	}

	void defineMapMatrix(){
		int map = level % 3;

		if(map == 0){
			mapMatrix = {
					"---X---XXXXXXXXXXXXX",
					"-X-X-X-XXXXXXXXXXXXX",
					"---X---XXXXXXXXXXXXX",
					"LLLL3XXXXXXXXXXX4LLL",
					"@@23XXXXXXXXXXXXX1LL",
					"DdXXXXXXXXXXXXXXXX1@",
					"TtXXXXXXXXXXXXXXXXDd",
					"TcbbbbbbbbbbbbvvvbCt",
					"TtXXXXXXXXXXXXVVVXTt",
					"TtXXXXXXXXXXXXVVVXTt",
					"TtXXXXXXXXXXXXVVVXTt",
					"TtXXXXXXXXXXXXVVVXTt",
					"Tcbvvvbbbbbbbbbb&***",
					"TtXVVVXXXXXXXXXX1LLL",
					"TtXVVVXXXXXXXXXXX1@@",
					"TtXVVVXXXXXXXXXXXXDd",
					"TtXVVVXXXXXXXXXXXXTt",
					"***(bbbbbbbbbbvvvbCt",
					"LLL3XXXXXXXXXXVVVXTt",
					"@@3XXXXXXXXXXXVVVXTt",
					"DdXXXXXXXXXXXXVVVXTt",
					"TtXXXXXXXXXXXXVVVXTt",
					"---XXXXXXXXXXXXXX---"};
		}
		//needs to be changed - NOT FINAL
		if(map == 1){
			mapMatrix = {
					"---III-IIIIIIIIIIIII",
					"-I-III-IIIIIIIIIIIII",
					"---III-IIIIIIIIIIIII",
					"LLLL3XXXXXXXXXX4LLLL",
					"@@23XXXXXXXXXXX1LLLL",
					"DdXXXXXXXXXXXXXX12@@",
					"TtXXXXXXXXXXXXvvvXDd",
					"TcbbbbbbbbbbbbvvvbCt",
					"TtXXXXXXXXXXXXXXXXTt",
					"TtXXXXXXXXXXXXXXXXTt",
					"TtXXXXXXXXXXXXXXXXTt",
					"TtXvvvXXXXXXXXXXXXTt",
					"Tcbvvvbbbbbbbbbb&***",
					"TtXXXXXXXXXXXXXX1LLL",
					"TtXXXXXXXXXXXXXXX1@@",
					"TtXXXXXXXXXXXXXXXXDd",
					"TtXXXXXXXXXXXXvvvXTt",
					"***(bbbbbbbbbbvvvbCt",
					"LLL3XXXXXXXXXXXXXXTt",
					"@@3XXXXXXXXXXXXXXXTt",
					"DdXXXXXXXXXXXXXXXXTt",
					"TtXXXXXXXXXXXXXXXXTt",
					"--------------------"};
		}
		//needs to be changed - NOT FINAL
		if(map == 2){
			mapMatrix = {
					"II-I---IIIIIIIIIIIII",
					"II-I-I-IIIIIIIIIIIII",
					"II-I---IIIIIIIIIIIII",
					"LLLL3XXXXXXXXXX4LLLL",
					"@@23XXXXXXXXXXX1LLLL",
					"DdXXXXXXXXXXXXXX12@@",
					"TtXXXXXXXXXXXXvvvXDd",
					"TcbbbbbbbbbbbbvvvbCt",
					"TtXXXXXXXXXXXXVVVXTt",
					"TtXXXXXXXXXXXXVVVXTt",
					"TtXXXXXXXXXXXXVVVXTt",
					"TtXvvvXXXXXXXXXXXXTt",
					"Tcbvvvbbbbbbbbbb&***",
					"TtXVVVXXXXXXXXXX1LLL",
					"TtXVVVXXXXXXXXXXX1@@",
					"TtXVVVXXXXXXXXXXXXDd",
					"TtXXXXXXXXXXXXXXXXTt",
					"***(XXXXXXXXXXXXXXCt",
					"LLL3XXXXXXXXXXXXXXTt",
					"@@3XXXXXXXXXXXXXXXTt",
					"DdXXXXXXXXXXXXXXXXTt",
					"TtXXXXXXXXXXXXXXXXTt",
					"--------------------"};
		}
	}

	void loadPlatforms(){
		for(size_t i = 0; i < mapMatrix.size(); ++i){
			for(size_t j = 0; j < 20; ++j){
				if(mapMatrix[i][j] != 'X' && mapMatrix[i][j] != 'I' &&
						mapMatrix[i][j] != 'V' && mapMatrix[i][j] != 'v'){
					Platform * platform = new Platform(Vector2f(j * 24, i * 24), Vector2f(24, 24));
					platform->assignTexture(mapMatrix[i][j]);
					platforms.push_back(platform);
				}
				else if(mapMatrix[i][j] != 'I' &&
						(mapMatrix[i][j] == 'V' || mapMatrix[i][j] == 'v')){
					Ladder * ladder = new Ladder(Vector2f(j * 24, i * 24), Vector2f(24, 24));
					ladder->assignTexture(mapMatrix[i][j]);
					if(mapMatrix[i][j] == 'v')
						ladder->halfSolid = true;
					ladders.push_back(ladder);
				}
			}
		}
	}

	void drawPlatforms(RenderWindow& window){
		for(auto& platform : platforms){
			platform->draw(&window);
		}
		for(auto& ladder : ladders){
			ladder->draw(&window);
		}
	}

	void render(){
		window->clear();
		window->draw(background_sprite);
		drawPlatforms(*window);
		player.draw(window);

		window->display();
	}

	void updateLevel(){
		Vector2f position = player.getPosition();

		if(position.y <= windowSize.y * 6 / 22){
			level++;
			defineMapMatrix();
			loadPlatforms();

			player.setPosition(Vector2f(24 * 3, 24 * 20));

			if(lives < 3){
				lives++;
			}
		}
	}

	void run(){
		game_theme.setLoop(true);
		//game_theme.play();
		Clock time;
		while (window->isOpen()){ //Loop de eventos
			Event event;
			Time deltaTime;
			deltaTime = time.restart();

			while (window->pollEvent(event)){
				if (event.type == Event::Closed || Keyboard::isKeyPressed(Keyboard::Escape)){
					window->close();
					exit(EXIT_SUCCESS);
				}

				if((event.type == Event::KeyReleased) && (event.key.code == Keyboard::M)){
					if(game_theme.getStatus() == sf::SoundSource::Status::Playing)
						game_theme.pause();
					else if(game_theme.getStatus() == sf::SoundSource::Status::Paused)
						game_theme.play();
				}
			}

			player.player_update(window, platforms, ladders, deltaTime.asSeconds());
			updateLevel();
			render();
		}
	}

	void finish(){
		for(unsigned int i = 0; i < platforms.size(); i++){
			delete platforms.at(i);
		}
		for(unsigned int i = 0; i < ladders.size(); i++){
			delete ladders.at(i);
		}
	}
};

#endif // GAME_H
