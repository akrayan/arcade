//
// Arcade.cpp for Arcade.cpp in /home/rayan/CPP/cpp_arcade
//
// Made by Rayan
// Login   <raihane.akkache@epitech.net>
//
// Started on  Mon Apr  3 18:17:50 2017 Rayan
// Last update Sun Apr  9 23:37:07 2017 Rayan
//

#include "Arcade.hh"

std::vector<std::string>        get_lib(std::string dirName)
{
  struct dirent                 *file;
  DIR                           *dir;
  std::vector<std::string>      tab;
  std::string                   s;

  dir = opendir(dirName.c_str());
  while ((file = readdir(dir)) != NULL)
    {
      s = dirName + file->d_name;
      if (s[s.size() - 3] == '.' && s[s.size() - 2] == 's' && s[s.size() - 1] == 'o')
	tab.push_back(s);
    }
  closedir(dir);
  return (tab);
}

void			Arcade::opLibGraph(const char *path)
{
  IGraph		*(*graph)();

  if (dlhgraph != NULL)
    dlclose(dlhgraph);
  dlhgraph = dlopen(path, RTLD_NOW);
  if (dlhgraph == NULL)
    {
      std::cout << "err dl1" << std::endl;
      std::cout << dlerror() << std::endl;
      exit(EXIT_FAILURE);
    }
  graph = reinterpret_cast<IGraph* (*)()>(dlsym(dlhgraph, "createInterface"));
  if (graph == NULL)
    {
      std::cout << "pas trouvé1" << std::endl;
      exit(EXIT_FAILURE);
    }
  Graph = graph();
  if (Game != NULL)
    Graph->initTexture(Game->getGameName());
}

void			Arcade::opLibGame(const char *path)
{
  std::string		s;
  IGame			*(*game)();

  s = "./games/lib_arcade_";
  s += path;
  s += ".so";
  path = s.c_str();
  if (dlhgame != NULL)
    dlclose(dlhgame);
  dlhgame = dlopen(path, RTLD_NOW);
  if (dlhgame == NULL)
    {
      std::cout << "err dl2" << std::endl;
      std::cout << dlerror() << std::endl;
      exit(EXIT_FAILURE);
    }
  game = reinterpret_cast<IGame* (*)()>(dlsym(dlhgame, "createGame"));
  if (game == NULL)
    {
      std::cout << "pas trouvé2" << std::endl;
      exit(EXIT_FAILURE);
    }
  Game = game();
  Graph->initTexture(Game->getGameName());
}

Arcade::Arcade(char *libpath)
{
  minitime = 0;

  indexGraph = 0;

  listgr = get_lib("./lib/");

  dlhgame = NULL;
  dlhgraph = NULL;
  opLibGraph(libpath);

  Game = NULL;
  com = (arcade::CommandType::ILLEGAL);
  Graph->showInterface(Game);

  gamePath = Graph->getSelectGame(com);
}


Arcade::~Arcade()
{
  delete Game;
  delete Graph;
  if (dlhgame != NULL)
    dlclose(dlhgame);
  if (dlhgraph != NULL)
    dlclose(dlhgraph);
}

void				Arcade::inMenu()
{

  if (arcade::CommandType::GO_LEFT == com)
    gamePath = Graph->getSelectGame(arcade::CommandType::PREVGAME);
  else if (arcade::CommandType::GO_RIGHT == com)
    gamePath = Graph->getSelectGame(arcade::CommandType::NEXTGAME);
  else if (arcade::CommandType::PLAY == com)
    opLibGame(gamePath.c_str());
  minitime = 1;
  if (com != arcade::CommandType::ILLEGAL)
    com = (arcade::CommandType::ILLEGAL);
}

void				Arcade::inGame()
{
  if (arcade::CommandType::PREVGAME == com)
    {
      gamePath = Graph->getSelectGame(arcade::CommandType::PREVGAME);
      delete Game;
      opLibGame(gamePath.c_str());
    }
  else if (arcade::CommandType::NEXTGAME == com)
    {
      gamePath = Graph->getSelectGame(arcade::CommandType::NEXTGAME);
      delete Game;
      opLibGame(gamePath.c_str());
    }
  else if (arcade::CommandType::RESTART == com)
    {
      delete Game;
      opLibGame(gamePath.c_str());
    }
  else if (arcade::CommandType::MENU == com)
    {
      delete Game;
      Game = NULL;
    }
  else
    Game->play(com);
}

void				Arcade::core()
{
  while (com != (arcade::CommandType::EXIT))
    {
      if (Game != NULL)
	com = (arcade::CommandType::ILLEGAL);
     Graph->showInterface(Game);
      if (com != (arcade::CommandType::EXIT))
	com = Graph->pollEvent();
      if (com == (arcade::CommandType::PREVGRAPH))
	{
	  indexGraph--;
	  if (indexGraph == -1)
	    indexGraph = listgr.size() - 1;
	  delete Graph;
	  opLibGraph(listgr[indexGraph].c_str());
	}
      if (com == (arcade::CommandType::NEXTGRAPH))
	{
	  indexGraph++;
	  if (indexGraph == (int)(listgr.size()))
	    indexGraph = 0;
	  delete Graph;
	  opLibGraph(listgr[indexGraph].c_str());
	}
      if (Game != NULL)
	inGame();
      else
	inMenu();
      usleep(70000);
    }
}
