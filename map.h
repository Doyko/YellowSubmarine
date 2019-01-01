#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include "hitbox.h"
#include "animation.h"
#include "data.h"

class Hitbox;
class Animation;

class Tile
{

public:

    Tile(int tang, int x, int y, int w, int h);

    int tangible;
    sf::Sprite* sprite;
    Hitbox* hitbox;
};

class AnimatedTile : public Tile
{

public:

    AnimatedTile(int tang, int x, int y, int w, int h, int nbSprite, int speed);
    void update();

    Animation* animation;
};

class Map
{

public:

    Map(std::string name);
    int** readMap(std::string name);
    void draw(sf::RenderWindow &window, sf::View &view) const;
    int getIdTileRock(int** m, int i, int j) const; // 16 tiles => 0 -> 15
    int getIdTileSand(int** m, int i, int j) const; // 54 tiles => 16 -> 69

    int nbTileX;
    int nbTileY;
    std::vector<Tile*> tileList;
    std::vector<AnimatedTile*> animatedTiles;
    Tile*** tileMap;

};
