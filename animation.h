#pragma once
#include "param.h"

class Animation
{

public:

    Animation(sf::Sprite** cs, sf::Texture *t, sf::IntRect dimension, int nbSprite, int spd, int l);

    virtual bool update(int v);
    virtual bool update();

protected:

    std::vector<sf::Sprite*> sprites;
    sf::Sprite** currentSprite;
    int tick;
    int nb;
    int speed;
    int loop;
    int last;
};
