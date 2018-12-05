#include "logic.h"

//CONSTRUCTORS
//CHARACTER
Character::Character( int hp, sf::Vector2f speed, sf::RectangleShape hitbox)
    :speed{speed}, hp{hp}, hitbox{hitbox}{}

//PLAYER
Player::Player(int hp, sf::Vector2f speed, sf::RectangleShape hitbox)
    :Character{hp, speed, hitbox}{}

//ENEMY
Enemy::Enemy(int hp, sf::Vector2f speed, sf::RectangleShape hitbox, std::map<char, bool> immunity)
    :Character{hp, speed, hitbox}, immunity{immunity}{}
//KNIGHT
Knight::Knight(int hp, sf::Vector2f speed, sf::RectangleShape hitbox)
    :Enemy(hp, speed, hitbox, k_immunity){}

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

void Enemy::resolve_hit()
{

}

void Enemy::update(sf::Vector2f player_pos)
{
    if (player_pos.x > this->getPosition().x)
    {
        this->move(this->speed);
    }
    else
    {
        this->move(-this->speed);
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
    sf::RectangleShape hitbox{sf::Vector2f{1.0, 1.0}};
    
    
    std::map<char, bool> m{{'c', true}};
    Player p(3, sf::Vector2f{4.f, 0.f}, hitbox);   
    p.setOrigin(386.f, 0.f);
    Enemy e(3, sf::Vector2f{2.f, 0.f}, hitbox, m);   
    p.setPosition(sf::Vector2f{50.f, 60.f});
    e.setPosition(sf::Vector2f{700.f, 300.f});

    //Load and set textures
    player_tex.loadFromFile("static/textures/player.png");
    p.setTexture(player_tex);
    e.setTexture(player_tex);
    p.setScale(sf::Vector2f{0.3f, 0.3f});
    e.setScale(sf::Vector2f{0.3f, 0.3f});
    window.setVerticalSyncEnabled(true);
    while(window.isOpen())
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && p.getPosition().x < 600.f)
        {
            p.setScale(sf::Vector2f{0.3f, 0.3f});
            p.move(p.speed);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && p.getPosition().x > 0.f)
        {
            p.setScale(sf::Vector2f{-0.3f, 0.3f});
            p.move(-p.speed);
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

        sf::sleep(sf::seconds(2));
        e.update(p.getPosition());
        window.clear();
        window.draw(p);
        window.draw(e);
        window.display();
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
