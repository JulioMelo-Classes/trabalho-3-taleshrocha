#include "Level.h"

using namespace std;

Level::Level(){ // TODO: Make that dynamic
  mazeHeight = 15;
  mazeWidth = 10;
  spawn = make_pair(9, 3); // TODO: Don't make hard code
}
void Level::set_maze(string line){
  maze.push_back(line);
}

vector<string>* Level::get_maze(){ // TODO: Maybe don't pass the vector reference... Maybe
  return &maze;
}
