#include "player.h"

sf::IntRect Player::dimension = sf::IntRect(0, 0, 64, 37);
std::pair<int,int> Player::center = std::pair<int,int>(32, 19);
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
    animations[int(AnimationIndex::moveRight)]->setOrigin(center.first, center.second);
    animations[int(AnimationIndex::moveLeft)]->setOrigin(center.first, center.second);
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

    setColorSprite();

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
    }

    posX = posX + moveX;

    while(moveY != 0
        && (hitbox->checkCollision(posX, posY + moveY)
        || hitbox->checkCollision(posX, posY + moveY, Data::explosable)))
    {
        moveY > 0 ? moveY-- : moveY++;
    }

    posY = posY + moveY;
    sprite->setPosition(posX + center.first, posY + center.second);
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
    switch(dir)
    {
        case 0:
            currentAnimation = AnimationIndex::moveRight;
            break;
        case 1:
            currentAnimation = AnimationIndex::moveLeft;
            break;
        default:
            currentAnimation = AnimationIndex::moveRight;
            break;
    }
    sprite = animations[int(currentAnimation)]->currentSprite;
}

void Player::setPosition(const int x, const int y)
{
    posX = x;
    posY = y;
    sprite->setPosition(posX, posY);
    sprite->setRotation(0);
}

int Player::getLife() const
{
    return life;
}

void Player::addLife(const int amount)
{
    if(amount >= 0)
    {
        life += amount;
        if(life > MAXLIFE)
            life = MAXLIFE;
    }
    else if(buffs.getDuration(buffType::invincibility) == 0)
    {
        life += amount;
        if(life <= 0)
            Data::state = gameState::death;
        addBuff(buffType::invincibility, 50);
    }
}

void Player::setMaxLife()
{
    life = MAXLIFE;
}

void Player::setMaxSpeed()
{
    maxSpeed = MAXSPEED;
}

int Player::getCD() const
{
    return shootCD;
}

void Player::addCD(const int i)
{
    shootCD += i;
}

void Player::addBuff(const buffType type, const unsigned int t)
{
    buffs.addBuff(type, t);
}

void Player::clearBuff()
{
    buffs.clear();
}

void Player::setRotation()
{
    if(speedY > 0)
    {
        if(currentAnimation == AnimationIndex::moveRight)
            sprite->setRotation(10 * (float(speedY) / maxSpeed));
        else
            sprite->setRotation(-10 * (float(speedY) / maxSpeed));
    }
    else if(speedY < 0)
    {
        if(currentAnimation == AnimationIndex::moveLeft)
            sprite->setRotation(-10 * (float(speedY) / maxSpeed));
        else
            sprite->setRotation(10 * (float(speedY) / maxSpeed));
    }
    else
        sprite->setRotation(0);
}

void Player::setColorSprite()
{
    sprite->setColor(sf::Color(255, 255, 255));
    for(int i = 0; i < buffType::count; i++)
    {
        if(buffs.colorEnable[i] == true && buffs.colorEffect[i] != NULL)
        {
            sprite->setColor(*buffs.colorEffect[i]);
        }
    }
}
