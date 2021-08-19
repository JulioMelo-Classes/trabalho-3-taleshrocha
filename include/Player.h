#ifndef PLAYER_H_
#define PLAYER_H_
#include <utility>


class Player{
 private:
  //<! Attributes
  std::pair<int, int> direction;

public:
  Player();

  //Direction or Pair next_move();
  bool find_solution();

};

#endif // PLAYER_H_
