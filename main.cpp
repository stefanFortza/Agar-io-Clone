#include <iostream>
#include <array>
#include <chrono>
#include <thread>
#include <SFML/Graphics.hpp>
#include <Helper.h>
#include <Game.hpp>

//////////////////////////////////////////////////////////////////////
/// NOTE: this include is needed for environment-specific fixes     //
/// You can remove this include and the call from main              //
/// if you have tested on all environments, and it works without it //
#include "env_fixes.h" //
//////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////
/// This class is used to test that the memory leak checks work as expected even when using a GUI
class SomeClass
{
public:
    explicit SomeClass(int) {}
};

SomeClass *getC()
{
    return new SomeClass{2};
}
//////////////////////////////////////////////////////////////////////

int main()
{
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
	while (!game.GetWindow()->IsDone())
	{
		// Game loop.
		game.HandleInput();
		game.Update();
		game.Render();
		// sf::sleep(sf::seconds(0.2));
		game.RestartClock();
	}

    return 0;
}
