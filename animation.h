#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include "hitbox.h"

class Animation
{

public:

    Animation() = default;
    Animation(const sf::Texture *t, sf::IntRect dimension, const int nbSprite, const int spd);

    virtual bool update();

    sf::Sprite* currentSprite;

private:

    std::vector<sf::Sprite*> sprites;
    int tick;
    int nb;
    int speed;
};
