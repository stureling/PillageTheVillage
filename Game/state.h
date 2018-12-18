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
    public:
        PlayState(sf::Texture &background, sf::RenderWindow &window);
        void addEnemy(Enemy* entity);
        void setPlayer(Player* player);
        void update(sf::Time time, 
                sf::Event &event, 
                sf::RenderWindow &window,
                int &stateNum,
                sf::Text &score);
    private:
        std::vector<Enemy*> enemies;
        Player* player;
        unsigned total_points;
};

class Playfield
{
    public:
        Playfield();
        std::map<sf::Time, std::vector<Enemy*> wave;
};

#endif
