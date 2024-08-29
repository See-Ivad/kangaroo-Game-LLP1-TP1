#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "movable.hpp"
#include "player.HPP"
#include "game.hpp"

using namespace std;

int main(){
	vector<string> map{"XXXXXXXXXXX#XXXXXXXX",
					   "X##XXXXXXXXXXXXXXXXX",
					   "XXXXXXXXXXXXXXXXXXXX",
					   "XXXXXXXXXXXXXXXXXXXX",
					   "XXXXXXXXXX###XXXXXXX",
					   "XXXXXXXXXXXXXXXXXXXX",
					   "XXXXXXXXXXXXXXXXXXXX",
					   "XXXXXXXXXXXXXXXXXXXX",
					   "XXXXXXXXXXXXXXXXXXXX",
					   "XXXXXXXXXXXXXXXXXXXX",
					   "XXXXXXXXXXXXXXXXXXXX",
					   "XXXXXXXXXXXXXXXXXXXX",
					   "XXXXXXXXXXXXXXXXXXXX",
					   "XXXXXXXXXXXXXXXXXXXX",
					   "XXXXXXXXXXXXXXXXXXXX",
					   "XXXXXXXXXXXXXXXXXXXX",
					   "XXXXXXXXXXXXXXXXXXXX",
					   "XXXXXXXXXXXXXXXXXXXX",
					   "XXXXXXXXXXXXXXXXXXXX",
					   "XXXXXXXXXXXXXXXXXXXX",
					   "XXXXXXXXXXXXXXXXXXXX",
					   "XXXXXXXXXXXXXXXXXXXX",
					   "XXXXXXXXXXXXXXXXXXXX",
					   "XXXXXXXXX####XXXXXXX"};
	Game game1(map);
	game1.run();
    return 0;
}

