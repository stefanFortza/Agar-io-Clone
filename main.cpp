#include <iostream>
#include <array>
#include <chrono>
#include <thread>
#include "src/headers/Game.hpp"

//////////////////////////////////////////////////////////////////////
/// NOTE: this include is needed for environment-specific fixes     //
/// You can remove this include and the call from main              //
/// if you have tested on all environments, and it works without it //
#include "env_fixes.h" //
//////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////
/// This class is used to test that the memory leak checks work as expected even when using a GUI
class SomeClass {
public:
	explicit SomeClass(int) {
	}
};

SomeClass *getC() {
	return new SomeClass{2};
}

//////////////////////////////////////////////////////////////////////

int main() {
	////////////////////////////////////////////////////////////////////////
	/// NOTE: this function call is needed for environment-specific fixes //
	init_threads(); //
	////////////////////////////////////////////////////////////////////////
	///

	SomeClass *c = getC();
	std::cout << c << "\n";
	delete c;

	// Program entry point.
	Game game; // Creating our game object.
	game.start();
	// while (!game.getWindow()->isDone()) {
	// 	// while (game.isWindowOpen()) {
	// 	// Game loop.
	// 	game.handleInput();
	// 	game.update();
	// 	game.render();
	// 	// sf::sleep(sf::seconds(0.2));
	// 	game.restartClock();
	// }

	return 0;
}
