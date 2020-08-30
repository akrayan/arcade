//
// Created by dupeg on 11/03/17.
//

#ifndef CPP_ARCADE_SFML_HH
#define CPP_ARCADE_SFML_HH

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <string.h>
#include <vector>
#include <dlfcn.h>
#include <dirent.h>
#include <sstream>
#include "IGraph.hh"
#include "../games/Protocol.hpp"
#include "../Leaderboard.hh"

#define	POSMX 50
#define	POSMY 100
#define	SIZTX 30
#define	SIZTY 30

#define	BOXLARGE 4
#define	BOXHEIGHT 4

#define	WIN_HEIGHT 1080
#define	WIN_LARGE 1920

class				Sfml : public IGraph
{
  int				indexGame;
  std::vector<std::string>	listGame;
  //std::vector<sf::RectangleShape>	Head;
  sf::RenderWindow		*window;
  sf::RectangleShape		tabTexture[13];
  sf::Texture			tabText[13];
  sf::Texture			boxText[8];
  sf::Texture			background;
  sf::Font			ftext;
  sf::Font			ftitle;
  std::string			name;
  std::string			buff;
  sf::Event			event;
  sf::Music			music;
  bool				gameLaunched;
  bool				setScore;
  bool				multDir;
  arcade::CommandType		com;
  Leaderboard			*_leaderboard;
  int				posx;
  int				posy;

public:
  Sfml();
  ~Sfml();

  void showInterface(IGame *);
  void showGame(IGame *);
  void showEnd(IGame *);
  void showMenu();
  void	initBox();
  std::string getSelectGame(arcade::CommandType);
  arcade::CommandType pollEvent(void);
  void initTexture(std::string gameName);
};

#endif //CPP_ARCADE_IGRAPH_HH
