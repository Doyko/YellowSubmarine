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
    bool isEmpty;

    do {
        isEmpty = true;
        for(int j = 0; j < HEIGHT; j++){
            for(int i = 0; i < WIDTH; i++){
                if(hitbox->tab[j][i] == '1' && map->tileMap[(posY + j)/32][(posX + moveX + i)/32] != NULL){
                    isEmpty = false;
                    moveX > 0 ? moveX-- : moveX++;
                    break;
                }
            }
            if (!isEmpty)
                break;
        }

    } while(!isEmpty && moveX != 0);

    do {
        isEmpty = true;
        for(int i = 0; i < WIDTH; i++){
            for(int j = 0; j < HEIGHT; j++){
                if(hitbox->tab[j][i] == '1' && map->tileMap[(posY + moveY + j)/32][(posX + i)/32] != NULL)
                {
                    isEmpty = false;
                    moveY > 0 ? moveY-- : moveY++;
                    break;
                }
            }
            if (!isEmpty)
                break;
        }

    } while(!isEmpty && moveY != 0);


    posX = posX + moveX;
    posY = posY + moveY;
    sprite->setPosition(posX,posY);
    return true;
}
