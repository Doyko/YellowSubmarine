#include "game.h"

int main()
{
    Data::init();
    Game game("Yellow Submarine");
    game.loop();
    return 0;
}
