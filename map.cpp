#include "map.h"

Tile::Tile(bool b, sf::Texture* t, int x, int y, int w, int h)
:
    tangible(b)
{
    sprite = new sf::Sprite(*t, sf::IntRect(x, y, w, y));
}

Map::Map(std::string name)
{
    int m = readMap(name);
}

int Map::readMap(std::string name)
{
    std::ifstream ifs(name);
    int nbTile;
    int tangible;

    ifs >> nbTile;
    for(int i = 0; i < nbTile; i++)
    {
        ifs >> tangible;
        if(tangible == 0)
            tileList.push_back(new Tile(false, i * TILE_WIDTH, 0, TILE_WIDTH, TILE_HEIGHT));
        else
            tileList.push_back(new Tile(true, i * TILE_WIDTH, 0, TILE_WIDTH, TILE_HEIGHT));
    }
    ifs >> nbTileX;
    ifs >> nbTileY;
    return 0;
}
