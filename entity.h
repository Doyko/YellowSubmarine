#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "param.h"

class Entity
{
    public:

    Entity(int x, int y, int l, int w, sf::Texture *t);
    bool move(int x, int y);
    ~Entity();

    int posX;
    int posY;
    int width;
    int height;
    sf::Sprite *eSprite;
};
