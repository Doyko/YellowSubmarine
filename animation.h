#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>

class Animation
{
    public:

    Animation(sf::Texture *t, sf::IntRect dimension, int nbSprite, int spd, int l);
    ~Animation();

    bool update(int v);

    std::vector<sf::Sprite*> sprites;
    sf::Sprite* currentSprite;

    int tick;
    int nb;
    int speed;
    int loop;
    int last;
};
