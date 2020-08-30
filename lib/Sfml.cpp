//
// Sfml.cpp for Sfml.cpp in /home/rayan/CPP/cpp_arcade/lib
//
// Made by Rayan
// Login   <raihane.akkache@epitech.net>
//
// Started on  Wed Mar 22 14:55:18 2017 Rayan
// Last update Sun Apr  9 23:38:52 2017 Rayan
//

#include "Sfml.hh"
#include <time.h>

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

std::string			intToString(int i)
{
  std::ostringstream s;

  s << i;
  return(s.str());
}

void		Sfml::initBox()
{
  background.loadFromFile("./textures/background.jpg");
  boxText[0].loadFromFile("./textures/box/chg.png");
  boxText[1].loadFromFile("./textures/box/chd.png");
  boxText[2].loadFromFile("./textures/box/cbg.png");
  boxText[3].loadFromFile("./textures/box/cbd.png");
  boxText[4].loadFromFile("./textures/box/bh.png");
  boxText[5].loadFromFile("./textures/box/bg.png");
  boxText[6].loadFromFile("./textures/box/bd.png");
  boxText[7].loadFromFile("./textures/box/bb.png");
}

Sfml::Sfml()
{
  int	i;

  posx = 0;
  posy = 0;
  setScore = false;
  gameLaunched = false;
  multDir = false;
  if (!ftitle.loadFromFile("./font/title.ttf"))
    std::cout << "pas trouvé frere" << std::endl;
  if (!ftext.loadFromFile("./font/text.ttf"))
    std::cout << "pas trouvé frere" << std::endl;
  window = new sf::RenderWindow(sf::VideoMode(1920, 1080), "Arcade");
  indexGame = 0;
  listGame = get_lib("./games/");
  i = -1;
  while (++i < 10)
    tabTexture[i].setSize(sf::Vector2f(SIZTX, SIZTY));
  initTexture("");
  initBox();
  name = "NULL";
  buff = "";
  music.openFromFile("sound/05.ogg");
  music.setLoop(true);
  music.play();
  _leaderboard = new Leaderboard;
}

Sfml::~Sfml()
{
  window->close();
  delete window;
}

void	Sfml::showEnd(IGame *G)
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
      score.setFont(ftext);
      score.setString(sscore);
      score.setCharacterSize(32);
      score.setColor(sf::Color::White);
      score.setPosition(POSMX, POSMY + i * 40);
      window->draw(score);
      i = i + 1;
    }
}

void				Sfml::showGame(IGame *G)
{
  int				i;
  int				j;
  const arcade::GetMap		*m;
  const arcade::WhereAmI	*p;
  sf::RectangleShape		rect;
  sf::Text			score;
  std::string			sscore;

  m = G->getMap();
  p = G->getPlayer();
   j = -1;
  while (++j < m->height)
    {
      i = -1;
      while (++i < m->width)
	{
	  rect = tabTexture[0];
	  rect.setPosition(sf::Vector2f(POSMX + (SIZTX * i), POSMY + (SIZTY * j)));
	  window->draw(rect);
	}
    }
  j = -1;
  while (++j < m->height)
    {
      i = -1;
      while (++i < m->width)
	{
	  rect = tabTexture[(int)m->tile[((m->width * j) + i)]];
	  rect.setPosition(sf::Vector2f(POSMX + (SIZTX * i), POSMY + (SIZTY * j)));
	  window->draw(rect);
	}
    }
  rect = tabTexture[9];
  rect.setPosition(sf::Vector2f(POSMX + (p->position[0].x * SIZTX),
				POSMY + (p->position[0].y * SIZTY)));
  window->draw(rect);
  i = 1;
  rect = tabTexture[8];
  while (i < p->lenght)
    {
      rect.setPosition(sf::Vector2f(POSMX + (p->position[i].x * SIZTX),
				    POSMY + (p->position[i].y * SIZTY)));
      window->draw(rect);
      i++;
    }
  posx = p->position[0].x;
  posy = p->position[0].y;
  sscore = "Score : " + intToString((int)(G->getScore()));

  score.setFont(ftext);
  score.setString(sscore);
  score.setCharacterSize(32);
  score.setColor(sf::Color::White);
  score.setPosition(POSMX + SIZTX * (m->width + 1), POSMY);
  window->draw(score);

  rect.setTexture(&boxText[0]);
  rect.setSize(sf::Vector2f(BOXLARGE, BOXHEIGHT));
  rect.setPosition(sf::Vector2f(POSMX - BOXLARGE, POSMY - BOXHEIGHT));
  window->draw(rect);

  rect.setTexture(&boxText[1]);
  rect.setSize(sf::Vector2f(BOXLARGE, BOXHEIGHT));
  rect.setPosition(sf::Vector2f(POSMX + m->width * SIZTX, POSMY - BOXHEIGHT));
  window->draw(rect);

  rect.setTexture(&boxText[2]);
  rect.setSize(sf::Vector2f(BOXLARGE, BOXHEIGHT));
  rect.setPosition(sf::Vector2f(POSMX - BOXLARGE, POSMY + m->height * SIZTY));
  window->draw(rect);

  rect.setTexture(&boxText[3]);
  rect.setSize(sf::Vector2f(BOXLARGE, BOXHEIGHT));
  rect.setPosition(sf::Vector2f(POSMX + m->width * SIZTX, POSMY + m->height * SIZTY));
  window->draw(rect);

  rect.setTexture(&boxText[4]);
  rect.setSize(sf::Vector2f(m->width * SIZTX, BOXHEIGHT));
  rect.setPosition(sf::Vector2f(POSMX, POSMY - BOXHEIGHT));
  window->draw(rect);

  rect.setTexture(&boxText[5]);
  rect.setSize(sf::Vector2f(BOXLARGE, m->height * SIZTY));
  rect.setPosition(sf::Vector2f(POSMX - BOXLARGE, POSMY));
  window->draw(rect);

  rect.setTexture(&boxText[6]);
  rect.setSize(sf::Vector2f(BOXLARGE, m->height * SIZTY));
  rect.setPosition(sf::Vector2f(POSMX + m->width * SIZTX, POSMY));
  window->draw(rect);

  rect.setTexture(&boxText[7]);
  rect.setSize(sf::Vector2f(m->width * SIZTX, BOXHEIGHT));
  rect.setPosition(sf::Vector2f(POSMX, POSMY + m->height * SIZTY));
  window->draw(rect);

}

void				Sfml::showMenu()
{
  sf::Font font;
  sf::Text title;
  sf::Text gamename;
  char		c;

  title.setFont(ftitle);
  title.setString("ARCADE");
  title.setCharacterSize(200);
  title.setColor(sf::Color::Cyan);
  title.setPosition(350, 200);
  window->draw(title);

  if (name != "NULL")
    {
      gamename.setFont(ftext);
      gamename.setString(change_str(listGame[indexGame]));
      gamename.setCharacterSize(50);
      gamename.setColor(sf::Color::Red);
      gamename.setPosition(350, 600);
      window->draw(gamename);
    }
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

	  if ((int)event.text.unicode < 128 && ((int)event.text.unicode > 31 || (int)event.text.unicode == '\b'))
	    c = static_cast<char>(event.text.unicode);
	  if (c < 128 && c != '\n' && c != '\b')
	    buff += c;
	  else if (c == '\b' && buff.size() > 0)
	    buff.erase(buff.size() - 1);
	}
      usleep(10000);
      gamename.setFont(ftext);
      gamename.setString(buff);
      gamename.setCharacterSize(50);
      gamename.setColor(sf::Color::Red);
      gamename.setPosition(350, 600);
      window->draw(gamename);
      gamename.setString("Enter your name :");
      gamename.setPosition(350, 540);
      window->draw(gamename);
    }
}

void				Sfml::showInterface(IGame *G)
{
  sf::Sprite			back(background);

  window->clear(sf::Color::Black);
  window->draw(back);
  if (G == NULL)
    {
      gameLaunched = false;
      showMenu();
    }
  else if (G != NULL && G->IsEnd() == false && G->IsGameOver() == false)
    {
      gameLaunched = true;
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
  window->display();
}

std::string	Sfml::getSelectGame(arcade::CommandType ct)
{
  setScore = false;
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

arcade::CommandType	Sfml::pollEvent()
{
  while (window->pollEvent(event))
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
      else if (sf::Keyboard::isKeyPressed(sf::Keyboard::P) && name != "NULL")
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

void	Sfml::initTexture(std::string name)
{
  int	i;

  i = -1;
  while (++i < 10)
    {
      tabTexture[i].setFillColor(sf::Color::White);
      tabTexture[i].setTexture(NULL);
    }

  multDir = false;
  if (name == "snake")
    {
      tabText[0].loadFromFile("./textures/sfml/snake/empty.png");
      tabText[1].loadFromFile("./textures/sfml/snake/block.png");
      tabText[6].loadFromFile("./textures/sfml/snake/apple.png");
      tabText[9].loadFromFile("./textures/sfml/snake/head.png");
      tabText[8].loadFromFile("./textures/sfml/snake/body.png");

      tabTexture[0].setTexture(&tabText[0]);
      tabTexture[1].setTexture(&tabText[1]);
      tabTexture[6].setTexture(&tabText[6]);
      tabTexture[8].setTexture(&tabText[8]);
      tabTexture[9].setTexture(&tabText[9]);
    }
  else if (name == "centipede")
    {
      tabText[0].loadFromFile("./textures/sfml/centipede/empty.png");
      tabText[2].loadFromFile("./textures/sfml/centipede/block.png");
      tabText[3].loadFromFile("./textures/sfml/centipede/evil.png");
      tabText[5].loadFromFile("./textures/sfml/centipede/shoot.png");
      tabText[9].loadFromFile("./textures/sfml/centipede/player.png");

      tabTexture[0].setTexture(&tabText[0]);
      tabTexture[2].setTexture(&tabText[2]);
      tabTexture[3].setTexture(&tabText[3]);
      tabTexture[5].setTexture(&tabText[5]);
      tabTexture[9].setTexture(&tabText[9]);
    }
  else if (name == "pacman")
    {
      multDir = true;
      tabText[0].loadFromFile("./textures/sfml/pacman/back.png");
      tabText[6].loadFromFile("./textures/sfml/pacman/lp.png");
      tabText[3].loadFromFile("./textures/sfml/pacman/ghostd.png");
      tabText[4].loadFromFile("./textures/sfml/pacman/ghost.png");
      tabText[1].loadFromFile("./textures/sfml/pacman/block.png");
      tabText[5].loadFromFile("./textures/sfml/pacman/powerup.png");
      tabText[9].loadFromFile("./textures/sfml/pacman/player_l.png");
      tabText[10].loadFromFile("./textures/sfml/pacman/player_r.png");
      tabText[11].loadFromFile("./textures/sfml/pacman/player_u.png");
      tabText[12].loadFromFile("./textures/sfml/pacman/player_d.png");

      tabTexture[0].setTexture(&tabText[0]);
      tabTexture[1].setTexture(&tabText[1]);
      tabTexture[6].setTexture(&tabText[6]);
      tabTexture[3].setTexture(&tabText[3]);
      tabTexture[4].setTexture(&tabText[4]);
      tabTexture[5].setTexture(&tabText[5]);
      tabTexture[9].setTexture(&tabText[9]);
      tabTexture[10].setTexture(&tabText[10]);
      tabTexture[11].setTexture(&tabText[11]);
      tabTexture[12].setTexture(&tabText[12]);
    }
  else if (name == "nibbler")
    {
      tabText[0].loadFromFile("./textures/sfml/nibbler/empty.png");
      tabText[1].loadFromFile("./textures/sfml/nibbler/block.png");
      tabText[6].loadFromFile("./textures/sfml/nibbler/powerup.png");
      tabText[9].loadFromFile("./textures/sfml/nibbler/head.png");
      tabText[8].loadFromFile("./textures/sfml/nibbler/body.png");

      tabTexture[0].setTexture(&tabText[0]);
      tabTexture[1].setTexture(&tabText[1]);
      tabTexture[6].setTexture(&tabText[6]);
      tabTexture[8].setTexture(&tabText[8]);
      tabTexture[9].setTexture(&tabText[9]);
    }
  else
    {

      tabTexture[0].setFillColor(sf::Color::Black);
      tabTexture[1].setFillColor(sf::Color::Blue);
      tabTexture[2].setFillColor(sf::Color::Magenta);
      tabTexture[3].setFillColor(sf::Color::Green);
      tabTexture[4].setFillColor(sf::Color::Yellow);
      tabTexture[5].setFillColor(sf::Color::White);
      tabTexture[6].setFillColor(sf::Color::Cyan);
    }
    setScore = false;
}

extern "C"
{
  IGraph *createInterface()
  {
    return new Sfml();
  }
}
