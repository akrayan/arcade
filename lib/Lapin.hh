//
// Created by dupeg on 11/03/17.
//

#ifndef CPP_ARCADE_LAPIN_HH
#define CPP_ARCADE_LAPIN_HH

#include <string.h>
#include <vector>
#include <dlfcn.h>
#include <dirent.h>
#include <sstream>
#include <lapin.h>
#include <SFML/Graphics.hpp>
#include "IGraph.hh"
#include "../games/Protocol.hpp"
#include "../Leaderboard.hh"

#define	POSMX 50
#define	POSMY 100
#define	SIZTX 25
#define	SIZTY 25

#define	BOXLARGE 4
#define	BOXHEIGHT 4

#define	WIN_HEIGHT 1080
#define	WIN_LARGE 1920


struct bunny_window {
  size_t type;
  sf::RenderWindow *window;
  ssize_t width;
  ssize_t height;
  const char *window_name;

};

class				Lapin : public IGraph
{
  int				indexGame;
  std::vector<std::string>	listGame;
  t_bunny_pixelarray    *pix;
  t_bunny_pixelarray    *background;
  t_bunny_window        *win;
  t_bunny_position      p;
  t_bunny_pixelarray    *font;
  std::vector<t_bunny_pixelarray *>	listTile;
  std::vector<t_bunny_pixelarray *>	listChar;
  std::string			name;
  std::string			buff;
  sf::Event event;
  t_bunny_music			*music;
  bool				setScore;
  Leaderboard	*_leaderboard;

public:
  Lapin();
  ~Lapin();

  void showInterface(IGame *);
  void showGame(IGame *);
  void showMenu();
  void initBox();
  void b_clear();
  void draw_tile(t_bunny_pixelarray *tile, t_bunny_position p);
  void draw_str(std::string s, int x, int y);
  void init_font();
  void showEnd(IGame *G);
  std::string getSelectGame(arcade::CommandType);
  arcade::CommandType pollEvent(void);
  void initTexture(std::string gameName);
};

#endif //CPP_ARCADE_IGRAPH_HH
