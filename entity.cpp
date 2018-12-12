#include "entity.h"
#include <iostream>
Entity::Entity(int x, int y, int w, int h)
:
    posX(x),
    posY(y),
    width(w),
    height(h)
{}

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
                    move(-1, 0);
                else if(x < 0)
                    move(1, 0);
                if(y > 0)
                    move(0, - 1);
                else if (y < 0)
                    move(0, 1);
                return false;
            }
        }
    }
    posX = posX + x;
    posY = posY + y;
    return true;
}