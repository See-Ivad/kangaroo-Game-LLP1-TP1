#ifndef MENU_HPP_
#define MENU_HPP_
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#define maxNumbersOfItems 3

using namespace sf;

class Menu{
public:
	Menu(float width, float height);
	~Menu();

	void draw(RenderWindow &window);
	void moveUp();
	void moveDown();
	int getPressedItem(){return selectedItemIndex;}

	// private:
	int selectedItemIndex;
	Font font;
	Text menu[maxNumbersOfItems];
};

#endif /* MENU_HPP_ */
