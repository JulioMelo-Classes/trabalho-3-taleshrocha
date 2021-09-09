#include "Player.h"

using namespace std;

void wait(int ms){
    this_thread::sleep_for(chrono::milliseconds(ms));
}

Player::Player(){ // TODO: Make that useful
}

bool Player::find_solution(std::shared_ptr<Level> level, std::shared_ptr<Snake> snake){
  auto maze = level->get_maze();
  auto body = snake->get_body();
  pair<int, int> lastPos = (*body)[0];
  bool bite = false; // just to auxiliate
  visited.push_back((*body)[0]);
  //wait(100);

  if((*maze)[(*body)[0].first][(*body)[0].second] == '$')
    return true;

  for(int x = -1; x < 2; x++){   // for the lines
    for(int y = -1; y < 2; y++){ // for the columns
      if(((*body)[0].first + x < (int) level->get_maze_height() and (*body)[0].second + y < (int) level->get_maze_width()) // can't be outside the maze
         and ((*body)[0].first + x > 0  and (*body)[0].second + y > 0)     // can't be outside the maze
         and ((*maze)[(*body)[0].first + x][(*body)[0].second + y] != '#') // can't be in the wall
         and !(x == 0 and y == 0)                                          // can't be in the same spot
         and !(x != 0 and y != 0)                                          // can't be in the diagonals
         and (find(visited.begin(), visited.end(), make_pair((*body)[0].first + x, (*body)[0].second + y)) == visited.end())
         and !(lastPos.first == (*body)[0].first + x and lastPos.second == (*body)[0].second + y)){ // can't be in the back
        for(int i = 1; i < (int) body->size(); i++){ // see if the snake will not bite it's tail at any spot
          if((*body)[0].first + x == (*body)[i].first and (*body)[0].second + y == (*body)[i].second){
            bite = true;
            break;
          }
        }
        if(!bite){
          cout << x << " " << y << endl;
          lastPos = (*body)[0];
          snake->move(make_pair((*body)[0].first + x, (*body)[0].second + y), false);
          visited.push_back((*body)[0]);
          if(find_solution(level, snake)){
            //solution.push_back((*body)[0]);
            solution.insert(solution.begin(), (*body)[0]);
            return true;
          }
        }
        bite = false;
      }
    }
  }
  //solution.push_back(make_pair(-1, -1));
  //cout << "CLEAR" << endl;
  //visited.clear();
  return false;
}

pair<int, int> Player::next_move(){
  moveCounter++;
  return solution[moveCounter];
}

void Player::reset(){
  solution.clear();
  moveCounter = -1;
}
