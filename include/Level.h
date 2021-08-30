#ifndef LEVEL_H_
#define LEVEL_H_
#include <vector>
#include <string>
#include <memory>

class Level{
 private:
  unsigned int mazeHeight; //< The height of the maze vector
  unsigned int mazeWidth; //< The width of the maze vector
  unsigned int foodQuantity; //< How many times the food is going to be spawn in the map
  std::pair<int, int> spawn; //< The snake spawn point. The "*"
  std::vector<std::string> maze; //<! Vector containing the maze
  std::vector<std::pair<int, int>> foodValidPositions; //<! Store all the positions that the food can go in the map
  std::pair<int, int> foodPosition; //< To store the food position

 public:
  Level(std::vector<std::string> _maze, unsigned int _mazeHeight, unsigned int _mazeWidth, unsigned int _foodQuantity, std::pair<int, int> _spawn);

  void set_maze(std::string line);

  std::vector<std::string>* get_maze();

  unsigned int get_maze_height();

  unsigned int get_maze_width();

  unsigned int get_foodQuantity();

  bool eat_food(); // TODO: The snake eats the food, not the level

  void put_food();

  std::pair<int, int> get_spawn();

};

#endif // LEVEL_H_
