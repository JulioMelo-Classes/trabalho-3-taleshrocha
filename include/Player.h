#ifndef PLAYER_H_
#define PLAYER_H_
#include <iostream>
#include <utility>
#include <vector>
#include <string>
#include <memory>
#include "Level.h"

class Player{
 private:
  //<! Attributes
  std::vector<std::pair<int, int>> solution;

public:
  Player();

  template<class maze>
  std::vector<std::pair<int, int>> find_valid_positions(maze _maze, std::pair<int, int> spawn);
  bool find_solution(Level *level, std::pair<int, int> spawn);
  std::pair<int, int> next_move();

};

#endif // PLAYER_H_
