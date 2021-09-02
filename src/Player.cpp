#include "Player.h"

using namespace std;

Player::Player(){ // TODO: Make that useful
}

std::vector<std::pair<int, int>> Player::find_valid_positions(std::shared_ptr<Level> level, std::shared_ptr<Snake> snake){
  vector<pair<int, int>> validPositions; // Is where all the valid positions around the snake go
  bool bite = false; // Just to auxiliate
  auto maze = level->get_maze();
  auto body = snake->get_body();


  // Se all the possible places around the snake that it can go and stores them in the validPositions vector
  for(int x = -1; x < 2; x++){   // For the lines
    for(int y = -1; y < 2; y++){ // For the columns
      if(((*body)[0].first + x < (int) level->get_maze_height() and (*body)[0].second + y < (int) level->get_maze_width()) // Can't be outside the maze
         and ((*body)[0].first + x > 0  and (*body)[0].second + y > 0)     // Can't be outside the maze
         and ((*maze)[(*body)[0].first + x][(*body)[0].second + y] != '#') // Can't be in the wall
         and !(x == 0 and y == 0)                                          // Can't be in the same spot
         and !(x != 0 and y != 0)){                                        // Can't be in the diagonals
        for(int i = 1; i < (int) body->size(); i++){ // See if the snake will not bite it's tail at any spot
          if((*body)[0].first + x == (*body)[i].first and (*body)[0].second + y == (*body)[i].second){
            cout << "BITE" << endl;
            bite = true;
            break;
          }
        }
        if(!bite){
          validPositions.push_back(make_pair((*body)[0].first + x, (*body)[0].second + y));
        }
        bite = false;
      }
    }
  }

  return validPositions;
}

bool Player::find_solution(std::shared_ptr<Level> level, std::shared_ptr<Snake> snake){
  solution.clear(); // Deletes all old solutions
  moveCounter = -1; // Resets the counter
  vector<pair<int, int>> validPositions; // Store all the save positions generated by find_valid_positions
  auto maze = level->get_maze();
  auto body = snake->get_body();
  cout << "IN FIND_SOLUTION" << endl;
  for(int i = 0; i < (int) body->size(); i++)
    cout << "bodyLog["<< i << "]: " << (*body)[i].first << " | " << (*body)[i].second << endl;
  cout <<  "END" << endl;

  // Pics a random position of the validPositions and stores it in the solution vector
  while((*maze)[(*body)[0].first][(*body)[0].second] != '$'){
    validPositions = find_valid_positions(level, snake);
    cout << validPositions.size() << endl;
    if(!validPositions.size()){
      return false;
    }
    snake->move(validPositions[rand() % validPositions.size()], false);
    solution.push_back((*body)[0]);
  }

  return true;
}

pair<int, int> Player::next_move(){
  moveCounter++;
  return solution[moveCounter];
}
