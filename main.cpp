#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "movable.hpp"
#include "player.HPP"
#include "game.hpp"

using namespace std;

int main(){
	vector<string> map{"XXXXXXXXXXXXXXXXXXXX",
						"XXXXXXXXXXXXXXXXXXXX",
						"XXXXXXXXXXXXXXXXXXXX",
						"XXXXXXXXXXXXXXXXXXXX",
						"##XXXXXXXXXXXXXXXX##",
						"##XXXXXXXXXXXXXXXX##",
						"##XXXXXXXXXXXXXXXX##",
						"##XXXXXXXXXXXXXXXX##",
						"##############XXX###",
						"##XXXXXXXXXXXXXXXX##",
						"##XXXXXXXXXXXXXXXX##",
						"##XXXXXXXXXXXXXXXX##",
						"##XXXXXXXXXXXXXXXX##",
						"###XXX##############",
						"##XXXXXXXXXXXXXXXX##",
						"##XXXXXXXXXXXXXXXX##",
						"##XXXXXXXXXXXXXXXX##",
						"##XXXXXXXXXXXXXXXX##",
						"##############XXX###",
						"##XXXXXXXXXXXXXXXX##",
						"##XXXXXXXXXXXXXXXX##",
						"##XXXXXXXXXXXXXXXX##",
						"##XXXXXXXXXXXXXXXX##",
						"###XXXXXXXXXXXXXX###"};
	Game game1(map);
	game1.run();
	return 0;
}

