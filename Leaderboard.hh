//
// Leaderboard.hh for  in /home/laurent/rendu/cpp_arcade
//
// Made by laurent
// Login   <laurent@epitech.net>
//
// Started on  Sun Apr  9 18:57:21 2017 laurent
// Last update Sun Apr  9 19:09:44 2017 laurent
//

#ifndef LEADERBOARD_HH_
# define LEADERBOARD_HH_

# include <iostream>
# include <vector>
# include <map>
# include <fstream>
# include <iostream>

class	Leaderboard
{
public:
    struct		HighScore
    {
        std::string	PlayerName;
        size_t	Score;
    };
private:
  std::vector<HighScore>	_Leaderboard;
public:
  Leaderboard();
  ~Leaderboard();
  void		set_high_score(std::string const&, std::string const &, int);
  void		check_file(std::string const &);
  size_t	getHigh(std::vector<HighScore> const &);
  std::vector<HighScore>	getLeaderboard(std::string const &);
};

#endif /* !LEADERBOARD_HH_ */
