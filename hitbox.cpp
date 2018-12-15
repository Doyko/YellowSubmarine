#include "hitbox.h"

Hitbox::Hitbox():
    width(0),
    height(0),
    tab(NULL){}

Hitbox::Hitbox(int w, int h, char** t):
    width(w),
    height(h),
    tab(t){}

Hitbox::Hitbox(const char* fileName){

    std::ifstream ifs(fileName);
    std::string buffer;
    ifs >> buffer;

    if (buffer != "HB")
    {
        std::cout << "Error reading hitbox : wrong file format" << std::endl;
        exit(1);
    }

    ifs >> width;
    ifs >> height;

    tab = new char*[height];

    for(int y = 0 ; y < height ; y++){
        tab[y] = new char[width];
        for(int x = 0 ; x < width ; x++){
            ifs >> tab[y][x];
            //std::cout << (char)(tab[y][x] -'0' +' ');
        }
        //std::cout << std::endl;
    }
    ifs.close();
}

Hitbox::~Hitbox()
{
    for(int y = 0 ; y < height ; y++){
        delete tab[y];
    }
    delete tab;
}
