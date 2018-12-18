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
Sword::Sword(sf::Vector2f scale, sf::Texture &texture, float speed = 1)
    :attack_mode{false}, speed{speed}
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
Enemy::Enemy(int hp,int immunity, unsigned points, sf::Vector2f speed, sf::Vector2f position, sf::Vector2f scale, sf::Texture &texture)
    :Entity{hp, speed, position, scale, texture}, immunity{immunity}, points{points}{}

//PEASANT
Peasant::Peasant(sf::Vector2f speed, sf::Vector2f position, sf::Vector2f scale, sf::Texture &texture)
    :Enemy{1, 0, 50, speed, position, scale, texture}{}

//KNIGHT
Knight::Knight(int hp, sf::Vector2f speed, sf::Vector2f position, sf::Vector2f scale, sf::Texture &texture, sf::Texture &sword_t)
    :Enemy{hp, 1, 150, speed, position, scale, texture}, sword{scale, sword_t, 1.5f}{}



//FUNCTIONS
//ENTITY FUNCTIONS
int Entity::get_hp()
    /** \brief Returns hp.
     *
     * Returns hp.
     */
{
    return hp;
}

//ENEMY FUCNTIONS
void Enemy::update(sf::Vector2f player_pos, sf::Time tick)
    /** \brief Moves the enemies towards the player character.
     *
     * Moves the enemies towards the player character based on the time elapsed sincecthe last frame.
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


unsigned Enemy::get_points()
    /** \brief Returns points.
     *
     * Returns points.
     */
{
    return points;
}

//PLAYER FUNCTIONS

void Player::hit(std::vector<Enemy*> enemies)
    /** \brief Checks if the player character is colliding with an enemy and updates the player accordingly.
     *
     * Checks if any enemy intersects with the player character if it isn't currently immune.
     * If intersection occurs; knockback is applied on both the player character and the enemy. The player character's health is reduced and immunity is gained.
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
    /** \brief Updates the player character
     *
     * Calls subfunctions related to updating the player characters position, scale, health. Ends the playstate if the player's health reaches 0.
     */
{
    process_input(event_queue, stateNum, window, time);
    sword.update(enemies, this);
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
    /** \brief Draws the player character.
     *
     * Draws the player character. If the player character is currently immune to damage the player character blinks with a frequency of 5 blinks per second.
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
        health.setPosition((120.f * i ), 800.f);
        window.draw(health);
    }

}

void Player::process_input( sf::Event &event_queue, int &stateNum, sf::RenderWindow &window, sf::Time tick)
    /** \brief Handels the inputs from the keyboard and other events
     *
     * Changes the current state based on player input.
     * Updates the player characters position and scale based on input and time passed since last function call.
     *
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
                && timer.getElapsedTime().asSeconds() > 1.f)
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

void Player::player_death(int &stateNum, sf::RenderWindow &window)
    /** \brief Detta är en kort beskrivning.
     *
     * Detta är en detaljerad kommentar
     */
{
    
}

void Player::jump(sf::Time tick)
    /** \brief Detta är en kort beskrivning.
     *
     * Detta är en detaljerad kommentar
     */
{

}

//SWORD FUNCTIONS

void Sword::update(std::vector<Enemy*> enemies, sf::Sprite* holder)
    /** \brief Updates the swords position and scale relative to its holder and calls attack functions if the sword is in an attack mode.
     *
    * Updates the swords position and scale relative to its holder and calls attack functions if the sword is in an attack mode. 
     * 
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
            light_attack(enemies, orientation);
        }
        else if (attack_mode == 2)
        {
            heavy_attack(enemies, orientation);
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
    /** \brief Detects collision during attack.
     *
     * Goes through a list of enemies and checks collision.
     * If collision occurs the enemy is knocked back and the hit function is called on the object.
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

void Sword::light_attack(std::vector<Enemy*> enemies, float orientation)
    /** \brief The sword swings back and forth quickly.
     *
     * The sword swings back and forth between 0 and 45 degrees and checks for collision with enemies relative to the holder.
     * If collision with an enemy-object occurs during the forward swing a function to deal damage to the object is called.
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

void Sword::heavy_attack(std::vector<Enemy*> enemies, float orientation)
    /** \brief The sword moves in a predetermined pattern relative to the holder
     *
     * The sword follows a specific animation pattern relative to the holders position and scale.
     * During the attack-frames, when the sword is thrust forward, the function calls the strike function to resolve potential hits.
     * To change the total time of the animation; tweak the swords speed variable.
     *
     */
{
    if (timer.getElapsedTime().asSeconds() < 1.f * speed)
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
