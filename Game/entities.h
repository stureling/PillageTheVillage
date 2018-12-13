#ifndef ENTITIES_H
#define ENTITIES_H
#include <SFML/Graphics.hpp>
#include <iostream>
#include <iterator>
#include <cmath>
/*class Playfield
{
    public:
        sf::Sprite background;
        //std::map<sf::Time, std::vector<Enemy> waves;
       
}*/


class Entity : public sf::Sprite
{
    public:
        Entity(int hp, sf::Vector2f speed, sf::Vector2f position, sf::Vector2f scale, sf::Texture*);
    protected:
        sf::Vector2f const speed; 
        int hp;
};

class Enemy : public Entity
{
    public:
        Enemy(int hp, int immunity, sf::Vector2f speed, sf::Vector2f position, sf::Vector2f scale, sf::Texture*);
        void hit(int attack_type);
        void update(sf::Vector2f player_pos, sf::Time tick);
        int get_hp();
    protected:
        bool valid_hit();
        int immunity;
};

class Sword : public sf::Sprite
{
    friend class Player;
    friend class Knight;
    public:
        Sword(sf::Vector2f scale, sf::Texture* texture);
        void update(sf::Time tick, 
                std::vector<Enemy*>* enemies, 
                Sprite* holder);
        void light_attack();
        void heavy_attack();
    private:
        int attack_mode;
        sf::Clock timer;

};

class Player : public Entity
{
    public:
        Player(int hp, sf::Vector2f speed, 
                sf::Vector2f position, 
                sf::Vector2f scale, 
                sf::Texture* player_t, 
                sf::Texture* sword_t);
        void player_update(sf::Time time, 
                sf::Event &event_queue, 
                sf::RenderWindow &window, 
                std::vector<Enemy*> &enemies);
        ~Player();
        void hit(std::vector<Enemy*> Enemy);
        //void jump();
    private:
        Sword sword;
        sf::Clock timer;

};

class Knight : public Enemy
{
    public:
        Knight(int hp, 
                sf::Vector2f speed, 
                sf::Vector2f position, 
                sf::Vector2f scale, 
                sf::Texture*);
        //void update(sf::Vector2f player_pos, sf::Time tick) override;
};

class Peasant : public Enemy
{
    public:
        Peasant(sf::Vector2f speed, sf::Vector2f position, sf::Vector2f scale, sf::Texture*);
};

#endif
