#ifndef MENU_HPP_
#define MENU_HPP_
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>



using namespace sf;

class Menu{
public:
	Menu(float width, float height);
	~Menu();

    int const static maxNumbersOfItems = 3;

	void draw(RenderWindow &window);
	void moveUp();
	void moveDown();
	int getPressedItem(){return selectedItemIndex;}
	int getmaxNumbersOfItems(){return maxNumbersOfItems;}

	// private:
	int selectedItemIndex;
	Font font;
	Text menu[maxNumbersOfItems];
};

#endif /* MENU_HPP_ */
