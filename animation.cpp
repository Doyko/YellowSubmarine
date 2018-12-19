#include "animation.h"

Animation::Animation(sf::Texture *t, sf::IntRect dimention, int nbSprite, int spd, int l)
:
    tick(0),
    nb(0),
    speed(spd),
    loop(l),
    last(0)
{
    for(int i = 0; i < nbSprite; i++)
    {
        dimention.left = i*dimention.width;
        sprites.push_back(new sf::Sprite(*t, dimention));
    }
    currentSprite = sprites[0];
}

bool Animation::update(int v)
{
    last = v;
    tick++;
    if(tick != speed)
        return false;

    tick = 0;
    nb++;
    if(nb == loop)
        nb = 0;
    currentSprite = sprites[nb + v];
    return true;
}
