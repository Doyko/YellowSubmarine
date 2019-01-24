#include "hitbox.h"

Hitbox::Hitbox()
:
    left(0),
    top(0),
    width(0),
    height(0),
    tab(NULL)
{}

Hitbox::Hitbox(const int w, const int h, char** t)
:
    left(0),
    top(0),
    width(w),
    height(h),
    tab(t)
{}

Hitbox::Hitbox(const std::string fileName)
:
    left(0),
    top(0),
    width(0),
    height(0),
    tab(NULL)
{
    std::ifstream ifs(fileName);
    if(!ifs)
    {
        std::cout << "Can't open \"" << fileName << "\"." << std::endl;
        exit(0);
    }

    char buffer[256];
    ifs >> buffer;

    if (strcmp(buffer, "P1"))
    {
        std::cout << "Error reading hitbox in \"" << fileName << "\" : wrong file format" << std::endl;
        exit(1);
    }

    ifs >> buffer;
    while(buffer[0] == '#')
    {
        ifs.getline(buffer, 256);
        ifs >> buffer;
    }
    width = atoi(buffer);
    ifs >> height;

    tab = new char*[height];

    for(int y = 0; y < height; y++)
    {
        tab[y] = new char[width];
        for(int x = 0; x < width; x++)
        {
            ifs >> tab[y][x];
        }
    }
    ifs.close();
}

Hitbox::Hitbox(const Hitbox& hb, const int x, const int y, const int w, const int h)
:
    left(0),
    top(0),
    width(w),
    height(h),
    tab(NULL)
{
    tab = new char*[height];

    for(int i = 0; i < height; i++)
    {
        tab[i] = new char[width];
        for(int j = 0; j < width; j++)
        {
            tab[i][j] = hb(j + x, i + y);
        }
    }
}

Hitbox::Hitbox(const Hitbox& hb, const sf::IntRect dimension)
:
    left(0),
    top(0),
    width(dimension.width),
    height(dimension.height),
    tab(NULL)
{
    tab = new char*[height];

    for(int i = 0; i < height; i++)
    {
        tab[i] = new char[width];
        for(int j = 0; j < width; j++)
        {
            tab[i][j] = hb(j + dimension.left, i + dimension.top);
        }
    }
}

Hitbox::~Hitbox()
{
    for(int y = 0; y < height; y++)
    {
        delete[] tab[y];
    }
    delete[] tab;
}

int Hitbox::getLeft() const
{
    return left;
}

int Hitbox::getTop() const
{
    return top;
}

int Hitbox::getWidth() const
{
    return width;
}

int Hitbox::getHeight() const
{
    return height;
}

void Hitbox::setPosition(const int x, const int y)
{
    left = x;
    top = y;
}

char Hitbox::operator()(const int x, const int y) const
{
    if(x >= 0 && x < width && y >= 0 && y < height)
        return tab[y][x];
    else
        return '\0';
}

bool Hitbox::checkCollision(const int x, const int y, const Hitbox* hb, const int hbX, const int hbY) const
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

    for(int i = 0; i < InterWidth; i++)
    {
        for(int j = 0; j < InterHeight; j++)
        {
            if((*this)(i + OffsetX, j + OffsetY) == '1' && (*hb)(i + OffsetHBX, j + OffsetHBY) == '1')
                return true;
        }
    }
    return false;
}

bool Hitbox::checkCollision(const int x, const int y, const std::vector<TangibleEntity*> v)
{
    for(auto & it : v)
    {
        if(checkCollision(x,y, it->hitbox, it->posX, it->posY))
            return true;
    }
    return false;
}

bool Hitbox::checkCollision(const int x, const int y) const
{
    int xmin = x;
    int xmax = x + width - 1;
    int ymin = y;
    int ymax = y + height - 1;

    if(xmin < 0 || xmax >= Data::map->getNbTileX() * TILE_WIDTH)
        return true;

    if(ymin < 0 || ymax >= Data::map->getNbTileY() * TILE_HEIGHT)
        return true;

    for(int i = xmin/TILE_WIDTH; i <= xmax / TILE_WIDTH; i++)
    {
        for(int j = ymin / TILE_HEIGHT; j <= ymax / TILE_HEIGHT; j++)
        {
            if((*Data::map)(j, i) != NULL && (*Data::map)(j, i)->getTangibility())
            {
                if(checkCollision(x, y, (*Data::map)(j, i)->hitbox, i * 32, j * 32))
                {
                    return true;
                }
            }
        }
    }
    return false;
}

bool Hitbox::checkCollision(const int x, const int y, const Tile* t, const int xTile, const int yTile) const
{
    int xTileRelatif = xTile * TILE_WIDTH - x;
    int yTileRelatif = yTile * TILE_HEIGHT - y;

    int xmin = 0 > xTileRelatif ? 0 : xTileRelatif;
    int ymin = 0 > yTileRelatif ? 0 : yTileRelatif;
    int xmax = width < xTileRelatif + TILE_WIDTH ? width : xTileRelatif + TILE_WIDTH;
    int ymax = height < yTileRelatif + TILE_HEIGHT ? height : yTileRelatif + TILE_HEIGHT;

    for (int i = xmin; i < xmax; i++)
    {
        for (int j = ymin; j < ymax; j++)
        {
            if ((*this)(i, j) == '1')
            {
                return true;
            }
        }
    }
    return false;
}
