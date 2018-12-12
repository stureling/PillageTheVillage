#include "entities.h"
//CONSTRUCTORS
//ENTITY
Entity::Entity(int hp, sf::Vector2f speed, sf::Vector2f position, sf::Vector2f scale, sf::Texture* texture)
    :speed{speed}, hp{hp}
{
    setTexture(*texture);
    setOrigin(sf::Vector2f{(getLocalBounds().width / 2.f), getLocalBounds().height});
    setScale(scale);
    setPosition(position);
}

//SWORD
Sword::Sword(sf::Vector2f scale, sf::Texture* texture)
    :attack_mode{false}
{
    setOrigin(sf::Vector2f{15.f, 336.f});
    setTexture(*texture);
    setScale(scale);
}

//PLAYER
Player::Player(int hp, sf::Vector2f speed, sf::Vector2f position, sf::Vector2f scale, sf::Texture* player_t, sf::Texture* sword_t)
    :Entity(hp, speed, position, scale, player_t), sword{scale, sword_t}{}

Player::~Player() = default;

//ENEMY
Enemy::Enemy(int hp, sf::Vector2f speed, sf::Vector2f position, sf::Vector2f scale, sf::Texture* texture)
    :Entity{hp, speed, position, scale, texture}{}

//PEASANT
Peasant::Peasant(sf::Vector2f speed, sf::Vector2f position, sf::Vector2f scale, sf::Texture* texture)
    :Enemy{1, speed, position, scale, texture}{}

//KNIGHT
Knight::Knight(int hp, sf::Vector2f speed, sf::Vector2f position, sf::Vector2f scale, sf::Texture* texture)
    :Enemy{hp, speed, position, scale, texture}{}



//FUNCTIONS
//ENEMY FUCNTIONS
void Enemy::update(sf::Vector2f player_pos, sf::Time tick)
{
    //DRY
    if (player_pos.x > getPosition().x)
    {
        setScale(sf::Vector2f(0.3f, 0.3f));
        move(speed * tick.asSeconds());
    }
    else
    {
        setScale(sf::Vector2f(-0.3f, 0.3f));
        move(-speed * tick.asSeconds());
    }
}

void Enemy::hit(char attack_type)
{
    
}


//PLAYER FUNCTIONS

void Player::hit(std::vector<Enemy*> enemies)
{
    for (Entity* c : enemies) 
    { 
        if (getGlobalBounds().intersects(c->getGlobalBounds())) 
        {

            sf::Vector2f knockback{10.f, 0.f};
            if (c->getPosition().x < getPosition().x) 
            {
                knockback *= -1.f;
            }
            move(-knockback); 
            c->move(2.f * knockback); 
        }
    } 
}


void Player::player_update(sf::Time time, sf::Event &event_queue, sf::RenderWindow &window, std::vector<Enemy*> &enemies)
{
    while (window.pollEvent(event_queue))
    {
        if (event_queue.type == sf::Event::Closed)
        {
            window.close();
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
        {
            window.close();
        }
        else if ((event_queue.type == sf::Event::KeyPressed) 
                && (event_queue.key.code == sf::Keyboard::Space)
                && getPosition().y == 200.f)
        {
            std::cout << "Jump" << std::endl; 
        }
        else if ((event_queue.type == sf::Event::KeyPressed) 
                && (event_queue.key.code == sf::Keyboard::J)
                && sword.attack_mode == 0)
        {
            std::cout << "Light attack" << std::endl;
            sword.attack_mode = 1;
            sword.timer.restart();
        }
        else if ((event_queue.type == sf::Event::KeyPressed) 
                && (event_queue.key.code == sf::Keyboard::K)
                && sword.attack_mode == 0)
        {
            std::cout << "Heavy attack" << std::endl; 
            sword.attack_mode = 2;
        }
    }
    //Movement has to be outside events to be smooth
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
    {
        setScale(sf::Vector2f(-0.3f, 0.3f));
        move(-speed * time.asSeconds() );
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    {
        setScale(sf::Vector2f(0.3f, 0.3f));
        move(speed * time.asSeconds() );
    }

    sword.update(time, &enemies, this);

    window.draw(sword);
    window.draw(*this);
}

//SWORD FUNCTIONS

void Sword::update(sf::Time tick, std::vector<Enemy*>* enemies, sf::Sprite* holder)
{
    float height{holder->getPosition().y - holder->getGlobalBounds().height + (290 * 0.3f)};
    float width{holder->getGlobalBounds().width / 2.f - 5.f};

    setScale(holder->getScale());

    if (getScale().x < 0)
    {
        width *= -1.f;
    }    
    setPosition(holder->getPosition().x + width, height);
    
    if (attack_mode != 0)
    {
        if (attack_mode == 1)
        {
            if (getRotation() < 45  || getRotation() > 90)
            {
                 rotate(1000 * tick.asSeconds());
            }
            else
            {
                attack_mode = 3;
                std::cout << "Set attack_mode = 3" << std::endl;
            }
            for (Enemy* c : *enemies) 
            {
                if (getGlobalBounds().intersects(c->getGlobalBounds()))
                {
                    c->hit('w');
                }

            }
        }
        else if (attack_mode == 2)
        {

        }
        else if (attack_mode == 3 && getRotation() > 0 && getRotation() < 90)
        {
             rotate(-1000 * tick.asSeconds());
        }
        else
        {
            attack_mode = 0;
        }
        

    }

}

