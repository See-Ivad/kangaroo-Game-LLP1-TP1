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
		"TcbbbbbbbbbbbbXXXbCt",
		"TtXXXXXXXXXXXXXXXXTt",
		"TtXXXXXXXXXXXXXXXXTt",
		"TtXXXXXXXXXXXXXXXXTt",
		"TtXXXXXXXXXXXXXXXXTt",
		"TcbXXXbbbbbbbbbb&***",
		"TtXXXXXXXXXXXXXX1LLL",
		"TtXXXXXXXXXXXXXXX1@@",
		"TtXXXXXXXXXXXXXXXXDd",
		"TtXXXXXXXXXXXXXXXXTt",
		"***(bbbbbbbbbXXXbbCt",
		"LLL3XXXXXXXXXXXXXXTt",
		"@@3XXXXXXXXXXXXXXXTt",
		"DdXXXXXXXXXXXXXXXXTt",
		"TtXXXXXXXXXXXXXXXXTt",
		"---XXXXXXXXXXXXXX---"};

	Game game1(map);

	RenderWindow window(VideoMode(480, 552), "Menu(use the arrows and enter)");

	Menu menu(480, 552);

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
		menu.draw(window);
		window.display();
	}
	return 0;
}

