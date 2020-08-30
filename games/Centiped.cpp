//
// Centiped.cpp for Centiped.cpp in /home/afou_n/cpp_arcade
//
// Made by Afou Nacerdine
// Login   <nacerdine.afou@epitech.net>
//
// Started on  Fri Mar 31 12:43:10 2017 Afou Nacerdine
// Last update Sun Apr  9 23:37:25 2017 Rayan
//

#include "Centiped.hh"

void		affvector(std::vector<std::vector<evilDude>> v)
{
  int		i;
  int		j;


  std::cout << "\n\n\n\n\n\n-------------------------------" << std::endl;
  j = -1;
  while (++j < (int)v.size())
    {
      i = -1;
      while (++i < (int)v[j].size())
	{
	  std::cout << v[j][i].x << "  " << v[j][i].y << "   ()   ";
	}
      std::cout << std::endl;
    }

}

void				Centiped::checkList()
{
  int				i;
  int				j;

  j = 0;
  while (j < listCentiped.size())
    {
      if (listCentiped[j].size() == 0)
	listCentiped.erase(listCentiped.begin() + j);
      else
	j++;
    }
  if (listCentiped.size() == 0)
    {
      nbCentipede++;
      j = -1;
      while (++j < MSX)
	hitBlock(j, 0, NBVO);
      creatCentiped();
    }
}

void				Centiped::creatCentiped()
{
  std::vector<evilDude>		centi;
  evilDude			onepart;
  int				i;

  onepart.x = MSX / 2;
  onepart.y = 0;
  onepart.droiteGauche = LEFT;
  onepart.upDown = 1;
  centi.push_back(onepart);
  i = -1;
  while (++i < 8)
    {
      onepart.x += 1;
      centi.push_back(onepart);
    }
  listCentiped.push_back(centi);
}

Centiped::Centiped()
{
  srand(time(NULL));
  this->_namegame = "centipede";
  this->_isover = false;
  initMap();
  initPlayer();
  _shoot = NULL;
  _score = 0;
  freeze = 0;
  nbCentipede = 0;
  creatCentiped();
  _isover = false;
  _isend = false;
}

Centiped::~Centiped()
{
  delete[] this->_map;
  delete[] this->_player;
}


bool const &Centiped::IsEnd(void) const
{
  return (_isend);
}

bool const &Centiped::IsGameOver(void) const
{
  return (_isover);
}

size_t const &Centiped::getScore(void) const
{
  return (_score);
}

void	Centiped::moveCentiped()
{
 int	i;
  int	j;
  int	d;

  d = 0;
  j = -1;
  while (++j < (int)(listCentiped.size()))
    {
      if (listCentiped[j][0].y <= 0)
	listCentiped[j][0].upDown = 1;
      else if (listCentiped[j][0].y >= MSY - 1)
	listCentiped[j][0].upDown = -1;
      if (listCentiped[j][0].droiteGauche == LEFT)
	d = -1;
      else
	d = 1;
      i = listCentiped[j].size();
      while (--i > 0)
	{
	  listCentiped[j][i].x = listCentiped[j][i - 1].x;
	  listCentiped[j][i].y = listCentiped[j][i - 1].y;
	}
      if ((d == -1 && (listCentiped[j][0].x > 0 && _map->tile[listCentiped[j][0].x -1 + listCentiped[j][0].y * MSX] == arcade::TileType::EMPTY)) ||
	  (d == 1 && (listCentiped[j][0].x + 1 < MSX && _map->tile[listCentiped[j][0].x + 1 + listCentiped[j][0].y * MSX] == arcade::TileType::EMPTY)))
	listCentiped[j][i].x += d;
      else
	{
	  listCentiped[j][i].y += listCentiped[j][i].upDown;
	  if (d == -1)
	    listCentiped[j][i].droiteGauche = RIGHT;
	  else
	    listCentiped[j][i].droiteGauche = LEFT;
	}
    }
}

void	Centiped::checkHitCentiped()
{
  int	k;
  int	j;
  int	i;
  std::vector<evilDude> newCenti;
  obstacle	o;

  j = -1;
  while (++j < (int)(listCentiped.size()))
    {
      i = -1;
      while (++i < (int)(listCentiped[j].size()))
	{
	  if (_shoot->x == listCentiped[j][i].x && _shoot->y == listCentiped[j][i].y)
	    {
	      _score += 42;
	      delete _shoot;
	      _shoot = NULL;
	      k = i;
	      if (k != (int)(listCentiped[j].size()) - 1)
		{
		  while (++k < (int)(listCentiped[j].size()))
		    {
		      newCenti.push_back(listCentiped[j][k]);
		      (newCenti[newCenti.size() - 1]).droiteGauche = listCentiped[j][0].droiteGauche;
		      (newCenti[newCenti.size() - 1]).upDown = listCentiped[j][0].upDown;
		    }
		  listCentiped.push_back(newCenti);
		}
	      o.y = listCentiped[j][i].y;
	      o.x = listCentiped[j][i].x;
	      o.vie = NBVO;
	      listObstacle.push_back(o);
	      _map->tile[listCentiped[j][i].x + listCentiped[j][i].y * MSX] = arcade::TileType::OBSTACLE;
	      while (i < (int)(listCentiped[j].size()))
		listCentiped[j].pop_back();
	      return ;
	    }
	}
    }
}

void	Centiped::hitBlock(int x, int y, int nb)
{
  int	i;

  i = 0;
  while (i < (int)listObstacle.size() && !(listObstacle[i].x == x && listObstacle[i].y == y))
    i++;
  if (i < (int)listObstacle.size())
    {
      listObstacle[i].vie -= nb;
      if (listObstacle[i].vie <= 0)
	{
	  _map->tile[listObstacle[i].x + listObstacle[i].y * MSX] = arcade::TileType::EMPTY;
	  listObstacle.erase(listObstacle.begin() + i);
	}
    }
}

void	Centiped::play(arcade::CommandType command)
{
  int	i;
  int	j;

  if (nbCentipede < MAXC && !_isover)
    {
      //if (freeze % 20 == 0)
      moveCentiped();
      if (command == arcade::CommandType::GO_UP && _player->position[0].y - 1 > MSY - (MSY / 5)
	  && _map->tile[(_player->position[0].x) + (_player->position[0].y - 1) * MSX] != arcade::TileType::OBSTACLE)
	(_player->position[0].y)--;
      else if (command == arcade::CommandType::GO_DOWN && _player->position[0].y + 1 < MSY
	       && _map->tile[(_player->position[0].x) + (_player->position[0].y + 1) * MSX] != arcade::TileType::OBSTACLE)
	(_player->position[0].y)++;
      else if (command == arcade::CommandType::GO_LEFT && _player->position[0].x - 1 >= 0
	       && _map->tile[(_player->position[0].x - 1) + (_player->position[0].y) * MSX] != arcade::TileType::OBSTACLE)
	(_player->position[0].x)--;
      else if (command == arcade::CommandType::GO_RIGHT && _player->position[0].x + 1 < MSX
	       && _map->tile[(_player->position[0].x + 1) + (_player->position[0].y) * MSX] != arcade::TileType::OBSTACLE)
	(_player->position[0].x)++;
      else if (command == arcade::CommandType::SHOOT)
	{
	  if (_shoot != NULL)
	    {
	      delete _shoot;
	      _shoot = NULL;
	    }
	  _shoot = new arcade::Position;
	  _shoot->x = _player->position[0].x;
	  _shoot->y = _player->position[0].y;
	}
      j = -1;
      while (++j < (int)(listCentiped.size()))
	{
	  i = -1;
	  while (++i < (int)(listCentiped[j].size()))
	    {
	      if (_player->position[0].x == listCentiped[j][i].x && _player->position[0].y == listCentiped[j][i].y)
		{
		  _isover = true;
		  return ;
		}
	    }
	}
      i = -1;
      while (_shoot != NULL && ++i < SPEEDSHOOT)
	{
	  _shoot->y--;
	  if (_map->tile[_shoot->x + _shoot->y * MSX] == arcade::TileType::OBSTACLE)
	    {
	      hitBlock(_shoot->x, _shoot->y, 1);
	      delete _shoot;
	      _shoot = NULL;
	    }
	  else if (_shoot->y < 0 || _map->tile[_shoot->y * MSX + _shoot->x] == arcade::TileType::BLOCK)
	    {
	      delete _shoot;
	      _shoot = NULL;
	    }
	  else
	    checkHitCentiped();
	}

      //freeze++;
      checkList();
    }
  else
    _isend = true;
}

arcade::WhereAmI const *Centiped::getPlayer(void) const
{
  return (this->_player);
}

arcade::GetMap const *Centiped::getMap(void) const
{
  arcade::GetMap	*map;
  int			i;
  int			j;

  map = new arcade::GetMap[MSX * MSY * sizeof(arcade::TileType)];
  map->type = arcade::CommandType::GET_MAP;
  map->width = MSX;
  map->height = MSY;

  i = -1;
  while (++i < MSX * MSY)
    map->tile[i] = _map->tile[i];

  j = -1;
  while (++j < (int)(listCentiped.size()))
    {
      i = -1;
      while (++i < (int)(listCentiped[j].size()))
	map->tile[listCentiped[j][i].x + listCentiped[j][i].y * MSX] = arcade::TileType::EVIL_DUDE;
    }

  if (_shoot != NULL)
    map->tile[_shoot->x + _shoot->y * MSX] = arcade::TileType::MY_SHOOT;
  return (map);
}

std::string const &Centiped::getGameName(void) const
{
  return (this->_namegame);
}

arcade::Position const &Centiped::getFluidMove(int ) const
{

}

void		Centiped::initMap()
{
  int		x;
  int		y;
  obstacle	o;

  _map = new arcade::GetMap[MSX * MSY * sizeof(arcade::TileType)];
  _map->type = arcade::CommandType::GET_MAP;
  _map->width = MSX;
  _map->height = MSY;

  x = -1;
  while (++x < MSX * MSY)
    _map->tile[x] = arcade::TileType::EMPTY;

  x = 0;
  while (x < MSX * MSY / 30)
    {
      y = (rand() % (MSX * MSY - MSX * MSY / 5)) + MSX;
      if (_map->tile[y] == arcade::TileType::EMPTY)
	{
	  o.y = y / MSX;
	  o.x = y % MSX;
	  o.vie = NBVO;
	  listObstacle.push_back(o);
	  _map->tile[y] = arcade::TileType::OBSTACLE;
	  x++;
	}
    }
}

void		Centiped::initPlayer()
{
  _player = new arcade::WhereAmI[sizeof(arcade::Position)];
  _player->type = arcade::CommandType::WHERE_AM_I;
  _player->lenght = 1;
  _player->position[0].x = MSX / 2;
  _player->position[0].y = MSY - 1;
}

void    Play()
{
  Centiped centiped;
  char c;
  arcade::CommandType tmp;
  arcade::WhereAmI *player = (arcade::WhereAmI *) centiped.getPlayer();
  arcade::GetMap *map = (arcade::GetMap *) centiped.getMap();

  c = 0;
  while (!std::cin.eof())
    {
      std::cin.get(c);
      if (c == 0)
	{
	  tmp = player->type;
	  player->type = (arcade::CommandType) c;
	  std::cout.write((char *) player, sizeof(arcade::WhereAmI) + sizeof(arcade::Position) * player->lenght);
	  player->type = tmp;
	}
      else if (c == 1)
	{
	  map->type = (arcade::CommandType) c;
	  std::cout.write((char *) map, sizeof(arcade::GetMap) + sizeof(arcade::TileType) * map->width * map->height);
	}
      else if ((arcade::CommandType) c == arcade::CommandType::GO_UP ||
	       (arcade::CommandType) c == arcade::CommandType::GO_LEFT ||
	       (arcade::CommandType) c == arcade::CommandType::GO_DOWN ||
	       (arcade::CommandType) c == arcade::CommandType::GO_RIGHT)
	{
	  player->type = (arcade::CommandType) c;
	}
      else
	{
	  centiped.play((arcade::CommandType) c);
	}
      std::cin.get(c);
      c = 0;
    }
}

extern "C"
{
  IGame *createGame()
  {
    return new Centiped;
  }
}
