#include "entity.h"
#include <iostream>

Entity::Entity(int x, int y, Map* m, sf::Texture *t, sf::IntRect dimention)
:
    posX(x),
    posY(y),
    map(m)
{
    sprite = new sf::Sprite(*t, dimention);
    sprite->setPosition(posX,posY);
    //std::cout << "constructor Entity" << std::endl;
}

Entity::~Entity()
{
    delete sprite;
}

MovableEntity::MovableEntity(int x, int y, Map* m, sf::Texture *t, sf::IntRect dimention):
    Entity(x, y, m, t, dimention),
    speedX(0),
    speedY(0),
    maxSpeed(20)
{
    //std::cout << "constructor MovableEntity" << std::endl;
}

void MovableEntity::changeSpeed(float x, float y)
{
    speedX += x;
    speedY += y;

    if(speedX > maxSpeed)
        speedX = maxSpeed;
    else if(speedX < -maxSpeed)
        speedX = -maxSpeed;

    if(speedY > maxSpeed)
        speedY = maxSpeed;
    else if(speedY < -maxSpeed)
        speedY = -maxSpeed;
}

TengibleEntity::TengibleEntity(int x, int y, Map* m, sf::Texture *t, sf::IntRect dimention, Hitbox* hb):
    Entity(x, y, m, t, dimention),
    hitbox(hb)
{
    //std::cout << "constructor TengibleEntity" << std::endl;
}

TengibleEntity::TengibleEntity(int x, int y, Map* m, Hitbox& hb, sf::Texture *t, sf::IntRect dimention):
    Entity(x, y, m, t, dimention),
    hitbox(new Hitbox(hb, dimention))
{}

bool TengibleEntity::checkCollision(TengibleEntity* te)
{
    return hitbox->checkCollision(posX, posY, te->hitbox, te->posX, te->posY);
}

bool TengibleEntity::checkCollision(Map* m)
{
    return hitbox->checkCollision(posX, posY, m);
}
