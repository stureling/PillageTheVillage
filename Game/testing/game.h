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
        //virtual void update(sf::Time tick) = 0;
        //virtual void resolve_hit() = 0;
    protected:
        int hp;
        sf::Vector2f const speed; 
};
class Sword : public Entity
{
    public:
        void update(sf::Time tick);

    private:
        bool attack_mode;

};

class Enemy : public Entity
{
    public:
        Enemy(int hp, sf::Vector2f speed);
        //void resolve_hit() override;
        void update(sf::Vector2f player_pos, sf::Time tick);
        sf::Vector2f getPlayerPos();
    protected:
        bool valid_hit();
};
class Player : public Entity
{
    public:
        Player(int hp, sf::Vector2f speed, sf::Texture &texture);
        void player_update(sf::Time time, sf::Event &event_queue, sf::Window &window);
        ~Player();
        void hit(std::vector<Enemy*> Enemy);
        //void attack_light();
        //void attack_heavy();
        //void jump();
    private:
        //bool is_attacking;
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
                sf::Window &window);
    private:
        std::vector<Enemy*> enemies;
        Player* player;
};
#endif
