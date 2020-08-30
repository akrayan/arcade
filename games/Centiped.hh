//
// Centiped.hh for Centiped.hh in /home/afou_n/cpp_arcade
//
// Made by Afou Nacerdine
// Login   <nacerdine.afou@epitech.net>
//
// Started on  Fri Mar 31 12:43:34 2017 Afou Nacerdine
// Last update Sun Apr  9 23:37:30 2017 Rayan
//

#ifndef CENTIPED_HH
# define CENTIPED_HH

#include "IGame.hh"
#include <vector>

#define	MSX 20
#define	MSY 30

#define NBVO 5

#define MAXC 10

#define	SPEEDSHOOT 1

enum			dir
  {
    UP,
    DOWN,
    LEFT,
    RIGHT
  };

typedef struct		s_evilDude
{
  dir			droiteGauche;
  int			upDown;
  int			x;
  int			y;
}			evilDude;

typedef struct		s_obstacle
{
  int			vie;
  int			x;
  int			y;
}			obstacle;

class	Centiped : public IGame
{
private:
  arcade::GetMap		*_map;
  arcade::WhereAmI		*_player;
  arcade::CommandType		_direction;
  arcade::Position		*_shoot;
  std::string			_namegame;
  bool				_isover;
  bool				_isend;
  size_t       			_score;
  std::vector<obstacle>		listObstacle;
  std::vector<std::vector<evilDude>>	listCentiped;
  int		freeze;
  int		nbCentipede;

public:
  Centiped();
  ~Centiped();

  bool const &IsEnd(void) const;
  bool const &IsGameOver(void) const;
  size_t const &getScore(void) const;
  void  play(arcade::CommandType);
  arcade::WhereAmI const *getPlayer(void) const;
  arcade::GetMap const *getMap(void) const;
  std::string const &getGameName(void) const;
  arcade::Position const &getFluidMove(int ) const;
  void		initMap();
  void		initPlayer();
  void		creatCentiped();
  void		moveCentiped();
  void		checkHitCentiped();
  void		hitBlock(int x, int y, int nb);
  void		checkList();
};

#endif /* !CENTIPED_HH */
