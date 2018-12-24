#include "map.h"

Tile::Tile(bool b, sf::Texture* t, Hitbox& hb, int x, int y, int w, int h)
:
    tangible(b),
    sprite(new sf::Sprite(*t, sf::IntRect(x, y, w, h))),
    hitbox(new Hitbox(hb, x, y, w, h))
{}

Map::Map(std::string name, sf::Texture* t, Hitbox& hb)
{
    int** m = readMap(name, t, hb);
    tileMap = new Tile**[nbTileY];
    for(int i = 0; i < nbTileY; i++)
    {
        tileMap[i] = new Tile*[nbTileX];
        for(int j = 0; j < nbTileX; j++)
        {
            switch(m[i][j])
            {
                case 0:
                    tileMap[i][j] = NULL;
                    break;
                case 1:
                    tileMap[i][j] = tileList[getIdTileRock(m, i, j)];
                    break;
                case 2:
                    tileMap[i][j] = tileList[getIdTileSand(m, i, j)];
                    break;
                default:
                    tileMap[i][j] = NULL;
                    break;
            }
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
            tileList.push_back(new Tile(false, t, hb, (i % 20) * TILE_WIDTH, (i / 20) * TILE_HEIGHT, TILE_WIDTH, TILE_HEIGHT));
        else
            tileList.push_back(new Tile(true, t, hb, (i % 20) * TILE_WIDTH, (i / 20) * TILE_HEIGHT, TILE_WIDTH, TILE_HEIGHT));
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

void Map::draw(sf::RenderWindow &window, sf::View &view) const
{
    sf::Vector2f center = view.getCenter();
    int minX = (center.x - WINDOW_WIDTH / 2) / TILE_WIDTH;
    int minY = (center.y - WINDOW_HEIGHT / 2) / TILE_HEIGHT;
    int maxX = ((center.x - 1 - WINDOW_WIDTH / 2) + WINDOW_WIDTH) / TILE_WIDTH;
    int maxY = ((center.y - 1 - WINDOW_HEIGHT / 2) + WINDOW_HEIGHT) / TILE_HEIGHT;
    for(int i = minY; i <= maxY; i++)
    {
        for(int j = minX; j <= maxX; j++)
        {
            if(tileMap[i][j] != NULL)
            {
                tileMap[i][j]->sprite->setPosition(sf::Vector2f(j * TILE_WIDTH, i * TILE_HEIGHT));
                window.draw(*(tileMap[i][j]->sprite));
            }
        }
    }
}

int Map::getIdTileRock(int** m, int i, int j) const
{
    int somme = 0;
    if(i - 1 < 0 || m[i - 1][j] != 0)
        somme += 1;
    if(i + 1 >= nbTileY || m[i + 1][j] != 0)
        somme += 4;
    if(j - 1 < 0 || m[i][j - 1] != 0)
        somme += 8;
    if(j + 1 >= nbTileX || m[i][j + 1] != 0)
        somme += 2;
    return somme;
}

int Map::getIdTileSand(int** m, int i, int j) const
{
    int somme = 16;
    if(i + 1 >= nbTileY || m[i + 1][j] == 2)//sand down
        somme += 9;
    else if(m[i + 1][j] == 0)//nothing down => rock
        return getIdTileRock(m, i, j);
    if(j - 1 < 0 || m[i][j - 1] == 2)//sand left
        somme += 6;
    else if(m[i][j - 1] == 1)//rock left
        somme += 3;
    if(j + 1 >= nbTileX || m[i][j + 1] == 2)// sand right
        somme += 2;
    else if(m[i][j + 1] == 1)// rock right
        somme += 1;
    if(i - 1 < 0 || m[i - 1][j] == 2)//sand up
        somme += 36;
    else if(m[i - 1][j] == 1)// rock up
        somme += 18;
    return somme;
}
