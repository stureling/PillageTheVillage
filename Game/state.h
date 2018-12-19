#ifndef STATE_H
#define STATE_H
#include "entities.h"
#include <SFML/Graphics.hpp>
#include <map>
#include <string>

class Engine
{
    friend class WinState;
    friend class GameOver;
    friend class MenuState;
    friend class PlayState;
public:
    Engine();
    void run();
    sf::RenderWindow window;
private:
    void switchPlay(sf::RenderWindow &window, int &stateNum);
    void switchMenu(sf::RenderWindow &window, int &stateNum);
    void switchGO(sf::RenderWindow &windows, int &stateNum);
    void switchWin(sf::RenderWindow &window, int &stateNum);
    std::map<std::string, sf::Texture> bgs;
};

class State
{
    friend class Engine;
public:
    State(sf::Texture &background, sf::RenderWindow &window);
    void window_resize(sf::RenderWindow &window);
protected:
    sf::Sprite bg;
};

class MenuState : public State
{
public:
    MenuState(sf::Texture &background, sf::RenderWindow &window);
    void update(sf::Event &event,
            sf::RenderWindow &window,
            int &stateNum);
};

class GameOver : public State 
{
public:
    GameOver(sf::Texture &background, sf::RenderWindow &window);
    void update(sf::Event &event_queue,
            sf::RenderWindow &window,
            int &stateNum);
};

class WinState : public State
{
public:
    WinState(sf::Texture &background, sf::RenderWindow &window);
    void update(sf::Event &event_queue,
                sf::RenderWindow &window,
                int &stateNum);
};


class PlayState : public State
{
    friend class Engine;
    public:
        PlayState(sf::Texture &background, sf::RenderWindow &window);
        void addEnemy(Enemy* entity);
        void setPlayer(Player* player);
        void update(sf::Time time, 
                sf::Event &event, 
                sf::RenderWindow &window,
                int &stateNum,
                sf::Text &score,
                std::vector<std::vector<Enemy*>> waves);
    private:
        std::vector<Enemy*> enemies;
        Player* player;
        unsigned total_points;
        sf::Clock wave_timer;
        unsigned current_wave;
};

class Wave
{
    friend class PlayState;
    public:
        Wave(sf::Vector2f p_speed,sf::Vector2f k_speed, float playheight, sf::Vector2f scale, sf::Texture &p_texture, sf::Texture &k_texture);
        std::vector<std::vector<Enemy*>> waves;
        
};


#endif
