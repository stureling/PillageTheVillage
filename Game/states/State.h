//
// Created by agnha531 on 12/12/18.
//

#ifndef STATES_STATE_H
#define STATES_STATE_H
#include <SFML/Graphics.hpp>
#include "game.h"
#include <map>
#include <string>

class Engine
{
    friend class WinState;
    friend class GameOver;
    friend class MenuState;
public:
    Engine();
    void run();
    sf::RenderWindow window;
private:
    void switchPlay();
    void switchMenu(sf::RenderWindow &window, int &stateNum);
    void switchGO(sf::RenderWindow &windows, int &stateNum);
    void switchWin(sf::RenderWindow &window, int &stateNum);
    std::map<std::string, sf::Texture> bgs;

};

class State{
public:
    State(sf::Texture &background);
protected:
    sf::Sprite bg;
};

class MenuState : public State{
public:
    MenuState(sf::Texture &background);
    void update(sf::Event &event,
            sf::RenderWindow &window,
            int &stateNum);
};

class GameOver : public State {
public:
    GameOver(sf::Texture &background);
    void update(sf::Event &event_queue,
            sf::RenderWindow &window,
            int &stateNum);
};

class WinState : public State{
public:
    WinState(sf::Texture &background);
    void update(sf::Event &event_queue,
                sf::RenderWindow &window,
                int &stateNum);
};

#endif //STATES_STATE_H
