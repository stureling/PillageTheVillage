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

class Character : public sf::Sprite
{
    public:
        Character(int hp, sf::Vector2f speed, sf::RectangleShape hitbox);
        sf::Vector2f const speed; 
    protected:
        int hp;
        sf::RectangleShape hitbox;
};
class Player : public Character
{
    public:
        Player(int hp, sf::Vector2f speed, 
                sf::RectangleShape hitbox);
        void attack_light();
        void attack_heavy();
        void jump();
};

class Enemy : public Character
{
    public:
        Enemy(int hp, sf::Vector2f speed, sf::RectangleShape hitbox, std::map<char, bool> immunity);
        void resolve_hit();
        virtual void update(sf::Vector2f player_pos);
    protected:
        std::map<char, bool> immunity;
        bool valid_hit();

};

class Knight : public Enemy
{
    public:
        Knight(int hp, sf::Vector2f speed, sf::RectangleShape hitbox);
        void attack();  
    private:
    std::map<char, bool> k_immunity
    {
    {'w', true},
    {'s', false}
    };
        
};
/*
class Peasant : public Enemy
{
    public:
        Peasant();
};*/

#endif
