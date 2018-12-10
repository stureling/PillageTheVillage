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
    :Enemy(hp, speed, hitbox, immunity){}

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

}

void Player::update(sf::Keyboard::Key code, std::vector<Character*> Enemy)
{
    if (code == sf::Keyboard::D && getPosition().x < 600.f)
    {
        setScale(sf::Vector2f{0.3f, 0.3f});
        move(speed);
    }
    if (code == sf::Keyboard::A && getPosition().x > 0.f)
    {
        setScale(sf::Vector2f{-0.3f, 0.3f});
        move(-speed);
    }
    hit(Enemy);
}

void Player::hit(std::vector<Character*> Enemy)
{
    for (Character* c : Enemy) {
        if (getGlobalBounds().intersects(c->getGlobalBounds())) {
            std::cout<<"Collision"<<std::endl;
        }
    }
}

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
        //this->move(-this->speed);
    }

}

bool Enemy::valid_hit()
{
    return true;
}


//GAME STATES
int PlayState() {
    sf::RenderWindow window{sf::VideoMode(960, 480), "Hang in there, bud."};
    sf::Texture background_tex;
    sf::Texture player_tex;
    sf::RectangleShape hitbox{sf::Vector2f{50.0, 50.0}};

    std::map<char, bool> m{{'c', true}};
    Player p(3, sf::Vector2f{4.f, 0.f}, hitbox);
    p.setOrigin(386.f, 0.f);
    Enemy e(3, sf::Vector2f{2.f, 0.f}, hitbox, m);
    Enemy e1(3, sf::Vector2f{2.f, 0.f}, hitbox, m);
    std::vector<Character*> enemies{};
    enemies.push_back(&e);
    enemies.push_back(&e1);
    p.setPosition(sf::Vector2f{600.f, 300.f});
    e.setPosition(sf::Vector2f{200.f, 300.f});
    e1.setPosition(sf::Vector2f{250.f, 300.f});

    //Load and set textures
    player_tex.loadFromFile("static/textures/player.png");
    p.setTexture(player_tex);
    e.setTexture(player_tex);
    e1.setTexture(player_tex);
    p.setScale(sf::Vector2f{0.3f, 0.3f});
    e.setScale(sf::Vector2f{0.3f, 0.3f});
    e1.setScale(sf::Vector2f{0.3f, 0.3f});

    window.setVerticalSyncEnabled(true);
    sf::Event event;
    while (window.isOpen()) {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) {
            window.close();
        }
        //sf::sleep(sf::seconds(2));
        e.update(p.getPosition());
        e1.update(p.getPosition());
        p.update(event.key.code, enemies);
        window.clear();
        window.draw(p);
        window.draw(e);
        window.draw(e1);
        window.display();
    }

    return 1;
}

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
/*std::map<char, int> Peasant{
    {'w', false},
    {'s', false}
};
*/