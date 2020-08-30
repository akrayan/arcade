//
// Created by dupeg on 11/03/17.
//

#ifndef CPP_ARCADE_IGRAPH_HH
#define CPP_ARCADE_IGRAPH_HH

#include <map>
#include "../games/IGame.hh"

class IGraph
{
public:
    virtual ~IGraph() {};

    ////// Show and Manage all interface (Menu, Game, end Menu)
    ///// if IGame == NULL show Menu
    //// else if IGame.isEnd() false show Game
    /// else show end Menu
    virtual void showInterface(IGame *) = 0;

    //// For get the name of the game select on menu
    /// (the next/prev game also thanks to arcade::CommandType)
    virtual std::string getSelectGame(arcade::CommandType) = 0;

    /// Call this function for get the event
    virtual arcade::CommandType pollEvent(void) = 0;

    /// Call this function for init texture
    virtual void initTexture(std::string gameName) = 0;
};

extern "C"
{
    IGraph *createInterface();
}

#endif //CPP_ARCADE_IGRAPH_HH
