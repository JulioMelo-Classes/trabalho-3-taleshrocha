#include <iostream>
#include "SnakeGame.h"

using namespace std;

int main(int argc, char *argv[]){

    srand(time(NULL)); //Creates the seed to generate random numbers. //TODO
    if(argc < 3){ // See if the maze file is not specified
        cout << "ERROR: Specify the maze file and the game mode (tail or notail)!" << endl;
        return 1;
    }

    SnakeGame game (argv[1], argv[2]);
    game.loop(); //bloqueia aqui e só saí quando o jogo termina

    return 0;
}
