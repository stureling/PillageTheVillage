#include "logic.h"

//CONSTRUCTORS
//ENTITY
Entity::Entity( int hp, sf::Vector2f speed)
    :speed{speed}, hp{hp}{}

//PLAYER
Player::Player(int hp, sf::Vector2f speed)
    :Entity{hp, speed}{}

//ENEMY
Enemy::Enemy(int hp, sf::Vector2f speed, std::map<char, bool> immunity)
    :Entity{hp, speed}, immunity{immunity}{}

//KNIGHT
Knight::Knight(int hp, sf::Vector2f speed)
    :Enemy(hp, speed, k_immunity){}

//SWORD
//Sword::Sword()

//FUNCIONS
//PLAYER FUNCTIONS
void Player::attack_light()
{
    
}
void Player::attack_heavy()
{

}
void Player::jump()
{

};

//ENEMY FUNCTIONS

/*void Enemy::resolve_hit()
{

}*/

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

bool Enemy::valid_hit()
{
    return true;
}


//GAME STATES
int PlayState()
{
    sf::RenderWindow window{sf::VideoMode(960, 480), "Hang in there, bud."};
    sf::Texture background_tex;
    sf::Texture player_tex;
    sf::Texture enemy_tex;
    
    
    std::map<char, bool> m{{'c', true}};
    Player p(3, sf::Vector2f{4.f, 0.f});   
    p.setOrigin(280.f, 0.f);
    Enemy e(3, sf::Vector2f{2.f, 0.f}, m);   
    e.setOrigin(280.f, 0.f);
    p.setPosition(sf::Vector2f{50.f, 60.f});
    e.setPosition(sf::Vector2f{700.f, 300.f});

    //Load and set textures
    player_tex.loadFromFile("static/textures/player.png");
    enemy_tex.loadFromFile("static/textures/peasant.png");
    p.setTexture(player_tex);
    e.setTexture(enemy_tex);
    p.setScale(sf::Vector2f{0.25f, 0.25f});
    e.setScale(sf::Vector2f{0.25f, 0.25f});
    window.setVerticalSyncEnabled(true);
    window.setKeyRepeatEnabled(false);
    sf::Clock global_clock{};
    while(window.isOpen())
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && p.getPosition().x < 900.f)
        {
            p.setScale(sf::Vector2f{0.25f, 0.25f});
            p.move(p.speed * global_clock.getElapsedTime().asSeconds());
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && p.getGlobalBounds().left > 0.f)
        {
            p.setScale(sf::Vector2f{-0.25f, 0.25f});
            p.move(-p.speed * global_clock.getElapsedTime().asSeconds());
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::J))
        {
            sf::Thread thread(&Player::attack_light, &p);
            thread.launch();
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
        {
            window.close();
        }

        e.update(p.getPosition(), global_clock.getElapsedTime());
        window.clear();
        window.draw(p);
        window.draw(e);
        window.display();
        std::cout << p.getGlobalBounds().left << std::endl;
    }
    return 1; 

};

void MenuState()
{

};

//GAME MAIN

int Game()
{
    return 1;
};


//GLOBAL VARIABLES
std::map<char, int> Knight{
    {'w', true},
    {'s', false}
};
std::map<char, int> Peasant{
    {'w', false},
    {'s', false}
};
