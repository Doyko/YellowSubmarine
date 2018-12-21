#include "map.h"

Tile::Tile(bool b, sf::Texture* t, Hitbox& hb, int x, int y, int w, int h)
:
    tangible(b),
    sprite(new sf::Sprite(*t, sf::IntRect(x, y, w, h))),
    hitbox(new Hitbox(hb, x, y, w, h))
{}

Map::Map(std::string name, sf::Texture* tTile, Hitbox& hbTile, sf::Texture* tEntity, Hitbox& hbEntity)
{
    int** m = readMap(name, tTile, hbTile, tEntity, hbEntity);
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

int** Map::readMap(std::string name, sf::Texture* tTile, Hitbox& hbTile, sf::Texture* tEntity, Hitbox& hbEntity)
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
            tileList.push_back(new Tile(false, tTile, hbTile, (i % 20) * TILE_WIDTH, (i / 20) * TILE_HEIGHT, TILE_WIDTH, TILE_HEIGHT));
        else
            tileList.push_back(new Tile(true, tTile, hbTile, (i % 20) * TILE_WIDTH, (i / 20) * TILE_HEIGHT, TILE_WIDTH, TILE_HEIGHT));
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

    readEntity(ifs, tEntity, hbEntity);

    ifs.close();
    return m;
}

void Map::readEntity(std::ifstream& ifs, sf::Texture* tEntity, Hitbox& hbEntity)
{
  int type;
  int x, y;

  ifs >> type;
  ifs >> x;
  ifs >> y;

  while(!ifs.eof())
  {
    std::cout << type << x << y << std::endl;

    switch(type)
    {
      case 0://heart
        entityList.push_back(new Bonus(x, y, this, hbEntity, tEntity, sf::IntRect(0,64,25,89)));
        break;
      default:
        break;
    }
    ifs >> type;
    ifs >> x;
    ifs >> y;
  }
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
