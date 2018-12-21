#include "animation.h"

Animation::Animation(sf::Sprite** cs, sf::Texture *t, sf::IntRect dimension, int nbSprite, int spd, int l)
:
    currentSprite(cs),
    tick(0),
    nb(0),
    speed(spd),
    loop(l),
    last(0)
{
    for(int i = 0; i < nbSprite; i++)
    {
        dimension.left = i*dimension.width;
        sprites.push_back(new sf::Sprite(*t, dimension));
    }
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
    *currentSprite = sprites[nb + v];
    return true;
}

bool Animation::update()
{
    return update(last);
}
