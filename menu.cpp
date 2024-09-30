#include "menu.hpp"

using namespace sf;

Menu::Menu(float width, float height){
	if(!font.loadFromFile("arial.ttf")){
		//em caso de erro
	}
	menu[0].setFont(font);
	menu[0].setColor(Color::Red);
	menu[0].setString("Play");
	menu[0].setPosition(Vector2f(width / 2, height / 3 * 1));

	menu[1].setFont(font);
	menu[1].setColor(Color::White);
	menu[1].setString("Exit");
	menu[1].setPosition(Vector2f(width / 2, height / 3 * 2));

	selectedItemIndex = 0;

//		menu[2].setFont(font);
//		menu[2].setColor(sf::Color::White);
//		menu[2].setString("Exit");
//		menu[2].setPosition(sf::Vector2f(width / 2, height / 4 * 3));
}

Menu::~Menu(){
}

void Menu::draw(RenderWindow &window){
	for(int i = 0; i < maxNumbersOfItems; i++){
		window.draw(menu[i]);
	}
}

void Menu::moveUp(){
	if(selectedItemIndex - 1 >= 0){
		menu[selectedItemIndex].setColor(Color::White);
		selectedItemIndex--;
		menu[selectedItemIndex].setColor(Color::Red);
	}
}

void Menu::moveDown(){
	if(selectedItemIndex + 1 < maxNumbersOfItems){
		menu[selectedItemIndex].setColor(Color::White);
		selectedItemIndex++;
		menu[selectedItemIndex].setColor(Color::Red);
	}
}









