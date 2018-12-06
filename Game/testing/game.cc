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
//ENEMY
Enemy::Enemy(int hp, sf::Vector2f speed)
    :Entity{hp, speed}{}

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

void Player::update(sf::Time time)
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && getPosition().x < 900.f)
    {
        setScale(sf::Vector2f(1.f, 1.f));
        move(speed * time.asSeconds());
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && getPosition().x < 0.f)
    {
        setScale(sf::Vector2f(-1.f, 1.f));
        move(-speed * time.asSeconds());

    }
}

void PlayState::addEnemy(Entity* entity)
{
    enemies.push_back(entity);
}

void PlayState::update(sf::Time time)
{
    //player->update(time);
    for( Entity* e : enemies )
    {
        e->update(time);
    }
}

PlayState::PlayState(){}


int main()
    //TODO
    //Fiender ska gå mot spelaren
    //Fiender ska kommunicera en träff med spelaren
    //
{
    sf::RenderWindow window(sf::VideoMode(960,480), "Hold on");
    sf::Texture player_t;
    player_t.loadFromFile("../static/textures/player.png");
    Player p{3, sf::Vector2f{1000.f, 0.f}, player_t};
    p.setPosition(sf::Vector2f{200.f, 200.f});
    PlayState playstate{};
    playstate.addEnemy(&p);
    sf::Clock clock;
    window.setVerticalSyncEnabled(true);
    while(window.isOpen())
    {
        playstate.update(clock.restart());
        window.clear(sf::Color(0, 200, 0, 255));
        window.draw(p);
        window.display();
    }
}
