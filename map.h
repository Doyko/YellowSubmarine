#pragma once
#include "param.h"

class Hitbox;
class InteractiveEntity;

class Tile
{

public:

    Tile(bool b, sf::Texture* t, Hitbox& hb, int x, int y, int w, int h);

    bool tangible;
    sf::Sprite* sprite;
    Hitbox* hitbox;
};

class Map
{

public:

    Map(std::string name, sf::Texture* tTile, Hitbox& hbTile, sf::Texture* tEntity, Hitbox& hbEntity);
    int** readMap(std::string name, sf::Texture* tTile, Hitbox& hbTile, sf::Texture* tEntity, Hitbox& hbEntity);
    void readEntity(std::ifstream& ifs, sf::Texture* tEntity, Hitbox& hbEntity);
    void draw(sf::RenderWindow &window) const;
    int getIdTileRock(int** m, int i, int j) const; // 16 tiles => 0 -> 15
    int getIdTileSand(int** m, int i, int j) const; // 54 tiles => 16 -> 69

    int nbTileX;
    int nbTileY;
    std::vector<Tile*> tileList;
    std::vector<InteractiveEntity*> entityList;
    Tile*** tileMap;

};
