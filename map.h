#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include "data.h"
#include "hitbox.h"
#include "animation.h"

class Hitbox;
class Animation;

class Tile
{

public:

    Tile(const int tang, const int x, const int y, const int w, const int h);
    ~Tile();

    bool getTangibility() const;

    sf::Sprite* sprite;
    Hitbox* hitbox;

private:

    int tangible;
};

class AnimatedTile : public Tile
{

public:

    AnimatedTile(const int tang, const int x, const int y, const int w, const int h, const int nbSprite, const int speed);
    ~AnimatedTile();

    void update();

    Animation* animation;
};

class Map
{

public:

    Map();
    Map(const std::string fileName);
    ~Map();

    void readMap(const std::string fileName);
    void draw(sf::RenderWindow &window, const sf::View &view) const;
    int getNbTileX() const;
    int getNbTileY() const;
    Tile* operator()(const int x, const int y) const;
    void updateAnimatedTiles();

private:

    void initParam();
    void freeMap();
    int** readPGM(const std::string fileName);
    int getIdTileRock(int** m, const int i, const int j) const; // 16 tiles => 0 -> 15
    int getIdTileSand(int** m, const int i, const int j) const; // 54 tiles => 16 -> 69

    int differentTiles;
    std::vector<Tile*> tileList;
    std::vector<AnimatedTile*> animatedTiles;
    Tile*** tileMap;
    int nbTileX;
    int nbTileY;
};
