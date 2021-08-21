#include "Level.h"

using namespace std;

Level::Level(){
  mazeHeight = 15;
  mazeWidth = 10;
}
void Level::set_maze(string line){
  maze.push_back(line);
}

vector<string>* Level::get_maze(){
  return &maze;
}
