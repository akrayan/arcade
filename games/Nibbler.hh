//
// Nibbler.hh for  in /home/laurent/rendu/cpp_arcade/games
//
// Made by laurent
// Login   <laurent@epitech.net>
//
// Started on  Fri Apr  7 10:41:27 2017 laurent
// Last update Sun Apr  9 23:38:00 2017 Rayan
//

#ifndef NIBBLER_HH
# define NIBBLER_HH

# include "IGame.hh"

class Nibbler : public IGame
{
private:
  arcade::GetMap                *_map;
  arcade::WhereAmI              *_player;
  arcade::CommandType           _direction;
  arcade::Position              _prev;
  std::string                   _namegame;
  bool                          _isover;
  size_t                        _score;
  size_t			_time;
public:
  Nibbler();
  ~Nibbler();
  bool const &IsEnd(void) const;
  bool const &IsGameOver(void) const;
  size_t const &getScore(void) const;
  size_t const &getTime(void) const;
  void  play(arcade::CommandType);
  arcade::WhereAmI const *getPlayer(void) const;
  arcade::GetMap const *getMap(void) const;
  std::string const &getGameName(void) const;
  arcade::Position const &getFluidMove(int ) const;
  arcade::GetMap        *initMap(size_t level);
  arcade::WhereAmI      *initPlayer();
  void                  turnLeft();
  void                  turnRight();
  void                  turnUp();
  void                  turnDown();
  void                  move(arcade::CommandType);
  bool                  setposApple();
  arcade::WhereAmI      *setnewPlayer(uint16_t);
  void                  collision();
  std::string		readMap(std::string);
  void			NiblEat();
  void			FollowMe();
  void			checkFinish();
};

#endif /* !NIBBLER_HH */
