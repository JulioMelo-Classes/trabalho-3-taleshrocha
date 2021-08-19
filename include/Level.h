#ifndef LEVEL_H_
#define LEVEL_H_
#include <vector>
#include <string>

class Level{
 private:
  int lines, colluns, food;
  std::vector<std::string> maze; //<! vector contendo o labirinto atual, pode ser interpretado como uma matriz

 public:
  Level();
  void set_lines(int _lines);
  void set_colluns(int _colluns);
  void set_food(int _food);
};

#endif // LEVEL_H_
