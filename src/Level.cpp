#include "Level.h"

using namespace std;

  Level::Level(vector<string> _maze, unsigned int _mazeHeight, unsigned int _mazeWidth, unsigned int _foodQuantity, pair<int, int> _spawn){
  for(auto line : _maze){
    maze.push_back(line);
  }
  mazeHeight = _mazeHeight;
  mazeWidth = _mazeWidth;
  foodQuantity = _foodQuantity;
  spawn = _spawn;

  for(int x = 0; x < mazeHeight; x++){  // For the lines
    for(int y = 0; y < mazeWidth; y++){ // For the columns
      if(maze[x][y] != '#'){
        foodValidPositions.push_back(make_pair(x, y));
      }
    }
  }
  foodPosition = foodValidPositions[rand() % foodValidPositions.size()];
  maze[foodPosition.first][foodPosition.second] = '$'; // Sets the first food position
}

vector<string>* Level::get_maze(){ // TODO: Maybe don't pass the vector reference... Maybe
  return &maze;
}

unsigned int Level::get_maze_height(){
  return mazeHeight;
}

unsigned int Level::get_maze_width(){
  return mazeWidth;
}

unsigned int Level::get_foodQuantity(){
  return foodQuantity;

}

pair<int, int> Level::get_spawn(){
  return spawn;
}

bool Level::eat_food(){
    foodQuantity--;
  if(foodQuantity == 0){ // The snake eat all the food
    return true;
  }
  else{
    return false;
  }
}

void Level::put_food(){
  maze[foodPosition.first][foodPosition.second] = ' '; // Deletes the previous position
  foodPosition = foodValidPositions[rand() % foodValidPositions.size()]; // Gets the new position
  maze[foodPosition.first][foodPosition.second] = '$'; // Sets the new position
}
