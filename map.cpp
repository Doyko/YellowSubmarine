#include "map.h"

Tile::Tile(const int tang, const int x, const int y, const int w, const int h)
:
    sprite(new sf::Sprite(Data::textureTile, sf::IntRect(x, y, w, h))),
    hitbox(new Hitbox(*Data::hitboxTile, x, y, w, h)),
    tangible(tang)
{}

bool Tile::getTangibility() const
{
    return tangible;
}

Tile::~Tile()
{
    if(sprite != NULL)
    {
        delete sprite;
        sprite = NULL;
    }
    delete hitbox;
}

AnimatedTile::AnimatedTile(const int tang, const int x, const int y, const int w, const int h, const int nbSprite, const int speed)
:
    Tile(tang, x, y, w, h),
    animation(new Animation(&Data::textureTile, sf::IntRect(x, y, w, h), nbSprite, speed))
{
    delete sprite;
    sprite = animation->currentSprite;
}

void AnimatedTile::update()
{
    animation->update();
    sprite = animation->currentSprite;
}

AnimatedTile::~AnimatedTile()
{
    delete animation;
    sprite = NULL;
}

Map::Map()
:
    nbTileX(-1),
    nbTileY(-1)
{
    initParam();
}

Map::Map(const std::string fileName)
:
    nbTileX(-1),
    nbTileY(-1)
{
    initParam();
    readMap(fileName);
}

Map::~Map()
{
    freeMap();

    for(size_t i = 0; i < animatedTiles.size(); i++)
    {
        delete animatedTiles[i];
    }

    for(size_t i = 0; i < tileList.size() - animatedTiles.size(); i++)
    {
        delete tileList[i];
    }
}

void Map::readMap(const std::string name)
{
    freeMap();

    int** m = readPGM(name);
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
                case 3:
                    tileMap[i][j] = tileList[70];
                    break;
                case 4:
                    tileMap[i][j] = tileList[71];
                    break;
                default:
                    break;
            }
        }
    }
    for(int i = 0; i < nbTileY; i++)
        delete[] m[i];
    delete[] m;
}

void Map::draw(sf::RenderWindow &window, const sf::View &view) const
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
            if((*this)(i, j) != NULL)
            {
                (*this)(i, j)->sprite->setPosition(sf::Vector2f(j * TILE_WIDTH, i * TILE_HEIGHT));
                window.draw(*(*this)(i, j)->sprite);
            }
        }
    }
}

int Map::getNbTileX() const
{
    return nbTileX;
}

int Map::getNbTileY() const
{
    return nbTileY;
}
Tile* Map::operator()(const int x, const int y) const
{
    return tileMap[x][y];
}

void Map::updateAnimatedTiles()
{
    for(size_t i = 0; i < animatedTiles.size(); i++)
    {
        animatedTiles[i]->update();
    }
}

void Map::initParam()
{
    const std::string fileName = "level/tileParam.txt";
    std::ifstream ifs(fileName);
    if(!ifs)
    {
        std::cout << "Can't open \"" << fileName << "\"." << std::endl;
        exit(0);
    }

    int nbTile;
    int tangible;

    ifs >> differentTiles;
    ifs >> nbTile;
    for(int i = 0; i < nbTile; i++)
    {
        ifs >> tangible;
        tileList.push_back(new Tile(tangible, (i % 20) * TILE_WIDTH, (i / 20) * TILE_HEIGHT, TILE_WIDTH, TILE_HEIGHT));
    }
    int nbAnimatedTile;
    int nbSprite;
    int speed;
    AnimatedTile* at;
    ifs >> nbAnimatedTile;
    for(int i = 0; i < nbAnimatedTile; i++)
    {
        ifs >> tangible;
        ifs >> nbSprite;
        ifs >> speed;
        at = new AnimatedTile(tangible, (nbTile % 20) * TILE_WIDTH, (nbTile / 20) * TILE_HEIGHT, TILE_WIDTH, TILE_HEIGHT, nbSprite, speed);
        tileList.push_back(at);
        animatedTiles.push_back(at);
        nbTile += nbSprite;
    }
}

void Map::freeMap()
{
    if(nbTileY != -1)
    {
        for(int i = 0; i < nbTileY; i++)
            delete[] tileMap[i];
        delete[] tileMap;
    }
}

int Map::getIdTileRock(int** m, const int i, const int j) const
{
    int somme = 0;
    if(i - 1 < 0 || m[i - 1][j] == 1 || m[i - 1][j] == 2)
        somme += 1;
    if(i + 1 >= nbTileY || m[i + 1][j] == 1 || m[i + 1][j] == 2)
        somme += 4;
    if(j - 1 < 0 || m[i][j - 1] == 1 || m[i][j - 1] == 2)
        somme += 8;
    if(j + 1 >= nbTileX || m[i][j + 1] == 1 || m[i][j + 1] == 2)
        somme += 2;
    return somme;
}

int Map::getIdTileSand(int** m, const int i, const int j) const
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

int** Map::readPGM(const std::string fileName)
{
    std::ifstream ifs(fileName);
    if(!ifs)
    {
        std::cout << "Can't open \"" << fileName << "\"." << std::endl;
        exit(0);
    }

    std::string buffer;
    int greyLevel;
    int val;

    ifs >> buffer;

    if (buffer != "P2")
    {
        std::cout << "Error reading map in \"" << fileName << "\" : wrong file format !" << std::endl;
        exit(1);
    }

    ifs >> nbTileX;
    ifs >> nbTileY;
    ifs >> greyLevel;

    int** m = new int*[nbTileY];
    for(int i = 0; i < nbTileY; i++)
    {
        m[i] = new int[nbTileX];
        for(int j = 0; j < nbTileX; j++)
        {
            ifs >> val;
            val = val / ( greyLevel / differentTiles);
            m[i][j] = val;
        }
    }
    ifs.close();
    return m;
}
