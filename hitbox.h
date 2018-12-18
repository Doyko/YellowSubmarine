#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include "map.h"

class Map;
class Tile;

class Hitbox{

public:
    Hitbox();
    Hitbox(int w, int h, char** t);
    Hitbox(const char* fileName);
    Hitbox(Hitbox& hb, int x, int y, int w, int h);
    Hitbox(Hitbox& hb, sf::IntRect dimention);
    ~Hitbox();

    int getWidth();
    int getHeight();
    char operator()(int x, int y);
    virtual bool checkCollision(int x, int y, Hitbox* hb, int hbX, int hbY);
    virtual bool checkCollision(int x, int y, Map* m); //return true if there is collision
    virtual bool checkCollision(int x, int y, Tile* t, int xTile, int yTile); //return true if there is collision

private :
    int width;
    int height;
    char** tab;
};
