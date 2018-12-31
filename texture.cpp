#include "texture.h"

void Texture::init()
{
    if(!Texture::textureEntity.loadFromFile("texture/textureEntity.png"))
        exit(1);

    if(!Texture::textureTile.loadFromFile("texture/textureTile.png"))
        exit(1);

    if(!Texture::textureBG.loadFromFile("texture/textureBG.png"))
        exit(1);

    if(!Texture::textureFG.loadFromFile("texture/textureFG.png"))
        exit(1);

    hitboxEntity = new Hitbox("hitbox/hitboxEntity.pbm");
    hitboxTile = new Hitbox("hitbox/hitboxTile.pbm");
}

sf::Texture Texture::textureEntity;
sf::Texture Texture::textureTile;
sf::Texture Texture::textureBG;
sf::Texture Texture::textureFG;
Hitbox* Texture::hitboxEntity;
Hitbox* Texture::hitboxTile;
