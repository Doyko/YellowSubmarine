#include <iostream>
#include <fstream>
#include <string>

class Hitbox{

public:
    Hitbox();
    Hitbox(int w, int h, char** t);
    Hitbox(const char* fileName);
    ~Hitbox();

    int width;
    int height;
    char** tab;
};
