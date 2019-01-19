#include "animation.h"

Animation::Animation()
{

}

Animation::Animation(const sf::Texture *t, sf::IntRect dimension, const int nbSprite, const int spd)
:
    tick(0),
    nb(0),
    speed(spd)
{
    // add all sprite to the animation
    for(int i = 0; i < nbSprite; i++)
    {
        sprites.push_back(new sf::Sprite(*t, dimension));
        dimension.left += dimension.width;
    }
    currentSprite = sprites[0];
}

// return true if the animation end
bool Animation::update()
{
    tick++;
    if(tick != speed)
        return false;

    tick = 0;
    nb++;
    // if it's the end of the animation
    if(nb == int(sprites.size()))
    {
        nb = 0;
        currentSprite = sprites[nb];
        return true;
    }
    currentSprite = sprites[nb];
    return false;
}

Animation::~Animation()
{
    for(size_t i = 0; i < sprites.size(); i++)
    {
        delete sprites[i];
        sprites[i] = NULL;
    }
}

void Animation::setPosition(const int x, const int y)
{
    for(size_t i = 0; i < sprites.size(); i++)
    {
        sprites[i]->setPosition(x,y);
    }
}
