#include "game.h"
//CONSTRUCTORS
//ENTITY
Entity::Entity(int hp, sf::Vector2f speed)
    :speed{speed}, hp{hp}{}

//PLAYER
Player::Player(int hp, sf::Vector2f speed, sf::Texture &texture)
    :Entity(hp, speed){
        setTexture(texture);
    }

Player::~Player(){}

//ENEMY
Enemy::Enemy(int hp, sf::Vector2f speed)
    :Entity{hp, speed}{}

//PEASANT
Peasant::Peasant(sf::Vector2f speed)
    :Enemy{1, speed}{}

//KNIGHT
Knight::Knight(int hp, sf::Vector2f speed)
    :Enemy{hp, speed}{}

//PLAYSTATE
PlayState::PlayState(){}


//FUNCTIONS
//ENEMY FUCNTIONS
void Enemy::update(sf::Vector2f player_pos, sf::Time tick)
{
    if (player_pos.x > this->getPosition().x)
    {
        this->setScale(sf::Vector2f(0.3f, 0.3f));
        this->move(speed * tick.asSeconds());
    }
    else
    {
        this->setScale(sf::Vector2f(-0.3f, 0.3f));
        this->move(-speed * tick.asSeconds());
    }

}
//PLAYER FUNCTIONS

void Player::hit(std::vector<Enemy*> Enemy)
{
    for (Entity* c : Enemy) 
    { 
        if (getGlobalBounds().intersects(c->getGlobalBounds()) 
                && c->getPosition().x < getPosition().x) 
        { 
            move(10.f, 0.f); c->move(-20.f, 0.f); 
        } 
        else if(getGlobalBounds().intersects(c->getGlobalBounds()) 
                && c->getPosition().x > getPosition().x) 
        { 
            move(-10.f, 0.f); c->move(20.f, 0.f); 
        } 
    } 
}

void Player::player_update(sf::Time time, sf::Event &event_queue, sf::Window &window)
{
    while (window.pollEvent(event_queue))
    {
        if ((event_queue.type == sf::Event::KeyPressed) 
                && (event_queue.key.code == sf::Keyboard::A))
        {
            setScale(sf::Vector2f(-0.3f, 0.3f));
            move(-speed * time.asSeconds());
        }

        if ((event_queue.type == sf::Event::KeyPressed) 
                && (event_queue.key.code == sf::Keyboard::D))
        {
            setScale(sf::Vector2f(0.3f, 0.3f));
            move(speed * time.asSeconds());
        }

        if ((event_queue.type == sf::Event::KeyPressed) 
                && (event_queue.key.code == sf::Keyboard::Space) 
                && getPosition().y == 200.f)
        {
            window.close();
        }
    }
}

//PLAYSTATE FUNCTIONS

void PlayState::addEnemy(Enemy* enemy)
{
    enemies.push_back(enemy);
}
void PlayState::setPlayer(Player* entity)
{
    player = entity;
}

void PlayState::update(sf::Time time, 
        sf::Event &event, 
        sf::Window &window)
{
    for( Enemy* e : enemies )
    {
        e->update(player->getPosition(), time);
    }
    player->player_update(time, event, window);
    player->hit(enemies);
}


//TEMPORARY MAIN
int main()
{
    sf::RenderWindow window(sf::VideoMode(960,480), "Hang in there, bud");

    //Load and set textures, scale and position
    sf::Texture player_t, peasant_t, knight_t;
    player_t.loadFromFile("static/textures/player.png");
    peasant_t.loadFromFile("static/textures/peasant.png");
    knight_t.loadFromFile("static/textures/knight.png");

    Player p{3, sf::Vector2f{1000.f, 0.f}, player_t};
    p.setPosition(sf::Vector2f{200.f, 200.f});
    p.setScale(sf::Vector2f{0.3f, 0.3f});
    p.setOrigin(sf::Vector2f{386.f, 0.f});
    
    Peasant e{sf::Vector2f{20.f, 0.f}};
    e.setTexture(peasant_t);
    e.setPosition(sf::Vector2f{600.f, 200.f});
    e.setScale(sf::Vector2f{0.3f, 0.3f});

    Knight k{3, sf::Vector2f{20.f, 0.f}};
    k.setTexture(knight_t);
    k.setPosition(sf::Vector2f{0.f, 200.f});
    k.setScale(sf::Vector2f{0.3f, 0.3f});


    //Setup playfield and run game
    PlayState playstate{};
    playstate.setPlayer(&p);
    playstate.addEnemy(&e);
    playstate.addEnemy(&k);
    sf::Clock clock;
    sf::Event event;
    window.setVerticalSyncEnabled(true);
    while(window.isOpen())
    {
        sf::Time elapsed = clock.restart();
        playstate.update(elapsed, event, window);
        window.clear(sf::Color(0, 200, 0, 255));
        window.draw(p);
        window.draw(e);
        window.draw(k);
        window.display();
    }
}
