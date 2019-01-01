#include "data.h"

void Data::init()
{
    if(!Data::textureEntity.loadFromFile("texture/textureEntity.png"))
        exit(1);

    if(!Data::textureTile.loadFromFile("texture/textureTile.png"))
        exit(1);

    if(!Data::textureBG.loadFromFile("texture/textureBG.png"))
        exit(1);

    if(!Data::textureFG.loadFromFile("texture/textureFG.png"))
        exit(1);
}

void Data::initMap(Map* m)
{
    map = m;
}

sf::Texture Data::textureEntity;
sf::Texture Data::textureTile;
sf::Texture Data::textureBG;
sf::Texture Data::textureFG;

Hitbox* Data::hitboxEntity = new Hitbox("hitbox/hitboxEntity.pbm");
Hitbox* Data::hitboxTile = new Hitbox("hitbox/hitboxTile.pbm");

Map* Data::map;
