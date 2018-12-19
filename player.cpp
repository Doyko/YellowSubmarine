#include "player.h"
#include <iostream>
<<<<<<< HEAD
Player::Player(int x, int y, Map* m, sf::Texture *t, sf::IntRect dimention)
:
    Entity(x, y, m, t, dimention),
    MovableEntity(x, y, m, t, dimention),
    TengibleEntity(x, y, m, t, dimention, new Hitbox("YShitbox.pbm")),
    anim(new Animation(t, dimention, 4, 10))
=======
Player::Player(int x, int y, Map* m, Hitbox& hb, sf::Texture *t, sf::IntRect dimention):
    Entity(x, y, m, t, dimention),
    MovableEntity(x, y, m, t, dimention),
    TengibleEntity(x, y, m, hb, t, dimention)

>>>>>>> ff406d48a6c781df17511f0475bf5d8f59d52f3b
{
    //std::cout << "constructor Player" << std::endl;
}

Player::~Player()
{
    hitbox->~Hitbox();
}

void Player::update()
{
    //std::cout << "speed : " << speedX << speedY << std::endl;

    if(speedX > 0)
        changeSpeed(-DECCELERATION,0);
    else if(speedX < 0)
        changeSpeed(DECCELERATION,0);

    if(speedY > 0)
        changeSpeed(0,-DECCELERATION);
    else if(speedY < 0)
        changeSpeed(0,DECCELERATION);

    move(speedX/4, speedY/4);

    if(anim->update())
        sprite = anim->currentSprite;
}

bool Player::move(int x, int y)
{
    int moveX = x, moveY = y;

    while (moveX != 0 && hitbox->checkCollision(posX + moveX, posY, map))
    {
        moveX > 0 ? moveX-- : moveX++;
        speedX = 0;
    }

    posX = posX + moveX;

    while (moveY != 0 && hitbox->checkCollision(posX, posY + moveY, map))
    {
        moveY > 0 ? moveY-- : moveY++;
        speedY = 0;
    }

    posY = posY + moveY;
    sprite->setPosition(posX,posY);
    return true;
}
