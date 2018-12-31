#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include "hitbox.h"

class Animation
{

public:

    Animation() = default;
    Animation(sf::Texture *t, sf::IntRect dimension, int nbSprite, int spd);

    virtual bool update();

    sf::Sprite* currentSprite;

protected:

    std::vector<sf::Sprite*> sprites;
    int tick;
    int nb;
    int speed;
};
