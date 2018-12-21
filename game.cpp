#include "game.h"

Game::Game(std::string name)
:
    HitboxEntity(Hitbox("HitboxEntity.pbm")),
    HitboxTile(Hitbox("HitboxTile.pbm")),
    map(new Map("level.txt", &TextureTile, HitboxTile, &TextureEntity, HitboxEntity)),
    player(new Player(128, 128, map, HitboxEntity, &TextureEntity, sf::IntRect(0,0,64,37)))
{
    srand(time(NULL));
    window.create(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Yellow Submarine");
    window.setVerticalSyncEnabled(true);
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
            map->draw(window);
            window.draw(*(player->sprite));

            /*for(std::vector<InteractiveEntity*>::iterator i = map->entityList.begin(); i != map->entityList.end() ; i++)
            {
              window.draw(*((*i)->sprite));
              if(player->interact((*i)))
              {
                std::cout << "delete" << std::endl;
                (*i)->~InteractiveEntity();
                map->entityList.erase(i);

              }*/

            for(size_t i = 0; i < map->entityList.size() ; i++)
            {
              window.draw(*(map->entityList[i]->sprite));
              if(player->interact(map->entityList[i]))
              {
                std::cout << "delete" << std::endl;
                map->entityList[i]->~InteractiveEntity();
                map->entityList.erase(map->entityList.begin()+i);

              }


            }
            window.display();
        }
    }
}
