#include "game.h"
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
Sword::Sword()
    :attack_mode{false}
{
    setOrigin(sf::Vector2f{15.f, 336.f});
}

//PLAYER
Player::Player(int hp, sf::Vector2f speed, sf::Vector2f position, sf::Vector2f scale, sf::Texture* player_t, sf::Texture* sword_t)
    :Entity(hp, speed, position, scale, player_t)
{
    setOrigin(sf::Vector2f{(getLocalBounds().width / 2.f), getLocalBounds().height});
    sword.setTexture(*sword_t);
    sword.setScale(sf::Vector2f{0.3f, 0.3f});
        
}

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

//PLAYSTATE
PlayState::PlayState() = default;


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
    sf::Vector2f knockback{10.f, 0.f};
    for (Entity* c : Enemy) 
    { 
        if (getGlobalBounds().intersects(c->getGlobalBounds()) 
                && c->getPosition().x < getPosition().x) 
        { 
            move(knockback); 
            sword.move(knockback); 
            c->move(-2.f * knockback); 
        } 
        else if(getGlobalBounds().intersects(c->getGlobalBounds()) 
                && c->getPosition().x > getPosition().x) 
        { 
            move(-knockback); 
            sword.move(-knockback); 
            c->move(2.f * knockback); 
        } 
    } 
}

void Player::move_player(sf::Vector2f speed, sf::Time tick)
{
    //DRY
    if ( speed.x > 0.f )
    {
        move(speed * tick.asSeconds());
        setScale(sf::Vector2f(0.3f, 0.3f));
        sword.setScale(sf::Vector2f(0.3f, 0.3f));
        sword.setPosition(sf::Vector2f{getPosition().x + (getGlobalBounds().width / 2.f) - 5.f, 
                getPosition().y - getGlobalBounds().height + (290 * 0.3f)});
    }
    else
    {
        move(speed * tick.asSeconds());
        setScale(sf::Vector2f(-0.3f, 0.3f));
        sword.setScale(sf::Vector2f(-0.3f, 0.3f));
        sword.setPosition(sf::Vector2f{getPosition().x - (getGlobalBounds().width / 2.f) + 5.f, 
                getPosition().y - getGlobalBounds().height + (290 * 0.3f)});
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
        move_player(-speed, time);
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    {
        move_player(speed, time);
    }

    sword.update(time, &enemies);

    window.draw(sword);
    window.draw(*this);
}

//SWORD FUNCTIONS

void Sword::update(sf::Time tick, std::vector<Enemy*>* enemies)
{
    
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
        sf::RenderWindow &window)
{
    window.clear(sf::Color(0, 200, 0, 255));
    for( Enemy* e : enemies )
    {
        e->update(player->getPosition(), time);
        window.draw(*e);
    }
    player->player_update(time, event, window, enemies);
    player->hit(enemies);
}


//TEMPORARY MAIN
int main()
{
    sf::RenderWindow window(sf::VideoMode(960,480), "Hang in there, bud");

    //Load textures
    sf::Texture player_t, peasant_t, knight_t, sword_t;
    player_t.loadFromFile("static/textures/player.png");
    peasant_t.loadFromFile("static/textures/peasant.png");
    knight_t.loadFromFile("static/textures/knight.png");
    sword_t.loadFromFile("static/textures/Sword-1.png");

    sf::Vector2f scale{0.3f, 0.3f};
    Player p{3, sf::Vector2f{500.f, 0.f}, sf::Vector2f{200.f, 200.f}, scale, &player_t, &sword_t};
    
    Peasant e{sf::Vector2f{50.f, 0.f}, sf::Vector2f{600.f, 200.f}, scale, &peasant_t};

    Knight k{2, sf::Vector2f{30.f, 0.f}, sf::Vector2f{0.f, 200.f}, scale, &knight_t};


    //Setup playfield and run game
    PlayState playstate{};
    playstate.setPlayer(&p);
    playstate.addEnemy(&e);
    playstate.addEnemy(&k);
    sf::Clock clock;
    sf::Event event{};
    window.setVerticalSyncEnabled(true);
    while(window.isOpen())
    {
        sf::Time elapsed = clock.restart();
        playstate.update(elapsed, event, window);
        window.display();
    }
}
