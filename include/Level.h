#ifndef LEVEL_H_
#define LEVEL_H_
#include <vector>
#include <string>
#include <memory>

class Level{
 private:
  int lines, colluns, food;
  std::vector<std::string> maze; //<! vector contendo o labirinto atual, pode ser interpretado como uma matriz
  int mazeHeight;
  int mazeWidth;

 public:
  Level();
  void set_maze(std::string line);
  //std::shared_ptr<std::vector<std::string>> get_maze();
  std::vector<std::string>* get_maze();
};

#endif // LEVEL_H_
