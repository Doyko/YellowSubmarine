#include "player.h"
#include <iostream>

sf::IntRect Player::dimension = sf::IntRect(0, 0, 64, 37);
sf::IntRect Player::animRight = sf::IntRect(0, 0, 64, 37);
sf::IntRect Player::animLeft = sf::IntRect(256, 0, 64, 37);
int Player::nbSprite = 4;
int Player::animSpeed = 10;

Player::Player(const int x, const int y)
:
    Entity(x, y, Player::dimension),
    MovableEntity(x, y, Player::dimension),
    TangibleEntity(x, y, Player::dimension),
    life(MAXLIFE),
    shootCD(0),
    buffs(this)
{
    delete sprite;
    animations[int(AnimationIndex::moveRight)] = new Animation(&Data::textureEntity, Player::animRight, Player::nbSprite, Player::animSpeed);
    animations[int(AnimationIndex::moveLeft)] = new Animation(&Data::textureEntity, Player::animLeft, Player::nbSprite, Player::animSpeed);
    sprite = animations[int(currentAnimation)]->currentSprite;
}

Player::~Player()
{
    for(int i = 0; i < int(AnimationIndex::count); i++)
    {
        delete animations[i];
    }
    sprite = NULL;
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
    animations[int(currentAnimation)]->update();
    sprite = animations[int(currentAnimation)]->currentSprite;

    if(speedY > 0)
        changeSpeed(0,-DECCELERATION);
    else if(speedY < 0)
        changeSpeed(0,DECCELERATION);

    move(speedX/4, speedY/4);

    setRotation();

    if(shootCD)
        shootCD--;

    buffs.update();

    return true;
}

bool Player::move(const int x, const int y)
{
    int moveX = x;
    int moveY = y;

    while(moveX != 0
        && (hitbox->checkCollision(posX + moveX, posY)
        || hitbox->checkCollision(posX + moveX, posY, Data::explosable)))
    {
        moveX > 0 ? moveX-- : moveX++;
        speedX = 0;
    }

    posX = posX + moveX;

    while(moveY != 0
        && (hitbox->checkCollision(posX, posY + moveY)
        || hitbox->checkCollision(posX, posY + moveY, Data::explosable)))
    {
        moveY > 0 ? moveY-- : moveY++;
        speedY = 0;
    }

    posY = posY + moveY;
    sprite->setPosition(posX, posY);
    return true;
}

void Player::shoot()
{
    if(shootCD != 0)
        return;

    shootCD = COOLDOWN;
    float rot = sprite->getRotation();
    if(rot > 180)
        rot = rot - 360;
    if(currentAnimation == AnimationIndex::moveRight)
        Data::effects.push_back(new Torpedo(posX + sprite->getTextureRect().width, posY + sprite->getTextureRect().height / 2 + 3 + rot, Torpedo::dimRight, Torpedo::speedRight));
    else
        Data::effects.push_back(new Torpedo(posX - 25, posY + sprite->getTextureRect().height / 2 + 3, Torpedo::dimLeft, Torpedo::speedLeft));
}

void Player::setDirection(const int dir)
{
    sprite = animations[dir]->currentSprite;;
}

int Player::getLife() const
{
    return life;
}

void Player::addLife(const int amout)
{
    if(buffs.is(BuffType::invincibility) == 0)
    {
        life += amout;
        if(amout < 0)
            addBuff(BuffType::invincibility, 50);
    }
}

void Player::addBuff(BuffType b, unsigned int t)
{
    buffs.addBuff(b, t);
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
