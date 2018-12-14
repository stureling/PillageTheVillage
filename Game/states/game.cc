//
// Created by agnha531 on 12/12/18.
//

#include "State.h"

//ENGINE FUNCTIONS
Engine::Engine()
: window{sf::VideoMode(1920, 1080), "Hang in there, bud"}, bgs{}
{
    window.setVerticalSyncEnabled(true);
}
void Engine::run()
{
    int stateNum{1};
    sf::Texture menu_tex;
    menu_tex.loadFromFile("../static/bg/menu.png");
    bgs.emplace(std::make_pair(std::string("Menu"), sf::Texture (menu_tex)));

    sf::Texture go_tex;
    go_tex.loadFromFile("../static/bg/go.png");
    bgs.emplace(std::make_pair(std::string("GO"), sf::Texture (go_tex)));

    sf::Texture win_tex;
    go_tex.loadFromFile("../static/bg/monster.png");
    bgs.emplace(std::make_pair(std::string("Win"), sf::Texture (go_tex)));

    while(stateNum == 1) {
        switchMenu(window, stateNum);
    }
    while (stateNum == 3){
        switchGO(window, stateNum);
    }

    while (stateNum == 4) {
        switchWin(window, stateNum);
    }
}
//SWITCH
void Engine::switchPlay()
{}
void Engine::switchMenu(sf::RenderWindow &window, int &stateNum)
{
    sf::Event event{};
    sf::Texture bg{bgs.at("Menu")};
    sf::Sprite bag;
    MenuState menu{bg};

    while(stateNum == 1) {

        menu.update(event, window, stateNum);
        window.display();
    }
}
void Engine::switchGO(sf::RenderWindow &window, int &stateNum)
{
    sf::Event event{};
    sf::Texture bg;
    bg = bgs.at("GO");
    GameOver g{bg};
    while(stateNum == 3) {
        g.update(event, window, stateNum);
        window.display();
    }
}
void Engine::switchWin(sf::RenderWindow &window, int &stateNum) {

    sf::Event event{};
    sf::Texture bg;
    bg = bgs.at("Win");
    WinState w{bg};
    while (stateNum == 4) {
        w.update(event, window, stateNum);
        window.display();
    }
}

//STATE CONSTRUCTOR
State::State(sf::Texture &background)
{
    bg.setTexture(background);
}
MenuState::MenuState(sf::Texture &background)
:State{background}{}

GameOver::GameOver(sf::Texture &background)
:State{background}{}

WinState::WinState(sf::Texture &background)
        : State{background}{}

//UPDATE
void MenuState::update(sf::Event &event_queue, sf::RenderWindow &window, int &stateNum) {
    window.clear(sf::Color(0, 200, 0, 255));
    window.draw(bg);
    while (window.pollEvent(event_queue)) {
        if (event_queue.type == sf::Event::KeyReleased
            && event_queue.key.code == sf::Keyboard::Num1) {
            stateNum = 3;
        }
        else if (event_queue.type == sf::Event::KeyReleased
                 && event_queue.key.code == sf::Keyboard::Num2) {
            window.close();
            stateNum = 0;
        }

    }
}

void GameOver::update(sf::Event &event_queue, sf::RenderWindow &window, int &stateNum) {
    window.clear(sf::Color(0, 0, 200, 255));
    window.draw(bg);
    while (window.pollEvent(event_queue)) {
        if (event_queue.type == sf::Event::KeyReleased
            && event_queue.key.code == sf::Keyboard::Escape) {
            stateNum = 1;
        }
        else if (event_queue.type == sf::Event::KeyReleased
                 && event_queue.key.code == sf::Keyboard::Return) {
            stateNum = 4;
        }
    }
}

void WinState::update(sf::Event &event_queue, sf::RenderWindow &window, int &stateNum) {
    window.clear(sf::Color(0, 0, 200, 255));
    window.draw(bg);
    while (window.pollEvent(event_queue)) {
        if (event_queue.type == sf::Event::KeyReleased
            && event_queue.key.code == sf::Keyboard::Return) {
            stateNum = 1;
        }
    }
}

int main() {
Engine engine{};
    while (engine.window.isOpen()) {
        engine.run();
    }
}



