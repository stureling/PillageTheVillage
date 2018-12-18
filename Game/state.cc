//
// Created by agnha531 on 12/12/18.
//

#include "state.h"

//ENGINE FUNCTIONS
Engine::Engine()
: window{sf::VideoMode(1280, 720), "Hang in there, bud"}, bgs{}
{
    window.setVerticalSyncEnabled(true);
    window.setKeyRepeatEnabled(false);
    window.setMouseCursorVisible(false);
}
void Engine::run()
{
    int stateNum{1};
    sf::Texture menu_tex, go_tex, win_tex, play_tex;
    menu_tex.loadFromFile("static/bg/menu.png");
    bgs.emplace(std::make_pair(std::string("Menu"), sf::Texture (menu_tex)));

    play_tex.loadFromFile("static/bg/playfield.png");
    bgs.emplace(std::make_pair(std::string("Play"), sf::Texture (play_tex)));

    go_tex.loadFromFile("static/bg/go.png");
    bgs.emplace(std::make_pair(std::string("GO"), sf::Texture (go_tex)));

    win_tex.loadFromFile("static/bg/monster.png");
    bgs.emplace(std::make_pair(std::string("Win"), sf::Texture (win_tex)));

    while(stateNum == 1) {
        switchMenu(window, stateNum);
    }
    while (stateNum == 2) {
        switchPlay(window, stateNum);
    }
    while (stateNum == 3){
        switchGO(window, stateNum);
    }
    while (stateNum == 4) {
        switchWin(window, stateNum);
    }
}
//SWITCH
void Engine::switchMenu(sf::RenderWindow &window, int &stateNum)
{
    sf::Event event{};
    sf::Texture bg{bgs.at("Menu")};
    sf::Sprite bag;
    MenuState menu{bg, window};

    while(stateNum == 1) {

        menu.update(event, window, stateNum);
        window.display();
    }
}
void Engine::switchPlay(sf::RenderWindow &window, int &stateNum)
{
    PlayState playstate{bgs.at("Play"), window};

    sf::Texture player_tex, peasant_tex, knight_tex, sword_tex;
    player_tex.loadFromFile("static/textures/player.png");
    peasant_tex.loadFromFile("static/textures/peasant.png");
    knight_tex.loadFromFile("static/textures/knight.png");
    sword_tex.loadFromFile("static/textures/Sword-1.png");

    sf::Vector2f scale{0.3f, 0.3f};
    float playheight{770};

    Player p{3, sf::Vector2f{500.f, 0.f}, sf::Vector2f{200.f, playheight}, scale, &player_tex, &sword_tex};
    Peasant e{sf::Vector2f{50.f, 0.f}, sf::Vector2f{600.f, playheight}, scale, &peasant_tex};
    Peasant e1{sf::Vector2f{50.f, 0.f}, sf::Vector2f{650.f, playheight}, scale, &peasant_tex};
    Knight k{2, sf::Vector2f{30.f, 0.f}, sf::Vector2f{10.f, playheight}, scale, &knight_tex};
    Knight k1{2, sf::Vector2f{30.f, 0.f}, sf::Vector2f{10.f, playheight}, scale, &knight_tex};

    playstate.setPlayer(&p);
    playstate.addEnemy(&e);
    playstate.addEnemy(&e1);
    playstate.addEnemy(&k);
    playstate.addEnemy(&k1);
    sf::Clock clock;
    sf::Event event{};
    while(stateNum == 2)
    {
        sf::Time elapsed = clock.restart();
        playstate.update(elapsed, event, window, stateNum);
        window.display();
    }

}
void Engine::switchGO(sf::RenderWindow &window, int &stateNum)
{
    sf::Event event{};
    sf::Texture bg{bgs.at("GO")};
    GameOver g{bg, window};
    while(stateNum == 3) {
        g.update(event, window, stateNum);
        window.display();
    }
}
void Engine::switchWin(sf::RenderWindow &window, int &stateNum) {

    sf::Event event{};
    sf::Texture bg{bgs.at("Win")};
    WinState w{bg, window};
    while (stateNum == 4) {
        w.update(event, window, stateNum);
        window.display();
    }
}

//STATE CONSTRUCTOR
State::State(sf::Texture &background, sf::RenderWindow &window)
{
    bg.setTexture(background);
}
MenuState::MenuState(sf::Texture &background, sf::RenderWindow &window)
    :State{background, window}{}

GameOver::GameOver(sf::Texture &background, sf::RenderWindow &window)
    :State{background, window}{}

WinState::WinState(sf::Texture &background, sf::RenderWindow &window)
    :State{background, window}{}

PlayState::PlayState(sf::Texture &background, sf::RenderWindow &window)
    :State{background, window}
{
    bg.setPosition(0.f, -250.f);
}

//UPDATE
void MenuState::update(sf::Event &event_queue, sf::RenderWindow &window, int &stateNum) {
    window_resize(window);
    window.clear(sf::Color(0, 0, 0, 255));
    window.draw(bg);
    while (window.pollEvent(event_queue)) {
        if (event_queue.type == sf::Event::KeyReleased
            && event_queue.key.code == sf::Keyboard::Num1) {
            stateNum = 2;
        }
        else if (event_queue.type == sf::Event::KeyReleased
                 && event_queue.key.code == sf::Keyboard::Num2) {
            window.close();
            stateNum = 0;
        }

    }
}

void GameOver::update(sf::Event &event_queue, sf::RenderWindow &window, int &stateNum) {
    window_resize(window);
    window.clear(sf::Color(0, 0, 0, 255));
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
    window_resize(window);
    window.clear(sf::Color(0, 0, 0, 255));
    window.draw(bg);
    while (window.pollEvent(event_queue)) {
        if (event_queue.type == sf::Event::KeyReleased
            && event_queue.key.code == sf::Keyboard::Return) {
            stateNum = 1;
        }
    }
}

void PlayState::update(sf::Time time, 
        sf::Event &event, 
        sf::RenderWindow &window,
        int &stateNum)
{
    window_resize(window);
    window.clear(sf::Color(0, 0, 0, 255));
    window.draw(bg);
    player->player_update(time, event, window, enemies, stateNum);
    player->hit(enemies);
    for(Enemy* e : enemies)
    {
        e->update(player->getPosition(), time);
        window.draw(*e);
    }
    enemies.erase(
    std::remove_if(
        enemies.begin(),
        enemies.end(),
        [](Enemy* const & c) { return c->get_hp() <= 0; }),
    enemies.end());
}
//STATE FUNCTIONS
void State::window_resize(sf::RenderWindow &window)
{
    sf::Vector2u valid_aspect{window.getSize().x, (window.getSize().x / 18) * 10};
    window.setSize(valid_aspect);
    bg.setScale(1, 1);
}


//PLAYSTATE FUNCTIONS
void PlayState::addEnemy(Enemy* enemy)
{
    enemies.push_back(enemy);
}

void PlayState::setPlayer(Player* entity)
{
    player = entity;
}
