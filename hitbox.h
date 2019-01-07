#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include "data.h"

class Map;
class Tile;

class Hitbox
{

public:
    Hitbox();
    Hitbox(const int w, const int h, char** t);
    Hitbox(const char* fileName);
    Hitbox(const Hitbox& hb, const int x, const int y, const int w, const int h);
    Hitbox(const Hitbox& hb, const sf::IntRect dimension);
    ~Hitbox();

    int getWidth() const;
    int getHeight() const;
    char operator()(const int x, const int y) const;
    virtual bool checkCollision(const int x, const int y, const Hitbox* hb, const int hbX, const int hbY) const;
    virtual bool checkCollision(const int x, const int y) const;
    virtual bool checkCollision(const int x, const int y, const Tile* t, const int xTile, const int yTile) const;

private :
    int width;
    int height;
    char** tab;
};
