#include "mob.h"

Octopus::Octopus(int x, int y, Map* m)
:
    Entity(x, y, m, Data::dimOctopus),
    MovableEntity(x, y, m, Data::dimOctopus),
    TengibleEntity(x, y, m, Data::dimOctopus),
    state(down),
    tick(100)
{
    spriteUp = new sf::Sprite(Data::textureEntity, Data::spriteOctopusUp);
    spriteDown = new sf::Sprite(Data::textureEntity, Data::spriteOctopusDown);
    sprite = spriteDown;
    speedY = 1;
}

bool Octopus::update()
{
    if(state == down)
    {
        tick--;
        if(tick == 0 || move(speedX, speedY))
        {
            state = up;
            tick = 30;
            speedY = -5;
            sprite = spriteUp;
            sprite->setPosition(posX,posY);
        }
    }
    else
    {
        tick--;
        if(tick == 0 || move(speedX, speedY))
        {
            state = down;
            tick = 110;
            speedY = 1;
            sprite = spriteDown;
            sprite->setPosition(posX,posY);
        }
        else
        {
            if(tick > 25)
                Projectile::projectiles.push_back(new Ink(posX, posY + 20, map, sf::Vector2f(0, 1)));
            if(tick == 25)
                speedY = -4;
            if(tick == 10)
                speedY = -3;
            if(tick == 5)
                speedY = -2;
        }
    }
    return false;
}

bool Octopus::move(int x, int y)
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

Octopus::~Octopus()
{

}
