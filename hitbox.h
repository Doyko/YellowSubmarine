#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include "data.h"

class Map;
class Tile;
class TangibleEntity;

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
    bool checkCollision(const int x, const int y, const Hitbox* hb, const int hbX, const int hbY) const;
    bool checkCollision(const int x, const int y) const;
    bool checkCollision(const int x, const int y, const Tile* t, const int xTile, const int yTile) const;
    bool checkCollision(const int x, const int y, const std::vector<TangibleEntity*> v);

private :
    int width;
    int height;
    char** tab;
};
