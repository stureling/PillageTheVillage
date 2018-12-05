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


//GAME STATES
int PlayState()
{
    sf::RenderWindow window{sf::VideoMode(960, 480), "Hang in there, bud."};
    sf::Texture background_tex;
    sf::Texture player_tex;
    sf::Vector2f speed{4.0, 0.0};
    sf::RectangleShape hitbox{sf::Vector2f{1.0, 1.0}};
    
    if (!background_tex.loadFromFile("static/textures/tpdog.jpg"))
    {
        return -1;
    }
    if (!player_tex.loadFromFile("static/textures/player.png"))
    {
        return -1;
    }
    sf::Sprite background{background_tex};
    Player p(player_tex, 3, speed, hitbox);   
    p.setPosition(sf::Vector2f{50.f, 40.f});
    p.setTexture(player_tex);
    window.setVerticalSyncEnabled(true);
    while(window.isOpen())
    {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
            {
                p.move(speed);
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
            {
                p.move(-speed.x, speed.y);
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::J))
            {
                p.attack_light();
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
            {
                window.close();
            }

            window.draw(background);
            window.draw(p);
            window.display();
    }
    return 1; 

};

void MenuState()
{

};

//GAME MAIN

int Game();
