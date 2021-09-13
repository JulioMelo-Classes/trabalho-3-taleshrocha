#ifndef LEVEL_H_
#define LEVEL_H_
#include <vector>
#include <iostream>
#include <string>
#include <memory>
#include "Snake.h"

class Level{
private:
  //<! Attributes
  int mazeHeight;                                      //<! The height of the maze vector.
  int mazeWidth;                                       //<! The width of the maze vector.
  int foodQuantity;                                    //<! How many times the food is going to be spawn in the map.
  int foodLeft;                                        //<! How many times the food is going to be spawn in the map.
  std::pair<int, int> spawn;                           //<! The snake spawn point. The "*".
  std::vector<std::string> maze;                       //<! Vector containing the maze.
  std::vector<std::pair<int, int>> foodValidPositions; //<! Store all the positions that the food can go in the map.
  std::pair<int, int> foodPosition;                    //<! To store the food position.

public:
  /* @brief The class constructor.
   * @param std::vector<std::string> _maze: A vector containing the maze structure.
   * @param int _mazeHeight: The height of the maze.
   * @param int _mazeWidth: The width of the maze.
   * @param int _foodQuantity: How many food there is in the map.
   * @param std::pair<int, int> _spawn: The default snake's spawn point in the level. */
  Level(std::vector<std::string> _maze, int _mazeHeight, int _mazeWidth, int _foodQuantity, std::pair<int, int> _spawn);

  /* @brief Get a pointer to the maze vector.
   * @return  A pointer to the vector containing the maze. */
  std::vector<std::string>* get_maze();

  /* @brief Gets the maze height.
   * @return A integer containing the mazeHeight attribute value. */
  int get_maze_height();

  /* @brief Gets the maze width.
   * @return A integer containing the mazewidth attribute value. */
  int get_maze_width();

  /* @brief Gets the how many food still in the maze.
   * @return A integer containing the foodLeft attribute value. */
  int get_foodLeft();

  /* @brief Removes the eaten food of the map puts a new one in a random position in it. The food will not be spawned in the snake body.
   * @param std::shared_ptr<Snake> snake: A smart pointer to the snake.
   * @param int foodEaten = 1: Decides how many food the snake eat when the function is called. The default is 1.
   * @return True if there is no more food in the map. False otherwise. */
  bool put_food(std::shared_ptr<Snake> snake, int foodEaten = 1);

  /* @brief Gets the level's snake spawn coordinates.
   * @return A pair containing the spawn coordinates. */
  std::pair<int, int> get_spawn();

  // @brief Renders the maze in the screen. Used in the render function in SnakeGame.
  void render(std::shared_ptr<Snake> snake);

  // @brief Prints the game initial screen.
  void wellcome();

  // @brief Resets the level, in this case, the levels foods quantity to its default.
  void reset();
};

#endif // LEVEL_H_
