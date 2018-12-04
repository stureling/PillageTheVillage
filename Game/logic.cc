#include "logic.h"

//CONSTRUCTORS
//CHARACTER
Character::Character(sf::Texture texture, int hp, sf::Vector2f speed, sf::RectangleShape hitbox)
    :hp{hp}, hitbox{hitbox}, speed{speed}
{
    setTexture(texture);
}

//PLAYER
Player::Player(sf::Texture texture, int hp, sf::Vector2f speed, sf::RectangleShape hitbox)
    :Character{texture, hp, speed, hitbox}
{
}

//PLAYER FUNCTIONS
void attack_light(){}
void attack_heavy(){}
void jump(){};

