#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include <fstream>
#include <iostream>

#include "hitbox.h"

#define TILE_WIDTH 32
#define TILE_HEIGHT 32

class Hitbox;

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

    Map(std::string name, sf::Texture* t, Hitbox& hb);
    int** readMap(std::string name, sf::Texture* t, Hitbox& hb);
    void draw(sf::RenderWindow &window) const;
    int getIdTile(int** m, int i, int j) const;

    int nbTileX;
    int nbTileY;
    std::vector<Tile*> tileList;
    Tile*** tileMap;
    
};
