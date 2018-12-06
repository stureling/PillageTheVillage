#ifndef LOGIC_H
#define LOGIC_H
#include <vector>
#include <map>
#include <SFML/Graphics.hpp>
#include <iostream>
/*class Playfield
{
    public:
        sf::Sprite background;
        //std::map<sf::Time, std::list<Enemy> waves;
       
}*/

class Entity : public sf::Sprite
{
    public:
        Entity(int hp, sf::Vector2f speed);
        //virtual void timed_move();
        //virtual void resolve_hit();
        sf::Vector2f const speed; 
    protected:
        int hp;
};
class Player : public Entity
{
    public:
        Player(int hp, sf::Vector2f speed);
        //void timed_move() override;
        void attack_light();
        void attack_heavy();
        void jump();
};

class Enemy : public Entity
{
    public:
        Enemy(int hp, sf::Vector2f speed, std::map<char, bool> immunity);
        //void resolve_hit() override;
        virtual void update(sf::Vector2f player_pos, sf::Time tick);
    protected:
        std::map<char, bool> immunity;
        bool valid_hit();
};

class Knight : public Enemy
{
    public:
        Knight(int hp, sf::Vector2f speed);
        void attack();  
    private:
    std::map<char, bool> k_immunity
    {
    {'w', true},
    {'s', false}
    };
};
class Sword : public Entity
{
    public:

    private:

};
/*
class Peasant : public Enemy
{
    public:
        Peasant();
};*/

#endif
