#ifndef LOGIC_H
#define LOGIC_H
#include<vector>
#include <map>
#include<SFML/Graphics.hpp>
/*class Playfield
{
    public:
        sf::Sprite background;
        //std::map<sf::Time, std::list<Enemy> waves;
       
}*/

class Character : public sf::Sprite
{
    public:
        Character(sf::Texture texture, int hp, sf::Vector2f speed, sf::RectangleShape hitbox);
    protected:
        int hp;
        sf::RectangleShape hitbox;
        sf::Vector2f const speed; 
};
class Player : public Character
{
    public:
        Player(sf::Texture texture, int hp, sf::Vector2f speed, 
                sf::RectangleShape hitbox);
        void attack_light();
        void attack_heavy();
        void jump();
};

/*class Enemy : public Character
{
    public:
        Enemy(std::map<char, bool> immunity);
        void resolve_hit();
    protected:
        std::map<char, bool> immunity;
        bool valid_hit();

};

class Knight : public Enemy
{
    public:
        Knight();
        void attack();  
};

class Peasant : public Enemy
{
    public:
        Peasant();
};*/

#endif
