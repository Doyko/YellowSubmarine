#pragma once
#include <SFML/Graphics.hpp>
#include "data.h"
#include "projectile.h"
#include "game.h"
#include "effect.h"

class Mob : public MovableEntity, public TangibleEntity
{

public :
    Mob(const int x, const int y, const sf::IntRect dimension);

    bool update();
    bool move(const int x, const int y);
};

class Octopus : public Mob
{

public:

    enum stateEnum{up, down};

    Octopus(const int x, const int y);
    ~Octopus();

    bool update();

private:

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
    Mine(const int x, const int y);
    ~Mine();

    void destroy();
    bool update();

private:

    static sf::IntRect dimension;
    int center;
    int tick;
};

class Shark : public Mob
{
public:

    Shark(const int x, const int y);
    ~Shark();

    void destroy();
    bool update();

private:

    enum class AnimationIndex
    {
        moveRight,
        moveLeft,
        count,
    };
    Animation* animations[int(AnimationIndex::count)];
    AnimationIndex currentAnimation = AnimationIndex::moveRight;

    static sf::IntRect dimension;
    static sf::IntRect animRight;
    static sf::IntRect animLeft;
    static int nbSprite;
    static int animSpeed;
};
