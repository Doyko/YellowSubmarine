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
        flag = true;
    }
    posX = posX + moveX;

    while(moveY != 0
        && (hitbox->checkCollision(posX, posY + moveY)
        || hitbox->checkCollision(posX, posY + moveY, Data::explosable)))
    {
        moveY > 0 ? moveY-- : moveY++;
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
    int d;
    if(checkCollision(Data::player))
    {
        if(Data::player->getLife() != 0)
            Data::player->addLife(-1);
    }

    if(state == down)
    {
        tick--;
        if(tick == 0)
        {
            state = up;
            tick = 30;
            speedY = -5;
            sprite = spriteUp;
            Data::effects.push_back(new Ink(posX, posY + 32));

            d = (Data::player->posX - posX)*(Data::player->posX - posX) +
                (Data::player->posY - posY)*(Data::player->posY - posY);
            if(d < RADIUS)
                Data::soundMap["sound/octopus.wav"]->play();
        }
    }
    else
    {
        tick--;
        if(tick == 0)
        {
            state = down;
            tick = 110;
            speedY = 1;
            sprite = spriteDown;
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

    move(speedX, speedY);

    return false;
}

void Octopus::destroy()
{
    Data::effects.push_back(new Corpse(posX, posY, Corpse::octopus));
    delete this;
}

//-----Mine-----

sf::IntRect Mine::dimension = sf::IntRect(32,64,32,64);

Mine::Mine(const int x, const int y)
:
    Entity(x, y, Mine::dimension),
    Mob(x, y, Mine::dimension),
    tick(1),
    dir(1)
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
    if(tick % 50 == 0)
        move(0, dir);

    if(tick == 0)
    {
        tick = 200;
        dir = -dir;
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
    animations[int(AnimationIndex::moveRight)]->setPosition(x, y);
    animations[int(AnimationIndex::moveLeft)]->setPosition(x, y);
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
    int d = (Data::player->posX - posX)*(Data::player->posX - posX) +
        (Data::player->posY - posY)*(Data::player->posY - posY);

    if(d > RADIUS)
        return false;

    if(checkCollision(Data::player))
    {
        if(Data::player->getLife() != 0)
            Data::player->addLife(-1);
        if(Data::soundMap["sound/bite.wav"]->getStatus() != sf::SoundSource::Status::Playing)
            Data::soundMap["sound/bite.wav"]->play();
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
    tick(rand()%21 + 90)
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
            tick = rand()%21 + 90;
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
    {
        Data::player->addLife(-1);
        if(Data::soundMap["sound/squishy.wav"]->getStatus() != sf::SoundSource::Status::Playing)
            Data::soundMap["sound/squishy.wav"]->play();
    }
    return false;
}

void Jellyfish::destroy()
{
    Data::effects.push_back(new Corpse(posX, posY, Corpse::jellyfish));
    delete this;
}

//-----Drone-----

sf::IntRect Drone::dimension = sf::IntRect(352, 160, 32, 32);

Drone::Drone(const int x, const int y)
:
    Entity(x, y, dimension),
    Mob(x, y, dimension),
    tick(rand() % 21 + 90),
    Smax(10)
{
    sprite->setOrigin(16,16);
    sprite->setPosition(posX + 16, posY + 16);
}

Drone::~Drone(){}

bool Drone::update()
{
    int dx = Data::player->posX - posX + 16;
    int dy = Data::player->posY - posY + 5;

    if(dx*dx + dy*dy > RADIUS)
        return false;

    preShoot(dx, dy);
    setRotation(dx, dy);

    if(tick > 0)
        tick--;
    else
    {
        tick = rand() % 21 + 90;
        shoot(dx, dy);
    }

    return false;
}

void Drone::setRotation(int x, int y)
{
    int a;

    if(x > y && x > -y)
    {
        float t = (float)y / (float)x;
        a =  45*t;
    }
    else if(y > x && y > -x)
    {
        float t = (float)x / (float)y;
        a = -45*t + 90;
    }
    else if(x < y && x < -y)
    {
        float t = (float)y / (float)x;
        a =  45*t + 180;
    }
    else if(y < x && y < -x)
    {
        float t = (float)x / (float)y;
        a = -45*t + 270;
    }
    else
        return;

    sprite->setRotation(a);
}

void Drone::shoot(int x, int y)
{
    int vx, vy;

    if(x > y && x > -y)
    {
        vx = Smax;
        vy = (2*Smax*y + x) / (2*x);
    }
    else if(y > x && y > -x)
    {
        vx = Smax * x / y;
        vy = Smax;
    }
    else if(x < y && x < -y)
    {
        vx = -Smax;
        vy = -Smax * y / x;
    }
    else if(y < x && y < -x)
    {
        vx = -Smax * x / y;
        vy = -Smax;
    }

    Data::effects.push_back(new Lazer(posX + 16 + 3*vx, posY + 16 + 3*vy, sf::Vector2f(vx, vy)));
    Data::soundMap["sound/laser.wav"]->play();
}

void Drone::preShoot(int &x, int &y)
{
    int tx, ty, t;

    if(x > 0)
        tx = x / (4*Smax - Data::player->getSpeedX());
    else
        tx = -x / (4*Smax + Data::player->getSpeedX());

    if(y > 0)
        ty = y / (4*Smax - Data::player->getSpeedY());
    else
        ty = -y / (4*Smax + Data::player->getSpeedY());

    t = tx > ty ? tx : ty;
    x += Data::player->getSpeedX() * t;
    y += Data::player->getSpeedY() * t;
}
