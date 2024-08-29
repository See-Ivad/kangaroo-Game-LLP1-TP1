#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include "player.hpp"
#include "platforms.hpp"
#include "ladder.hpp"
#include <vector>

class Game{
private:
	Vector2f windowSize;

	sf::RenderWindow window;

	Vector2f position;
	Vector2f velocity;
	Vector2f size;
	Player player;
	vector<Platform> platforms;
	vector<Ladder> ladders;

public:
	Game(vector<string> mapMatrix) :
	        windowSize(480, 480),
	        window(sf::VideoMode(windowSize.x, windowSize.y), "Kangaroo"),
	        position(windowSize.x * 3 / 20, windowSize.y * 17 / 22),
	        velocity(0.0f, 0.0f),
	        size(48, 48),
	        player(position, velocity, size)
	    {

		for (int i = 0; i < mapMatrix.size(); i++){
			for(int j = 0; j < 20 ; j++){
				if(mapMatrix[i][j] == '#'){
					platforms.push_back(Platform(Vector2f (j*20, i*20),Vector2f (24, 24)));

					cout << "create platform" << endl;
				}
			}
		}

		for (int i = 0; i < mapMatrix.size(); i++){
					for(int j = 0; j < 20 ; j++){
						if(mapMatrix[i][j] == '@'){
							ladders.push_back(Ladder(Vector2f (j*20, i*20),Vector2f (24, 24)));

							cout << "create ladder" << endl;
						}
					}
				}



//	        // Constructor body (if needed)
//		        platforms.push_back(
//						Platform(Vector2f(0, 21 * 24), Vector2f(20 * 24, 24)));//PLAT-0
//
//				platforms.push_back(
//						Platform(Vector2f(0, 16 * 24), Vector2f(530, 24)));//PLAT1
//
//				platforms.push_back(
//						Platform(Vector2f(615, 576), Vector2f(150, 24)));//PLAT1
//
//
//				platforms.push_back(
//						Platform(Vector2f(183, 396), Vector2f(600, 24)));//PLAT2
//				platforms.push_back(
//						Platform(Vector2f(0, 396), Vector2f(100, 24)));//PLAT2
//
//
//				platforms.push_back(
//						Platform(Vector2f(0, 216), Vector2f(530, 24)));//PLAT3
//
//				platforms.push_back(
//						Platform(Vector2f(615, 216), Vector2f(150, 24)));//PLAT3
//
//
//
//
//
//				ladders.push_back(
//						Ladder(Vector2f(540, 576), Vector2f(72, 180)));//ESCADA1
//
//				ladders.push_back(
//						Ladder(Vector2f(108, 396), Vector2f(72, 180)));//ESCADA2
//
//				ladders.push_back(
//						Ladder(Vector2f(540, 216), Vector2f(72, 180)));//ESCADA3
	    }



	void render() {
			window.clear();
			player.draw(&window);
			for (int i = 0; i < platforms.size(); i++) {
				window.draw(platforms[i].getBody());
			}

			for (int i = 0; i < ladders.size(); i++) {
				window.draw(ladders[i].getBody());
			}

			//cout << "Out: Game render" << endl;

			window.display();
		}

	void run(){
		while(window.isOpen()){
			sf::Event event;
			while(window.pollEvent(event)){
				if(event.type == sf::Event::Closed)
					window.close();
			}

			player.update(&window, platforms);
			render();
		}
	}

};

#endif // GAME_H
