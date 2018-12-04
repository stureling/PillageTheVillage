#include "logic.h"

//CONSTRUCTORS
//CHARACTER
Character::Character(sf::Texture texture, int hp, sf::Vector2f speed, sf::RectangleShape hitbox)
    :Sprite{texture}, hp{hp}, hitbox{hitbox}, speed{speed}
{
    setTexture(texture);
}

//PLAYER
Player::Player(sf::Texture texture, int hp, sf::Vector2f speed, sf::RectangleShape hitbox)
    :Character{texture, hp, speed, hitbox}
{
}

//PLAYER FUNCTIONS
void Player::attack_light()
{
    std::cout << "Light attack" << std::endl;
}
void Player::attack_heavy()
{

}
void Player::jump()
{

};

