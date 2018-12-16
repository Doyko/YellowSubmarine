#include "hitbox.h"

Hitbox::Hitbox():
    width(0),
    height(0),
    tab(NULL){}

Hitbox::Hitbox(int w, int h, char** t):
    width(w),
    height(h),
    tab(t){}

Hitbox::Hitbox(const char* fileName){

    std::ifstream ifs(fileName);
    std::string buffer;
    ifs >> buffer;

    if (buffer != "HB")
    {
        std::cout << "Error reading hitbox : wrong file format" << std::endl;
        exit(1);
    }

    ifs >> width;
    ifs >> height;

    tab = new char*[height];

    for(int y = 0 ; y < height ; y++){
        tab[y] = new char[width];
        for(int x = 0 ; x < width ; x++){
            ifs >> tab[y][x];
            //std::cout << (char)(tab[y][x] -'0' +' ');
        }
        //std::cout << std::endl;
    }
    ifs.close();
}

Hitbox::~Hitbox()
{
    for(int y = 0 ; y < height ; y++){
        delete tab[y];
    }
    delete tab;
}

bool Hitbox::checkCollision(int x, int y, Map* m)
{
    //std::cout << "check collision" << std::endl;
    int xmin = x;
    int xmax = x + width - 1;
    int ymin = y;
    int ymax = y + height - 1;

    /*std::cout << "xmin = " << xmin/TILE_WIDTH
    << "\txmax = " << xmax/TILE_WIDTH
    << "\tymin = " << ymin/TILE_HEIGHT
    << "\tymax = " << ymax/TILE_HEIGHT << std::endl;*/


    for (int i = xmin/TILE_WIDTH ; i <= xmax/TILE_WIDTH ; i++)
    {
        for (int j = ymin/TILE_HEIGHT ; j <= ymax/TILE_HEIGHT ; j++)
        {
            if (m->tileMap[j][i] != NULL && m->tileMap[j][i]->tangible)
            {
                //std::cout << "collision map" << i << j << std::endl;
                if(checkCollision(x, y, m->tileMap[j][i], i, j))
                {
                    return true;
                }
            }
        }
    }
    return false;
}

bool Hitbox::checkCollision(int x, int y, Tile* t, int xTile, int yTile)
{
    int xTileRelatif = xTile * TILE_WIDTH - x;
    int yTileRelatif = yTile * TILE_HEIGHT - y;

    //std::cout << "xTileRelatif = " << xTileRelatif
    //<< "\tyTileRelatif = " << yTileRelatif << std::endl;

    int xmin = 0 > xTileRelatif ? 0 : xTileRelatif;
    int ymin = 0 > yTileRelatif ? 0 : yTileRelatif;
    int xmax = width < xTileRelatif + TILE_WIDTH ? width : xTileRelatif + TILE_WIDTH;
    int ymax = height < yTileRelatif + TILE_HEIGHT ? height : yTileRelatif + TILE_HEIGHT;

    /*std::cout << "xmin = " << xmin
    << "\txmax = " << xmax
    << "\tymin = " << ymin
    << "\tymax = " << ymax << std::endl;*/

    for (int i = xmin ; i < xmax ; i++)
    {
        for (int j = ymin ; j < ymax ; j++)
        {
            if (tab[j][i] == '1')
            {
                //std::cout << "collision tile" << std::endl;
                return true;
            }
        }
    }
    return false;
}
