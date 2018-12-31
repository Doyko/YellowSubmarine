#pragma once
#include <SFML/Graphics.hpp>
#include "hitbox.h"

class Hitbox;

class Texture
{

public:

    static void init();

    static sf::Texture textureEntity;
    static sf::Texture textureTile;
    static sf::Texture textureBG;
    static sf::Texture textureFG;
    static Hitbox* hitboxEntity;
    static Hitbox* hitboxTile;
};
