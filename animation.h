#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include "hitbox.h"

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

class AnimationHB : public Animation
{
public:

    AnimationHB(sf::Sprite** cs, Hitbox** chb, sf::Texture *t, Hitbox& hb, sf::IntRect dimension, int nbSprite, int spd, int l);
    bool update(int v);
    bool update();

private:
    std::vector<Hitbox*> hitboxs;
    Hitbox** currentHB;
};
