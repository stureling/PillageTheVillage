#ifndef ENTITIES_H
#define ENTITIES_H
#include <SFML/Graphics.hpp>
#include <iostream>
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
        //virtual void update(sf::Time tick) = 0;
        //virtual void resolve_hit() = 0;
    protected:
        sf::Vector2f const speed; 
        int hp;
};

class Enemy : public Entity
{
    public:
        Enemy(int hp, sf::Vector2f speed, sf::Vector2f position, sf::Vector2f scale, sf::Texture*);
        void hit(char attack_type);
        void update(sf::Vector2f player_pos, sf::Time tick);
    protected:
        bool valid_hit();
};

class Sword : public sf::Sprite
{
    friend class Player;
    friend class Knight;
    public:
        Sword(sf::Vector2f scale, sf::Texture* texture);
        void update(sf::Time tick, std::vector<Enemy*>* enemies, Sprite* holder);
        void light_attack();
        void heavy_attack();
    private:
        int attack_mode;
        sf::Clock timer;

};

class Player : public Entity
{
    public:
        Player(int hp, sf::Vector2f speed, sf::Vector2f position, sf::Vector2f scale, sf::Texture* player_t, sf::Texture* sword_t);
        void player_update(sf::Time time, sf::Event &event_queue, sf::RenderWindow &window, std::vector<Enemy*> &enemies);
        ~Player() override;
        void hit(std::vector<Enemy*> Enemy);
        //void jump();
    private:
        Sword sword;
        sf::Clock timer;

};

class Knight : public Enemy
{
    public:
        Knight(int hp, sf::Vector2f speed, sf::Vector2f position, sf::Vector2f scale, sf::Texture*);
        void attack();  
    private:
    std::map<char, bool> k_immunity
    {
    {'w', true},
    {'s', false}
    };
};


class Peasant : public Enemy
{
    public:
        Peasant(sf::Vector2f speed, sf::Vector2f position, sf::Vector2f scale, sf::Texture*);
};

#endif
