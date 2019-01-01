#include "projectile.h"

std::vector<Projectile*> Projectile::projectiles;

Projectile::Projectile(int x, int y, sf::IntRect dimention, sf::Vector2f speed)
:
    Entity(x, y, dimention),
    MovableEntity(x, y, dimention),
    TengibleEntity(x, y, dimention)
{
    speedX = speed.x;
    speedY = speed.y;
}

bool Projectile::update()
{
    return move(speedX, speedY);
}

bool Projectile::move(int x, int y)
{
    int moveX = x;
    int moveY = y;
    bool flag = false;

    while(moveX != 0 && hitbox->checkCollision(posX + moveX, posY))
    {
        moveX > 0 ? moveX-- : moveX++;
        flag = true;
    }
    posX = posX + moveX;

    while(moveY != 0 && hitbox->checkCollision(posX, posY + moveY))
    {
        moveY > 0 ? moveY-- : moveY++;
        flag = true;
    }

    posY = posY + moveY;
    sprite->setPosition(posX,posY);
    return flag;
}

Projectile::~Projectile()
{

}

sf::IntRect Torpedo::dimRight = sf::IntRect(0, 37, 25, 7);
sf::IntRect Torpedo::dimLeft = sf::IntRect(0, 44, 25, 7);
sf::Vector2f Torpedo::speedRight = sf::Vector2f(1, 0);
sf::Vector2f Torpedo::speedLeft = sf::Vector2f(-1, 0);
int Torpedo::nbSprite = 4;
int Torpedo::animSpeed = 10;

Torpedo::Torpedo(int x, int y, sf::IntRect dimention, sf::Vector2f speed)
:
    Entity(x, y, dimention),
    Projectile(x, y, dimention, speed)
{
    maxSpeed = 20;
    if(speedX > 0)
        animation = new Animation(&Data::textureEntity, Torpedo::dimRight, Torpedo::nbSprite, Torpedo::animSpeed);
    else
        animation = new Animation(&Data::textureEntity, Torpedo::dimLeft, Torpedo::nbSprite, Torpedo::animSpeed);
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

Torpedo::~Torpedo()
{
    if(speedX > 0)
        Entity::entities.push_back(new Explosion(posX - 41, posY - 48));
    else
        Entity::entities.push_back(new Explosion(posX - 41, posY - 48));
    return;
}

sf::IntRect Explosion::dimension = sf::IntRect(128, 64, 96, 96);
int Explosion::nbSprite = 5;
int Explosion::animSpeed = 5;

Explosion::Explosion(int x, int y)
:
    Entity(x, y, Explosion::dimension),
    TengibleEntity(x, y, Explosion::dimension),
    animation(new Animation(&Data::textureEntity, Explosion::dimension, Explosion::nbSprite, Explosion::animSpeed))
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

sf::IntRect Ink::dimension = sf::IntRect(64, 96, 32, 32);
sf::Vector2f Ink::speed = sf::Vector2f(0, 2);

Ink::Ink(int x, int y)
:
    Entity(x, y, Ink::dimension),
    Projectile(x, y, Ink::dimension, Ink::speed)
{}

Ink::~Ink()
{

}
