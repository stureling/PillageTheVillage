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
        void update(Entity* player, sf::RenderWindow &window, sf::Time tick);
        unsigned get_points();
    protected:
        int immunity;
        unsigned points;
};
template <typename T>
class Sword : public sf::Sprite
{
    friend class Player;
    friend class Knight;
    public:
        Sword(sf::Vector2f scale, sf::Texture &texture, float speed = 1);
        void update(std::vector<T> enemies, 
                Entity* holder);
        void strike(std::vector<T> enemies);
        void light_attack(std::vector<T> enemies, float orientation);
        void heavy_attack(std::vector<T> enemies, float orientation);
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
        void collision(std::vector<Enemy*> Enemy);
        void hit(int attack_mode);
        void player_update(sf::Time time, 
                sf::Event &event_queue, 
                sf::RenderWindow &window, 
                std::vector<Enemy*> &enemies,
                int &stateNum);
        void draw_player(sf::RenderWindow &window);
        void process_input( sf::Event &event_queue, 
                int &stateNum, 
                sf::RenderWindow &window, 
                sf::Time tick);
        void jump();
    private:
        Sword<Enemy*> sword;
        sf::Sprite health;
        bool jumping;
        float playheight;

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
        void update(Entity* player, sf::RenderWindow &window, sf::Time tick);
    private:
        Sword<Player*> sword;
};

class Peasant : public Enemy
{
    public:
        Peasant(sf::Vector2f speed, sf::Vector2f position, sf::Vector2f scale, sf::Texture &texture);
};

#endif
