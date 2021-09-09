#ifndef PLAYER_H_
#define PLAYER_H_
#include <iostream>
#include <utility>
#include <vector>
#include <string>
#include <memory>
#include "Level.h"
#include "Snake.h"
#include <chrono> //por causa do sleep
#include <thread> //por causa do sleep

class Player{
 private:
  //<! Attributes
  std::vector<std::pair<int, int>> solution;
  std::vector<std::pair<int, int>> visited;
  int moveCounter = -1; // To keep track of the next move in the move function
  std::pair<int, int> lastPos = std::make_pair(-1, -1);

public:
  Player();

  std::vector<std::pair<int, int>> find_valid_positions(std::shared_ptr<Level> level, std::shared_ptr<Snake> snake, std::pair<int, int> lastPos);

  bool find_solution(std::shared_ptr<Level> level, std::shared_ptr<Snake> snake);

  std::pair<int, int> next_move();

  void reset();
};

#endif // PLAYER_H_
