//
// Ncurses.cpp for Ncurses.cpp in /home/rayan/CPP/cpp_arcade/lib
//
// Made by Rayan
// Login   <raihane.akkache@epitech.net>
//
// Started on  Wed Mar 22 14:55:18 2017 Rayan
// Last update Sun Apr  9 23:38:43 2017 Rayan
//

#include "Ncurses.hh"

std::vector<std::string>        get_lib(std::string dirName)
{
  struct dirent                 *file;
  DIR                           *dir;
  std::vector<std::string>	tab1;
  std::string                   s;

  dir = opendir(dirName.c_str());
  while ((file = readdir(dir)) != NULL)
    {
      s = dirName + file->d_name;
      if (s[s.size() - 3] == '.' && s[s.size() - 2] == 's' && s[s.size() - 1] == 'o')
	tab1.push_back(s);
    }
  closedir(dir);
  return (tab1);
}

std::string		change_str(std::string s)
{
  s = s.substr(19);
  s = s.substr(0, s.size() - 3);
  return (s);
}

Ncurses::Ncurses()
{
  srand(time(NULL));
  anim = 0;
  setScore = false;
  this->scr = initscr();
  keypad(stdscr, TRUE);
  curs_set(0);
  noecho();
  start_color();
  init_pair(1, COLOR_YELLOW, COLOR_YELLOW);
  init_pair(2, COLOR_RED, COLOR_RED);
  init_pair(3, COLOR_CYAN, COLOR_CYAN);
  init_pair(4, COLOR_WHITE, COLOR_WHITE);
  init_pair(5, COLOR_GREEN, COLOR_GREEN);
  init_pair(6, COLOR_BLACK, COLOR_YELLOW);

  init_pair(10, COLOR_YELLOW, COLOR_YELLOW);
  init_pair(8, COLOR_CYAN, COLOR_CYAN);
  init_pair(9, COLOR_MAGENTA, COLOR_MAGENTA);

  init_pair(7, COLOR_RED, COLOR_RED);
  init_pair(11, COLOR_GREEN, COLOR_GREEN);
  init_pair(12, COLOR_BLUE, COLOR_BLUE);
  mode(true);
  indexGame = 0;
  listGame = get_lib("./games/");
  _leaderboard = new Leaderboard;
  _errorname = false;
}

Ncurses::~Ncurses()
{
  mode(false);
  endwin();
}

void				Ncurses::showMenu()
{
  int				i;
  int				j;
  std::string			s;
  int				c;

  s = change_str(listGame[indexGame]);
  if (_name.size() > 0 && _buff[0] == 127)
    _name.erase(_name.end() - 1);
  else if (_buff[0] >= 32 && _buff[0] <= 126)
    _name += _buff[0];
  /* if (anim % 10 == 0)
     {*/
      clear();
      c = rand() % 6 + 7;
      attron(COLOR_PAIR(c));
      j = -1;
      while (++j < LINES)
	{
	  if (j % 2 == 0)
	    {
	      i = -1;
	      while (++i < COLS)
		{
		  if (i % 2 == 0)
		    {
		      //if (i % 6 == 0)
		      //{

		      //}
		      if (!(j > LINES / 2 - 17 && j < LINES / 2 + 4 && i > COLS / 2 - 40 && i < COLS / 2 + 40))
			mvprintw(j, i, " ");

		    }
		}
	    }

	}
      attroff(COLOR_PAIR(c));
  mvprintw(LINES / 2, (COLS - s.size()) / 2, s.c_str());
  s = "Enter your name here: ";
  s += _name;
  mvprintw(LINES / 2 + 1, (COLS - s.size()) / 2, s.c_str());
  //mvprintw((LINES / 2) + 1, (COLS - s.size()) / 2, "Enter your name here: %s", _name.c_str());
  //mvprintw((LINES / 2) + 2, (COLS - s.size()) / 2, "          ", _name.c_str());
  if (_errorname == true)
    {
      attron(COLOR_PAIR(7));
      mvprintw((LINES / 2) + 2, (COLS - s.size()) / 2, "Error name");
      attroff(COLOR_PAIR(7));
    }
  mvprintw((LINES / 4), (COLS / 2) - (62 / 2),     "    :::    :::::::::  ::::::::     :::    ::::::::: ::::::::::");
  mvprintw((LINES / 4) + 1, (COLS / 2) - (62 / 2), "  :+: :+:  :+:    :+::+:    :+:  :+: :+:  :+:    :+::+:");
  mvprintw((LINES / 4) + 2, (COLS / 2) - (62 / 2), " *+:+   +:+ +:+    +:++:+        +:+   +:+ +:+    +:++:+");
  mvprintw((LINES / 4) + 3, (COLS / 2) - (62 / 2), "+#++:++#++:+#++:++#: +#+       +#++:++#++:+#+    +:++#++:++#");
  mvprintw((LINES / 4) + 4, (COLS / 2) - (62 / 2), "+#+     +#++#+    +#++#+       +#+     +#++#+    +#++#+");
  mvprintw((LINES / 4) + 5, (COLS / 2) - (62 / 2), "*#+#     #+##+#    #+##+#    #+##+#     #+##+#    #+##+#");
  mvprintw((LINES / 4) + 6, (COLS / 2) - (62 / 2), "###     ######    ### ######## ###     ############ ##########");
  refresh();
  //}
}

void				Ncurses::showGame(IGame *G)
{
  const arcade::GetMap		*map;
  const arcade::WhereAmI	*player;
  int				x;
  int				y;

  clear();
  map = G->getMap();
  player = G->getPlayer();
  y = 0;
  while (y < map->height)
    {
      x = 0;
      while (x < map->width)
	{
	  if (map->tile[((map->width * y) + x)] == arcade::TileType::BLOCK)
	    {
	      attron(COLOR_PAIR(1));
	      mvprintw(y + (LINES / 2) - (map->height / 2), (x * 2) + (COLS / 2) - ((map->width * 2) / 2), "**");
	      attroff(COLOR_PAIR(1));
	    }
	  else if (map->tile[((map->width * y) + x)] == arcade::TileType::EMPTY)
	    {
	      attron(COLOR_PAIR(2));
	      mvprintw(y + (LINES / 2) - (map->height / 2), (x * 2) + (COLS / 2) - ((map->width * 2) / 2), "..");
	      attroff(COLOR_PAIR(2));
	    }
	  else if (map->tile[((map->width * y) + x)] == arcade::TileType::POWERUP)
	    {
	      attron(COLOR_PAIR(3));
	      mvprintw(y + (LINES / 2) - (map->height / 2), (x * 2) + (COLS / 2) - ((map->width * 2) / 2), "oo");
	      attroff(COLOR_PAIR(3));
	    }
	  x = x + 1;
	}
      y = y + 1;
    }
  y = 0;
  while (y < player->lenght)
    {
      if (y == 0)
	{
	  attron(COLOR_PAIR(4));
	  mvprintw(player->position[y].y + (LINES / 2) - (map->height / 2), (player->position[y].x * 2) + (COLS / 2) - ((map->width * 2) / 2), "]]");
	  attroff(COLOR_PAIR(4));
	}
      else
	{
	  attron(COLOR_PAIR(5));
	  mvprintw(player->position[y].y + (LINES / 2) - (map->height / 2), (player->position[y].x * 2) + (COLS / 2) - ((map->width * 2) / 2), "##");
	  attroff(COLOR_PAIR(5));
	}
      y = y + 1;
    }
  attron(COLOR_PAIR(6));
  mvprintw((LINES / 2) - (map->height / 2), (COLS / 2) - ((map->width * 2) / 2), "Score : %d", G->getScore());
  attroff(COLOR_PAIR(6));
  if (G->IsEnd() == true)
    {
      if (setScore == false)
	{
	  _leaderboard->set_high_score(G->getGameName(), _name, G->getScore());
	  setScore = true;
	}
      showEnd(G);
      _name = "";
    }
  refresh();
}

void				Ncurses::showInterface(IGame *G)
{

  if (G == NULL)
    {
      //      if (anim % 4 == 0)
	showMenu();
    }
  else
    showGame(G);
  anim++;
  if (anim > 2000000000)
    anim = 0;
}

std::string	Ncurses::getSelectGame(arcade::CommandType ct)
{
  if (ct == (arcade::CommandType)8)
    return (change_str(listGame[indexGame]));
  if (ct == (arcade::CommandType)12)
    indexGame--;
  else
    indexGame++;
  if (indexGame < 0)
    indexGame = listGame.size() - 1;
  if (indexGame == listGame.size())
    indexGame = 0;
  return (change_str(listGame[indexGame]));
}

void		Ncurses::mode(bool b)
{
  if (b)
    {
      ioctl(0, TCGETS, &old_term);
      ioctl(0, TCGETS, &new_term);
      new_term.c_lflag &= ~ECHO;
      new_term.c_lflag &= ~ICANON;
      new_term.c_cc[VMIN] = 0;
      new_term.c_cc[VTIME] = 0;
      ioctl(0, TCSETS, &new_term);
    }
  else
    ioctl(0, TCSETS, &old_term);
}

arcade::CommandType	Ncurses::pollEvent()
{
  char	buff[4];

  memset(buff, 0, 4);
  read(0, buff, 3);
  _buff = std::string(buff);
  if (strcmp(buff, tigetstr("kcuu1")) == 0)
    return (arcade::CommandType::GO_UP);
  else if (strcmp(buff,tigetstr("kcud1")) == 0)
    return (arcade::CommandType::GO_DOWN);
  else if (strcmp(buff,tigetstr("kcub1")) == 0)
    return (arcade::CommandType::GO_LEFT);
  else if (strcmp(buff,tigetstr("kcuf1")) == 0)
    return (arcade::CommandType::GO_RIGHT);
  else if (strcmp(buff, "t") == 0)
    return (arcade::CommandType::GO_FORWARD);
  else if (strcmp(buff, " ") == 0)
    return (arcade::CommandType::SHOOT);
  else if (strcmp(buff, "\r") == 0)
    {
      if (_name == "")
	{
	  _errorname = true;
	  return (arcade::CommandType::ILLEGAL);
	}
      return (arcade::CommandType::PLAY);
    }
  else if (strcmp(buff, "é") == 0 || strcmp(buff, "2") == 0)
    return (arcade::CommandType::PREVGRAPH);
  else if (strcmp(buff, "\"") == 0 || strcmp(buff, "3") == 0)
    return (arcade::CommandType::NEXTGRAPH);
  else if (strcmp(buff, "'") == 0 || strcmp(buff, "4") == 0)
    return (arcade::CommandType::PREVGAME);
  else if (strcmp(buff, "(") == 0 || strcmp(buff, "5") == 0)
    return (arcade::CommandType::NEXTGAME);
  else if (strcmp(buff, "_") == 0 || strcmp(buff, "8") == 0)
    return (arcade::CommandType::RESTART);
  else if (strcmp(buff, "ç") == 0 || strcmp(buff, "9") == 0)
    return (arcade::CommandType::MENU);
  else if (strcmp(buff, "\e") == 0)
      return (arcade::CommandType::EXIT);
  else
    return (arcade::CommandType::ILLEGAL);
}

void	Ncurses::initTexture(std::string name)
{
  setScore = false;
}

void	Ncurses::showEnd(IGame *G)
{
  std::vector<Leaderboard::HighScore> HighScore;
  int		i;

  clear();
  HighScore = _leaderboard->getLeaderboard(G->getGameName());
  i = 0;
  while (i < HighScore.size())
    {
      mvprintw(i, 0, "%s\t\t\t\t%d", HighScore[i].PlayerName.c_str(), HighScore[i].Score);
      i = i + 1;
    }
  refresh();
}

extern "C"
{
  IGraph *createInterface()
  {
    return new Ncurses();
  }
}
