#include "SnakeGame.h"

using namespace std;

/**
 * @brief função auxiliar para fazer o programa esperar por alguns milisegundos
 * @param ms a quantidade de segundos que o programa deve esperar */
void wait(int ms){
    this_thread::sleep_for(chrono::milliseconds(ms));
}

/**
 * @brief função auxiliar para limpar o terminal */
void clearScreen(){
    //some C++ voodoo here ;D
#if defined _WIN32
    system("cls");
#elif defined (__LINUX__) || defined(__gnu_linux__) || defined(__linux__)
    system("clear");
#elif defined (__APPLE__)
    system("clear");
#endif
}

SnakeGame::SnakeGame(char *arg1, char *arg2){
    levelPath = arg1;
    mode = arg2;
    choice = "";
    frameCount = 0;
    initialize_game();
}

Level level; // TODO: Is that ok?
Player player; // TODO: Is that ok?
void SnakeGame::initialize_game(){
    int lineCount = 0, i = 0;
    size_t pos = 0;
    string line, token;
    string delimiter = " ";
    ifstream levelFile(levelPath);
    if(levelFile.is_open()){
        while(getline(levelFile, line)){ //pega cada linha do arquivo
            if(lineCount > 0){ //ignora a primeira linha já que ela contem informações que não são uteis para esse exemplo
                level.set_maze(line);
            }
            //else{
            //    while((pos = line.find(delimiter)) != std::string::npos){
            //        token = line.substr(0, pos); //Break the string into tokens.
            //        //switch(i){
            //        //    case 0: stringstream ss(token); ss >> level.lines; break;
            //        //    case 1: stringstream ss(token); ss >> level.colluns; break;
            //        //    case 2: stringstream ss(token); ss >> level.foods; break;
            //        //}
            //        i++;
            //    }
            //}
            lineCount++;
        }
    }
    else{
        //TODO: Make that better. Like return 1
        cout << "ERROR: Unable to open the mazes file!" << endl;
    }
    state = RUNNING;
}

void SnakeGame::process_actions(){
    switch(state){
    case WAITING_USER: //o jogo bloqueia aqui esperando o usuário digitar a escolha dele
        cin>>std::ws>>choice;
        break;
    default:
        //nada pra fazer aqui
        break;
    }
}

void SnakeGame::update(){
    switch(state){
    case RUNNING:
        if(frameCount>0 && frameCount%1000 == 0) //depois de 10 frames o jogo pergunta se o usuário quer continuar //TODO
            state = WAITING_USER;
        break;
    case WAITING_USER: //se o jogo estava esperando pelo usuário então ele testa qual a escolha que foi feita
        if(choice == "n"){
            state = GAME_OVER;
            game_over();
        }
        else{
            //pode fazer alguma coisa antes de fazer isso aqui
            state = RUNNING;
        }
        break;
    default:
        //nada pra fazer aqui
        break;
    }
}

bool firstTime = true; // Just to auxiliate TODO: Kill that later
void SnakeGame::render(){
    auto maze = level.get_maze();
    clearScreen();
    //if(player.find_solution(&level)){ future
    if(firstTime){
        player.find_solution(&level, make_pair(9, 3));
        firstTime = false;
    }

    pair<int, int> move = player.next_move();
    switch(state){
    case RUNNING:
        // TODO: Change that to level.drawn_maze(solution);
        // Drawn the maze in the screen line by line
        for(int line = 0; line < (int) maze->size(); line++){ // For the lines
            for(int column = 0; column < (int) (*maze)[line].size(); column++){ // For the columns
                if(line == move.first and column == move.second){
                    cout << "V";
                }
                else{
                    cout << (*maze)[line][column];
                }
            }
            cout << endl;
        }
        break;
    case WAITING_USER:
        cout<<"Você quer continuar com o jogo? (s/n)"<<endl;
        break;
    case GAME_OVER:
        cout<<"O jogo terminou!"<<endl;
        break;
    }
    frameCount++;
}

void SnakeGame::game_over(){ // TODO: Implement that
}

void SnakeGame::loop(){
    while(state != GAME_OVER){
        process_actions();
        update();
        render();
        wait(100);// espera 1 segundo entre cada frame
    }
}
