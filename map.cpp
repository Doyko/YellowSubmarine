#include "map.h"

Tile::Tile(bool b, sf::Texture* t, Hitbox& hb, int x, int y, int w, int h)
:
    tangible(b),
    sprite(new sf::Sprite(*t, sf::IntRect(x, y, w, h))),
    hitbox(new Hitbox(hb, x, y, w, h))
{
}

Map::Map(std::string name, sf::Texture* t, Hitbox& hb)
{
    int** m = readMap(name, t, hb);
    tileMap = new Tile**[nbTileY];
    for(int i = 0; i < nbTileY; i++)
    {
        tileMap[i] = new Tile*[nbTileX];
        for(int j = 0; j < nbTileX; j++)
        {
            if(m[i][j] == 0)
                tileMap[i][j] = NULL;
            else
                tileMap[i][j] = tileList[getIdTile(m, i, j)];
        }
    }
    for(int i = 0; i < nbTileY; i++)
        delete[] m[i];
    delete[] m;
}

int** Map::readMap(std::string name, sf::Texture* t, Hitbox& hb)
{
    std::ifstream ifs(name);
    int nbTile;
    int tangible;

    ifs >> nbTile;
    if(nbTile < 16)
    {
        std::cout << "Error for loading the file " << name << " !" << '\n';
        exit(1);
    }
    for(int i = 0; i < nbTile; i++)
    {
        ifs >> tangible;
        if(tangible == 0)
            tileList.push_back(new Tile(false, t, hb, i * TILE_WIDTH, 0, TILE_WIDTH, TILE_HEIGHT));
        else
            tileList.push_back(new Tile(true, t, hb, i * TILE_WIDTH, 0, TILE_WIDTH, TILE_HEIGHT));
    }
    ifs >> nbTileX;
    ifs >> nbTileY;
    int** m = new int*[nbTileY];
    for(int i = 0; i < nbTileY; i++)
    {
        m[i] = new int[nbTileX];
        for(int j = 0; j < nbTileX; j++)
        {
            ifs >> m[i][j];
        }
    }
    ifs.close();
    return m;
}

void Map::draw(sf::RenderWindow &window) const
{
    for(int i = 0; i < nbTileY; i++)
    {
        for(int j = 0; j < nbTileX; j++)
        {
            if(tileMap[i][j] != NULL)
            {
                tileMap[i][j]->sprite->setPosition(sf::Vector2f(j * TILE_WIDTH, i * TILE_HEIGHT));
                window.draw(*(tileMap[i][j]->sprite));
            }
        }
    }
}

int Map::getIdTile(int** m, int i, int j) const
{
    int somme = 0;
    if(i - 1 < 0 || m[i - 1][j] == 1)
        somme += 1;
    if(i + 1 >= nbTileY || m[i + 1][j] == 1)
        somme += 4;
    if(j - 1 < 0 || m[i][j - 1] == 1)
        somme += 8;
    if(j + 1 >= nbTileX || m[i][j + 1] == 1)
        somme += 2;
    return somme;
}
