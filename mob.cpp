#include "mob.h"

//-----Mob-----

Mob::Mob(const int x, const int y, const sf::IntRect dimension)
:
    Entity(x, y, dimension),
    MovableEntity(x, y, dimension),
    TangibleEntity(x, y, dimension)
{

}

bool Mob::update()
{
    return true;
}

bool Mob::move(const int x, const int y)
{
    int moveX = x;
    int moveY = y;
    bool flag = false;

    while(moveX != 0
        && (hitbox->checkCollision(posX + moveX, posY)
        || hitbox->checkCollision(posX + moveX, posY, Data::explosable)))
    {
        moveX > 0 ? moveX-- : moveX++;
        speedX = 0;
        flag = true;
    }
    posX = posX + moveX;

    while(moveY != 0
        && (hitbox->checkCollision(posX, posY + moveY)
        || hitbox->checkCollision(posX, posY + moveY, Data::explosable)))
    {
        moveY > 0 ? moveY-- : moveY++;
        speedY = 0;
        flag = true;
    }

    posY = posY + moveY;
    sprite->setPosition(posX, posY);
    return flag;
}

//-----Octopus-----

sf::IntRect Octopus::dimension = sf::IntRect(96, 64, 32, 32);
sf::IntRect Octopus::dimSpriteUp = sf::IntRect(96, 96, 32, 32);
sf::IntRect Octopus::dimSpriteDown = sf::IntRect(96, 64, 32, 32);

Octopus::Octopus(const int x, const int y)
:
    Entity(x, y, Octopus::dimension),
    Mob(x, y, Octopus::dimension),
    state(down),
    tick(100)
{
    spriteUp = new sf::Sprite(Data::textureEntity, Octopus::dimSpriteUp);
    spriteDown = sprite;
    speedY = 1;
}

Octopus::~Octopus()
{
    delete spriteUp;
    delete spriteDown;
    sprite = NULL;
}

bool Octopus::update()
{
    if(checkCollision(Data::player))
    {
        if(Data::player->getLife() != 0)
            Data::player->addLife(-1);
    }

    if(state == down)
    {
        tick--;
        if(move(speedX, speedY) || tick == 0)
        {
            state = up;
            tick = 30;
            speedY = -5;
            sprite = spriteUp;
            sprite->setPosition(posX, posY);
            Data::effects.push_back(new Ink(posX, posY + 32));
        }
    }
    else
    {
        tick--;
        if(move(speedX, speedY) || tick == 0)
        {
            state = down;
            tick = 110;
            speedY = 1;
            sprite = spriteDown;
            sprite->setPosition(posX, posY);
        }
        else
        {
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

//-----Mine-----

sf::IntRect Mine::dimension = sf::IntRect(32,64,32,64);

Mine::Mine(const int x, const int y)
:
    Entity(x, y, Mine::dimension),
    Mob(x, y, Mine::dimension),
    center(y),
    tick(10)
{
    speedY = 2;
}

Mine::~Mine()
{

}

void Mine::destroy()
{
    Data::effects.push_back(new Explosion(posX - 32, posY - 32));
    delete this;
}

bool Mine::update()
{
    if(checkCollision(Data::player))
        return true;
    tick--;
    if(tick == 0)
    {
        tick = 20;
        if(posY > center)
            speedY--;
        else
            speedY++;
        move(0, speedY);
    }
    return false;
}

//-----Shark-----

sf::IntRect Shark::dimension = sf::IntRect(0, 224, 64, 32);
sf::IntRect Shark::animRight = sf::IntRect(0, 224, 64, 32);
sf::IntRect Shark::animLeft = sf::IntRect(256, 224, 64, 32);
int Shark::nbSprite = 4;
int Shark::animSpeed = 12;

Shark::Shark(const int x, const int y)
:
    Entity(x, y, Shark::dimension),
    Mob(x, y, Shark::dimension)
{
    delete sprite;
    maxSpeed = 12;
    animations[int(AnimationIndex::moveRight)] = new Animation(&Data::textureEntity, Shark::animRight, Shark::nbSprite, Shark::animSpeed);
    animations[int(AnimationIndex::moveLeft)] = new Animation(&Data::textureEntity, Shark::animLeft, Shark::nbSprite, Shark::animSpeed);
    sprite = animations[int(currentAnimation)]->currentSprite;
}

Shark::~Shark()
{
    for(int i = 0; i < int(AnimationIndex::count); i++)
    {
        delete animations[i];
    }
    sprite = NULL;
}

void Shark::destroy()
{
    Data::effects.push_back(new Corpse(posX, posY, Corpse::shark));
    delete this;
}

bool Shark::update()
{
    if(checkCollision(Data::player))
    {
        if(Data::player->getLife() != 0)
            Data::player->addLife(-1);
    }

    if(Data::player->posX > posX)
    {
        if(speedX < maxSpeed)
            speedX++;
        currentAnimation = AnimationIndex::moveRight;
    }
    else
    {
        if(speedX > -maxSpeed)
            speedX--;
        currentAnimation = AnimationIndex::moveLeft;
    }

    if(Data::player->posY > posY)
    {
        if(speedY < maxSpeed)
            speedY++;
    }
    else
    {
        if(speedY > -maxSpeed)
            speedY--;
    }

    animations[int(currentAnimation)]->update();
    sprite = animations[int(currentAnimation)]->currentSprite;

    move(speedX/4,speedY/4);
    return false;
}

//-----Jellyfish-----
sf::IntRect Jellyfish::dimension = sf::IntRect(192, 160, 32, 64);
int Jellyfish::nbSprite = 4;
int Jellyfish::animSpeed = 10;

Jellyfish::Jellyfish(const int x, const int y)
:
    Entity(x, y, Jellyfish::dimension),
    Mob(x, y, Jellyfish::dimension),
    tick(100)
{
    delete sprite;
    animation = new Animation(&Data::textureEntity, Jellyfish::dimension, Jellyfish::nbSprite, Jellyfish::animSpeed);
    animation->setPosition(x, y);
    sprite = animation->currentSprite;
}

Jellyfish::~Jellyfish()
{
    delete animation;
    sprite = NULL;
}

bool Jellyfish::update()
{
    tick--;
    if(tick < 0)
    {
        if(animation->update())
        {
            tick = 100;
        }
        sprite = animation->currentSprite;
        sprite->setPosition(posX, posY);
    }

    if(tick <= -30)
    {
        move(0,-1);
    }
    else if(tick % 14 == 0)
    {
        move(0,1);
    }

    if(checkCollision(Data::player))
        Data::player->addLife(-1);

    return false;
}
