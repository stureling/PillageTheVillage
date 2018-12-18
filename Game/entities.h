#ifndef ENTITIES_H
#define ENTITIES_H
#include <SFML/Graphics.hpp>
#include <iostream>
#include <iterator>
#include <math.h>

class Entity : public sf::Sprite
{
    public:
        Entity(int hp, sf::Vector2f speed, sf::Vector2f position, sf::Vector2f scale, sf::Texture &texture);
        int get_hp();
    protected:
        sf::Vector2f const speed; 
        int hp;
        sf::Vector2f scale;
        sf::Clock timer;
        sf::Clock immunity_timer;
        bool marked_for_destruction;
};

class Enemy : public Entity
{
    public:
        Enemy(int hp, int immunity, unsigned points, sf::Vector2f speed, sf::Vector2f position, sf::Vector2f scale, sf::Texture &texture);
        void hit(int attack_type);
        void update(sf::Vector2f player_pos, sf::Time tick);
        unsigned get_points();
    protected:
        int immunity;
        unsigned points;
};

class Sword : public sf::Sprite
{
    friend class Player;
    friend class Knight;
    public:
        Sword(sf::Vector2f scale, sf::Texture &texture, float speed);
        void update(std::vector<Enemy*> enemies, Sprite* holder);
        void strike_enemies(std::vector<Enemy*> enemies);
        void light_attack(std::vector<Enemy*> enemies, float orientation);
        void heavy_attack(std::vector<Enemy*> enemies, float orientation);
    private:
        int attack_mode;
        sf::Clock timer;
        float speed;

};

class Player : public Entity
{
    public:
        Player(int hp, sf::Vector2f speed, 
                sf::Vector2f position, 
                sf::Vector2f scale, 
                sf::Texture &player_t, 
                sf::Texture &sword_t,
                sf::Texture &health);
        ~Player();
        void hit(std::vector<Enemy*> Enemy);
        void player_update(sf::Time time, 
                sf::Event &event_queue, 
                sf::RenderWindow &window, 
                std::vector<Enemy*> &enemies,
                int &stateNum);
        void draw_player(sf::RenderWindow &window);
        void process_input( sf::Event &event_queue, int &stateNum, sf::RenderWindow &window, sf::Time tick);
        void player_death(int &stateNum, sf::RenderWindow &window);
        void jump(sf::Time tick);
    private:
        Sword sword;
        sf::Sprite health;

};

class Knight : public Enemy
{
    public:
        Knight(int hp, 
                sf::Vector2f speed, 
                sf::Vector2f position, 
                sf::Vector2f scale, 
                sf::Texture &texture,
                sf::Texture &sword_t);
        //void update(sf::Vector2f player_pos, sf::Time tick) override;
    private:
        Sword sword;
};

class Peasant : public Enemy
{
    public:
        Peasant(sf::Vector2f speed, sf::Vector2f position, sf::Vector2f scale, sf::Texture &texture);
};

#endif
