#include "player.h"
#include <iostream>
Player::Player(int x, int y, sf::Texture *t, Map* m)
:
    posX(x),
    posY(y),
    map(m)
{
    //std::cout << "constructor Player\n";
    sprite = new sf::Sprite(*t, sf::IntRect(0,0,64,37));
    sprite->setPosition(posX,posY);
    hitbox = new Hitbox("YShitbox.pbm");
}

Player::~Player()
{
    delete sprite;
    delete hitbox;
}

bool Player::move(int x, int y)
{
    int moveX = x, moveY = y;

    while (moveX != 0 && hitbox->checkMapCollision(posX + moveX, posY, map))
        moveX > 0 ? moveX-- : moveX++;

    while (moveY != 0 && hitbox->checkMapCollision(posX, posY + moveY, map))
        moveY > 0 ? moveY-- : moveY++;

    posX = posX + moveX;
    posY = posY + moveY;
    sprite->setPosition(posX,posY);
    return true;
}
