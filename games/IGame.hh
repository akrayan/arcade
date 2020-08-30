//
// Created by dupeg on 09/03/17.
//

#ifndef CPP_ARCADE_IGAME_HH
#define CPP_ARCADE_IGAME_HH

#include <iostream>
#include <unistd.h>
#include <map>
#include <vector>
#include <fstream>
#include <ncurses.h>
#include "Protocol.hpp"

class   IGame
{
public:
    virtual ~IGame() {};

    /// For know if the game is finish
    virtual bool const &IsEnd(void) const = 0;

    /// For know if the game is finish width Game Over or not
    virtual bool const &IsGameOver(void) const = 0;

    /// For get the game score
    virtual size_t const &getScore(void) const = 0;

    /// Call for the manage the game
    virtual void  play(arcade::CommandType) = 0;

    /// Get the position of player
    virtual arcade::WhereAmI const *getPlayer(void) const = 0;

    /// Get the Map
    virtual arcade::GetMap const *getMap(void) const = 0;

    /// Get the game name
    virtual std::string const &getGameName(void) const = 0;

    ///// For have fluid movement return value between 0 and 100
    //// 0 for player move
    /// 1 for shoot move
    virtual arcade::Position const &getFluidMove(int ) const = 0;
};

extern "C"
{
  IGame *createGame();
  void Play();
}

#endif //CPP_ARCADE_IGAME_HH
