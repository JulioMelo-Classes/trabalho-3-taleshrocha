#ifndef SNAKE_H_
#define SNAKE_H_
// TODO: revide those includes
#include <iostream>
#include <utility>
#include <vector>
#include <string>
#include <memory>
#include "Level.h"

class Snake{
private:
  //<! Attributes
  int life;
  int foodEaten;
  std::vector<std::pair<int, int>> body;
  enum positions{up, down, right, left};
  int headPosition;

public:
  explicit Snake(int _life, std::pair<int, int> spawn);
  void turn(int _headPosition);
  void move(std::pair<int, int> position, bool food);
};

#endif // SNAKE_H_
