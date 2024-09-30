#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "movable.hpp"
#include "player.HPP"
#include "game.hpp"
#include "menu.hpp"

using namespace std;

int main(){

	vector<string> map{"XXXXXXXXXXXXXXXXXXXX",
						"XXXXXXXXXXXXXXXXXXXX",
						"XXXXXXXXXXXXXXXXXXXX",
						"TTXXXXXXXXXXXXXXXXTT",
						"TTXXXXXXXXXXXXXXXXTT",
						"TTXXXXXXXXXXXXXXXXTT",
						"TTXXXXXXXXXXXXXXXXTT",
						"TTbbbbbbbbbbbbXXXbTT",
						"TTXXXXXXXXXXXXXXXXTT",
						"TTXXXXXXXXXXXXXXXXTT",
						"TTXXXXXXXXXXXXXXXXTT",
						"TTXXXXXXXXXXXXXXXXTT",
						"TTbXXXbbbbbbbbbbbbTT",
						"TTXXXXXXXXXXXXXXXXTT",
						"TTXXXXXXXXXXXXXXXXTT",
						"TTXXXXXXXXXXXXXXXXTT",
						"TTXXXXXXXXXXXXXXXXTT",
						"TTbbbbbbbbbbbXXXbbTT",
						"TTXXXXXXXXXXXXXXXXTT",
						"TTXXXXXXXXXXXXXXXXTT",
						"TTXXXXXXXXXXXXXXXXTT",
						"TTXXXXXXXXXXXXXXXXTT",
						"---XXXXXXXXXXXXXX---"};
	Game game1(map);


	sf::RenderWindow window(sf::VideoMode(480, 552), "Menu(use the arrows and enter)");

	Menu menu(480, 552);

	sf::Texture texture;
	 if(!texture.loadFromFile("/kangaroo/spritesheets/background.png")){
		 cout << "fundo n funfo"<<endl;
	 }

	 sf::Sprite sprite;
	 sprite.setTexture(texture);


	while(window.isOpen()){
		sf::Event event;

			while(window.pollEvent(event)){

				switch(event.type){

				case sf::Event::KeyReleased:
					switch(event.key.code){

					case sf::Keyboard::Up :
						menu.moveUp();
						break;

				case sf::Keyboard::Down:
						menu.moveDown();
						break;


				case sf::Keyboard::Return:
						switch(menu.getPressedItem()){

						case 0:
							 window.close();
								game1.run();
							break;

						case 1:
							window.close();
							break;
						}
						break;
					}

					break;

				case sf::Event::Closed:
					window.close();
					break;
				}
			}

			window.clear();
			menu.draw(window);
			window.draw(sprite);
			window.display();
	}

//	vector<string> map{"XXXXXXXXXXXXXXXXXXXX",
//						"XXXXXXXXXXXXXXXXXXXX",
//						"XXXXXXXXXXXXXXXXXXXX",
//						"TTXXXXXXXXXXXXXXXXTT",
//						"TTXXXXXXXXXXXXXXXXTT",
//						"TTXXXXXXXXXXXXXXXXTT",
//						"TTXXXXXXXXXXXXXXXXTT",
//						"TTbbbbbbbbbbbbXXXbTT",
//						"TTXXXXXXXXXXXXXXXXTT",
//						"TTXXXXXXXXXXXXXXXXTT",
//						"TTXXXXXXXXXXXXXXXXTT",
//						"TTXXXXXXXXXXXXXXXXTT",
//						"TTbXXXbbbbbbbbbbbbTT",
//						"TTXXXXXXXXXXXXXXXXTT",
//						"TTXXXXXXXXXXXXXXXXTT",
//						"TTXXXXXXXXXXXXXXXXTT",
//						"TTXXXXXXXXXXXXXXXXTT",
//						"TTbbbbbbbbbbbXXXbbTT",
//						"TTXXXXXXXXXXXXXXXXTT",
//						"TTXXXXXXXXXXXXXXXXTT",
//						"TTXXXXXXXXXXXXXXXXTT",
//						"TTXXXXXXXXXXXXXXXXTT",
//						"---XXXXXXXXXXXXXX---"};
//
//	Game game1(map);
//	game1.run();


	return 0;
}

