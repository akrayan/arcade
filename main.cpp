//
// main.cpp for main.cpp in /home/rayan/CPP/cpp_arcade
//
// Made by Rayan
// Login   <raihane.akkache@epitech.net>
//
// Started on  Fri Mar 24 14:47:59 2017 Rayan
// Last update Thu Apr  6 09:03:52 2017 Rayan

#include "Arcade.hh"

int				main(int ac, char** av)
{
  Arcade			*Arc;

  if (ac < 2)
    {
      std::cerr << "Usage : ./exemple4 <libXXX.so>" << std::endl;
      return(1);
    }
  Arc = new Arcade(av[1]);
  Arc->core();
  delete Arc;
  return (0);
}
