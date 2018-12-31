#include "game.h"

int main()
{
    Texture::init();
    Game game("Yellow Submarine");
    game.loop();
    return 0;
}
