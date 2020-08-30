//
// Leaderboard.cpp for Leaderboard.cpp in /home/afou_n/tek2/c++/projets/cpp_arcade
//
// Made by Afou Nacerdine
// Login   <nacerdine.afou@epitech.eu>
//
// Started on  Sun Apr  9 12:53:18 2017 Afou Nacerdine
// Last update Sun Apr  9 20:29:03 2017 laurent
//

#include "Leaderboard.hh"

Leaderboard::Leaderboard()
{

}

Leaderboard::~Leaderboard()
{

}

void		Leaderboard::set_high_score(std::string const& namegame, std::string const& playername, int score)
{
  std::fstream file;

  file.open("./score/" + namegame + ".score", std::ios::out | std::ios::app);
  if (file.is_open())
    {
      file.seekg(0, std::ios::end);
      file << playername << std::endl;
      file << score << std::endl;
      file.close();
    }
}

std::vector<Leaderboard::HighScore> Leaderboard::getLeaderboard(std::string const & name)
{
  check_file(name);
  return (_Leaderboard);
}

void		Leaderboard::check_file(std::string const &namegame)
{
  std::ifstream file("./score/" + namegame + ".score", std::ios::in);
  std::string buffer = "";
  std::string result;
  std::string buffer_score;
  Leaderboard::HighScore	tmp;
  std::vector<Leaderboard::HighScore>	HighScore;
  int				i;

  _Leaderboard.erase(_Leaderboard.begin(), _Leaderboard.end());
  if (file.is_open())
    {
      while (getline(file, buffer))
	{
	  tmp.PlayerName = buffer;
	  getline(file, buffer_score);
	  tmp.Score = stoi(buffer_score);
	  HighScore.push_back(tmp);
	}
      file.close();
    }
  i = 0;
  while (HighScore.size() > 0 && i < 5)
    {
      _Leaderboard.push_back(HighScore[getHigh(HighScore)]);
      HighScore.erase(HighScore.begin() + getHigh(HighScore));
      i = i + 1;
    }
}

size_t		Leaderboard::getHigh(std::vector<Leaderboard::HighScore> const &highscore)
{
  HighScore	tmp;
  int		i;

  tmp = highscore[0];
  i = 0;
  while (i < highscore.size())
    {
      if (highscore[i].Score > tmp.Score)
	tmp = highscore[i];
      i = i + 1;
    }
  i = 0;
  while (highscore[i].Score != tmp.Score)
    i = i + 1;
  return (i);
}
