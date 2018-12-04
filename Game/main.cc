#include "logic.cc"

int main()
{
    sf::RenderWindow window{sf::VideoMode(960, 480), "Hang in there, bud."};
    sf::Texture background_tex;
    sf::Texture player_tex;
    sf::Vector2f speed{3.0, 0.0};
    sf::RectangleShape hitbox{sf::Vector2f{1.0, 1.0}};
    
    if (!background_tex.loadFromFile("tpdog.jpg"))
    {
        return -1;
    }
    if (!player_tex.loadFromFile("icon.jpg"))
    {
        return -1;
    }
    Player p(player_tex, 3, speed, hitbox);   
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
        window.draw(background);
        window.draw(p);
        window.display();
    }
}
