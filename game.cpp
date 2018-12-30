#include "game.h"

Game::Game(std::string name)
:
    hitboxEntity(Hitbox("hitbox/hitboxEntity.pbm")),
    hitboxTile(Hitbox("hitbox/hitboxTile.pbm")),
    map(new Map("level.txt", &textureTile, hitboxTile)),
    player(new Player(128, 32, map, hitboxEntity, &textureEntity, sf::IntRect(0,0,64,37)))
{
    srand(time(NULL));
    window.create(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Yellow Submarine");
    window.setVerticalSyncEnabled(true);
    view.reset(sf::FloatRect(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2, WINDOW_WIDTH, WINDOW_HEIGHT));
    //settings.antialiasingLevel = 8;

    if(!textureEntity.loadFromFile("texture/textureEntity.png"))
        exit(1);

    if(!textureTile.loadFromFile("texture/textureTile.png"))
        exit(1);

    if(!textureBG.loadFromFile("texture/textureBG.png"))
        exit(1);

    background.setTexture(textureBG);

    readEntity("Entity.txt");
}

void Game::loop()
{
    while(window.isOpen())
    {
        if(clock.getElapsedTime() >= sf::milliseconds(20))
        {
            clock.restart();

            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
                player->changeSpeed(0, -ACCELERATION);
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
                player->changeSpeed(0, ACCELERATION);
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
                player->changeSpeed(ACCELERATION, 0);
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
                player->changeSpeed(-ACCELERATION, 0);
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
                player->shoot(projectiles, &textureEntity, hitboxEntity);

            player->update();

            for(size_t i = 0; i < map->animatedTiles.size(); i++)
                map->animatedTiles[i]->update();

            updateView();

            while(window.pollEvent(event))
            {
                switch(event.type)
                {
                    case sf::Event::Closed:
                        window.close();
                        break;
                    default :
                        break;
                }
            }
            window.clear(sf::Color(21, 96, 189));
            drawBackground();
            map->draw(window, view);

            for(size_t i = 0; i < projectiles.size(); i++)
            {
                if(projectiles[i]->update())
                {
                    entities.push_back(new Explosion(projectiles[i]->posX - 48, projectiles[i]->posY - 48, map, hitboxEntity, &textureEntity, sf::IntRect(128, 64, 96, 96)));
                    delete projectiles[i];
                    projectiles.erase(projectiles.begin() + i);
                    i--;
                }
                else
                    window.draw(*projectiles[i]->sprite);
            }

            for(size_t i = 0; i < entities.size(); i++)
            {
                if(entities[i]->update())
                {
                    delete entities[i];
                    entities.erase(entities.begin() + i);
                    i--;
                }
                else
                    window.draw(*entities[i]->sprite);
            }
            for(size_t i = 0; i < bonus.size(); i++)
            {
                if(!bonus[i]->interact(player))
                {
                    delete bonus[i];
                    bonus.erase(bonus.begin() + i);
                }
                else if(bonus[i]->draw)
                    window.draw(*bonus[i]->sprite);
            }

            window.draw(*(player->sprite));
            window.setView(view);

            window.display();
        }
    }
}

void Game::updateView()
{
    int x;
    int y;

    if(player->posX < WINDOW_WIDTH / 2)
        x = WINDOW_WIDTH / 2;
    else if(player->posX > map->nbTileX * TILE_WIDTH - WINDOW_WIDTH / 2)
        x = map->nbTileX * TILE_WIDTH - WINDOW_WIDTH / 2;
    else
        x = player->posX;

    if(player->posY < WINDOW_HEIGHT / 2)
        y = WINDOW_HEIGHT / 2;
    else if(player->posY > map->nbTileY * TILE_HEIGHT - WINDOW_HEIGHT / 2)
        y = map->nbTileY * TILE_HEIGHT - WINDOW_HEIGHT / 2;
    else
        y = player->posY;

    view.setCenter(x, y);
}

void Game::drawBackground()
{
    float y = float(view.getCenter().y - WINDOW_HEIGHT / 2) / (map->nbTileY * TILE_HEIGHT - WINDOW_HEIGHT);
    float x = float(view.getCenter().x - WINDOW_HEIGHT / 2) / (map->nbTileY * TILE_HEIGHT - WINDOW_HEIGHT);
    background.setPosition(x * (map->nbTileY * TILE_HEIGHT - background.getTextureRect().height) - background.getTextureRect().width, y * (map->nbTileY * TILE_HEIGHT - background.getTextureRect().height));

    while(background.getPosition().x + background.getTextureRect().width < view.getCenter().x - WINDOW_WIDTH / 2)
        background.move(background.getTextureRect().width, 0);

    for(int i = 0; i < WINDOW_WIDTH / background.getTextureRect().width + 1; i++)
    {
        window.draw(background);
        background.move(background.getTextureRect().width, 0);
    }
}

void Game::readEntity(const char * filename)
{
    std::ifstream ifs(filename);
    int nbBonus, x, y;
    char type;

    ifs >> nbBonus;

    for(int i = 0 ; i < nbBonus ; i++)
    {
        ifs >> type;
        ifs >> x;
        ifs >> y;
        switch (type)
        {
            case 'l':
                bonus.push_back(new LifeBonus(x, y, map, hitboxEntity, &textureEntity, sf::IntRect(0,64,32,32)));
                break;
            case 'm':
                bonus.push_back(new MineBonus(x, y, map, hitboxEntity, &textureEntity, sf::IntRect(32,64,32,64)));
                break;
            case 's':
                bonus.push_back(new SpeedBonus(x, y, map, hitboxEntity, &textureEntity, sf::IntRect(64,64,32,32)));
                break;

            default:
                break;
        }

    }
}
