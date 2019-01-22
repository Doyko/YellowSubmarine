#include "game.h"

int main()
{
    srand (time(NULL));
    Data::init();
    Game* game = new Game("Yellow Submarine");
    game->menuLoop();
    delete game;
    Data::clearData();
    return 0;
}
