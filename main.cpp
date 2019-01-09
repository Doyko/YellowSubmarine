#include "game.h"

int main()
{
    Data::init();
    Game* game = new Game("Yellow Submarine");
    game->menuLoop();
    game->loop();
    delete game;
    Data::clearData();
    return 0;
}
