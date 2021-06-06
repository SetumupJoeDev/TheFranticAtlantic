
#include <SFML/Graphics.hpp>

#include "Game.h"

int main( )
{
    srand( time( NULL ) );
    Game game;
    game.runMainLoop( );

    return 0;
}