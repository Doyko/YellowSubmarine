#pragma once
#include <SFML/Graphics.hpp>
#include "map.h"
#include "hitbox.h"
#include "entity.h"

#define TILE_WIDTH 32
#define TILE_HEIGHT 32
#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 720

class Hitbox;
class Map;
class Player;
class Mob;
class Projectile;
class Bonus;

class Data
{

public:

    static void init();
    static void initMap(Map* m);
    static void initPlayer(Player* p);

    static sf::Texture textureEntity;
    static sf::Texture textureTile;
    static sf::Texture textureBG;
    static sf::Texture textureFG;

    static Hitbox* hitboxEntity;
    static Hitbox* hitboxTile;

    static std::vector<Mob*> mobs;
    static std::vector<Projectile*> projectiles;
    static std::vector<Bonus*> bonus;

    static Player* player;

    static Map* map;
};
