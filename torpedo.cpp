#include "torpedo.h"

Torpedo::Torpedo(int x, int y, Map* m, Hitbox& hb, sf::Texture *t, sf::IntRect dimention, int d)
:
    Entity(x, y, m, t, dimention),
    MovableEntity(x, y, m, t, dimention),
    TengibleEntity(x, y, m, hb, t, dimention),
    dir(d)
{
    maxSpeed = 20;
    if(d == 1)
        animation = new Animation(t, sf::IntRect(0, 37, 25, 7), 4, 10);
    else
        animation = new Animation(t, sf::IntRect(0, 44, 25, 7), 4, 10);
}

bool Torpedo::update()
{
    if(dir == 1)
        changeSpeed(ACCELERATION, 0);
    else
        changeSpeed(-ACCELERATION, 0);
    sprite->move(speedX, speedY);
    return true;
}

bool move(int x, int y)
{
    return true;
}
