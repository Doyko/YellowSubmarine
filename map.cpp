#include "map.h"

Tile::Tile(bool b, sf::Texture* t, int x, int y, int w, int h)
:
    tangible(b)
{
    sprite = new sf::Sprite(*t, sf::IntRect(x, y, w, h));
}

Map::Map(std::string name, sf::Texture* t)
{
    int** m = readMap(name, t);
    tileMap = new Tile**[nbTileY];
    for(int i = 0; i < nbTileY; i++)
    {
        tileMap[i] = new Tile*[nbTileX];
        for(int j = 0; j < nbTileX; j++)
        {
            if(m[i][j] == 0)
                tileMap[i][j] = NULL;
            else
                tileMap[i][j] = tileList[0];
        }
    }
}

int** Map::readMap(std::string name, sf::Texture* t)
{
    std::ifstream ifs(name);
    int nbTile;
    int tangible;

    ifs >> nbTile;
    for(int i = 0; i < nbTile; i++)
    {
        ifs >> tangible;
        if(tangible == 0)
            tileList.push_back(new Tile(false, t, i * TILE_WIDTH, 0, TILE_WIDTH, TILE_HEIGHT));
        else
            tileList.push_back(new Tile(true, t, i * TILE_WIDTH, 0, TILE_WIDTH, TILE_HEIGHT));
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
