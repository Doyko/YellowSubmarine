#pragma once
#include <SFML/Graphics.hpp>
#include "entity.h"
#include "data.h"
#include "projectile.h"
#include "game.h"
#include "effect.h"

class Mob : public MovableEntity, public TangibleEntity
{

public :
    Mob(int x, int y, sf::IntRect dimension);
    bool update();
    bool move(int x, int y);
};

class Octopus : public Mob
{

public:

    enum stateEnum{up, down};

    Octopus(int x, int y);
    bool update();
    ~Octopus();

    stateEnum state;
    int tick;
    sf::Sprite* spriteUp;
    sf::Sprite* spriteDown;

    static sf::IntRect dimension;
    static sf::IntRect dimSpriteUp;
    static sf::IntRect dimSpriteDown;
};

class Mine : public Mob
{

public:
    Mine(int x, int y);
    ~Mine();
    bool update();

    static sf::IntRect dimension;
    int center;
    int tick;
};

class Barricade : public TangibleEntity
{

public:

    Barricade(int x, int y);
    ~Barricade();

    static sf::IntRect dimension;
};
