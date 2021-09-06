#include <iostream>
#include "SnakeGame.h"

using namespace std;

int main(int argc, char *argv[]){

    srand(time(NULL)); //Creates the seed to generate random numbers

    if(argc < 2){
        cout << "ERROR: Specify the maze file and the game mode (tail or non-tail)!" << endl;
        return 1;
    }
    if(argc < 3){
        cout << "ERROR: Specify the the game mode (tail or notail)!" << endl;
        return 2;
    }

    SnakeGame game (argv[1], argv[2]);
    game.loop(); // Leaves only when the game finishes

    return 0;
}
