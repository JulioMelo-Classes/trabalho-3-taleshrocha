#ifndef SNAKE_H_
#define SNAKE_H_
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

public:
  Snake(int _life, int _foodEaten);
};

#endif // SNAKE_H_
