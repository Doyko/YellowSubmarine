#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "map.h"

class Entity
{
    public:

    Entity(int x, int y, int l, int w, sf::Texture *t, Map* map);
    bool move(int x, int y);
    ~Entity();

    int posX;
    int posY;
    int width;
    int height;
    sf::Sprite* sprite;
    Map* map;
};
