#include <iostream>
#include "SnakeGame.h"

using namespace std;

int main(int argc, char *argv[]){

    if(argc < 2){ // See if the maze file is not specified
        cout << "ERROR: Specify the maze file!" << endl;
        return 1;
    }

    SnakeGame game (argv[1]);
    game.loop(); //bloqueia aqui e só saí quando o jogo termina

    return 0;
}
