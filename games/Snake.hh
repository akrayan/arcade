//
// Snake.hh for Snake.hh in /home/afou_n/cpp_arcade
//
// Made by Afou Nacerdine
// Login   <nacerdine.afou@epitech.net>
//
// Started on  Fri Mar 31 12:43:34 2017 Afou Nacerdine
// Last update Sun Apr  9 23:37:43 2017 Rayan
//

#ifndef SNAKE_HH
# define SNAKE_HH

#include "IGame.hh"

class	Snake : public IGame
{
private:
  arcade::GetMap		*_map;
  arcade::WhereAmI		*_player;
  arcade::CommandType		_direction;
  arcade::Position		_prev;
  arcade::Position		_posapple;
  std::string			_namegame;
  bool				_isover;
  size_t			_score;
public:
  Snake();
  ~Snake();
  bool const &IsEnd(void) const;
  bool const &IsGameOver(void) const;
  size_t const &getScore(void) const;
  void  play(arcade::CommandType);
  arcade::WhereAmI const *getPlayer(void) const;
  arcade::GetMap const *getMap(void) const;
  std::string const &getGameName(void) const;
  arcade::Position const &getFluidMove(int ) const;
  arcade::GetMap	*initMap();
  void			*initPlayer();
  void			turnLeft();
  void			turnRight();
  void			turnUp();
  void			turnDown();
  void			move(arcade::CommandType);
  bool			setposApple();
  arcade::WhereAmI	*setnewPlayer(uint16_t);
  void			collision();
};

#endif /* !SNAKE_HH */
