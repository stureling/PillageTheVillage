//
// Created by agnha531 on 12/12/18.
//

#include "state.h"

//ENGINE FUNCTIONS
Engine::Engine()
: window{sf::VideoMode(1920, 1080), "Hang in there, bud"}, bgs{}
  /**\brief Constructor for Engine.
   *
   *Engine's constructor is responsible for creating the window with the correct resolution. It's also responsible for enabling and disabling window's settings. Finally it creates a map to contain the textures for all the background sprites.
   */
{
    window.setVerticalSyncEnabled(true);
    window.setKeyRepeatEnabled(false);
    window.setMouseCursorVisible(false);
}
void Engine::run()
/**\brief The function that initiates the game and switches between states.
 *
 *Adds all relevant background textures to its map. Uses stateNum to determine which state should be active. Calls the appropriate switch-function to create andrun the desired state.
 */
{
    int stateNum{1};
    sf::Texture menu_tex, go_tex, win_tex, play_tex;
    menu_tex.loadFromFile("static/bg/menu.png");
    bgs.emplace(std::make_pair(std::string("Menu"), sf::Texture (menu_tex)));

    play_tex.loadFromFile("static/bg/playfieldwithframe.png");
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
    /**\brief The function responsible for creating and switching to MenuState.
   *
   *Creates the MenuState and sets it texture by using Engine's map of textures. While the state is active the MenuState's update function is run.
   */
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
  /**\brief The function responsible for creating and switching to PlayState.
   *
   *Creates the PlayState and sets it texture by using Engine's map of textures. While the state is active the PlayState's update function is run.
   */
{
    PlayState playstate{bgs.at("Play"), window};

    sf::Texture player_tex, peasant_tex, knight_tex, sword_tex, heart_tex;
    player_tex.loadFromFile("static/textures/player.png");
    peasant_tex.loadFromFile("static/textures/peasant.png");
    knight_tex.loadFromFile("static/textures/knight.png");
    sword_tex.loadFromFile("static/textures/Sword-1.png");
    heart_tex.loadFromFile("static/textures/heart.png");

    sf::Font point_font{};
    point_font.loadFromFile("static/fonts/Hack-Bold.ttf");

    sf::Vector2f scale{0.3f, 0.3f};
    float playheight{730};

    Player p{3, sf::Vector2f{500.f, 0.f}, sf::Vector2f{200.f, playheight}, scale, player_tex, sword_tex, heart_tex};
    Peasant e{sf::Vector2f{50.f, 0.f}, sf::Vector2f{600.f, playheight}, scale, peasant_tex};
    Peasant e1{sf::Vector2f{50.f, 0.f}, sf::Vector2f{650.f, playheight}, scale, peasant_tex};
    Knight k{2, sf::Vector2f{30.f, 0.f}, sf::Vector2f{10.f, playheight}, scale, knight_tex, sword_tex};

    playstate.setPlayer(&p);
    playstate.addEnemy(&e);
    playstate.addEnemy(&e1);
    playstate.addEnemy(&k);
    sf::Clock clock;
    sf::Event event{};
    sf::Text score{"", point_font, 50};
    score.setPosition(1500.f, 850.f);
    score.setScale(2.f, 2.f);
    while(stateNum == 2)
    {
        sf::Time elapsed = clock.restart();
        playstate.update(elapsed, event, window, stateNum, score);
        window.display();
    }

}
void Engine::switchGO(sf::RenderWindow &window, int &stateNum)
  /**\brief The function responsible for creating and switching to GameOverState.
   *
   *Creates the GameOverState and sets it texture by using Engine's map of textures. While the state is active the GameOverState's update function is run.
   */
{
    sf::Event event{};
    sf::Texture bg{bgs.at("GO")};
    GameOver g{bg, window};
    while(stateNum == 3) {
        g.update(event, window, stateNum);
        window.display();
    }
}

void Engine::switchWin(sf::RenderWindow &window, int &stateNum)
  /**\brief The function responsible for creating and switching to WinState.
   *
   *Creates the WinState and sets it texture by using Engine's map of textures. While the state is active the WinState's update function is run.
   */
{
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
  /**\brief State's constructor. 
   *
   *Sets texture for the background sprite and causes the dimensionens of the window to keep a ratio of 16:9 regardless oc scaling.
   */
{
    sf::Vector2u valid_aspect{window.getSize().x, (window.getSize().x / 18) * 10};
    window.setSize(valid_aspect);
    bg.setTexture(background);
}
MenuState::MenuState(sf::Texture &background, sf::RenderWindow &window)
    :State{background, window}{}

GameOver::GameOver(sf::Texture &background, sf::RenderWindow &window)
    :State{background, window}{}

WinState::WinState(sf::Texture &background, sf::RenderWindow &window)
    :State{background, window}{}

PlayState::PlayState(sf::Texture &background, sf::RenderWindow &window)
    :State{background, window}, total_points{}{}

//UPDATE
void MenuState::update(sf::Event &event_queue, sf::RenderWindow &window, int &stateNum) 
    /** \brief A function to update the game while in MenuState.
     *
     * Draws the background image. Takes in keyboard input to either switch to the PlayState or close the game. Trigger switching of states by changing the value of stateNum.
     */
{
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

void GameOver::update(sf::Event &event_queue, sf::RenderWindow &window, int &stateNum) 
    /** \brief A function to update the game while in GameOverState.
     *
     *  Draws the background image. Takes in keyboard input to switch to MenuState. Triggers switching of states by changing the value of stateNum.
     */
{
    window_resize(window);
    window.clear(sf::Color(0, 0, 0, 255));
    window.draw(bg);
    while (window.pollEvent(event_queue)) {
        if (event_queue.type == sf::Event::KeyReleased
            && event_queue.key.code == sf::Keyboard::Return)
	  {
            stateNum = 1;
	  }
    }
}

void WinState::update(sf::Event &event_queue, sf::RenderWindow &window, int &stateNum) 
    /** \brief A function to update the game while in WinState.
     *
     *  Draws the background image. Takes in keyboard input to switch to MenuState. Triggers switching of states by changing the value of stateNum.
     */
{
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

void PlayState::update(sf::Time time, sf::Event &event, sf::RenderWindow &window, int &stateNum, sf::Text &score)
    /** \brief Detta är en kort beskrivning.
     *
     * Detta är en detaljerad kommentar
     */
{
    window_resize(window);
    window.clear(sf::Color(0, 0, 0, 255));
    window.draw(bg);
    player->hit(enemies);
    player->player_update(time, event, window, enemies, stateNum);
    for(Enemy* e : enemies)
    {
        e->update(player->getPosition(), time);
        window.draw(*e);
        if(e->get_hp() <= 0)
        {
            total_points += e->get_points();
        }
    }
    enemies.erase(std::remove_if(
                enemies.begin(),
                enemies.end(),
                [](Enemy* const & c) { return c->get_hp() <= 0; }),
                enemies.end());
    score.setString(std::to_string(total_points));
    window.draw(score);
    if (enemies.size() == 0)
    {
        stateNum =4;
    }
}
//STATE FUNCTIONS
void State::window_resize(sf::RenderWindow &window)
    /** \brief Controls the scaling of the window.
     *
     * Keeps the window at a constant ratio of 16:9 regardless of scaling.
     */
{
    sf::Vector2u valid_aspect{window.getSize().x, (window.getSize().x / 18) * 10};
    window.setSize(valid_aspect);
    bg.setScale(1, 1);
}


//PLAYSTATE FUNCTIONS
void PlayState::addEnemy(Enemy* enemy)
    /** \brief Adds an Enemy object to a vector.
     *
     * Inserts the Enemy object at the beginning of the vector.
     */
{
    enemies.push_back(enemy);
}

void PlayState::setPlayer(Player* entity) //WHAT DOES THIS DOOO?
    /** \brief Adds an Player object to the PlayState vector.
     *
     * Inserts the Player object at the beginning of the vector.
     */
{
    player = entity;
}

//PLAYFIELD
Playfield::Playfield()
{}
