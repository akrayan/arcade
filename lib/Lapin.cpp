//
// Lapin.cpp for Lapin.cpp in /home/rayan/CPP/cpp_arcade/lib
//
// Made by Rayan
// Login   <raihane.akkache@epitech.net>
//
// Started on  Wed Mar 22 14:55:18 2017 Rayan
// Last update Sun Apr  9 23:38:26 2017 Rayan
//

#include "Lapin.hh"

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

//s.color.full = BLACK;

std::string		change_str(std::string s)
{
  s = s.substr(19);
  s = s.substr(0, s.size() - 3);
  return (s);
}


std::string		clean_str(std::string s)
{
  int			i;

  i = 0;
  while (i < s.size())
    {
      if (!((s[i] >= 'A' && s[i] <= 'Z') || (s[i] >= 'a' && s[i] <= 'z') ||
	    (s[i] >= '0' && s[i] <= '9') || s[i] == ' '))
	s.erase(i);
      else
	i++;
    }
  return (s);
}

void                    fill_it(t_bunny_pixelarray *pix, t_color *color)
{
  unsigned char         *pixel;
  int                   i;

  i = 0;
  pixel = (unsigned char *)(pix->pixels);
  while (i < (pix->clipable.clip_width * pix->clipable.clip_height * 4))
    {
      pixel[i] = color->argb[0];
      pixel[i + 1] = color->argb[1];
      pixel[i + 2] = color->argb[2];
      pixel[i + 3] = color->argb[3];
      i = i + 4;
    }
}

void                    Lapin::b_clear()
{
  unsigned char         *pixel;
  int                   i;

  i = 0;
  pixel = (unsigned char *)(pix->pixels);
  while (i < (pix->clipable.clip_width * pix->clipable.clip_height * 4))
    {
      pixel[i] = 0;
      pixel[i + 1] = 0;
      pixel[i + 2] = 0;
      pixel[i + 3] = 0;
      i = i + 4;
    }
}

void			Lapin::draw_tile(t_bunny_pixelarray *tile, t_bunny_position p)
{
  unsigned int		*pixel;
  unsigned int		*pixelt;
  int			i;
  int			j;

  j = 0;
  pixel = (unsigned int *)(pix->pixels);
  pixelt = (unsigned int *)(tile->pixels);
  while (j < (tile->clipable.clip_width * tile->clipable.clip_height))
    {
      pixel[(p.x + (j % 25)) + (((j / 25) + p.y) * pix->clipable.clip_width)] = pixelt[j];
      j++;
    }
}

void			Lapin::init_font()
{
  t_bunny_position	p;
  unsigned int		*pixelf;
  unsigned int		*pixelc;
  int			large;
  int			i;
  int			j;
  int			k;

  font = bunny_load_pixelarray("./textures/lapin/font.png");
  large = (font->clipable.clip_width / 36);
  i = -1;
  while (++i < 36)
    listChar.push_back(bunny_new_pixelarray(large, font->clipable.clip_height));
  k = -1;
  while (++k < 36)
    {
      pixelf = (unsigned int *)(font->pixels);
      pixelc = (unsigned int *)((listChar[k])->pixels);
      p.y = 0;
      p.x = k * large;
      j = 0;
      while (j < font->clipable.clip_height)
	{
	  i = 0;
	  while (i < (font->clipable.clip_width / 36))
	    {
	      pixelc[i + (j * large)] = pixelf[p.x + i + (j * font->clipable.clip_width)];
	      i++;
	    }
	  j++;
	}
    }
}

void			Lapin::draw_str(std::string s, int x, int y)
{
  int			i;
  int			large;
  t_bunny_position	p;

  p.x = x;
  p.y = y;
  large = (font->clipable.clip_width / 36);
  i = -1;
  while (++i < (int)s.size())
    {
      if (s[i] >= 'A' && s[i] <= 'Z')
	bunny_blit(&win->buffer, &((listChar[s[i] - 65])->clipable), &p);
      else if (s[i] >= 'a' && s[i] <= 'z')
	bunny_blit(&win->buffer, &((listChar[s[i] - 97])->clipable), &p);
      else if (s[i] >= '0' && s[i] <= '9')
	bunny_blit(&win->buffer, &((listChar[s[i] - 48 + 26])->clipable), &p);
      p.x = p.x + large + (large / 6);
    }
}

std::string			intToString(int i)
{
  std::ostringstream s;

  s << i;
  return(s.str());
}

Lapin::Lapin()
{
  int		i;

  setScore = false;
  i = -1;
  while (++i < 10)
    listTile.push_back(NULL);
  win = bunny_start(WIN_LARGE, WIN_HEIGHT, false, "Raytracer 2");
  pix = bunny_new_pixelarray(WIN_LARGE, WIN_HEIGHT);
  //bunny_set_maximum_ram(100000000000);
  indexGame = 0;
  listGame = get_lib("./games/");
  init_font();
  name = "NULL";
  buff = "";
  music = bunny_load_music("./sound/05.ogg");
  bunny_sound_play(&music->sound);
  bunny_sound_loop(&music->sound, 1);
  background = bunny_load_pixelarray("./textures/lapin/background.jpg");
  _leaderboard = new Leaderboard;
}

Lapin::~Lapin()
{
  int		i;

  /*  i = -1;
  while (i < (int)listTile.size())
    {
      if (listTile[i] != NULL)
	bunny_delete_clipable(&listTile[i]->clipable);
      listTile[i] = NULL;
      }*/
  bunny_sound_loop(&music->sound, 0);
  bunny_sound_stop(&music->sound);
  bunny_delete_sound(&music->sound);
  bunny_stop(win);
}

void				Lapin::showGame(IGame *G)
{
  int				i;
  t_bunny_position		pos;
  t_bunny_position		pos2;
  const arcade::GetMap		*m;
  const arcade::WhereAmI	*p;
  std::string			sscore;

  pos2.x = 0;
  pos2.y = 0;
  m = G->getMap();
  p = G->getPlayer();
  pos.y = -1;
  while (++(pos.y) < m->height)
    {
      pos.x = -1;
      while (++(pos.x) < m->width)
	{
	  pos2.x = POSMX + pos.x * 25;
	  pos2.y = POSMY + pos.y * 25;
	  if ((int)m->tile[((m->width * pos.y) + pos.x)] == 6)
	    bunny_blit(&win->buffer, &((listTile[0])->clipable), &pos2);


	  bunny_blit(
		     &win->buffer,
		     &((listTile[static_cast<int>(m->tile[pos.x + (pos.y * m->width)])])->clipable),
		     &pos2);
	}
      i = 0;
      while (i < p->lenght)
	{

	  pos2.x = POSMX + p->position[i].x * 25;
	  pos2.y = POSMY + p->position[i].y * 25;
	  bunny_blit(&win->buffer, &((listTile[0])->clipable), &pos2);
	  if (i == 0)
	    bunny_blit(&win->buffer, &((listTile[8])->clipable), &pos2);
	  else
	    bunny_blit(&win->buffer, &((listTile[9])->clipable), &pos2);
	  i++;
	}
    }
  sscore = "Score ";
  sscore += intToString(G->getScore());
  draw_str(sscore, POSMX + 25 + m->width * 25, POSMY);
}

void				Lapin::showMenu()
{
  char				c;

  draw_str("ARCADE", 300, 200);
  if (name != "NULL")
    draw_str(change_str(listGame[indexGame]), 300, 600);
  else
    {
      buff = clean_str(buff);
      c = 150;

      if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return) && (buff.size() > 0))
	{
	  name = buff;
	  return ;
	}
      if (event.type == sf::Event::TextEntered)
	{
	  if ((int)event.text.unicode < 128 && ((int)event.text.unicode > 31 ||
						(int)event.text.unicode == '\b'))
	    c = static_cast<char>(event.text.unicode);
	  if (c < 128 && c != '\n' && c != '\b')
	    buff += c;
	  else if (c == '\b' && buff.size() > 0)
	    buff.erase(buff.size() - 1);
	}
      usleep(10000);
      draw_str(buff, 300, 600);
      draw_str("Enter your name :", 300, 540);
    }
}

void	Lapin::showEnd(IGame *G)
{
  sf::Text			score;
  std::string			sscore;
  std::vector<Leaderboard::HighScore> HighScore;
  int		i;

  HighScore = _leaderboard->getLeaderboard(G->getGameName());
  i = 0;
  while (i < HighScore.size())
    {
      //mvprintw(i, 0, "%s\t\t\t\t%d", HighScore[i].PlayerName.c_str(), HighScore[i].Score);
      sscore = HighScore[i].PlayerName + "      ";
      sscore += intToString(HighScore[i].Score);
      draw_str(sscore, 50, 100 + i * 55);

      i = i + 1;
    }
}

void				Lapin::showInterface(IGame *G)
{
  p.x = 0;
  p.y = 0;
  bunny_fill(&win->buffer, ALPHA(32, BLACK));
  bunny_blit(&win->buffer, &(background->clipable), &p);
  if (G == NULL)
    {
      showMenu();
    }
  else if (G != NULL && !G->IsEnd() && !G->IsGameOver())
    {
      showGame(G);
    }
  else
    {
      if (setScore == false)
	{
	  _leaderboard->set_high_score(G->getGameName(), name, G->getScore());
	  setScore = true;
	}
      showEnd(G);
    }
  //bunny_blit(&win->buffer, &pix->clipable, &p);
  bunny_display(win);
}

std::string	Lapin::getSelectGame(arcade::CommandType ct)
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

arcade::CommandType	Lapin::pollEvent()
{
  struct bunny_window *window = (struct bunny_window *)win;

  while (window->window->pollEvent(event))
    {
      if (event.type == sf::Event::KeyPressed)
	{
	  if (event.key.code == sf::Keyboard::Up)
	    return (arcade::CommandType)2;
	  else if (event.key.code == sf::Keyboard::Down)
	    return (arcade::CommandType)3;
	  else if (event.key.code == sf::Keyboard::Left)
	    return (arcade::CommandType)4;
	  else if (event.key.code == sf::Keyboard::Right)
	    return (arcade::CommandType)5;
	  else if (event.key.code == sf::Keyboard::LShift)
	    return (arcade::CommandType)6;
	  else if (event.key.code == sf::Keyboard::Space)
	    return (arcade::CommandType)7;
	  else if (event.key.code == (sf::Keyboard::P) && name != "NULL")
	    return (arcade::CommandType::PLAY);
	  else if (event.key.code == sf::Keyboard::Num2)
	    return (arcade::CommandType)10;
	  else if (event.key.code == sf::Keyboard::Num3)
	    return (arcade::CommandType)11;
	  else if (event.key.code == sf::Keyboard::Num4)
	    return (arcade::CommandType)12;
	  else if (event.key.code == sf::Keyboard::Num5)
	    return (arcade::CommandType)13;
	  else if (event.key.code == sf::Keyboard::Num8)
	    return (arcade::CommandType)14;
	  else if (event.key.code == sf::Keyboard::Num9)
	    return (arcade::CommandType)15;
	  else if (event.key.code == sf::Keyboard::Escape)
	    return (arcade::CommandType)16;
	}
    }
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
    return (arcade::CommandType::GO_UP);
  else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
    return (arcade::CommandType::GO_DOWN);
  else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    return (arcade::CommandType::GO_LEFT);
  else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    return (arcade::CommandType::GO_RIGHT);
  else if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
    return (arcade::CommandType::GO_FORWARD);
  else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
    return (arcade::CommandType::SHOOT);
  else if (sf::Keyboard::isKeyPressed(sf::Keyboard::P) && name == "NULL")
    return (arcade::CommandType::PLAY);
  else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2))
    return (arcade::CommandType::PREVGRAPH);
  else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num3))
    return (arcade::CommandType::NEXTGRAPH);
  else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num4))
    return (arcade::CommandType::PREVGAME);
  else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num5))
    return (arcade::CommandType::NEXTGAME);
  else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num8))
    return (arcade::CommandType::RESTART);
  else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num9))
    return (arcade::CommandType::MENU);
  else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
    return (arcade::CommandType::EXIT);
  else
    return (arcade::CommandType::ILLEGAL);
}

void		Lapin::initTexture(std::string name)
{
  int		i;
  t_color	c;

  i = -1;
  /*  while (++i < 10)
    listTile[i] = bunny_new_pixelarray(25, 25);
    c.full = BLACK;*/
  /*  i = -1;
  while (i < (int)listTile.size())
    {
      if (listTile[i] != NULL)
	bunny_delete_clipable(&listTile[i]->clipable);
      listTile[i] = NULL;
      }*/
    setScore = false;
  if (name == "snake")
    {
      listTile[0] = bunny_load_pixelarray("./textures/lapin/snake/empty.png");
      listTile[1] = bunny_load_pixelarray("./textures/lapin/snake/block.png");
      listTile[6] = bunny_load_pixelarray("./textures/lapin/snake/apple.png");
      listTile[8] = bunny_load_pixelarray("./textures/lapin/snake/head.png");
      listTile[9] = bunny_load_pixelarray("./textures/lapin/snake/body.png");
    }
  else if (name == "centipede")
    {
      listTile[0] = bunny_load_pixelarray("./textures/lapin/centipede/empty.png");
      listTile[2] = bunny_load_pixelarray("./textures/lapin/centipede/block.png");
      listTile[3] = bunny_load_pixelarray("./textures/lapin/centipede/evil.png");
      listTile[5] = bunny_load_pixelarray("./textures/lapin/centipede/shoot.png");
      listTile[8] = bunny_load_pixelarray("./textures/lapin/centipede/player.png");
    }
  else if (name == "pacman")
    {
      listTile[0] = bunny_load_pixelarray("./textures/lapin/pacman/back.png");
      listTile[1] = bunny_load_pixelarray("./textures/lapin/pacman/block.png");
      listTile[3] = bunny_load_pixelarray("./textures/lapin/pacman/ghostd.png");
      listTile[4] = bunny_load_pixelarray("./textures/lapin/pacman/ghost.png");
      listTile[5] = bunny_load_pixelarray("./textures/lapin/pacman/powerup.png");
      listTile[6] = bunny_load_pixelarray("./textures/lapin/pacman/lp.png");
      listTile[8] = bunny_load_pixelarray("./textures/lapin/pacman/player.png");

    }
  else if (name == "nibbler")
    {
      listTile[0] = bunny_load_pixelarray("./textures/lapin/nibbler/empty_l.png");
      listTile[1] = bunny_load_pixelarray("./textures/lapin/nibbler/block_l.png");
      listTile[6] = bunny_load_pixelarray("./textures/lapin/nibbler/powerup_l.png");
      listTile[8] = bunny_load_pixelarray("./textures/lapin/nibbler/head_l.png");
      listTile[9] = bunny_load_pixelarray("./textures/lapin/nibbler/body_l.png");
    }
  else
    {
      i = -1;
      while (++i < 10)
	listTile[i] = bunny_new_pixelarray(25, 25);
      c.full = BLACK;
      fill_it(listTile[0], &c);
      c.full = BLUE;
      fill_it(listTile[1], &c);
      c.full = RED;
      fill_it(listTile[2], &c);
      c.full = GREEN;
      fill_it(listTile[3], &c);
      c.full = PURPLE;
      fill_it(listTile[4], &c);
      c.full = TEAL;
      fill_it(listTile[5], &c);
      c.full = YELLOW;
      fill_it(listTile[6], &c);
      c.full = WHITE;
      fill_it(listTile[7], &c);
      c.full = PINK;
      fill_it(listTile[8], &c);
      c.full = PINK2;
      fill_it(listTile[9], &c);
    }
  /*
  else
    {

    }*/
}

extern "C"
{
  IGraph *createInterface()
  {
    return new Lapin();
  }
}
