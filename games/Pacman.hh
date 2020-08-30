//
// Pacman.hh for Pacman.hh in /home/afou_n/tek2/c++/projets/cpp_arcade
//
// Made by Afou Nacerdine
// Login   <nacerdine.afou@epitech.eu>
//
// Started on  Wed Apr  5 14:18:54 2017 Afou Nacerdine
// Last update Sun Apr  9 23:38:18 2017 Rayan
//

#ifndef PACMAN_HH
# define PACMAN_HH

# include "IGame.hh"

class	Pacman : public IGame
{
private:
  struct	Evil
  {
    arcade::TileType	stat;
    arcade::Position	position;
  };
  arcade::GetMap		*_map;
  arcade::GetMap		*_mapinitial;
  arcade::WhereAmI		*_player;
  std::string			_namegame;
  bool				_isover;
  size_t			_vulnerable;
  size_t			_score;
  size_t			_lives;
  arcade::CommandType		_prev;
  std::vector<Evil>		_evils;
  bool				_restart;
  int				_wait;
public:
  Pacman();
  ~Pacman();
  bool const &IsEnd(void) const;
  bool const &IsGameOver(void) const;
  size_t const &getScore(void) const;
  void  play(arcade::CommandType);
  arcade::WhereAmI const *getPlayer(void) const;
  arcade::GetMap const *getMap(void) const;
  std::string const &getGameName(void) const;
  arcade::Position const &getFluidMove(int ) const;
  arcade::GetMap	*initMap();
  arcade::WhereAmI	*initPlayer();
  std::vector<Evil>	initEvil();
  arcade::GetMap	*copyMap(arcade::GetMap *oldMap);
  void			setEvilmap();
  std::string		readMap();
  void			movePlayer(arcade::CommandType);
  void			pacEat();
  bool			checkEatAll();
  void			moveAi();
  void			isVulnerable();
  void			resetGame();
  void			aiRandomOne(int y);
  void			aiRandomTwo(int y);
  void			aiRandomThree(int y);
  void			aiRandomFour(int y);
  void			outAiOne(int reset);
  void			outAiTwo(int reset);
  void			outAiThree(int reset);
  void			outAiFour(int reset);
  void			begininGame(int reset);
};

#endif /* !PACMAN_HH */
