#include "game.h"

Game::Game(std::string name)
:
    HitboxEntity(Hitbox("HitboxEntity.pbm")),
    HitboxTile(Hitbox("HitboxTile.pbm")),
    map(new Map("level.txt", &TextureTile, HitboxTile)),
    player(new Player(128, 128, map, HitboxEntity, &TextureEntity, sf::IntRect(0,0,64,37))),
    ball(new TengibleEntity(1024, 448, map, HitboxEntity, &TextureEntity, sf::IntRect(0,64,25,89)))
{
    srand(time(NULL));
    window.create(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Yellow Submarine");
    window.setVerticalSyncEnabled(true);
    view.reset(sf::FloatRect(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2, WINDOW_WIDTH, WINDOW_HEIGHT));
    //settings.antialiasingLevel = 8;

    if(!TextureEntity.loadFromFile("TextureEntity.png"))
        exit(1);

    if(!TextureTile.loadFromFile("TextureTile.png"))
        exit(1);
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
            map->draw(window, view);
            window.draw(*(player->sprite));
            if(!player->checkCollision(ball))
                window.draw(*(ball->sprite));
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
