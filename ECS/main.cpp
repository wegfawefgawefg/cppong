// SDL Test 2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "Game.hpp"

#undef main

int main()
{
    Game game = Game();
    game.run();
    return 0;
}