//
// Nibbler.cpp for  in /home/laurent/rendu/cpp_arcade/games
//
// Made by laurent
// Login   <laurent@epitech.net>
//
// Started on  Fri Apr  7 10:28:16 2017 laurent
// Last update Sun Apr  9 23:37:56 2017 Rayan
//

#include "Nibbler.hh"

Nibbler::Nibbler()
{
  srand(time(NULL));
  this->_namegame = "nibbler";
  this->_isover = false;
  this->_score = 0;
  this->_map = initMap(1);
  this->_player = initPlayer();
  this->_time = 990;
  this->_direction = arcade::CommandType::GO_RIGHT;
}

Nibbler::~Nibbler()
{
  delete[] this->_map;
  delete[] this->_player;
}

bool const &Nibbler::IsEnd(void) const
{
  return (this->_isover);
}

bool const &Nibbler::IsGameOver(void) const
{
  return (this->_isover);
}

size_t const &Nibbler::getTime(void) const
{
  return (this->_time);
}

size_t const &Nibbler::getScore(void) const
{
  return (this->_score);
}

arcade::WhereAmI const *Nibbler::getPlayer(void) const
{
  return (this->_player);
}

arcade::GetMap const *Nibbler::getMap(void) const
{
  return (this->_map);
}

std::string const &Nibbler::getGameName(void) const
{
  return (this->_namegame);
}

arcade::Position const &Nibbler::getFluidMove(int) const
{

}

void	Nibbler::play(arcade::CommandType command)
{
  static int	i = 0;

  if (i == 5)
    {
      this->_time -= 10;
      i = 0;
    }
  else
    i = i + 1;
  if (this->_time <= 0)
    this->_isover = true;
  this->move(command);
  this->NiblEat();
  this->checkFinish();
}

std::string             Nibbler::readMap(std::string map_path)
{
  std::ifstream file(map_path, std::ios::in);
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

arcade::GetMap          *Nibbler::initMap(size_t level)
{
  arcade::GetMap        *map;
  std::string           file;
  uint16_t              width;
  uint16_t              height;
  int                   y;
  int                   x;
  unsigned int          i;

  width = 17;
  height = 19;
  if (level == 1)
      file = this->readMap("./textures/nibbler/lvl1.txt");
  if (level == 2)
    file = this->readMap("./textures/nibbler/lvl2.txt");
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
	  else if (file[i] == ' ')
	    map->tile[(y * map->width) + x] = arcade::TileType::EMPTY;
	  else if (file[i] == 'o')
	    map->tile[(y * map->width) + x] = arcade::TileType::POWERUP;
	  x = x + 1;
	  i = i + 1;
	}
      y = y + 1;
    }
  return (map);
}

arcade::WhereAmI	*Nibbler::initPlayer()
{
  arcade::WhereAmI	*player;
  int			y;
  int			lenght;

  lenght = 4;
  player = new arcade::WhereAmI[lenght * sizeof(arcade::Position)];
  player->type = arcade::CommandType::WHERE_AM_I;
  player->lenght = lenght;
  y = 0;
  while (y < player->lenght)
    {
      player->position[y].x = (this->_map->width / 2) - y;
      player->position[y].y = (this->_map->height - 2);
      y = y + 1;
    }
  return (player);
}

void    Nibbler::turnLeft()
{
  this->_direction = arcade::CommandType::GO_LEFT;
  this->_prev.x = this->_player->position[0].x;
  this->_prev.y = this->_player->position[0].y;
  this->_player->position[0].x = this->_player->position[0].x - 1;
  this->_player->position[0].y = this->_player->position[0].y;
  this->FollowMe();
}

void    Nibbler::turnRight()
{
  this->_direction = arcade::CommandType::GO_RIGHT;
  this->_prev.x = this->_player->position[0].x;
  this->_prev.y = this->_player->position[0].y;
  this->_player->position[0].x = this->_player->position[0].x + 1;
  this->_player->position[0].y = this->_player->position[0].y;
  this->FollowMe();
}

void    Nibbler::turnUp()
{
  this->_direction = arcade::CommandType::GO_UP;
  this->_prev.x = this->_player->position[0].x;
  this->_prev.y = this->_player->position[0].y;
  this->_player->position[0].x = this->_player->position[0].x;
  this->_player->position[0].y = this->_player->position[0].y - 1;
  this->FollowMe();
}

void    Nibbler::turnDown()
{
  this->_direction = arcade::CommandType::GO_DOWN;
  this->_prev.x = this->_player->position[0].x;
  this->_prev.y = this->_player->position[0].y;
  this->_player->position[0].x = this->_player->position[0].x;
  this->_player->position[0].y = this->_player->position[0].y + 1;
  this->FollowMe();
}

void	Nibbler::move(arcade::CommandType command)
{
  int	y;

  if (command == arcade::CommandType::GO_LEFT
      && this->_direction != arcade::CommandType::GO_RIGHT
      && this->_map->tile[(_player->position[0].y * this->_map->width) + _player->position[0].x - 1] != arcade::TileType::BLOCK)
    turnLeft();
  else if (command == arcade::CommandType::GO_RIGHT
	   && this->_direction != arcade::CommandType::GO_LEFT
	   && this->_map->tile[(_player->position[0].y * this->_map->width) + _player->position[0].x + 1] != arcade::TileType::BLOCK)
    turnRight();
  else if (command == arcade::CommandType::GO_UP
	   && this->_direction != arcade::CommandType::GO_DOWN
	   && this->_map->tile[((_player->position[0].y - 1) * this->_map->width) + _player->position[0].x] != arcade::TileType::BLOCK)
    turnUp();
  else if (command == arcade::CommandType::GO_DOWN
	   && this->_direction != arcade::CommandType::GO_UP
	   && this->_map->tile[((_player->position[0].y + 1) * this->_map->width) + _player->position[0].x] != arcade::TileType::BLOCK)
    turnDown();
  else
    {
      if (this->_direction == arcade::CommandType::GO_LEFT &&
	  this->_map->tile[(_player->position[0].y * this->_map->width) + _player->position[0].x - 1] != arcade::TileType::BLOCK)
	turnLeft();
      else if (this->_direction == arcade::CommandType::GO_RIGHT &&
	       this->_map->tile[(_player->position[0].y * this->_map->width) + _player->position[0].x + 1] != arcade::TileType::BLOCK)
	turnRight();
      else if (this->_direction == arcade::CommandType::GO_UP &&
	       this->_map->tile[((_player->position[0].y - 1) * this->_map->width) + _player->position[0].x] != arcade::TileType::BLOCK)
	turnUp();
      else if (this->_direction == arcade::CommandType::GO_DOWN &&
	       this->_map->tile[((_player->position[0].y + 1) * this->_map->width) + _player->position[0].x] != arcade::TileType::BLOCK)
	turnDown();
    }
}

void		Nibbler::NiblEat()
{
  int   y;

  y = 1;
  while (y < this->_player->lenght)
    {
      if (this->_player->position[0].x == this->_player->position[y].x &&
	  this->_player->position[0].y == this->_player->position[y].y)
	this->_isover = true;
      y = y + 1;
    }
  if (this->_map->tile[(_player->position[0].y * this->_map->width) + _player->position[0].x] == arcade::TileType::POWERUP)
    {
      this->_score = this->_score + 10;
      this->_map->tile[(_player->position[0].y * this->_map->width) + _player->position[0].x] = arcade::TileType::EMPTY;
      this->_player = this->setnewPlayer(this->_player->lenght + 1);
    }
}

arcade::WhereAmI	*Nibbler::setnewPlayer(uint16_t lenght)
{
  arcade::WhereAmI	*player;
  int			y;
  int			movex;
  int			movey;

  movex = 0;
  movey = 0;
  player = new arcade::WhereAmI[lenght * sizeof(arcade::Position)];
  player->type = arcade::CommandType::WHERE_AM_I;
  player->lenght = lenght;
  y = 0;
  while (y < this->_player->lenght)
    {
      player->position[y].x = this->_player->position[y].x;
      player->position[y].y = this->_player->position[y].y;
      y++;
    }
  if (this->_direction == arcade::CommandType::GO_UP)
    movey = 1;
  else if (this->_direction == arcade::CommandType::GO_DOWN)
    movey = -1;
  else if (this->_direction == arcade::CommandType::GO_LEFT)
    movex = 1;
  else if (this->_direction == arcade::CommandType::GO_RIGHT)
    movex = -1;
  player->position[y].x = this->_player->position[y - 1].x + movex;
  player->position[y].y = this->_player->position[y - 1].y + movey;
  delete[] this->_player;
  return (player);
}

void		Nibbler::FollowMe()
{
  int		y;
  arcade::Position tmp;

  y = 1;
  while (y < _player->lenght)
    {
      tmp.x = this->_prev.x;
      tmp.y = this->_prev.y;
      this->_prev.x = _player->position[y].x;
      this->_prev.y = _player->position[y].y;
      _player->position[y].x = tmp.x;
      _player->position[y].y = tmp.y;
      y = y + 1;
    }
}

void		Nibbler::checkFinish()
{
  int	y = 0;
  int	x = 0;
  int	nb = 0;

  while (y < this->_map->height)
    {
      x = 0;
      while (x < this->_map->width)
	{
	  if (this->_map->tile[(y * this->_map->width) + x] == arcade::TileType::POWERUP)
	    nb++;
	  x = x + 1;
	}
      y = y + 1;
    }
    if (nb == 0)
      {
	delete[] _map;
	delete[] _player;
	this->_time = 990;
	this->_map = initMap(2);
	this->_player = initPlayer();
      }
}

void    Play()
{
  Nibbler nibbler;
  char c;
  arcade::CommandType tmp;
  arcade::WhereAmI *player = (arcade::WhereAmI *) nibbler.getPlayer();
  arcade::GetMap *map = (arcade::GetMap *) nibbler.getMap();

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
	nibbler.play((arcade::CommandType) c);
      std::cin.get(c);
      c = 0;
    }
}

extern "C"
{
  IGame *createGame()
  {
    return new Nibbler();
  }
}
