#include "entity.h"
#include <iostream>
Entity::Entity(int x, int y, int w, int h, sf::Texture *t)
:
    posX(x),
    posY(y),
    width(w),
    height(h)
{
    eSprite = new sf::Sprite(*t, sf::IntRect(0,0,64,37));
    eSprite->setPosition(posX,posY);
    //std::cout << "constructor Entity\n";
}

Entity::~Entity()
{

}

bool Entity::move(int x, int y)
{
    int xmin = (posX + x) / TILE_WIDTH;
    int xmax = (posX + width + x - 1) / TILE_WIDTH;
    int ymin = (posY + y) / TILE_HEIGHT;
    int ymax = (posY + height + y - 1) / TILE_HEIGHT;

    for(int i = xmin; i <= xmax; i++)
    {
        for(int j = ymin; j <= ymax; j++)
        {
            if(map[j][i] == 1)
            {
                if(x > 0)
                    move(x - 1, 0);
                else if(x < 0)
                    move(x + 1, 0);
                if(y > 0)
                    move(0, y - 1);
                else if (y < 0)
                    move(0, y + 1);
                return false;
            }
        }
    }
    posX = posX + x;
    posY = posY + y;
    eSprite->setPosition(posX,posY-12);
    return true;
}
