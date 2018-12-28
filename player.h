#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "hitbox.h"
#include "map.h"
#include "entity.h"
#include "param.h"
#include "animation.h"
#include "torpedo.h"

#define MAXLIFE 3
#define COOLDOWN 100

class Player : public MovableEntity, public TengibleEntity
{

public:

    Player(int x, int y, Map* m, Hitbox& hb, sf::Texture *t, sf::IntRect dimention);
    bool update();
    bool move(int x, int y);
    void shoot(std::vector<Entity*>& entities, sf::Texture *t, Hitbox& hb);
    void setRotation();
    ~Player();

    enum class AnimationIndex
    {
        moveRight,
        moveLeft,
        count,
    };
    Animation animations[int(AnimationIndex::count)];
    AnimationIndex currentAnimation = AnimationIndex::moveRight;

    int life;
    int shootCD;
};
