#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include <cstring>
#include <string>

class Hitbox
{

public:
    Hitbox();
    Hitbox(const int w, const int h, char** t);
    Hitbox(const std::string fileName);
    Hitbox(const Hitbox& hb, const int x, const int y, const int w, const int h);
    Hitbox(const Hitbox& hb, const sf::IntRect dimension);
    ~Hitbox();

    int getLeft() const;
    int getTop() const;
    int getWidth() const;
    int getHeight() const;
    void setPosition(const int x, const int y);
    char operator()(const int x, const int y) const;
    bool checkCollision(const Hitbox* hb) const;

private :
    int left;
    int top;
    int width;
    int height;
    char** tab;
};
