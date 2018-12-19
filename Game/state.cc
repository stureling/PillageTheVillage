#include "state.h"

//ENGINE FUNCTIONS
Engine::Engine()
: window{sf::VideoMode(1920, 1080), "Hang in there, bud"}, bgs{}
  /**\brief Constructor for Engine.
   *
   * Engine's constructor is responsible for creating the window with the correct resolution. 
   * It's also responsible for enabling and disabling window's settings. 
   * Finally it creates a map to contain the textures for all the background sprites.
   */
{
    window.setVerticalSyncEnabled(true);
    window.setKeyRepeatEnabled(false);
    window.setMouseCursorVisible(false);
}
void Engine::run()
/**\brief The function that initiates the game and switches between states.
 *
 * Adds all relevant background textures to its map. Uses stateNum to determine which state should be active. 
 * Calls the appropriate switch-function to create and run the desired state.
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
      switchPlay(window, stateNum, total_points);
    }
    while (stateNum == 3){
      switchGO(window, stateNum, total_points);
    }
    while (stateNum == 4) {
      switchWin(window, stateNum, total_points);
    }
}
//SWITCH
void Engine::switchMenu(sf::RenderWindow &window, int &stateNum)
    /**\brief The function responsible for creating and switching to MenuState.
   *
   * Creates the MenuState and sets it texture by using Engine's map of textures. 
   * While the state is active the MenuState's update function is run.
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
void Engine::switchPlay(sf::RenderWindow &window, int &stateNum, unsigned &total_points)
  /**\brief The function responsible for creating and switching to PlayState.
   *
   * Creates the PlayState and sets the background texture by using Engine's map of textures. 
   * While the state is active the PlayState's update function is run.
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

    Player p{3, 
        sf::Vector2f{500.f, 0.f}, 
        sf::Vector2f{200.f, playheight}, 
        scale, 
        player_tex, 
        sword_tex, 
        heart_tex};

        std::vector<std::vector<std::shared_ptr<Enemy>>> waves;
        waves = create_waves(sf::Vector2f{25.f, 0.f}, sf::Vector2f{15.f, 0.f}, playheight, scale, peasant_tex, knight_tex, sword_tex);
    playstate.setPlayer(&p);
    sf::Clock clock;
    sf::Event event{};
    sf::Text score{"", point_font, 100};
    score.setPosition(1500.f, 850.f);
    score.setScale(1.2f, 1.2f);
    playstate.wave_timer.restart();
    while(stateNum == 2)
    {
        sf::Time elapsed = clock.restart();
        playstate.update(elapsed, event, window, stateNum, score, waves, total_points);
        window.display();
    }

}
void Engine::switchGO(sf::RenderWindow &window, int &stateNum, unsigned const &total_points)
  /**\brief The function responsible for creating and switching to GameOverState.
   *
   * Creates the GameOverState and sets it texture by using Engine's map of textures. 
   * While the state is active the GameOverState's update function is run.
   */
{
    sf::Event event{};
    sf::Texture bg{bgs.at("GO")};
    GameOver g{bg, window};
    sf::Font point_font{};
    point_font.loadFromFile("static/fonts/Hack-Bold.ttf");
    sf::Text score{"", point_font, 100};
    score.setScale(1.f, 1.f);
    score.setPosition(970.f, 775.f);
    
    while(stateNum == 3) 
    {
      g.update(event, window, stateNum, score, total_points);
      window.display();
    }
}

void Engine::switchWin(sf::RenderWindow &window, int &stateNum, unsigned const &total_points)
  /**\brief The function responsible for creating and switching to WinState.
   *
   * Creates the WinState and sets it texture by using Engine's map of textures. 
   * While the state is active the WinState's update function is run.
   */
{
    sf::Event event{};
    sf::Texture bg{bgs.at("Win")};
    WinState w{bg, window};
    sf::Font point_font{};
    point_font.loadFromFile("static/fonts/Hack-Bold.ttf");
    sf::Text score{"", point_font, 50};
    score.setPosition(930.f, 500.f);
    score.setScale(2.f, 2.f);
    
    while (stateNum == 4) {
      w.update(event, window, stateNum, score, total_points);
        window.display();
    }
}

//STATE CONSTRUCTOR
State::State(sf::Texture &background, sf::RenderWindow &window)
  /**\brief State's constructor. 
   *
   * Sets texture for the background sprite and causes the dimensionens of the window to keep a ratio of 16:9 regardless of scaling.
   */
{
    sf::Vector2u valid_aspect{window.getSize().x, (window.getSize().x / 18) * 10};
    window.setSize(valid_aspect);
    bg.setTexture(background);
    float scale = window.getSize().x / bg.getLocalBounds().width;
    bg.setScale(scale, scale);
}
MenuState::MenuState(sf::Texture &background, sf::RenderWindow &window)
    :State{background, window}{}

GameOver::GameOver(sf::Texture &background, sf::RenderWindow &window)
    :State{background, window}{}

WinState::WinState(sf::Texture &background, sf::RenderWindow &window)
    :State{background, window}{}

PlayState::PlayState(sf::Texture &background, sf::RenderWindow &window)
    :State{background, window}, current_wave{0}{}

//UPDATE
void MenuState::update(sf::Event &event_queue, sf::RenderWindow &window, int &stateNum) 
    /** \brief A function to update the game while in MenuState.
     *
     * Draws the background image. 
     * Recieves keyboard input to either switch to the PlayState or close the game. 
     * Trigger switching of states by changing the value of stateNum.
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

void GameOver::update(sf::Event &event_queue, sf::RenderWindow &window, int &stateNum, sf::Text &score, unsigned const &total_points) 
    /** \brief A function to update the game while in GameOverState.
     *
     *  Draws the background image. 
     *  Recieves keyboard input to switch to MenuState. 
     *  Triggers switching of states by changing the value of stateNum.
     */
{
    window_resize(window);
    window.clear(sf::Color(0, 0, 0, 255));
    window.draw(bg);
    score.setString(std::to_string(total_points));
    score.setOrigin(score.getLocalBounds().width/2.f, 0.f);
    window.draw(score);
    while (window.pollEvent(event_queue)) {
        if (event_queue.type == sf::Event::KeyReleased
            && event_queue.key.code == sf::Keyboard::Return)
	  {
            stateNum = 1;
	  }
    }
}

void WinState::update(sf::Event &event_queue, sf::RenderWindow &window, int &stateNum, sf::Text &score, unsigned const &total_points) 
    /** \brief A function to update the game while in WinState.
     *
     *  Draws the background image. 
     *  Recieves keyboard input to switch to MenuState. 
     *  Triggers switching of states by changing the value of stateNum.
     */
{
    window_resize(window);
    window.clear(sf::Color(0, 0, 0, 255));
    window.draw(bg);
    score.setString(std::to_string(total_points));
    score.setOrigin(score.getLocalBounds().width/2.f, 0.f);
    window.draw(score);
    while (window.pollEvent(event_queue)) {
        if (event_queue.type == sf::Event::KeyReleased
            && event_queue.key.code == sf::Keyboard::Return) {
            stateNum = 1;
        }
    }
}

void PlayState::update(sf::Time time, sf::Event &event, sf::RenderWindow &window, int &stateNum, sf::Text &score, std::vector<std::vector<std::shared_ptr<Enemy>>> &waves, unsigned &total_points)
    /** \brief Updates all objects belonging to PlayState and then displays them. Changes the state if win or lose conditions are met.
     *
     * Updates all objects belonging to PlayState and then displays them. 
     * It adds Enemy objects to the playfield at specific intervals.
     * Erases Enemy objects when their health is reduced to 0 and adds the objects points to the variable total_points.
     * Changes the state if win or lose conditions are met.
     */
{
    window_resize(window);
    window.clear(sf::Color(0, 0, 0, 255));
    window.draw(bg);
    player->player_update(time, event, window, enemies, stateNum);

    if (wave_timer.getElapsedTime().asSeconds() > 5.f && waves.size() != current_wave)
    {
        for (unsigned element{}; element < waves[current_wave].size() ; element++)
        {
            enemies.push_back(waves[current_wave][element]);
        }
        current_wave++;
        wave_timer.restart();
    }
    for(unsigned element{}; element < enemies.size() ; element++ )
    {
        std::shared_ptr<Knight> knight = std::dynamic_pointer_cast<Knight>(enemies[element]);
        if( knight )
        {
            knight->update(player, window, time);
            std::cout << "knight" << std::endl;
        }
        else
        {
            enemies[element]->update(player, window, time);
        }
        if(enemies[element]->get_hp() <= 0)
        {
            total_points += enemies[element]->get_points();
        }
    }
    enemies.erase(std::remove_if(
                enemies.begin(),
                enemies.end(),
                [](std::shared_ptr<Enemy> const & c) { return c->get_hp() <= 0;}),
                enemies.end());

    score.setString(std::to_string(total_points));
    window.draw(score);

    if (enemies.size() == 0 && waves.size() == current_wave)
    {
        stateNum = 4;
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
void PlayState::addEnemy(std::shared_ptr<Enemy> enemy)
    /** \brief Adds an Enemy object to a vector.
     *
     * Inserts the Enemy object at the beginning of the vector.
     */
{
    enemies.push_back(enemy);
}

void PlayState::setPlayer(Player* entity) 
    /** \brief Adds a pointer to the Player object in PlayState.
     *
     * Adds a pointer to the Player object in PlayState.
     */
{
    player = entity;
}

std::vector<std::vector<std::shared_ptr<Enemy>>> Engine::create_waves(sf::Vector2f p_speed,sf::Vector2f k_speed, float playheight, sf::Vector2f scale, sf::Texture &peasant_tex, sf::Texture &knight_tex, sf::Texture &sword_tex)
{
    int max_waves{};
    std::map<int, std::vector<int>> enemies{};
    std::ifstream file("playfield.txt");
    if( file.is_open() )
    {
        std::string line;
        std::getline(file,line);
        std::getline(file,line);
        
        max_waves = std::stoi(line);
        for( int linum{0}; linum < 4; linum++ )
        {
            std::getline(file,line);
            std::getline(file,line);
            std::vector<int> v{};
            v.push_back(std::stoi(line));
            std::getline(file,line);
            std::getline(file,line);
            v.push_back(std::stoi(line));
            enemies.emplace(std::pair<int, std::vector<int>>{linum, v});
        }
    }

    std::vector<std::vector<std::shared_ptr<Enemy>>> waves;
    for (int current_wave{}; current_wave < max_waves; current_wave++)
    {
        int knights{enemies.at(current_wave)[0]};
        int peasants{enemies.at(current_wave)[1]};
        std::vector<std::shared_ptr<Enemy>> subwave;
        //Peasants
        for(int i{};i <  peasants; i++)
        {
            int spacing{i};
            if ( spacing % 2 == 0 )
            {
                spacing *= -1;
            }
            std::shared_ptr<Enemy> p = std::make_shared<Enemy>(Peasant{p_speed, 
                    sf::Vector2f{(300.f * spacing + 1920 * spacing), 
                    playheight}, 
                    scale, 
                    peasant_tex});
            subwave.push_back(p);
        }
        //Knights
        for(int i{};i <  knights; i++)
        {
            int spacing{i};
            if ( spacing % 2 == 0 )
            {
                spacing *= -1;
            }
            std::shared_ptr<Knight> p = std::make_shared<Knight>(Knight{k_speed, 
                    sf::Vector2f{(300.f * spacing + 1920 * spacing), playheight}, 
                    scale, 
                    knight_tex,
                    sword_tex});
            subwave.push_back(p);
        }
        waves.push_back(subwave);
    }
    return waves;
}
