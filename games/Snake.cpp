//
// Snake.cpp for Snake.cpp in /home/afou_n/cpp_arcade
//
// Made by Afou Nacerdine
// Login   <nacerdine.afou@epitech.net>
//
// Started on  Fri Mar 31 12:43:10 2017 Afou Nacerdine
// Last update Sun Apr  9 23:37:40 2017 Rayan
//

#include "Snake.hh"

Snake::Snake()
{
  srand(time(NULL));
  this->_namegame = "snake";
  this->_isover = false;
  this->_score = 0;
  this->_map = initMap();
  initPlayer();
  this->_player->type = arcade::CommandType::GO_DOWN;
  while (setposApple() == false);
}

Snake::~Snake()
{
  delete[] this->_map;
  delete[] this->_player;
}

bool const &Snake::IsEnd(void) const
{
  return (this->_isover);
}

bool const &Snake::IsGameOver(void) const
{
  return (this->_isover);
}

size_t const &Snake::getScore(void) const
{
  return (this->_score);
}

void	Snake::play(arcade::CommandType command)
{
  this->move(command);
  this->collision();
}

arcade::WhereAmI const *Snake::getPlayer(void) const
{
  return (this->_player);
}

arcade::GetMap const *Snake::getMap(void) const
{
  return (this->_map);
}

std::string const &Snake::getGameName(void) const
{
  return (this->_namegame);
}

arcade::Position const &Snake::getFluidMove(int ) const
{

}

arcade::GetMap	*Snake::initMap()
{
  arcade::GetMap	*map;
  int		x;
  int		y;
  uint16_t width = 40;
  uint16_t height = 30;

  map = (arcade::GetMap*) ::operator new(sizeof(arcade::GetMap) + width * height * sizeof(arcade::TileType));
  map->type = arcade::CommandType::GET_MAP;
  map->width = width;
  map->height = height;
  y = 0;
  while (y < map->height)
    {
      x = 0;
      while (x < map->width)
	{
	  if (y == 0 || y + 1 == map->height || x == 0 || x + 1 == map->width)
	    map->tile[((map->width * y) + x)] = arcade::TileType::BLOCK;
	  else
	    map->tile[((map->width * y) + x)] = arcade::TileType::EMPTY;
	  x = x + 1;
	}
      y = y + 1;
    }
  return (map);
}

void	*Snake::initPlayer()
{
  arcade::WhereAmI	*player;
  int			y;
  int			lenght;

  lenght = 4;
  _player = (arcade::WhereAmI*) ::operator new(sizeof(arcade::WhereAmI) + lenght * sizeof(arcade::Position));
  _player->type = arcade::CommandType::WHERE_AM_I;
  _player->lenght = lenght;
  y = 0;
  while (y < _player->lenght)
    {
      _player->position[y].x = (this->_map->width / 2);
      _player->position[y].y = (this->_map->height / 2) - y;
      y = y + 1;
    }
}


void	Snake::move(arcade::CommandType command)
{
  int	y;

  if (command == arcade::CommandType::GO_LEFT
      && _player->type != arcade::CommandType::GO_RIGHT)
      _player->type = arcade::CommandType::GO_LEFT;
  else if (command == arcade::CommandType::GO_RIGHT
	   && _player->type != arcade::CommandType::GO_LEFT)
      _player->type = arcade::CommandType::GO_RIGHT;
  else if (command == arcade::CommandType::GO_UP
	   && _player->type != arcade::CommandType::GO_DOWN)
      _player->type = arcade::CommandType::GO_UP;
  else if (command == arcade::CommandType::GO_DOWN
	   && _player->type != arcade::CommandType::GO_UP)
      _player->type = arcade::CommandType::GO_DOWN;
  y = _player->lenght;
  while (--y > 0)
    {
      _player->position[y].x = _player->position[y - 1].x;
      _player->position[y].y = _player->position[y - 1].y;
    }
  if (_player->type == arcade::CommandType::GO_LEFT ||
      _player->type == arcade::CommandType::GO_RIGHT)
    _player->position[0].x += (_player->type == arcade::CommandType::GO_LEFT) ? -1 : 1;
  if (_player->type == arcade::CommandType::GO_UP ||
      _player->type == arcade::CommandType::GO_DOWN)
    _player->position[0].y += (_player->type == arcade::CommandType::GO_UP) ? -1 : 1;
}

bool	Snake::setposApple()
{
  int	y;

  this->_posapple.y = rand() % this->_map->height;
  this->_posapple.x = rand() % this->_map->width;
  y = 0;
  if (this->_posapple.y == 0 || this->_posapple.y + 1 == this->_map->height
      || this->_posapple.x == 0 || this->_posapple.x + 1 == this->_map->width)
    return (false);
  while (y < this->_player->lenght)
    {
      if (this->_player->position[y].x == this->_posapple.x || this->_player->position[y].y == this->_posapple.y)
	return (false);
      y = y + 1;
    }
  this->_map->tile[((this->_map->width * this->_posapple.y) + this->_posapple.x)] = arcade::TileType::POWERUP;
  return (true);
}

arcade::WhereAmI *Snake::setnewPlayer(uint16_t lenght)
{
  arcade::WhereAmI	*player;
  int			y;
  int			movex;
  int			movey;

  movex = 0;
  movey = 0;
  player = (arcade::WhereAmI*) ::operator new (sizeof(arcade::WhereAmI) + lenght * sizeof(arcade::Position));
  player->type = _player->type;
  player->lenght = lenght;
  y = 0;
  while (y < this->_player->lenght)
    {
      player->position[y].x = this->_player->position[y].x;
      player->position[y].y = this->_player->position[y].y;
      y = y + 1;
    }
  if (_player->type == arcade::CommandType::GO_UP)
    movey = 1;
  else if (_player->type == arcade::CommandType::GO_DOWN)
    movey = -1;
  else if (_player->type == arcade::CommandType::GO_LEFT)
    movex = 1;
  else if (_player->type == arcade::CommandType::GO_RIGHT)
    movex = -1;
  player->position[y].x = this->_player->position[y - 1].x + movex;
  player->position[y].y = this->_player->position[y - 1].y + movey;
  delete this->_player;
  return (player);
}

void	Snake::collision()
{
  int	y;

  y = 1;
  while (y < this->_player->lenght)
    {
      if (this->_player->position[0].x == this->_player->position[y].x &&
	  this->_player->position[0].y == this->_player->position[y].y)
	this->_isover = true;
      y = y + 1;
    }
  if (this->_player->position[0].y == 0 || this->_player->position[0].y + 1 == this->_map->height ||
      this->_player->position[0].x == 0 || this->_player->position[0].x + 1 == this->_map->width)
    this->_isover = true;
  else if (this->_player->position[0].y == this->_posapple.y &&
	   this->_player->position[0].x == this->_posapple.x)
  {
    this->_map->tile[((this->_map->width * this->_posapple.y) + this->_posapple.x)] = arcade::TileType::EMPTY;
    this->_player = this->setnewPlayer(this->_player->lenght + 1);
    while (setposApple() == false);
    this->_score = this->_score + 100;
  }
}

void	Play()
{
  Snake snake;
  char c;
  arcade::CommandType tmp;
  arcade::WhereAmI *player = (arcade::WhereAmI *) snake.getPlayer();
  arcade::GetMap *map = (arcade::GetMap *) snake.getMap();

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
	  snake.play((arcade::CommandType) c);
	}
      std::cin.get(c);
      c = 0;
    }
}

extern "C"
{
  IGame *createGame()
  {
    return new Snake();
  }
}
