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

    bool checkMapCollision(int x, int y, Map* m); //return true if there is collision
    bool checkTileCollision(int x, int y, Tile* t, int xTile, int yTile); //return true if there is collision

private :
    int width;
    int height;
    char** tab;
};
