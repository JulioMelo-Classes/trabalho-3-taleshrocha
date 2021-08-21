#include "Player.h"

using namespace std;

Player::Player(){

}

template<class maze>
vector<pair<int, int>> Player::find_valid_positions(maze _maze, pair<int, int> spawn){ //TODO: pass by reference
  vector<pair<int, int>> validPositions;
  // Se all the possible places that the snake can go and store them in the validPositions vector
  for(int x = -1; x < 2; x++){
   for(int y = -1; y < 2; y++){
     if((spawn.first + x < 14 and spawn.second + y < 9) and
        (spawn.first + x > 0 and spawn.second + y > 0) and
        ((*_maze)[spawn.first + x, spawn.second + y] != "#")){
       validPositions.push_back(make_pair(spawn.first + x, spawn.second + y));
     }
   }
  }
  return validPositions;
}

bool Player::find_solution(Level *level, vector<pair<int, int>> *solution, pair<int, int> spawn){
  int i = 0;
  auto maze = level->get_maze();
  vector<pair<int, int>> validPositions;
  pair<int, int> randomPosition;

  do{
    validPositions = find_valid_positions(maze, spawn);
    // Creates a random solution
    randomPosition = validPositions[rand() % validPositions.size()]; //TODO: .size() + 1?
    spawn = randomPosition;
    solution->push_back(randomPosition);
    i++;
  } while(i != 1000);
  //} while(validPositions.size() != 0);

  for(auto pair : *solution){
    //cout << pair.first << " " << pair.second << endl;
  }

  return true;
}

//pair<int, int> Player::next_move(){
//}
