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

AnimationHB::AnimationHB(sf::Sprite** cs, Hitbox** chb, sf::Texture *t,  Hitbox& hb, sf::IntRect dimension, int nbSprite, int spd, int l)
:
    Animation(cs, t, dimension, nbSprite, spd, l),
    currentHB(chb)
{
    for(int i = 0; i < nbSprite; i++)
    {
        dimension.left = i*dimension.width;
        hitboxs.push_back(new Hitbox(hb, dimension));
    }
}

bool AnimationHB::update(int v)
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
    *currentHB = hitboxs[nb + v];
    return true;
}

bool AnimationHB::update()
{
    return update(last);
}
