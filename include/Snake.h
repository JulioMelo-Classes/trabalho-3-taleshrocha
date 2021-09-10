#ifndef SNAKE_H_
#define SNAKE_H_
#include <iostream>
#include <utility>
#include <vector>
#include <string>
#include <memory>

//#include "Level.h"

class Snake{
private:
  //<! Attributes
  int life;
  int foodEaten;
  std::vector<std::pair<int, int>> body;
  enum positions{up, down, right, left};
  bool tail;
  int headPosition;

public:
  explicit Snake(int _life, std::pair<int, int> spawn, bool _tail);
  void turn(int _headPosition);
  void move(std::pair<int, int> position, bool food);
  void reset_body(std::pair<int, int> spawn);
  std::vector<std::pair<int, int>>* get_body();
  int get_life();
  int get_foodEaten();
  bool has_tail();
};

#endif // SNAKE_H_
