// Kind of Advanced Language Assistant Laboratory 2006-2042
// Epitech 1999-2042
// Jason Brillante brilla_a brilla_b
// Have you played Atari today?
//
// WELCOME TO THE ARCADE
// ENJOY OR DIE

#ifndef			__ARCADE_PROTOCOL_HPP__
# define		__ARCADE_PROTOCOL_HPP__
# include		<stdint.h>

namespace		arcade
{
  enum class		CommandType : uint16_t
  {
      WHERE_AM_I	= 0,		// RETURN A WHERE AM I STRUCTURE
      GET_MAP		= 1,		// RETURN A GETMAP STRUCTURE
      GO_UP		= 2,		// MOVE THE CHARACTER UP
      GO_DOWN		= 3,		// MOVE THE CHARACTER DOWN
      GO_LEFT		= 4,		// MOVE THE CHARACTER LEFT
      GO_RIGHT		= 5,		// MOVE THE CHARACTER RIGHT
      GO_FORWARD	= 6,		// MOVE THE CHARACTER FORWARD (FOR SNAKE)
      SHOOT		= 7,		// SHOOT (FOR SOLAR FOX AND CENTIPEDE)
      ILLEGAL		= 8,		// THE INSTRUCTION WAS ILLEGAL
      PLAY		= 9,		// PLAY A ROUND
      PREVGRAPH = 10,  // PREVIOUS GRAPHIQUE LIBRARY ("2")
      NEXTGRAPH = 11,  // NEXT GRAPHIQUE LIBRARY ("3")
      PREVGAME = 12,   // PREVIOUS GAME ("4")
      NEXTGAME = 13,   // NEXT GAME ("5")
      RESTART = 14,    // RESTART GAME ("8")
      MENU = 15,      // GO TO MENU ("9")
      EXIT = 16,      // EXIT GAME (ESCAPE)
    };

  enum class		TileType : uint16_t
    {
      EMPTY		= 0,		// TILE WHERE THE CHARACTER CAN GO
      BLOCK		= 1,		// TILE WHERE THE CHARACTER CANNOT GO
      OBSTACLE		= 2,		// FOR CENTIPEDE
      EVIL_DUDE		= 3,		// EVIL DUDE
      EVIL_SHOOT	= 4,		// EVIL SHOOT
      MY_SHOOT		= 5,
      POWERUP		= 6,		// POWERUP
      OTHER		= 7,		// ANYTHING THAT WILL BE IGNORED BY THE KOALINETTE
    };

  /// The format is width, height, and width * height * sizeof(TileType) quantity of TileType
  struct		GetMap
  {
    CommandType		type;
    uint16_t		width;
    uint16_t		height;
    TileType		tile[0];
  } __attribute__((packed));

  /// The format is length, length * Position quantity of TileType
  struct		Position
  {
    uint16_t		x;
    uint16_t		y;
  } __attribute__((packed));

  struct		WhereAmI
  {
    CommandType		type;
    uint16_t		lenght;
    Position		position[0];
  } __attribute__((packed));
}

#endif	//		__ARCADE_PROTOCOL_HPP__
