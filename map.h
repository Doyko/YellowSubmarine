#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#define TILE_WIDTH 32
#define TILE_HEIGHT 32

class Tile
{
    public:

    Tile(bool b, sf::Texture* t, int x, int y, int w, int h);

    bool tangible;
    sf::Sprite* sprite;
};

class Map
{
    public:

    Map(std::string name, sf::Texture* t);
    int** readMap(std::string name, sf::Texture* t);
    void draw(sf::RenderWindow &window) const;

    int nbTileX;
    int nbTileY;
    std::vector<Tile*> tileList;
    Tile*** tileMap;
};
