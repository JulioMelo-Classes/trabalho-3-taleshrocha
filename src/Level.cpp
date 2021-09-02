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

void Level::put_food(){

 //   foodQuantity--;
 // if(foodQuantity == 0){ // The snake eat all the food
 //   return true;
 // }
 // else{
 //   return false;
 // }


  maze[foodPosition.first][foodPosition.second] = ' '; // Deletes the previous position
  foodPosition = foodValidPositions[rand() % foodValidPositions.size()]; // Gets the new position
  maze[foodPosition.first][foodPosition.second] = '$'; // Sets the new position
}

void Level::render(std::shared_ptr<Snake> snake){
  auto body = snake->get_body();

  bool print; // TODO: see if i can get rid of this



        //cout << "----SNAKE----" << endl;
        //for(int i = 0; i < (int) body->size(); i++)
        //    cout << "body["<< i <<"]: " << (*body)[i].first << " | " << (*body)[i].second << endl;
        //cout << "-------------" << endl;

        //cout << "----SNAKELOG----" << endl;
        //for(int i = 0; i < (int) bodyLog->size(); i++)
        //    cout << "bodyLog["<< i << "]: " << (*bodyLog)[i].first << " | " << (*bodyLog)[i].second << endl;
        //cout << "----------------" << endl;

  for(int line = 0; line < mazeHeight; line++){ // For the lines
    for(int column = 0; column < mazeWidth; column++){ // For the columns
      for(int i = 0; i < (int) body->size(); i++){
        if(line == ((*body)[i]).first and column == ((*body)[i]).second){
          if(i == 0)
            cout << "V";
          else
            cout << "O";
          print = true;
        }
      }
      if(!print){
        cout << maze[line][column];
      }
      print = false;
    }
    cout << endl;
  }
}
