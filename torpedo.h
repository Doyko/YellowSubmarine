#pragma once
#include <SFML/Graphics.hpp>
#include "entity.h"
#include "map.h"
#include "animation.h"

class Torpedo : public MovableEntity, public TengibleEntity
{

public:

    Torpedo(int x, int y, Map* m, Hitbox& hb, sf::Texture *t, sf::IntRect dimention, int d);
    bool update();
    bool move(int x, int y);

    int dir;
    Animation* animation;
};
