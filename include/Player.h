#ifndef PLAYER_H_
#define PLAYER_H_
#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include "Level.h"
#include "Snake.h"

class Player{
private:
  //<! Attributes
  std::vector<std::pair<int, int>> solution;            //<! A vector containing all the steps to the food.
  std::vector<std::pair<int, int>> visited;             //<! A vector containing all the places in the map that the snake as passed by.
  int moveCounter = -1;                                 //<! To keep track of the next move in the move function.
  std::pair<int, int> lastPos = std::make_pair(-1, -1); //<! The snake's last position (coordinate in the map).

public:
  // @brief The class constructor.
  Player();

  /* @brief Finds all the positions around the snake that it can go.
   * @param std::shared_ptr<Level> level: A smart pointer to some level.
   * @param std::shared_ptr<Snake> snake: A smart pointer to some snake.
   * @param std::pair<int, int> lastPos: The snake's last position in the maze.
   * @return A vector containing all the coordinates of the valid places around the snake. */
  std::vector<std::pair<int, int>> find_valid_positions(std::shared_ptr<Level> level, std::shared_ptr<Snake> snake, std::pair<int, int> lastPos);

  /* @brief A recursive function that implements backtracking.
   * @param std::shared_ptr<Level> level: A smart pointer to some level.
   * @param std::shared_ptr<Snake> snake: A smart pointer to some snake.
   * @return True if finds a path to the food. False otherwise. */
  bool find_solution(std::shared_ptr<Level> level, std::shared_ptr<Snake> snake);

  /* @brief Gives the coordinates of the next movement the snake should do. Uses as base the solution vector.
   * @return The coordinates to the snake's next movement. */
  std::pair<int, int> next_move();

  // @brief Clears the solution and visited places vectors and resets the moveCounter attribute.
  void reset();
};

#endif // PLAYER_H_
