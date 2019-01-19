#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

class Animation
{

public:

    Animation();
    Animation(const sf::Texture *t, sf::IntRect dimension, const int nbSprite, const int spd);
    ~Animation();

    void setPosition(const int x, const int y);

    bool update();

    sf::Sprite* currentSprite;

private:

    std::vector<sf::Sprite*> sprites;
    int tick;
    int nb;
    int speed;
};
