//
// Pacman.cpp for Pacman.cpp in /home/afou_n/tek2/c++/projets/cpp_arcade
//
// Made by Afou Nacerdine
// Login   <nacerdine.afou@epitech.eu>
//
// Started on  Wed Apr  5 14:16:10 2017 Afou Nacerdine
// Last update Sun Apr  9 23:38:13 2017 Rayan
//

#include "Pacman.hh"

Pacman::Pacman()
{
  srand(time(NULL));
  begininGame(1);
  this->_namegame = "pacman";
  this->_isover = false;
  this->_score = 0;
  this->_lives = 2;
  this->_restart = true;
  this->_vulnerable = 0;
  this->_prev = arcade::CommandType::ILLEGAL;
  this->_map = initMap();
  this->_mapinitial = initMap();
  this->_evils = initEvil();
  this->_player = initPlayer();
  this->_wait = 60;
}

Pacman::~Pacman()
{
  delete[] this->_map;
  delete[] this->_mapinitial;
  delete[] this->_player;
}

bool const &Pacman::IsEnd(void) const
{
  return (this->_isover);
}

bool const &Pacman::IsGameOver(void) const
{
  return (this->_isover);
}

size_t const &Pacman::getScore(void) const
{
  return (this->_score);
}

void  Pacman::play(arcade::CommandType command)
{
  if (_wait == 0)
    _restart = false;
  delete[] this->_map;
  this->_map = copyMap(this->_mapinitial);
  if (_restart == false)
    {
      movePlayer(command);
      pacEat();
    }
  this->_mapinitial = copyMap(this->_map);
  if (_restart == false)
    moveAi();
  setEvilmap();
  if (_wait >= 0)
    _wait -= 1;
}

arcade::WhereAmI const *Pacman::getPlayer(void) const
{
  return (this->_player);
}

arcade::GetMap const *Pacman::getMap(void) const
{
  return (this->_map);
}

std::string const &Pacman::getGameName(void) const
{
  return (this->_namegame);
}

arcade::Position const &Pacman::getFluidMove(int ) const
{

}

std::string		Pacman::readMap()
{
  std::ifstream file("./textures/pacman/map.txt", std::ios::in);
  std::string buffer = "";
  std::string result;

  if (file)
    {
      while (getline(file, buffer))
	result = result + buffer;
    }
  file.close();
  return (result);
}

arcade::GetMap		*Pacman::initMap()
{
  arcade::GetMap	*map;
  std::string		file;
  int			width;
  int			height;
  int			y;
  int			x;
  unsigned int		i;

  width = 28;
  height = 31;
  file = this->readMap();
  map = new arcade::GetMap[width * height * sizeof(arcade::TileType)];
  map->height = height;
  map->width = width;
  map->type = arcade::CommandType::GET_MAP;
  y = 0;
  i = 0;
  while (y < map->height)
    {
      x = 0;
      while (x < map->width)
	{
	  if (file[i] == '#')
	    map->tile[(y * map->width) + x] = arcade::TileType::BLOCK;
	  if (file[i] == ' ')
	    map->tile[(y * map->width) + x] = arcade::TileType::EMPTY;
	  if (file[i] == 'o')
	    map->tile[(y * map->width) + x] = arcade::TileType::MY_SHOOT;
	  if (file[i] == '.')
	    map->tile[(y * map->width) + x] = arcade::TileType::POWERUP;
	  x = x + 1;
	  i = i + 1;
	}
      y = y + 1;
    }
  return (map);
}

arcade::WhereAmI	*Pacman::initPlayer()
{
  arcade::WhereAmI	*player;
  int			y;
  int			lenght;

  lenght = 1;
  player = new arcade::WhereAmI[lenght * sizeof(arcade::Position)];
  player->type = arcade::CommandType::WHERE_AM_I;
  player->lenght = lenght;
  y = 0;
  while (y < player->lenght)
    {
      player->position[y].x = (this->_map->width / 2) - 1;
      player->position[y].y = (this->_map->height / 2) + (this->_map->height / 4) + 1;
      y = y + 1;
    }
  return (player);
}

std::vector<Pacman::Evil>	Pacman::initEvil()
{
  std::vector<Pacman::Evil>	evils;
  Pacman::Evil			tmp;
  int				lenght;
  int				y;

  lenght = 4;
  y = 0;
  while (y < lenght)
    {
      if (y == 0)
	{
	  tmp.position.x = (this->_map->width / 2) - 1;
	  tmp.position.y = (this->_map->height / 2) - 4;
	}
      else
	{
	  tmp.position.x = (this->_map->width / 2) + y - 2;
	  tmp.position.y = (this->_map->height / 2) - 1;
	}
      tmp.stat = arcade::TileType::EVIL_SHOOT;
      evils.push_back(tmp);
      y = y + 1;
    }
  return (evils);
}

arcade::GetMap		*Pacman::copyMap(arcade::GetMap *oldMap)
{
  arcade::GetMap	*newMap;
  int			y;
  int			x;

  newMap = new arcade::GetMap[oldMap->width * oldMap->height * sizeof(arcade::TileType)];
  newMap->height = oldMap->height;
  newMap->width = oldMap->width;
  newMap->type = arcade::CommandType::GET_MAP;
  y = 0;
  while (y < newMap->height)
    {
      x = 0;
      while (x < newMap->width)
	{
	  newMap->tile[(y * oldMap->width) + x] = oldMap->tile[(y * oldMap->width) + x];
	  x = x + 1;
	}
      y = y + 1;
    }
  return (newMap);
}

void			Pacman::setEvilmap()
{
  int			y;

  y = 0;
  while (y < this->_evils.size())
    {
      this->_map->tile[(_evils[y].position.y * this->_map->width) + _evils[y].position.x] = this->_evils[y].stat;
      y = y + 1;
    }
}


void		Pacman::movePlayer(arcade::CommandType command)
{
  if (command == arcade::CommandType::GO_LEFT)
    {
      if (this->_map->tile[(_player->position[0].y * this->_map->width) + _player->position[0].x - 1] != arcade::TileType::BLOCK)
	{
	  this->_prev = arcade::CommandType::GO_LEFT;
	  this->_player->position[0].x = this->_player->position[0].x - 1;
	}
      else if (this->_player->position[0].x == 0 && this->_player->position[0].y == 14)
	this->_player->position[0].x = this->_map->width - 1;
    }
  else if (command == arcade::CommandType::GO_RIGHT)
    {
      if (this->_map->tile[(_player->position[0].y * this->_map->width) + _player->position[0].x + 1] != arcade::TileType::BLOCK)
	{
	  this->_prev = arcade::CommandType::GO_RIGHT;
	  this->_player->position[0].x = this->_player->position[0].x + 1;
	}
      else if (this->_player->position[0].x + 1 ==  this->_map->width && this->_player->position[0].y == 14)
	this->_player->position[0].x = 0;
    }
  else if (command == arcade::CommandType::GO_UP)
    {
      if (this->_map->tile[((_player->position[0].y - 1) * this->_map->width) + _player->position[0].x] != arcade::TileType::BLOCK)
	{
	  this->_prev = arcade::CommandType::GO_UP;
	  this->_player->position[0].y = this->_player->position[0].y - 1;
	}
    }
  else if (command == arcade::CommandType::GO_DOWN)
    {
      if (this->_map->tile[((_player->position[0].y + 1) * this->_map->width) + _player->position[0].x] != arcade::TileType::BLOCK)
	{
	  this->_prev = arcade::CommandType::GO_DOWN;
	  this->_player->position[0].y = this->_player->position[0].y + 1;
	}
    }
  if (this->_prev == arcade::CommandType::GO_LEFT && this->_prev != command)
    {
      if (this->_map->tile[(_player->position[0].y * this->_map->width) + _player->position[0].x - 1] != arcade::TileType::BLOCK)
	this->_player->position[0].x = this->_player->position[0].x - 1;
      else if (this->_player->position[0].x == 0 && this->_player->position[0].y == 14)
	this->_player->position[0].x = this->_map->width - 1;
    }
  else if (this->_prev == arcade::CommandType::GO_RIGHT && this->_prev != command)
    {
      if (this->_map->tile[(_player->position[0].y * this->_map->width) + _player->position[0].x + 1] != arcade::TileType::BLOCK)
	this->_player->position[0].x = this->_player->position[0].x + 1;
      else if (this->_player->position[0].x + 1 ==  this->_map->width && this->_player->position[0].y == 14)
	this->_player->position[0].x = 0;
    }
  else if (this->_prev == arcade::CommandType::GO_UP && this->_prev != command)
    {
      if (this->_map->tile[((_player->position[0].y - 1) * this->_map->width) + _player->position[0].x] != arcade::TileType::BLOCK)
	{
	  this->_player->position[0].y = this->_player->position[0].y - 1;
	}
    }
  else if (this->_prev == arcade::CommandType::GO_DOWN && this->_prev != command)
    {
      if (this->_map->tile[((_player->position[0].y + 1) * this->_map->width) + _player->position[0].x] != arcade::TileType::BLOCK)
	{
	  this->_player->position[0].y = this->_player->position[0].y + 1;
	}
    }
}

void		Pacman::pacEat()
{
  int		y;

  y = 0;
  if (this->_map->tile[(_player->position[0].y * this->_map->width) + _player->position[0].x] == arcade::TileType::POWERUP)
    {
      this->_score = this->_score + 10;
      this->_map->tile[(_player->position[0].y * this->_map->width) + _player->position[0].x] = arcade::TileType::EMPTY;
      if (checkEatAll() == true)
	_isover = true;
    }
  else if (this->_map->tile[(_player->position[0].y * this->_map->width) + _player->position[0].x] == arcade::TileType::MY_SHOOT)
    {
      while (y < _evils.size())
	{
	  _evils[y].stat = arcade::TileType::EVIL_DUDE;
	  y = y + 1;
	}
      this->_vulnerable = 75;
      this->_map->tile[(_player->position[0].y * this->_map->width) + _player->position[0].x] = arcade::TileType::EMPTY;
    }
}

bool			Pacman::checkEatAll()
{
  int			y;
  int			x;

  y = 0;
  while (y < _map->height)
    {
      x = 0;
      while (x < _map->width)
	{
	  if (this->_map->tile[(y * this->_map->width) + x] == arcade::TileType::POWERUP)
	    return (false);
	  x = x + 1;
	}
      y = y + 1;
    }
  return (true);
}

void			Pacman::moveAi()
{
  int			y;

  begininGame(0);

  isVulnerable();

  aiRandomOne(0);
  aiRandomTwo(1);
  aiRandomThree(2);
  aiRandomFour(3);
  isVulnerable();
  y = 0;
  while (y < _evils.size())
    {
      y = y + 1;
    }

}

void			Pacman::isVulnerable()
{
  int			y;
  int			again = 0;

  if (_vulnerable > 0)
    {
      y = 0;
      while (y < _evils.size())
	{
	  if (_evils[y].position.x == _player->position[0].x &&
	      _evils[y].position.y == _player->position[0].y &&
	      _vulnerable > 0)
	    {
	      if (_evils[y].position.x != (this->_map->width / 2) + y - 2 &&
		  _evils[y].position.y != (this->_map->height / 2) - 1)
		{
		  _evils[y].position.x = (this->_map->width / 2) + y - 2;
		  _evils[y].position.y = (this->_map->height / 2) - 1;
		  if (again == 0)
		    {
		      if (y == 0)
			outAiOne(1);
		      if (y == 1)
			outAiTwo(1);
		      if (y == 2)
			outAiThree(1);
		      if (y == 3)
			outAiFour(1);
		    }
		}
	    }
	  y = y + 1;
	}
      if (again == 0)
	_vulnerable -= 1;
    }
  else
    {
      y = 0;
      while (y < _evils.size())
	{
	  if (_evils[y].position.x == _player->position[0].x &&
	      _evils[y].position.y == _player->position[0].y &&
	      _vulnerable == 0)
	    {
	      if (_lives > 0)
		{
		  resetGame();
		  _lives -= 1;
		}
	      else
		_isover = true;
	    }
	  _evils[y].stat = arcade::TileType::EVIL_SHOOT;
	  y = y + 1;
	}

    }
  y = 0;
  while (y < _evils.size())
    {
      if (_evils[y].position.x == (this->_map->width / 2) + y - 2 &&
	  _evils[y].position.y == (this->_map->height / 2) - 1)
	{
	  if (again == 0)
	    {
	      if (y == 0)
		outAiOne(0);
	      if (y == 1)
		outAiTwo(0);
	      if (y == 2)
		outAiThree(0);
	      if (y == 3)
		outAiFour(0);
	      again += 1;
	    }
	}
      y = y + 1;
    }
  if (again == 1)
    again = 0;
}

void			Pacman::resetGame()
{
  int			y;

  y = 0;
  while (y < _evils.size())
    {
      if (y == 0)
	{
	  _evils[y].position.x = (this->_map->width / 2) - 1;
	  _evils[y].position.y = (this->_map->height / 2) - 4;
	}
      else
	{
	  _evils[y].position.x = (this->_map->width / 2) + y - 2;
	  _evils[y].position.y = (this->_map->height / 2) - 1;
	}
      y = y + 1;
    }
  _player->position[0].x = (this->_map->width / 2) - 1;
  _player->position[0].y = (this->_map->height / 2) + (this->_map->height / 4) + 1;
  begininGame(1);
  _restart = true;
  _wait = 60;
}

void			Pacman::aiRandomOne(int y)
{
  static int		again = 0;
  static arcade::CommandType	random;

  if (_evils[y].position.x == (this->_map->width / 2) + y - 2 &&
      _evils[y].position.y == (this->_map->height / 2) - 1)
    return ;

  if (again == 0)
    {
      random = (arcade::CommandType)((rand() % 4) + 2);
      while ((random == arcade::CommandType::GO_UP && this->_map->tile[((_evils[y].position.y - 1) * this->_map->width) + _evils[y].position.x] == arcade::TileType::BLOCK) ||
	     (random == arcade::CommandType::GO_DOWN && this->_map->tile[((_evils[y].position.y + 1) * this->_map->width) + _evils[y].position.x] == arcade::TileType::BLOCK) ||
	     (random == arcade::CommandType::GO_LEFT && this->_map->tile[((_evils[y].position.y) * this->_map->width) + _evils[y].position.x - 1] == arcade::TileType::BLOCK) ||
	     (random == arcade::CommandType::GO_RIGHT && this->_map->tile[((_evils[y].position.y) * this->_map->width) + _evils[y].position.x + 1] == arcade::TileType::BLOCK))
	random = (arcade::CommandType)((rand() % 4) + 2);
      again = 1;
    }
  if (again == 1)
    {
      if (random == arcade::CommandType::GO_UP)
	{
	  if (this->_map->tile[((_evils[y].position.y - 1) * this->_map->width) + _evils[y].position.x] == arcade::TileType::BLOCK)
	    again = 0;
	  else
	    _evils[y].position.y -= 1;
	}
      else if (random == arcade::CommandType::GO_DOWN)
	{
	  if (this->_map->tile[((_evils[y].position.y + 1) * this->_map->width) + _evils[y].position.x] == arcade::TileType::BLOCK)
	    again = 0;
	  else
	    _evils[y].position.y += 1;
	}
      else if (random == arcade::CommandType::GO_LEFT)
	{
	  if (this->_map->tile[((_evils[y].position.y) * this->_map->width) + _evils[y].position.x - 1] == arcade::TileType::BLOCK)
	    again = 0;
	  else
	    _evils[y].position.x -= 1;
	}
      else if (random == arcade::CommandType::GO_RIGHT)
	{
	  if (this->_map->tile[((_evils[y].position.y) * this->_map->width) + _evils[y].position.x + 1] == arcade::TileType::BLOCK)
	    again = 0;
	  else
	    _evils[y].position.x += 1;
	}
    }
}

void			Pacman::aiRandomTwo(int y)
{
  static int		again = 0;
  static arcade::CommandType	random;

  if (_evils[y].position.x == (this->_map->width / 2) + y - 2 &&
      _evils[y].position.y == (this->_map->height / 2) - 1)
    return ;
  if (again == 0)
    {
      random = (arcade::CommandType)((rand() % 4) + 2);
      while ((random == arcade::CommandType::GO_UP && this->_map->tile[((_evils[y].position.y - 1) * this->_map->width) + _evils[y].position.x] == arcade::TileType::BLOCK) ||
	     (random == arcade::CommandType::GO_DOWN && this->_map->tile[((_evils[y].position.y + 1) * this->_map->width) + _evils[y].position.x] == arcade::TileType::BLOCK) ||
	     (random == arcade::CommandType::GO_LEFT && this->_map->tile[((_evils[y].position.y) * this->_map->width) + _evils[y].position.x - 1] == arcade::TileType::BLOCK) ||
	     (random == arcade::CommandType::GO_RIGHT && this->_map->tile[((_evils[y].position.y) * this->_map->width) + _evils[y].position.x + 1] == arcade::TileType::BLOCK))
	random = (arcade::CommandType)((rand() % 4) + 2);
      again = 1;
    }
  if (again == 1)
    {
      if (random == arcade::CommandType::GO_UP)
	{
	  if (this->_map->tile[((_evils[y].position.y - 1) * this->_map->width) + _evils[y].position.x] == arcade::TileType::BLOCK)
	    again = 0;
	  else
	    _evils[y].position.y -= 1;
	}
      else if (random == arcade::CommandType::GO_DOWN)
	{
	  if (this->_map->tile[((_evils[y].position.y + 1) * this->_map->width) + _evils[y].position.x] == arcade::TileType::BLOCK)
	    again = 0;
	  else
	    _evils[y].position.y += 1;
	}
      else if (random == arcade::CommandType::GO_LEFT)
	{
	  if (this->_map->tile[((_evils[y].position.y) * this->_map->width) + _evils[y].position.x - 1] == arcade::TileType::BLOCK)
	    again = 0;
	  else
	    _evils[y].position.x -= 1;
	}
      else if (random == arcade::CommandType::GO_RIGHT)
	{
	  if (this->_map->tile[((_evils[y].position.y) * this->_map->width) + _evils[y].position.x + 1] == arcade::TileType::BLOCK)
	    again = 0;
	  else
	    _evils[y].position.x += 1;
	}
    }
}

void			Pacman::aiRandomThree(int y)
{
  static int		again = 0;
  static arcade::CommandType	random;

  if (_evils[y].position.x == (this->_map->width / 2) + y - 2 &&
      _evils[y].position.y == (this->_map->height / 2) - 1)
    return ;
  if (again == 0)
    {
      random = (arcade::CommandType)((rand() % 4) + 2);
      while ((random == arcade::CommandType::GO_UP && this->_map->tile[((_evils[y].position.y - 1) * this->_map->width) + _evils[y].position.x] == arcade::TileType::BLOCK) ||
	     (random == arcade::CommandType::GO_DOWN && this->_map->tile[((_evils[y].position.y + 1) * this->_map->width) + _evils[y].position.x] == arcade::TileType::BLOCK) ||
	     (random == arcade::CommandType::GO_LEFT && this->_map->tile[((_evils[y].position.y) * this->_map->width) + _evils[y].position.x - 1] == arcade::TileType::BLOCK) ||
	     (random == arcade::CommandType::GO_RIGHT && this->_map->tile[((_evils[y].position.y) * this->_map->width) + _evils[y].position.x + 1] == arcade::TileType::BLOCK))
	random = (arcade::CommandType)((rand() % 4) + 2);
      again = 1;
    }
  if (again == 1)
    {
      if (random == arcade::CommandType::GO_UP)
	{
	  if (this->_map->tile[((_evils[y].position.y - 1) * this->_map->width) + _evils[y].position.x] == arcade::TileType::BLOCK)
	    again = 0;
	  else
	    _evils[y].position.y -= 1;
	}
      else if (random == arcade::CommandType::GO_DOWN)
	{
	  if (this->_map->tile[((_evils[y].position.y + 1) * this->_map->width) + _evils[y].position.x] == arcade::TileType::BLOCK)
	    again = 0;
	  else
	    _evils[y].position.y += 1;
	}
      else if (random == arcade::CommandType::GO_LEFT)
	{
	  if (this->_map->tile[((_evils[y].position.y) * this->_map->width) + _evils[y].position.x - 1] == arcade::TileType::BLOCK)
	    again = 0;
	  else
	    _evils[y].position.x -= 1;
	}
      else if (random == arcade::CommandType::GO_RIGHT)
	{
	  if (this->_map->tile[((_evils[y].position.y) * this->_map->width) + _evils[y].position.x + 1] == arcade::TileType::BLOCK)
	    again = 0;
	  else
	    _evils[y].position.x += 1;
	}
    }
}

void			Pacman::aiRandomFour(int y)
{
  static int		again = 0;
  static arcade::CommandType	random;

  if (_evils[y].position.x == (this->_map->width / 2) + y - 2 &&
      _evils[y].position.y == (this->_map->height / 2) - 1)
    return ;
  if (again == 0)
    {
      random = (arcade::CommandType)((rand() % 4) + 2);
      while ((random == arcade::CommandType::GO_UP && this->_map->tile[((_evils[y].position.y - 1) * this->_map->width) + _evils[y].position.x] == arcade::TileType::BLOCK) ||
	     (random == arcade::CommandType::GO_DOWN && this->_map->tile[((_evils[y].position.y + 1) * this->_map->width) + _evils[y].position.x] == arcade::TileType::BLOCK) ||
	     (random == arcade::CommandType::GO_LEFT && this->_map->tile[((_evils[y].position.y) * this->_map->width) + _evils[y].position.x - 1] == arcade::TileType::BLOCK) ||
	     (random == arcade::CommandType::GO_RIGHT && this->_map->tile[((_evils[y].position.y) * this->_map->width) + _evils[y].position.x + 1] == arcade::TileType::BLOCK))
	random = (arcade::CommandType)((rand() % 4) + 2);
      again = 1;
    }
  if (again == 1)
    {
      if (random == arcade::CommandType::GO_UP)
	{
	  if (this->_map->tile[((_evils[y].position.y - 1) * this->_map->width) + _evils[y].position.x] == arcade::TileType::BLOCK)
	    again = 0;
	  else
	    _evils[y].position.y -= 1;
	}
      else if (random == arcade::CommandType::GO_DOWN)
	{
	  if (this->_map->tile[((_evils[y].position.y + 1) * this->_map->width) + _evils[y].position.x] == arcade::TileType::BLOCK)
	    again = 0;
	  else
	    _evils[y].position.y += 1;
	}
      else if (random == arcade::CommandType::GO_LEFT)
	{
	  if (this->_map->tile[((_evils[y].position.y) * this->_map->width) + _evils[y].position.x - 1] == arcade::TileType::BLOCK)
	    again = 0;
	  else
	    _evils[y].position.x -= 1;
	}
      else if (random == arcade::CommandType::GO_RIGHT)
	{
	  if (this->_map->tile[((_evils[y].position.y) * this->_map->width) + _evils[y].position.x + 1] == arcade::TileType::BLOCK)
	    again = 0;
	  else
	    _evils[y].position.x += 1;
	}
    }
}

void			Pacman::outAiOne(int reset)
{
  static int dec = -1;

  if (reset == 1)
    {
      dec = 75;
      return ;
    }
  if (dec == 0)
    {
      _evils[0].position.x = (this->_map->width / 2) - 1;
      _evils[0].position.y = (this->_map->height / 2) - 4;
    }
  else if (dec > -1)
    dec -= 1;
}

void			Pacman::outAiTwo(int reset)
{
  static int dec = -1;

  if (reset == 1)
    {
      dec = 75;
      return ;
    }
  if (dec == 0)
    {
      _evils[1].position.x = (this->_map->width / 2) - 1;
      _evils[1].position.y = (this->_map->height / 2) - 4;
    }
  else if (dec > -1)
    dec -= 1;
}

void			Pacman::outAiThree(int reset)
{
  static int dec = -1;

  if (reset == 1)
    {
      dec = 75;
      return ;
    }
  if (dec == 0)
    {
      _evils[2].position.x = (this->_map->width / 2) - 1;
      _evils[2].position.y = (this->_map->height / 2) - 4;
    }
  else if (dec > -1)
    dec -= 1;
}

void			Pacman::outAiFour(int reset)
{
  static int dec = -1;

    if (reset == 1)
    {
      dec = 75;
      return ;
    }
  if (dec == 0)
    {
      _evils[3].position.x = (this->_map->width / 2) - 1;
      _evils[3].position.y = (this->_map->height / 2) - 4;
    }
  else if (dec > -1)
    dec -= 1;
}

void			Pacman::begininGame(int reset)
{
  static int i = 0;

  if (reset == 1)
    {
      i = 0;
      return ;
    }
  if (i == 75)
    {
      _evils[1].position.x = (this->_map->width / 2) - 1;
      _evils[1].position.y = (this->_map->height / 2) - 4;
    }
  if (i == 150)
    {
      _evils[2].position.x = (this->_map->width / 2) - 1;
      _evils[2].position.y = (this->_map->height / 2) - 4;
    }
  if (i == 225)
    {
      _evils[3].position.x = (this->_map->width / 2) - 1;
      _evils[3].position.y = (this->_map->height / 2) - 4;
    }
  if (i <= 226)
    i = i + 1;
}

void    Play()
{
  Pacman pacman;
  char c;
  arcade::CommandType tmp;
  arcade::WhereAmI *player = (arcade::WhereAmI *) pacman.getPlayer();
  arcade::GetMap *map = (arcade::GetMap *) pacman.getMap();

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
	player->type = (arcade::CommandType) c;
      else
	pacman.play((arcade::CommandType) c);
      std::cin.get(c);
      c = 0;
    }
}

extern "C"
{
  IGame *createGame()
  {
    return new Pacman();
  }
}
