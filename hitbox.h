#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include "map.h"

class Hitbox{

public:
    Hitbox();
    Hitbox(int w, int h, char** t);
    Hitbox(const char* fileName);
    ~Hitbox();

    virtual bool checkCollision(int x, int y, Map* m); //return true if there is collision
    virtual bool checkCollision(int x, int y, Tile* t, int xTile, int yTile); //return true if there is collision

private :
    int width;
    int height;
    char** tab;
};
