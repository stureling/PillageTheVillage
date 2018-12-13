#include "entities.cc"

using namespace std;

class PlayState
{
    public:
        PlayState();
        void addEnemy(Enemy* entity);
        void setPlayer(Player* player);
        void update(sf::Time time, 
                sf::Event &event, 
                sf::RenderWindow &window);
    private:
        std::vector<Enemy*> enemies;
        Player* player;
};

//PLAYSTATE CONSTRUCTOR
PlayState::PlayState() = default;

//PLAYSTATE FUNCTIONS

void PlayState::addEnemy(Enemy* enemy)
{
    enemies.push_back(enemy);
}
void PlayState::setPlayer(Player* entity)
{
    player = entity;
}

void PlayState::update(sf::Time time, 
        sf::Event &event, 
        sf::RenderWindow &window)
{
    window.clear(sf::Color(0, 200, 0, 255));
    for(vector<Enemy*>::iterator it = enemies.begin(); it != enemies.end(); it++)
    {
        Enemy* e = *it;
        //e->update(player->getPosition(), time);
        if (e->get_hp() <= 0)
        {
            enemies.erase(it);
        }
        window.draw(*e);
    }
    player->player_update(time, event, window, enemies);
    player->hit(enemies);
}


//TEMPORARY MAIN
int main()
{
    sf::RenderWindow window(sf::VideoMode(960,480), "Hang in there, bud");

    //Load textures
    sf::Texture player_t, peasant_t, knight_t, sword_t;
    player_t.loadFromFile("static/textures/player.png");
    peasant_t.loadFromFile("static/textures/peasant.png");
    knight_t.loadFromFile("static/textures/knight.png");
    sword_t.loadFromFile("static/textures/Sword-1.png");

    sf::Vector2f scale{0.3f, 0.3f};
    Player p{3, sf::Vector2f{500.f, 0.f}, sf::Vector2f{200.f, 200.f}, scale, &player_t, &sword_t};
    
    Peasant e{sf::Vector2f{50.f, 0.f}, sf::Vector2f{600.f, 200.f}, scale, &peasant_t};

    Knight k{2, sf::Vector2f{30.f, 0.f}, sf::Vector2f{0.f, 200.f}, scale, &knight_t};


    //Setup playfield and run game
    PlayState playstate{};
    playstate.setPlayer(&p);
    playstate.addEnemy(&e);
    playstate.addEnemy(&k);
    sf::Clock clock;
    sf::Event event{};
    window.setVerticalSyncEnabled(true);
    while(window.isOpen())
    {
        sf::Time elapsed = clock.restart();
        playstate.update(elapsed, event, window);
        window.display();
    }
}
