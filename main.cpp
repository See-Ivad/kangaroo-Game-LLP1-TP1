#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "movable.hpp"
#include "player.HPP"
#include "game.hpp"
#include "menu.hpp"

using namespace std;
using namespace sf;

int main(){
	vector<string> map{"XXXXXXXXXXXXXXXXXXXX",
						"XXXXXXXXXXXXXXXXXXXX",
						"XXXXXXXXXXXXXXXXXXXX",
						"LLLL3XXXXXXXXXX4LLLL",
						"@@23XXXXXXXXXXX1LLLL",
						"DdXXXXXXXXXXXXXX12@@",
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
	Game game1(map);

	RenderWindow window(VideoMode(480, 552), "Menu (use the arrows and enter)");

	Menu menu(480, 552);
	Texture texture;

	if(!texture.loadFromFile("spritesheets/menu.png")){
		cout << "fundo n funfo"<<endl;
	}

	Sprite sprite;
	sprite.setTexture(texture);
	sprite.setScale(2.0f, 2.0f);

	while(window.isOpen()){
		Event event;

		while(window.pollEvent(event)){

			switch(event.type){
			case Event::KeyReleased:
				switch(event.key.code){
				case Keyboard::Up :
					menu.moveUp();
					break;
				case Keyboard::Down:
					menu.moveDown();
					break;
				case Keyboard::Return:
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
				case Event::Closed:
					window.close();
					break;
			}
		}

		window.clear();
		window.draw(sprite);
		menu.draw(window);
		window.display();
	}
	return 0;
}
