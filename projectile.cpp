#include "projectile.h"

Projectile::Projectile(int x, int y, Map* m, Hitbox& hb, sf::Texture *t, sf::IntRect dimention, sf::Vector2f speed)
:
    Entity(x, y, m, t, dimention),
    MovableEntity(x, y, m, t, dimention),
    TengibleEntity(x, y, m, hb, t, dimention)
{
    speedX = speed.x;
    speedY = speed.y;
}

Projectile::~Projectile()
{

}

Torpedo::Torpedo(int x, int y, Map* m, Hitbox& hb, sf::Texture *t, sf::IntRect dimention, sf::Vector2f speed)
:
    Entity(x, y, m, t, dimention),
    Projectile(x, y, m, hb, t, dimention, speed)
{
    maxSpeed = 20;
    if(speedX > 0)
        animation = new Animation(t, sf::IntRect(0, 37, 25, 7), 4, 10);
    else
        animation = new Animation(t, sf::IntRect(0, 44, 25, 7), 4, 10);
}

bool Torpedo::update()
{
    if(speedX > 0)
        changeSpeed(ACCELERATION, 0);
    else
        changeSpeed(-ACCELERATION, 0);
    animation->update();
    sprite = animation->currentSprite;
    return move(speedX, speedY);
}

bool Torpedo::move(int x, int y)
{
    int moveX = x;
    int moveY = y;
    bool flag = false;

    while(moveX != 0 && hitbox->checkCollision(posX + moveX, posY, map))
    {
        moveX > 0 ? moveX-- : moveX++;
        flag = true;
    }
    posX = posX + moveX;

    while(moveY != 0 && hitbox->checkCollision(posX, posY + moveY, map))
    {
        moveY > 0 ? moveY-- : moveY++;
        flag = true;
    }

    posY = posY + moveY;
    sprite->setPosition(posX,posY);
    return flag;
}

Torpedo::~Torpedo()
{
    return;
}

Explosion::Explosion(int x, int y, Map* m, Hitbox& hb, sf::Texture *t, sf::IntRect dimention)
:
    Entity(x, y, m, t, dimention),
    TengibleEntity(x, y, m, hb, t, dimention),
    animation(new Animation(t, dimention, 5, 5))
{}

bool Explosion::update()
{
    if(animation->update())
        return true;
    sprite = animation->currentSprite;
    sprite->setPosition(posX, posY);
    return false;
}

Explosion::~Explosion()
{
    return;
}
