#include "entities.h"
//CONSTRUCTORS
//ENTITY
Entity::Entity(int hp, sf::Vector2f speed, sf::Vector2f position, sf::Vector2f scale, sf::Texture &texture)
    :speed{speed}, hp{hp}, scale{scale}, timer{}, immunity_timer{}, marked_for_destruction{false}
{
    setTexture(texture);
    setOrigin(sf::Vector2f{(getLocalBounds().width / 2.f), getLocalBounds().height});
    setScale(scale);
    setPosition(position);
}

//SWORD
Sword::Sword(sf::Vector2f scale, sf::Texture &texture)
    :attack_mode{false}
{
    setOrigin(sf::Vector2f{15.f, 336.f});
    setTexture(texture);
    setScale(scale);
}

//PLAYER
Player::Player(int hp, sf::Vector2f speed, sf::Vector2f position, sf::Vector2f scale, sf::Texture &player_t, sf::Texture &sword_t, sf::Texture &health)
    :Entity(hp, speed, position, scale, player_t), sword{scale, sword_t}, health{health}{}

Player::~Player() = default;

//ENEMY
Enemy::Enemy(int hp,int immunity, sf::Vector2f speed, sf::Vector2f position, sf::Vector2f scale, sf::Texture &texture)
    :Entity{hp, speed, position, scale, texture}, immunity{immunity}{}

//PEASANT
Peasant::Peasant(sf::Vector2f speed, sf::Vector2f position, sf::Vector2f scale, sf::Texture &texture)
    :Enemy{1, 0, speed, position, scale, texture}{}

//KNIGHT
Knight::Knight(int hp, sf::Vector2f speed, sf::Vector2f position, sf::Vector2f scale, sf::Texture &texture)
    :Enemy{hp, 1, speed, position, scale, texture}{}



//FUNCTIONS
//ENEMY FUCNTIONS
void Enemy::update(sf::Vector2f player_pos, sf::Time tick)
    /** \brief Detta är en kort beskrivning.
     *
     * Detta är en detaljerad kommentar
     */
{
    //DRY
    if (player_pos.x > getPosition().x)
    {
        setScale(scale);
        move(speed / getScale().y * tick.asSeconds());
    }
    else
    {
        setScale(-scale.x, scale.y);
        move(-speed / getScale().y * tick.asSeconds());
    }
}

void Enemy::hit(int attack_type)
    /** \brief Detta är en kort beskrivning.
     *
     * Detta är en detaljerad kommentar
     */
{
    if( attack_type != immunity && timer.getElapsedTime().asSeconds() > 0.5f )
    {
        hp -= 1;
        timer.restart();
        std::cout << "Hit!" << std::endl;
    }
}

int Enemy::get_hp()
    /** \brief Detta är en kort beskrivning.
     *
     * Detta är en detaljerad kommentar
     */
{
    return hp;
}


//PLAYER FUNCTIONS

void Player::hit(std::vector<Enemy*> enemies)
    /** \brief Detta är en kort beskrivning.
     *
     * Detta är en detaljerad kommentar
     */
{
    if( immunity_timer.getElapsedTime().asSeconds() > 1.5f)
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
                if (immunity_timer.getElapsedTime().asSeconds() > 1.5f )
                {
                    hp -= 1;
                    immunity_timer.restart();
                }
            }
        }
    }
}


void Player::player_update(sf::Time time, sf::Event &event_queue, sf::RenderWindow &window, std::vector<Enemy*> &enemies, int &stateNum)
    /** \brief Detta är en kort beskrivning.
     *
     * Detta är en detaljerad kommentar
     */
{
    process_input(event_queue, stateNum, window, time);
    sword.update(time, enemies, this);
    hit(enemies);
    window.draw(sword);
    draw_player(window);
    if( hp <= 0 )
    {
        //player_death(stateNum, window);
        stateNum = 3;
    }
}

void Player::draw_player(sf::RenderWindow &window)
    /** \brief Detta är en kort beskrivning.
     *
     * Detta är en detaljerad kommentar
     */
{
    if( immunity_timer.getElapsedTime().asSeconds() <= 1.5f )
    {
        if( std::fmod(immunity_timer.getElapsedTime().asSeconds(), 0.2f) < 0.1f )
        {
            window.draw(*this);
        }
    }
    else
    {
        window.draw(*this);
    }
    for(int i{}; i < hp; i++)
    {
        health.setScale(0.5f, 0.5f);
        health.setPosition((100.f * i ), 800.f);
        window.draw(health);
    }

}

void Player::process_input( sf::Event &event_queue, int &stateNum, sf::RenderWindow &window, sf::Time tick)
    /** \brief Detta är en kort beskrivning.
     *
     * Detta är en detaljerad kommentar
     */
{
    while (window.pollEvent(event_queue))
    {
        if (event_queue.type == sf::Event::Closed)
        {
            stateNum = 0;
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
        {
            stateNum = 1;
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
            sword.attack_mode = 1;
            sword.timer.restart();
        }
        else if ((event_queue.type == sf::Event::KeyPressed) 
                && (event_queue.key.code == sf::Keyboard::K)
                && sword.attack_mode == 0)
        {
            sword.attack_mode = 2;
            sword.timer.restart();
        }
    }
    //Movement has to be outside events to be smooth
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && getPosition().x > getGlobalBounds().width / 2)
    {
        setScale(-scale.x, scale.y);
        move(-speed * tick.asSeconds() );
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && getPosition().x < 1920 - getGlobalBounds().width / 2)
    {
        setScale(scale);
        move(speed * tick.asSeconds() );
    }

}

//SWORD FUNCTIONS

void Sword::update(sf::Time tick, std::vector<Enemy*> enemies, sf::Sprite* holder)
    /** \brief Detta är en kort beskrivning.
     *
     * Detta är en detaljerad kommentar
     */
{
    float height{holder->getPosition().y - holder->getGlobalBounds().height + (290 * holder->getScale().y)};
    float width{holder->getGlobalBounds().width / 2.f - 5.f};

    setScale(holder->getScale());
    float orientation{1.f};

    if (getScale().x < 0)
    {
        orientation *= -1.f;
    }    
    setPosition(holder->getPosition().x + width * orientation, height);
    
    if (attack_mode != 0)
    {
        if (attack_mode == 1)
        {
            light_attack(tick, enemies, orientation);
        }
        else if (attack_mode == 2)
        {
            heavy_attack(tick, enemies, orientation);
        }
        else if (attack_mode == 3 && timer.getElapsedTime().asSeconds() < 0.15f)
        {
            setRotation(45 * orientation - timer.getElapsedTime().asSeconds() * (45.f / 0.15) * orientation);
        }
        else
        {
            setRotation(0);
            attack_mode = 0;
        }
    }
}

void Sword::strike_enemies(std::vector<Enemy*> enemies)
    /** \brief Detta är en kort beskrivning.
     *
     * Detta är en detaljerad kommentar
     */
{
    if (enemies.size() > 0)
    {
        for (Enemy* c : enemies) 
        {
            if (getGlobalBounds().intersects(c->getGlobalBounds()))
            {
                c->hit(attack_mode);
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
}

void Sword::light_attack(sf::Time tick, std::vector<Enemy*> enemies, float orientation)
    /** \brief Detta är en kort beskrivning.
     *
     * Detta är en detaljerad kommentar
     */
{
    float animation_time{timer.getElapsedTime().asSeconds()};
    if (animation_time < 0.03f)
    {
        setRotation(animation_time * (45.f / 0.03f) * orientation);
        strike_enemies(enemies);
    }
    else
    {
        attack_mode = 3;
        timer.restart();
    }
}

void Sword::heavy_attack(sf::Time tick, std::vector<Enemy*> enemies, float orientation)
    /** \brief Detta är en kort beskrivning.
     *
     * Detta är en detaljerad kommentar
     */
{
    if (timer.getElapsedTime().asSeconds() < 1.f)
    {
        float new_origin_x{timer.getElapsedTime().asSeconds() * 255.f + 15.f};
        float new_origin_y{getOrigin().x * -1.423728813559322f + 357.35593220338984f};
        setOrigin(new_origin_x, new_origin_y);
        setRotation(45 * timer.getElapsedTime().asSeconds() * orientation);
    }
    else if (timer.getElapsedTime().asSeconds() > 1.f && timer.getElapsedTime().asSeconds() < 1.5f)
    {
            setRotation(45 * orientation);
    }
    else if (timer.getElapsedTime().asSeconds() > 1.5f && timer.getElapsedTime().asSeconds() < 2.5f)
    {
        if ( getOrigin().x > 15 )
        {
            float new_origin_x{getOrigin().x - timer.getElapsedTime().asSeconds() * 20.f};
            float new_origin_y{getOrigin().x * -1.423728813559322f + 357.35593220338984f};
            setOrigin(new_origin_x, new_origin_y);
            strike_enemies(enemies);
        }
        setRotation(45 * orientation);
    }
    else
    {
        setOrigin(sf::Vector2f{15.f, 336.f});
        setRotation(45 * orientation);
        attack_mode = 3;
        timer.restart();
    }
}

//KNIGHT FUNCTIONS
