#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "param.h"

class Entity
{
    public:

    Entity(int x, int y, int l, int w);
    bool move(int x, int y);

    int posX;
    int posY;
    int width;
    int height;
};
