/*
 * menu.hpp
 *
 *  Created on: 30 de set. de 2024
 *      Author: vitor
 */

#ifndef MENU_HPP_
#define MENU_HPP_
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#define maxNumbersOfItems 3

class Menu {

	public:
	 Menu(float width, float height);
     ~Menu();

     void draw(sf::RenderWindow &window);
     void moveUp();
     void moveDown();
     int getPressedItem(){return selectedItemIndex;}

   // private:
     int selectedItemIndex;
     sf::Font font;
     sf::Text menu[maxNumbersOfItems];
};


#endif /* MENU_HPP_ */
