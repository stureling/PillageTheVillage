#ifndef STATE_H
#define STATE_H
#include "entities.h"

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
  void switchPlay(sf::RenderWindow &window, int &stateNum, unsigned &total_points);
  void switchMenu(sf::RenderWindow &window, int &stateNum) const;
  void switchGO(sf::RenderWindow &windows, int &stateNum, unsigned const &total_points) const;
  void switchWin(sf::RenderWindow &window, int &stateNum, unsigned const &total_points) const;
  std::vector<std::vector<std::shared_ptr<Enemy>>> create_waves(sf::Vector2f p_speed,
								       sf::Vector2f k_speed, 
								       float playheight, 
								       sf::Vector2f scale, 
								       sf::Texture &peasant_tex, 
								       sf::Texture &knight_tex, 
								       sf::Texture &sword_tex);
  std::map<std::string, sf::Texture> bgs;
  unsigned total_points;  
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
	      int &stateNum,
	      sf::Text &score,
	      unsigned const &total_points);
};

class WinState : public State
{
 public:
  WinState(sf::Texture &background, sf::RenderWindow &window);
  void update(sf::Event &event_queue,
	      sf::RenderWindow &window,
	      int &stateNum,
	      sf::Text &score,
	      unsigned const &total_points, 
	      std::map<std::string, sf::Texture> &bgs);
 private:
  sf::Clock timer;
};

class PlayState : public State
{
  friend class Engine;
 public:
  PlayState(sf::Texture &background, sf::RenderWindow &window);
  void addEnemy(std::shared_ptr<Enemy> enemy);
  void setPlayer(Player* player);
  void update(sf::Time time, 
	      sf::Event &event, 
	      sf::RenderWindow &window,
	      int &stateNum,
	      sf::Text &score,
	      std::vector<std::vector<std::shared_ptr<Enemy>>> &waves,
	      unsigned &total_points);
 private:
  std::vector<std::shared_ptr<Enemy>> enemies;
  Player* player;
  sf::Clock timer;
  unsigned current_wave;
};
#endif
