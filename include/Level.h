#ifndef LEVEL_H_
#define LEVEL_H_
#include <vector>
#include <string>
#include <memory>

class Level{
 private:
  int lines;
  int colluns;
  int food;
  int mazeHeight;
  int mazeWidth;
  std::vector<std::string> maze; //<! Vector containing the maze

 public:
  Level();
  void set_maze(std::string line);
  std::vector<std::string>* get_maze();
  std::pair<int, int> spawn;
};

#endif // LEVEL_H_
