#include "hitbox.h"

Hitbox::Hitbox()
:
    width(0),
    height(0),
    tab(NULL)
{}

Hitbox::Hitbox(int w, int h, char** t):
    width(w),
    height(h),
    tab(t)
{}

Hitbox::Hitbox(const char* fileName)
{
    std::ifstream ifs(fileName);
    std::string buffer;
    ifs >> buffer;

    if (buffer != "P1")
    {
        std::cout << "Error reading hitbox in \"" << fileName << "\" : wrong file format" << std::endl;
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

Hitbox::Hitbox(Hitbox& hb, int x, int y, int w, int h)
:
    width(w),
    height(h)
{
    tab = new char*[height];

    for(int i = 0 ; i < height; i++){
        tab[i] = new char[width];
        for(int j = 0 ; j < width ; j++){
            tab[i][j] = hb(j + x, i + y);
            //std::cout << (char)(tab[y][x] -'0' +' ');
        }
    }
}

Hitbox::Hitbox(Hitbox& hb, sf::IntRect dimention)
:
    width(dimention.width),
    height(dimention.height)
{
    tab = new char*[height];

    for(int i = 0 ; i < height ; i++){
        tab[i] = new char[width];
        for(int j = 0 ; j < width ; j++){
            tab[i][j] = hb(j + dimention.left, i + dimention.top);
            //std::cout << (char)(tab[y][x] -'0' +' ');
        }
    }
}

Hitbox::~Hitbox()
{
    for(int y = 0 ; y < height ; y++){
        delete[] tab[y];
    }
    delete[] tab;
}

int Hitbox::getWidth()
{
    return width;
}

int Hitbox::getHeight()
{
    return height;
}

char Hitbox::operator()(int x, int y)
{
    if(x >= 0 && x < width && y >= 0 && y < height)
        return tab[y][x];
    else
        return '\0';
}

bool Hitbox::checkCollision(int x, int y, Hitbox* hb, int hbX, int hbY)
{
    int xmin = x > hbX ? x : hbX;
    int xmax = x + width < hbX + hb->getWidth() ? x + width : hbX + hb->getWidth();
    int ymin = y > hbY ? y : hbY;
    int ymax = y + height < hbY + hb->getHeight() ? y + height : hbY + hb->getHeight();

    int InterWidth = xmax - xmin;
    int InterHeight = ymax - ymin;

    int OffsetX = xmin - x;
    int OffsetY = ymin - y;
    int OffsetHBX = xmin - hbX;
    int OffsetHBY = ymin - hbY;

    for(int i = 0 ; i < InterWidth ; i++)
    {
        for(int j = 0 ; j < InterHeight ; j++)
        {
            if((*this)(i + OffsetX, j + OffsetY) == '1' && (*hb)(i + OffsetHBX, j + OffsetHBY) == '1')
                return true;
        }
    }

    return false;
}

bool Hitbox::checkCollision(int x, int y)
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


    for(int i = xmin/TILE_WIDTH ; i <= xmax/TILE_WIDTH ; i++)
    {
        for(int j = ymin/TILE_HEIGHT ; j <= ymax/TILE_HEIGHT ; j++)
        {
            if(Data::map->tileMap[j][i] != NULL && Data::map->tileMap[j][i]->tangible)
            {
                //std::cout << "collision map" << i << j << std::endl;
                if(checkCollision(x, y, Data::map->tileMap[j][i]->hitbox, i*32, j*32))
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
            if ((*this)(i, j) == '1')
            {
                //std::cout << "collision tile" << std::endl;
                return true;
            }
        }
    }
    return false;
}
