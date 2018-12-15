#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "param.h"
#include "hitbox.h"

#define HEIGHT 37
#define WIDTH 64
#include "map.h"

class Player
{
    public:

    Player(int x, int y, sf::Texture *t, Map* m);
    bool move(int x, int y);
    ~Player();

    int posX;
    int posY;
    Map* map;
    sf::Sprite *sprite;
    Hitbox* hitbox;
};
