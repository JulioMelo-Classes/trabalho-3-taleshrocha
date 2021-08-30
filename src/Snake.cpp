#include "Snake.h"

Snake::Snake(int _life, std::pair<int, int> spawn){
  life = _life;
  foodEaten = 0;
  headPosition = up;
  body.push_back(spawn); // Creates the head of my snake
}

void Snake::turn(int _headPosition){
  headPosition = _headPosition;
}

void Snake::move(std::pair<int, int> position, bool food){
  body.insert(body.begin(), position); // Puts the new head in the snake and makes it bigger

  if(!food){
    body.pop_back(); // Remove the point of the snake's tail, since the snake doesn't eat, it will not grow
  }
}
