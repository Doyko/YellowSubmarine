#include "game.h"

int main()
{
    Data::init();
    Game game("Yellow Submarine");
    game.menuLoop();
    game.loop();
    Data::clearData();
    return 0;
}
