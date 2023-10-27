#include <iostream>

#include "Game.h"

int main()
{
    //initalise Game engine
    game game;

    //runs the game
    game.run();

    //end of application
    std::cout<<"Game Ended"<<std::endl;

    return 0;
}