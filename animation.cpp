#include "animation.h"

Animation::Animation(sf::Texture *t, sf::IntRect dimension, int nbSprite, int spd)
:
    tick(0),
    nb(0),
    speed(spd)
{
    for(int i = 0; i < nbSprite; i++)
    {
        sprites.push_back(new sf::Sprite(*t, dimension));
        dimension.left += dimension.width;
    }
    currentSprite = sprites[0];
}

bool Animation::update()
{
    tick++;
    if(tick != speed)
        return false;

    tick = 0;
    nb++;
    if(nb == int(sprites.size()))
        nb = 0;
    currentSprite = sprites[nb];
    return true;
}
