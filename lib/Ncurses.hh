//
// Created by dupeg on 11/03/17.
//

#ifndef CPP_ARCADE_NCURSES_HH
#define CPP_ARCADE_NCURSES_HH

#include <time.h>
#include <term.h>
#include <termios.h>
#include <sys/ioctl.h>
#include <string.h>
#include <unistd.h>
#include <ncurses.h>
#include <dlfcn.h>
#include <dirent.h>
#include <vector>
#include "IGraph.hh"
#include "../Leaderboard.hh"

class Ncurses : public IGraph
{
private:
  WINDOW	*scr;
  struct termios old_term;
  struct termios new_term;
  int				indexGame;
  std::vector<std::string>	listGame;
  bool		setScore;
  int				anim;
  std::string	_name;
  std::string	_buff;
  Leaderboard	*_leaderboard;
  bool	_errorname;
public:
  Ncurses();
  ~Ncurses();

  void showInterface(IGame *);
  void showGame(IGame *);
  void showMenu();
  std::string getSelectGame(arcade::CommandType);
  arcade::CommandType pollEvent(void);
  void initTexture(std::string gameName);
  void mode(bool b);
  void showEnd(IGame *);
};

#endif //CPP_ARCADE_IGRAPH_HH
