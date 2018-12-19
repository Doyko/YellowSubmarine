#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>

class Animation
{
    public:

    Animation(sf::Texture *t, sf::IntRect dimension, int nbSprite, int spd);
    ~Animation();

    bool update();

    std::vector<sf::Sprite*> sprites;
    sf::Sprite* currentSprite;

    int tick;
    int nb;
    int speed;
};
