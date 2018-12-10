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
        virtual void update(sf::Time tick) = 0;
        //virtual void resolve_hit() = 0;
    protected:
        int hp;
        sf::Vector2f const speed; 
};
class Player : public Entity
{
    public:
        Player(int hp, sf::Vector2f speed, sf::Texture &texture);
        void update(sf::Time tick);
        //void attack_light();
        //void attack_heavy();
        //void jump();
    private:
        //bool is_attacking;
};
class Sword : public Entity
{
    public:

    private:

};

class Enemy : public Entity
{
    public:
        Enemy(int hp, sf::Vector2f speed);
        //void resolve_hit() override;
        virtual void update(sf::Vector2f player_pos, sf::Time tick);
        sf::Vector2f getPlayerPos();
    protected:
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


class Peasant : public Enemy
{
    public:
        Peasant();
};

class PlayState
{
    public:
        PlayState();
        void addEnemy(Entity* entity);
        void addPlayer(Entity* player);
        void update(sf::Time tick);
    private:
        std::vector<Entity*> enemies;
        Entity* player;
};
#endif
