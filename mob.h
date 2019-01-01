#pragma once
#include <SFML/Graphics.hpp>
#include "entity.h"
#include "data.h"
#include "projectile.h"
class Octopus : public TengibleEntity, public MovableEntity
{

public:

    enum stateEnum{up, down};

    Octopus(int x, int y, Map* m);
    bool update();
    bool move(int x, int y);
    ~Octopus();

    stateEnum state;
    int tick;
    sf::Sprite* spriteUp;
    sf::Sprite* spriteDown;
};