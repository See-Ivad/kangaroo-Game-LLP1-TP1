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
	game1.run();
	return 0;
}

