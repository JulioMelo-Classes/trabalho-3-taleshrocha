#include "Snake.h"

Snake::Snake(int _life, std::pair<int, int> spawn, bool _tail){
  life = _life;
  foodEaten = 0;
  headPosition = up;
  tail = _tail;
  body.push_back(spawn); // Creates the head of my snake
}

void Snake::turn(int _headPosition){
  headPosition = _headPosition;
}

void Snake::move(std::pair<int, int> position, bool food){ // TODO: make that food var more understandable
  body.insert(body.begin(), position); // Puts the new head in the snake and makes it bigger

  if(!food){
    body.pop_back(); // Remove the point of the snake's tail, since the snake doesn't eat, it will not grow
  }
}

void Snake::reset_body(std::pair<int, int> spawn){
  body.clear();
  body.push_back(spawn); // Creates the head of my snake... Again
}

std::vector<std::pair<int, int>>* Snake::get_body(){
  return &body;
}

int Snake::get_life(){
  return life;
}

int Snake::get_foodEaten(){
  return foodEaten;
}
