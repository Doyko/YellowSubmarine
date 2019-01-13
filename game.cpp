#include "game.h"

Game::Game(const std::string name)
{
    srand(time(NULL));

    window.create(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Yellow Submarine");
    window.setVerticalSyncEnabled(true);
    view.reset(sf::FloatRect(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2, WINDOW_WIDTH, WINDOW_HEIGHT));

    background.setTexture(Data::textureBG);
    foreground.setTexture(Data::textureFG);
    menu.setTexture(Data::textureMenu);
    hub.setTexture(Data::textureHub);
    message.setTexture(Data::textureMessage);

    player = new Player(128, 32);
    Data::initPlayer(player);

    map = new Map();
    Data::initMap(map);

    level = 1;
}

Game::~Game()
{
    clearVectors();
    delete player;
    delete map;
}

void Game::menuLoop()
{
    menuView();
    int tick = 255;
    int choice = 0;

    while(window.isOpen())
    {
        if(clock.getElapsedTime() >= sf::milliseconds(20))
        {
            clock.restart();

            if(tick == 0)
            {
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
                {
                    if(choice == 0)
                    {
                        loop();
                        menuView();
                    }
                    else if(choice == 1)
                    {
                        window.close();
                        break;
                    }
                }
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
                {
                    if(choice != 0)
                        choice--;
                }
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
                {
                    if(choice != 1)
                        choice++;
                }
            }
            else
                tick -= 3;

            pollEvent();
            player->update();
            drawMenu(choice, tick);
            window.display();
        }
    }
}

void Game::loop()
{
    if(!window.isOpen())
        return;

    state = play;

    clearVectors();
    readEntity("level/entity" + std::to_string(level) + ".txt");
    map->readMap("level/level" + std::to_string(level) + ".pgm");
    player->setMaxLife();

    while(window.isOpen() && state == play)
    {
        if(clock.getElapsedTime() >= sf::milliseconds(20))
        {
            clock.restart();

            keyEvent();
            pollEvent();
            update();
            draw();

            window.display();

            if(state == win)
            {
                if(level == NBLEVEL)
                {
                    level = 1;
                    printMessage();
                }
                else
                {
                    level++;
                    nextLevel();
                }
            }
            if(state == death)
            {
                level = 1;
                printMessage();
            }
        }
    }
}

void Game::keyEvent()
{
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        player->changeSpeed(0, -ACCELERATION);
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        player->changeSpeed(0, ACCELERATION);
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        player->changeSpeed(ACCELERATION, 0);
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        player->changeSpeed(-ACCELERATION, 0);
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
        player->shoot();
}

void Game::pollEvent()
{
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
}

void Game::update()
{
    player->update();

    updateView();

    map->updateAnimatedTiles();
    updateVector(Data::effects);
    updateVector(Data::explosable);
    updateVector(Data::entities);
    updateVector(Data::bonus);
    if(state == play)
    {
        if(player->getLife() <= 0)
            state = death;
        if(Data::nbChest == 0)
            state = win;
    }
}

void Game::updateView()
{
    int x;
    int y;

    if(player->posX < WINDOW_WIDTH / 2)
        x = WINDOW_WIDTH / 2;
    else if(player->posX > map->getNbTileX() * TILE_WIDTH - WINDOW_WIDTH / 2)
        x = map->getNbTileX() * TILE_WIDTH - WINDOW_WIDTH / 2;
    else
        x = player->posX;

    if(player->posY < WINDOW_HEIGHT / 2)
        y = WINDOW_HEIGHT / 2;
    else if(player->posY > map->getNbTileY() * TILE_HEIGHT - WINDOW_HEIGHT / 2)
        y = map->getNbTileY() * TILE_HEIGHT - WINDOW_HEIGHT / 2;
    else
        y = player->posY;

    view.setCenter(x, y);
}


void Game::updateVector(std::vector<Bonus*> &vect) const
{
    for(size_t i = 0; i < vect.size(); i++)
    {
        if(!vect[i]->interact())
        {
            delete vect[i];
            vect.erase(vect.begin() + i);
            i--;
        }
    }
}

void Game::menuView()
{
    view.setCenter(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);
    menu.setPosition(WINDOW_WIDTH / 2 - menu.getTextureRect().width / 2, WINDOW_HEIGHT / 2 - menu.getTextureRect().height / 2);
    window.setView(view);
}

void Game::drawMenu(const int choice, const int tick)
{
    player->setDirection(0);
    window.clear(sf::Color(255, 0, 0));
    background.setPosition(0, 0);

    for(int i = 0; i < WINDOW_WIDTH / background.getTextureRect().width + 1; i++)
    {
        window.draw(background);
        background.move(background.getTextureRect().width, 0);
    }

    menu.setColor(sf::Color(255, 255, 255, 255 - tick));
    window.draw(menu);

    if(tick == 0)
    {
        player->setPosition(WINDOW_WIDTH / 2 - menu.getTextureRect().width / 2 + 40, WINDOW_HEIGHT / 2 + menu.getTextureRect().height / 2 - (2 - choice) * 70 + 15);
        window.draw(*player->sprite);
    }
}

void Game::draw()
{
    window.clear(sf::Color(21, 96, 189));
    window.setView(view);

    drawBackground();

    map->draw(window, view);

    drawVector(Data::effects);
    drawVector(Data::explosable);
    drawVector(Data::entities);
    drawVector(Data::bonus);

    window.draw(*(player->sprite));
    drawForeground();

    drawHub();
}

void Game::drawVector(const std::vector<Bonus*> &vect)
{
    for(size_t i = 0; i < vect.size(); i++)
    {
        window.draw(*vect[i]->sprite);
    }
}

void Game::drawBackground()
{
    float y = float(view.getCenter().y - WINDOW_HEIGHT / 2) / (map->getNbTileY() * TILE_HEIGHT - WINDOW_HEIGHT);
    float x = - float(view.getCenter().x - WINDOW_HEIGHT / 2) / (map->getNbTileY() * TILE_HEIGHT - WINDOW_HEIGHT);
    background.setPosition(x * (map->getNbTileY() * TILE_HEIGHT - background.getTextureRect().height) - background.getTextureRect().width, y * (map->getNbTileY() * TILE_HEIGHT - background.getTextureRect().height));

    while(background.getPosition().x + background.getTextureRect().width < view.getCenter().x - WINDOW_WIDTH / 2)
        background.move(background.getTextureRect().width, 0);

    for(int i = 0; i < WINDOW_WIDTH / background.getTextureRect().width + 1; i++)
    {
        window.draw(background);
        background.move(background.getTextureRect().width, 0);
    }
}

void Game::drawForeground()
{
    float x = - float(view.getCenter().x - WINDOW_HEIGHT / 2) / 5;
    foreground.setPosition(x, background.getPosition().y);

    while(foreground.getPosition().x + foreground.getTextureRect().width < view.getCenter().x - WINDOW_WIDTH / 2)
        foreground.move(foreground.getTextureRect().width, 0);

    for(int i = 0; i < WINDOW_WIDTH / foreground.getTextureRect().width + 1; i++)
    {
        window.draw(foreground);
        foreground.move(foreground.getTextureRect().width, 0);
    }
}

void Game::drawHub()
{
    int x = view.getCenter().x - WINDOW_WIDTH / 2;
    int y = view.getCenter().y - WINDOW_HEIGHT / 2;
    hub.setPosition(x, y);
    hub.setTextureRect(sf::IntRect(0, 0, 50, 50));
    window.draw(hub);
    hub.setTextureRect(sf::IntRect(player->getLife() * 40 + 50, 0, 40, 50));
    hub.setPosition(x + 60, y);
    window.draw(hub);
}

void Game::clearVectors() const
{
    clearVector(Data::effects);
    clearVector(Data::explosable);
    clearVector(Data::entities);
    clearVector(Data::bonus);
}

void Game::printMessage()
{
    int tick = 0;
    sf::RectangleShape rect(sf::Vector2f(WINDOW_WIDTH, WINDOW_HEIGHT));
    rect.setFillColor(sf::Color(0, 0, 0));

    if(state == win)
        message.setTextureRect(sf::IntRect(0, 360, 720, 120));
    else
        message.setTextureRect(sf::IntRect(0, 0, 420, 120));

    while(window.isOpen() && tick <= 510)
    {
        if(clock.getElapsedTime() >= sf::milliseconds(20))
        {
            clock.restart();
            if(tick < 255)
            {
                tick += 3;
                update();
                draw();
                rect.setPosition(view.getCenter().x - WINDOW_WIDTH / 2, view.getCenter().y - WINDOW_HEIGHT / 2);
                rect.setFillColor(sf::Color(0, 0, 0, tick));
                window.draw(rect);
            }
            else
            {
                tick++;
                window.draw(rect);
                message.setPosition(view.getCenter().x - message.getTextureRect().width / 2, view.getCenter().y - message.getTextureRect().height / 2);
                message.setColor(sf::Color(255, 255, 255, tick - 255));
                window.draw(message);
            }
            window.display();
            pollEvent();
        }
    }
}

void Game::nextLevel()
{
    std::cout << level << '\n';
    int tick = 0;
    sf::RectangleShape rect(sf::Vector2f(WINDOW_WIDTH, WINDOW_HEIGHT));
    rect.setFillColor(sf::Color(0, 0, 0));

    while(window.isOpen() && tick <= 510)
    {
        if(clock.getElapsedTime() >= sf::milliseconds(20))
        {
            clock.restart();
            if(tick < 255)
            {
                tick += 3;
                update();
                draw();
                rect.setPosition(view.getCenter().x - WINDOW_WIDTH / 2, view.getCenter().y - WINDOW_HEIGHT / 2);
                rect.setFillColor(sf::Color(0, 0, 0, tick));
                window.draw(rect);
            }
            else
            {
                tick++;
                window.draw(rect);
                message.setColor(sf::Color(255, 255, 255, tick - 255));
                printLevel();
            }
            window.display();
            pollEvent();
        }
    }
}

void Game::printLevel()
{
    message.setTextureRect(sf::IntRect(0, 120, 240, 120));
    message.setPosition(view.getCenter().x - message.getTextureRect().width, view.getCenter().y - message.getTextureRect().height / 2);
    window.draw(message);
    message.setTextureRect(sf::IntRect(60 * (level / 10), 240, 60, 120));
    message.move(280, 0);
    window.draw(message);
    message.setTextureRect(sf::IntRect(60 * (level % 10), 240, 60, 120));
    message.move(60, 0);
    window.draw(message);
}

void Game::readEntity(const std::string fileName) const
{
    std::ifstream ifs(fileName);
    if(!ifs)
    {
        std::cout << "Can't open \"" << fileName << "\"." << std::endl;
        exit(0);
    }

    int nbEntities;
    int x;
    int y;
    EntityType entity;

    ifs >> x;
    ifs >> y;
    player->setPosition(x * TILE_WIDTH, y * TILE_HEIGHT);

    while(ifs >> entity)
    {
        ifs >> nbEntities;
        for(int i = 0 ; i < nbEntities; i++)
        {
            ifs >> x;
            ifs >> y;
            addEntity(x * TILE_WIDTH, y * TILE_HEIGHT, entity);
        }
    }
    ifs.close();
}

void Game::addEntity(const int x, const int y, const EntityType e) const
{
    switch(e)
    {
        case EntityType::chest:
            Data::nbChest++;
            Data::effects.push_back(new Chest(x, y));
            break;
        case EntityType::lifebonus:
            Data::bonus.push_back(new Bonus(x, y, BuffType::life, Bonus::lifeDimension));
            break;
        case EntityType::speedbonus:
            Data::bonus.push_back(new Bonus(x, y, BuffType::speed, Bonus::speedDimension));
            break;
        case EntityType::shark:
            Data::entities.push_back(new Shark(x, y));
            break;
        case EntityType::octopus:
            Data::entities.push_back(new Octopus(x, y));
            break;
        case EntityType::mine:
            Data::entities.push_back(new Mine(x, y));
            break;
        case EntityType::barricade:
            Data::explosable.push_back(new Barricade(x, y));
            break;
        default:
            std::cout << "miss" << '\n';
            break;
    }
}
