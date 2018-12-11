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
        //std::map<sf::Time, std::vector<Enemy> waves;
       
}*/


class Entity : public sf::Sprite
{
    public:
        Entity(int hp, sf::Vector2f speed);
        //virtual void update(sf::Time tick) = 0;
        //virtual void resolve_hit() = 0;
    protected:
        sf::Vector2f const speed; 
        int hp;
};

class Enemy : public Entity
{
    public:
        Enemy(int hp, sf::Vector2f speed);
        //void resolve_hit() override;
        void update(sf::Vector2f player_pos, sf::Time tick);
    protected:
        bool valid_hit();
};

class Sword : public sf::Sprite
{
    public:
        Sword();
        void update(sf::Time tick, std::vector<Enemy*> enemies);
        void light_attack();
        void heavy_attack();
    private:
        bool attack_mode;

};

class Player : public Entity
{
    public:
        Player(int hp, sf::Vector2f speed, sf::Texture &player_t, sf::Texture &sword_t);
        void player_update(sf::Time time, sf::Event &event_queue, sf::RenderWindow &window);
        void move_player(sf::Vector2f, sf::Time tick);
        ~Player() override;
        void hit(std::vector<Enemy*> Enemy);
        //void jump();
    private:
        Sword sword;
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
        Peasant(sf::Vector2f speed);
};

class PlayState
{
    public:
        PlayState();
        void addEnemy(Enemy* entity);
        void setPlayer(Player* player);
        void update(sf::Time time, 
                sf::Event &event, 
                sf::RenderWindow &window);
    private:
        std::vector<Enemy*> enemies;
        Player* player;
};
#endif
