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

bool Hitbox::checkCollision(const Hitbox* hb) const
{
    //find the intercection of the two hitbox
    int xmin = left > hb->getLeft() ? left : hb->getLeft();
    int xmax = left + width < hb->getLeft() + hb->getWidth() ? left + width : hb->getLeft() + hb->getWidth();
    int ymin = top > hb->getTop() ? top : hb->getTop();
    int ymax = top + height < hb->getTop() + hb->getHeight() ? top + height : hb->getTop() + hb->getHeight();

    int InterWidth = xmax - xmin;
    int InterHeight = ymax - ymin;

    int OffsetX = xmin - left;
    int OffsetY = ymin - top;
    int OffsetHBX = xmin - hb->getLeft();
    int OffsetHBY = ymin - hb->getTop();

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
