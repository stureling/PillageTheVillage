#include <SFML/Graphics.hpp>



/*void update()
{
    
}*/

int main()
{
    sf::RenderWindow window{sf::VideoMode(1280, 720), "Hang in there, bud."};
    sf::Texture background_tex;
    if (!background_tex.loadFromFile("tpdog.jpg"))
    {
        return -1;
    }
    sf::Sprite background(background_tex);
    sf::Color color{0, 0, 255, 255};
    sf::Color color2{0, 255, 255, 200};
    sf::CircleShape con{90};
    con.setPosition(0.0, 180.0);
    float x_speed{0.0};
    float y_speed{0.0};
    bool jump{false};
    con.setFillColor(color2);
    window.setVerticalSyncEnabled(true);
    sf::Clock clock;
    while (window.isOpen()) 
    {

        //window.draw(con);
        sf::Event event;
        while (window.pollEvent(event))
        {
            window.clear(color);
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
            {
                window.close();
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
            {
                con.move(x_speed+2, y_speed);
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
            {
                con.move(x_speed-2, y_speed);
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && con.getPosition().y == 180.0 )
            {
                jump = true;
            }
            if (jump)
            {
                con.move(x_speed, y_speed-10);
                if (con.getPosition().y < 90.0)
                {
                    jump = false;
                }
            }
            else if (jump == false && con.getPosition().y < 180.0)
            {
                con.move(x_speed, y_speed+5);
            }
            window.draw(background);
            window.draw(con);
            window.display();
            //sf::Event::processEvent(event);
        }
        //update();
    }
    sf::sleep(sf::seconds(5));
    return 0;
}
