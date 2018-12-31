#include "player.h"
#include <iostream>

Player::Player(int x, int y, Map* m, sf::IntRect dimention)
:
    Entity(x, y, m, dimention),
    MovableEntity(x, y, m, dimention),
    TengibleEntity(x, y, m, dimention),
    life(MAXLIFE),
    shootCD(0)
{
    animations[int(AnimationIndex::moveRight)] = Animation(&Texture::textureEntity, sf::IntRect(0, 0, 64, 37), 4, 10);
    animations[int(AnimationIndex::moveLeft)] = Animation(&Texture::textureEntity, sf::IntRect(256, 0, 64, 37), 4, 10);
    //std::cout << "constructor Player" << std::endl;
}

Player::~Player()
{
    hitbox->~Hitbox();
}

bool Player::update()
{
    if(speedX > 0)
    {
        changeSpeed(-DECCELERATION,0);
        currentAnimation = AnimationIndex::moveRight;
    }
    else if(speedX < 0)
    {
        changeSpeed(DECCELERATION,0);
        currentAnimation = AnimationIndex::moveLeft;
    }
    animations[int(currentAnimation)].update();
    sprite = animations[int(currentAnimation)].currentSprite;

    if(speedY > 0)
        changeSpeed(0,-DECCELERATION);
    else if(speedY < 0)
        changeSpeed(0,DECCELERATION);


    move(speedX/4, speedY/4);

    setRotation();

    if(shootCD)
        shootCD--;

    return true;
}

bool Player::move(int x, int y)
{
    int moveX = x;
    int moveY = y;

    while(moveX != 0 && hitbox->checkCollision(posX + moveX, posY, map))
    {
        moveX > 0 ? moveX-- : moveX++;
        speedX = 0;
    }

    posX = posX + moveX;

    while(moveY != 0 && hitbox->checkCollision(posX, posY + moveY, map))
    {
        moveY > 0 ? moveY-- : moveY++;
        speedY = 0;
    }

    posY = posY + moveY;
    sprite->setPosition(posX,posY);
    return true;
}

void Player::shoot(std::vector<Projectile*>& projectiles)
{
    if(shootCD != 0)
        return;

    shootCD = COOLDOWN;
    float rot = sprite->getRotation();
    if(rot > 180)
        rot = rot - 360;
    if(currentAnimation == AnimationIndex::moveRight)
        projectiles.push_back(new Torpedo(posX + sprite->getTextureRect().width, posY + sprite->getTextureRect().height / 2 + 3 + rot, map, sf::IntRect(0, 37, 25, 7), sf::Vector2f(1, 0)));
    else
        projectiles.push_back(new Torpedo(posX - 25, posY + sprite->getTextureRect().height / 2 + 3, map, sf::IntRect(0, 44, 25, 7), sf::Vector2f(-1, 0)));
}

void Player::setRotation()
{
    if(speedY > 0)
    {
        if(currentAnimation == AnimationIndex::moveRight)
            sprite->setRotation(7 * (float(speedY) / maxSpeed));
        else
            sprite->setRotation(-7 * (float(speedY) / maxSpeed));
    }
    else if(speedY < 0)
    {
        if(currentAnimation == AnimationIndex::moveLeft)
            sprite->setRotation(-7 * (float(speedY) / maxSpeed));
        else
            sprite->setRotation(7 * (float(speedY) / maxSpeed));
    }
    else
        sprite->setRotation(0);
}
