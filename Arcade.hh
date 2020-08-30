//
// Arcade.hh for Arcade.hh in /home/rayan/CPP/cpp_arcade
//
// Made by Rayan
// Login   <raihane.akkache@epitech.net>
//
// Started on  Mon Apr  3 16:26:56 2017 Rayan
// Last update Sun Apr  9 23:37:14 2017 Rayan
//

#ifndef	ARCADE_HH_
# define ARCADE_HH_

#include <iostream>
#include <dlfcn.h>
#include <dirent.h>
#include "./lib/IGraph.hh"
#include "./games/IGame.hh"

class		Arcade
{
public:
  IGame				*Game;
  IGraph			*Graph;
  arcade::CommandType		com;
  std::string			gamePath;
  std::vector<std::string>	listgr;
  int				indexGraph;
  void				*dlhgraph;
  void				*dlhgame;
  int				minitime;


  Arcade(char *);
  ~Arcade();

  void		core();
  void		inMenu();
  void		inGame();
  void		opLibGraph(const char *path);
  void		opLibGame(const char *path);
};

#endif
